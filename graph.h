#include <stack>
#include <atomic>
#include <queue>
#include <iostream>

using namespace std;

typedef struct node{ // Will be used for adjacent list representation

    int weight;
    int node; 

} node;

class Graph{

    private:
        vector<node> (*adjList); // Represents edges
        atomic<double> (*bc);
        vector<int> comm[5];
        int size = 0;
    
    public:

        // Creates a graph with no edges and no vertices
        Graph(){}

        // Creates a graph with no edges
        Graph(int size){ 
            adjList = new vector<node>[size];
            this->size = size;
            bc = new atomic<double>[size];
        }

        ~Graph(){
            delete [] adjList;
            delete [] bc;
        }

        // Adds edges from n1 to n2 with weight
        void add_edge(int n1, int n2, int weight){
            for(int i=0; i<adjList[n1].size(); i++){
                if(adjList[n1][i].node == n2){
                    return;
                }
            }
            adjList[n1].push_back(node{weight, n2});
            adjList[n2].push_back(node{weight, n1});
        }

        void print_bc(){
            for(int i=0; i<size; i++){
                cout << i << ": " << bc[i] << "\n";
            }
        }

        void print_bc_sorted(){
            for(int j=0; j<size; j++){
                double max = -1;
                int index;
                for(int i=0; i<size; i++){
                    if(bc[i] > max){
                        max = bc[i];
                        index = i;
                    }
                }
                cout << index << ": " << max << "\n";
                bc[index] = -2;
            }
        }

        void Betweenness_Centrality(int b, int t){
            //struct timespec start, end;
            //clock_gettime(CLOCK_REALTIME, &start);
            for(int s=b; s<t; ++s){
                stack<int> st;
                vector<int> P[size];
                queue<int> q;
                int sigma[size];
                int d[size];
                double delta[size];
                for(int i=0; i<size; i++){
                    sigma[i] = 0;
                    d[i] = -1;
                    delta[i] = 0;
                }
                sigma[s] = 1;
                d[s] = 0;
                q.push(s);
                while(!q.empty()){
                    int v = q.front();
                    q.pop();
                    st.push(v);
                    for(int i = 0; i<adjList[v].size(); i++){
                        int w = adjList[v][i].node;
                        if(d[w] < 0){
                            q.push(w);
                            d[w] = d[v] + 1;
                        }
                        if(d[w] == d[v] + 1){
                            sigma[w] += sigma[v];
                            P[w].push_back(v);
                        }
                    }
                }
                while(!st.empty()){
                    int w = st.top();
                    st.pop();
                    for(int i=0; i<P[w].size(); i++){
                        int v = P[w][i];
                        if(sigma[w]){
                            delta[v] += ((double)sigma[v] / (double)sigma[w]) * (double)(1 + delta[w]);
                        }
                    }
                    if(w != s){
                        double old = bc[w].load(memory_order_consume);
                        double d = delta[w];
                        double desired = old + d;
                        while (!bc[w].compare_exchange_weak(old, desired,
                            memory_order_release, memory_order_consume))
                        {
                            desired = old + d;
                        }
                    }
                }
            }
        //clock_gettime(CLOCK_REALTIME, &end);
        //cout << end.tv_sec - start.tv_sec << ":" << end.tv_nsec - start.tv_nsec << "\n";
        }
};
