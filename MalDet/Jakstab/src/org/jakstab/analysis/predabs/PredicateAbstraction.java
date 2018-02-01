/*
 * PredicateAbstraction.java - This file is part of the Jakstab project.
 * Copyright 2009-2010 Johannes Kinder <kinder@cs.tu-darmstadt.de>
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, see <http://www.gnu.org/licenses/>.
 */
package org.jakstab.analysis.predabs;

import java.util.BitSet;
import java.util.Collections;
import java.util.Set;

import org.jakstab.analysis.*;
import org.jakstab.cfa.CFAEdge;
import org.jakstab.cfa.Location;
import org.jakstab.cfa.StateTransformer;
import org.jakstab.rtl.Context;
import org.jakstab.rtl.expressions.*;
import org.jakstab.rtl.statements.*;
import org.jakstab.solver.Solver;
import org.jakstab.util.Characters;
import org.jakstab.util.Logger;
import org.jakstab.util.Pair;


/**
 * @author Johannes Kinder
 */
public class PredicateAbstraction implements ConfigurableProgramAnalysis {

	@SuppressWarnings("unused")
	private static final Logger logger = Logger.getLogger(PredicateAbstraction.class);
	
	/*
	 * @see org.jakstab.analysis.ConfigurableProgramAnalysis#initPrecision()
	 */
	@Override
	public Precision initPrecision(Location location, StateTransformer transformer) {
		return new PredicatePrecision();
	}

	/*
	 * @see org.jakstab.analysis.ConfigurableProgramAnalysis#initStartState(org.jakstab.cfa.Location)
	 */
	@Override
	public AbstractState initStartState(Location label) {
		return new PredicateAbstractionState();
	}

	/*
	 * @see org.jakstab.analysis.ConfigurableProgramAnalysis#merge(org.jakstab.analysis.AbstractState, org.jakstab.analysis.AbstractState, org.jakstab.analysis.Precision)
	 */
	@Override
	public AbstractState merge(AbstractState s1, AbstractState s2,
			Precision precision) {
		return CPAOperators.mergeSep(s1, s2, precision);
	}

	/*
	 * @see org.jakstab.analysis.ConfigurableProgramAnalysis#post(org.jakstab.analysis.AbstractState, org.jakstab.cfa.CFAEdge, org.jakstab.analysis.Precision)
	 */
	@Override
	public Set<AbstractState> post(final AbstractState state, CFAEdge edge,
			final Precision precision) {
		final RTLStatement statement = (RTLStatement)edge.getTransformer();
		final PredicateAbstractionState s = (PredicateAbstractionState)state;
		final PredicatePrecision prec = (PredicatePrecision)precision;
		final ExpressionFactory factory = ExpressionFactory.getInstance();
		return statement.accept(new DefaultStatementVisitor<Set<AbstractState>>() {

			private final Set<AbstractState> fallThroughState() {
				return Collections.singleton(state);
			}

			@Override
			public Set<AbstractState> visit(RTLAlloc stmt) {
				return fallThroughState();
			}

			@Override
			public Set<AbstractState> visit(RTLAssert stmt) {
				if (Solver.isSatisfiable(factory.createAnd(s.getStateFormula(prec), factory.createNot(stmt.getAssertion())))) {
					logger.error("Found possible assertion violation at " + stmt.getLabel() + "! " + stmt + " evaluated to " + Characters.TOP + " in state:");
					logger.error(s);
				}
				return fallThroughState();
			}

			@Override
			public Set<AbstractState> visit(RTLAssignment stmt) {
				BitSet postPreds = (BitSet)s.predicates.clone();
				Writable lhs = stmt.getLeftHandSide();

				RTLExpression xprime = (lhs instanceof RTLVariable) ? 
						factory.createVariable("xprime" + lhs.getBitWidth(), lhs.getBitWidth()) : 
							factory.createMemoryLocation(1, ((RTLMemoryLocation)lhs).getAddress(), lhs.getBitWidth());

				Context subCtx = new Context();
				subCtx.substitute(lhs, xprime);

				Solver solver = Solver.createSolver();
				solver.addAssertion(s.getStateFormula(prec));
				solver.addAssertion(factory.createEqual(xprime, 
						stmt.getRightHandSide()));

				for (int predIdx = 0; predIdx <= PredicateMap.getMaxIndex(); predIdx++) { 
					RTLExpression p = PredicateMap.getPredicate(predIdx);
					if (lhs instanceof RTLVariable && !p.getUsedVariables().contains((RTLVariable)lhs)) 
						continue;
					// substitute x by xprime
					p = p.evaluate(subCtx);
					// check if the predicate holds or not
					solver.push();
					solver.addAssertion(factory.createNot(p));
					if (solver.isUnsatisfiable())
						postPreds.set(predIdx);
					else
						postPreds.clear(predIdx);
					solver.pop();
				}

				return Collections.singleton((AbstractState)new PredicateAbstractionState(postPreds));
			}

			@Override
			public Set<AbstractState> visit(RTLAssume stmt) {
				Solver solver = Solver.createSolver();
				solver.addAssertion(s.getStateFormula(prec));
				solver.addAssertion(stmt.getAssumption()); 
				if (solver.isUnsatisfiable())
					return Collections.emptySet();

				// Start with empty bitset since we don't skip any predicates
				BitSet postPreds = new BitSet();
				for (int predIdx = 0; predIdx <= PredicateMap.getMaxIndex(); predIdx++) { 
					RTLExpression p = PredicateMap.getPredicate(predIdx);
					// check if the predicate holds or not
					solver.push();
					solver.addAssertion(factory.createNot(p));
					if (solver.isUnsatisfiable())
						postPreds.set(predIdx);
					solver.pop();
				}

				return Collections.singleton((AbstractState)new PredicateAbstractionState(postPreds));
			}

			@Override
			public Set<AbstractState> visit(RTLDealloc stmt) {
				return fallThroughState();
			}

			@Override
			public Set<AbstractState> visit(RTLSkip stmt) {
				return fallThroughState();
			}
			
			
		});
	}

	@Override
	public AbstractState strengthen(AbstractState s, Iterable<AbstractState> otherStates,
			CFAEdge cfaEdge, Precision precision) {
		return s;
	}

	/*
	 * @see org.jakstab.analysis.ConfigurableProgramAnalysis#prec(org.jakstab.analysis.AbstractState, org.jakstab.analysis.Precision, org.jakstab.analysis.ReachedSet)
	 */
	@Override
	public Pair<AbstractState, Precision> prec(AbstractState s,
			Precision precision, ReachedSet reached) {
		return Pair.create(s, precision);
	}

	/*
	 * @see org.jakstab.analysis.ConfigurableProgramAnalysis#stop(org.jakstab.analysis.AbstractState, org.jakstab.analysis.ReachedSet, org.jakstab.analysis.Precision)
	 */
	@Override
	public boolean stop(AbstractState s, ReachedSet reached, Precision precision) {
		return CPAOperators.stopSep(s, reached, precision);
	}

}
