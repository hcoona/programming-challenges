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

// The Trip �����У�
// PC/UVa IDs: 110103/10137, Popularity: B, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-04-09
// UVa Run Time: 0.016s
//
// ��Ȩ���У�C��2011�����metaphysis # yeah dot net
//
// ���ȼ��㡰ƽ�����á������ܷ��ó���ѧ�������õ�����ֵ��������Ҫ��֧������� 1 ��Ǯ���ڣ��ʿ�
// �Կ����ڼ���ʱȡС�������λ�����ڵ���λ�Ժ����������������ķ����������ƽ��ֵΪ 9.666
// 666����ȡ 9.67����ô���ȶ�ȡ������n��Ȼ��˳���ȡn����ֵ�������з�����ӣ��õ�ƽ��ֵ��������
// Ŀ��Ҫ���ǡ������ٲ�������ô���԰�ѧ���ֳ����飬һ���ǵ渶�ķ��ô���ƽ�����õģ�һ������С�ڵ���
// ƽ�����õġ��渶���ѧ��Ӧ���˻�Ǯ��渶�ٵ�Ӧ��ȡ���á��������⣬��Ҫȡ���ٵ��ǲ��֡��ڴˣ�
// ��Ҫע��������������ݣ�0.01��0.01��0.01��0.01��0.01��0.01��0.01��0.01��0.01��0.01��
// 0.01��0.01��0.01��0.01��0.03�� �������ݵ�ƽ��ֵΪ 0.01�����ǲ������˻������� 0.03 ��Ԫ��
// �Ǹ��� 0.02 ��Ԫ����ΪֻҪ��������� 1 �����ڣ�����ֻ���˻����� 0.03 ��Ԫ���Ǹ��� 0.01 ��Ԫ
// �������������˻��������1����֮�ڣ����ϸ�ڿ����Ǵ���������ύ���������û��ע�⵽�ġ�
//
// ��Ҫע���������͵�ʹ�ã��ڴ���Ŀ�У���Ϊÿ��ѧ����֧�������� $100000������õ����ȸ�������ʾ��
// ����ݵ��������Ķ��壬�ܱ��� 7 λ��Ч���ݣ����ǵ�ѧ�����ܷ��ó��� $100000.00 �Ժ����Ʊس�
// �־��ȶ�ʧ�����������Ҫʹ��˫�������ݣ��������᲻��ȷ��

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