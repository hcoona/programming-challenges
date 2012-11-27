#include "entry_points.h"
#include <algorithm>
#include <cstdio>
#include <map>
#include <stdexcept>

using namespace std;

typedef long long TYPE110101;
class Resolver110101
{
public:
	int get_max_cycle_length(const pair<int, int> & range);
	int get_max_cycle_length(const int from, const int to);
	
private:
	static const int MAX_ENTRY = 1000000;
	static const int INVALID_VALUE = 0;

private:
	int * entry_table;
	void fill_entry_table(const int from, const int to);
public:
	Resolver110101() { 
		entry_table = new int[MAX_ENTRY + 1];
		fill(entry_table, &entry_table[MAX_ENTRY + 1], INVALID_VALUE);
	}
	~Resolver110101() { delete[] entry_table; }
private:
	int calculate_cycle_length(TYPE110101 n, int * const table, map<TYPE110101, int> & out_of_range_mapper);
	int find_in_table_and_mapper(TYPE110101 n, int * const table, map<TYPE110101, int> & out_of_range_mapper);
	void update_table_and_mapper(TYPE110101 n, int cycle_length,
		int * const table, map<TYPE110101, int> & out_of_range_mapper);
};

int Resolver110101::get_max_cycle_length(const pair<int, int> & range)
{
	int from = min(range.first, range.second);
	int to = max(range.first, range.second);
	return get_max_cycle_length(from, to);
}

int Resolver110101::get_max_cycle_length(const int from, const int to)
{
	if(from > to) {
		throw new invalid_argument("from must be less or equal than to");
	} else {
		fill_entry_table(from, to);
		return *max_element(&entry_table[from], &entry_table[to + 1]);
	}
}

void Resolver110101::fill_entry_table(const int from, const int to)
{
	map<TYPE110101, int> out_of_range_mapper;

	for(int i = from; i <= to; i++) {
		if(entry_table[i] == INVALID_VALUE) {
			entry_table[i] = calculate_cycle_length(i, entry_table, out_of_range_mapper);
		}
	}
}

int Resolver110101::calculate_cycle_length(
	TYPE110101 n, int * const table, map<TYPE110101, int> & out_of_range_mapper)
{
	if(n < 1) return 0;
	if(n == 1) return 1;

	int cycle_length = find_in_table_and_mapper(n, table, out_of_range_mapper);
	if(cycle_length != INVALID_VALUE) return cycle_length;

	if(n & 1) {
		TYPE110101 new_n = n * 3 + 1;
		if(new_n < n) {
			throw new overflow_error("Overflow when make a new n");
		}
		cycle_length = calculate_cycle_length(new_n, table, out_of_range_mapper) + 1;
	} else {
		cycle_length = calculate_cycle_length(n / 2, table, out_of_range_mapper) + 1;
	}

	update_table_and_mapper(n, cycle_length, table, out_of_range_mapper);

	return cycle_length;
}

int Resolver110101::find_in_table_and_mapper(TYPE110101 n,
	int * const table, map<TYPE110101, int> & out_of_range_mapper)
{
	if(n <= MAX_ENTRY) {
		return table[n];
	} else {
		return out_of_range_mapper[n];
	}
}

void Resolver110101::update_table_and_mapper(TYPE110101 n, int cycle_length,
	int * const table, map<TYPE110101, int> & out_of_range_mapper)
{	
	if(n <= MAX_ENTRY) {
		table[n] = cycle_length;
	} else {
		out_of_range_mapper[n] = cycle_length;
	}
}

int entry110101(void)
{
	Resolver110101 resolver;

	int from, to;
	while(scanf("%d%d", &from, &to) == 2) {
		printf("%d %d %d\n", from, to, 
			resolver.get_max_cycle_length(make_pair(from, to)));
	}

	return 0;
}