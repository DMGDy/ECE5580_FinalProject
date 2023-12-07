#include "instruction_queue.h"
#include <algorithm>
#include <memory>
#include <shared_mutex>
#include <iostream>

std::unique_ptr<instruction_queue>
instruction_queue::create(size_t size)
{
  return std::unique_ptr<instruction_queue>(new instruction_queue(size));
}

int
instruction_queue::enqueue(std::shared_ptr<instruction_t> instruction) {
  if(instruction)
  {
    this->queue.push_back(instruction);
    std::cout<<"enquiing"<<this->queue.size()<<std::endl;
    return 1;
  }
  return 0;
}

std::shared_ptr<instruction_t>
instruction_queue::dequeue(void)
{
  if(this->queue.empty())
    return nullptr;
  auto instruction = this->queue.front();
  this->queue.erase(this->queue.begin());
  std::cout<<"dequeing:"<<this->queue.size()<<std::endl;
  return instruction;
}

/*
 * return 0 if queue is not full
 * else return 1 meaning is full
 */
int
instruction_queue::full(void)
{
  if(this->queue.size() != this->size)
    return 0;
  return 1;
}

int
instruction_queue::empty(void)
{
  if(this->queue.empty())
    return 1;
  return 0;
}

int
instruction_queue::is_decoded(void)
{
  return this->queue.front()->decoded();
}

