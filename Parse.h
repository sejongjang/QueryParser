#ifndef Parse_h
#define Parse_h

#include <stdio.h>
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"

class Parser {

    vector<Token> tokenList;
    int itr;
    DatalogProgram hold;
    string output;
public:

    Parser(vector<Token> input): tokenList(input), itr(0) {}
    ~Parser(){}
    DatalogProgram parse();

    void match(tokenType token);

    DatalogProgram datalogProgram();

    vector<Predicate> schemeList();

    Predicate scheme();
 
    vector<Predicate> factList();
 
    Predicate fact();

    vector<Predicate> queryList();

    Predicate query();

    vector<Rule> ruleList();

    Rule rule();

    vector<Predicate> predicateList();

    Predicate predicate();

    vector<Parameter> parameterList();

    Parameter parameter();

    void printStructures(string fileName);

};

#endif /* Parse_h */
