#include<iostream>

int main(int argc, char** argv){
    int size = atoi(argv[1]); 
    int clique_num = atoi(argv[2]);
    int clique_size = atoi(argv[3]);
    int s,t;
    int index;
    int n_size = size-clique_size*clique_num+clique_num;

    index = size-clique_size*clique_num;
    bool **table = new bool*[n_size];
    for(int i = 0; i < n_size; i++){
        table[i] = new bool[n_size];
        for(int j=0; j < n_size; j++){
            table[i][j] = false;
        }
    }
     

    while(1){
        scanf("%d %d", &s ,&t);
        if(s == size-2 && t == size-1){
            break;
        }
    }
    while(1){
        if(scanf("%d %d", &s, &t) == EOF){
            break;
        }
        if(s > index+clique_num-1){
            s = index+(s-index)/clique_size;
        }
        if(t > index+clique_num-1){
            t = index+(t-index)/clique_size;
        }
        if(!table[s][t]){
            printf("%d %d\n", s, t);
            table[s][t] = true;
            table[t][s] = true;
        }
    }
    return 0;
}