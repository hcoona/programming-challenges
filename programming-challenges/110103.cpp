#include "entry_points.h"
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

class Resolver110103
{
public:
	void AddStudent(double amount);
	double OptimalExchangeMoney(void);
private:
	const int numberOfStudent;
	int * moneyArray;
	int currentArrayPos;
	int sumOfMoney;
public:
	Resolver110103(int numberOfStudent)
		: currentArrayPos(0), sumOfMoney(0), numberOfStudent(numberOfStudent) {
		moneyArray = new int[numberOfStudent];
	}
	~Resolver110103(void) {
		delete[] moneyArray;
	}
private:
	int RoundDecimal(const double &value) const {
		return static_cast<int>(value + 0.5);
	}
	int OneHundredLargerRound(const double &value) const {
		return RoundDecimal(value * 100.0);
	}
};

void Resolver110103::AddStudent(double amount) {
	int scaledMoney = OneHundredLargerRound(amount);
	moneyArray[currentArrayPos++] = scaledMoney;
	sumOfMoney += scaledMoney;
}

double Resolver110103::OptimalExchangeMoney(void) {
	int numberOfStudentAdjustToCeilingAverage = sumOfMoney % numberOfStudent;
	if(numberOfStudentAdjustToCeilingAverage) {
		int numberOfStudentAdjustToFlooringAverage = 
			numberOfStudent - numberOfStudentAdjustToCeilingAverage;
		int flooringAverage = RoundDecimal(
			floor(static_cast<double>(sumOfMoney) 
				/ static_cast<double>(numberOfStudent)));
	
		sort(moneyArray, &moneyArray[numberOfStudent]);
		int adjust = 0;
		for(int i = 0; i < numberOfStudentAdjustToFlooringAverage; i++) {
			adjust += labs(flooringAverage - moneyArray[i]);
		}
		int ceilingAverage = flooringAverage + 1;
		for(int i = numberOfStudentAdjustToFlooringAverage; i < numberOfStudent; i++) {
			adjust += labs(moneyArray[i] - ceilingAverage);
		}
		return static_cast<double>(adjust) / 2.0 / 100.0;
	} else {
		int average = sumOfMoney / numberOfStudent;
		int adjust = 0;
		for(int i = 0; i < numberOfStudent; i++) {
			const int & value = moneyArray[i];
			if(value < average) {
				adjust += average - value;
			}
		}
		return static_cast<double>(adjust) / 100.0;
	}
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