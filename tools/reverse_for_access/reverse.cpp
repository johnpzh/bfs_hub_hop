#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

void reverse(char *filename, unsigned long max_sources)
{
	FILE *fin = fopen(filename, "r");
	if (NULL == fin) {
		fprintf(stderr, "Error: cannot open file %s.\n", filename);
		exit(1);
	}

	string name_str(filename);
	string output_name = name_str.substr(0, name_str.rfind(".")) + "_reverse" + ".txt";
	FILE *fout = fopen(output_name.c_str(), "w");
	if (NULL == fout) {
		fprintf(stderr, "Error: cannot open file %s.\n", output_name.c_str());
		exit(1);
	}

	// Get data and reverse
	puts("Reading...");
	//map<unsigned long, unsigned long> value_to_count;
	//unsigned long id;
	//unsigned long value;
	//while (fscanf(fin, "%lu%lu", &id, &value) != EOF) {
	//	if (value_to_count.find(value) == value_to_count.end()) {
	//		value_to_count[value] = 1;
	//	} else {
	//		++value_to_count[value];
	//	}
	//}
	++max_sources;
	vector<unsigned long> counts(max_sources, 0);
	unsigned long id;
	unsigned long value;
	while (fscanf(fin, "%lu%lu", &id, &value) != EOF) {
		++counts[value];
	}

	// Buckets
	//const unsigned width = 1000;
	//unsigned size = max_sources / width	+ 1;
	//vector<unsigned long> buckets(size, 0);
	//buckets[0] = counts[0];
	//unsigned k = 1;
	//for (unsigned long left_bin = 1; left_bin < max_sources; left_bin += width) {
	//	for (unsigned i = 0; i < width; ++i) {
	//		buckets[k] += counts[left_bin + i];
	//	}
	//	++k;
	//}
	const unsigned width = 1000;
	unsigned size = (max_sources - 1) / width + 1;
	vector<unsigned long> buckets(size, 0);
	buckets[0] = counts[0];
	for (unsigned k = 1; k < size; ++k) {
		for (unsigned i = 0; i < width; ++i) {
			buckets[k] += counts[(k - 1) * width + i + 1];
		}
	}


	// Write to file
	puts("Writing...");
	for (unsigned i = 0; i < size; ++i) {
		fprintf(fout, "%u %lu\n", i, buckets[i]);
	}
	for (unsigned i = 0; i < max_sources; ++i) {
		fprintf(fout, "%u %lu\n", i, counts[i]);
	}
	//for (auto el : value_to_count) {
	//	fprintf(fout, "%lu %lu\n", el.first, el.second);
	//}


}

int main(int argc, char *argv[])
{
	char *filename = nullptr;
	unsigned long max_sources;

	if (argc > 2) {
		filename = argv[1];
		max_sources = strtoul(argv[2], NULL, 0);
	} else {
		puts("Usage: ./reverse <data> <max_sources>");
		exit(1);
	}

	reverse(filename, max_sources);
	return 0;
}
