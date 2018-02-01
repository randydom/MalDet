/*
 * ControlFlowReconstruction.java - This file is part of the Jakstab project.
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
package org.jakstab.analysis;

import java.util.*;

import org.jakstab.Options;
import org.jakstab.Program;
import org.jakstab.Algorithm;
import org.jakstab.analysis.callstack.CallStackAnalysis;
import org.jakstab.analysis.composite.CompositeProgramAnalysis;
import org.jakstab.analysis.explicit.BasedConstantPropagation;
import org.jakstab.analysis.explicit.ConstantPropagation;
import org.jakstab.analysis.explicit.BoundedAddressTracking;
import org.jakstab.analysis.intervals.IntervalAnalysis;
import org.jakstab.analysis.location.LocationAnalysis;
import org.jakstab.analysis.substitution.ExpressionSubstitutionAnalysis;
import org.jakstab.asm.*;
import org.jakstab.asm.x86.X86Instruction;
import org.jakstab.cfa.*;
import org.jakstab.rtl.*;
import org.jakstab.rtl.statements.BasicBlock;
import org.jakstab.util.*;

/**
 * The control flow reconstruction algorithm in the CPA framework.
 * 
 * @author Johannes Kinder
 */
public class ControlFlowReconstruction implements Algorithm {

	private class PriorityWorklist implements Worklist<AbstractState> {
		private FastSet<AbstractState> worklist = new FastSet<AbstractState>();
		private FastSet<AbstractState> priorityList = new FastSet<AbstractState>();
		
		@Override
		public AbstractState pick() {
			if (!priorityList.isEmpty()) {
				AbstractState p = priorityList.pick();
				//logger.info("Returning prioritized state at " + p.getLocation());
				return p;
			} else {
				return worklist.pick();
			}
		}
		
		@Override
		public boolean add(AbstractState a) {
			if (!program.containsLabel(((RTLLabel)(a.getLocation())))) {
				return priorityList.add(a);
			} else {
				if (priorityList.contains(a)) return false;
				else return worklist.add(a);
			}
		}
		
		public boolean isEmpty() {
			return priorityList.isEmpty() && worklist.isEmpty();
		}
		
		@Override
		public boolean remove(AbstractState a) {
			// Single | is intended, run remove on both
			return priorityList.remove(a) | worklist.remove(a);
		}

		@Override
		public int size() {
			return priorityList.size() + worklist.size();
		}

	}
	
	@SuppressWarnings("unused")
	private static final Logger logger = Logger.getLogger(ControlFlowReconstruction.class);
	
	private Program program;
	private ResolvingTransformerFactory transformerFactory;
	private CPAAlgorithm cpaAlgorithm;
	private String status;
	
	public ControlFlowReconstruction(Program program) {

		logger.info("Initializing control flow reconstruction.");
		
		this.program = program;

		// Init CPAs
		ConfigurableProgramAnalysis[] cpas = new ConfigurableProgramAnalysis[Options.cpas.length()];
		boolean addedExplicitAnalysis = false;
		
		for (int i=0; i<Options.cpas.length(); i++) {
			switch (Options.cpas.charAt(i)) {
			case 'c':
				logger.info("--- Using constant propagation.");
				cpas[i] = new ConstantPropagation();
				addedExplicitAnalysis = true;
				break;
			case 'b':
				logger.info("--- Using based constant propagation.");
				cpas[i] = new BasedConstantPropagation();
				addedExplicitAnalysis = true;
				break;
			case 'x':
				logger.info("--- Using bounded address tracking.");
				cpas[i] = new BoundedAddressTracking();
				addedExplicitAnalysis = true;
				break;
			case 'i':
				logger.info("--- Using interval analysis.");
				cpas[i] = new IntervalAnalysis();
				addedExplicitAnalysis = true;
				break;
			case 's':
				logger.info("--- Using call stack analysis.");
				cpas[i] = new CallStackAnalysis();
				break;
			case 'f':
				logger.info("--- Using forward expression substitution.");
				cpas[i] = new ExpressionSubstitutionAnalysis();
				break;
			default:
				logger.fatal("'" + Options.cpas.charAt(i) + "' does not reference a valid analysis!");
				System.exit(1);
			}
		}
		
		if (!addedExplicitAnalysis) {
			logger.fatal("You need to specify at least one explicit value analysis: c, b, x or i");
			System.exit(1);
		}
		
		ConfigurableProgramAnalysis cpa = new CompositeProgramAnalysis(
				new LocationAnalysis(),
				cpas
		);

		// Init State transformer factory
		if (Options.basicBlocks) {
			transformerFactory = new PessimisticBasicBlockFactory();
		} else {
			switch (Options.procedureAbstraction) {
			case 0: 
				transformerFactory = new PessimisticStateTransformerFactory();
				break;
			case 1:
				transformerFactory = new SemiOptimisticStateTransformerFactory();
				break;
			case 2:
				transformerFactory = new OptimisticStateTransformerFactory();
				break;
			default:
				throw new RuntimeException("Invalid procedure abstraction level: " + Options.procedureAbstraction);
			}
		}
		
		PriorityWorklist worklist = new PriorityWorklist();
		//FastSet<AbstractState> worklist = new FastSet<AbstractState>();

		cpaAlgorithm = new CPAAlgorithm(program, cpa, transformerFactory, worklist, Options.failFast);
	}

	public ReachedSet getReachedStates() {
		return cpaAlgorithm.getReachedStates();
	}
	
	public long getNumberOfStatesVisited()  {
		return cpaAlgorithm.getNumberOfStatesVisited();
	}
	
	public AbstractReachabilityTree getART() {
		return cpaAlgorithm.getART();
	}
	
	public boolean isCompleted() {
		return cpaAlgorithm.isCompleted();
	}
	
	public boolean isSound() {
		return !Options.ignoreWeakUpdates && transformerFactory.isSound();
	}
	
	public void run() {
		logger.info("Starting control flow reconstruction.");
		try {
			cpaAlgorithm.run();
			status = cpaAlgorithm.isCompleted() ? "OK" : "interrupted"; 
		} catch (StateException e) {
			logger.warn(e.getMessage());
			status = e.getClass().getSimpleName();
			
			Deque<AbstractState> trace = new LinkedList<AbstractState>();
			
			if (cpaAlgorithm.getART() != null) {
				if (Options.errorTrace) {

					AbstractState s = e.getState();
					while (s != null) {
						trace.addFirst(s);
						s = cpaAlgorithm.getART().getParent(s);
					}
					
					AbstractState last = null;
					logger.warn("==== Error trace ====");
					for (AbstractState state : trace) {

						// If we use basic blocks, don't attempt to print last edge (is probably a split block)
						if (transformerFactory instanceof PessimisticBasicBlockFactory && 
								state == e.getState())
							break;
						
						if (last != null) {
							for (CFAEdge edge : transformerFactory.getExistingOutEdges(last.getLocation())) {
								if (edge.getTarget().equals(state.getLocation())) {
									logger.warn(edge.getTransformer());
									break;
								}
							}
						}
						
						logger.warn("");
						logger.warn(state);
						logger.warn("");
						last = state;
					}

					// Replay basic block up to the error state location
					if (transformerFactory instanceof PessimisticBasicBlockFactory) {
						for (CFAEdge edge : transformerFactory.getExistingOutEdges(last.getLocation())) {
							BasicBlock bb = (BasicBlock)edge.getTransformer();
							if (bb.containsLocation(e.getState().getLocation())) {
								logger.warn(bb.toStringUntil(e.getState().getLocation()));
								break;
							}
						}
						logger.warn("State before last statement in block:");
						logger.warn(e.getState());
					} 
					// No basic block, just output all transformers where post possibly failed
					else {
						logger.warn("Edges from error state: ");
						for (CFAEdge edge : transformerFactory
								.getExistingOutEdges(e.getState().getLocation()))
							logger.warn(edge.getTransformer());
					}
					
					
					//logger.warn("Error state:");
					//logger.warn(s);
/*
					AbstractState p = cpaAlgorithm.getART().getParent(s);
					while (p != null) {
						//logger.warn(program.getStatement((RTLLabel)s.getLocation()));
						//logger.warn(s);
						//s = cpaAlgorithm.getART().getParent(s);
						for (CFAEdge edge : transformerFactory.getExistingOutEdges(p.getLocation())) {
							if (edge.getTarget().equals(s.getLocation())) {
								logger.warn(edge.getTransformer());
								break;
							}
						}
						logger.warn(p);
						s = p;
						p = cpaAlgorithm.getART().getParent(s);
					}
*/
				}

				if (Options.asmTrace) {
					logger.warn("==== Error trace (ASM) ====");
					AbsoluteAddress lastAddr = null;
					AbsoluteAddress addr = null;
					AbstractState s = e.getState();
					while (s != null) {
						
						lastAddr = addr;
						addr = ((RTLLabel)s.getLocation()).getAddress();
						if (!addr.equals(lastAddr) && program.getModule(addr) != null) {
							StringBuilder sb = new StringBuilder();
							SymbolFinder symFinder = program.getModule(addr).getSymbolFinder();
							sb.append(symFinder.getSymbolFor(addr));
							sb.append(":\t");
							Instruction instr = program.getInstruction(addr);
							if (instr != null) {
								if (instr instanceof X86Instruction &&
										((X86Instruction)instr).hasPrefixLOCK() &&
										((X86Instruction)instr).hasPrefixREPZ()) {
									sb.append(program.getStatement((RTLLabel)s.getLocation()));
								} else {
									sb.append(instr.toString(addr.getValue(), symFinder));
								}
							}
							if (symFinder.hasSymbolFor(addr)) sb.append(Characters.NEWLINE);
							logger.warn(sb.toString());
						}
						s = cpaAlgorithm.getART().getParent(s);
					}
				}
			} else {
				logger.warn("No ART has been built, cannot show backtrace!");
			}
			
		} catch (RuntimeException e) {
			// For other runtime exceptions (bugs in Jakstab), set the status to the name of the exception 
			status = e.toString();
			throw e;
		} finally {
			program.setCFA(transformerFactory.getCFA());
			program.setUnresolvedBranches(transformerFactory.getUnresolvedBranches());
		}
	}
	
	public void stop() {
		cpaAlgorithm.stop();
	}
	
	public String getStatus() {
		return status;
	}

}
