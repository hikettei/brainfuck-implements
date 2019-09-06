#include <string>
#include <istream>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;



struct ProgramSeq {
  string instructions;
};


struct VMachine {
  int pointer;
  vector<int> memory;
};

void brainfuck_execute(string code, VMachine *machine);
void sequence_execute(char instruction, VMachine *machine);                                            


ProgramSeq parse_from_stream(istream& streams) {


  ProgramSeq prog;


  for(string line; getline(streams, line);) {

    for(char c : line) {
    
      if (c == '+' ||
          c == '-' ||
          c == '[' ||
          c == ']' ||
          c == '.' ||
          c == ',' ||
          c == '<' ||
          c == '>') {


        prog.instructions.push_back(c);
      } 

    }

  }

  return prog;
}


void brainfuck_execute(string code, VMachine *machine) {

  for(char i : code) {

    sequence_execute(i, machine);

  }

}


void sequence_execute(char instruction, VMachine *machine){

  int addres = machine->pointer;


  switch (instruction) {

    case '+':
      machine->memory[addres] += 1;
    
    break;

    case '-':

      machine->memory[addres] -= 1;

    break;

    case '.':

      putchar(machine->memory[addres]);

    break;

    case ',':
     
      machine->memory[addres] = getchar();
  
    break;

    case '<':

      machine->pointer--;

    break;

    case '>':

      machine->pointer++;

    break;
  }

}


int main(int argc, const char** argv) {  
  ifstream file("prog.bf");
  string code;

  vector<int> memory(256,0);
  
  VMachine machine = {0, memory};

  code = parse_from_stream(file).instructions;

  brainfuck_execute(code, &machine);
  return 0;
}

