// http://blog.csdn.net/metaphysis/article/details/6432062
// Wrong for following data:
//
// 5
// 0.01
// 0.19
// 0.20
// 0.21
// 0.22
// 0.23
//
// Should be 0.15, but run result is 0.14.
// 0.01 -> 0.16, 0.19 -> 0.16, others -> 0.17

// The Trip （旅行）
// PC/UVa IDs: 110103/10137, Popularity: B, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-04-09
// UVa Run Time: 0.016s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 首先计算“平均费用”，即总费用除以学生人数得到的数值，由于是要求支付差距在 1 分钱以内，故可
// 以考虑在计算时取小数点后两位，对于第三位以后的数采用四舍五入的方法，如计算平均值为 9.666
// 666，则取 9.67。那么首先读取正整数n，然后顺序读取n个数值。将所有费用相加，得到平均值。根据题
// 目的要求是“多退少补”，那么可以把学生分成两组，一组是垫付的费用大于平均费用的，一组则是小于等于
// 平均费用的。垫付多的学生应该退还钱款，垫付少的应收取费用。根据题意，需要取最少的那部分。在此，
// 需要注意的是这样的数据：0.01，0.01，0.01，0.01，0.01，0.01，0.01，0.01，0.01，0.01，
// 0.01，0.01，0.01，0.01，0.03， 此组数据的平均值为 0.01，但是并不是退还花费了 0.03 美元的
// 那个人 0.02 美元，因为只要满足误差在 1 美分内，所以只需退还花费 0.03 美元的那个人 0.01 美元
// 即可满足所有人花费误差在1美分之内，这个细节可能是大多数人在提交该问题答案所没有注意到的。
//
// 需要注意数据类型的使用，在此题目中，因为每个学生的支出不超过 $100000，如果用单精度浮点数表示，
// 则根据单精度数的定义，能保留 7 位有效数据，但是当学生的总费用超过 $100000.00 以后，则势必出
// 现精度丢失的情况，故需要使用双精度数据，否则结果会不正确。

#include <iostream>

using namespace std;

#define SIZE 1000

double findChange(double *money, int total)
{
	double average = 0.0, changeDown = 0.0, changeUp = 0.0, change = 0.0;

	for (int i = 0; i < total; i++)
		average += money[i];

	average /= total;
	average = (long) (average * 100 + 0.5) / 100.00;

	for (int i = 0; i < total; i++)
	{
		if (money[i] > average)
			changeUp += (money[i] - average);
		else
			changeDown += (average - money[i]);
	}

	if (changeDown > 0 && changeUp > 0)
	{
		if (changeDown > changeUp)
			change = changeUp;
		else
			change = changeDown;
	}
	else
	{
		if (changeUp == 0 && changeDown == 0)
			change = 0.0;
		else
		{
			if (changeDown == 0)
			{
				for (int i = 0; i < total; i++)
					if (money[i] > average)
						change +=
							(money[i] - average -
							0.01);
			}
			else
			{
				for (int i = 0; i < total; i++)
					if (money[i] < average)
						change +=
							(average - money[i] -
							0.01);
			}
		}
	}

	return change;
}

int metaphysis110103(void)
{
	double money[SIZE], result = 0.0;
	int total;

	while (cin >> total, total)
	{
		for (int i = 0; i < total; i++)
			cin >> money[i];

		result = findChange(money, total);

		cout.precision(2);
		cout.setf(ios::fixed | ios::showpoint);
		cout << "$" << result << endl;
	}

	return 0;
}