/*
 * PredicateAbstractionState.java - This file is part of the Jakstab project.
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

import java.util.*;

import org.jakstab.analysis.AbstractState;
import org.jakstab.analysis.LatticeElement;
import org.jakstab.cfa.Location;
import org.jakstab.rtl.expressions.*;
import org.jakstab.util.Characters;
import org.jakstab.util.Logger;
import org.jakstab.util.Tuple;

public class PredicateAbstractionState implements AbstractState {

	@SuppressWarnings("unused")
	private static final Logger logger = Logger.getLogger(PredicateAbstractionState.class);
	
	final BitSet predicates;
	
	PredicateAbstractionState() {
		predicates = new BitSet();
	}
	
	PredicateAbstractionState(PredicateAbstractionState proto) {
		predicates = (BitSet)proto.predicates.clone();
	}
	
	PredicateAbstractionState(BitSet preds) {
		predicates = preds;
	}

	@Override
	public String getIdentifier() {
		return Integer.toString(hashCode());
	}

	@Override
	public Location getLocation() {
		throw new UnsupportedOperationException(this.getClass().getSimpleName() + " does not contain location information.");
	}

	@Override
	public AbstractState join(LatticeElement l) {
		return new PredicateAbstractionState();
	}

	@Override
	public Set<Tuple<RTLNumber>> projectionFromConcretization(
			RTLExpression... expressions) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean isBot() {
		return predicates == null;
	}

	@Override
	public boolean isTop() {
		return predicates.isEmpty();
	}
	
	Iterator<RTLExpression> predicateIterator() {
		return new Iterator<RTLExpression>() {
			int next = predicates.nextSetBit(0);

			public boolean hasNext() {
				return next >= 0;
			}

			public RTLExpression next() {
				if (next < 0) throw new NoSuchElementException();
				RTLExpression p = PredicateMap.getPredicate(next);
				next = predicates.nextSetBit(next + 1);
				return p;
			}

			public void remove() {
				throw new UnsupportedOperationException();
			}
		};
	}
	
	RTLExpression getStateFormula(PredicatePrecision prec) {
		ExpressionFactory factory = ExpressionFactory.getInstance();
		
		if (isTop()) return factory.TRUE;
		
		RTLExpression result = null;

		for (int i = predicates.nextSetBit(0); i >= 0; i = predicates.nextSetBit(i + 1)) {
			RTLExpression p = PredicateMap.getPredicate(i);
			if (result == null) result = p;
			else result = factory.createAnd(result, p);
		}
		assert(result != null);
		return result;
	}

	@Override
	public boolean lessOrEqual(LatticeElement l) {
		PredicateAbstractionState other = (PredicateAbstractionState)l;
		// return (this -> other)
		// 110 <= 100 but 110 !<= 101
		BitSet c = (BitSet)this.predicates.clone();
		// 110            111
		c.or(other.predicates);
		// true           false
		return (c.equals(this.predicates));
	}

	/*
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		if (isTop()) return Characters.TOP;
		if (isBot()) return Characters.BOT;
		StringBuilder res = new StringBuilder();
		for (Iterator<RTLExpression> predIter = predicateIterator(); predIter.hasNext();) {
			res.append("(");
			res.append(predIter.next());
			res.append(") ");
		}
		return res.toString();
	}

}
