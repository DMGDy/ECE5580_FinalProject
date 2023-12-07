#include <iostream>
#include <memory>
#include <string>
#include <cstdint>
#include <unordered_map>

#ifndef PIPELINE_HPP
#define PIPELINE_HPP

/**
 * @file pipeline.hpp
 *
 * Classes and definitions used in Pipeline architecture
 */

// Defining static sizes of pipeline structures
#define RS_SIZE 32
#define IQ_SIZE 16
#define ROB_SIZE 64
#define W 4

enum class vector_instruction: int 
{
  NONE = -1,
  VMULPS,
  VADDPS
};

enum class vector_register: int 
{
  null = -1,
  YMM0,YMM1,YMM2,YMM3,YMM4,YMM5,YMM6,YMM7,
  YMM8,YMM9,YMM10,YMM11,YMM12,YMM13,YMM14,YMM15,
};

enum class status_enum_t: int
{
  EMPTY=0, WAITING, READY,
  EXECUTING, EXECUTED
};

class instruction_t
{
public:
  virtual ~instruction_t(){}
};

class fetched_instruction: public instruction_t 
{
public:
  fetched_instruction(const std::string instruction) :
    instruction(instruction){}
  ~fetched_instruction();

private:
  std::string instruction;
};

class decoded_instruction: public instruction_t
{
public:
  decoded_instruction(const std::string operation, const std::string destination,
                      const std::string source1,   const std::string source2);
  static std::unique_ptr<in
  ~decoded_instruction();
  vector_instruction get_opcode();
  vector_register get_destination_register();

private:
  vector_instruction opcode;
  vector_register destination;
  vector_register source1;
  vector_register source2;
};

class instruction_queue
{
public:
  
private:

};



class reservation_station_t
{
public:
  reservation_station_t();
  ~reservation_station_t();
  void issue_instruction(std::unique_ptr<instruction_t> instruction);
  void remove_instruction();
  int full(void);

private:
  class reservation_station_entry
  {
  public:
    reservation_station_entry(std::unique_ptr<instruction_t> instruction);
    void update_entry();

  private:
    std::unique_ptr<instruction_t> instruction;
    status_enum_t status;
  };

  std::unordered_map<std::unique_ptr<instruction_t>, std::unique_ptr<reservation_station_entry>>
    reservation_station;
  unsigned size;

};

#endif 
