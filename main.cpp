#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
#include "PlayingCard.h"
#include "Game.h"
#include "LLC.h"
using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "Invalid arguments. Try again." << endl;
	}
	else {
		ifstream inputFile;
		inputFile.open(argv[1]);
		string names[64];
		int i = 0;
		string line;
		while (getline(inputFile,line)) {
			if (i < 64)
				if (line != "")
					names[i] = line;
				else
					i--;
			else {
				i++;
				break;
			}
			i++;
		}
		if (i < 2 or i == 65 or i&(i-1))
			cout << "Invalid number of players." << endl;
		else {
			Game(names, argv[2], 0, i-1); 
		}
	}
}
