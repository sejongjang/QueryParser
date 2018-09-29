#include "Rule.h"
#include <sstream>
#include <string>

string Rule::toString() const {
    std::stringstream ss;
    ss << name.toString() << " :- ";
    for (unsigned int i = 0; i < predicateList.size(); i++) {
        ss << predicateList[i].toString();
        if (i < predicateList.size() - 1) ss << ',';
    }
	ss << ".";
    return ss.str();
}