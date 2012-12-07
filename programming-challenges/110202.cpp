#include "entry_points.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace std;

class Resolver110202 {
private:
	static const int CardCount = 5;
	typedef pair<int, char> Poker;
    int pokerComparer(const pair<int, char> & p1, const pair<int, char> & p2) {
        return p1.first - p2.first;
    }
	enum PokerHandType {
		HighCard, Pair, TwoPair, ThreeOfAKing, Straight,
		Flush, FullHouse, FourOfAKing, StraightFlush
	};
private:
	Poker pokerHands[CardCount];
public:
	void LoadFromStream(istream stream);
	friend const int CompareTo(const Resolver110202 & a, const Resolver110202 & b);
private:
	PokerHandType GetPokerHandType(void) const;
	friend const int HighCardCompareTo(const Resolver110202 & a, const Resolver110202 & b);
	friend const int PairCompareTo(const Resolver110202 & a, const Resolver110202 & b);
    friend const int TwoPairCompareTo(const Resolver110202 & a, const Resolver110202 & b);
    friend const int ThreeOfAKingCompareTo(const Resolver110202 & a, const Resolver110202 & b);
    friend const int StraightCompareTo(const Resolver110202 & a, const Resolver110202 & b);
    friend const int FlushCompareTo(const Resolver110202 & a, const Resolver110202 & b);
    friend const int FullHouseCompareTo(const Resolver110202 & a, const Resolver110202 & b);
    friend const int FourOfAKingCompareTo(const Resolver110202 & a, const Resolver110202 & b);
    friend const int StraightFlushCompareTo(const Resolver110202 & a, const Resolver110202 & b);
};

void Resolver110202::LoadFromStream(istream stream) {
	for(int i = 0; i < CardCount; i++) {
		int value;
		char suit;
		stream >> value >> suit;
		stream.ignore(1);
        pokerHands[i] = make_pair(value, suit);
	}
    sort(&pokerHands[0], &pokerHands[CardCount], &Resolver110202::pokerComparer);
}

const int CompareTo(const Resolver110202 & a, const Resolver110202 & b) {
	Resolver110202::PokerHandType aType = a.GetPokerHandType();
	Resolver110202::PokerHandType bType = b.GetPokerHandType();

	if(aType == bType) {
		switch(aType) {
		case Resolver110202::HighCard: return HighCardCompareTo(a, b);
		case Resolver110202::Pair: return PairCompareTo(a, b);
        case Resolver110202::TwoPair: return TwoPairCompareTo(a, b);
        case Resolver110202::ThreeOfAKing: return ThreeOfAKingCompareTo(a, b);
        case Resolver110202::Straight: return StraightCompareTo(a, b);
		case Resolver110202::Flush: return FlushCompareTo(a, b);
        case Resolver110202::FullHouse: return FullHouseCompareTo(a, b);
        case Resolver110202::FourOfAKing: return FourOfAKingCompareTo(a, b);
        case Resolver110202::StraightFlush: return StraightFlushCompareTo(a, b);
		default: throw new out_of_range("Impossible hand card type.");
		}
	} else {
		return aType - bType;
	}
}

Resolver110202::PokerHandType Resolver110202::GetPokerHandType(void) const {
    return 0;
}
const int HighCardCompareTo(const Resolver110202 & a, const Resolver110202 & b);
const int PairCompareTo(const Resolver110202 & a, const Resolver110202 & b);
const int TwoPairCompareTo(const Resolver110202 & a, const Resolver110202 & b);
const int ThreeOfAKingCompareTo(const Resolver110202 & a, const Resolver110202 & b);
const int StraightCompareTo(const Resolver110202 & a, const Resolver110202 & b);
const int FlushCompareTo(const Resolver110202 & a, const Resolver110202 & b);
const int FullHouseCompareTo(const Resolver110202 & a, const Resolver110202 & b);
const int FourOfAKingCompareTo(const Resolver110202 & a, const Resolver110202 & b);
const int StraightFlushCompareTo(const Resolver110202 & a, const Resolver110202 & b);

int entry110202(void) {
	return 0;
}