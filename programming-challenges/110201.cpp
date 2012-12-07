#include "entry_points.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

class Resolver110201 {
private:
	static const int MaxN = 3000;
private:
	const int n;
	int sequence[MaxN];
	bool diffSpotted[MaxN];
public:
	Resolver110201(const int & n) : n(n) {
		fill(&sequence[0], &sequence[MaxN], 0);
		fill(&diffSpotted[0], &diffSpotted[MaxN], false);
	}
	void LoadFromStream(istream & stream) {
		for(int i = 0; i < n; i++) {
			stream >> sequence[i];
		}
	}
	bool JudgeJolly(void) {
		for(int i = 1; i < n; i++) {
			int diff = abs(sequence[i - 1] - sequence[i]);
			if(diff == 0 || diff > n - 1 || diffSpotted[diff]) {
				return false;
			} else {
				diffSpotted[diff] = true;
			}
		}

		for(int i = 1; i <= n - 1; i++) {
			if(!diffSpotted[i]) {
				return false;
			}
		}
		return true;
	}
};

int entry110201(void) {
	int n;
	while(cin >> n) {
		Resolver110201 resolver(n);
		resolver.LoadFromStream(cin);
		if(resolver.JudgeJolly()) {
			cout << "Jolly" << endl;
		} else {
			cout << "Not jolly" << endl;
		}
	}
	return 0;
}