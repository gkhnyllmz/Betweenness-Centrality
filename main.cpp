#include<time.h>
#include<thread>
#include"graph.h"

int main(int argc, char** argv){
    int size = atoi(argv[1]);
    Graph g(size);
    clock_t start = clock();
    while(1){
        int i1, i2;
        if(scanf("%d %d", &i1, &i2) == EOF)
            break;
        g.add_edge(i1,i2,1);
    }
    // For running on 4 cores
    /*thread t1(&Graph::Betweenness_Centrality, &g, 0, size/4);
    thread t2(&Graph::Betweenness_Centrality, &g, size/4, size/2);
    thread t3(&Graph::Betweenness_Centrality, &g, size/2, 3*size/4);
    thread t4(&Graph::Betweenness_Centrality, &g, 3*size/4, size);
    t1.join();
    t2.join();
    t3.join();
    t4.join();*/
    g.Betweenness_Centrality(0,size);
    printf("Time taken: %.3fs\n", double(clock()-start)/CLOCKS_PER_SEC);
    g.print_bc_sorted();
    return 0;
}
