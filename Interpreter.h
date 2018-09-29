#ifndef Interpreter_h
#define Interpreter_h

#include <stdio.h>
#include "DatalogProgram.h"
#include "Database.h"

using namespace std;

class Interpreter {

    DatalogProgram input;
 
    Database database;

    string output;
public:

    Interpreter(DatalogProgram& input) : input(input) {}

    void createRelations();

    void fillRelations();

    void interpret();

    void printResults();
};

#endif /* Interpreter_h */
