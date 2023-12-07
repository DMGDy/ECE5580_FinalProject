#include "pin.H"
#include <iostream>
#include <fstream>
#include <stdio.h>

FILE* trace;


BOOL INS_IsVector(INS ins);

BOOL
INS_IsVector(INS ins)
{
    INT32 category = INS_Category(ins);
    if(category == XED_CATEGORY_AVX2 || category == XED_CATEGORY_AVX512 ||
            category == XED_CATEGORY_AVX || category ==  XED_CATEGORY_AVX512_4FMAPS ||
            category == XED_CATEGORY_AVX512_4VNNIW || category == XED_CATEGORY_AVX512_BITALG
            || category == XED_CATEGORY_AVX512_VBMI || category == XED_CATEGORY_AVX512_VP2INTERSECT)
        return TRUE;
    return FALSE;
}
VOID Instruction(INS ins, VOID *v) {
    if (1) {
        // For each instruction, log the details
        std::string instruction;
      //  instruction = "VECTOR ";
        instruction += INS_Mnemonic(ins);
        // Include destination and source registers

        instruction += " DEST " + std::string(REG_StringShort(INS_RegW(ins, 0))) + " ";
 //       if (INS_OperandCount(ins) > 1) {
            for (UINT32 i = 0; i < INS_OperandCount(ins); ++i) {
   //             if (INS_OperandRead(ins, i)) {
                    instruction += "SRC " + std::string(REG_StringShort(INS_RegR(ins, i))) + " ";
                //}
            }
        //}
        fprintf(trace,"%s\n",instruction.c_str());
        fprintf(stdout,"%s\n",instruction.c_str());
    }
}

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v) {
    fprintf(trace,"#eof\n");
    fclose(trace);
}

// Initialize the pin tool
int main(int argc, char *argv[]) {
    // Initialize pin
    if (PIN_Init(argc, argv)) {
        std::cerr << "This Pintool prints a trace of memory addresses." << std::endl;
        return 1;
    }
    
    trace = fopen("trace.out","w");

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);

    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}

