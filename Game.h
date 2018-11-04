#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <fstream>
#include "LLC.h"
#include "PlayingCard.h"

using namespace std;

class Game {
	public:
		Game(const string names[64], string fileName, int low, int high);
		LLC<PlayingCard> cards = PlayingCard::makedeck();
		string _winner = "";
		string _loser = "";
		int _battles = 0;
		int _round = 0;
		void playgame(string name1, string name2);
	private:
		Game(int low, int high);
		static ofstream _file;
		static const string* _names;
		static int _totalBattles;
		static int _mostBattles;
};
#endif
