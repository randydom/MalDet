// $ANTLR : "SSL.g" -> "SSLPreprocessor.java"$

	package org.jakstab.ssl.parser;

import antlr.TreeParser;
import antlr.Token;
import antlr.collections.AST;
import antlr.RecognitionException;
import antlr.ANTLRException;
import antlr.NoViableAltException;
import antlr.MismatchedTokenException;
import antlr.SemanticException;
import antlr.collections.impl.BitSet;
import antlr.ASTPair;
import antlr.collections.impl.ASTArray;

	import java.util.*;
	import org.jakstab.rtl.*;
	import org.jakstab.rtl.expressions.*;
	import org.jakstab.rtl.statements.*;

	@SuppressWarnings("all")


public class SSLPreprocessor extends antlr.TreeParser       implements SSLParserTokenTypes
 {

	private Map<String,Long> constants = new HashMap<String,Long>();
	private Map<String,List<AST>> tables = new HashMap<String,List<AST>>();
	private Map<String,SSLFunction> functions = new HashMap<String,SSLFunction>();
	private Map<String,SSLFunction> instructions = new TreeMap<String,SSLFunction>();
	private Stack<Map<String,AST>> locals = new Stack<Map<String,AST>>();
	private SetOfVariables registers = new SetOfVariables(); 
	private ExpressionFactory factory = ExpressionFactory.getInstance();

	public SetOfVariables getRegisters() { return registers; }	
	//public Map<String,SSLFunction> getFunctions() { return functions; }
	public Map<String,SSLFunction> getInstructions() { return instructions; }

	public Map<String,List<AST>> getTables() { return tables; }
	
public SSLPreprocessor() {
	tokenNames = _tokenNames;
}

	public final void start(AST _t) throws RecognitionException {
		
		AST start_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST start_AST = null;
		
		specification(_t);
		_t = _retTree;
		astFactory.addASTChild(currentAST, returnAST);
		start_AST = (AST)currentAST.root;
		returnAST = start_AST;
		_retTree = _t;
	}
	
	public final void specification(AST _t) throws RecognitionException {
		
		AST specification_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST specification_AST = null;
		
		AST __t256 = _t;
		AST tmp1_AST = null;
		AST tmp1_AST_in = null;
		tmp1_AST = astFactory.create((AST)_t);
		tmp1_AST_in = (AST)_t;
		astFactory.addASTChild(currentAST, tmp1_AST);
		ASTPair __currentAST256 = currentAST.copy();
		currentAST.root = currentAST.child;
		currentAST.child = null;
		match(_t,SEMI);
		_t = _t.getFirstChild();
		{
		_loop258:
		do {
			if (_t==null) _t=ASTNULL;
			if ((_tokenSet_0.member(_t.getType()))) {
				part(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
			}
			else {
				break _loop258;
			}
			
		} while (true);
		}
		currentAST = __currentAST256;
		_t = __t256;
		_t = _t.getNextSibling();
		specification_AST = (AST)currentAST.root;
		returnAST = specification_AST;
		_retTree = _t;
	}
	
	public final void part(AST _t) throws RecognitionException {
		
		AST part_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST part_AST = null;
		AST cn = null;
		AST cn_AST = null;
		AST tn = null;
		AST tn_AST = null;
		AST fn = null;
		AST fn_AST = null;
		AST fb = null;
		AST fb_AST = null;
		AST ib = null;
		AST ib_AST = null;
		
				long lv=0; 
				List<AST> tv; 
				List<String> pl; 
				List<SSLInstructionName> inam; 
			
		
		if (_t==null) _t=ASTNULL;
		switch ( _t.getType()) {
		case CONSTANT:
		{
			AST __t260 = _t;
			AST tmp2_AST = null;
			AST tmp2_AST_in = null;
			tmp2_AST = astFactory.create((AST)_t);
			tmp2_AST_in = (AST)_t;
			ASTPair __currentAST260 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,CONSTANT);
			_t = _t.getFirstChild();
			cn = (AST)_t;
			AST cn_AST_in = null;
			cn_AST = astFactory.create(cn);
			match(_t,NAME);
			_t = _t.getNextSibling();
			lv=const_expr(_t);
			_t = _retTree;
			currentAST = __currentAST260;
			_t = __t260;
			_t = _t.getNextSibling();
			
						constants.put(cn.getText(), Long.valueOf(lv));
					
			break;
		}
		case REGDECL:
		{
			AST __t261 = _t;
			AST tmp3_AST = null;
			AST tmp3_AST_in = null;
			tmp3_AST = astFactory.create((AST)_t);
			tmp3_AST_in = (AST)_t;
			ASTPair __currentAST261 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,REGDECL);
			_t = _t.getFirstChild();
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case LITERAL_INTEGER:
			{
				AST tmp4_AST_in = null;
				match(_t,LITERAL_INTEGER);
				_t = _t.getNextSibling();
				break;
			}
			case LITERAL_FLOAT:
			{
				AST tmp5_AST_in = null;
				match(_t,LITERAL_FLOAT);
				_t = _t.getNextSibling();
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			{
			_loop264:
			do {
				if (_t==null) _t=ASTNULL;
				if (((_t.getType() >= REG_ID && _t.getType() <= LSQUARE))) {
					register_decl(_t);
					_t = _retTree;
				}
				else {
					break _loop264;
				}
				
			} while (true);
			}
			currentAST = __currentAST261;
			_t = __t261;
			_t = _t.getNextSibling();
			break;
		}
		case TABLE:
		{
			AST __t265 = _t;
			AST tmp6_AST = null;
			AST tmp6_AST_in = null;
			tmp6_AST = astFactory.create((AST)_t);
			tmp6_AST_in = (AST)_t;
			ASTPair __currentAST265 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,TABLE);
			_t = _t.getFirstChild();
			tn = (AST)_t;
			AST tn_AST_in = null;
			tn_AST = astFactory.create(tn);
			match(_t,NAME);
			_t = _t.getNextSibling();
			tv=table_expr(_t);
			_t = _retTree;
			currentAST = __currentAST265;
			_t = __t265;
			_t = _t.getNextSibling();
			
						tables.put(tn.getText(), tv); 
					
			break;
		}
		case FUNCTION:
		{
			AST __t266 = _t;
			AST tmp7_AST = null;
			AST tmp7_AST_in = null;
			tmp7_AST = astFactory.create((AST)_t);
			tmp7_AST_in = (AST)_t;
			ASTPair __currentAST266 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,FUNCTION);
			_t = _t.getFirstChild();
			fn = (AST)_t;
			AST fn_AST_in = null;
			fn_AST = astFactory.create(fn);
			match(_t,NAME);
			_t = _t.getNextSibling();
			pl=param_list(_t);
			_t = _retTree;
			fb = (AST)_t;
			AST fb_AST_in = null;
			fb_AST = astFactory.create(fb);
			match(_t,RTL);
			_t = _t.getNextSibling();
			currentAST = __currentAST266;
			_t = __t266;
			_t = _t.getNextSibling();
			functions.put(fn.getText(), new SSLFunction(fn.getText(), pl, astFactory.dupTree(fb)));
			break;
		}
		case INSTR:
		{
			AST __t267 = _t;
			AST tmp8_AST = null;
			AST tmp8_AST_in = null;
			tmp8_AST = astFactory.create((AST)_t);
			tmp8_AST_in = (AST)_t;
			ASTPair __currentAST267 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,INSTR);
			_t = _t.getFirstChild();
			inam=instr_name(_t);
			_t = _retTree;
			pl=param_list(_t);
			_t = _retTree;
			ib = (AST)_t;
			AST ib_AST_in = null;
			ib_AST = astFactory.create(ib);
			match(_t,RTL);
			_t = _t.getNextSibling();
			currentAST = __currentAST267;
			_t = __t267;
			_t = _t.getNextSibling();
			
						for (SSLInstructionName in : inam) {
			if (in.getVarMap() != null) 
				locals.push(in.getVarMap()); 
			else 
				locals.push(new HashMap<String,AST>());
			rtl_expand(astFactory.dupTree(ib));
			locals.pop();
			AST rtl = getAST();
			
			if (instructions.containsKey(in.getName())) {
			SSLFunction oldIns = instructions.get(in.getName());
			/*                    if (oldpl != old_ip: TODO: JK - Check parameter list
			throw new SemanticException(#ib, "parameter list of '%s' changed" % n)*/
			if (rtl.getFirstChild() != null)
			oldIns.getAST().addChild(rtl.getFirstChild());
			} else
			instructions.put(in.getName(), new SSLFunction(in.getName(), pl, rtl));
						}
					
			break;
		}
		default:
		{
			throw new NoViableAltException(_t);
		}
		}
		returnAST = part_AST;
		_retTree = _t;
	}
	
	public final long  const_expr(AST _t) throws RecognitionException {
		long v=0;
		
		AST const_expr_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST const_expr_AST = null;
		AST n = null;
		AST n_AST = null;
		long l,r;
		
		if (_t==null) _t=ASTNULL;
		switch ( _t.getType()) {
		case NUM:
		{
			n = (AST)_t;
			AST n_AST_in = null;
			n_AST = astFactory.create(n);
			match(_t,NUM);
			_t = _t.getNextSibling();
			v = Long.parseLong(n.getText());
			break;
		}
		case PLUS:
		{
			AST __t275 = _t;
			AST tmp9_AST = null;
			AST tmp9_AST_in = null;
			tmp9_AST = astFactory.create((AST)_t);
			tmp9_AST_in = (AST)_t;
			ASTPair __currentAST275 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,PLUS);
			_t = _t.getFirstChild();
			l=const_expr(_t);
			_t = _retTree;
			r=const_expr(_t);
			_t = _retTree;
			currentAST = __currentAST275;
			_t = __t275;
			_t = _t.getNextSibling();
			v = l + r;
			break;
		}
		case MINUS:
		{
			AST __t276 = _t;
			AST tmp10_AST = null;
			AST tmp10_AST_in = null;
			tmp10_AST = astFactory.create((AST)_t);
			tmp10_AST_in = (AST)_t;
			ASTPair __currentAST276 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MINUS);
			_t = _t.getFirstChild();
			l=const_expr(_t);
			_t = _retTree;
			r=const_expr(_t);
			_t = _retTree;
			currentAST = __currentAST276;
			_t = __t276;
			_t = _t.getNextSibling();
			v = l - r;
			break;
		}
		default:
		{
			throw new NoViableAltException(_t);
		}
		}
		returnAST = const_expr_AST;
		_retTree = _t;
		return v;
	}
	
	public final void register_decl(AST _t) throws RecognitionException {
		
		AST register_decl_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST register_decl_AST = null;
		AST r1 = null;
		AST r1_AST = null;
		AST r2 = null;
		AST r2_AST = null;
		AST coveredRegFrom = null;
		AST coveredRegFrom_AST = null;
		AST coveredRegTo = null;
		AST coveredRegTo_AST = null;
		AST sharedReg = null;
		AST sharedReg_AST = null;
		
				int bitWidth; int regIdFrom; int regIdTo; int shareFrom = -1; int shareTo = -1;
				List<String> regList;
			
		
		if (_t==null) _t=ASTNULL;
		switch ( _t.getType()) {
		case INDEX:
		{
			AST tmp11_AST = null;
			AST tmp11_AST_in = null;
			tmp11_AST = astFactory.create((AST)_t);
			tmp11_AST_in = (AST)_t;
			match(_t,INDEX);
			_t = _t.getNextSibling();
			r1 = (AST)_t;
			AST r1_AST_in = null;
			r1_AST = astFactory.create(r1);
			match(_t,REG_ID);
			_t = _t.getNextSibling();
			regIdFrom=intValue(_t);
			_t = _retTree;
			
							registers.add((RTLVariable)factory.createRegisterVariable(r1.getText(), RTLVariable.UNKNOWN_BITWIDTH));
					
			break;
		}
		case REG_ID:
		{
			r2 = (AST)_t;
			AST r2_AST_in = null;
			r2_AST = astFactory.create(r2);
			match(_t,REG_ID);
			_t = _t.getNextSibling();
			AST tmp12_AST = null;
			AST tmp12_AST_in = null;
			tmp12_AST = astFactory.create((AST)_t);
			tmp12_AST_in = (AST)_t;
			match(_t,LSQUARE);
			_t = _t.getNextSibling();
			bitWidth=intValue(_t);
			_t = _retTree;
			AST tmp13_AST = null;
			AST tmp13_AST_in = null;
			tmp13_AST = astFactory.create((AST)_t);
			tmp13_AST_in = (AST)_t;
			match(_t,RSQUARE);
			_t = _t.getNextSibling();
			AST tmp14_AST = null;
			AST tmp14_AST_in = null;
			tmp14_AST = astFactory.create((AST)_t);
			tmp14_AST_in = (AST)_t;
			match(_t,INDEX);
			_t = _t.getNextSibling();
			regIdFrom=intValue(_t);
			_t = _retTree;
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case LITERAL_COVERS:
			{
				AST tmp15_AST_in = null;
				match(_t,LITERAL_COVERS);
				_t = _t.getNextSibling();
				coveredRegFrom = (AST)_t;
				AST coveredRegFrom_AST_in = null;
				coveredRegFrom_AST = astFactory.create(coveredRegFrom);
				match(_t,REG_ID);
				_t = _t.getNextSibling();
				AST tmp16_AST = null;
				AST tmp16_AST_in = null;
				tmp16_AST = astFactory.create((AST)_t);
				tmp16_AST_in = (AST)_t;
				match(_t,TO);
				_t = _t.getNextSibling();
				coveredRegTo = (AST)_t;
				AST coveredRegTo_AST_in = null;
				coveredRegTo_AST = astFactory.create(coveredRegTo);
				match(_t,REG_ID);
				_t = _t.getNextSibling();
				break;
			}
			case LITERAL_SHARES:
			{
				AST tmp17_AST_in = null;
				match(_t,LITERAL_SHARES);
				_t = _t.getNextSibling();
				sharedReg = (AST)_t;
				AST sharedReg_AST_in = null;
				sharedReg_AST = astFactory.create(sharedReg);
				match(_t,REG_ID);
				_t = _t.getNextSibling();
				AST tmp18_AST = null;
				AST tmp18_AST_in = null;
				tmp18_AST = astFactory.create((AST)_t);
				tmp18_AST_in = (AST)_t;
				match(_t,AT);
				_t = _t.getNextSibling();
				AST tmp19_AST = null;
				AST tmp19_AST_in = null;
				tmp19_AST = astFactory.create((AST)_t);
				tmp19_AST_in = (AST)_t;
				match(_t,LSQUARE);
				_t = _t.getNextSibling();
				shareFrom=intValue(_t);
				_t = _retTree;
				AST tmp20_AST = null;
				AST tmp20_AST_in = null;
				tmp20_AST = astFactory.create((AST)_t);
				tmp20_AST_in = (AST)_t;
				match(_t,TO);
				_t = _t.getNextSibling();
				shareTo=intValue(_t);
				_t = _retTree;
				AST tmp21_AST = null;
				AST tmp21_AST_in = null;
				tmp21_AST = astFactory.create((AST)_t);
				tmp21_AST_in = (AST)_t;
				match(_t,RSQUARE);
				_t = _t.getNextSibling();
				break;
			}
			case 3:
			case REG_ID:
			case INDEX:
			case LSQUARE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			
							if (coveredRegFrom != null) 
								throw new RuntimeException("COVERS not yet supported!");
							if (sharedReg != null) {
								factory.createSharedRegisterVariable(r2.getText(), sharedReg.getText(), shareFrom, shareTo);
							} else {
								registers.add((RTLVariable)factory.createRegisterVariable(r2.getText(), bitWidth));
							}
						
			break;
		}
		case LSQUARE:
		{
			AST tmp22_AST = null;
			AST tmp22_AST_in = null;
			tmp22_AST = astFactory.create((AST)_t);
			tmp22_AST_in = (AST)_t;
			match(_t,LSQUARE);
			_t = _t.getNextSibling();
			regList=register_list(_t);
			_t = _retTree;
			AST tmp23_AST = null;
			AST tmp23_AST_in = null;
			tmp23_AST = astFactory.create((AST)_t);
			tmp23_AST_in = (AST)_t;
			match(_t,RSQUARE);
			_t = _t.getNextSibling();
			AST tmp24_AST = null;
			AST tmp24_AST_in = null;
			tmp24_AST = astFactory.create((AST)_t);
			tmp24_AST_in = (AST)_t;
			match(_t,LSQUARE);
			_t = _t.getNextSibling();
			bitWidth=intValue(_t);
			_t = _retTree;
			AST tmp25_AST = null;
			AST tmp25_AST_in = null;
			tmp25_AST = astFactory.create((AST)_t);
			tmp25_AST_in = (AST)_t;
			match(_t,RSQUARE);
			_t = _t.getNextSibling();
			AST tmp26_AST = null;
			AST tmp26_AST_in = null;
			tmp26_AST = astFactory.create((AST)_t);
			tmp26_AST_in = (AST)_t;
			match(_t,INDEX);
			_t = _t.getNextSibling();
			regIdFrom=intValue(_t);
			_t = _retTree;
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case TO:
			{
				AST tmp27_AST = null;
				AST tmp27_AST_in = null;
				tmp27_AST = astFactory.create((AST)_t);
				tmp27_AST_in = (AST)_t;
				match(_t,TO);
				_t = _t.getNextSibling();
				regIdTo=intValue(_t);
				_t = _retTree;
				break;
			}
			case 3:
			case REG_ID:
			case INDEX:
			case LSQUARE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			
						for (String regName : regList) {
							registers.add((RTLVariable)factory.createRegisterVariable(regName, bitWidth));
						}
					
			break;
		}
		default:
		{
			throw new NoViableAltException(_t);
		}
		}
		returnAST = register_decl_AST;
		_retTree = _t;
	}
	
	public final List<AST>  table_expr(AST _t) throws RecognitionException {
		List<AST> res = null;
		
		AST table_expr_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST table_expr_AST = null;
		AST any = null;
		AST any_AST = null;
		AST n = null;
		AST n_AST = null;
		List<AST> h,t;
		
		if (_t==null) _t=ASTNULL;
		switch ( _t.getType()) {
		case LCURLY:
		{
			AST __t278 = _t;
			AST tmp28_AST = null;
			AST tmp28_AST_in = null;
			tmp28_AST = astFactory.create((AST)_t);
			tmp28_AST_in = (AST)_t;
			ASTPair __currentAST278 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LCURLY);
			_t = _t.getFirstChild();
			h=table_expr(_t);
			_t = _retTree;
			
				  		res = new LinkedList<AST>(h); /* Copy so we don't change the other table! */ 
				  	
			{
			_loop280:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_tokenSet_1.member(_t.getType()))) {
					t=table_expr(_t);
					_t = _retTree;
					res.addAll(t);
				}
				else {
					break _loop280;
				}
				
			} while (true);
			}
			currentAST = __currentAST278;
			_t = __t278;
			_t = _t.getNextSibling();
			break;
		}
		case CROSSP:
		{
			AST __t281 = _t;
			AST tmp29_AST = null;
			AST tmp29_AST_in = null;
			tmp29_AST = astFactory.create((AST)_t);
			tmp29_AST_in = (AST)_t;
			ASTPair __currentAST281 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,CROSSP);
			_t = _t.getFirstChild();
			h=table_expr(_t);
			_t = _retTree;
			res = h;
			{
			t=table_expr(_t);
			_t = _retTree;
			
						res = new LinkedList<AST>(); 
						for (AST tt : t) for (AST hh : h)
							res.add(astFactory.create(NAME, hh.getText() + tt.getText())); 
					
			}
			currentAST = __currentAST281;
			_t = __t281;
			_t = _t.getNextSibling();
			break;
		}
		case QUOTE:
		{
			AST __t283 = _t;
			AST tmp30_AST = null;
			AST tmp30_AST_in = null;
			tmp30_AST = astFactory.create((AST)_t);
			tmp30_AST_in = (AST)_t;
			ASTPair __currentAST283 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,QUOTE);
			_t = _t.getFirstChild();
			any = (AST)_t;
			AST any_AST_in = null;
			any_AST = astFactory.create(any);
			if ( _t==null ) throw new MismatchedTokenException();
			_t = _t.getNextSibling();
			currentAST = __currentAST283;
			_t = __t283;
			_t = _t.getNextSibling();
			res = new LinkedList<AST>(); res.add(astFactory.dupTree(any));
			break;
		}
		case NAME:
		{
			n = (AST)_t;
			AST n_AST_in = null;
			n_AST = astFactory.create(n);
			match(_t,NAME);
			_t = _t.getNextSibling();
			
					if (tables.containsKey(n.getText())) 
						res = tables.get(n.getText());
					else { res = new LinkedList<AST>(); res.add(n); 
						/*  lax specification of SSL seems to allow missing quotes? treat as string literal. 
						   throw new RecognitionException("Undefined table reference " + n.getText() + "!"); */ 
					}
				
			break;
		}
		default:
		{
			throw new NoViableAltException(_t);
		}
		}
		returnAST = table_expr_AST;
		_retTree = _t;
		return res;
	}
	
	public final List<String>  param_list(AST _t) throws RecognitionException {
		List<String> res = null;
		
		AST param_list_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST param_list_AST = null;
		AST n = null;
		AST n_AST = null;
		
		AST __t285 = _t;
		AST tmp31_AST = null;
		AST tmp31_AST_in = null;
		tmp31_AST = astFactory.create((AST)_t);
		tmp31_AST_in = (AST)_t;
		ASTPair __currentAST285 = currentAST.copy();
		currentAST.root = currentAST.child;
		currentAST.child = null;
		match(_t,COMMA);
		_t = _t.getFirstChild();
		res = new LinkedList<String>();
		{
		_loop287:
		do {
			if (_t==null) _t=ASTNULL;
			if ((_t.getType()==NAME)) {
				n = (AST)_t;
				AST n_AST_in = null;
				n_AST = astFactory.create(n);
				match(_t,NAME);
				_t = _t.getNextSibling();
				res.add(n.getText());
			}
			else {
				break _loop287;
			}
			
		} while (true);
		}
		currentAST = __currentAST285;
		_t = __t285;
		_t = _t.getNextSibling();
		returnAST = param_list_AST;
		_retTree = _t;
		return res;
	}
	
	public final List<SSLInstructionName>  instr_name(AST _t) throws RecognitionException {
		List<SSLInstructionName> res = null;;
		
		AST instr_name_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST instr_name_AST = null;
		List<SSLInstructionName> e;
		
		AST __t289 = _t;
		AST tmp32_AST = null;
		AST tmp32_AST_in = null;
		tmp32_AST = astFactory.create((AST)_t);
		tmp32_AST_in = (AST)_t;
		ASTPair __currentAST289 = currentAST.copy();
		currentAST.root = currentAST.child;
		currentAST.child = null;
		match(_t,INSTR_NAME);
		_t = _t.getFirstChild();
		res = new LinkedList<SSLInstructionName>();
		{
		_loop291:
		do {
			if (_t==null) _t=ASTNULL;
			if ((_t.getType()==NAME||_t.getType()==LSQUARE||_t.getType()==DECOR)) {
				e=instr_name_elem(_t);
				_t = _retTree;
				
								// If this is the first element, set result to this element's return value e.
								if (res.size() == 0) 
									res = e;
								// Otherwise, do a cross product of the previous result with e
								else {
					List<SSLInstructionName> tmp = new LinkedList<SSLInstructionName>();
					            for (SSLInstructionName lhsIn : res) {
					            for (SSLInstructionName rhsIn : e) {
					        Map newMap = new HashMap();
					        if (lhsIn.getVarMap() != null) newMap.putAll(lhsIn.getVarMap());
					        if (rhsIn.getVarMap() != null) newMap.putAll(rhsIn.getVarMap());
					                        tmp.add(new SSLInstructionName(lhsIn.getName() + rhsIn.getName(), newMap));
					            }
					    } 
					res = tmp;
								}
							
			}
			else {
				break _loop291;
			}
			
		} while (true);
		}
		currentAST = __currentAST289;
		_t = __t289;
		_t = _t.getNextSibling();
		returnAST = instr_name_AST;
		_retTree = _t;
		return res;
	}
	
	public final int  intValue(AST _t) throws RecognitionException {
		 int value = -1; ;
		
		AST intValue_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST intValue_AST = null;
		AST number = null;
		AST number_AST = null;
		
		number = (AST)_t;
		AST number_AST_in = null;
		number_AST = astFactory.create(number);
		astFactory.addASTChild(currentAST, number_AST);
		match(_t,NUM);
		_t = _t.getNextSibling();
		value = Integer.parseInt(number.getText());
		intValue_AST = (AST)currentAST.root;
		returnAST = intValue_AST;
		_retTree = _t;
		return value;
	}
	
	public final List<String>  register_list(AST _t) throws RecognitionException {
		List<String> res = new LinkedList<String>();
		
		AST register_list_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST register_list_AST = null;
		AST r = null;
		AST r_AST = null;
		AST rn = null;
		AST rn_AST = null;
		
		r = (AST)_t;
		AST r_AST_in = null;
		r_AST = astFactory.create(r);
		match(_t,REG_ID);
		_t = _t.getNextSibling();
		res.add(r.getText());
		{
		_loop273:
		do {
			if (_t==null) _t=ASTNULL;
			if ((_t.getType()==REG_ID)) {
				rn = (AST)_t;
				AST rn_AST_in = null;
				rn_AST = astFactory.create(rn);
				match(_t,REG_ID);
				_t = _t.getNextSibling();
				res.add(rn.getText());
			}
			else {
				break _loop273;
			}
			
		} while (true);
		}
		returnAST = register_list_AST;
		_retTree = _t;
		return res;
	}
	
	public final List<SSLInstructionName>  instr_name_elem(AST _t) throws RecognitionException {
		List<SSLInstructionName> res = null;;
		
		AST instr_name_elem_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST instr_name_elem_AST = null;
		AST name = null;
		AST name_AST = null;
		AST tname = null;
		AST tname_AST = null;
		AST vname = null;
		AST vname_AST = null;
		AST tidx = null;
		AST tidx_AST = null;
		AST d = null;
		AST d_AST = null;
		
			res = new LinkedList<SSLInstructionName>();
			List<AST> table = null;
		
		
		if (_t==null) _t=ASTNULL;
		switch ( _t.getType()) {
		case NAME:
		{
			name = (AST)_t;
			AST name_AST_in = null;
			name_AST = astFactory.create(name);
			match(_t,NAME);
			_t = _t.getNextSibling();
				
						res.add(new SSLInstructionName(name.getText())); 
					
			break;
		}
		case LSQUARE:
		{
			AST __t293 = _t;
			AST tmp33_AST = null;
			AST tmp33_AST_in = null;
			tmp33_AST = astFactory.create((AST)_t);
			tmp33_AST_in = (AST)_t;
			ASTPair __currentAST293 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LSQUARE);
			_t = _t.getFirstChild();
			tname = (AST)_t;
			AST tname_AST_in = null;
			tname_AST = astFactory.create(tname);
			match(_t,NAME);
			_t = _t.getNextSibling();
			
			if (tables.containsKey(tname.getText())) 
				table = tables.get(tname.getText());
						else throw new RecognitionException("Undefined table: "+ tname.getText());
					
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case NAME:
			{
				vname = (AST)_t;
				AST vname_AST_in = null;
				vname_AST = astFactory.create(vname);
				match(_t,NAME);
				_t = _t.getNextSibling();
				
								int i = 0;
								for (AST tableEntry : table) {
									Map<String,AST>  curVars = new HashMap<String,AST> (); 
									curVars.put(vname.getText(), (AST)astFactory.make( (new ASTArray(1)).add(astFactory.create(NUM,Integer.toString(i)))));
									res.add(new SSLInstructionName(tableEntry.getText(), curVars));
									i++;
								}
							
				break;
			}
			case NUM:
			{
				tidx = (AST)_t;
				AST tidx_AST_in = null;
				tidx_AST = astFactory.create(tidx);
				match(_t,NUM);
				_t = _t.getNextSibling();
				
								int index = Integer.parseInt(tidx.getText());
					if (index < table.size()) {
						res.add(new SSLInstructionName(table.get(index).getText())); 
					} else throw new RecognitionException("Index " + index + " out of bounds for table " + tname.getText() + "!");
							
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			currentAST = __currentAST293;
			_t = __t293;
			_t = _t.getNextSibling();
			break;
		}
		case DECOR:
		{
			d = (AST)_t;
			AST d_AST_in = null;
			d_AST = astFactory.create(d);
			match(_t,DECOR);
			_t = _t.getNextSibling();
			
						res.add(new SSLInstructionName('.' + d.getText().substring(1))); 
					
			break;
		}
		default:
		{
			throw new NoViableAltException(_t);
		}
		}
		returnAST = instr_name_elem_AST;
		_retTree = _t;
		return res;
	}
	
	public final void rtl_expand(AST _t) throws RecognitionException {
		
		AST rtl_expand_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST rtl_expand_AST = null;
		AST rt_AST = null;
		AST rt = null;
		AST name = null;
		AST name_AST = null;
		AST etname = null;
		AST etname_AST = null;
		AST etindex_AST = null;
		AST etindex = null;
		AST lexpr_AST = null;
		AST lexpr = null;
		AST otname = null;
		AST otname_AST = null;
		AST otindex_AST = null;
		AST otindex = null;
		AST rexpr_AST = null;
		AST rexpr = null;
		AST fname = null;
		AST fname_AST = null;
		AST farg_AST = null;
		AST farg = null;
		
		if (_t==null) _t=ASTNULL;
		if ((_t.getType()==RTL)) {
			AST __t296 = _t;
			AST tmp34_AST = null;
			AST tmp34_AST_in = null;
			tmp34_AST = astFactory.create((AST)_t);
			tmp34_AST_in = (AST)_t;
			ASTPair __currentAST296 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,RTL);
			_t = _t.getFirstChild();
			rtl_expand_AST = (AST)currentAST.root;
			rtl_expand_AST = astFactory.create(RTL,"RTL");
			currentAST.root = rtl_expand_AST;
			currentAST.child = rtl_expand_AST!=null &&rtl_expand_AST.getFirstChild()!=null ?
				rtl_expand_AST.getFirstChild() : rtl_expand_AST;
			currentAST.advanceChildToEnd();
			{
			_loop298:
			do {
				if (_t==null) _t=ASTNULL;
				if (((_t.getType() >= SEMI && _t.getType() <= DOT))) {
					rt = _t==ASTNULL ? null : (AST)_t;
					rtl_expand(_t);
					_t = _retTree;
					rt_AST = (AST)returnAST;
					rtl_expand_AST = (AST)currentAST.root;
					
					// do not nest RTL blocks
					if (rt.getType() == RTL) {
					if (rt.getFirstChild() != null)
					rtl_expand_AST.addChild(rt.getFirstChild());
					} else
					rtl_expand_AST.addChild(rt_AST);
								
				}
				else {
					break _loop298;
				}
				
			} while (true);
			}
			currentAST = __currentAST296;
			_t = __t296;
			_t = _t.getNextSibling();
		}
		else if ((_t.getType()==NAME)) {
			name = (AST)_t;
			AST name_AST_in = null;
			name_AST = astFactory.create(name);
			match(_t,NAME);
			_t = _t.getNextSibling();
			rtl_expand_AST = (AST)currentAST.root;
			
			String s = name_AST.getText();
			if (locals.peek().containsKey(s))
			rtl_expand_AST = astFactory.dupTree(locals.peek().get(s));
			else if (constants.containsKey(s))
			rtl_expand_AST = astFactory.create(NUM, Long.toString(constants.get(s)));
			else
			rtl_expand_AST = astFactory.dupTree(name_AST);
					
			currentAST.root = rtl_expand_AST;
			currentAST.child = rtl_expand_AST!=null &&rtl_expand_AST.getFirstChild()!=null ?
				rtl_expand_AST.getFirstChild() : rtl_expand_AST;
			currentAST.advanceChildToEnd();
		}
		else if ((_t.getType()==LSQUARE)) {
			AST __t299 = _t;
			AST tmp35_AST = null;
			AST tmp35_AST_in = null;
			tmp35_AST = astFactory.create((AST)_t);
			tmp35_AST_in = (AST)_t;
			ASTPair __currentAST299 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LSQUARE);
			_t = _t.getFirstChild();
			etname = (AST)_t;
			AST etname_AST_in = null;
			etname_AST = astFactory.create(etname);
			match(_t,NAME);
			_t = _t.getNextSibling();
			etindex = _t==ASTNULL ? null : (AST)_t;
			rtl_expand(_t);
			_t = _retTree;
			etindex_AST = (AST)returnAST;
			currentAST = __currentAST299;
			_t = __t299;
			_t = _t.getNextSibling();
			rtl_expand_AST = (AST)currentAST.root;
			
			List<AST> table = tables.get(etname_AST.getText());
			int index = Integer.parseInt(etindex_AST.getText());
			AST expr = table.get(index);
			rtl_expand_AST = astFactory.dupTree(expr);
					
			currentAST.root = rtl_expand_AST;
			currentAST.child = rtl_expand_AST!=null &&rtl_expand_AST.getFirstChild()!=null ?
				rtl_expand_AST.getFirstChild() : rtl_expand_AST;
			currentAST.advanceChildToEnd();
		}
		else if ((_t.getType()==LOOKUP_OP)) {
			AST __t300 = _t;
			AST tmp36_AST = null;
			AST tmp36_AST_in = null;
			tmp36_AST = astFactory.create((AST)_t);
			tmp36_AST_in = (AST)_t;
			ASTPair __currentAST300 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LOOKUP_OP);
			_t = _t.getFirstChild();
			lexpr = _t==ASTNULL ? null : (AST)_t;
			rtl_expand(_t);
			_t = _retTree;
			lexpr_AST = (AST)returnAST;
			otname = (AST)_t;
			AST otname_AST_in = null;
			otname_AST = astFactory.create(otname);
			match(_t,NAME);
			_t = _t.getNextSibling();
			otindex = _t==ASTNULL ? null : (AST)_t;
			rtl_expand(_t);
			_t = _retTree;
			otindex_AST = (AST)returnAST;
			rexpr = _t==ASTNULL ? null : (AST)_t;
			rtl_expand(_t);
			_t = _retTree;
			rexpr_AST = (AST)returnAST;
			currentAST = __currentAST300;
			_t = __t300;
			_t = _t.getNextSibling();
			rtl_expand_AST = (AST)currentAST.root;
			
			List <AST> table = tables.get(otname_AST.getText());
			int index = Integer.parseInt(otindex_AST.getText());
			AST op = table.get(index);
			op = astFactory.dupTree(op);
			rtl_expand_AST = (AST)astFactory.make( (new ASTArray(3)).add(op).add(lexpr_AST).add(rexpr_AST));
					
			currentAST.root = rtl_expand_AST;
			currentAST.child = rtl_expand_AST!=null &&rtl_expand_AST.getFirstChild()!=null ?
				rtl_expand_AST.getFirstChild() : rtl_expand_AST;
			currentAST.advanceChildToEnd();
		}
		else if ((_t.getType()==FUNCTION)) {
			AST __t301 = _t;
			AST tmp37_AST = null;
			AST tmp37_AST_in = null;
			tmp37_AST = astFactory.create((AST)_t);
			tmp37_AST_in = (AST)_t;
			ASTPair __currentAST301 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,FUNCTION);
			_t = _t.getFirstChild();
			fname = (AST)_t;
			AST fname_AST_in = null;
			fname_AST = astFactory.create(fname);
			match(_t,NAME);
			_t = _t.getNextSibling();
			List<AST> fargs = new LinkedList<AST>();
			{
			_loop303:
			do {
				if (_t==null) _t=ASTNULL;
				if (((_t.getType() >= SEMI && _t.getType() <= DOT))) {
					farg = _t==ASTNULL ? null : (AST)_t;
					rtl_expand(_t);
					_t = _retTree;
					farg_AST = (AST)returnAST;
					fargs.add(farg_AST);
				}
				else {
					break _loop303;
				}
				
			} while (true);
			}
			currentAST = __currentAST301;
			_t = __t301;
			_t = _t.getNextSibling();
			rtl_expand_AST = (AST)currentAST.root;
			
			SSLFunction f = functions.get(fname.getText());
						Map<String,AST> assignment = new HashMap<String,AST>();
						for (int i=0; i<f.getParameterCount(); i++)
							assignment.put(f.getParameter(i), fargs.get(i));
						if (assignment != null) locals.push(assignment); else locals.push(new HashMap<String,AST>());
			rtl_expand(f.getAST());
			rtl_expand_AST = this.getAST();
			locals.pop();
					
			currentAST.root = rtl_expand_AST;
			currentAST.child = rtl_expand_AST!=null &&rtl_expand_AST.getFirstChild()!=null ?
				rtl_expand_AST.getFirstChild() : rtl_expand_AST;
			currentAST.advanceChildToEnd();
		}
		else if (((_t.getType() >= SEMI && _t.getType() <= DOT))) {
			AST __t304 = _t;
			AST tmp38_AST = null;
			AST tmp38_AST_in = null;
			tmp38_AST = astFactory.create((AST)_t);
			tmp38_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp38_AST);
			ASTPair __currentAST304 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			if ( _t==null ) throw new MismatchedTokenException();
			_t = _t.getFirstChild();
			{
			_loop306:
			do {
				if (_t==null) _t=ASTNULL;
				if (((_t.getType() >= SEMI && _t.getType() <= DOT))) {
					rtl_expand(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
				}
				else {
					break _loop306;
				}
				
			} while (true);
			}
			currentAST = __currentAST304;
			_t = __t304;
			_t = _t.getNextSibling();
			rtl_expand_AST = (AST)currentAST.root;
		}
		else {
			throw new NoViableAltException(_t);
		}
		
		returnAST = rtl_expand_AST;
		_retTree = _t;
	}
	
	public final StatementSequence  convertToRTL(AST _t) throws RecognitionException {
		 StatementSequence statements = new StatementSequence(); ;
		
		AST convertToRTL_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST convertToRTL_AST = null;
		AST type = null;
		AST type_AST = null;
		AST other = null;
		AST other_AST = null;
		
			RTLExpression lhs = null; 
			RTLExpression rhs = null;
			RTLExpression cnt = null; 
			StatementSequence subStatements = null;
			int bitWidth = -1;
		
		
		if (_t==null) _t=ASTNULL;
		if ((_t.getType()==RTL)) {
			AST __t308 = _t;
			AST tmp39_AST = null;
			AST tmp39_AST_in = null;
			tmp39_AST = astFactory.create((AST)_t);
			tmp39_AST_in = (AST)_t;
			ASTPair __currentAST308 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,RTL);
			_t = _t.getFirstChild();
			{
			_loop310:
			do {
				if (_t==null) _t=ASTNULL;
				if (((_t.getType() >= SEMI && _t.getType() <= DOT))) {
					subStatements=convertToRTL(_t);
					_t = _retTree;
					statements.addLast(subStatements);
				}
				else {
					break _loop310;
				}
				
			} while (true);
			}
			currentAST = __currentAST308;
			_t = __t308;
			_t = _t.getNextSibling();
		}
		else if ((_t.getType()==ASSIGNTYPE)) {
			AST __t311 = _t;
			type = _t==ASTNULL ? null :(AST)_t;
			AST type_AST_in = null;
			type_AST = astFactory.create(type);
			ASTPair __currentAST311 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,ASSIGNTYPE);
			_t = _t.getFirstChild();
			
						String aType = type.getText();
						if (aType.length() >= 3) aType = aType.substring(1, aType.length() - 1);
						else aType = "0";
						if (aType.startsWith("f")) aType = aType.substring(1); // Float assigntype
						bitWidth = Integer.parseInt(aType);
					
			lhs=rtlExpr(_t,bitWidth);
			_t = _retTree;
			rhs=rtlExpr(_t,-bitWidth);
			_t = _retTree;
			currentAST = __currentAST311;
			_t = __t311;
			_t = _t.getNextSibling();
			
					statements.addFirst(new RTLAssignment(bitWidth, (Writable)lhs, rhs));
					//System.out.println("Got assigntype!" + statements.toString());
				
		}
		else if ((_t.getType()==LITERAL_MEMSET)) {
			AST __t312 = _t;
			AST tmp40_AST_in = null;
			ASTPair __currentAST312 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LITERAL_MEMSET);
			_t = _t.getFirstChild();
			bitWidth = constants.get("ADDRESSBITS").intValue();
			lhs=rtlExpr(_t,bitWidth);
			_t = _retTree;
			rhs=rtlExpr(_t,RTLVariable.UNKNOWN_BITWIDTH);
			_t = _retTree;
			cnt=rtlExpr(_t,bitWidth);
			_t = _retTree;
			currentAST = __currentAST312;
			_t = __t312;
			_t = _t.getNextSibling();
			
					statements.addFirst(new RTLMemset(lhs, rhs, cnt));
				
		}
		else if ((_t.getType()==LITERAL_MEMCPY)) {
			AST __t313 = _t;
			AST tmp41_AST_in = null;
			ASTPair __currentAST313 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LITERAL_MEMCPY);
			_t = _t.getFirstChild();
			bitWidth = constants.get("ADDRESSBITS").intValue();
			lhs=rtlExpr(_t,bitWidth);
			_t = _retTree;
			rhs=rtlExpr(_t,bitWidth);
			_t = _retTree;
			cnt=rtlExpr(_t,bitWidth);
			_t = _retTree;
			currentAST = __currentAST313;
			_t = __t313;
			_t = _t.getNextSibling();
			
					statements.addFirst(new RTLMemcpy(lhs, rhs, cnt));
				
		}
		else if (((_t.getType() >= SEMI && _t.getType() <= DOT))) {
			AST __t314 = _t;
			other = _t==ASTNULL ? null :(AST)_t;
			AST other_AST_in = null;
			other_AST = astFactory.create(other);
			ASTPair __currentAST314 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			if ( _t==null ) throw new MismatchedTokenException();
			_t = _t.getFirstChild();
			{
			_loop316:
			do {
				if (_t==null) _t=ASTNULL;
				if (((_t.getType() >= SEMI && _t.getType() <= DOT))) {
					AST tmp42_AST_in = null;
					if ( _t==null ) throw new MismatchedTokenException();
					_t = _t.getNextSibling();
				}
				else {
					break _loop316;
				}
				
			} while (true);
			}
			currentAST = __currentAST314;
			_t = __t314;
			_t = _t.getNextSibling();
			
					if (other.getText().equals("halt")) {
						statements.addFirst(new RTLHalt());
					} 
					else statements.addFirst(new RTLSkip()); 
				
		}
		else {
			throw new NoViableAltException(_t);
		}
		
		returnAST = convertToRTL_AST;
		_retTree = _t;
		return statements;
	}
	
	public final RTLExpression  rtlExpr(AST _t,
		int bw
	) throws RecognitionException {
		 RTLExpression ret = null;;
		
		AST rtlExpr_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST rtlExpr_AST = null;
		AST vname = null;
		AST vname_AST = null;
		AST rname = null;
		AST rname_AST = null;
		
			RTLExpression e1 = null, e2 = null, e3 = null;
			RTLExpression[] exprList = new RTLExpression[5]; // Needed for the BUILTIN-rule
			int i = 0; // counter 
			int n1 = -1, n2 = -1; 
			double f1 = Double.NaN;
			String str = null; 
		
		
		if (_t==null) _t=ASTNULL;
		switch ( _t.getType()) {
		case EQ:
		{
			AST __t318 = _t;
			AST tmp43_AST = null;
			AST tmp43_AST_in = null;
			tmp43_AST = astFactory.create((AST)_t);
			tmp43_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp43_AST);
			ASTPair __currentAST318 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,EQ);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST318;
			_t = __t318;
			_t = _t.getNextSibling();
			ret = factory.createEqual(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case NE:
		{
			AST __t319 = _t;
			AST tmp44_AST = null;
			AST tmp44_AST_in = null;
			tmp44_AST = astFactory.create((AST)_t);
			tmp44_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp44_AST);
			ASTPair __currentAST319 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,NE);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST319;
			_t = __t319;
			_t = _t.getNextSibling();
			ret = factory.createNotEqual(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case GT:
		{
			AST __t320 = _t;
			AST tmp45_AST = null;
			AST tmp45_AST_in = null;
			tmp45_AST = astFactory.create((AST)_t);
			tmp45_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp45_AST);
			ASTPair __currentAST320 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,GT);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST320;
			_t = __t320;
			_t = _t.getNextSibling();
			ret = factory.createGreaterThan(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LT:
		{
			AST __t321 = _t;
			AST tmp46_AST = null;
			AST tmp46_AST_in = null;
			tmp46_AST = astFactory.create((AST)_t);
			tmp46_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp46_AST);
			ASTPair __currentAST321 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LT);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST321;
			_t = __t321;
			_t = _t.getNextSibling();
			ret = factory.createLessThan(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case GE:
		{
			AST __t322 = _t;
			AST tmp47_AST = null;
			AST tmp47_AST_in = null;
			tmp47_AST = astFactory.create((AST)_t);
			tmp47_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp47_AST);
			ASTPair __currentAST322 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,GE);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST322;
			_t = __t322;
			_t = _t.getNextSibling();
			ret = factory.createGreaterOrEqual(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LE:
		{
			AST __t323 = _t;
			AST tmp48_AST = null;
			AST tmp48_AST_in = null;
			tmp48_AST = astFactory.create((AST)_t);
			tmp48_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp48_AST);
			ASTPair __currentAST323 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LE);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST323;
			_t = __t323;
			_t = _t.getNextSibling();
			ret = factory.createLessOrEqual(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case GTU:
		{
			AST __t324 = _t;
			AST tmp49_AST = null;
			AST tmp49_AST_in = null;
			tmp49_AST = astFactory.create((AST)_t);
			tmp49_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp49_AST);
			ASTPair __currentAST324 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,GTU);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST324;
			_t = __t324;
			_t = _t.getNextSibling();
			ret = factory.createUnsignedGreaterThan(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LTU:
		{
			AST __t325 = _t;
			AST tmp50_AST = null;
			AST tmp50_AST_in = null;
			tmp50_AST = astFactory.create((AST)_t);
			tmp50_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp50_AST);
			ASTPair __currentAST325 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LTU);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST325;
			_t = __t325;
			_t = _t.getNextSibling();
			ret = factory.createUnsignedLessThan(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case GEU:
		{
			AST __t326 = _t;
			AST tmp51_AST = null;
			AST tmp51_AST_in = null;
			tmp51_AST = astFactory.create((AST)_t);
			tmp51_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp51_AST);
			ASTPair __currentAST326 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,GEU);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST326;
			_t = __t326;
			_t = _t.getNextSibling();
			ret = factory.createUnsignedGreaterOrEqual(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LEU:
		{
			AST __t327 = _t;
			AST tmp52_AST = null;
			AST tmp52_AST_in = null;
			tmp52_AST = astFactory.create((AST)_t);
			tmp52_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp52_AST);
			ASTPair __currentAST327 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LEU);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST327;
			_t = __t327;
			_t = _t.getNextSibling();
			ret = factory.createUnsignedLessOrEqual(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case PLUS:
		{
			AST __t328 = _t;
			AST tmp53_AST = null;
			AST tmp53_AST_in = null;
			tmp53_AST = astFactory.create((AST)_t);
			tmp53_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp53_AST);
			ASTPair __currentAST328 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,PLUS);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST328;
			_t = __t328;
			_t = _t.getNextSibling();
			ret = factory.createPlus(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case PLUS_F:
		{
			AST __t329 = _t;
			AST tmp54_AST = null;
			AST tmp54_AST_in = null;
			tmp54_AST = astFactory.create((AST)_t);
			tmp54_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp54_AST);
			ASTPair __currentAST329 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,PLUS_F);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST329;
			_t = __t329;
			_t = _t.getNextSibling();
			ret = factory.createPlus(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case PLUS_FD:
		{
			AST __t330 = _t;
			AST tmp55_AST = null;
			AST tmp55_AST_in = null;
			tmp55_AST = astFactory.create((AST)_t);
			tmp55_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp55_AST);
			ASTPair __currentAST330 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,PLUS_FD);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST330;
			_t = __t330;
			_t = _t.getNextSibling();
			ret = factory.createPlus(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case PLUS_FQ:
		{
			AST __t331 = _t;
			AST tmp56_AST = null;
			AST tmp56_AST_in = null;
			tmp56_AST = astFactory.create((AST)_t);
			tmp56_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp56_AST);
			ASTPair __currentAST331 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,PLUS_FQ);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST331;
			_t = __t331;
			_t = _t.getNextSibling();
			ret = factory.createPlus(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case MINUS:
		{
			AST __t332 = _t;
			AST tmp57_AST = null;
			AST tmp57_AST_in = null;
			tmp57_AST = astFactory.create((AST)_t);
			tmp57_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp57_AST);
			ASTPair __currentAST332 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MINUS);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST332;
			_t = __t332;
			_t = _t.getNextSibling();
			ret = factory.createMinus(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case MINUS_F:
		{
			AST __t333 = _t;
			AST tmp58_AST = null;
			AST tmp58_AST_in = null;
			tmp58_AST = astFactory.create((AST)_t);
			tmp58_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp58_AST);
			ASTPair __currentAST333 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MINUS_F);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST333;
			_t = __t333;
			_t = _t.getNextSibling();
			ret = factory.createMinus(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case MINUS_FD:
		{
			AST __t334 = _t;
			AST tmp59_AST = null;
			AST tmp59_AST_in = null;
			tmp59_AST = astFactory.create((AST)_t);
			tmp59_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp59_AST);
			ASTPair __currentAST334 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MINUS_FD);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST334;
			_t = __t334;
			_t = _t.getNextSibling();
			ret = factory.createMinus(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case MINUS_FQ:
		{
			AST __t335 = _t;
			AST tmp60_AST = null;
			AST tmp60_AST_in = null;
			tmp60_AST = astFactory.create((AST)_t);
			tmp60_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp60_AST);
			ASTPair __currentAST335 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MINUS_FQ);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST335;
			_t = __t335;
			_t = _t.getNextSibling();
			ret = factory.createMinus(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case MUL:
		{
			AST __t336 = _t;
			AST tmp61_AST = null;
			AST tmp61_AST_in = null;
			tmp61_AST = astFactory.create((AST)_t);
			tmp61_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp61_AST);
			ASTPair __currentAST336 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MUL);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST336;
			_t = __t336;
			_t = _t.getNextSibling();
			ret = factory.createMultiply(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case MUL_F:
		{
			AST __t337 = _t;
			AST tmp62_AST = null;
			AST tmp62_AST_in = null;
			tmp62_AST = astFactory.create((AST)_t);
			tmp62_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp62_AST);
			ASTPair __currentAST337 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MUL_F);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST337;
			_t = __t337;
			_t = _t.getNextSibling();
			ret = factory.createFloatMultiply(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case MUL_FD:
		{
			AST __t338 = _t;
			AST tmp63_AST = null;
			AST tmp63_AST_in = null;
			tmp63_AST = astFactory.create((AST)_t);
			tmp63_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp63_AST);
			ASTPair __currentAST338 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MUL_FD);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST338;
			_t = __t338;
			_t = _t.getNextSibling();
			ret = factory.createFloatMultiply(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case MUL_FQ:
		{
			AST __t339 = _t;
			AST tmp64_AST = null;
			AST tmp64_AST_in = null;
			tmp64_AST = astFactory.create((AST)_t);
			tmp64_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp64_AST);
			ASTPair __currentAST339 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MUL_FQ);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST339;
			_t = __t339;
			_t = _t.getNextSibling();
			ret = factory.createFloatMultiply(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case MUL_FSD:
		{
			AST __t340 = _t;
			AST tmp65_AST = null;
			AST tmp65_AST_in = null;
			tmp65_AST = astFactory.create((AST)_t);
			tmp65_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp65_AST);
			ASTPair __currentAST340 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MUL_FSD);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST340;
			_t = __t340;
			_t = _t.getNextSibling();
			ret = factory.createFloatMultiply(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case MUL_FDQ:
		{
			AST __t341 = _t;
			AST tmp66_AST = null;
			AST tmp66_AST_in = null;
			tmp66_AST = astFactory.create((AST)_t);
			tmp66_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp66_AST);
			ASTPair __currentAST341 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MUL_FDQ);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST341;
			_t = __t341;
			_t = _t.getNextSibling();
			ret = factory.createFloatMultiply(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case SMUL:
		{
			AST __t342 = _t;
			AST tmp67_AST = null;
			AST tmp67_AST_in = null;
			tmp67_AST = astFactory.create((AST)_t);
			tmp67_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp67_AST);
			ASTPair __currentAST342 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,SMUL);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST342;
			_t = __t342;
			_t = _t.getNextSibling();
			ret = factory.createMultiply(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case DIV:
		{
			AST __t343 = _t;
			AST tmp68_AST = null;
			AST tmp68_AST_in = null;
			tmp68_AST = astFactory.create((AST)_t);
			tmp68_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp68_AST);
			ASTPair __currentAST343 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,DIV);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST343;
			_t = __t343;
			_t = _t.getNextSibling();
			ret = factory.createDivide(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case DIV_F:
		{
			AST __t344 = _t;
			AST tmp69_AST = null;
			AST tmp69_AST_in = null;
			tmp69_AST = astFactory.create((AST)_t);
			tmp69_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp69_AST);
			ASTPair __currentAST344 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,DIV_F);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST344;
			_t = __t344;
			_t = _t.getNextSibling();
			ret = factory.createFloatDivide(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case DIV_FD:
		{
			AST __t345 = _t;
			AST tmp70_AST = null;
			AST tmp70_AST_in = null;
			tmp70_AST = astFactory.create((AST)_t);
			tmp70_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp70_AST);
			ASTPair __currentAST345 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,DIV_FD);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST345;
			_t = __t345;
			_t = _t.getNextSibling();
			ret = factory.createFloatDivide(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case DIV_FQ:
		{
			AST __t346 = _t;
			AST tmp71_AST = null;
			AST tmp71_AST_in = null;
			tmp71_AST = astFactory.create((AST)_t);
			tmp71_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp71_AST);
			ASTPair __currentAST346 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,DIV_FQ);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST346;
			_t = __t346;
			_t = _t.getNextSibling();
			ret = factory.createFloatDivide(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case SDIV:
		{
			AST __t347 = _t;
			AST tmp72_AST = null;
			AST tmp72_AST_in = null;
			tmp72_AST = astFactory.create((AST)_t);
			tmp72_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp72_AST);
			ASTPair __currentAST347 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,SDIV);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST347;
			_t = __t347;
			_t = _t.getNextSibling();
			ret = factory.createDivide(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case MOD:
		{
			AST __t348 = _t;
			AST tmp73_AST = null;
			AST tmp73_AST_in = null;
			tmp73_AST = astFactory.create((AST)_t);
			tmp73_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp73_AST);
			ASTPair __currentAST348 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MOD);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST348;
			_t = __t348;
			_t = _t.getNextSibling();
			ret = factory.createModulo(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case SMOD:
		{
			AST __t349 = _t;
			AST tmp74_AST = null;
			AST tmp74_AST_in = null;
			tmp74_AST = astFactory.create((AST)_t);
			tmp74_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp74_AST);
			ASTPair __currentAST349 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,SMOD);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST349;
			_t = __t349;
			_t = _t.getNextSibling();
			ret = factory.createModulo(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LITERAL_pow:
		{
			AST __t350 = _t;
			AST tmp75_AST = null;
			AST tmp75_AST_in = null;
			tmp75_AST = astFactory.create((AST)_t);
			tmp75_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp75_AST);
			ASTPair __currentAST350 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LITERAL_pow);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST350;
			_t = __t350;
			_t = _t.getNextSibling();
			ret = factory.createPowerOf(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case AND:
		{
			AST __t351 = _t;
			AST tmp76_AST = null;
			AST tmp76_AST_in = null;
			tmp76_AST = astFactory.create((AST)_t);
			tmp76_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp76_AST);
			ASTPair __currentAST351 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,AND);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST351;
			_t = __t351;
			_t = _t.getNextSibling();
			ret = factory.createAnd(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LAND:
		{
			AST __t352 = _t;
			AST tmp77_AST = null;
			AST tmp77_AST_in = null;
			tmp77_AST = astFactory.create((AST)_t);
			tmp77_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp77_AST);
			ASTPair __currentAST352 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LAND);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST352;
			_t = __t352;
			_t = _t.getNextSibling();
			ret = factory.createAnd(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case OR:
		{
			AST __t353 = _t;
			AST tmp78_AST = null;
			AST tmp78_AST_in = null;
			tmp78_AST = astFactory.create((AST)_t);
			tmp78_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp78_AST);
			ASTPair __currentAST353 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,OR);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST353;
			_t = __t353;
			_t = _t.getNextSibling();
			ret = factory.createOr(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LOR:
		{
			AST __t354 = _t;
			AST tmp79_AST = null;
			AST tmp79_AST_in = null;
			tmp79_AST = astFactory.create((AST)_t);
			tmp79_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp79_AST);
			ASTPair __currentAST354 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LOR);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST354;
			_t = __t354;
			_t = _t.getNextSibling();
			ret = factory.createOr(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case XOR:
		{
			AST __t355 = _t;
			AST tmp80_AST = null;
			AST tmp80_AST_in = null;
			tmp80_AST = astFactory.create((AST)_t);
			tmp80_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp80_AST);
			ASTPair __currentAST355 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,XOR);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST355;
			_t = __t355;
			_t = _t.getNextSibling();
			ret = factory.createXor(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case ANDNOT:
		{
			AST __t356 = _t;
			AST tmp81_AST = null;
			AST tmp81_AST_in = null;
			tmp81_AST = astFactory.create((AST)_t);
			tmp81_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp81_AST);
			ASTPair __currentAST356 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,ANDNOT);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST356;
			_t = __t356;
			_t = _t.getNextSibling();
			ret = factory.createAnd(e1, factory.createNot(e2));
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case ORNOT:
		{
			AST __t357 = _t;
			AST tmp82_AST = null;
			AST tmp82_AST_in = null;
			tmp82_AST = astFactory.create((AST)_t);
			tmp82_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp82_AST);
			ASTPair __currentAST357 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,ORNOT);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST357;
			_t = __t357;
			_t = _t.getNextSibling();
			ret = factory.createOr(e1, factory.createNot(e2));
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case XORNOT:
		{
			AST __t358 = _t;
			AST tmp83_AST = null;
			AST tmp83_AST_in = null;
			tmp83_AST = astFactory.create((AST)_t);
			tmp83_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp83_AST);
			ASTPair __currentAST358 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,XORNOT);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST358;
			_t = __t358;
			_t = _t.getNextSibling();
			ret = factory.createXor(e1, factory.createNot(e2));
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case NOT:
		{
			AST __t359 = _t;
			AST tmp84_AST = null;
			AST tmp84_AST_in = null;
			tmp84_AST = astFactory.create((AST)_t);
			tmp84_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp84_AST);
			ASTPair __currentAST359 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,NOT);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST359;
			_t = __t359;
			_t = _t.getNextSibling();
			ret = factory.createNot(e1);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LNOT:
		{
			AST __t360 = _t;
			AST tmp85_AST = null;
			AST tmp85_AST_in = null;
			tmp85_AST = astFactory.create((AST)_t);
			tmp85_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp85_AST);
			ASTPair __currentAST360 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LNOT);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST360;
			_t = __t360;
			_t = _t.getNextSibling();
			ret = factory.createNot(e1);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case FNEG:
		{
			AST __t361 = _t;
			AST tmp86_AST = null;
			AST tmp86_AST_in = null;
			tmp86_AST = astFactory.create((AST)_t);
			tmp86_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp86_AST);
			ASTPair __currentAST361 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,FNEG);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST361;
			_t = __t361;
			_t = _t.getNextSibling();
			ret = factory.createNeg(e1);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LITERAL_rlc:
		{
			AST __t362 = _t;
			AST tmp87_AST = null;
			AST tmp87_AST_in = null;
			tmp87_AST = astFactory.create((AST)_t);
			tmp87_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp87_AST);
			ASTPair __currentAST362 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LITERAL_rlc);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST362;
			_t = __t362;
			_t = _t.getNextSibling();
			ret = factory.createRotateLeftWithCarry(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LITERAL_rrc:
		{
			AST __t363 = _t;
			AST tmp88_AST = null;
			AST tmp88_AST_in = null;
			tmp88_AST = astFactory.create((AST)_t);
			tmp88_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp88_AST);
			ASTPair __currentAST363 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LITERAL_rrc);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST363;
			_t = __t363;
			_t = _t.getNextSibling();
			ret = factory.createRotateRightWithCarry(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LITERAL_rl:
		{
			AST __t364 = _t;
			AST tmp89_AST = null;
			AST tmp89_AST_in = null;
			tmp89_AST = astFactory.create((AST)_t);
			tmp89_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp89_AST);
			ASTPair __currentAST364 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LITERAL_rl);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST364;
			_t = __t364;
			_t = _t.getNextSibling();
			ret = factory.createRotateLeft(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LITERAL_rr:
		{
			AST __t365 = _t;
			AST tmp90_AST = null;
			AST tmp90_AST_in = null;
			tmp90_AST = astFactory.create((AST)_t);
			tmp90_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp90_AST);
			ASTPair __currentAST365 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LITERAL_rr);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST365;
			_t = __t365;
			_t = _t.getNextSibling();
			ret = factory.createRotateRight(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case RSHIFT:
		{
			AST __t366 = _t;
			AST tmp91_AST = null;
			AST tmp91_AST_in = null;
			tmp91_AST = astFactory.create((AST)_t);
			tmp91_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp91_AST);
			ASTPair __currentAST366 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,RSHIFT);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST366;
			_t = __t366;
			_t = _t.getNextSibling();
			ret = factory.createShiftRight(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case LSHIFT:
		{
			AST __t367 = _t;
			AST tmp92_AST = null;
			AST tmp92_AST_in = null;
			tmp92_AST = astFactory.create((AST)_t);
			tmp92_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp92_AST);
			ASTPair __currentAST367 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LSHIFT);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST367;
			_t = __t367;
			_t = _t.getNextSibling();
			ret = factory.createShiftLeft(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case RSHIFTA:
		{
			AST __t368 = _t;
			AST tmp93_AST = null;
			AST tmp93_AST_in = null;
			tmp93_AST = astFactory.create((AST)_t);
			tmp93_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp93_AST);
			ASTPair __currentAST368 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,RSHIFTA);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST368;
			_t = __t368;
			_t = _t.getNextSibling();
			ret = factory.createShiftArithmeticRight(e1, e2);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case NAME:
		{
			vname = (AST)_t;
			AST vname_AST_in = null;
			vname_AST = astFactory.create(vname);
			astFactory.addASTChild(currentAST, vname_AST);
			match(_t,NAME);
			_t = _t.getNextSibling();
			ret = factory.createRegisterVariable(vname.getText(), (bw>0 ? bw : RTLVariable.UNKNOWN_BITWIDTH));
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case REG_ID:
		{
			rname = (AST)_t;
			AST rname_AST_in = null;
			rname_AST = astFactory.create(rname);
			astFactory.addASTChild(currentAST, rname_AST);
			match(_t,REG_ID);
			_t = _t.getNextSibling();
			ret = factory.createRegisterVariable(rname.getText(), (bw>0 ? bw : RTLVariable.UNKNOWN_BITWIDTH));
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case NUM:
		{
			n1=intValue(_t);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			ret = factory.createNumber(n1, RTLVariable.UNKNOWN_BITWIDTH);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case FLOATNUM:
		{
			f1=floatValue(_t);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			ret = factory.createNumber((long)f1, 80);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case MEM_IDX:
		{
			AST __t369 = _t;
			AST tmp94_AST = null;
			AST tmp94_AST_in = null;
			tmp94_AST = astFactory.create((AST)_t);
			tmp94_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp94_AST);
			ASTPair __currentAST369 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,MEM_IDX);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,-Math.abs(bw));
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST369;
			_t = __t369;
			_t = _t.getNextSibling();
			ret = factory.createMemoryLocation(e1, (bw!=0 ? Math.abs(bw) : RTLVariable.UNKNOWN_BITWIDTH));
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case CAST:
		{
			AST __t370 = _t;
			AST tmp95_AST = null;
			AST tmp95_AST_in = null;
			tmp95_AST = astFactory.create((AST)_t);
			tmp95_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp95_AST);
			ASTPair __currentAST370 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,CAST);
			_t = _t.getFirstChild();
			n1=intValue(_t);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e1=rtlExpr(_t,n1);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST370;
			_t = __t370;
			_t = _t.getNextSibling();
			
						//ret = factory.createCast(e1, factory.createNumber(n1, RTLVariable.UNKNOWN_BITWIDTH));
						ret = e1;
						
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case AT:
		{
			AST __t371 = _t;
			AST tmp96_AST = null;
			AST tmp96_AST_in = null;
			tmp96_AST = astFactory.create((AST)_t);
			tmp96_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp96_AST);
			ASTPair __currentAST371 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,AT);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,0);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,0);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e3=rtlExpr(_t,0);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST371;
			_t = __t371;
			_t = _t.getNextSibling();
			ret = factory.createBitRange(e1, e2, e3);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case QUEST:
		{
			AST __t372 = _t;
			AST tmp97_AST = null;
			AST tmp97_AST_in = null;
			tmp97_AST = astFactory.create((AST)_t);
			tmp97_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp97_AST);
			ASTPair __currentAST372 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,QUEST);
			_t = _t.getFirstChild();
			e1=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e2=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			e3=rtlExpr(_t,bw);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			currentAST = __currentAST372;
			_t = __t372;
			_t = _t.getNextSibling();
			ret = factory.createConditionalExpression(e1, e2, e3);
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		case BUILTIN:
		{
			AST __t373 = _t;
			AST tmp98_AST = null;
			AST tmp98_AST_in = null;
			tmp98_AST = astFactory.create((AST)_t);
			tmp98_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp98_AST);
			ASTPair __currentAST373 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,BUILTIN);
			_t = _t.getFirstChild();
			str=nameValue(_t);
			_t = _retTree;
			astFactory.addASTChild(currentAST, returnAST);
			{
			_loop375:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_tokenSet_2.member(_t.getType()))) {
					e1=rtlExpr(_t,bw);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
					exprList[i++] = e1;
				}
				else {
					break _loop375;
				}
				
			} while (true);
			}
			currentAST = __currentAST373;
			_t = __t373;
			_t = _t.getNextSibling();
			
						  	if (str.equals("sgnex")) ret = factory.createSignExtend(exprList[0], exprList[1], exprList[2]);
						  	else if (str.equals("zfill")) ret = factory.createZeroFill(exprList[0], exprList[1], exprList[2]);
						  	else if (str.equals("fsize")) ret = factory.createFloatResize(exprList[0], exprList[1], exprList[2]);
						  	// temporary solution until real float support
						  	else if (str.equals("ftoi")) ret = factory.createFloatResize(exprList[0], exprList[1], exprList[2]);
						  	else if (str.equals("itof")) ret = factory.createFloatResize(exprList[0], exprList[1], exprList[2]);
							else ret = factory.createSpecialExpression(str, exprList); 
						
			rtlExpr_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(_t);
		}
		}
		returnAST = rtlExpr_AST;
		_retTree = _t;
		return ret;
	}
	
	public final double  floatValue(AST _t) throws RecognitionException {
		 double value = -1; ;
		
		AST floatValue_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST floatValue_AST = null;
		AST number = null;
		AST number_AST = null;
		
		number = (AST)_t;
		AST number_AST_in = null;
		number_AST = astFactory.create(number);
		astFactory.addASTChild(currentAST, number_AST);
		match(_t,FLOATNUM);
		_t = _t.getNextSibling();
		value = Double.parseDouble(number.getText());
		floatValue_AST = (AST)currentAST.root;
		returnAST = floatValue_AST;
		_retTree = _t;
		return value;
	}
	
	public final String  nameValue(AST _t) throws RecognitionException {
		 String value = null; ;
		
		AST nameValue_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST nameValue_AST = null;
		AST str = null;
		AST str_AST = null;
		
		str = (AST)_t;
		AST str_AST_in = null;
		str_AST = astFactory.create(str);
		astFactory.addASTChild(currentAST, str_AST);
		match(_t,NAME);
		_t = _t.getNextSibling();
		value = str.getText();
		nameValue_AST = (AST)currentAST.root;
		returnAST = nameValue_AST;
		_retTree = _t;
		return value;
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"SEMI",
		"NUM",
		"NAME",
		"EQUATE",
		"PLUS",
		"MINUS",
		"\"INTEGER\"",
		"\"FLOAT\"",
		"COMMA",
		"REG_ID",
		"INDEX",
		"LSQUARE",
		"RSQUARE",
		"\"COVERS\"",
		"TO",
		"\"SHARES\"",
		"AT",
		"\"OPERAND\"",
		"LCURLY",
		"RCURLY",
		"ASSIGNTYPE",
		"\"ENDIANNESS\"",
		"\"BIG\"",
		"\"LITTLE\"",
		"LPAREN",
		"RPAREN",
		"QUOTE",
		"DECOR",
		"MOD",
		"MUL",
		"DIV",
		"SMUL",
		"SDIV",
		"SMOD",
		"\"rlc\"",
		"\"rrc\"",
		"\"rl\"",
		"\"rr\"",
		"RSHIFT",
		"LSHIFT",
		"RSHIFTA",
		"OR",
		"ORNOT",
		"AND",
		"ANDNOT",
		"XOR",
		"XORNOT",
		"MUL_F",
		"MUL_FD",
		"MUL_FQ",
		"MUL_FSD",
		"MUL_FDQ",
		"DIV_F",
		"DIV_FD",
		"DIV_FQ",
		"PLUS_F",
		"PLUS_FD",
		"PLUS_FQ",
		"MINUS_F",
		"MINUS_FD",
		"MINUS_FQ",
		"\"pow\"",
		"EQ",
		"NE",
		"LT",
		"GT",
		"LE",
		"GE",
		"LTU",
		"GTU",
		"LEU",
		"GEU",
		"PRIME",
		"DOLLAR",
		"\"halt\"",
		"UNDERSCORE",
		"\"MEMSET\"",
		"\"MEMCPY\"",
		"\"r\"",
		"\"m\"",
		"COLON",
		"FLOATNUM",
		"QUEST",
		"S_E",
		"NOT",
		"FNEG",
		"LNOT",
		"\"and\"",
		"\"or\"",
		"\"FAST\"",
		"CONSTANT",
		"TABLE",
		"CROSSP",
		"FUNCTION",
		"INSTR",
		"INSTR_NAME",
		"LOOKUP_OP",
		"RTL",
		"BUILTIN",
		"CAST",
		"REGDECL",
		"WS",
		"COMMENT",
		"DIGITS",
		"HEXDIGITS",
		"FLOAT_OR_NUM",
		"ASSIGN",
		"THEN",
		"ASSIGNTYPE_OR_MUL",
		"DOT"
	};
	
	private static final long[] mk_tokenSet_0() {
		long[] data = { 0L, 1128502657024L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_0 = new BitSet(mk_tokenSet_0());
	private static final long[] mk_tokenSet_1() {
		long[] data = { 1077936192L, 4294967296L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_1 = new BitSet(mk_tokenSet_1());
	private static final long[] mk_tokenSet_2() {
		long[] data = { -4293909664L, 825160634367L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_2 = new BitSet(mk_tokenSet_2());
	}
	
