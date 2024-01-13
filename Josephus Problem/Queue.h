#pragma once
#include<iostream>
using namespace std;
#include"Windoww.h"
#include"SFML/Graphics.hpp"
#include<math.h>
#include<sstream>
const double PI = 3.14159;
double Convert(double radian)
{
	return(radian * (180 / PI));
}

//queue based on a circular singly linklist
//template <class T>
//class queue
//{
//	class node
//	{
//		node* next;
//		T data;
//	public:
//		friend class queue<T>;
//		node()
//		{
//			next = nullptr;
//		}
//		~node()
//		{
//			next = nullptr;
//		}
//	};
//	node* front;
//	node* tail;
//public:
//	queue()
//	{
//		front = nullptr;
//		tail = nullptr;
//	}
//	bool isEmpty()
//	{
//		if (front == nullptr)
//			return true;
//		return false;
//	}
//	void Enqueue(T data)
//	{
//		//insert_at_tail()
//		if (front == nullptr)
//		{
//			node* n = new node;
//			n->data = data;
//			n->next = nullptr;
//			front = n;
//			tail = n;
//			tail->next = front;
//		}
//		else
//		{
//			node* n = new node;
//			n->data = data;
//			tail->next = n;
//			//n->next = nullptr;
//			tail = n;
//			tail->next = front;
//		}
//	}
//	bool Dequeue(T data)
//	{
//		//delete_at_head()
//		if (front == nullptr)
//			return false;
//		node* n = front->next;
//		data = front->data;
//		if (front == tail->next)
//			tail->next = n;
//		delete front;
//		front = n;
//		return true;
//	}
//	bool front_data(T data)
//	{
//		if (front == nullptr)
//			return false;
//		data = front->data;
//		return true;
//	}
//	void increment_front()
//	{
//		front = front->next;
//	}
//	~queue()
//	{
//		if (front != nullptr)
//		{
//			T data=0;
//			while (front != tail)
//				this->Dequeue(data);
//			delete front;
//		}
//	}
//};

template <class T>
class queue
{
	int front;
	int rear;
	T* arr;
	int size;
	int count;
public:
	queue()
	{
		size = 0;
		arr = nullptr;
		front = 1;
		rear = 0;
		count = 0;
	}
	queue(int x)
	{
		size = x;
		arr = new T[size];
		for (int i = 0; i < size; i++)
			arr[i] = 0;
		front = 1;
		rear = 0;
		count = 0;
	}
	queue(const queue & obj)
	{
		size = obj.size;
		arr = new T[size];
		for (int i = 0; i < size;i++)
			arr[i] = obj.arr[i];
		front = obj.front;
		rear = obj.rear;
		count = obj.count;
	}
	bool isFull()
	{
		if (count == size)
			return true;
		return false;
	}
	bool isEmpty()
	{
		if (count == 0)
			return true;
		return false;
	}
	bool Enqueue(T e)
	{
		if (!isFull())
		{
			rear++;
			if (rear == size)
				rear = 0;
			arr[rear] = e;
			count++;
			return true;
		}
		return false;
	}
	bool Dequeue(T& e)
	{
		if (!isEmpty())
		{
			//front++;
			if (front == size)
				front = 0;
			e = arr[front];
			arr[front] = 0;
			increment_front();
			count--;
			return true;
		}
		return false;
	}
	void print()
	{
		for (int i = 1; i <size; i++)
		{
			if (arr[i] != 0)
				cout << arr[i] << endl;
		}
		if (arr[0] != 0)
			cout << arr[0];
	}

	void printall()
	{
		for (int i = 0; i < size; i++)
			cout << arr[i] << endl;
	}
	 
	void increment_front()
	{
		//front++;
		if (!isEmpty())
		{
			do {
				if (front == size - 1)
					front = 0;
				else
					front++;
			} while (arr[front] == 0);

		}
	}

	void decrement_front()
	{
		//front++;
		if (!isEmpty())
		{
			do {
				front--;
				if (front < 0)
					front = size - 1;
			} while (arr[front] == 0);
		}
	}
	T Front()
	{
		return arr[front];
	}
	
	void show_soldier(int x, int y,float angle,int number)
	{
		sf::Texture t;
		if (!t.loadFromFile("soldier.png"))
			cout << "cannot load file";
		else
		{
			sf::Sprite soldier;
			soldier.setTexture(t);
			soldier.setPosition(x, y);
			soldier.setRotation(angle);
			soldier.setScale(sf::Vector2f(0.5, 0.5));
			
			sf::Font f;
			if (!f.loadFromFile("chp-fire.ttf"))
				cout << "error loading font";
			sf::Text num;
			stringstream ss;
			ss << number;
			num.setFont(f);
			num.setCharacterSize(32);
			num.setString(ss.str());
			num.setPosition(x -5, y);
			window.draw(num);
			
			window.draw(soldier);

		}
	}
	/*void show_cross(float x, float y)
	{
		sf::RectangleShape line1(sf::Vector2f(90, 5));
		sf::RectangleShape line2(sf::Vector2f(90, 5));


		line1.rotate(45);
		line2.rotate(135);
		line1.setPosition(x , y);
		line2.setPosition(x + 65, y + 4);
		window.draw(line1);
		window.draw(line2);

	}*/
	void showCross(int x, int y, float angle)
	{
		sf::Texture t;
		if (!t.loadFromFile("cross2.png"))
			cout << "cannot load file";
		else
		{
			sf::Sprite soldier;
			soldier.setTexture(t);
			soldier.setPosition(x, y);
			soldier.setRotation(angle);
			soldier.setScale(sf::Vector2f(0.5, 0.5));

			

			window.draw(soldier);

		}
	}


	void show_circle()
	{
		
		float centreX = 960;
		float centreY = 540;
		float radius=300;
		int k = 1;
		float i = 0;
		//float i = 0; i < 2 * PI; i = i + (PI /(size/2.0))
		for (int j=0;j<size;j++)
		{
			
			if (arr[k] != 0 && k < size)
				show_soldier(centreX + radius * cos(i), centreY + radius * sin(i), Convert(i), arr[k]);
			else if (k < size)
			showCross(centreX + radius * cos(i), centreY + radius * sin(i), Convert(i));
			if (k < size)
			{
				k++;
			}
			else if (arr[0] != 0)
				show_soldier(centreX + radius * cos(i), centreY + radius * sin(i), Convert(i), arr[0]);
			else
				showCross(centreX + radius * cos(i), centreY + radius * sin(i), Convert(i));
			i = i + (PI / (size / 2.0));
			
		
			
		}
	}

};