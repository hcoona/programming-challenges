#include "entry_points.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

class Resolver110106 {
public:
	static const size_t RegisterCount = 10;
	static const size_t MemorySize = 1000;

private:
	unsigned registers[RegisterCount];
	unsigned memory[MemorySize];
	int executedInstructionCount;
public:
	Resolver110106(void) : executedInstructionCount(0) {
		fill(&registers[0], &registers[RegisterCount], 0);
		fill(&memory[0], &memory[MemorySize], 0);
	}

public:
	const int GetExecutedInstructionCount(void) const {
		return executedInstructionCount;
	}
	void LoadInstructions(const unsigned * begin, const unsigned * end) {
		copy(begin, end, &memory[0]);
	}
	void Execute(void);

private:
	void ParseInstructionCode(const unsigned & code,
		int & inst, int & p1, int & p2) {
		inst = (code / 100) % 10;
		p1 = (code / 10) % 10;
		p2 = code % 10;
	}
	void SetRegisterToInstantNumber(const int & registerId, const int & value) {
		registers[registerId] = value;
	}
	void AddRegisterWithInstantNumber(const int & registerId, const int & value) {
		registers[registerId] += value;
	}
	void MultiplyRegisterByInstantNumber(const int & registerId, const int & value) {
		registers[registerId] *= value;
	}
	void SetRegisterFromValueOfAnother(const int & toRegisterId, const int & fromRegisterId) {
		registers[toRegisterId] = registers[fromRegisterId];
	}
	void AddRegisterFromValueOfAnother(const int & toRegisterId, const int & fromRegisterId) {
		registers[toRegisterId] += registers[fromRegisterId];
	}
	void MultiplyRegisterByValueOfAnother(const int & toRegisterId, const int & byRegisterId) {
		registers[toRegisterId] *= registers[byRegisterId];
	}
	void SetRegisterFromValueOfAddressInRegister(const int & toRegisterId, const int & addressRegisterId) {
		const int & address = registers[addressRegisterId];
		registers[toRegisterId] = memory[address];
	}
	void SetValueOfAddressInRegisterToValueOfAddressInAnotherRegister(
		const int & toAddressRegisterId, const int & fromAddressRegisterId) {
		const int & toAddress = registers[toAddressRegisterId];
		const int & fromAddress = registers[fromAddressRegisterId];
		memory[toAddress] = memory[fromAddress];
	}

public:
	void PrintRegisters(void) {
		for(int i = 0; i < RegisterCount; i++) {
			cout << "Register " << i << ": " << registers[i] << endl;
		}
	}
	void PrintMemory(const int & maxAddress) {
		for(int i = 0; i < maxAddress; i++) {
			cout << "Memory " << i << ": " << memory[i] << endl;
		}
	}
};

void Resolver110106::Execute(void) {
	bool halt = false;
	for(int pc = 0; !halt && pc < MemorySize; pc++, executedInstructionCount++) {
		int inst, p1, p2;
		ParseInstructionCode(memory[pc], inst, p1, p2);
		switch(inst) {
		case 1: halt = true; break;
		case 2: SetRegisterToInstantNumber(p1, p2); break;
		case 3: AddRegisterWithInstantNumber(p1, p2); break;
		case 4: MultiplyRegisterByInstantNumber(p1, p2); break;
		case 5: SetRegisterFromValueOfAnother(p1, p2); break;
		case 6: AddRegisterFromValueOfAnother(p1, p2); break;
		case 7: MultiplyRegisterByValueOfAnother(p1, p2); break;
		case 8: SetRegisterFromValueOfAddressInRegister(p1, p2); break;
		case 9: SetValueOfAddressInRegisterToValueOfAddressInAnotherRegister(p1, p2); break;
		case 0: if(registers[p2] % 1000) { pc = registers[p1] - 1; continue; } else break;
		default: throw new invalid_argument("Invalid instruction");
		}
	}
}

#ifndef BUFSIZ
#define BUFSIZ 1024
#endif

int entry110106(void) {
	int n;
	cin >> n;

	char lineBuffer[BUFSIZ];
	cin.getline(lineBuffer, BUFSIZ);
	cin.getline(lineBuffer, BUFSIZ);

	stringstream stream;
	while(n--) {
		unsigned instructions[Resolver110106::MemorySize] = { 0 };
		int instIdx = 0;
		while(cin.getline(lineBuffer, BUFSIZ) && cin.gcount() > 1) {
			stream << lineBuffer;
			stream >> instructions[instIdx++];
		}

		Resolver110106 resolver;
		resolver.LoadInstructions(&instructions[0], &instructions[Resolver110106::MemorySize]);
		resolver.Execute();
		cout << resolver.GetExecutedInstructionCount() << endl;
		
		if(n) cout << endl;
	}

	return 0;
}