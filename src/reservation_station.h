#ifndef RESERVATION_STATION_H
#define RESERVATION_STATION_H

#include "instruction.h"
#include <vector>

enum class status_t
{ 
  NONE = 0,
  EMPTY, WAITING, READY, EXECUTING, EXECUTED 
};

class reservation_station_entry 
{
public:
  explicit reservation_station_entry(std::shared_ptr<decoded_instruction> instruction);
  int is_ready(void) const;
  std::pair<reg,reg> sources(void) const;
  status_t inst_status(void);
  int update_status(status_t);
  std::shared_ptr<decoded_instruction> get_inst(void);

private:
  std::shared_ptr<decoded_instruction> instruction;
  status_t status;
};

class reservation_station
{
public:
  static std::unique_ptr<reservation_station>create(size_t);
  int issue_instruction(std::shared_ptr<decoded_instruction> instruction);
  int update(status_t);
  std::shared_ptr<decoded_instruction> 
    remove_instruction(std::vector<reservation_station_entry>::iterator);
  int full() const;
  int empty() const;


private:
  reservation_station(size_t maxSize);
  std::vector<reservation_station_entry> entries;
  size_t maxSize;
};
#endif
