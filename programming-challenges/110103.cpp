#include "entry_points.h"
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

class Resolver110103
{
public:
	void AddStudent(double amount);
	double OptimalExchangeMoney(void) const;
private:
	const int numberOfStudent;
	double * moneyArray;
	int currentArrayPos;
	double sumOfMoney;
public:
	Resolver110103(int numberOfStudent)
		: currentArrayPos(0), sumOfMoney(0), numberOfStudent(numberOfStudent) {
		moneyArray = new double[numberOfStudent];
	}
	~Resolver110103(void) {
		delete[] moneyArray;
	}
};

void Resolver110103::AddStudent(double amount) {
	moneyArray[currentArrayPos++] = amount;
	sumOfMoney += amount;
}

double Resolver110103::OptimalExchangeMoney(void) const {
	int numberOfHigherAverage = static_cast<int>(sumOfMoney * 100.0 + 0.5) % numberOfStudent;
	double average = sumOfMoney / static_cast<double>(currentArrayPos);
	average = floor(average * 100.0) / 100.0;

	double result = 0.0;
	if(numberOfHigherAverage && (numberOfHigherAverage * 2 < numberOfStudent)) {
		average += 0.01;
		for(int i = 0; i < numberOfStudent; i++) {
			const double & value = moneyArray[i];
			if(value > average) {
				result += value - average;
			}
		}
	} else {
		for(int i = 0; i < numberOfStudent; i++) {
			const double & value = moneyArray[i];
			if(value < average) {
				result += average - value;
			}
		}
	}
	return result;
}

int entry110103(void)
{
	int n;
	while(scanf("%d", &n) == 1 && n) {
		Resolver110103 resolver(n);
		for(int i = 0; i < n ; i++) {
			double money = 0;
			scanf("%lf", &money);
			resolver.AddStudent(money);
		}
		printf("$%.2lf\n", resolver.OptimalExchangeMoney());
	}
	return 0;
}