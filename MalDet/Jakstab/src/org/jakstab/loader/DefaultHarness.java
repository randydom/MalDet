/*
 * DefaultHarness.java - This file is part of the Jakstab project.
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
package org.jakstab.loader;

import org.jakstab.Program;
import org.jakstab.asm.AbsoluteAddress;
import org.jakstab.rtl.RTLLabel;
import org.jakstab.rtl.expressions.ExpressionFactory;
import org.jakstab.rtl.expressions.RTLExpression;
import org.jakstab.rtl.expressions.RTLVariable;
import org.jakstab.rtl.statements.*;
import org.jakstab.util.Logger;

/**
 * @author Johannes Kinder
 */
public class DefaultHarness implements Harness {
	
	@SuppressWarnings("unused")
	private static final Logger logger = Logger.getLogger(DefaultHarness.class);

	private long PROLOGUE_BASE = 0xface0000L;
	private long EPILOGUE_BASE = 0xfee70000L;
	private AbsoluteAddress prologueAddress = new AbsoluteAddress(PROLOGUE_BASE);
	private AbsoluteAddress epilogueAddress = new AbsoluteAddress(EPILOGUE_BASE);

	private ExpressionFactory factory = ExpressionFactory.getInstance();
	private RTLVariable esp = Program.getProgram().getArchitecture().stackPointer(); 
	
	@Override
	public void install(Program program) {

		StatementSequence seq = new StatementSequence();
		seq.addLast(new RTLAssignment(1, factory.createVariable("%DF", 1), factory.FALSE));
		
		// Pseudo-stackframe for in-procedure entry points during debugging
		//seq.addLast(new RTLAssignment(32, program.getArchitecture().framePointer(), program.getArchitecture().stackPointer()));
		//seq.addLast(new RTLAssignment(32, factory.createVariable("%ebx"), program.getArchitecture().stackPointer()));

		push32(seq, factory.createNumber(epilogueAddress.getValue(), 32));
		seq.addLast(new RTLGoto(factory.createNumber(program.getStart().getAddress().getValue(), 32), RTLGoto.Type.CALL));
		putSequence(program, seq, prologueAddress);
		
		program.setEntryAddress(prologueAddress);

		// epilogue with halt statement
		seq = new StatementSequence();
		//seq.addLast(new RTLSkip());
		seq.addLast(new RTLHalt());
		putSequence(program, seq, epilogueAddress);
	}
	
	private void push32(StatementSequence seq, RTLExpression value) {
		seq.addLast(new RTLAssignment(esp.getBitWidth(), esp, 
				factory.createPlus(esp, factory.createNumber(-4, esp.getBitWidth()))
		));
		if (value != null) {
			seq.addLast(new RTLAssignment(32, factory.createMemoryLocation(esp, 32), value));
		}
	}
	
	private void putSequence(Program program, StatementSequence seq, AbsoluteAddress address) {
		int rtlId = 0;
		for (RTLStatement stmt : seq) {
			stmt.setLabel(address, rtlId++);
			stmt.setNextLabel(new RTLLabel(address, rtlId));
		}
		seq.getLast().setNextLabel(null);

		// add stub statements to program
		for (RTLStatement s : seq)
			program.putStatement(s);
	}

	@Override
	public boolean contains(AbsoluteAddress a) {
		return (a.equals(prologueAddress) || a.equals(epilogueAddress));
	}

	@Override
	public AbsoluteAddress getFallthroughAddress(AbsoluteAddress a) {
		if (a.equals(prologueAddress))
			return epilogueAddress;
		else
			return null;
	}

}
