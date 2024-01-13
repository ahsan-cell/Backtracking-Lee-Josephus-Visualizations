#pragma once
#include<iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include<SFML/Graphics.hpp>
#include"windoww.h"
using namespace std;

class grid
{
	int size;
	int** arr;
	int x;
	int y;
	bool destination_reached;
	void showgrid()
	{
		sf::RectangleShape line1(sf::Vector2f(size * 50, 1));
		sf::RectangleShape line2(sf::Vector2f(size * 50, 1));
		line1.rotate(90);
		int j = 450;
		for (int i = 0; i < size + 1; i++)
		{


			line1.setPosition(j, 75);

			window.draw(line1);
			j = j + 50;
		}
		j = 75;
		for (int i = 0; i < size + 1; i++)
		{

			line2.setPosition(450, j);
			window.draw(line2);
			j = j + 50;
		}
	}
	void showEmptySpaces(int i, int j)
	{
		int temp = i;
		i = j;
		j = temp;
		sf::RectangleShape empty(sf::Vector2f(49, 49));
		empty.setFillColor(sf::Color::Color(255, 165, 0));
		empty.setPosition(450 + (i * 50), 75 + (j * 50));
		window.draw(empty);
	}
	void showAlreadyPassed(int i, int j)
	{
		int temp = i;
		i = j;
		j = temp;
		sf::RectangleShape passed(sf::Vector2f(49, 49));
		passed.setFillColor(sf::Color::Green);
		passed.setPosition(450 + (i * 50), 75 + (j * 50));
		window.draw(passed);
	}
	void showBlockage(int i, int j)
	{
		int temp = i;
		i = j;
		j = temp;
		sf::RectangleShape blocked(sf::Vector2f(50, 50));
		blocked.setFillColor(sf::Color::Blue);
		blocked.setPosition(450 + (i * 50), 75 + (j * 50));
		window.draw(blocked);
	}
	void showbacktrack(int i, int j)
	{
		int temp = i;
		i = j;
		j = temp;
		sf::RectangleShape back(sf::Vector2f(49, 49));
		back.setFillColor(sf::Color::Red);
		back.setPosition(450 + (i * 50), 75 + (j * 50));
		window.draw(back);
	}
	void showRat(int i, int j)
	{
		int temp = i;
		i = j;
		j = temp;
		sf::RectangleShape passed(sf::Vector2f(50, 50));
		passed.setFillColor(sf::Color::Green);
		passed.setPosition(450 + (i * 50), 75 + (j * 50));
		window.draw(passed);

		sf::Texture x;
		if (!(x.loadFromFile("rat.png")))
			cout << "cannot load rat.png";
		else
		{
			sf::Sprite rat;
			rat.setTexture(x);
			rat.setScale(sf::Vector2f(0.09, 0.09));
			rat.setPosition(450 + (i * 50), 75 + (j * 50));
			window.draw(rat);
		}
	}
public:
	//0 for empty space
	//5 source
	//6 destination
	//10 indicates positon of rat
	//7 indicates position which rat already passed 
	//-1 blockage (cannot move here)
	//-2 back tracked (cannot move here)
	grid()
	{
		size = 0;
		arr = nullptr;
		x = 0;
		y = 0;
		destination_reached = false;
	}
	grid(int s)
	{
		size = s;
		arr = new int* [size];
		for (int i = 0; i < size; i++)
			arr[i] = new int[size];
		x = 0;
		y = 0;
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				arr[i][j] = 0;
		destination_reached = false;
	}
	grid(const grid& obj)
	{
		size = obj.size;
		this->arr = new int* [size];
		for (int i = 0; i < size; i++)
			this->arr[i] = new int[size];
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				this->arr[i][j] = obj.arr[i][j];
		}
		x = obj.x;
		y = obj.y;
		destination_reached = obj.destination_reached;
	}
	~grid()
	{
		for (int i = 0; i < size; i++)
			delete[] arr[i];
		delete[] arr;
		size = 0;
		x = 0;
		y = 0;
		destination_reached = false;
	}
	void print()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				cout << arr[i][j] << " ";
			cout << endl;
		}
	}
	int get(int x, int y)
	{
		return arr[x][y];
	}
	
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	int getSize()
	{
		return size;
	}
	bool Completed()
	{
		return destination_reached;
	}
	void getLocation(int& x, int& y)
	{
		x = this->x;
		y = this->y;
	}
	bool insertSource(int x, int y)
	{
		if (arr[x][y] == 0)
		{
			arr[x][y] = 5;
			return true;
		}
		return false;
	}
	bool insertDestination(int x, int y)
	{
		if (arr[x][y] == 0)
		{
			arr[x][y] = 6;
			return true;
		}
		return false;
	}
	void insertBacktracked(int x, int y)
	{
		arr[x][y] = -2;
	}
	bool insertRat()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (arr[i][j] == 5)
				{
					arr[i][j] = 10;
					x = i;
					y = j;
					return true;
				}
			}
		}
		return false;
	}
	void insertRat(int x, int y)
	{
		arr[x][y] = 10;
		this->x = x;
		this->y = y;
	}
	bool moveUp()
	{
		if (x - 1 < 0)
			return false;
		if (arr[x - 1][y] == -1 || arr[x - 1][y] == -2 || arr[x-1][y]==7)
			return false;
		arr[x][y] = 7;
		x--;
		if (arr[x][y] == 6)
			destination_reached = true;
		arr[x][y] = 10;
		return true;
	}
	bool moveDown()
	{
		if (x + 1 > size - 1)
			return false;
		if (arr[x + 1][y] == -1 || arr[x + 1][y] == -2 || arr[x+1][y]==7)
			return false;
		arr[x][y] = 7;
		x++;
		if (arr[x][y] == 6)
			destination_reached = true;
		arr[x][y] = 10;
		return true;
	}
	bool moveLeft()
	{
		if (y - 1 < 0)
			return false;
		if (arr[x][y - 1] == -1 || arr[x][y - 1] == -2 || arr[x][y-1]==7)
			return false;
		arr[x][y] = 7;
		y--;
		if (arr[x][y] == 6)
			destination_reached = true;
		arr[x][y] = 10;
		return true;
	}
	bool moveRight()
	{
		if (y + 1 > size - 1)
			return false;
		if (arr[x][y + 1] == -1 || arr[x][y + 1] == -2 || arr[x][y+1]==7)
			return false;
		arr[x][y] = 7;
		y++;
		if (arr[x][y] == 6)
			destination_reached = true;
		arr[x][y] = 10;
		return true;
	}
	void insertBlockages()
	{
		int num_of_blockages = (size * size) * 0.22;
		srand(time(0));
		for (int i = 0; i < num_of_blockages; i++)
		{
			int a = rand() % size;
			int b = rand() % size;
			if (arr[a][b] == 0)
				arr[a][b] = -1;
			else
				i--;
		}
	}
	void Frontend()
	{
		showgrid();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (arr[i][j] == 0)
					showEmptySpaces(i, j);
				else if (arr[i][j] == 10)
					showRat(i, j);
				else if (arr[i][j] == 7)
					showAlreadyPassed(i, j);
				else if (arr[i][j] == -1)
					showBlockage(i, j);
				else if (arr[i][j] == -2)
					showbacktrack(i, j);

			}
		}
	}
	bool InputSource(int x, int y)
	{
		if (x == -1 && y == -1)
			return false;
		/*int temp = x;
		x = y;
		y = temp;*/
		int a = 0;
		int b = 0;
		int startx = 450;
		int starty = 75;
		bool flag = false;
		while(!flag)
		{
			if (startx < x)
				a++;
			else
			    flag=true;
			startx+=50;
		}
		flag = false;
		while(!flag)
		{
			if (starty < y)
				b++;
			else
				flag=true;
			starty+=50;
		}
		a--;
		b--;
		if (a<0 || a>size - 1 || b<0 || b>size - 1)
			return false;
		bool inserted=this->insertSource(b, a);
		if (inserted)
			insertRat();
		return inserted;
	}

	bool InputDestination(int x, int y)
	{
		if (x == -1 && y == -1)
			return false;
		/*int temp = x;
		x = y;
		y = temp;*/
		int a = 0;
		int b = 0;
		int startx = 450;
		int starty = 75;
		bool flag = false;
		while (!flag)
		{
			if (startx < x)
				a++;
			else
				flag = true;
			startx += 50;
		}
		flag = false;
		while (!flag)
		{
			if (starty < y)
				b++;
			else
				flag = true;
			starty += 50;
		}
		a--;
		b--;
		if (a<0 || a>size - 1 || b<0 || b>size - 1)
			return false;
		bool inserted = this->insertDestination(b, a);
		return inserted;
	}


};