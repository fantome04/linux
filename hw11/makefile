run: mutex spinlock semaphore
	./mutex
	./spinlock
	./semaphore

mutex: ex1_1.cpp
	g++ ex1_1.cpp -o mutex -pthread

spinlock: ex1_2.cpp
	g++ ex1_2.cpp -o spinlock -pthread

semaphore: ex1_3.cpp
	g++ ex1_3.cpp -o semaphore -pthread


run2: bank
	./bank

bank: ex2.cpp
	g++ ex2.cpp -o bank -pthread