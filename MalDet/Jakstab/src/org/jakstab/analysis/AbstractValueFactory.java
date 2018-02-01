/*
 * AbstractValueFactory.java - This file is part of the Jakstab project.
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

package org.jakstab.analysis;

import java.util.Collection;

import org.jakstab.rtl.expressions.RTLNumber;

public interface AbstractValueFactory<A extends AbstractValue> {
	
	public A createAbstractValue(RTLNumber n);
	
	public A createAbstractValue(Collection<RTLNumber> numbers);
	
	public A createTop(int bitWidth);

	public A createTrue();

	public A createFalse();

}
