#ifndef Database_h
#define Database_h

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "Relation.h"
#include "Predicate.h"
#include "Rule.h"
#include "Graph.h"

using namespace std;

class Database {

    string results;
    map<string, Relation> database;
    map<string, vector<int>> variables;
    map<int, Rule> graphID;
    map<int, int> postOrderID;
    Graph dependencyGraph;
    Graph reverseGraph;
    
public:
    void addRelation(Relation& r){
        database.insert(pair<string, Relation>(r.getName(),r));
    }
    void editRelation(Tuple& t, string& ID){
        database[ID].addTuple(t);
    }

    Relation evaluateQuery(Predicate& query);
 
    string printRelations();

    vector<int> toProject(const vector<string>& parameters);

    vector<int> toProj(const Scheme& a, const Scheme& b);

    string getResults() const {
        return results;
    }

    Relation evaluateRule(const Rule& rule);

    string evaluateRules(const vector<Rule>& ruleList);
    int getSize() const {
        int size = 0;
        for (auto itr : database) size += itr.second.getSize();
        return size;
    }
 
    string buildGraphs(const vector<Rule>& ruleList);
    
    string fixedPointAlgorithm(const set<int>& component, const vector<Rule>& ruleList);

	bool isFirst = true;
	int passes = 0;
};

#endif /* Database_h */
