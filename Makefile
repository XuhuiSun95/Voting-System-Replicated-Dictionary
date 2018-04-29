all:
	g++ -std=c++11 *.cpp -lpthread -o voting_sys

clean:
	rm voting_sys
