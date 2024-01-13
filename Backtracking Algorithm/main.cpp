#include<iostream>
#include"grid.h"
#include<SFML/Graphics.hpp>
#include"windoww.h"
#include"stack.h"
#include<Windows.h>
using namespace std;
void Mouseinput(int& ,int&);

int main()
{
    //sf::RenderWindow window(sf::VideoMode(1920, 1080), "Rat and maze",sf::Style::Close | sf::Style::Fullscreen);
    int size;
    cout << "---------YOU CAN CHOOSE SOURCE AND DESTINATION USING MOUSE INPUT--------\n\n";
    cout << "Enter Grid Size: ";
    cin >> size;
    if (size < 2)
    {
        cout << "Invalid Input";
        return 0;
    }
    grid g1(size);

    g1.insertBlockages();
    int x=-1;
    int y = -1;
    bool source = false;
    bool dest = false;
    stack<int> s1;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        window.clear();
        g1.Frontend();
        Mouseinput(x,y);
        if (source == false)
        {
            source = g1.InputSource(x, y);
            x = -1; y = -1;

        }
        if (dest == false)
           dest= g1.InputDestination(x, y);
        if (source && dest &&!(g1.Completed()))
        {
           Sleep(99);
            s1.push(g1.getX(), g1.getY());
            if (!(g1.moveDown()))
               if(!(g1.moveUp()))
                    if(!(g1.moveLeft()))
                        if (!(g1.moveRight()))
                        {
                            int i, j;
                            s1.pop(i, j); //to be marked as backtracked
                            int i2, j2;
                            s1.pop(i2, j2);
                            g1.insertRat(i2, j2);
                            g1.insertBacktracked(i, j);
                        }
            
        }
        
        window.display();
    }

    return 0;

}

void Mouseinput(int&x,int&y)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {

        x = sf::Mouse::getPosition(window).x;
        y = sf::Mouse::getPosition(window).y;
       
    }
}

//void main()  //this one is for testing stack
//{
//    stack<int> s1;
//    s1.push(0, 0);
//    s1.push(0, 1);
//    s1.push(0, 2);
//    s1.push(0, 3);
//    int x, y;
//    s1.pop(x, y);
//    cout << x << " " << y;
//
//}