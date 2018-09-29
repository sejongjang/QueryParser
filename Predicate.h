#ifndef Predicate_h
#define Predicate_h

#include <stdio.h>
#include <vector>
#include <string>
#include "Parameter.h"

using namespace std;

class Predicate{
    
public:

    Predicate(){}
    ~Predicate(){}
 
    string toString() const;

    void setName(string name) {
        this->name = name;
    }
    void addParameters(vector<Parameter> p) {
        parameterList.insert(parameterList.end(), p.begin(), p.end());
    }
    vector<string> getStrings();
    string getName() const {
        return name;
    }
private:    

    vector<Parameter> parameterList;
    string name;
};

#endif /* Predicate_h */
