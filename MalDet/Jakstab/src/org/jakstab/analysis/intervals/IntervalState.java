/*
 * IntervalState.java - This file is part of the Jakstab project.
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

import java.util.*;

import org.jakstab.analysis.*;
import org.jakstab.cfa.Location;
import org.jakstab.rtl.expressions.*;
import org.jakstab.util.*;
import org.jakstab.util.MapMap.EntryIterator;

/**
 * @author Johannes Kinder
 */
public class IntervalState implements AbstractState {

	@SuppressWarnings("unused")
	private static final Logger logger = Logger.getLogger(IntervalState.class);
	private static long maxStateId = 0;
	
	public static IntervalState TOP = new IntervalState();
	
	private VariableValuation<IntervalElement> aVarVal;
	private PartitionedMemory<IntervalElement> aStore;
	private final long stateId;
	
	private IntervalState(VariableValuation<IntervalElement> aVarVal, 
			PartitionedMemory<IntervalElement> aStore) {
		this.aVarVal = aVarVal;
		this.aStore = aStore;
		this.stateId = ++maxStateId;
	}
	
	IntervalState(IntervalState proto) {
		this(new VariableValuation<IntervalElement>(proto.aVarVal), 
				new PartitionedMemory<IntervalElement>(proto.aStore));
	}
	
	public IntervalState() {
		this(new VariableValuation<IntervalElement>(IntervalElementFactory.getInstance()),
				new PartitionedMemory<IntervalElement>(IntervalElementFactory.getInstance()));
	}
	
	IntervalElement abstractEvalAddress(RTLMemoryLocation m) {
		IntervalElement abstractAddress = abstractEval(m.getAddress());
		if (m.getSegmentRegister() != null) {
			if (abstractAddress.getRegion() != MemoryRegion.GLOBAL)
				return IntervalElement.getTop(m.getBitWidth());
			IntervalElement segmentValue = abstractEval(m.getSegmentRegister());
			assert segmentValue.getLeft() == 0 && segmentValue.getRight() == 0 : 
				"Segment " + m.getSegmentRegister() + " has been assigned a value!";
			abstractAddress = new IntervalElement(segmentValue.getRegion(), 
					abstractAddress.getLeft(), abstractAddress.getRight(), 
					abstractAddress.getStride(), abstractAddress.getBitWidth());
		}
		return abstractAddress;
	}

	IntervalElement abstractEval(RTLExpression e) {
		return Lattices.joinAll(abstractEvalPowerSet(e));
	}

	Set<IntervalElement> abstractEvalPowerSet(RTLExpression e) {
		return e.accept(new ExpressionVisitor<Set<IntervalElement>>() {

			@Override
			public Set<IntervalElement> visit(RTLBitRange e) {
				IntervalElement first = Lattices.joinAll(e.getFirstBitIndex().accept(this));
				IntervalElement last = Lattices.joinAll(e.getLastBitIndex().accept(this));
				if (first.size() == 1 && last.size() == 1) {
					Set<IntervalElement> res = new FastSet<IntervalElement>();
					for (IntervalElement aOp : e.getOperand().accept(this)) {
						res.add(aOp.bitExtract((int)first.getLeft(), (int)last.getLeft()));
					}
					return res;
				} else {
					return Collections.singleton(IntervalElement.getTop(e.getBitWidth()));
				}
			}

			@Override
			public Set<IntervalElement> visit(RTLMemoryLocation e) {
				Set<IntervalElement> res = new FastSet<IntervalElement>();
				for (IntervalElement aAddress : e.getAddress().accept(this)) {
					res.addAll(getMemoryValuePowerSet(aAddress, e.getBitWidth()));
				}
				return res;
			}

			@Override
			public Set<IntervalElement> visit(RTLOperation e) {
				Tuple<Set<IntervalElement>> aOperandSets = 
					new Tuple<Set<IntervalElement>>(e.getOperandCount());
				for (int i=0; i<e.getOperandCount(); i++) {
					aOperandSets.set(i, e.getOperands()[i].accept(this));
				}

				int bitWidth = e.getBitWidth();

				Set<IntervalElement> res = new FastSet<IntervalElement>();

				for (Tuple<IntervalElement> aOperands : Sets.crossProduct(aOperandSets)) {

					IntervalElement result;

					switch (e.getOperator()) {
					case PLUS:
						result = aOperands.get(0);
						for (int i=1; i<aOperands.size(); i++) {
							result = result.plus(aOperands.get(i));
						}
						break;

					case MUL:
						result = aOperands.get(0);
						for (int i=1; i<aOperands.size(); i++) {
							result = result.multiply(aOperands.get(i));
						}
						break;

					case EQUAL:
						if (aOperands.get(0).size() == 1 && aOperands.get(1).size() == 1) {
							if(aOperands.get(0).getLeft() == aOperands.get(1).getLeft()) {
								result = IntervalElement.TRUE;
							} else {
								result = IntervalElement.FALSE;
							}
						} else {
							result = IntervalElement.getTop(bitWidth);
						}
						break;

					case SIGN_EXTEND: {
						int from = ((RTLNumber)e.getOperands()[0]).intValue();
						int to = ((RTLNumber)e.getOperands()[1]).intValue();
						result = aOperands.get(2).signExtend(from, to);
						break;
						}

					case ZERO_FILL: {
						int from = ((RTLNumber)e.getOperands()[0]).intValue();
						int to = ((RTLNumber)e.getOperands()[1]).intValue();
						result = aOperands.get(2).zeroFill(from, to);
						break;
						}

					default:
						result = IntervalElement.getTop(bitWidth);
					}

					res.add(result);

				}
				return res;
			}

			@Override
			public Set<IntervalElement> visit(RTLVariable e) {
				return Collections.singleton(getValue(e));
			}

			@Override
			public Set<IntervalElement> visit(RTLConditionalExpression e) {
				Set<IntervalElement> res = new FastSet<IntervalElement>();
				res.addAll(e.getTrueExpression().accept(this));
				res.addAll(e.getFalseExpression().accept(this));
				return res;
			}

			@Override
			public Set<IntervalElement> visit(RTLNondet e) {
				return Collections.singleton(IntervalElement.getTop(e.getBitWidth()));
			}

			@Override
			public Set<IntervalElement> visit(RTLNumber e) {
				return Collections.singleton(new IntervalElement(e));
			}

			@Override
			public Set<IntervalElement> visit(RTLSpecialExpression e) {
				return Collections.singleton(IntervalElement.getTop(e.getBitWidth()));
			}
			
		});
	}

	@Override
	public String getIdentifier() {
		return Long.toString(stateId);
	}

	@Override
	public Location getLocation() {
		throw new UnsupportedOperationException(this.getClass().getSimpleName() + " does not contain location information.");
	}
	
	protected IntervalElement getValue(RTLVariable var) {
		return aVarVal.get(var);
	}
	
	protected void setValue(RTLVariable var, IntervalElement value) {
		aVarVal.set(var, value);
	}
	
	protected IntervalElement getMemoryValue(IntervalElement pointer, int bitWidth) {
		if (pointer.isTop()) return IntervalElement.getTop(bitWidth);
		
		long offset = pointer.getLeft(); 
		IntervalElement res = aStore.get(pointer.getRegion(), offset, bitWidth);
		if (pointer.getStride() > 0) {
			offset+=pointer.getStride();
			for (;offset <= pointer.getRight(); offset += pointer.getStride()) {
				if (res.isTop()) {
					logger.info("Joined intervals to TOP while reading memory range " + pointer);
					return res;
				}
				IntervalElement v = aStore.get(pointer.getRegion(), offset, bitWidth);
				res = res.join(v);
			}
		}
		return res;
	}

	protected Set<IntervalElement> getMemoryValuePowerSet(IntervalElement pointer, int bitWidth) {
		if (pointer.isTop()) 
			return Collections.singleton(IntervalElement.getTop(bitWidth));
		
		Set<IntervalElement> res = new FastSet<IntervalElement>();
		for (long offset : pointer) {
			res.add(aStore.get(pointer.getRegion(), offset, bitWidth));
		}
		return res;
	}

	protected void setMemoryValue(IntervalElement pointer, int bitWidth, IntervalElement value) {
		if (!pointer.getRegion().isSummary() && pointer.size() == 1) {
			// Strong update
			aStore.set(pointer.getRegion(), 
					pointer.getLeft(), 
					bitWidth, value);
		} else {
			// Weak update
			if (pointer.getRegion().isTop() || pointer.size() > 100)
				aStore.setTop(pointer.getRegion());
			else {
				for (long i : pointer) {
					aStore.weakUpdate(pointer.getRegion(), i, bitWidth, value);
				}
			}
			
		}
	}

	private RTLExpression addClause(RTLExpression formula, RTLExpression clause) {
		if (formula != null) {
			return ExpressionFactory.getInstance().createAnd(formula, clause);
		} else {
			return clause;
		}
	}
	
	public RTLExpression getStateFormula() {
		ExpressionFactory factory = ExpressionFactory.getInstance();
		RTLExpression result = null;
		
		for (Map.Entry<RTLVariable, IntervalElement> entry : aVarVal) {
			RTLVariable var = entry.getKey();
			IntervalElement interval = entry.getValue();
			
			if (interval.size() == 1) {
				result = addClause(result, factory.createEqual(var, factory.createNumber(interval.getLeft(), var.getBitWidth())));
			} else {
				if (!interval.leftOpen()) {
					result = addClause(result, factory.createLessOrEqual(factory.createNumber(interval.getLeft(), var.getBitWidth()), var));
				}

				if (!interval.rightOpen()) {
					result = addClause(result, factory.createLessOrEqual(var, factory.createNumber(interval.getRight(), var.getBitWidth())));
				}
			}
		}
		
		if (result == null) {
			result = factory.TRUE;
		}

		return result;
	}


	@Override
	public IntervalState join(LatticeElement l) {
		IntervalState other = (IntervalState)l;
		if (isTop() || other.isBot()) return this;
		if (isBot() || other.isTop()) return other;

		// Join variable valuations
		VariableValuation<IntervalElement> jVarVal = aVarVal.join(other.aVarVal);
		PartitionedMemory<IntervalElement> jStore = aStore.join(other.aStore);
		
		return new IntervalState(jVarVal, jStore);
	}

	public IntervalState widen(IntervalState other) {
		if (isTop() || other.isBot()) return this;
		if (other.isTop()) return other;

		IntervalState widenedState = new IntervalState();
		// Widen variable valuations
		for (Map.Entry<RTLVariable,IntervalElement> entry : aVarVal) {
			RTLVariable var = entry.getKey();
			IntervalElement v = entry.getValue();
			widenedState.setValue(var, v.widen(other.getValue(var)));
		}
		
		// Widen memory
		for (EntryIterator<MemoryRegion, Long, IntervalElement> entryIt = aStore.entryIterator(); entryIt.hasEntry(); entryIt.next()) {
			MemoryRegion region = entryIt.getLeftKey();
			Long offset = entryIt.getRightKey();
			IntervalElement v = entryIt.getValue();
			int bitWidth = v.getBitWidth();
			widenedState.aStore.set(region, offset, bitWidth, 
					v.widen(other.aStore.get(region, offset, bitWidth)));
		}
		
		return widenedState;
	}

	@Override
	public Set<Tuple<RTLNumber>> projectionFromConcretization(
			RTLExpression... expressions) {
		Tuple<Set<RTLNumber>> tupleOfSets = new Tuple<Set<RTLNumber>>(expressions.length);
		for (int i=0; i<expressions.length; i++) {
			Set<RTLNumber> concreteValues = new FastSet<RTLNumber>();
			// Use the powerset evaluation to iterate over concrete values
			// more precisely (needed for jump tables)
			for (IntervalElement el : abstractEvalPowerSet(expressions[i])) {
				Set<RTLNumber> c = el.concretize();
				if (c == null) {
					concreteValues = null;
					break;
				} else {
					concreteValues.addAll(c);
				}
			}
			tupleOfSets.set(i, concreteValues);
		}
		//logger.info(Arrays.toString(expressions) + ": " + tupleOfSets);
		return Sets.crossProduct(tupleOfSets);
	}

	@Override
	public boolean isBot() {
		return false;
	}

	@Override
	public boolean isTop() {
		return aVarVal.isTop() && aStore.isTop();
	}

	@Override
	public boolean lessOrEqual(LatticeElement l) {
		if (this == l) return true;
		IntervalState other = (IntervalState)l;
		if (isBot() || other.isTop()) return true;
		if (isTop() || other.isBot()) return false;

		if (!aVarVal.lessOrEqual(other.aVarVal))
			return false;

		if (!aStore.lessOrEqual(other.aStore)) 
			return false;
		
		return true;
	}
	
	@Override
	public String toString() {
		return "I: " + aVarVal.toString() + " Mem:" + aStore.toString();  
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((aStore == null) ? 0 : aStore.hashCode());
		result = prime * result + ((aVarVal == null) ? 0 : aVarVal.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		IntervalState other = (IntervalState) obj;
		if (aStore == null) {
			if (other.aStore != null)
				return false;
		} else if (!aStore.equals(other.aStore))
			return false;
		if (aVarVal == null) {
			if (other.aVarVal != null)
				return false;
		} else if (!aVarVal.equals(other.aVarVal))
			return false;
		return true;
	}

}
