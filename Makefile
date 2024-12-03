all: main

main: Main.o GameSetting.o Survival_log.o
	g++ -o main Main.o GameSetting.o Survival_log.o

Main.o: Main.cpp GameSetting.h Survival_log.h
	g++ -c Main.cpp

GameSetting.o: GameSetting.cpp GameSetting.h
	g++ -c GameSetting.cpp

Survival_log.o: Survival_log.cpp Survival_log.h Survival_log.h
	g++ -c Survival_log.cpp

clean:
	rm -f *.o main
