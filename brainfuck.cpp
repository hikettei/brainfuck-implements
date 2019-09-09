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
  ProgramSeq seq;
  vector<int> memory;
};

void brainfuck_execute(string code, VMachine *machine);
void sequence_execute(char instruction, VMachine *machine, int pc);                                            


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

  int pc = 0;

  for(char i : code) {

    pc++;
    sequence_execute(i, machine, pc);

  }

}


void sequence_execute(char instruction, VMachine *machine, int pc){

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

    case '[':

      string prog = "";
      int brac_size = 1;
      
      while (brac_size <= 0) {
	cout << brac_size;
	prog+=machine->seq.instructions[pc];

	switch (machine->seq.instructions[pc]) {
	  case '[':
	    brac_size++;
	  break;

	  case ']':
	    brac_size--;
	  break;
	}
      }

    
      int last_pointer = machine->memory[machine->pointer];

      while(last_pointer) {
        brainfuck_execute(prog, machine);
        last_pointer = machine->memory[machine->pointer];
      }

    break;
  }

}


int main(int argc, const char** argv) {  

  ifstream file("prog.bf");
  string code;

  vector<int> memory(256,0);
 
  code = parse_from_stream(file).instructions;   

  VMachine machine = {0, code, memory};

  brainfuck_execute(code, &machine);
  return 0;

}

