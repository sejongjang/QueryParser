#include <sstream>
#include <iostream>
#include "Database.h"


Relation Database::evaluateQuery(Predicate& query){
    variables.clear();
    stringstream hold;
    stringstream output;
    string ID = query.getName();
    Relation relation = database[ID]; 
    vector<string> parameters = query.getStrings(); 
    vector<int> positions = toProject(parameters);
    Scheme finalScheme;
    set<string> toRename;

    for (unsigned int i = 0; i < parameters.size(); i++) {
        if (parameters[i][0] == '\'') relation.select(i,parameters[i]); 
        else {
            variables[parameters[i]].push_back(i);
            if (!toRename.count(parameters[i])) {
                toRename.insert(parameters[i]);
                finalScheme.push_back(parameters[i]);
            }
        }
    }
    for (auto itr : variables) {
        relation.select(itr.second);
    }

    Relation projected = relation.project(positions);

    Relation renamed = projected.rename(finalScheme);

	hold<< renamed.toString();
    if (relation.getSize() > 0) output << endl << query.toString() << "? Yes(" << relation.getSize() << ')' << hold.str();
    else output << endl << query.toString() << "? No\n\n";
    results = output.str();
    return renamed;
}

string Database::printRelations(){
    stringstream output;
    for (auto itr : database){
        output << endl << itr.first;
        output << itr.second.toString();
        output << endl;
    }
    return output.str();
}

vector<int> Database::toProject(const vector<string>& parameters){
    vector<int> positions;
    set<string> variables;
    for (unsigned int i = 0; i < parameters.size(); i++){
        if (parameters[i][0] != '\'')
            if (!variables.count(parameters[i])){
                positions.push_back(i);
                variables.insert(parameters[i]);
            }
    }
    return positions;
}

vector<int> Database::toProj(const Scheme& a, const Scheme& b){
    vector<int> positions;
    for (unsigned int i = 0; i < a.size(); ++i) {
        for (unsigned int j = 0; j < b.size(); ++j) {
            if (a[i] == b[j]) {
                positions.push_back(j);
            }
        }
    }
    return positions;
}

Relation Database::evaluateRule(const Rule& rule){

    vector<Relation> intermediateResults;
    vector<Predicate> ruleBody = rule.getPredicates();
    vector<int> toProject;
    vector<string> ruleParameters = rule.getName().getStrings();
    Scheme intermediateScheme, ruleScheme, factScheme;
    Relation intermediate, projected, renamed, unioned;
    string factName = rule.getName().getName();

    for (string parameter : ruleParameters) ruleScheme.push_back(parameter);

    for(Predicate predicate : ruleBody) intermediateResults.push_back(evaluateQuery(predicate));

    if (intermediateResults.size() > 1) {
        intermediate = intermediateResults[0];
        for (unsigned int i = 1; i < intermediateResults.size(); ++i) intermediate = intermediate.join(intermediate, intermediateResults[i]);
    } else intermediate = intermediateResults[0];

    intermediateScheme = intermediate.getScheme();
    toProject = toProj(ruleScheme, intermediateScheme);
    projected = intermediate.project(toProject);

    factScheme = database[factName].getScheme();
    renamed = projected.rename(factScheme);

    unioned = database[factName].Union(renamed);

    return unioned;
}

string Database::evaluateRules(const vector<Rule>& ruleList){

    stringstream output;
    vector<set<int>> components;

    reverseGraph.dfsForest();

	reverseGraph.getPostOrderNumbers();

    reverseGraph.populateIDmap(postOrderID);

	dependencyGraph.scComponents(components, postOrderID);

    for(set<int> component : components){

        output << "\nSCC:";
		isFirst = true;
		for (int i : component) {
			if (isFirst)
			{
				output << ' ' << 'R' << i;
				isFirst = false;
			}
			else 
			{
				output << ',' << 'R' << i;
			}
		}
        output << endl;
        
        output << fixedPointAlgorithm(component, ruleList);
		output << passes << " passes:";

		isFirst = true;
		for (int i : component) {
			if (isFirst)
			{
				output << ' ' << 'R' << i;
				isFirst = false;
			}
			else
			{
				output << ',' << 'R' << i;
			}
		}
		passes = 0;
    }
    return output.str();
}

string Database::fixedPointAlgorithm(const set<int>& component, const vector<Rule>& ruleList){
    stringstream output;
    bool change = true;
    Relation relation;
    
    if (component.size() == 1 && !dependencyGraph.getGraph()[*component.begin()].edges.count(*component.begin())){
        relation = evaluateRule(ruleList[*component.begin()]);
        output << ruleList[*component.begin()].toString();
        output << relation.toString() << endl;
		++passes;
    } else {  
        while (change) {        
			++passes;
            int size = 0;           
            for (int i : component) size += database[ruleList[i].getName().getName()].getSize();
            for (int i : component) {
                relation = evaluateRule(ruleList[i]);
                output << ruleList[i].toString();
                output << relation.toString() << endl;
            }
            int newSize = 0;           
            for (int i : component) newSize += database[ruleList[i].getName().getName()].getSize();          
            if (size == newSize) change = false;
			
        }      
    }
    return output.str();
}

string Database::buildGraphs(const vector<Rule>& ruleList){

    stringstream output;
    
    vector<Predicate> predicateList;
    string predicateName, ruleName;
    
    for (unsigned int i = 0; i < ruleList.size(); i++) {

        dependencyGraph.addNode(i);
        reverseGraph.addNode(i);

        predicateList = ruleList[i].getPredicates();
        
        for (unsigned int j = 0; j < predicateList.size(); j++) {
            
            for (unsigned int k = 0; k < ruleList.size(); k++) {
                
                predicateName = predicateList[j].getName();
                ruleName = ruleList[k].getName().getName();
                
                if (predicateName == ruleName) {
                    dependencyGraph.addEdge(i, k);
                    reverseGraph.addEdge(k, i);           
                }
            }
        }
    }
    output << "Dependency Graph\n" << dependencyGraph.toString();
    return output.str();
}

