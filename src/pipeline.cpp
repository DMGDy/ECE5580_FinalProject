#include "pipeline.h"
#include <memory>
#include <sstream>
#include <iostream>


std::map<reg,int> register_state;

Simulator::Pipeline::Pipeline(void)
{
  this->iq = instruction_queue::create(IQ_SIZE);
  this->rob = reorder_buffer::create(ROB_SIZE);
  this->rs = reservation_station::create(RS_SIZE);

  for(int i=static_cast<int>(reg::RAX);i<=static_cast<int>(reg::XMM15);++i) 
        register_state[static_cast<reg>(i)] = 1; 
}

int
Simulator::Pipeline::cycle(std::string line)
{
  this->commit();
  this->memory();
  this->execute();
  this->dispatch();
  this->issue();
  this->decode();
  this->fetch(line);

  return 0;
}

int
Simulator::Pipeline::fetch(std::string fetched_inst)
{
  for(size_t i=0;i<W;++i)
  {
    if(this->iq->full())
      return 1;
    this->iq->enqueue(fetched_instruction::create(fetched_inst));
  }
  return 0;
}

int
Simulator::Pipeline::decode(void)
{
  for(size_t i=0;i<W;++i)
  {
    if((this->iq->empty()) || (this->iq->full()))
    {
      return 1;
    }
    if(!this->iq->is_decoded())
    {
      std::shared_ptr<instruction_t> inst = iq->dequeue();
      std::string inst_str = std::dynamic_pointer_cast
        <fetched_instruction>(inst)->instruction_str();
      std::istringstream iss(inst_str);
      std::string token;
      std::vector<std::string> tokens;

      while(iss >> token)
        tokens.push_back(token);

      if(!token.empty())
      {
        std::string instruction = tokens[0];
        std::string dest_reg = tokens.size() > 1 ? tokens[1] : "" ; 
        std::string srcreg1 = tokens.size() > 1 ? tokens[2] : "" ; 
        std::string srcreg2 = tokens.size() > 1 ? tokens[3] : "" ; 
        this->iq->enqueue(decoded_instruction::create(instruction,
                                                      dest_reg,
                                                      srcreg1,
                                                      srcreg2));
      }
    }
  }
  return 0;
}

int
Simulator::Pipeline::issue(void)
{
  for(size_t i=0;i<W;++i)
  {
    if((this->iq->empty()) || (this->rs->full()))
    {
      return 1;

    }
    if(this->iq->is_decoded())
    {
      std::shared_ptr<instruction_t> inst = iq->dequeue();
      auto decoded_inst = std::dynamic_pointer_cast<decoded_instruction>(inst);
      this->rs->issue_instruction(decoded_inst);
      this->rob->add_instruction(decoded_inst);
    }
  }
  return 0;
}

int
Simulator::Pipeline::dispatch(void)
{
  if(this->rs->empty())
    return 1;
  this->rs->update(status_t::WAITING);

  return 0;
}

int
Simulator::Pipeline::execute(void)
{
  if(this->rs->empty())
    return 1;

  this->rs->update(status_t::EXECUTING);
  return 0;
}

//remove rs entry only when there is rob first one
int
Simulator::Pipeline::memory(void)
{
  this->rs->update(status_t::EXECUTED);
  return 0;
}

int
Simulator::Pipeline::commit(void)
{
  return 0;
}
