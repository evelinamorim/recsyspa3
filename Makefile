datadir = ../PA1/ml-100k/

index:
	g++ -O3 -c -o util.o util.cpp -ggdb
	g++ -O3 -c -o index.o index.cpp -ggdb
	g++ -O3 -c -o main_index.o main_index.cpp -ggdb
	g++ -O3 -o tp3-index main_index.o util.o index.o -g

recommend:
	g++ -O3 -c -o util.o util.cpp -ggdb
	g++ -O3 -c -o recommend.o recommend.cpp -ggdb
	g++ -O3 -c -o main_recommend.o main_recommend.cpp -ggdb
	g++ -O3 -c -o index.o index.cpp -ggdb
	g++ -O3 -o tp3-recommend main_recommend.o util.o recommend.o index.o -g
eval:
	g++ -O3 -c -o util.o util.cpp -ggdb
	g++ -O3 -c -o evaluation.o evaluation.cpp -ggdb
	g++ -O3 -c -o main_evaluation.o main_evaluation.cpp -ggdb
	g++ -O3 -o tp3-eval main_evaluation.o util.o evaluation.o  -g

runindex:
	#./tp3-index $(datadir)/u.item-omdb
	./tp3-index toy.item

runrecommend:
	#./tp3-recommend $(datadir)/u.users  $(datadir)/u.item-omdb $(datadir)/ua.base
	./tp3-recommend toy.user  toy.item toy.base
clean:
	#rm voc.txt idx_film.txt idx_term.txt
	rm voc_toy.txt idx_film_toy.txt idx_term_toy.txt
