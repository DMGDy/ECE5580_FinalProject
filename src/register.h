#ifndef REGISTER_H
#define REGISTER_H

#include <string>
enum class reg;

reg reg_conv(const std::string);
void init_reg_state(void);

enum class reg: int
{
  null = 0,
  /* 64-bit registers */
  RAX,RBX,RCX,RDX,RSI,RDI,RBP,RSP,RIP,RFLAGS,
  /* 32-bit registers */
  EAX,EBX,ECX,EDX,ESI,EDI,EBP,ESP,EIP,EFLAGS,
  /* 16-bit registers */
  AX,BX,CX,DX,SI,DI,BP,SP,IP,FLAGS,

  /* Vector Registers */
  YMM0,YMM1,YMM2,YMM3,YMM4,YMM5,YMM6,YMM7,
  YMM8,YMM9,YMM10,YMM11,YMM12,YMM13,YMM14,YMM15,
  XMM0,XMM1,XMM2,XMM3,XMM4,XMM5,XMM6,XMM7,
  XMM8,XMM9,XMM10,XMM11,XMM12,XMM13,XMM14,XMM15,
};

#endif
