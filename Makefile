all: main

main: Main.o GameSetting.o FileHandling.o
	g++ -o main Main.o GameSetting.o FileHandling.o

Main.o: Main.cpp GameSetting.h FileHandling.h
	g++ -c Main.cpp

GameSetting.o: GameSetting.cpp GameSetting.h
	g++ -c GameSetting.cpp

FileHandling.o: FileHandling.cpp FileHandling.h GameSetting.h
	g++ -c FileHandling.cpp

clean:
	rm -f *.o main
