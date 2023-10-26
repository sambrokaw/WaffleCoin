

all: probing chaining

probing: runner_probing.cpp ProbingHashTable.cpp Hash.cpp
	g++ -std=c++17 -o probing runner_probing.cpp ProbingHashTable.cpp Hash.cpp

chaining: runner_chaining.cpp ChainingHashTable.cpp Hash.cpp
	g++ -std=c++17 -o chaining runner_chaining.cpp ChainingHashTable.cpp Hash.cpp

WaffleCoin: WaffleCoin.cpp Block.h Hash.cpp
	g++ -std=c++17 -o WaffleCoin WaffleCoin.cpp Hash.cpp

clean:
	rm probing
	rm chaining
	rm WaffleCoin
