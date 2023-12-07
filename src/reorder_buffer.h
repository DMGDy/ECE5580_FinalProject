#ifndef REORDER_BUFFER_H
#define REORDER_BUFFER_H

#include "instruction.h"
#include <vector>


class reorder_buffer
{
public:
  static std::unique_ptr<reorder_buffer>create(ssize_t);
  int add_instruction(std::shared_ptr<instruction_t>instruction);
  void complete_instruction(std::shared_ptr<instruction_t> inst);
  void commit_instructions(void);
  int is_full();

private:
  reorder_buffer(ssize_t size);
  std::vector<std::pair<std::shared_ptr<instruction_t>,bool>> buffer;
  size_t size;
};


#endif
