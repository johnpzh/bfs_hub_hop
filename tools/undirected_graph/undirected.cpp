/*
   For the input data of Pruned Landmark Labeling.
   The original graph might be a directed graph. So this program processes it and outputs a 
   undirected graph.
   It read a edge (s, t). If the s < t, then keep this edge, otherwise remove it.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <omp.h>
#include <algorithm>
//#include <immintrin.h>
using std::ifstream;
using std::string;
using std::getline;
using std::stringstream;
using std::cout;
using std::endl;
using std::vector;
using std::to_string;


unsigned nnodes, nedges;
double start, now;

void input_untiled(char filename[]) {
	printf("input: %s\n", filename);
	FILE *fin = fopen(filename, "r");
	if (!fin) {
		fprintf(stderr, "cannot open file: %s\n", filename);
		exit(1);
	}

	fscanf(fin, "%u %u", &nnodes, &nedges);
	unsigned *n1s = (unsigned *) malloc(nedges * sizeof(unsigned));
	unsigned *n2s = (unsigned *) malloc(nedges * sizeof(unsigned));
	vector< vector<unsigned> > n1sv(nnodes);
	unsigned bound_i = nedges;
	for (unsigned i = 0; i < bound_i; ++i) {
		if (i % 10000000 == 0) {
			now = omp_get_wtime();
			printf("time: %lf, got %u 10M edges...\n", now - start, i/10000000);//test
		}
		unsigned n1;
		unsigned n2;
		fscanf(fin, "%u %u", &n1, &n2);
		if (n1 >= n2) {
			// Swap n1 n2
			std::swap(n1, n2);
		}
		n1--;
		n1sv[n1].push_back(n2);
	}
	printf("Got origin data: %s\n", filename);

	// Make it undirected
	for (unsigned i = 0; i < nnodes; ++i) {
		if (i % 1000000 == 0) {
			now = omp_get_wtime();
			printf("time: %lf, mark %u 1M nodes...\n", now - start, i/1000000);//test
		}
		for (unsigned j = 0; j < n1sv[i].size(); ++j) {
			unsigned v = n1sv[i][j];
			if (v == (unsigned) -1) {
				continue;
			}
			for (unsigned k = j + 1; k < n1sv[i].size(); ++k) {
				if (v == n1sv[i][k]) {
					n1sv[i][k] = (unsigned) -1;
				}
			}
		}
	}
	printf("Mark finished.\n");
	vector< vector<unsigned> > n1sv_tmp(nnodes);
	for (unsigned i = 0; i < nnodes; ++i) {
		if (i % 1000000 == 0) {
			now = omp_get_wtime();
			printf("time: %lf, got %u 1M nodes...\n", now - start, i/1000000);//test
		}
		for (unsigned j = 0; j < n1sv[i].size(); ++j) {
			unsigned v = n1sv[i][j];
			if (v == (unsigned) -1) {
				continue;
			}
			n1sv_tmp[i].push_back(v);
		}
	}
	printf("Got undirected data.\n");
	unsigned edge_id = 0;
	for (unsigned i = 0; i < nnodes; ++i) {
		for (unsigned j = 0; j < n1sv_tmp[i].size(); ++j) {
			n1s[edge_id] = i + 1;
			n2s[edge_id] = n1sv_tmp[i][j];
			edge_id++;
		}
	}
	nedges = edge_id;
	printf("Only need to write.\n");

	// Write to file
	string prefix = string(filename) + "_undirected";
	FILE *fout = fopen(prefix.c_str(), "w");
	//fprintf(fout, "%u %u\n", nnodes, nedges);
	for (unsigned i = 0; i < nedges; ++i) {
		fprintf(fout, "%u %u\n", n1s[i], n2s[i]);
	}
	printf("Done.\n");
	// Clean the vectors for saving memory
	fclose(fin);
	fclose(fout);
	free(n1s);
	free(n2s);
}

int main(int argc, char *argv[]) 
{
	start = omp_get_wtime();
	char *filename;
	if (argc > 1) {
		filename = argv[1];
	} else {
		//filename = "/home/zpeng/benchmarks/data/pokec/soc-pokec";
		printf("Usage: ./app <input_file>\n");
		exit(1);
	}
	input_untiled(filename);
	return 0;
}
