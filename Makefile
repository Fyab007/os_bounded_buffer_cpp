a.out: main.o producer.o consumer.o
	g++ main.o producer.o consumer.o -lpthread

main.o: main.cpp defs.h
	g++ -c main.cpp

producer.o: producer.cpp defs.h
	g++ -c producer.cpp

consumer.o: consumer.cpp defs.h
	g++ -c consumer.cpp