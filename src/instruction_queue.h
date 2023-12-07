#ifndef INSTRUCTION_QUEUE_H
#define INSTRUCTION_QUEUE_H

#include "instruction.h"
#include <memory>
#include <vector>

class instruction_queue
{
public:
  static std::unique_ptr<instruction_queue> create(size_t);
  int enqueue(std::shared_ptr<instruction_t>);
  std::shared_ptr<instruction_t> dequeue(void);
  int full(void);
  int empty(void);
  int is_decoded(void);

private:
  instruction_queue(size_t size):size(size){};
  
  std::vector<std::shared_ptr<instruction_t>> queue;
  size_t size;
};

#endif
