#include "register.h"
#include <unordered_map>
#include <map>
#include <string>


/*
 * mapped values to convert expected register string
 * from trace file into associated enum value of reg enum
 */
std::unordered_map<std::string, reg> str_reg_map = 
{
  {"null", reg::null},
  {"rax", reg::RAX},{"rbx", reg::RBX},{"rcx", reg::RCX}, 
  {"rdx", reg::RDX},{"rsi", reg::RSI},{"rdi", reg::RDI}, 
  {"rbp", reg::RBP}, {"rsp", reg::RSP},{"rip", reg::RIP},
  {"rflags", reg::RFLAGS},
  {"eax", reg::EAX},{"ebx", reg::EBX},{"ecx", reg::ECX}, 
  {"edx", reg::EDX},{"esi", reg::ESI}, {"edi", reg::EDI},
  {"ebp", reg::EBP},{"esp", reg::ESP},{"eip", reg::EIP}, 
  {"eflags", reg::EFLAGS},
  {"ax", reg::AX},{"bx", reg::BX},{"cx", reg::CX},
  {"dx", reg::DX},{"si", reg::SI},{"di", reg::DI},
  {"bp", reg::BP},{"sp", reg::SP},{"ip", reg::IP},
  {"flags", reg::FLAGS},
  {"ymm0", reg::YMM0},{"ymm1", reg::YMM1},{"ymm2", reg::YMM2},
  {"ymm3", reg::YMM3},{"ymm4", reg::YMM4},{"ymm5", reg::YMM5},
  {"ymm6", reg::YMM6},{"ymm7", reg::YMM7},{"ymm8", reg::YMM8},
  {"ymm9", reg::YMM9},{"ymm10", reg::YMM10},{"ymm11", reg::YMM11},
  {"ymm12", reg::YMM12},{"ymm13", reg::YMM13},{"ymm14", reg::YMM14},
  {"ymm15", reg::YMM15},
  {"xmm0", reg::XMM0},{"xmm1", reg::XMM1},{"xmm2", reg::XMM2},
  {"xmm3", reg::XMM3},{"xmm4", reg::XMM4},{"xmm5", reg::XMM5},
  {"xmm6", reg::XMM6},{"xmm7", reg::XMM7},{"xmm8", reg::XMM8},
  {"xmm9", reg::XMM9},{"xmm10", reg::XMM10},{"xmm11", reg::XMM11},
  {"xmm12", reg::XMM12},{"xmm13", reg::XMM13},{"xmm14", reg::XMM14},
  {"xmm15", reg::XMM15}
};


reg
reg_conv(const std::string reg_str)
{
  auto it = str_reg_map.find(reg_str);
  if(it != str_reg_map.end())
    return it->second;
  else
    return reg::null;
}
