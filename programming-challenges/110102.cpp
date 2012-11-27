#include "entry_points.h"
#include <cstdio>
#include <stdexcept>

using namespace std;

class Resolver110102 {
private:
	static const int MINE_FLAG = -1;
	static const int EMPTY_FLAG = 0;
	static const int MINE_SYMBOL = '*';
	static const int EMPTY_SYMBOL = '.';

public:
	void parse(FILE * input);
	void calculateLabel(void);
	void toLabelMatrix(FILE * output) const;

private:
	const int ROW;
	const int COL;
	int ** mineArray;
	int ** labelArray;
	int ** new_two_dimension_array(int row, int col) const {
		int ** result = new int * [row];
		for(int i = 0; i < row; i++) {
			result[i] = new int[col];
		}
		return result;
	}
	void delete_two_dimension_array(int ** arr, int row) {
		for(int i = 0; i < row; i++) {
			delete[] arr[i];
		}
		delete[] arr;
	}
public:
	Resolver110102(int row, int col) : ROW(row), COL(col) {
		mineArray = new_two_dimension_array(row, col);
		labelArray = new_two_dimension_array(row, col);
	}
	~Resolver110102() {
		delete_two_dimension_array(mineArray, ROW);
		delete_two_dimension_array(labelArray, ROW);
	}

private:
	int sum3x3(int ** arr, int row, int col) const;
};

void Resolver110102::parse(FILE * input)
{
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COL; j++) {
			int ch = fgetc(input);
			switch(ch) {
			case MINE_SYMBOL: mineArray[i][j] = MINE_FLAG; break;
			case EMPTY_SYMBOL: mineArray[i][j] = EMPTY_FLAG; break;
			default: throw new logic_error("Invalid input file");
			}
		}
		fgetc(input); // Eat newline symbol.
	}
}

void Resolver110102::calculateLabel(void)
{
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COL; j++) {
			if(mineArray[i][j] == MINE_FLAG) {
				labelArray[i][j] = MINE_FLAG;
			} else {
				labelArray[i][j] = sum3x3(mineArray, i, j);
			}
		}
	}
}

void Resolver110102::toLabelMatrix(FILE * output) const
{
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COL; j++) {
			int value = labelArray[i][j];
			if(value == MINE_FLAG) {
				fputc(MINE_SYMBOL, output);
			} else {
				fputc('0' + value, output);
			}
		}
		fputc('\n', output);
	}
}

int Resolver110102::sum3x3(int ** arr, int row, int col) const
{
	int sum = arr[row][col];

	if(row - 1 >= 0 && col - 1 >= 0) sum += arr[row - 1][col - 1];
	if(row - 1 >= 0) sum += arr[row - 1][col];
	if(col - 1 >= 0) sum += arr[row][col - 1];
	if(col + 1 < COL) sum += arr[row][col + 1];
	if(row + 1 < ROW) sum += arr[row + 1][col];
	if(row + 1 < ROW && col + 1 < COL) sum += arr[row + 1][col + 1];

	if(row - 1 >= 0 && col + 1 < COL) sum += arr[row - 1][col + 1];
	if(row + 1 < ROW && col - 1 >= 0) sum += arr[row + 1][col - 1];

	return -sum;
}

int entry110102(void)
{
	int rows, cols;
	int caseNumber = 1;
	while(scanf("%d%d", &rows, &cols) == 2) {
		if(rows == 0 && cols == 0) {
			break;
		} else {
			Resolver110102 resolver(rows, cols);
			fgetc(stdin); // Eat newline symbol.
			resolver.parse(stdin);
			resolver.calculateLabel();

			if(caseNumber > 1) {				
				printf("\n");
			}
			printf("Field #%d:\n", caseNumber);
			resolver.toLabelMatrix(stdout);

			caseNumber++;
		}
	}
	return 0;
}