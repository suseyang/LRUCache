#include "LRUCache.h"

LRUCache::LRUCache(int size)
	: m_cacheSize(size), queue(size), hash(size)
{

}

int LRUCache::get(int key)
{
	shared_ptr<QNode> sp = hash.get(key);
	if (sp==nullptr)
	{
		return -1;
	}
	else if (sp==queue.front)
	{
		return sp->value;
	}
	else
	{
		sp->prev->next = sp->next;
		if (sp->next)
		{
			sp->next->prev = sp->prev;

		}
		queue.front->prev = sp;
		if (sp==queue.rear)
		{
			queue.rear = sp->prev;
		}
		sp->next = queue.front;
		queue.front = sp;
		sp->prev = nullptr;
		return sp->value;
	}

}

void LRUCache::set(int key, int value)
{
	if (hash.get(key)==nullptr)
	{
		shared_ptr<QNode> sp(new QNode(value));
		hash.set(key, sp);

		if (queue.isQueueFull())
		{
			// Delete rear
			queue.pop_rear();

		}

		queue.insert(sp);
	}
	else
	{
		// If the node exists, move it to front.
		shared_ptr<QNode> sp = hash.get(key);
		sp->next->prev = sp->prev;
		sp->prev->next = sp->next;
		if (sp==queue.rear)
		{
			queue.rear = sp->prev;
		}
		queue.front->prev = sp;
		sp->next = queue.front;
		sp->prev = nullptr;
		queue.front = sp;
	}

}