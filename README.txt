################################# Usage Steps #################################

1-Generate a random graph by "generator"
2-Detect cliques by "PCE"
3-Convert the cliques by "converter"
4-Calculate betweenness centrality by "main"

################################# Generator #################################

-Generates a graph with given size and density including cliques with given number and size

-It takes 4 inputs:
1 - Graph size
2 - Graph density
3 - Clique number
4 - Clique size

Example run:

./generator > graph.txt
-> 1000
-> 10
-> 20
-> 5

-Generates a graph with size 1000 and density 10% including 20 cliques with size 5 in graph.txt
-It generates edges in the cliques at first, then generates random edges.

################################# PCE #################################

-PCE has its readme file.
-NOTE: The generated graph is not suitable for PCE. It must be tranformed by transgraph.pl in PCE.

Example Run
./transgraph.pl < graph.txt > trans_graph.txt

-It can be used after this transformation.

################################# Converter #################################

-Deletes edges in the cliques, enumarates the cliques and change other edges according to this enameration

-NOTE: converter uses the generation style of the generator for detecting and converting cliques, so PCE is used for only observing detection time. It is a future work that developing a converter that uses the PCE output.

-It takes a graph, graph size, clique number and clique size and prints the converted graph to the standart output.

Template Run:
./converter < [input graph] > [output graph] [graph size] [clique number] [clique size]

Example Run for a graph with size 1000 including 20 cliques with size 5:
./converter < graph.txt > con_graph.txt 1000 20 5

Example:

-Output of the generator with inputs 20,10,1,5 -> graph with size 20 and density 10 with 1 clique with size 5:

15 16
15 17
15 18
15 19
16 17
16 18
16 19
17 18
17 19
18 19
15 12
6 7
13 18
5 6
3 19
18 11
1 17
0 10
5 12
5 14
15 8
10 6
18 8
6 18
2 15

The first 10 edges are cliques edges. converter deletes them and enumarates the clique as 15. Then updates all edges which include a node from the clique.

Converter output (./converter < graph.txt > con_graph.txt 20 1 5):

15 12
6 7
13 15
5 6
3 15
15 11
1 15
0 10
5 12
5 14
15 8
10 6
6 15
2 15

################################# Main #################################

-Calculates betweenness centrality scores of the given graph.
-Takes a graph and its size as input.

Template Run:
./main < [graph name] [size]
