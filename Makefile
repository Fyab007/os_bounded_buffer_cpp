p1: main.o producer.o consumer.o
	g++ main.o producer.o consumer.o -lpthread -o p1

p0: main_race.o producer_race.o consumer_race.o
	g++ main_race.o producer_race.o consumer_race.o -lpthread -o p0

main.o: main.cpp defs.h
	g++ -c main.cpp

producer.o: producer.cpp defs.h
	g++ -c producer.cpp

consumer.o: consumer.cpp defs.h
	g++ -c consumer.cpp

main_race.o: main_race.cpp defs.h
	g++ -c main_race.cpp

producer_race.o: producer_race.cpp defs.h
	g++ -c producer_race.cpp

consumer_race.o: consumer_race.cpp defs.h
	g++ -c consumer_race.cpp

clean:
	rm *.o p0 p1 *.txt