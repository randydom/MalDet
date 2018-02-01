/*
 * RTLAssignment.java - This file is part of the Jakstab project.
 * Copyright 2007-2010 Johannes Kinder <kinder@cs.tu-darmstadt.de>
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

package org.jakstab.rtl.statements;


import java.util.Set;

import org.jakstab.rtl.*;
import org.jakstab.rtl.expressions.*;
import org.jakstab.ssl.Architecture;
import org.jakstab.util.FastSet;
import org.jakstab.util.Logger;

/**
 * Assigns the value of the righthandside to the lefthandside. Has an explicit bit width, which should be
 * equal to the bitwidth of the lefthandside.
 * 
 * @author Johannes Kinder
 */
public class RTLAssignment extends AbstractRTLStatement implements RTLStatement {

	private static final Logger logger = Logger.getLogger(RTLAssignment.class);

	private static final long serialVersionUID = 77230387535470541L;

	private int bitWidth;
	private Writable leftHandSide;
	private RTLExpression rightHandSide;

	public RTLAssignment(int bitWidth, Writable leftHandSide, RTLExpression rightHandSide) {
		super();
		this.bitWidth = bitWidth;
		this.leftHandSide = leftHandSide;
		this.rightHandSide = rightHandSide;
	}

	@Override
	public RTLStatement evaluate(Context context) {
		invalidateCache();
		RTLExpression evaldRHS = this.rightHandSide.evaluate(context);
		int evaldBitWidth = this.bitWidth;

		if (evaldRHS == null) logger.warn("No more RHS after evaluation of " + this.toString());

		// remove all killed assignments from the context
		context.removeAssignment(leftHandSide.getDefinedVariablesOnWrite());

		RTLExpression evaldLHS = this.leftHandSide.evaluate(context);

		if (evaldLHS.equals(evaldRHS)) {
			//logger.debug("Removed self-assignment: " + evaldLHS + " = " + evaldRHS);
			return null;
		}

		// Only do this if the statement has already been instantiated
		if (isInstantiated()) {
			/* Remove bitranges on LHS */
			if (evaldLHS instanceof RTLBitRange) {
				//logger.debug("Normalizing bitrange: " + evaldLHS + " :=" +evaldBitWidth + "= " + evaldRHS);
				RTLBitRange bitrange = (RTLBitRange)evaldLHS;
				
				evaldRHS = bitrange.applyInverse(evaldRHS);
				evaldLHS = bitrange.getOperand();
				
				/*
				evaldLHS = bitrange.getOperand();
				int firstBit = ((RTLNumber)bitrange.getFirstBitIndex()).intValue();
				int lastBit = ((RTLNumber)bitrange.getLastBitIndex()).intValue();
				long bitMask = RTLBitRange.bitMask(0, firstBit - 1) | 
					RTLBitRange.bitMask(lastBit + 1, ((Writable)evaldLHS).getBitWidth());

				evaldRHS = factory.createOr(
						factory.createAnd(
								evaldLHS, 
								factory.createNumber(bitMask, evaldLHS.getBitWidth())
						),
						factory.createZeroFill( 
								factory.createNumber(lastBit + 1, 8),
								factory.createNumber(evaldLHS.getBitWidth() - 1, 8),
								evaldRHS
						)
				);*/
				
				// Recurse
				evaldRHS = evaldRHS.evaluate(context);
				evaldLHS = evaldLHS.evaluate(context);
				// Set bitwidth of the assignment to variable width
				evaldBitWidth = ((Writable)evaldLHS).getBitWidth();
				//logger.debug("Result: " + evaldLHS + " :=" + evaldBitWidth + "= " + evaldRHS);
			}
		}

		bitWidth = evaldBitWidth;
		rightHandSide = evaldRHS;
		if (evaldLHS instanceof Writable) {
			leftHandSide = (Writable)evaldLHS;
		} else {
			logger.error("Error: LHS of assignment no longer writable after evaluation: " + 
					this.leftHandSide.toString() + " = " + evaldLHS.toString());
		}
		return this;
	}
	
	public int getBitWidth() {
		return bitWidth;
	}

	public Writable getLeftHandSide() {
		return leftHandSide;
	}

	public RTLExpression getRightHandSide() {
		return rightHandSide;
	}

	@Override
	public void inferTypes(Architecture arch) throws TypeInferenceException {
		leftHandSide = (Writable)(leftHandSide.inferBitWidth(arch, bitWidth));
		rightHandSide = rightHandSide.inferBitWidth(arch, bitWidth);
	}

	@Override
	public String toString() {
		StringBuilder res = new StringBuilder(255);
		/*if (getLabel() != null) {
			res.append(getLabel());
			res.append(": ");
		}*/
		res.append(leftHandSide);
		res.append(" := ");
		/*if (bitWidth > 0) res.append(bitWidth);
		else res.append('?');
		res.append("= ");*/
		res.append(rightHandSide);
		return res.toString();
	}

	@Override
	protected SetOfVariables initDefinedVariables() {
		return new SetOfVariables(leftHandSide.getDefinedVariablesOnWrite());
	}

	@Override
	protected SetOfVariables initUsedVariables() {
		SetOfVariables usedVariables = new SetOfVariables();
		usedVariables.addAll(leftHandSide.getUsedVariablesOnWrite());
		usedVariables.addAll(rightHandSide.getUsedVariables());
		return usedVariables;
	}

	@Override
	protected Set<RTLMemoryLocation> initUsedMemoryLocations() {
		Set<RTLMemoryLocation> usedMemory = new FastSet<RTLMemoryLocation>();
		usedMemory.addAll(leftHandSide.getUsedMemoryLocationsOnWrite());
		usedMemory.addAll(rightHandSide.getUsedMemoryLocations());
		return usedMemory;
	}

	@Override
	public <T> T accept(StatementVisitor<T> visitor) {
		return visitor.visit(this);
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = super.hashCode();
		result = prime * result + bitWidth;
		result = prime * result
				+ ((leftHandSide == null) ? 0 : leftHandSide.hashCode());
		result = prime * result
				+ ((rightHandSide == null) ? 0 : rightHandSide.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!super.equals(obj))
			return false;
		if (getClass() != obj.getClass())
			return false;
		RTLAssignment other = (RTLAssignment) obj;
		if (bitWidth != other.bitWidth)
			return false;
		if (leftHandSide == null) {
			if (other.leftHandSide != null)
				return false;
		} else if (!leftHandSide.equals(other.leftHandSide))
			return false;
		if (rightHandSide == null) {
			if (other.rightHandSide != null)
				return false;
		} else if (!rightHandSide.equals(other.rightHandSide))
			return false;
		return true;
	}
	
}
