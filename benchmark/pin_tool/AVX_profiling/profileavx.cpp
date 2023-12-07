#include <pin.H>
#include <iostream>
#include <fstream>

std::ofstream simdTraceFile;

/* Function to safely get register name */
std::string
GetRegName(REG reg)
{
  if (reg != REG_INVALID())
    {
      return REG_StringShort(reg);
    }
  return "\0";
}

/* Function to log SIMD instructions */
VOID
LogSIMDInstruction(const std::string &instruction, const std::string &dst, 
                   const std::string &src1, const std::string &src2,
                   const std::string category, const std::string address)
{
  simdTraceFile << " "<< instruction << " " << dst << " " << src1;
  if (!src2.empty())
    {
      simdTraceFile << " " << src2;
    }
  simdTraceFile << std::endl;
}

/* Instrumentation routine */
VOID
Instruction(INS ins, VOID *v)
{
    unsigned category = INS_Category(ins);
  if (category == XED_CATEGORY_AVX || category == XED_CATEGORY_AVX2 || category == XED_CATEGORY_AVX512)
//    if(1)
    {
      std::string instruction = INS_Mnemonic(ins);
      std::string dstReg = GetRegName(INS_RegW(ins, 0));
      std::string srcReg1 = INS_OperandCount(ins) > 0 ? GetRegName(INS_RegR(ins, 0)) : "";
      std::string srcReg2 = INS_OperandCount(ins) > 1 ? GetRegName(INS_RegR(ins, 1)) : "";
      std::string cat = CATEGORY_StringShort(INS_Category(ins));
      std::string address = StringFromAddrint(INS_Address(ins));

      INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)LogSIMDInstruction,
                     IARG_PTR, new std::string(instruction),
                     IARG_PTR, new std::string(dstReg),
                     IARG_PTR, new std::string(srcReg1),
                     IARG_PTR, new std::string(srcReg2),
                     IARG_PTR, new std::string(cat),
                     IARG_PTR, new std::string(address),
                     IARG_END);
    }
}

/* This function is called when the application exits */
VOID
Finishing(INT32 code, VOID *v)
{
  simdTraceFile.close();
}

/* Initialize Pin */
int
main(int argc, char *argv[])
{
  if (PIN_Init(argc, argv))
    {
      std::cerr << "This Pintool logs SIMD (AVX and AVX2) instructions" << std::endl;
      std::cerr << "Usage: " << argv[0] << " [options] -- <application to run>" << std::endl;
      return 1;
    }

  simdTraceFile.open("SIMD.trace");

  INS_AddInstrumentFunction(Instruction, 0);
  PIN_AddFiniFunction(Finishing, 0);

  // Start the program, never returns
  PIN_StartProgram();

  return 0;
}

