#include "instruction.h"
#include <algorithm>
#include <unordered_map>
#include <map>
#include <vector>


vector_instruction inst_conv(const std::string);

std::map<vector_instruction, int> instruction_latencies = {
    {vector_instruction::VADDPS, 2},
    {vector_instruction::VSHUFPS, 1},
    {vector_instruction::VRSQRTSS, 5},
    {vector_instruction::VSQRTSS, 18},
    {vector_instruction::VCOMISD, 3},
    {vector_instruction::VMULSS, 8},
    {vector_instruction::VSUBPS, 2},
    {vector_instruction::VADDSS, 2},
    {vector_instruction::VZEROUPPER, 1},
    {vector_instruction::VMULPS, 8},
    {vector_instruction::VPMOVMSKB, 3},
    {vector_instruction::VPCMPEQB, 1},
    {vector_instruction::VINSERTF128, 3},
    {vector_instruction::VEXTRACTF128, 3}
};

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
  return std::shared_ptr<fetched_instruction>(new fetched_instruction(instruction));
}

std::string
fetched_instruction::instruction_str(void)
{
  return this->instruction;
}

int
fetched_instruction::decoded(void) const
{
  return 0;
}

decoded_instruction::decoded_instruction(const std::string op,
                                         const std::string destination,
                                         const std::string source1,
                                         const std::string source2)
{
  this->opcode = inst_conv(op);
  this->destination = reg_conv(destination);
  this->source1 = reg_conv(source1);
  this->source2 = reg_conv(source2);
}

int
decoded_instruction::decoded(void) const
{
  return 1;
}



std::shared_ptr<decoded_instruction>
decoded_instruction::create(const std::string op,
                            const std::string destination,
                            const std::string source1, 
                            const std::string source2)
{
  return std::shared_ptr<decoded_instruction>(
      new decoded_instruction(op,destination,source1,source2));
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

std::pair<reg,reg>
decoded_instruction::get_sources(void)
{
  return std::make_pair(this->source1,this->source2);
}
