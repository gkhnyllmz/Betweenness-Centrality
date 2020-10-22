#include <iostream>
#include "Graph.h"
#define G_SIZE 5

using namespace std;

template<class T>
void print_vector(vector<T> v){
    int size = v.size();
    for(int i=0; i<size; i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

void print_matrix(vector<vector<int>> matrix){
    int size = matrix[0].size();
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){

    int size;

    // Read vertex number of graph
    cin >> size;

    // bc will be filled by function Betweenness Centrality
    vector<double> bc(size);

    // Read the graph as adj. matrix
    int **matrix = new int*[size];
    for(int i=0; i<size; i++){
        matrix[i] = new int[size];
        for(int j=0; j<size; j++){
            cin >> matrix[i][j];
        } 
    }

    // Create graph from the matrix
    Graph g(size, matrix);

    // Calculate betweenness centrality values of vertices of graph
    g.Betweenness_Centrality(bc);

    // Print betweenness centrality values
    print_vector(bc);

    // Deallocate matrix
    for(int i=0; i<size; i++){
        delete [] matrix[i];
    }
    delete [] matrix;
    
    return 0;
}