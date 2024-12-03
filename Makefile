all: main

main: Main.o GameSetting.o SurvivalLog.o
	g++ -o main Main.o GameSetting.o SurvivalLog.o

Main.o: Main.cpp GameSetting.h SurvivalLog.h
	g++ -c Main.cpp

GameSetting.o: GameSetting.cpp GameSetting.h
	g++ -c GameSetting.cpp

SurvivalLog.o: SurvivalLog.cpp SurvivalLog.h SurvivalLog.h
	g++ -c SurvivalLog.cpp

clean:
	rm -f *.o main
