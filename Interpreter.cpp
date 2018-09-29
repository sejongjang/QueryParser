#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Interpreter.h"
#include "Predicate.h"
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

void Interpreter::createRelations(){
    for (Predicate scheme : input.getSchemes()) {
        Scheme s;
        for (string str : scheme.getStrings()) s.push_back(str);
        string n = scheme.getName();
        Relation temp(n,s);
        database.addRelation(temp);
    }
}

void Interpreter::fillRelations(){
    for (Predicate fact : input.getFacts()) {
        string n = fact.getName();
        Tuple t;
        for (string str : fact.getStrings()) t.push_back(str);
        database.editRelation(t, n);
    }
}

void Interpreter::interpret(){
    vector<Rule> ruleList = input.getRules();
    Relation relation;
    stringstream ss;

    createRelations();
    fillRelations();

	cout << database.buildGraphs(ruleList);
    cout << "\nRule Evaluation";

    cout << database.evaluateRules(ruleList);

    cout << "\n\nQuery Evaluation";
    for (Predicate query : input.getQueries()){
        database.evaluateQuery(query);
		cout << database.getResults();
    }
	cout << endl;
    output = ss.str();
}

void Interpreter::printResults(){
    //ofstream outFile;
    //outFile.open(fileName);
    //outFile << output;
    //outFile.close();
}