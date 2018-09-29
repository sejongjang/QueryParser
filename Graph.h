#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Graph {
    
    struct Node {

        bool visited;

        std::set<int> edges;

        int postOrderNumber;

        Node() :  visited(false), postOrderNumber(0) {}

        void Insert(const int ID){
            edges.insert(ID);
        }

        int getPostOrderNumber() const {
            return postOrderNumber;
        }
    };

    std::map<int, Node> graph;

    int currentPostOrderNumber;
    
public:

    void addNode(const int ID){
        Node newNode;
        graph.insert(std::pair<int, Node> (ID, newNode));
    }

    void addEdge(const int node, const int adjacent){
        graph[node].Insert(adjacent);
    }

    string toString();

    void dfsForest();

    void dfsForest(const int ID);

    string scComponents(int ID, set<int>& scc);

    string scComponents(vector<set<int>>& components, map<int, int>& postID);

    string getPostOrderNumbers(){
        stringstream output;
        for (auto itr : graph) output << "  R" << itr.first << ": " << itr.second.postOrderNumber << endl;
        return output.str();
    }

    void populateIDmap(map<int, int>& m){
        for (auto entry : graph) m[entry.second.getPostOrderNumber()] = entry.first;
    }

    map<int, Node>& getGraph() {
        return graph;
    }

    Graph(): currentPostOrderNumber(1) {}
	bool isFirst = true;
};

#endif /* Graph_h */
