#include<iostream>
#include"grid.h"
#include<SFML/Graphics.hpp>
#include"windoww.h"
#include<Windows.h>
#include"Queue.h"
using namespace std;
void Mouseinput(int&, int&);

int main()
{
    
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
    int x = -1;
    int y = -1;
    bool source = false;
    bool dest = false;
    queue<int> q1;
    int distance = 1;
    int destX, destY;
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
       //-----------------------------//
        g1.Frontend();
        Mouseinput(x, y);
        if (source == false)
        {
            source = g1.InputSource(x, y);
            x = -1; y = -1;
            /*if (source)
                q1.Enqueue(g1.getX(), g1.getY());*/

        }
        

        if (dest == false)
        {
            dest = g1.InputDestination(x, y);
            if (dest)
                g1.getDestination(destX, destY);
        }
        if (source && dest && !(g1.Completed()))
        {
            if (g1.insert_distance_up(distance))
            {
                q1.Enqueue(g1.getX() - 1, g1.getY());
            }
            if (g1.insert_distance_down(distance))
            {
                q1.Enqueue(g1.getX() + 1, g1.getY());
            }
            if (g1.insert_distance_left(distance))
            {
                q1.Enqueue(g1.getX(), g1.getY() - 1);
            }
            if (g1.insert_distance_right(distance))
            {
                q1.Enqueue(g1.getX(), g1.getY() + 1);
            }
            
            int i, j;
            q1.Dequeue(i, j);
            g1.update_location(i, j);
            distance = g1.getDistance(i, j);
            distance++;
          //  cout << endl;
            //g1.print();
        }
        if (g1.Completed() && distance!=1)
        {
            if(!g1.trace_up(destX,destY,distance))
                if(!g1.trace_down(destX,destY,distance))
                    if(!g1.trace_left(destX,destY,distance))
                        if (!g1.trace_right(destX, destY, distance))
                        {
                            distance--;
                        }

        }
        //----------------------------//
        window.display();
    }

    return 0;

}

void Mouseinput(int& x, int& y)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {

        x = sf::Mouse::getPosition(window).x;
        y = sf::Mouse::getPosition(window).y;


    }
}

//void main()
//{
//    queue<int> q1;
//    int x, y;
//    q1.Enqueue(0, 0);
//    q1.Enqueue(1, 1);
//    q1.Enqueue(2, 2);
//    q1.Enqueue(3, 3);
//    q1.Enqueue(4, 4);
//    q1.Dequeue(x, y);
//
//}


// comparison: it is obvious that the queue based solution finds the shortest path
//becuase it maps the whole grid whereas the stack based solution just randomly moves until it reaches destination

//time complexity of lee's algorithm: O(n^2) where n is the number of rows and number of columns of grids 
//time complexity of stack based solution is O(2^n^2)