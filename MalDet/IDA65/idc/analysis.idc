//
//      Sample IDC program to automate IDA.
//
//      IDA can be run from the command line in the
//      batch (non-interactive) mode.
//
//      If IDA is started with
//
//              idag -A -Sanalysis.idc file
//
//      then this IDC file will be executed. It performs the following:
//
//        - the code segment is analyzed
//        - the output file is created
//        - IDA exits to OS
//
//      Feel free to modify this file as you wish
//      (or write your own script/plugin to automate IDA)
//
//      Since the script calls the Exit() function at the end,
//      it can be used in the batch files (use text mode idaw.exe)
//
//      NB: "idag -B file" is equivalent to the command line above
//

#include <idc.idc>

static main()
{
  // turn on coagulation of data in the final pass of analysis
  SetShortPrm(INF_AF2, GetShortPrm(INF_AF2) | AF2_DODATA);

  Message("Waiting for the end of the auto analysis...\n");
  Wait();
  Message("\n\n------ Creating the output file.... --------\n");
  auto file = GetIdbPath()[0:-4] + ".asm";
  WriteTxt(file, 0, BADADDR);           // create the assembler file
  
  
  //
  auto file1, file2;
  auto addr, count;
  auto segtype;
  auto endaddr;
  auto filepath;
  auto cFile1, cFile2;
  auto check1;
 auto check;
  check =0;
  check1 =0;
   count=0;
  
  addr=FirstSeg();
  filepath = GetInputFilePath();
  Message(filepath+"\n");
  
  
  cFile1=0;
  cFile2=0;
  
  while(addr!=BADADDR && (check==0 ||check1==0 ))
  {  
    segtype=GetSegmentAttr(addr,SEGATTR_TYPE);
	
		if(segtype==SEG_CODE && check==0 )
  	{
			if(cFile1==0){			
			//file1="import_code"+".lst";
			//file1=filepath+"_code"+".lst";
			//CreateLST(file1, SegStart(addr), SegEnd(addr)); 
			cFile1=1;
			 }else{
			//WriteLST(file1, SegStart(addr), SegEnd(addr)); 
			}
   		//break;
		
		if(check==0)
		{
		/*Message("generate GDL...\n");
		//GenFuncGdl(filepath+"_GDL.out","Graph", SegStart(addr), SegEnd(addr),CHART_GEN_GDL);*/
		//GenCallGdl("outpuFuncGDL", ""Call Graph",CHART_WINGRAPH);
		 auto ofp = fopen(filepath+"_statements.out", "w");
		Message("generate statements...\n");
		auto nEntry = GetEntryPointQty();
		fprintf(ofp,"%ld\n",nEntry);
		while(nEntry>0){
		fprintf(ofp,"%ld\n",GetEntryPoint(GetEntryOrdinal(nEntry-1)));
		nEntry=nEntry-1;
		}
		auto ea = SegStart(addr);
		
		fprintf(ofp, "addr|\tInst\tOpnd0\tType\tValue\tOpnd1\tType\tValue\tcomment\n");
		
		while(ea!= SegEnd(addr) &&  ea!=-1){
		if(GetMnem(ea)!="")
			fprintf(ofp, "%ld\t%s\t%s\t%ld\t%ld\t%s\t%ld\t%ld\t%s\n", ea,GetMnem(ea),GetOpnd(ea,0),GetOpType(ea,0),GetOperandValue(ea,0),GetOpnd(ea,1),GetOpType(ea,1),GetOperandValue(ea,1),CommentEx (ea,0));
		//else
			//fprintf(ofp, "%s\n",GetDisasm(ea));
		ea = NextAddr(ea);
		}
		fclose(ofp);
		
		ofp = fopen(filepath+"_Func.out", "w");
		Message("generate Func...\n");
		ea = SegStart(addr);
		ea = NextFunction(ea);		
		while(ea!=-1){
			fprintf(ofp, "%ld\t%s\t%ld\t%ld\t%ld\t%ld\t%d\n",ea, GetFunctionName(ea),GetFrameArgsSize(ea)/4,GetFrameLvarSize(ea)/4,GetFrameRegsSize(ea)/4,FindFuncEnd(ea),GetFunctionFlags(ea) );
		ea = NextFunction(ea);
		}
		fclose(ofp);
		check=1;
		}
   	} 
		if(segtype==SEG_XTRN && check1==0)
  	{
			if(cFile2==0){
 			//file2="import_API"+".lst";
			//file2=filepath+"_API"+".lst";
			//CreateLST(file2, SegStart(addr), SegEnd(addr)); 
			cFile2=1;
			}else{
 			//WriteLST(file2, SegStart(addr), SegEnd(addr)); 		
			}

   		//break;
		if(check1==0)
		{
		ofp = fopen(filepath+"_API.out", "w");
		Message("generate API...\n");
		ea = SegStart(addr);
		while(ea!=SegEnd(addr) && ea!=-1){
		if(GetTrueNameEx(ea,ea)!=""){
			fprintf(ofp, "%ld\t%s\t%s\n",ea,GetTrueNameEx(ea,ea),GetString(ea,-1,GetStringType(ea)));
			//fprintf(ofp, "%s\n",GetDisasm(ea));
			}
		ea = NextAddr(ea);
		}
		fclose(ofp);
		check1=1;
		}
   	}    	
		
		
		addr=NextSeg(addr);  	 
	 }
  //
  
  
 
  
  
  Message("All done, exiting...\n");
  Exit(0);                              // exit to OS, error code 0 - success
}
