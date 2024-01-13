#pragma once
#include<iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include<SFML/Graphics.hpp>
#include"windoww.h"
#include<sstream>
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
	void showSource(int i, int j)
	{
		int temp = i;
		i = j;
		j = temp;
		
		sf::Font f1;
		if (!f1.loadFromFile("numbers.ttf"))
		{
			cout << "cannot load font";
			return;
		}
		sf::Text text;
		text.setCharacterSize(50);
		text.setString("S");
		text.setFont(f1);
		text.setPosition(450 + (i * 50)+10, 75 + (j * 50)-5);
		
		window.draw(text);
		
	}
	void showDistance(int i, int j)
	{
		int x = getDistance(i, j);
		int temp = i;
		i = j;
		j = temp;

		sf::Font f1;
		if (!f1.loadFromFile("numbers.ttf"))
		{
			cout << "cannot load font";
			return;
		}
		sf::Text text;
		text.setCharacterSize(32);
		
		stringstream ss;
		ss << x;
		text.setString(ss.str());
		text.setFont(f1);
		text.setPosition(450 + (i * 50) + 10, 75 + (j * 50) + 5);

		window.draw(text);

	}
	void showYellow(int i, int j)
	{
		int temp = i;
		i = j;
		j = temp;
		sf::RectangleShape yellow(sf::Vector2f(49, 49));
		yellow.setFillColor(sf::Color::Yellow);
		yellow.setPosition(450 + (i * 50), 75 + (j * 50));
		window.draw(yellow);
	}
	void showBacktracked(int i, int j)
	{
		int x = getDistance(i, j);
		int temp = i;
		i = j;
		j = temp;
		x =x/ 100;

		sf::Font f1;
		if (!f1.loadFromFile("numbers.ttf"))
		{
			cout << "cannot load font";
			return;
		}
		sf::Text text;
		text.setCharacterSize(32);
		text.setFillColor(sf::Color::Black);
		stringstream ss;
		ss << x;
		text.setString(ss.str());
		text.setFont(f1);
		text.setPosition(450 + (i * 50) + 10, 75 + (j * 50) + 5);

		window.draw(text);
	}
public:
	//0 for empty space
	//-5 source
	//-6 destination
	//-1 blockage (cannot move here)
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
	void getDestination(int& x, int& y)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (arr[i][j] == -6)
				{
					x = i;
					y = j;
					return;
				}
			}
		}
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
	void set(int x, int y, int dis)  //testing
	{
		arr[x][y] = dis;
	}
	int getDistance(int x,int y)
	{
		return arr[x][y];
	}
	bool Completed()
	{
		return destination_reached;
	}
	
	bool insertSource(int x, int y)
	{
		if (arr[x][y] == 0)
		{
			arr[x][y] = -5;
			this->x = x;
			this->y = y;
			return true;
		}
		return false;
	}
	bool insertDestination(int x, int y)
	{
		if (arr[x][y] == 0)
		{
			arr[x][y] = -6;
			return true;
		}
		return false;
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
	bool insert_distance_up(int distance)
	{
		if (x - 1 < 0)
			return false;
		if (arr[x - 1][y] != 0 && arr[x - 1][y] != -6)
			return false;
		else
		{
			if (arr[x - 1][y] == -6)
			{
				destination_reached = true;
				arr[x - 1][y] = distance * 100;
			}
			else
			  arr[x - 1][y] = distance;
			return true;
		}
	}
	bool insert_distance_down(int distance)
	{
		if (x + 1 > size - 1)
			return false;
		if (arr[x + 1][y] != 0 && arr[x + 1][y] != -6)
			return false;
		else
		{
			if (arr[x + 1][y] == -6)
			{
				destination_reached = true;
				arr[x + 1][y] = distance*100;
			}
			else
			  arr[x + 1][y] = distance;
			return true;
		}
	}
	bool insert_distance_left(int distance)
	{
		if (y - 1 < 0)
			return false;
		if (arr[x][y - 1] != 0 && arr[x][y - 1] != -6)
			return false;
		else
		{
			if (arr[x][y - 1] == -6)
			{
				destination_reached = true;
				arr[x][y - 1] = distance*100;
			}
			else
			  arr[x][y - 1] = distance;
			return true;
		}
	}
	bool insert_distance_right(int distance)
	{
		if (y + 1 > size - 1)
			return false;
		if (arr[x][y + 1] != 0 && arr[x][y + 1] != -6)
			return false;
		else
		{
			if (arr[x][y + 1] == -6)
			{
				destination_reached = true;
				arr[x][y + 1] = distance*100;
			}
			else
			  arr[x][y + 1] = distance;
			return true;
		}
	}
	void update_location(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	bool trace_up(int& x, int& y, int& distance)
	{
		if (x - 1 < 0)
			return false;
		
		else if (arr[x - 1][y] == distance - 1)
		{
			arr[x - 1][y] *= 100;
			x--;
			distance--;
			return true;
		}
		else
			return false;
	}

	bool trace_down(int& x, int& y, int& distance)
	{
		if (x + 1 > size-1)
			return false;
		

		else if (arr[x + 1][y] == distance - 1)
		{
			arr[x + 1][y] *= 100;
			x++;
			distance--;
			return true;
		}
		else
			return false;
	}

	bool trace_left(int& x, int& y, int& distance)
	{
		if (y - 1 < 0)
			return false;
		
		else if (arr[x][y - 1] == distance - 1)
		{
			arr[x][y - 1] *= 100;
			y--;
			distance--;
			return true;
		}
		else
			return false;
	}

	bool trace_right(int& x, int& y, int& distance)
	{
		if (y + 1 > size - 1)
			return false;
		
		else if (arr[x][y + 1] == distance - 1)
		{
			arr[x][y + 1] *= 100;
			y++;
			distance--;
			return true;
		}
		else
			return false;
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
		bool inserted = this->insertSource(b, a);
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
	void Frontend()
	{
		showgrid();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (arr[i][j] == 0)
					showEmptySpaces(i, j);
				else if (arr[i][j] == -1)
					showBlockage(i, j);
				else if (arr[i][j] == -5)
				{
					showYellow(i, j);
					showSource(i, j);
				}
				else if (arr[i][j] >= 100)
				{
					showYellow(i, j);
					showBacktracked(i, j);
				}
				else if(arr[i][j]!=-6)
				{
					showEmptySpaces(i, j);
					showDistance(i, j);
				}
				
			}
		}
	}
};



