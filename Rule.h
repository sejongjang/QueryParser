#ifndef Rule_h
#define Rule_h

#include <stdio.h>
#include <string>
#include <vector>
#include "Predicate.h"

using namespace std;

class Rule {
    
private:
    vector<Predicate> predicateList;
    Predicate name;
    friend class DatalogProgram;
    
public:
    string toString() const;
    void setName(Predicate name) {
        this->name = name;
    }
    Predicate getName() const {
        return name;
    }
    void addPredicates(vector<Predicate> p) {
        predicateList.insert(predicateList.end(), p.begin(), p.end());
    }
    vector<Predicate> getPredicates() const {
        return predicateList;
    }
};

#endif /* Rule_h */
