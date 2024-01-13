#pragma once

#include<iostream>
using namespace std;

template <class T>
class queue
{
	class node
	{
		node* next;
		T x;
		T y;
	public:
		friend class queue<T>;
		node()
		{
			next = nullptr;
		}
		~node()
		{
			next = nullptr;
		}
	};
	node* front;
	node* tail;
public:
	queue()
	{
		front = nullptr;
		tail = nullptr;
	}
	bool isEmpty()
	{
		if (front == nullptr)
			return true;
		return false;
	}
	void Enqueue(T x, T y)
	{
		//insert_at_tail()
		if (front == nullptr)
		{
			node* n = new node;
			n->x = x;
			n->y = y;
			n->next = nullptr;
			front = n;
			tail = n;
		}
		else
		{
			node* n = new node;
			n->x = x;
			n->y = y;
			tail->next = n;
			n->next = nullptr;
			tail = n;
		}
	}
	bool Dequeue(T& x, T& y)
	{
		//delete_at_head()
		if (front == nullptr)
			return false;
		node* n = front->next;
		x = front->x;
		y = front->y;
		delete front;
		front = n;
		return true;
	}
	bool start(T& x, T& y)
	{
		if (front == nullptr)
			return false;
		x = front->x;
		y = front->y;
		return true;
	}
	~queue()
	{
		if (front != nullptr)
		{
			T x, y;
			while (front != nullptr)
				this->Dequeue(x, y);
		}
	}
};