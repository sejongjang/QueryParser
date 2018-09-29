#ifndef Scanner_h
#define Scanner_h

#include <stdio.h>
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"

using namespace std;

class Scanner{
    
friend class DatalogProgram;
    
public:
    Scanner(): total(0), line (1), error(false) {}
    ~Scanner(){}
    void scan(string fileName);
    void idReader(ifstream& inFile, char last);
    void stringReader(ifstream& inFile);
    void printTokens(string fileName);
    vector<Token> getTokens() const {
        return tokenList;
    }
    
private:

    vector<Token> tokenList;
    int total;
    int line;
    bool error;
};

#endif /* Scanner_h */
