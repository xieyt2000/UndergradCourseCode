P_FLAGS = -Wall -pthread -std=c++11 -Ofast

default: prod_cons_2 prod_cons_2k prod_cons_any task_queue fib

prod_cons_any:prod_cons_any.cpp 
	g++ $(P_FLAGS) prod_cons_any.cpp -o prod_cons_any

prod_cons_2k:prod_cons_2k.cpp 
	g++ $(P_FLAGS) prod_cons_2k.cpp -o prod_cons_2k

prod_cons_2: prod_cons_2.cpp
	g++ $(P_FLAGS) prod_cons_2.cpp -o prod_cons_2

task_queue: task_queue.cpp pthreadClass.h
	g++ $(P_FLAGS) task_queue.cpp -o task_queue

fib: fib.cpp pthreadClass.h
	g++ $(P_FLAGS) fib.cpp -o fib

clean:
	rm prod_cons_2 prod_cons_2k task_queue