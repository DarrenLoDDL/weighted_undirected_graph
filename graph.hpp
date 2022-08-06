#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility> 
#include <algorithm>
#include <string>
#include <cstdlib>
#include <vector>
#include <tuple>

using namespace std;

template <typename T> // the template allows the weight of an edge to take any numeric data type (denoted by T).
class Graph {

	public:

        //int get_index(const string&);
        
        /* define your data structure to represent a weighted undirected graph */
        vector<string> vertex_list; //declare vertex
        vector<tuple<string, string, T>> edge_list;
    
        /* test1 */
		Graph(); // the contructor function.
		~Graph(); // the destructor function.
		size_t num_vertices(); // returns the total number of vertices in the graph.
		size_t num_edges(); // returns the total number of edges in the graph.
        vector<string> all_visits;

        /* test2 */
        void add_vertex(const string&); // adds a vertex to the graph -- every vertex uses a string as its unique identifier.
        bool contains(const string&); // checks if a vertex is in the graph -- returns true if the graph contains the given vertex; otherwise, returns false.
        
        /* test3 */
        vector<string> get_vertices(); // returns a vector of all the vertices in the graph.

        void add_edge(const string&, const string&, const T&); // adds a weighted edge to the graph -- the two strings represent the incident vertices; the third parameter represents the edge's weight.
        bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the graph -- returns true if the edge exists; otherwise, returns false.
		
        /* test5 */
        vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the graph -- each edge is represented by a pair of vertices incident to the edge.
        
        /* test6 */
        vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex by an edge.
        size_t degree(const string&); // returns the degree of a vertex.

        /* test7 */
		void remove_edge(const string&, const string&); // removes the edge between two vertices, if it exists.
        
        /* test8 */
        void remove_vertex(const string&); // delete the given vertex from the graph -- note that, all incident edges of the vertex should be deleted as well.

        /* test9 */
		vector<string> depth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a depth-first traversal from the given vertex.
		vector<string> depth_first_traversal_helper(const string&, vector<string>, unordered_map<string, bool>); 

        /* test10 */
        vector<string> breadth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a breadth-first traversal from the given vertex.
        
        /* test11 */
		bool contain_cycles(); // check if the graph contains any cycle -- returns true if there exists a path from a vertex to itself; otherwise, return false.
        
        /* test12 */
		Graph<T> minimum_spanning_tree(); // returns a spanning tree of the graph -- the returned tree is preferably a minimum spanning tree.
		
};

/* test1 */

template <typename T>
Graph<T>::Graph() {
    //adj_matrix = new T*[num_vertices()];
	//for(int i = 0; i < num_vertices(); i++) {
		//adj_matrix[i] = new T[num_vertices()];
		// TO PRINT OUT
	//for(int j = 0; j < num_vertices(); j++) {
		//	adj_matrix[i][j] = 0;
		//}
	//}
} 

template <typename T>
Graph<T>::~Graph() {}


template <typename T>
size_t Graph<T>::num_vertices() {
    return vertex_list.size();
    //just get size 
}

template <typename T>
size_t Graph<T>::num_edges() {
    return edge_list.size();
}

/* test2 */

template <typename T>
void Graph<T>::add_vertex(const string& u) {
    vertex_list.push_back(u);
}

template <typename T>
bool Graph<T>::contains(const string& u) {
    for(int i = 0; i < vertex_list.size(); i++){
        if(vertex_list[i] == u){
            return true;
        }
    }
    return false;
}

/* test3 */

template <typename T>
vector<string> Graph<T>::get_vertices() {
    return vertex_list;
}

/* test4 */

template <typename T>
void Graph<T>::add_edge(const string& u, const string& v, const T& weight) {
    tuple<const string&, const string&, const T&>
    edge_pair = make_tuple(u, v, weight);
    edge_list.push_back(edge_pair);
}
    
template <typename T>
bool Graph<T>::adjacent(const string& u, const string& v) {
    for(int i = 0; i < edge_list.size(); i++){
        if(get<0>(edge_list[i]) == u && get<1>(edge_list[i]) == v){
               return true;
           }
        if(get<0>(edge_list[i]) == v && get<1>(edge_list[i]) == u){
            return true;
        }
    }
    return false;
}

/* test5 */

template <typename T>
vector<pair<string,string>> Graph<T>::get_edges() {
    vector<pair<string, string>> edge_list_mini;
    for(int i = 0; i < edge_list.size(); i++){
        pair<string,string> edge;
        edge.first = get<0>(edge_list[i]);
        edge.second = get<1>(edge_list[i]);
        edge_list_mini.push_back(edge);
    }

    return edge_list_mini;
}

/* test6 */

template <typename T>
vector<string> Graph<T>::get_neighbours(const string& u) {
    vector<string> neighbours;
    for(int i = 0; i < edge_list.size(); i++){
        if(get<0>(edge_list[i]) == u){
            neighbours.push_back(get<1>(edge_list[i]));
        }
        if(get<1>(edge_list[i]) == u){
            neighbours.push_back(get<0>(edge_list[i]));
        }
    }
    return neighbours;
}

template <typename T>
size_t Graph<T>::degree(const string& u) {
    return get_neighbours(u).size();
}

/* test7 */

template <typename T>
void Graph<T>::remove_edge(const string& u, const string& v) {

    for (int i = 0; i < edge_list.size(); i++){
        if(get<1>(edge_list[i]) == v && get<0>(edge_list[i]) == u){
            edge_list.erase(edge_list.begin() + i);
            i--;
        }
        if(get<1>(edge_list[i]) == u && get<0>(edge_list[i]) == v){
            edge_list.erase(edge_list.begin() + i);
            i--;
        }
    }
    
}

/* test8 */

template <typename T>
void Graph<T>::remove_vertex(const string& u) {
    //if first or second entry contain u, remove edge
    vector<string> neighbours = get_neighbours(u);
    for(int i = 0; i < neighbours.size(); i++){
       remove_edge(u, neighbours[i]); //we dont need if statments, since remove_edge takes (a, b) and (b,a)
    }
    
    //then remove the vertex
    for(int i = 0; i < vertex_list.size(); i++){
        if(vertex_list[i]==u){
            vertex_list.erase(vertex_list.begin()+i);
            i--;
        }
    }
}

/* test9 */

template <typename T>
vector<string> Graph<T>::depth_first_traversal(const string& u) {
    stack<string> stack; //the stack....
    unordered_map<string, bool> visit_status; //to track our visits
    vector<string> all_visits; //the final output
    for(int i = 0; i < vertex_list.size() ; i++){
        visit_status.insert({vertex_list[i], false}); //add to our list, we track if we visited with bool
    }
    //for (auto x : visit_status)
      //cout << x.first << endl;

    stack.push(u); 
    string s = stack.top();
    //cout << s << endl;
    while(stack.empty() != false){
        
        stack.pop();
        if(visit_status.at(s) == false){ //if you havent visited, mark as visited, push to list
            visit_status.at(s) = true;
            all_visits.push_back(s); 
            stack.pop();
            vector<string> neighbours = get_neighbours(s);
            for(int i = 0; i < neighbours.size(); i++){
                    stack.push(neighbours[i]); //push neighbours onto stack
                }
                s = stack.top(); //update the top fo stack
            }
        if(visit_status.at(s) == true){
            stack.pop();
            s = stack.top(); //pop then go next if youve seen it
        }
    }
    //cout<<all_visits.size();
     return all_visits;
}


/* test10 */

template <typename T>
vector<string> Graph<T>::breadth_first_traversal(const string& u) {
   return vector<string>();
}

/* test11 */

template <typename T>
bool Graph<T>::contain_cycles() {
    return false;
}

/* test12 */

template <typename T>
Graph<T> Graph<T>::minimum_spanning_tree() {
    return Graph<T>();
}
