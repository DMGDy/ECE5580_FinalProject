#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "pipeline.h"

unsigned l;

int
main(int argc, char* argv[])
{
  std::ofstream out("/dev/stderr");
  if(argc != 3)
  {
    out << "Usage: vector_pipeline [tracefile.trace] [FU lanes]" << std::endl;
    return 1;
  }
  std::string argv1 = argv[1];
  std::string argv2 = argv[2];

  std::cout << "Opened file " << argv2 << " for reading" <<std::endl;
  l = (unsigned)std::stoi(argv2);
  std::cout << "Functional Unit laned = " << l << std::endl;

  std::ifstream trace_file(argv1);
  if(!trace_file.is_open())
  {
    out << "Error opening file: " << argv2 << std::endl;
    return 2;
  }

  std::string line;
  Simulator::Pipeline* p = new Simulator::Pipeline();
  std::getline(trace_file,line);
  do
  {
    p->cycle(line);
  }while(std::getline(trace_file,line));

  delete p;



  return 0;
}
