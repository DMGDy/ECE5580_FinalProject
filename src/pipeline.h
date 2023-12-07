#ifndef PIPELINE_H
#define PIPELINE_H
#include "register.h"
#include "instruction.h"
#include "reorder_buffer.h"
#include "reservation_station.h"
#include "instruction_queue.h"
#include <map>

namespace Simulator{



/*
 * constants for this simulator
 */
#define RS_SIZE 32
#define IQ_SIZE 16
#define ROB_SIZE 64
#define W 4

class Pipeline 
{
public:
  Pipeline(void);
  int cycle(std::string);

private:
  /* pipeline stages */
  int fetch(std::string);
  int decode(void);
  int issue(void);
  int dispatch(void);
  int execute(void);
  int memory(void);
  int commit(void);

  void init_reg_state(std::map<reg,int>);

  std::unique_ptr<instruction_queue> iq;
  std::unique_ptr<reorder_buffer> rob;
  std::unique_ptr<reservation_station> rs;


  /*
   * Keeping map of all registers
   */


};

}

#endif

