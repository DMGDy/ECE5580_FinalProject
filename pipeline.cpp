#include "pipeline.hpp"
#include <vector>

/* ==========================================================================
 *
 *  Function declerations
 *
 * ==========================================================================
 */

reg reg_conv(const std::string);
vector_instruction inst_conv(const std::string);

/* ==========================================================================
 *
 *  Function implementations
 *
 * ==========================================================================
 */

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

/*
 * mapped values to convert expected instruction string
 */

std::unordered_map<std::string, vector_instruction> str_inst_map = {
  {"NONE", vector_instruction::NONE},
  {"VADDPS", vector_instruction::VADDPS},
  {"VSHUFPS", vector_instruction::VSHUFPS},
  {"VRSQRTSS", vector_instruction::VRSQRTSS},
  {"VSQRTSS", vector_instruction::VSQRTSS},
  {"VCOMISD", vector_instruction::VCOMISD},
  {"VMULSS", vector_instruction::VMULSS},
  {"VSUBPS", vector_instruction::VSUBPS},
  {"VADDSS", vector_instruction::VADDSS},
  {"VZEROUPPER", vector_instruction::VZEROUPPER},
  {"VMULPS", vector_instruction::VMULPS},
  {"VPMOVMSKB", vector_instruction::VPMOVMSKB},
  {"VPCMPEQB", vector_instruction::VPCMPEQB},
  {"VINSERTF128", vector_instruction::VINSERTF128},
  {"VEXTRACTF128", vector_instruction::VEXTRACTF128}
};

vector_instruction
inst_conv(const std::string inst)
{
  auto it = str_inst_map.find(inst);
  if(it != str_inst_map.end())
    return it->second;
  else
    return vector_instruction::NONE;
}

/* ==========================================================================
 *
 *  # Class Method Implementations
 *
 * ==========================================================================
 */

/* ==========================================================================
 *
 *  ## instruction_t class implementations
 *
 * ==========================================================================
 */


std::shared_ptr<fetched_instruction>
fetched_instruction::create(const std::string instruction)
{
  return std::make_shared<fetched_instruction>(instruction);
}

decoded_instruction::decoded_instruction(const std::string op,
                                         const std::string destination,
                                         const std::string source1,
                                         const std::string source2,
                                         uint32_t address)
{
  this->address = address;
  this->opcode = inst_conv(op);
  this->destination = reg_conv(destination);
  this->source1 = reg_conv(source1);
  this->source2 = reg_conv(source2);
}



std::shared_ptr<decoded_instruction>
decoded_instruction::create(const std::string op,
                            const std::string destination,
                            const std::string source1, 
                            const std::string source2,
                            uint32_t address)
{
  return std::make_shared<decoded_instruction>(op,destination,source1,source2,
                                               address);
}

vector_instruction
decoded_instruction::get_opcode(void)
{
  return this->opcode;
}

reg
decoded_instruction::get_destination_register(void)
{
  return this->destination;
}


/* ==========================================================================
 *
 *  Reorder Buffer method implementations
 *
 *==========================================================================
 */

reorder_buffer::reorder_buffer(ssize_t size):size(size)
{
  this->buffer.reserve(size);
}

std::unique_ptr<reorder_buffer>
reorder_buffer::create(ssize_t size)
{
  return reorder_buffer::create(size);
}

int
reorder_buffer::add_instruction(std::shared_ptr<instruction_t> instruction)
{
  if(this->buffer.size() > this->size)
    this->buffer.push_back(std::make_pair(instruction,false));
  else
    return -1;
  return 0;
}

/*
 * finds first instance of the instruction in the reorder
 * buffer and marks that instruction as complete
 */
void
reorder_buffer::complete_instruction(std::shared_ptr<instruction_t> inst)
{
  for(auto& it: this->buffer)
    if(it.first == inst)
    {
      it.second = true;
      return;
    }
}

/*
 * removes instructions that are ready to be comitted
 *
 */
void 
reorder_buffer::commit_instructions(void)
{
  for(auto it = this->buffer.begin();it != this->buffer.end();)
  {
    if(it->second == true)
      it = this->buffer.erase(it);
  }
};
  
/*
 * checks if ROB is full
 */
int
reorder_buffer::is_full(void)
{
  if(this->buffer.size() >= this->size)
    return 0;
  else
    return 1;
}

/* ==========================================================================
 *
 *  Reservation station
 *
 *==========================================================================
 */

