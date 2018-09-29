#include "Predicate.h"
#include <sstream>
#include <string>

string Predicate::toString() const {
    std::stringstream ss;
    ss << name << '(';
    for (unsigned int i = 0; i < parameterList.size(); i++) {
        ss << parameterList[i].getName();
        if (i < parameterList.size() -1) ss << ',';
    }
    ss << ')';
    return ss.str();
}

vector<string> Predicate::getStrings() {
    vector<string> s;
    for (unsigned int i = 0; i < parameterList.size(); i++) {
        s.push_back(parameterList[i].getName());
    }
    return s;
}