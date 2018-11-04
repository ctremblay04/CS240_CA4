#include "Game.h"

ofstream Game :: _file;
const string* Game :: _names;
int Game :: _totalBattles = 0;
int Game :: _mostBattles = 0;
Game :: Game(const string names[64], string fileName, int low, int high) {
	_file.open(fileName);
	_names = names;
	string name1;
	string name2;
	int temp = high-low+1;
	while (temp >>= 1) {this->_round++;}
	if (high-low == 1) {
		name1 = _names[low];
		name2 = _names[high];
	}
	else {
		name1 = Game(low, low+(high-low)/2)._winner;
		name2 = Game(low+(high-low)/2+1, high)._winner;
	}
	this->playgame(name1, name2);
	cout << "Tournament Winner: " << this->_winner << endl;
	cout << "Average number of battles per matchup: " << int(this->_totalBattles/(high-low)) << endl;
	cout << "Largest number of battles in one matchup: " << this->_mostBattles << endl;
	_file.close();
}

Game :: Game(int low, int high) {
	string name1;
	string name2;
	int temp = high-low+1;
	while (temp >>= 1) {this->_round++;}
	if (high-low == 1) {
		name1 = _names[low];
		name2 = _names[high];
	}
	else {
		name1 = Game(low, low+(high-low)/2)._winner;
		name2 = Game(low+(high-low)/2+1, high)._winner;
	}
	this->playgame(name1, name2);
}

void Game :: playgame(string name1, string name2) {
	_file << "===\n" << name1 << " VS. " << name2 << endl;
	int numBattles = 0;
	int numWars = 0;
	bool war = false;
	LLC<PlayingCard> p1 = PlayingCard::makedeck();
	p1.shuffle();
	LLC<PlayingCard> p2 = p1.pop(26);
	p1.shuffle();
	p2.shuffle();
	LLC<PlayingCard> pot = LLC<PlayingCard>();
	while (numBattles+numWars < 1000) {
		LLC<PlayingCard> t1 = p1.pop();
		LLC<PlayingCard> t2 = p2.pop();
		PlayingCard c1 = t1._head->next->data;
		PlayingCard c2 = t2._head->next->data;
		pot.join(&t1);
		pot.join(&t2);
		if (c1 > c2) {
			p1.join(&pot);
			if (war) {
				numWars++;
				_file << "\tWar " << numWars;
			}
			else {
				numBattles++;
				_file << "\tBattle " << numBattles;
			}
			_file << ": " << name1 << " (" << c1 << ")"
			<< " defeated " << name2 << " (" << c2 << "): " << name1 << " "
			<<  p1.num << ", " << name2 << " " << p2.num << endl;
			if (p2.num == 0) {
				this->_winner = name1;
				this->_loser = name2;
				break;
			}
			war = false;
		}
		else if (c1 < c2) {
			p2.join(&pot);
			if (war) {
				numWars++;
				_file << "\tWar " << numWars;
			}
			else {
				numBattles++;
				_file << "\tBattle " << numBattles;
			}
			_file << ": " << name2 << " (" << c2 << ")"
			<< " defeated " << name1 << " (" << c1 << "): " << name1 << " "
			<<  p1.num << ", " << name2 << " " << p2.num << endl;
			if (p1.num == 0) {
				this->_winner = name2;
				this->_loser = name1;
				break;
			}
			war = false;
		}
		else {
			if (p1.num == 0) {
				p2.join(&pot);
				if (war) {
					numWars++;
					_file << "\tWar " << numWars;
				}
				else {
					numBattles++;
					_file << "\tBattle " << numBattles;
				}
				_file << ": " << name2 << " (" << c2 << ")"
				<< " defeated " << name1 << " (" << c1 << "): " << name1 << " "
				<<  p1.num << ", " << name2 << " " << p2.num << endl;
				this->_winner = name2;
				this->_loser = name1;
				break;
			}
			if (p2.num == 0) {
				p1.join(&pot);
				if (war) {
					numWars++;
					_file << "\tWar " << numWars;
				}
				else {
					numBattles++;
					_file << "\tBattle " << numBattles;
				}
				_file << ": " << name1 << " (" << c1 << ")"
				<< " defeated " << name2 << " (" << c2 << "): " << name1 << " "
				<<  p1.num << ", " << name2 << " " << p2.num << endl;
				this->_winner = name1;
				this->_loser = name2;
				break;
			}
			if (war) {
				numWars++;
				_file << "\tWar " << numWars;
			}
			else {
				numBattles++;
				_file << "\tBattle " << numBattles;
			}
			_file << ": " << name1 << " (" << c1 << ")"
			<< " tied " << name2 << " (" << c2 << "): " << name1 << " "
			<<  p1.num << ", " << name2 << " " << p2.num << endl;
			t1 = p1.pop(min(3, p1.num-1));
			t2 = p2.pop(min(3, p2.num-1));
			pot.join(&t1);
			pot.join(&t2);
			war = true;
		}
	}
	if (numBattles+numWars == 1000) {
		if (p1.num >= p2.num) {
			this->_winner = name1;
			this->_loser = name2;
		}
		else {
			this->_winner = name2;
			this->_loser = name1;
		}
	}
	_file << this->_winner << " (" << this->_round << ") DEFEATED " << this->_loser << " in "
	<< numBattles << " Battles and " << numWars << " Wars" << endl;
	_totalBattles += numBattles;
	_mostBattles = max(_mostBattles, numBattles);
}








