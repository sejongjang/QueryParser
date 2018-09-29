#ifndef Token_h
#define Token_h

#include <stdio.h>
#include <string>
#include "tokenType.h"

using std::string;

class Token {
public:
    Token(tokenType type, string value,  int line):
    type(type), line(line), value(value) {}

    ~Token(){}
 
    string toString();
 
    tokenType getType() const {
        return type;
    }
    string getValue() const {
     return value;   
    }
private:
    tokenType type;
    int line;
    string value;
    
};

#endif /* token_h */
