#include "entry_points.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class LCDNumberBase {
public:
	static const int GetRows(const int & Size) { return Size * 2 + 3; }
	static const int GetCols(const int & Size) { return Size + 2; }
	static const char BlankChar = ' ';
	static const char HorizonalChar = '-';
	static const char VerticalChar = '|';

public:
	virtual const vector<string> ToStringVector(void) const = 0;
protected:
	void ToStringVectorAux(vector<string> & result,
		const string & header, const string & belt, const string & footer,
		const string & upper, const string lower) const;

protected:
	const int size;
	const int rows;
	const int cols;
protected:
	const string blankRow;
	const string dashedRow;
	const string leftVerticalRow;
	const string rightVerticalRow;
	const string bothVerticalRow;
protected:
	LCDNumberBase(const int & size) : size(size), 
		rows(LCDNumberBase::GetRows(size)), 
		cols(LCDNumberBase::GetCols(size)),
		blankRow(cols, BlankChar),
		dashedRow(BlankChar + string(cols - 2, HorizonalChar) + BlankChar),
		leftVerticalRow(VerticalChar + string(cols - 1, BlankChar)),
		rightVerticalRow(string(cols - 1, BlankChar) + VerticalChar),
		bothVerticalRow(VerticalChar + string(cols - 2, BlankChar) + VerticalChar)
	{ }
	virtual ~LCDNumberBase(void) { }
private:
	LCDNumberBase(const LCDNumberBase &);
	LCDNumberBase & operator = (const LCDNumberBase &);
};

void LCDNumberBase::ToStringVectorAux(vector<string> & result,
	const string & header, const string & belt, const string & footer,
	const string & upper, const string lower) const 
{
	result[0] = header;
	result[size + 1] = belt;
	result[rows - 1] = footer;
	for(int i = 0; i < size; i++) {
		result[i + 1] = upper;
		result[i + size + 2] = lower;
	}
}

class ZeroLCDNumber : public LCDNumberBase {
public:
	ZeroLCDNumber(const int & size) : LCDNumberBase(size) { }
	virtual const vector<string> ToStringVector(void) const {
		vector<string> result(rows);
		ToStringVectorAux(result,
			dashedRow, blankRow, dashedRow,
			bothVerticalRow, bothVerticalRow);
		return result;
	}
};

class OneLCDNumber : public LCDNumberBase {
public:
	OneLCDNumber(const int & size) : LCDNumberBase(size) { }
	virtual const vector<string> ToStringVector(void) const {
		vector<string> result(rows);
		ToStringVectorAux(result,
			blankRow, blankRow, blankRow,
			rightVerticalRow, rightVerticalRow);
		return result;
	}
};

class TwoLCDNumber : public LCDNumberBase {
public:
	TwoLCDNumber(const int & size) : LCDNumberBase(size) { }
	virtual const vector<string> ToStringVector(void) const {
		vector<string> result(rows);
		ToStringVectorAux(result,
			dashedRow, dashedRow, dashedRow,
			rightVerticalRow, leftVerticalRow);
		return result;
	}
};

class ThreeLCDNumber : public LCDNumberBase {
public:
	ThreeLCDNumber(const int & size) : LCDNumberBase(size) { }
	virtual const vector<string> ToStringVector(void) const {
		vector<string> result(rows);
		ToStringVectorAux(result,
			dashedRow, dashedRow, dashedRow,
			rightVerticalRow, rightVerticalRow);
		return result;
	}
};

class FourLCDNumber : public LCDNumberBase {
public:
	FourLCDNumber(const int & size) : LCDNumberBase(size) { }
	virtual const vector<string> ToStringVector(void) const {
		vector<string> result(rows);
		ToStringVectorAux(result,
			blankRow, dashedRow, blankRow,
			bothVerticalRow, rightVerticalRow);
		return result;
	}
};

class FiveLCDNumber : public LCDNumberBase {
public:
	FiveLCDNumber(const int & size) : LCDNumberBase(size) { }
	virtual const vector<string> ToStringVector(void) const {
		vector<string> result(rows);
		ToStringVectorAux(result,
			dashedRow, dashedRow, dashedRow,
			leftVerticalRow, rightVerticalRow);
		return result;
	}
};

class SixLCDNumber : public LCDNumberBase {
public:
	SixLCDNumber(const int & size) : LCDNumberBase(size) { }
	virtual const vector<string> ToStringVector(void) const {
		vector<string> result(rows);
		ToStringVectorAux(result,
			dashedRow, dashedRow, dashedRow,
			leftVerticalRow, bothVerticalRow);
		return result;
	}
};

class SevenLCDNumber : public LCDNumberBase {
public:
	SevenLCDNumber(const int & size) : LCDNumberBase(size) { }
	virtual const vector<string> ToStringVector(void) const {
		vector<string> result(rows);
		ToStringVectorAux(result,
			dashedRow, blankRow, blankRow,
			rightVerticalRow, rightVerticalRow);
		return result;
	}
};

class EightLCDNumber : public LCDNumberBase {
public:
	EightLCDNumber(const int & size) : LCDNumberBase(size) { }
	virtual const vector<string> ToStringVector(void) const {
		vector<string> result(rows);
		ToStringVectorAux(result,
			dashedRow, dashedRow, dashedRow,
			bothVerticalRow, bothVerticalRow);
		return result;
	}
};

class NineLCDNumber : public LCDNumberBase {
public:
	NineLCDNumber(const int & size) : LCDNumberBase(size) { }
	virtual const vector<string> ToStringVector(void) const {
		vector<string> result(rows);
		ToStringVectorAux(result,
			dashedRow, dashedRow, dashedRow,
			bothVerticalRow, rightVerticalRow);
		return result;
	}
};

class LCDNumberFactory {
private:
	const ZeroLCDNumber zero;
	const OneLCDNumber one;
	const TwoLCDNumber two;
	const ThreeLCDNumber three;
	const FourLCDNumber four;
	const FiveLCDNumber five;
	const SixLCDNumber six;
	const SevenLCDNumber seven;
	const EightLCDNumber eight;
	const NineLCDNumber nine;

public:
	LCDNumberFactory(const int & size);
	const LCDNumberBase & GetInstance(const char & number) const;
};

LCDNumberFactory::LCDNumberFactory(const int & size) : zero(size), one(size),
	two(size), three(size), four(size), five(size), six(size), seven(size),
	eight(size), nine(size)
{ }

const LCDNumberBase & LCDNumberFactory::GetInstance(const char & number) const {
	switch(number) {
	case '0': return zero;
	case '1': return one;
	case '2': return two;
	case '3': return three;
	case '4': return four;
	case '5': return five;
	case '6': return six;
	case '7': return seven;
	case '8': return eight;
	case '9': return nine;
	default: throw new invalid_argument("Number is invalid.");
	}
}

class Resolver110104 {
private:
	const int size;
	const int rows;
	const vector<string> blankColumn;
	LCDNumberFactory engineFactory;
public:
	Resolver110104(const int & size);
	const vector<string> DrawString(const string & numbers) const;

private:
	void MergeTwoStringVector(vector<string> & to, const vector<string> & from) const;
};

Resolver110104::Resolver110104(const int & size) : size(size),
	rows(LCDNumberBase::GetRows(size)), blankColumn(rows),
	engineFactory(size)
{
	vector<string> & mutableBlankColumn = const_cast<vector<string> &>(blankColumn);
	for(int i = 0; i < rows; i++) {
		mutableBlankColumn[i] = LCDNumberBase::BlankChar;
	}
}

const vector<string> Resolver110104::DrawString(const string & numbers) const {
	vector<string> result(engineFactory.GetInstance(numbers[0]).ToStringVector());

	for(size_t i = 1; i < numbers.length(); i++) {
		MergeTwoStringVector(result, engineFactory.GetInstance(numbers[i]).ToStringVector());
	}

	return result;
}

void Resolver110104::MergeTwoStringVector(vector<string> & to, 
										  const vector<string> & from) const {
	for(int i = 0; i < rows; i++) {
		to[i] += blankColumn[i] + from[i];
	}
}

int entry110104(void) {
	int size;
	string numbers;
	while(cin >> size >> numbers && size) {
		Resolver110104 resolver(size);
		const vector<string> & lines = resolver.DrawString(numbers);
		for(size_t i = 0; i < lines.size(); i++) {
			cout << lines[i] << endl;
		}
		cout << endl;
	}
	return 0;
}