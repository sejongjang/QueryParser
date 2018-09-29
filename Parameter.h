#ifndef Parameter_h
#define Parameter_h

#include <stdio.h>
#include <string>

using namespace std;

class Parameter {
    string name;
    
public:

    string getName() const {
        return name;
    }
    void setName(string name) {
        this->name = name;
    }
};

#endif /* Parameter_h */
