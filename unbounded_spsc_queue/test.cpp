#include "unbounded_spsc_queue.hpp"

int main(void) {
	unbounded_spsc_queue<int> q; 
	q.enqueue(1); 
	q.enqueue(2); 
	int v; 
	bool b = q.dequeue(v); 
	b = q.dequeue(v); 
	q.enqueue(3); 
	q.enqueue(4); 
	b = q.dequeue(v); 
	b = q.dequeue(v); 
	b = q.dequeue(v); 

	return 0;
}
