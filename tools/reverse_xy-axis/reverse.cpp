#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>

using std::map;
using std::string;

void reverse(char *filename)
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
	map<unsigned long, unsigned long> value_to_count;
	unsigned long id;
	unsigned long value;
	while (fscanf(fin, "%lu%lu", &id, &value) != EOF) {
		if (value_to_count.find(value) == value_to_count.end()) {
			value_to_count[value] = 1;
		} else {
			++value_to_count[value];
		}
	}

	// Write to file
	puts("Writing...");
	for (auto el : value_to_count) {
		fprintf(fout, "%lu %lu\n", el.first, el.second);
	}
}

int main(int argc, char *argv[])
{
	char *filename = nullptr;

	if (argc > 1) {
		filename = argv[1];
	} else {
		puts("Usage: ./reverse <data>");
		exit(1);
	}

	reverse(filename);
	return 0;
}
