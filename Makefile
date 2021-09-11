p0: main_race.o producer_race.o consumer_race.o
	g++ main_race.o producer_race.o consumer_race.o -lpthread -o p0

main_race.o: main_race.cpp defs.h
	g++ -c main_race.cpp

producer_race.o: producer_race.cpp defs.h
	g++ -c producer_race.cpp

consumer_race.o: consumer_race.cpp defs.h
	g++ -c consumer_race.cpp

clean:
	rm *.o a.out