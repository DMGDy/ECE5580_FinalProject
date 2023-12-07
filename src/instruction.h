#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "register.h"
#include <memory>
#include <string>


enum class vector_instruction: int 
{
  NONE = -1,
  VADDPS,
  VSHUFPS,
  VRSQRTSS,
  VSQRTSS,
  VCOMISD,
  VMULSS,
  VSUBPS,
  VADDSS,
  VZEROUPPER,
  VMULPS,
  VPMOVMSKB,
  VPCMPEQB,
  VINSERTF128,
  VEXTRACTF128
};

 

class instruction_t
{
public:
  virtual ~instruction_t(){};
  virtual int decoded(void) const = 0;
};

class fetched_instruction: public instruction_t 
{

public:
  static std::shared_ptr<fetched_instruction>create(const std::string instruction);
  std::string instruction_str(void);
  int decoded(void)const override;

private:
  fetched_instruction(const std::string instruction):
    instruction(instruction){};
  std::string instruction;

};

class decoded_instruction: public instruction_t
{
public:
  static std::shared_ptr<decoded_instruction> create(const std::string op, 
                                                    const std::string destination, 
                                                    const std::string source1,   
                                                    const std::string source2);
  int decoded(void)const override;
  static std::shared_ptr<instruction_t> instruction;
  vector_instruction get_opcode();
  reg get_destination_register();
  std::pair<reg,reg> get_sources();

private:
  decoded_instruction(const std::string op,
                      const std::string destination,
                      const std::string source1,
                      const std::string source2);

  vector_instruction opcode;
  reg destination;
  reg source1;
  reg source2;
  uint32_t address;
};

#endif
