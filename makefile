# Specifiy the target
all:	LLC

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
LLC:	PlayingCard.o Game.o main.o
	g++ PlayingCard.o Game.o main.o -o LLC

# Specify how the object files should be created from source files
Game.o: Game.cpp
	g++ -g -Wall -c Game.cpp

PlayingCard.o: PlayingCard.cpp
	g++ -g -Wall -c PlayingCard.cpp

main.o:	main.cpp
	g++ -g -Wall -c main.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o LLC
