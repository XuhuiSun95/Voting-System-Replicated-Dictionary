all:
	g++ -std=c++11 server/*.cpp -lpthread -o voting_sys

clean:
	rm voting_sys record/state_*
