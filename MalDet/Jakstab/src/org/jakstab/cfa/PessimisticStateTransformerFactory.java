/*
 * PessimisticStateTransformerFactory.java - This file is part of the Jakstab project.
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
package org.jakstab.cfa;

import java.util.Set;

import org.jakstab.Options;
import org.jakstab.analysis.AbstractState;
import org.jakstab.asm.AbsoluteAddress;
import org.jakstab.rtl.Context;
import org.jakstab.rtl.RTLLabel;
import org.jakstab.rtl.expressions.ExpressionFactory;
import org.jakstab.rtl.expressions.RTLExpression;
import org.jakstab.rtl.expressions.RTLNumber;
import org.jakstab.rtl.statements.*;
import org.jakstab.util.FastSet;
import org.jakstab.util.Logger;
import org.jakstab.util.Tuple;

/**
 * Provides state transformers without assumptions about procedures. Call instructions
 * are treated as push / jmp combinations and return instructions as indirect jumps.
 * 
 * @author Johannes Kinder
 */
public class PessimisticStateTransformerFactory extends ResolvingTransformerFactory {

	@SuppressWarnings("unused")
	private static final Logger logger = Logger.getLogger(PessimisticStateTransformerFactory.class);
	
	@Override
	public Set<CFAEdge> resolveGoto(final AbstractState a, final RTLGoto stmt) {
		assert stmt.getCondition() != null;
		ExpressionFactory factory = ExpressionFactory.getInstance();
		Set<CFAEdge> results = new FastSet<CFAEdge>();

		Set<Tuple<RTLNumber>> valuePairs = a.projectionFromConcretization(
				stmt.getCondition(), stmt.getTargetExpression());
		for (Tuple<RTLNumber> pair : valuePairs) {
			RTLNumber conditionValue = pair.get(0);
			RTLNumber targetValue = pair.get(1);
			RTLLabel nextLabel;
			// assume correct condition case 
			assert conditionValue != null;
			RTLExpression assumption = 
				factory.createEqual(stmt.getCondition(), conditionValue);
			if (conditionValue.equals(factory.FALSE)) {
				// assume (condition = false), and set next statement to fallthrough
				nextLabel = stmt.getNextLabel();
			} else {
				if (targetValue == null) {
					// if target could not be resolved, just leave the edge out for now
					logger.info(stmt.getLabel() + ": Cannot resolve target expression " + 
							stmt.getTargetExpression() + ". Continuing with unsound underapproximation.");
					logger.debug("State is: " + a);
					sound = false;
					unresolvedBranches.add(stmt.getLabel());
					if (Options.debug)
						throw new ControlFlowException(a, "Unresolvable control flow from " + stmt.getLabel());
					continue;
				} else {
					// assume (condition = true AND targetExpression = targetValue)
					assumption = factory.createAnd(
							assumption,
							factory.createEqual(
									stmt.getTargetExpression(),
									targetValue)
					);
					// set next label to jump target
					nextLabel = new RTLLabel(new AbsoluteAddress(targetValue));
				}
			}
			assumption = assumption.evaluate(new Context());
			RTLAssume assume = new RTLAssume(assumption, stmt);
			assume.setLabel(stmt.getLabel());
			assume.setNextLabel(nextLabel);
			// Target address sanity check
			if (nextLabel.getAddress().getValue() < 10L) {
				logger.warn("Control flow from " + a.getLocation() + " reaches address " + nextLabel.getAddress() + "!");
			}

			results.add(new CFAEdge(assume.getLabel(), assume.getNextLabel(), assume));
		}
		return results;
	}
}
