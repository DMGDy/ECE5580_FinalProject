#include "reservation_station.h"
#include <memory>
#include <vector>
#include <map>
  
 
extern std::map<reg,int> register_state;

reservation_station_entry::reservation_station_entry(
                      std::shared_ptr<decoded_instruction> instruction)
                      : instruction(instruction), status(status_t::EMPTY){}


int 
reservation_station_entry::is_ready() const
{
 if(register_state[this->sources().first] == 1 ||
    register_state[this->sources().second] == 1)
    return 1;
 else
    return 0;
}

std::pair<reg,reg>
reservation_station_entry::sources() const
{
    return this->instruction->get_sources();
}

int
reservation_station_entry::update_status(enum status_t s)
{
  this->status = s;
  
  return 0;
}

std::shared_ptr<decoded_instruction>
reservation_station_entry::get_inst(void)
{
  return this->instruction;
}

// Implementation for reservation_station_t

reservation_station::reservation_station(size_t maxSize)
    : maxSize(maxSize) 
{
    this->entries.reserve(this->maxSize);
}
std::unique_ptr<reservation_station>
reservation_station::create(size_t size)
{
    return std::unique_ptr<reservation_station>(new reservation_station(size));
}

int 
reservation_station::issue_instruction(std::shared_ptr<decoded_instruction> instruction) 
{
    if (entries.size() < maxSize)
    {
        entries.emplace_back(instruction);
        return 1;
    }
    return 0; // Station is full
}

std::shared_ptr<decoded_instruction>
reservation_station::remove_instruction(
                     std::vector<reservation_station_entry>::iterator it) 
{
  auto instruction = it->get_inst();
  this->entries.erase(it);

  return instruction;
}

int 
reservation_station::full(void) const 
{
    if(this->entries.size() >= this->maxSize)
        return 1;
    return 0;
}

int
reservation_station::empty(void)const
{
    if(this->entries.size() == 0)
        return 1;
    return 0;
}

int
reservation_station::update(status_t s)
{
  for(auto& entry: this->entries)
  {
    switch(s)
    {
      case(status_t::EMPTY):
        entry.update_status(status_t::WAITING);
        break;
      case(status_t::WAITING):
        if(entry.is_ready())
        {
          entry.update_status(status_t::EXECUTING);
          register_state[entry.sources().first] = 0;
          register_state[entry.sources().second] = 0;
        }
        break;
      case(status_t::READY):
        entry.update_status(status_t::EXECUTING);
        break;
      case(status_t::EXECUTING):
        entry.update_status(status_t::EXECUTED);
        break;
      case(status_t::EXECUTED):

        break;
      case(status_t::NONE):
        break;
        

    }
  }
  return 0;
}

