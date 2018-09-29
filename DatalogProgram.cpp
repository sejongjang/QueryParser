#include <vector>
#include <string>
#include <sstream>
#include "DatalogProgram.h"
#include "Token.h"

string DatalogProgram::toString() const {
    stringstream ss;
	int schemeSize = schemeList.size();
    ss << "Schemes(" << schemeList.size() << "):\n";
    for (int i = 0; i < schemeSize; i++) {
        ss << "  " << schemeList[i].toString() << endl;
    }
	int factSize = factList.size();
    ss << "Facts(" << factList.size() << "):\n";
    for (int i = 0; i < factSize; i++) {
        ss << "  " << factList[i].toString() << endl;
    }
	int ruleSize = ruleList.size();
    ss << "Rules(" << ruleList.size() << "):\n";
    for (int i = 0; i <ruleSize; i++) {
        ss << "  " << ruleList[i].toString() << endl;
    }
	int querySize = queryList.size();
    ss << "Queries(" << queryList.size() << "):\n";
    for (int i = 0; i < querySize; i++) {
        ss << "  " << queryList[i].toString() << endl;
    }
	
    ss << "Domain(" << domain.size() << "):\n";
    for (string s : domain){
        ss << "  " << s << endl;
    }
    return ss.str();
}

void DatalogProgram::addDomain(string s){
    domain.insert(s);
}
