/*
 * IntervalAnalysis.java - This file is part of the Jakstab project.
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
package org.jakstab.analysis.intervals;

import java.util.Collections;
import java.util.Map;
import java.util.Set;

import org.jakstab.Program;
import org.jakstab.analysis.*;
import org.jakstab.analysis.explicit.BasedNumberElement;
import org.jakstab.analysis.explicit.BasedNumberValuation;
import org.jakstab.cfa.CFAEdge;
import org.jakstab.cfa.Location;
import org.jakstab.cfa.StateTransformer;
import org.jakstab.rtl.expressions.*;
import org.jakstab.rtl.statements.*;
import org.jakstab.util.*;

/**
 * A reduced interval congruence analysis with regioned memory. Inspired by
 * Codesurfer's VSA domain. 
 * 
 * @author Johannes Kinder
 */
public class IntervalAnalysis implements ConfigurableProgramAnalysis {

	@SuppressWarnings("unused")
	private static final Logger logger = Logger.getLogger(IntervalAnalysis.class);

	/*
	 * @see org.jakstab.analysis.ConfigurableProgramAnalysis#initPrecision()
	 */
	@Override
	public Precision initPrecision(Location location, StateTransformer transformer) {
		return new IntervalPrecision();
	}

	/*
	 * @see org.jakstab.analysis.ConfigurableProgramAnalysis#initStartState(org.jakstab.rtl.RTLLabel)
	 */
	@Override
	public AbstractState initStartState(Location label) {
		IntervalState init = new IntervalState();
		init.setValue(Program.getProgram().getArchitecture().stackPointer(), 
				new IntervalElement(MemoryRegion.STACK, 0, 0, 0, 32));
		return init;
	}

	/*
	 * @see org.jakstab.analysis.ConfigurableProgramAnalysis#merge(org.jakstab.analysis.AbstractState, org.jakstab.analysis.AbstractState)
	 */
	@Override
	public AbstractState merge(AbstractState s1, AbstractState s2, Precision precision) {
		return ((IntervalState)s2).widen((IntervalState)s1);
	}

	/*
	 * @see org.jakstab.analysis.ConfigurableProgramAnalysis#post(org.jakstab.analysis.AbstractState, org.jakstab.analysis.StateTransformer, org.jakstab.analysis.Precision)
	 */
	@Override
	public Set<AbstractState> post(final AbstractState state, CFAEdge cfaEdge, Precision precision) {

		final RTLStatement statement = (RTLStatement)cfaEdge.getTransformer();
		final IntervalState iState = (IntervalState)state;

		return statement.accept(new DefaultStatementVisitor<Set<AbstractState>>() {
			
			private Set<AbstractState> fallThroughState() {
				return Collections.singleton(state);
			}

			@Override
			public Set<AbstractState> visit(RTLAssignment stmt) {
				Writable lhs = ((RTLAssignment)stmt).getLeftHandSide();
				// only store variables
				RTLExpression rhs = ((RTLAssignment)stmt).getRightHandSide();
				IntervalElement evaledRhs = iState.abstractEval(rhs);
				IntervalState post = new IntervalState(iState);
				if (lhs instanceof RTLVariable) {
					post.setValue((RTLVariable)lhs, evaledRhs);
					return Collections.singleton((AbstractState)post);
				} else if (lhs instanceof RTLMemoryLocation) {
					RTLMemoryLocation m = (RTLMemoryLocation)lhs;
					IntervalElement evaledAddress = iState.abstractEval(m.getAddress());
					post.setMemoryValue(evaledAddress, m.getBitWidth(), evaledRhs);
					return Collections.singleton((AbstractState)post);
				} else {
					return fallThroughState();
				}
			}

			@Override
			public Set<AbstractState> visit(RTLAssume stmt) {
				
				RTLExpression assumption = stmt.getAssumption();

				IntervalState post = new IntervalState(iState);
				
				// TODO: implement assume
				
				if (assumption instanceof RTLOperation) {
					RTLOperation op = (RTLOperation)assumption;
					switch (op.getOperator()) {
					case UNSIGNED_LESS_OR_EQUAL:
						RTLExpression lhs = op.getOperands()[0];
						RTLExpression rhs = op.getOperands()[1];
						IntervalElement evaledLhs = iState.abstractEval(lhs);
						IntervalElement evaledRhs = iState.abstractEval(rhs);

						if (evaledRhs.getLeft() >= 0) {
							IntervalElement uLessInt = new IntervalElement(
									evaledRhs.getRegion(), 0, 
									evaledRhs.getRight(), 1, evaledLhs.getBitWidth()
							);
							// TODO: Implement meet for interval elements for optimal result
							// uLessInt = uLessInt.meet(evaledLhs);
							// if uLessInt.isBot() return Collections.emptySet();
							// cheap but sound solution for now: only use new interval if it has less elements
							if (uLessInt.size() < evaledLhs.size()) {
								if (lhs instanceof RTLVariable) {
									post.setValue((RTLVariable)lhs, uLessInt);
								} else if (lhs instanceof RTLMemoryLocation) {
									RTLMemoryLocation m = (RTLMemoryLocation)lhs;
									IntervalElement evaledAddress = iState.abstractEval(m.getAddress());
									post.setMemoryValue(evaledAddress, m.getBitWidth(), uLessInt);
								}
							}
						}
						break;
					}
				}

				return Collections.singleton((AbstractState)post);
			}

			@Override
			public Set<AbstractState> visit(RTLAssert stmt) {
				return fallThroughState();
			}

			@Override
			public Set<AbstractState> visit(RTLSkip stmt) {
				return fallThroughState();
			}

			@Override
			public Set<AbstractState> visit(RTLAlloc stmt) {
				IntervalState post = new IntervalState(iState);
				Writable lhs = stmt.getPointer();

				// TODO: Detect whether this allocation is unique to allow strong updates
				MemoryRegion newRegion = MemoryRegion.createAsSummary("alloc" + stmt.getLabel());
				if (lhs instanceof RTLVariable) {
					post.setValue((RTLVariable)lhs, new IntervalElement(newRegion, 
							ExpressionFactory.getInstance().createNumber(0, 32)));
				} else {
					RTLMemoryLocation m = (RTLMemoryLocation)lhs;
					IntervalElement abstractAddress = iState.abstractEvalAddress(m);
					post.setMemoryValue(abstractAddress, m.getBitWidth(), 
							new IntervalElement(newRegion, 
									ExpressionFactory.getInstance().createNumber(0, 32)));
				}

				return Collections.singleton((AbstractState)post);
			}

			@Override
			public Set<AbstractState> visit(RTLDealloc stmt) {
				return fallThroughState();
			}

			@Override
			public Set<AbstractState> visit(RTLHavoc stmt) {
				IntervalState post = new IntervalState(iState);
				
				// Only create a single state with the havoc range, since this analysis
				// is not path sensitive
				post.setValue(stmt.getVariable(), 
						//new IntervalElement(ExpressionFactory.getInstance().createNumber(0, stmt.getVariable().getBitWidth()), 
								//(RTLNumber)stmt.getMaximum()));
						new IntervalElement(MemoryRegion.GLOBAL, 0, ((RTLNumber)stmt.getMaximum()).longValue(), 1, 
								stmt.getVariable().getBitWidth())
						);
				
				return Collections.singleton((AbstractState)post);
			}

			@Override
			public Set<AbstractState> visit(RTLUnknownProcedureCall stmt) {
				IntervalState post = new IntervalState(iState);
				for (RTLVariable var : stmt.getDefinedVariables()) {
					post.setValue(var, IntervalElement.getTop(var.getBitWidth()));
				}
				post.setMemoryValue(IntervalElement.getTop(Program.getProgram().getArchitecture().getAddressBitWidth()), 
						32, IntervalElement.getTop(32));
				return Collections.singleton((AbstractState)post);
			}
			
		});
	}

	@Override
	public AbstractState strengthen(AbstractState s, Iterable<AbstractState> otherStates,
			CFAEdge cfaEdge, Precision precision) {

		IntervalState state = (IntervalState)s;
		IntervalState strengthenedState = null;

		for (AbstractState t : otherStates) {
			// TODO: Does not work correctly if BoundedAddressTracking returns more than
			// 		 one successor state.
			if (t instanceof BasedNumberValuation) {
				BasedNumberValuation exState = (BasedNumberValuation)t;
				for (Map.Entry<RTLVariable, BasedNumberElement> entry : 
					exState.getVariableValuation()) {
					RTLVariable var = entry.getKey();
					BasedNumberElement exVal = entry.getValue();
					if (exVal.isTop() || exVal.isNumberTop())
						continue;
					if (state.getValue(var).isTop()) {
						if (strengthenedState == null) {
							strengthenedState = new IntervalState(state);
						}
						strengthenedState.setValue(var, new IntervalElement(exVal.getRegion(),
								exVal.getNumber()));
						//logger.debug("Strengthened state " + state.getIdentifier() + 
						//		" by setting " + var + " to " + state.getValue(var));
					}
				}
			}
		}
		
		return strengthenedState == null ? state : strengthenedState;
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
	 * @see org.jakstab.analysis.ConfigurableProgramAnalysis#stop(org.jakstab.analysis.AbstractState, org.jakstab.analysis.ReachedSet)
	 */
	@Override
	public boolean stop(AbstractState s, ReachedSet reached, Precision precision) {
		return CPAOperators.stopJoin(s, reached, precision);
	}

}
