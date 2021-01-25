#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <regex>

using namespace std;

char line[1024];
int main() {

	FILE *fin = fopen("input.txt", "r");
	if (!fin) {
		fprintf(stderr, "Can't open input file\n");
		return 1;
	}


	int start;
	fgets(line, sizeof(line), fin);

	char *endptr;
	start = strtol(line, &endptr, 10);

	fgets(line, sizeof(line), fin);

	fclose(fin);

	regex sep(",|\\s");

	regex_token_iterator<string::iterator> rend;

	vector<int> values;

	string s(line);

	int v;
	for (regex_token_iterator<string::iterator> d(s.begin(), s.end(), sep, -1); d != rend; d++) {
		if (d->str()[0] != 'x') {
			v = strtol(d->str().c_str(), &endptr, 10);
			values.push_back(v);
		}
	}

	vector<int> limits;
	limits.resize(values.size());

	for (int i = 0; i < limits.size(); i++) {
		limits[i] = (start / values[i])*values[i];
		if (limits[i] < start)
			limits[i] += values[i];
	}

	int minind = 0;
	for (int i = 1; i < limits.size(); i++) {
		if (limits[i] < limits[minind])
			minind = i;
	}

	int diff = limits[minind] - start;
	int ans = diff*values[minind];

	printf("%d\n", ans);

	return 0;
}