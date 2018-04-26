#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include <string>
#include <unistd.h>
#include <algorithm>
#include <functional>

using std::string;
using std::to_string;

struct Vertex {
	unsigned *out_neighbors;
	unsigned out_degree;

	unsigned get_out_neighbor(unsigned i) {
		return out_neighbors[i];
	}
	unsigned get_out_degree() {
		return out_degree;
	}
};

unsigned NNODES;
unsigned NEDGES;
unsigned NUM_THREADS;
unsigned TILE_WIDTH;
unsigned SIDE_LENGTH;
unsigned NUM_TILES;
unsigned ROW_STEP;
unsigned CHUNK_SIZE;
unsigned T_RATIO;


///////////////////////////////////////////////////////////////////////////////
// Input data and then apply BFS
///////////////////////////////////////////////////////////////////////////////
void graph_input(
			char *input_f,
			unsigned *&graph_heads,
			unsigned *&graph_tails,
			unsigned *&tile_offsets,
			unsigned *&tile_sizes,
			unsigned *&graph_vertices,
			unsigned *&graph_edges,
			unsigned *&graph_degrees)
{
	/////////////////////////////////////////////////////////////////////
	// Input real dataset
	/////////////////////////////////////////////////////////////////////
	string prefix = string(input_f) + "_untiled";
	//string prefix = string(input_f) + "_coo-tiled-" + to_string(TILE_WIDTH);
	//string prefix = string(input_f) + "_col-" + to_string(ROW_STEP) + "-coo-tiled-" + to_string(TILE_WIDTH);
	//string prefix = string(input_f) + "_col-2-coo-tiled-" + to_string(TILE_WIDTH);
	string fname = prefix + "-0";
	FILE *fin = fopen(fname.c_str(), "r");
	if (!fin) {
		fprintf(stderr, "cannot open file: %s\n", fname.c_str());
		exit(1);
	}
	fscanf(fin, "%u %u", &NNODES, &NEDGES);
	fclose(fin);

	// For Sparse
	graph_degrees = (unsigned *) malloc(sizeof(unsigned) * NNODES);

	// Read degrees
	fname = prefix + "-nneibor";
	fin = fopen(fname.c_str(), "r");
	if (!fin) {
		fprintf(stderr, "cannot open file: %s\n", fname.c_str());
		exit(1);
	}
	for (unsigned i = 0; i < NNODES; ++i) {
		fscanf(fin, "%u", graph_degrees + i);
	}
	fclose(fin);

	std::sort(graph_degrees, graph_degrees + NNODES, std::greater<unsigned>());
	for (unsigned i = 0; i < NNODES; ++i) {
		printf("%u %u\n", i, graph_degrees[i]);
	}

	// End Input real dataset
	/////////////////////////////////////////////////////////////////////


}
///////////////////////////////////////////////////////////////////////////////
// Main Program
///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv) 
{
	int max_hop;
	int max_count;
	char *input_f;
	
	if(argc > 1){
		input_f = argv[1];
	} else {
		puts("Usage: ./bfs <data>");
		exit(1);
	}

	// Input
	unsigned *graph_heads = nullptr;
	unsigned *graph_tails = nullptr;
	unsigned *tile_offsets = nullptr;
	unsigned *tile_sizes = nullptr;
	unsigned *graph_vertices = nullptr;
	unsigned *graph_edges = nullptr;
	unsigned *graph_degrees = nullptr;

	//input( argc, argv);
	graph_input(
			input_f,
			graph_heads,
			graph_tails,
			tile_offsets,
			tile_sizes,
			graph_vertices,
			graph_edges,
			graph_degrees);
	// cleanup memory
	free( graph_heads);
	free( graph_tails);
	free( graph_edges);
	free( graph_degrees);
	free( graph_vertices);
	free( tile_offsets);
	free( tile_sizes);
}

//int main( int argc, char** argv) 
//{
//	start = omp_get_wtime();
//	input( argc, argv);
//}

