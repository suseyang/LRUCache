#include "LRUCache.h"

int main()
{
	LRUCache cache(2);

	cache.set(1, 1);
	cache.set(2, 2);
	cout<<cache.get(1)<<" ";       // returns 1
	cache.set(3, 3);    // evicts key 2
	cout<<cache.get(2)<<" ";       // returns -1 (not found)
	cache.set(4, 4);    // evicts key 1
	cout<<cache.get(1)<<" ";       // returns -1 (not found)
	cout<<cache.get(3)<<" ";       // returns 3
	cout<<cache.get(4)<<" ";       // returns 4
	cout << endl;
}