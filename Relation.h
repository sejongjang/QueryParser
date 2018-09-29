#ifndef Relation_h
#define Relation_h

#include <stdio.h>
#include <string>
#include <set>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation {
 
    string name;
    Scheme scheme;
    set<Tuple> tuples;
    
public:
    Relation(){}
    Relation(string& name, Scheme& scheme) : name(name), scheme(scheme) {}

    void addTuple(Tuple& t){
        tuples.insert(t);
    }
    string getName() const {
        return name;
    }
    Scheme getScheme() const {
        return scheme;
    }
    set<Tuple> getTuples() const {
        return tuples;
    }

    void select(int position, string& ID);

    void select(const vector<int>& positions);

    Relation project(const vector<int>& positions);

    Relation rename(const Scheme& actual);

    string toString();

    int getSize() const {
        return tuples.size();
    }

    Tuple join(const Tuple& a, const Scheme& A, const Tuple& b, const Scheme& B);

    bool isJoinable(const Tuple& a, const Scheme& A, const Tuple& b, const Scheme& B) const;

    Scheme createScheme(const Scheme& a, const Scheme& b);

    Relation join(const Relation& a, const Relation& b);

    Relation Union(const Relation& newTuples);
};

#endif /* Relation_h */
