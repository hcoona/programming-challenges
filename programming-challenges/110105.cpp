#include "entry_points.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

class Resolver10105 {
private:
	static const int WhiteColor = '0';
	static const int InvalidColor = -1;
	typedef const pair<int, int> Point;
private:
	int rows, cols;
	int ** image;
public:
	Resolver10105(void) : rows(0), cols(0), image(0) { }
	~Resolver10105(void) { Delete(); }
	void Eval(const char & cmd, const string & parameters);
private:
	void Create(const int & rows, const int & cols);
	void Delete(void);
	void Clear(void);
	void Let(const int & x, const int & y, const char & color);
	void VerticalSegment(const int & x, const int & y1, const int &y2, const char & color);
	void HorizontalSegment(const int & x1, const int & x2, const int y, const char & color);
	void Rectangle(const int & x1, const int & x2,
		const int & y1, const int &y2, const char & color);
	void FillRegion(const int & x, const int & y, const char & color);
	const string Save(const string & name) const;
private:
	bool IsPointValid(Point & point) const;
};

void Resolver10105::Eval(const char & cmd, const string & parameters) {
	stringstream stream(parameters);
	switch(cmd) {
	case 'I': {
		int rows, cols;
		stream >> cols >> rows;
		Create(rows, cols);
		break;
	}
	case 'C': Clear(); break;
	case 'L': {
		int x, y;
		char c;
		stream >> x >> y >> c;
		Let(x, y, c);
		break;
	}
	case 'V': {
		int x, y1, y2;
		char c;
		stream >> x >> y1 >> y2 >> c;
		VerticalSegment(x, y1, y2, c);
		break;
	}
	case 'H': {
		int x1, x2, y;
		char c;
		stream >> x1 >> x2 >> y >> c;
		HorizontalSegment(x1, x2, y, c);
		break;
	}
	case 'K': {
		int x1, x2, y1, y2;
		char c;
		stream >> x1 >> x2 >> y1 >> y2 >> c;
		Rectangle(x1, x2, y1, y2, c);
		break;
	}
	case 'F': {
		int x, y;
		char c;
		stream >> x >> y >> c;
		FillRegion(x, y, c);
		break;
	}
	case 'S': {
		string name;
		stream >> name;
		cout << Save(name);
		break;
	}
	default: break;
	}
}

void Resolver10105::Create(const int & rows, const int & cols) {
	Delete();
	this->rows = rows;
	this->cols = cols;
	image = new int * [rows];
	for(int i = 0; i < rows; i++) {
		image[i] = new int[cols];
	}
	Clear();
}

void Resolver10105::Delete(void) {
	if(image) {
		for(int i = 0; i < rows; i++) {
			delete[] image[i];
		}
		delete[] image;
		rows = cols = 0;
		image = 0;
	}
}

void Resolver10105::Clear(void) {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			image[i][j] = WhiteColor;
		}
	}
}

void Resolver10105::Let(const int & x, const int & y, const char & color) {
	image[x][y] = color;
}

void Resolver10105::VerticalSegment(
	const int & x, const int & y1, const int &y2, const char & color) {
	int yy1 = min(y1, y2), yy2 = max(y1, y2);
	for(int j = yy1; j <= yy2; j++) {
		image[x][j] = color;
	}
}

void Resolver10105::HorizontalSegment(
	const int & x1, const int & x2, const int y, const char & color) {
	int xx1 = min(x1, x2), xx2 = max(x1, x2);
	for(int i = xx1; i <= xx2; i++) {
		image[i][y] = color;
	}
}

void Resolver10105::Rectangle(const int & x1, const int & x2,
	const int & y1, const int &y2, const char & color) {
	int xx1 = min(x1, x2), xx2 = max(x1, x2);
	int yy1 = min(y1, y2), yy2 = max(y1, y2);
	for(int i = xx1; i <= xx2; i++) {
		for(int j = yy1; j <= yy2; j++) {
			image[i][j] = color;
		}
	}
}

void Resolver10105::FillRegion(const int & x, const int & y, const char & color) {
	const int MarkerColor = InvalidColor;
	const int SeedColor = image[x][y];

	queue<Point> fillQueue;
	fillQueue.push(make_pair(x, y));

	while(!fillQueue.empty()) {
		Point & currentPoint = fillQueue.front();
		image[currentPoint.first][currentPoint.second] = MarkerColor;
		fillQueue.pop();

		const int NeighborPointsCount = 4;
		Point neighborPoints[NeighborPointsCount] = {
			make_pair(currentPoint.first - 1, currentPoint.second),
			make_pair(currentPoint.first, currentPoint.second - 1),
			make_pair(currentPoint.first + 1, currentPoint.second),
			make_pair(currentPoint.first, currentPoint.second + 1),
		};
		for(int i = 0; i < NeighborPointsCount; i++) {
			Point & p = neighborPoints[i];
			if(IsPointValid(p) && image[p.first][p.second] == SeedColor) {
				fillQueue.push(p);
			}
		}
	}
	
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(image[i][j] == MarkerColor)
				image[i][j] = color;
		}
	}
}

bool Resolver10105::IsPointValid(Point & point) const {
	const int & x = point.first;
	const int & y = point.second;
	return x >= 0 && x <= cols
		&& y >= 0 && y <= rows;
}

const string Resolver10105::Save(const string & name) const {
	ostringstream out;
	out << name << endl;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			out << static_cast<char>(image[i][j]);
		}
		out << endl;
	}
	return out.str();
}

int entry110105(void) {
	Resolver10105 resolver;
	const int BUFF_SIZE = 1024;
	char buffer[BUFF_SIZE];
	char cmd;
	while(cin >> cmd && cmd != 'X') {
		cin.getline(buffer, BUFF_SIZE);
		resolver.Eval(cmd, buffer);
	}
	return 0;
}