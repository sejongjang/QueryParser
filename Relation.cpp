#include <sstream>
#include <iostream>
#include "Relation.h"

using namespace std;

void Relation::select(int position, string& ID){
    set<Tuple> temp;
    for (Tuple curr : tuples){
        if (curr[position] == ID) temp.insert(curr);
    }
    tuples = temp;
}

void Relation::select(const vector<int>& positions){
    bool valid = true;
    set<Tuple>::iterator itr = tuples.begin();
    while (itr != tuples.end()){
        for (unsigned int i = 0; i < positions.size() - 1; i++) {
            if ((*itr)[positions[i]] != (*itr)[positions[i + 1]]) {
                valid = false;
                break;
            }
        }
        set<Tuple>::iterator temp = itr;
        itr++;
        if (!valid) {
            tuples.erase(*(temp));
            valid = true;
        }
    }
}

Relation Relation::project(const vector<int>& positions) {
    if (positions.size() == 0){
        return Relation();
    } else {
        Scheme newScheme;
        set<Tuple> newTuples;
        for (unsigned int i = 0; i < positions.size(); i++) {
            newScheme.push_back(scheme[positions[i]]);
        }
        for (Tuple tuple : tuples) {
            Tuple newTuple;
            for (unsigned int i = 0; i < positions.size(); i++) {
                newTuple.push_back(tuple[positions[i]]);
            }
            newTuples.insert(newTuple);
        }
        Relation newRelation(name, newScheme);
        newRelation.tuples = newTuples;
        return newRelation;
    }
}

Relation Relation::rename(const Scheme& actual){
    Scheme newScheme;
    Relation newRelation;
    newRelation.name = this->name;
    newRelation.tuples = this->tuples;
    newRelation.scheme = this->scheme;
    for (unsigned int i = 0; i < actual.size(); i++) newRelation.scheme[i] = actual[i];
    return newRelation;
}

string Relation::toString(){
    if (tuples.size() == 0) return "";
    else {
        stringstream output;
        for (Tuple tuple : tuples){
            output << "\n  ";
            for (unsigned int i = 0; i < tuple.size(); i++) {
                output << scheme[i] << '=' << tuple[i];
                if (i < scheme.size() - 1) output << ", ";
            }
        }
        return output.str();
    }
}

Relation Relation::join(const Relation& a, const Relation& b){   
    Scheme newScheme = createScheme(a.scheme, b.scheme);
    string sejong = "sejong";
    Relation newRelation(sejong, newScheme);
    for (Tuple tupleA : a.tuples){
             
        for (Tuple tupleB : b.tuples){
                      
            if (isJoinable(tupleA, a.scheme, tupleB, b.scheme)) {
                Tuple newTuple = join(tupleA, a.scheme, tupleB, b.scheme);
                newRelation.addTuple(newTuple);      
            }
        }
    }     
    return newRelation;
}

Tuple Relation::join(const Tuple& a, const Scheme& A, const Tuple& b, const Scheme& B){
    Tuple newTuple = a;
    for (unsigned int i = 0; i < B.size(); ++i) if (A.find(B[i]) == -1) newTuple.push_back(b[i]);
    return newTuple;
}

Scheme Relation::createScheme(const Scheme& a, const Scheme& b){
    Scheme newScheme = a;
    for (unsigned int i = 0; i < b.size(); ++i) if (a.find(b[i]) == -1) newScheme.push_back(b[i]);
    return newScheme;
}

bool Relation::isJoinable(const Tuple& a, const Scheme& A, const Tuple& b, const Scheme& B) const {
    
#ifdef RULE
    cout << "Entering isJoinable ";
#endif
    
    for (unsigned int i = 0; i < B.size(); ++i) if ((A.find(B[i]) != -1) && b[i] != a[A.find(B[i])]) return false;
    return true;
}

Relation Relation::Union(const Relation& newTuples){
    Relation newRelation;
    newRelation.scheme = newTuples.scheme;
    bool success;
    for (Tuple tuple : newTuples.tuples) {
        success = tuples.insert(tuple).second;
        if (success) newRelation.addTuple(tuple);
    }
    
    return newRelation;
}