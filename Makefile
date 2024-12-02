# Makefile
CC=g++
CFLAGS=-Wall -std=c++11

all: SurvivalIslandGame

SurvivalIslandGame: Main.o GameSetting.o GameActions.o GameUtilities.o GameItems.o
	$(CC) $(CFLAGS) -o $@ $^

Main.o: Main.cpp GameSetting.h
	$(CC) $(CFLAGS) -c $<

GameSetting.o: GameSetting.cpp GameSetting.h GameActions.h GameUtilities.h GameItems.h
	$(CC) $(CFLAGS) -c $<

GameActions.o: GameActions.cpp GameActions.h GameSetting.h
	$(CC) $(CFLAGS) -c $<

GameUtilities.o: GameUtilities.cpp GameUtilities.h
	$(CC) $(CFLAGS) -c $<

GameItems.o: GameItems.cpp GameItems.h GameSetting.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o SurvivalIslandGame
