#include<iostream>
using namespace std;
#include"Queue.h"
#include"SFML/Graphics.hpp"
#include"Windoww.h"
#include<Windows.h>
void Mouseinput(int&, int&);

int main()
{
    int n = 0;
    int k = 0;
    int start = 0;
    cout << "Enter the number of soldiers N: ";
    cin >> n;
    cout << "Enter value of K: ";
    cin >> k;
    cout << "Enter starting point: ";
    cin >> start;
    queue<int> q1(n);
    for (int i = 1; i <= n; i++)
        q1.Enqueue(i);
    for (int i = 0; i < start-1; i++)
        q1.increment_front();
    int x = -1,y=-1;
    bool done = false;
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
        while (!done)
        {
            for (int i = 0; i < n-1; i++)
            {
                if (i == 0)
                {
                    window.clear();
                    q1.show_circle();
                    window.display();

                }
                window.clear();
                //-----------------------------//
                Sleep(500);
                
                for (int i = 0; i < k; i++)
                    q1.increment_front();
                q1.Dequeue(x);
                /*for (int i = 0; i < k - 1; i++)
                    q1.decrement_front();*/
                //q1.printall();
               // cout << "-----------------\n";
                q1.show_circle();
                window.display();
            }
            done = true;
        }
       
    } 

    cout <<"Last man standing: " <<q1.Front();
    return 0;

}

void Mouseinput(int& x, int& y)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {

        x = sf::Mouse::getPosition(window).x;
        y = sf::Mouse::getPosition(window).y;
        cout << "X:" << x << endl;
        cout << "Y:" << y << endl;


    }
}


