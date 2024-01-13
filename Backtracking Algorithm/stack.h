#pragma once
#include<iostream>
using namespace std;

//template <class T>
//class linklist
//{
//	class node
//	{
//		T x;
//		T y;
//		node* next;
//	public:
//		node()
//		{
//			next = nullptr;
//		}
//		~node()
//		{
//			next = nullptr;
//		}
//		friend class linklist<T>;
//	};
//
//	node* head;
//public:
//	linklist()
//	{
//		head = nullptr;
//	}
//	void insertAtHead(T const x,T const y)
//	{
//		Node* n = new Node<T>;
//		n->x = x;
//		n->y = y;
//		n->next = head;
//		head = n;
//	}
//	void DeleteAtHead()
//	{
//		if (head == nullptr)
//			return;
//		node* current = head;
//		current = current->next;
//		delete head;
//		head = current;
//
//	}
//};

template <class T>
class stack
{
	class node
	{
		node* next;
		T x;
		T y;
	public:
		friend class stack<T>;
		node()
		{
			next = nullptr;
		}
		~node()
		{
			next = nullptr;
		}
	};
	node* top;
public:
	stack()
	{
		top = nullptr;
	}
	stack(const stack& obj)
	{
		if (obj.top != nullptr)
		{
			node* curr = obj.top;
			node* n = new node;
			n->x = obj.top->x;
			top = n;
			curr = curr->next;
			node* curr2 = top;
			while (curr != nullptr)
			{

				node* n = new node;
				n->x = curr->x;
				curr2->next = n;
				curr = curr->next;
				curr2 = curr2->next;
			}

		}
	}
	bool isEmpty()
	{
		if (top == nullptr)
			return true;
		return false;
	}
	void push(T x, T y)
	{
		//insertAtHead()
		node* n = new node;
		n->x = x;
		n->y = y;
		n->next = top;
		top = n;
	}
	bool pop(T& x, T& y)
	{
		if (isEmpty())
			return false;
		x = top->x;
		y = top->y;
		node* current = top;
		current = current->next;
		delete top;
		top = current;
		return true;
	}
	bool peek(T& a, T& b)
	{
		if (isEmpty())
			return false;
		a = top->x;
		b = top->y;
		return true;
	}
	~stack()
	{
		int x, y;
		while (!isEmpty())
		{
			this->pop(x, y);
		}
	}
};