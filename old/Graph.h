#include "BinaryHeap.h"

using namespace std;

typedef struct node{ // Will be used for adjacent list representation

    struct node* next;
    int weight;
    int node; 

} node;

class Graph{

    private:
        vector<node*> adjList; // Represents edges
        int size = 0;
    
    public:

        // Creates a graph with no edges and no vertices
        Graph(){}

        // Creates a graph with no edges
        Graph(int size){ 
            adjList = vector<node*>(size, NULL);
            this->size = size;
        }

        // Creates a graph from matrix representation
        Graph(int size, int** matrix){
            adjList = vector<node*>(size, NULL);
            this->size = size;
            for(int i=0; i<size; i++){
                for(int j=0; j<size; j++){
                    if(matrix[i][j]){
                        add_edge(i,j,matrix[i][j]);
                    }
                }
            }
        }

        ~Graph(){
            for(int i=0; i<size; i++){
                node *temp = adjList[i];
                while(temp){
                    node *del = temp;
                    temp = temp->next;
                    delete del;
                }
            }
        }

        // Adds node to end of the adjacent list with node number "size-1"
        void add_node(){
            adjList.push_back(NULL);
            size++;
        }

        // Deletes node from end of the adjacent list
        void delete_node(){
            node *temp = adjList[size-1];
            while(temp){
                node *del = temp;
                temp = temp->next;
                delete del;
            }
            adjList.erase(adjList.begin()+size-1);
            size--;
        }

        // Adds edges from n1 to n2 with wei
        void add_edge(int n1, int n2, int weight){
            if(adjList[n1] == NULL){ // There is no edge from n1 to any vertex
                adjList[n1] = new node{NULL, weight, n2};
            }
            else{
                node* temp = adjList[n1];
                while(temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = new node{NULL, weight, n2};
            }
        }
        
        // Returns size of the graph
        int get_size(){
            return size;
        }

        // Prints adjacent list
        // Ex: a->b:c means that there is an edge from a to b with weight c
        void print(){
            for(int i=0; i<size; i++){
                node* temp = adjList[i];
                while(temp){
                    printf("%d->%d:%d, ", i, temp->node, temp->weight);
                    temp = temp->next;
                }
                cout << endl;
            }
        }

        // Calculates single source shortest path for graphs which contain negative edges without negative cycles
        // Input: s: Source, dist: Array with size V (V: vertex number)
        // Output: Fills the array with shortest paths (dist[i]->shortest path from s to i)
        bool Bellman_Ford(int s, vector<int>& dist){
            for (int i=0; i<size; i++){ // Set all distances to INF
                dist[i] = INT_MAX;
            }
            dist[s] = 0; // Set distances of source to 0
            for(int i=0; i<size-1; i++){ // Visit all edges V-1 times
                for(int j=0; j<size; j++){
                    node* temp = adjList[j];
                    while(temp){
                        if(dist[temp->node] > temp->weight + dist[j] && dist[j] != INT_MAX){ // If there is a shorter path, relax the distance array 
                            dist[temp->node] = temp->weight + dist[j];
                        }
                        temp = temp->next;
                    }
                }
            }
            for(int j=0; j<size; j++){ // Look for whethere there is a negative cycle
                node* temp = adjList[j]; 
                while(temp){
                    if(dist[temp->node] > temp->weight + dist[j]){ // After V-1 step, it we still make relaxation, there is negative cycle
                        return true; // Return TRUE if there is negative cycle
                    }
                    temp = temp->next;
                }
            }
            return false; // Return FALSE if there is no negative cycle
        }

        // Calculates single source shortest path for graphs which don't contain negative edges
        // Input:  s: Source, dist: Array with size V, count: Array with size V (V: vertex number)
        // Output: Fills the dist array with shortest paths (dist[i]->shortest path from s to i)
        //         Fills the count array with number of shortest paths (count[i]->number of shortest paths from s to i)
        void Dijkstra(int s, vector<int>& dist, vector<int>& count){
            vector<bool> visited(size, false);
            BinaryHeap heap(size);
            for (int i=0; i<size; i++){ // Set all distances to INF
                dist[i] = INT_MAX;
                count[i] = 0;
            }
            dist[s] = 0; // Set distance of source to 0 on distance array
            visited[s] = true;
            count[s] = 1;
            heap.decrease_key(s, 0); // Set key of source to 0 on heap
            while (!heap.is_empty()){
                int u = heap.extract_min(); // Pop the root of the heap
                visited[u] = true; // If it is visited, it should not be visited again
                for(node* temp = adjList[u]; temp; temp=temp->next){ // Visit all edges from u
                    if(!visited[temp->node] && dist[temp->node] > temp->weight + dist[u] && dist[u] != INT_MAX){ // Relax if there is a shorter path
                        dist[temp->node] = temp->weight + dist[u]; // Relax the distance array
                        heap.decrease_key(temp->node, temp->weight + dist[u]); // Relax the heap
                        count[temp->node] = count[u]; // Set the count of reached node with its parents count
                    }
                    else if(dist[temp->node] == temp->weight + dist[u]){
                        count[temp->node]++; // If a node is reached again with the same cost, increase its count by 1
                    }
                }
            }
        }

        // Calculates all pair shortest path for graphs which contain negative edges
        // Input: VxV matrix (V: vertex number)
        // Output: False if there is negative cycle
        //         True if there is no negative cycle, and fills the matrix with shortest paths (allPairs[i][j]->shortest path from i to j)
        bool Jonhson(vector<vector<int>>& allPairs, vector<vector<int>>& count){
            this->add_node(); // Add a new vertex
            for(int i=0; i<size-1; i++){ // Add edges from new vertex to all vertices with 0 weight
                add_edge(size-1, i, 0);
            }
            vector<int> dist(size);
            if(this->Bellman_Ford(size-1,dist)){ // Calculate shortest paths from new vertex to all vertices
                cout << "This graph contains negative cycle" << endl;
                return false; // If there is negative cycle, don't do anything
            }
            else{
                for(int u=0; u<size; u++){ // Reweight all edges
                    for(node *temp=adjList[u]; temp; temp=temp->next){
                        temp->weight += dist[u] - dist[temp->node]; // w(u,v) += h(u) - h(v)
                    }
                }
                delete_node();
                allPairs = vector<vector<int>>(size, vector<int>(size, INT_MAX));
                for(int i=0; i<size; i++){
                    this->Dijkstra(i,allPairs[i],count[i]); // For all vertices, run Dijkstra for all pair shortest path
                    for(int j=0; j<size; j++){
                        allPairs[i][j] += dist[j] - dist[i]; // d(i,j) += h(j)- h(i)
                    }
                }
                return true;
            }
        }

        // Calculates betweenness centrality for graphs(Graphs can include negative edges)
        // Input: bc: Array with size V (V: vertex number)
        // Output: False if there is negative cycle
        //         True if there is no negative cycle, and fills the array with betweenness centrality values(bc[i]->betweenness centrality value for vertex i)
        bool Betweenness_Centrality(vector<double>& bc){
            vector<vector<int>> allPairs(size, vector<int>(size, INT_MAX));
            vector<vector<int>> count(size, vector<int>(size));
            if(Jonhson(allPairs, count)){
                for(int v=0; v<size; v++){
                    double sum = 0;
                    for(int s=0; s<size; s++){
                        if(s != v){
                            for(int t=0; t<size; t++){
                                if(t != s && t != v && allPairs[s][v] + allPairs[v][t] == allPairs[s][t]){
                                    // (Number of shortest paths from s to t which include v) / (Number of shortest path from s to t)
                                    sum += ((double)(count[s][v] * count[v][t])) / count[s][t]; 
                                }
                            }
                        }
                    }
                    bc[v] = sum;
                }
                return true;
            }
            else{
                return false;
            }
        }
};