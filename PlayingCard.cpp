#include "PlayingCard.h"

enum vals {TWO, THR, FOU, FIV, SIX, SEV, EIG, NIN, TEN, JAC, KIN, QUE, ACE};
enum suits {CLUB, HEART, SPADE, DIAMOND};

PlayingCard :: PlayingCard() {};

PlayingCard :: PlayingCard(vals val, suits suit) {
	this->_suit = suit;
	this->_val = val;
}

LLC<PlayingCard> PlayingCard :: makedeck() {
	LLC<PlayingCard> temp = LLC<PlayingCard>();
	for (int i = 0; i < 13; i++) {
		vals val = static_cast<vals>(i);
		for (int j = 0; j < 4; j++) {
			suits suit = static_cast<suits>(j);
			PlayingCard card = PlayingCard(val, suit);
			temp.insert(card);
		}
	}
	return temp;
}

bool PlayingCard :: operator<(PlayingCard card) {
	return this->_val < card._val;
}

bool PlayingCard :: operator>(PlayingCard card) {
	return this->_val > card._val;
}

bool PlayingCard :: operator==(PlayingCard card) {
	return card._val == this->_val and card._suit == this->_suit;
}

ostream& operator<<(ostream &os, const PlayingCard &obj) {
	switch(obj._val) {
		case TWO:
			os << "2";
			break;
		case THR:
			os << "3";
			break;
		case FOU:
			os << "4";
			break;
		case FIV:
			os << "5";
			break;
		case SIX:
			os << "6";
			break;
		case SEV:
			os << "7";
			break;
		case EIG:
			os << "8";
			break;
		case NIN:
			os << "9";
			break;
		case TEN:
			os << "T";
			break;
		case JAC:
			os << "J";
			break;
		case QUE:
			os << "Q";
			break;
		case KIN:
			os << "K";
			break;
		case ACE:
			os << "A";
			break;
	}
	switch(obj._suit) {
		case CLUB:
			os << "C";
			break;
		case HEART:
			os << "H";
			break;
		case SPADE:
			os << "S";
			break;
		case DIAMOND:
			os << "D";
			break;
	}
	return os;
}
