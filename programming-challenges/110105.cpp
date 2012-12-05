#include "entry_points.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

class Position : public pair<int, int> {
public:
	Position(const int & row, const int & col) : pair<int, int>(row, col) { }
	friend Position operator+(const Position & Left,const Position & Right) {
		return Position(Left.first + Right.first, Left.second + Right.second);
	}
};

class Resolver10105 {
private:
	static const int MaxRows = 250;
	static const int MaxCols = 250;
	static const char WhiteColor = '0';
private:
	const int rows, cols;
	char image[MaxRows][MaxCols];
public:
	Resolver10105(void) : rows(0), cols(0) {
		Clear();
	}
	void Initialize(const int & rows, const int & cols) {
		const_cast<int &>(this->rows) = rows;
		const_cast<int &>(this->cols) = cols;
		Clear();
	}
	void Clear(void) { fill(&image[0][0], &image[MaxRows - 1][MaxCols - 1], WhiteColor); }
	void Let(const int & x, const int & y, const char & color) { image[y - 1][x - 1] = color; }
	void VerticalSegment(const int & x, const int & y1, const int &y2, const char & color);
	void HorizontalSegment(const int & x1, const int & x2, const int y, const char & color);
	void Rectangle(const int & x1, const int & x2,
		const int & y1, const int &y2, const char & color);
	void FillRegion(const int & x, const int & y, const char & color);
	const string Save(const string & name) const;
private:
	bool IsValidPosition(const Position & position) const;
	char & Pixel(const Position & position);
	const char & Pixel(const Position & position) const;
};

void Resolver10105::VerticalSegment(const int & x, 
	const int & y1, const int &y2, const char & color) {
	const int RowFrom = min(y1, y2) - 1, RowTo = max(y1, y2) - 1;
	const int Col = x - 1;

	for(int row = RowFrom; row <= RowTo; row++) {
		image[row][Col] = color;
	}
}

void Resolver10105::HorizontalSegment(const int & x1, const int & x2,
									  const int y, const char & color) {
	const int ColFrom = min(x1, x2) - 1, ColTo = max(x1, x2) - 1;
	const int Row = y - 1;

	for(int col = ColFrom; col <= ColTo; col++) {
		image[Row][col] = color;
	}
}

void Resolver10105::Rectangle(const int & x1, const int & x2,
							  const int & y1, const int &y2,
							  const char & color) {
	const int RowFrom = min(y1, y2) - 1, RowTo = max(y1, y2) - 1;
	const int ColFrom = min(x1, x2) - 1, ColTo = max(x1, x2) - 1;

	for(int row = RowFrom; row <= RowTo; row++) {
		for(int col = ColFrom; col <= ColTo; col++) {
			image[row][col] = color;
		}
	}
}

void Resolver10105::FillRegion(const int & x, const int & y, const char & color) {
	const int Row = y - 1, Col = x - 1;
	const char SeedColor = image[Row][Col];
	
	const int NeighborCount = 4;
	const Position DeltaNeighbors[NeighborCount] = {
		Position(-1, 0), Position(1, 0), Position(0, -1), Position(0, 1)
	};
	const char MarkerColor = -1;

	queue<const Position> fillQueue;
	fillQueue.push(Position(Row, Col));

	while(!fillQueue.empty()) {
		const Position & p = fillQueue.front();
		if(Pixel(p) != MarkerColor) {
			Pixel(p) = MarkerColor;
			for(int i = 0; i < NeighborCount; i++) {
				const Position & neighbor = p + DeltaNeighbors[i];
				if(IsValidPosition(neighbor) && Pixel(neighbor) == SeedColor) {
					fillQueue.push(neighbor);
				}
			}
		}
		fillQueue.pop();
	}

	for(int row = 0; row <= rows; row++) {
		for(int col = 0; col <= cols; col++) {
			if(image[row][col] == MarkerColor) {
				image[row][col] = color;
			}
		}
	}
}

const string Resolver10105::Save(const string & name) const {
	ostringstream stream;
	stream << name << endl;
	for(int row = 0; row <= rows; row++) {
		for(int col = 0; col <= cols; col++) {
			stream << image[row][col];
		}
		stream << endl;
	}
	return stream.str();
}

bool Resolver10105::IsValidPosition(const Position & position) const {
	return position.first >= 0 && position.first <= rows
		&& position.second >= 0 && position.second <= cols;
}

char & Resolver10105::Pixel(const Position & position) {
	return image[position.first][position.second];
}

const char & Resolver10105::Pixel(const Position & position) const {
	return image[position.first][position.second];
}

class Interpreter110105 {
private:
	Resolver10105 resolver;
public:
	void Parse(const string & line) {
		istringstream stream(line);
		char cmd;
		stream >> cmd;
		switch(cmd) {
		case 'I': {
			int rows, cols;
			stream >> cols >> rows;
			resolver.Initialize(rows, cols);
			break;
		}
		case 'C': resolver.Clear(); break;
		case 'L': {
			int x, y;
			char c;
			stream >> x >> y >> c;
			resolver.Let(x, y, c);
			break;
		}
		case 'V': {
			int x, y1, y2;
			char c;
			stream >> x >> y1 >> y2 >> c;
			resolver.VerticalSegment(x, y1, y2, c);
			break;
		}
		case 'H': {
			int x1, x2, y;
			char c;
			stream >> x1 >> x2 >> y >> c;
			resolver.HorizontalSegment(x1, x2, y, c);
			break;
		}
		case 'K': {
			int x1, x2, y1, y2;
			char c;
			stream >> x1 >> x2 >> y1 >> y2 >> c;
			resolver.Rectangle(x1, x2, y1, y2, c);
			break;
		}
		case 'F': {
			int x, y;
			char c;
			stream >> x >> y >> c;
			resolver.FillRegion(x, y, c);
			break;
		}
		case 'S': {
			string name;
			stream >> name;
			cout << resolver.Save(name);
			break;
		}
		default: break;
		}
	}
};

#ifndef BUFSIZ
#define BUFSIZ 1024
#endif

int entry110105(void) {
	Interpreter110105 interpreter;
	char lineBuffer[BUFSIZ];
    while(true) {
		cin.getline(lineBuffer, BUFSIZ);
		if(lineBuffer[0] == 'X') break;

		interpreter.Parse(lineBuffer);
	}
	return 0;
}