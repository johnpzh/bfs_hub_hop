#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <utility> // Pair
#include "NetworKit/graph/Graph.h"
#include "NetworKit/io/EdgeListReader.h"
#include "NetworKit/centrality/ApproxBetweenness.h"

using std::string;
using std::vector;
using std::pair;
using NetworKit::Graph;
using NetworKit::EdgeListReader;
using NetworKit::ApproxBetweenness;
using NetworKit::node;

void test(char *filename)
{
	EdgeListReader reader(
						' ',
						1,
						"#",
						true,
						false);
	Graph G = reader.read(string(filename));
	uint64_t n = G.numberOfNodes();
	uint64_t m = G.numberOfEdges();
	printf("n: %lu, m: %lu\n", n, m);
}

void betweenness(char *filename)
{
	EdgeListReader reader(
						' ',
						1,
						"#",
						true,
						false);
	Graph G = reader.read(string(filename));

	// Instantiate
	ApproxBetweenness aab(G);
	// Run Approximate Betweenness
	aab.run();
	// Get Score
	const vector<double> &scores = aab.scores();
	printf("Scores:\n");
	for (auto s : scores) {
		printf("%f\n", s);
	}
	// Get Ranking
	const vector< pair<node, double> > &ranking = aab.ranking();
	printf("Ranking:\n");
	for (auto p : ranking) {
		printf("(%lu, %f)\n", p.first, p.second);
	}
}

int main(int argc, char *argv[])
{
	char *filename = nullptr;
	if (argc > 1) {
		filename = argv[1];
	} else {
		printf("Usage: ./bc.out <data_file>\n");
		exit(1);
	}
	//test(filename);
	betweenness(filename);
	return 0;
}
