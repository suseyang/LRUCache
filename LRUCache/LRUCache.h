#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <memory>

using namespace std;

struct QNode
{
	QNode(int val):value(val){}
	shared_ptr<QNode> prev;
	shared_ptr<QNode> next;
	int value;
};

struct Queue
{
	Queue(int size): count(0), size(size), front(nullptr), rear(nullptr) { }
	bool isQueueFull() { return count == size ? true : false; }

	void pop_rear()
	{
		rear->prev->next = nullptr;
		rear->value = -1;
		rear = rear->prev;
		//rear.reset();
		count--;
	}

	void insert(shared_ptr<QNode> sp)
	{
		if (count==size)
		{
			return;
		}

		count++;
		if (front==nullptr)
		{
			front = rear = sp;
			return;
		}

		// Add new created QNode to queue front.
		front->prev = sp;
		sp->next = front;
		sp->prev = nullptr;
		front = sp;

	}

	shared_ptr<QNode> front;
	shared_ptr<QNode> rear;
	int count;
	int size;

};

struct Hash
{
	Hash(int cap) :capacity(cap) { map.reserve(cap); }
	int capacity;
	unordered_map<int, shared_ptr<QNode>> map;

	shared_ptr<QNode> get(int key)
	{
		return map[key];
	}
	void set(int key, shared_ptr<QNode> sp)
	{
		map[key] = sp;
	}

};

class LRUCache
{
public:
	LRUCache(int size);

	int get(int key);
	void set(int key, int value);

private:
	int m_cacheSize;
	Queue queue;
	Hash hash;

};