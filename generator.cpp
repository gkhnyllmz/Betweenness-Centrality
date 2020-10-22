#include<iostream>
#include <stdlib.h>
#include <time.h> 

int main(){
    int size;
    int clique_size;
    int clique_num;
    int density;
    int index;
    int clique_edge = 0;
    srand(time(NULL));

    scanf("%d", &size);
    scanf("%d", &density);
    scanf("%d", &clique_num);
    scanf("%d", &clique_size);
    /*int cliques[clique_num];
    for(int i=0; i<clique_num; i++){
        scanf("%d", &cliques[i]);
    }*/

    index = size-clique_size*clique_num;
    bool **matrix = new bool*[size];
    for(int i=0; i<size; i++){
        matrix[i] = new bool[size];
        for(int j=0; j<size; j++){
            matrix[i][j] = false;
        }
    }
    for(int i=0; i<clique_num; i++){
        //printf("%d\n", size);
        //printf("%d\n", clique_size);
        for(int i=index; i<index+clique_size; i++){
            for(int j=i+1; j<index+clique_size; j++){
                if(i != j){
                    matrix[i][j] = true;
                    printf("%d %d\n", i, j);
                    clique_edge++;
                }
            }
        }
        index += clique_size;
    }

    int e = size*size*density/200-clique_edge/2;
    for(int i=0; i < e; i++){
        int s = rand()%size;
        int t = rand()%size;
        if(s == t || matrix[s][t]){
            i--;
            continue;
        }
        matrix[s][t] = true;
        matrix[t][s] = true;
        printf("%d %d\n", s, t);
    }

    return 0;
}
