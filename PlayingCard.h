#ifndef PLAYINGCARD_H
#define PLAYINGCARD_H

#include "LLC.h"
#include <iostream>

using namespace std;

class PlayingCard {
	public:
		enum vals {TWO, THR, FOU, FIV, SIX, SEV, EIG, NIN, TEN, JAC, KIN, QUE, ACE};
		enum suits {CLUB, HEART, SPADE, DIAMOND};
		PlayingCard();
		static LLC<PlayingCard> makedeck();
		bool operator==(PlayingCard card);
		bool operator<(PlayingCard card);
		bool operator>(PlayingCard card);
		friend ostream& operator<<(ostream &os, const PlayingCard &obj);
	private:
		PlayingCard(vals val, suits suit);
		vals _val;
		suits _suit;
};
#endif
