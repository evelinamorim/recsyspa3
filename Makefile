datadir = ../PA1/ml-100k/

index:
	g++ -O3 -c -o util.o util.cpp -ggdb
	g++ -O3 -c -o index.o index.cpp -ggdb
	g++ -O3 -c -o main_index.o main_index.cpp -ggdb
	g++ -O3 -o tp3-index main_index.o util.o index.o -g
runindex:
	./tp3-index $(datadir)/u.item-omdb
clean:
	rm voc.txt idx_film.txt idx_term.txt
