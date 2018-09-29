#include "Graph.h"

string Graph::toString(){
	
    stringstream ss;
    for (auto i : graph){
        ss << "  R" << i.first << ':';
        for (int j : i.second.edges) {
			if (isFirst)
			{
				ss << " R" << j;
				isFirst = false;
			}
			else
			{
				ss << ",R" << j;
			}
        }
		isFirst = true;
        ss << endl;
    }
    return ss.str();
}

void Graph::dfsForest(){
    currentPostOrderNumber = 1;
    for (auto itr : graph)
        if (!itr.second.visited) {
            dfsForest(itr.first);
        }
}

void Graph::dfsForest(const int ID){

    graph[ID].visited = true;

    for (int i : graph[ID].edges){

        if (!graph[i].visited) dfsForest(i);
        
    }

    graph[ID].postOrderNumber = currentPostOrderNumber;
    currentPostOrderNumber++;
    
}

string Graph::scComponents(int ID, set<int>& scc){
    
    stringstream output;
    
    output << "  R" << ID << endl;
    
    Node& x = graph[ID];
    
    x.visited = true;
    
    for (int i : x.edges) if (!graph[i].visited) output << scComponents(i, scc);
    
    scc.insert(ID);
    
    return output.str();
}

string Graph::scComponents(vector<set<int>>& components, map<int, int>& postID){

    stringstream output;
    for (unsigned int i = graph.size(); i > 0; i--){

        set<int> component;

        int begin = postID[i];
        
        output << endl << "  R" << begin;

        if (!graph[begin].visited) {
            scComponents(begin, component);
            components.push_back(component);
        }
    }
    
    return output.str();
}
