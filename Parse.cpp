#include "Parse.h"
#include <vector>

#include <iostream>
#include <sstream>
//#define MATCH
//#define EXC
//#define DP
//#define PARSE
//#define QUERY

using namespace std;

void Parser::match(tokenType token) {
#ifdef MATCH
    cout << "Token: " << token << ", Matching token: " << tokenList[itr].toString() << endl;
#endif
    if (token == tokenList[itr].getType()) {
        if (tokenList[itr].getType() == STRING) hold.addDomain(tokenList[itr].getValue());
        itr++;
    }
    else {
#ifdef MATCH
        cout << "Throwing token exception\n";
#endif
        throw tokenList[itr];
    }
}

DatalogProgram Parser::parse(){
#ifdef PARSE
    cout << "Calling Parser::parse\n";
#endif
    try {
        datalogProgram();
        match(END);
    } catch (Token& t) {
        output = "Failure!\n  " + t.toString();
    }
    return hold;
}

DatalogProgram Parser::datalogProgram(){
#ifdef DP
    cout << "Calling Parser::datalogProgram\n";
#endif
    vector<Rule> r;
    vector<Predicate> p;
    vector<Predicate> q;
    match(SCHEMES);
    match(COLON);
    p.push_back(scheme());
    q = schemeList();
    p.insert(p.end(), q.begin(), q.end());
    hold.addSchemes(p);
    p.clear();
    q.clear();
    match(FACTS);
    match(COLON);
    p = factList();
    hold.addFacts(p);
    p.clear();
    match(RULES);
    match(COLON);
    r = ruleList();
    hold.addRules(r);
    match(QUERIES);
    match(COLON);
    p.push_back(query());
    q = queryList();
    p.insert(p.end(), q.begin(), q.end());
    hold.addQueries(p);
    return hold;
}

vector<Predicate> Parser::schemeList(){
    vector<Predicate> p;
    vector<Predicate> q;
    if (tokenList[itr].getType() != FACTS){
        p.push_back(scheme());
        q = schemeList();
        p.insert(p.end(), q.begin(), q.end());
    }
    return p;
}

Predicate Parser::scheme(){
    Predicate p = predicate();
    return p;
}

vector<Predicate> Parser::factList(){
    vector<Predicate> p;
    vector<Predicate> q;
    if (tokenList[itr].getType() != RULES){
        p.push_back(fact());
        q = factList();
        p.insert(p.end(), q.begin(), q.end());
    }
    return p;
}

Predicate Parser::fact(){
    Predicate p = predicate();
    match(PERIOD);
    return p;
}

vector<Rule> Parser::ruleList(){
    vector<Rule> r;
    vector<Rule> q;
    if (tokenList[itr].getType() != QUERIES){
        r.push_back(rule());
        q = ruleList();
        r.insert(r.end(), q.begin(), q.end());
    }
    return r;
}

Rule Parser::rule(){
    Rule r;
    vector<Predicate> p;
    vector<Predicate> q;
    r.setName(predicate());
    match(COLON_DASH);
    p.push_back(predicate());
    q = predicateList();
    p.insert(p.end(), q.begin(), q.end());
    match(PERIOD);
    r.addPredicates(p);
    return r;
}

vector<Predicate> Parser::queryList(){
#ifdef QUERY
    cout << "Calling Parser::queryList\n";
#endif
    vector<Predicate> p;
    vector<Predicate> q;
    //stop looking for more queries once the end of file token is reached
    if (tokenList[itr].getType() != END){
        p.push_back(query());
        q = queryList();
        p.insert(p.end(), q.begin(), q.end());
    }
    return p;
}

Predicate Parser::query(){
#ifdef QUERY
    cout << "Calling Parser::query\n";
#endif
    Predicate p = predicate();
    match(Q_MARK);
    return p;
}

vector<Predicate> Parser::predicateList(){
    vector<Predicate> p;
    vector<Predicate> q;
    if (tokenList[itr].getType() != PERIOD) {
        match(COMMA);
        p.push_back(predicate());
        q = predicateList();
        p.insert(p.end(), q.begin(), q.end());
    }
    return p;
}

Predicate Parser::predicate(){
    Predicate pre;
    vector<Parameter> par;
    vector<Parameter> qar;
    pre.setName(tokenList[itr].getValue());
    match(ID);
    match(LEFT_PAREN);
    par.push_back(parameter());
    qar = parameterList();
    par.insert(par.end(), qar.begin(), qar.end());
    pre.addParameters(par);
    match(RIGHT_PAREN);
    return pre;
}

vector<Parameter> Parser::parameterList(){
    vector<Parameter> p;
    vector<Parameter> q;
    if (tokenList[itr].getType() != RIGHT_PAREN) {
        match(COMMA);
        p.push_back(parameter());
        q = parameterList();
        p.insert(p.end(), q.begin(), q.end());
    }
    return p;
}

Parameter Parser::parameter(){
    Parameter p;
    if (tokenList[itr].getType() == STRING) match(STRING);
    else if (tokenList[itr].getType() == ID) match(ID);
    else {
        throw tokenList[itr];
#ifdef EXC
        cout << "Token exception thrown in Parser::parameter()\n";
#endif
    }
    p.setName(tokenList[itr - 1].getValue());
    return p;
}

void Parser::printStructures(string fileName){
    //ofstream outFile;
    //outFile.open(fileName);
    if (output == "") {
        output = hold.toString();
		cout << "Success!\n";
    }
	cout << output;
}
