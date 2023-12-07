#include "reorder_buffer.h"
#include <memory>

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
  return std::unique_ptr<reorder_buffer>(new reorder_buffer(size));
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

