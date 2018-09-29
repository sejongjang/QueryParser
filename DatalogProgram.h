#ifndef DatalogProgram_h
#define DatalogProgram_h

#include <stdio.h>
#include <vector>
#include <string>
#include <set>
#include "Scanner.h"
#include "tokenType.h"
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"

using namespace std;

class DatalogProgram{
    
public:

    DatalogProgram(){}
    ~DatalogProgram(){}
 
    void addRules(vector<Rule> r) {
        ruleList.insert(ruleList.end(), r.begin(), r.end());
    }
 
    vector<Rule> getRules(){
        return ruleList;
    }
 
    void addSchemes(vector<Predicate> p) {
        schemeList.insert(schemeList.end(), p.begin(), p.end());
    }
 
    vector<Predicate> getSchemes(){
        return schemeList;
    }

    void addQueries(vector<Predicate> p) {
        queryList.insert(queryList.end(), p.begin(), p.end());
    }

    vector<Predicate> getQueries(){
        return queryList;
    }

    void addFacts(vector<Predicate> p) {
        factList.insert(factList.end(), p.begin(), p.end());
    }
   
    vector<Predicate> getFacts(){
        return factList;
    }
   
    void addDomain(string s);
    
    string toString() const;
    
private:
    vector<Rule> ruleList;
   
    vector<Predicate> schemeList;
    
    vector<Predicate> queryList;
    
    vector<Predicate> factList;
   
    set<string> domain;
    };

#endif /* DatalogProgram_h */
