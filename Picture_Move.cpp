#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

#pragma warning(disable : 4018)
#pragma warning(disable : 4305)
#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#pragma warning(disable : 26495)

using namespace std;
using namespace sf;

bool checkOne(int table[], const int& size)
{
    int c = 0;
    for (int k(0); k < size; k++)
    {
        if (table[k])c++;
    }
    if (c == size)return true;
    return false;
}

int main()
{
    srand(time(NULL));
    const int width(1000), height(1000);
    const int squareSize(40);
    const int squaresH = width / squareSize;
    const int squaresV = height / squareSize;
    const int allSquares = squaresH * squaresV;

    sf::RenderWindow window(sf::VideoMode(width, height), "Opposite");

    Texture eagleTexture;
    eagleTexture.loadFromFile("images/amd.jpg");

    Sprite eagle;
    eagle.setTexture(eagleTexture);

    Sprite* squares = new Sprite[allSquares];
    Sprite* copySquares = new Sprite[allSquares];


    int* table = new int[allSquares];

    for (int k(0); k < allSquares; k++)
    {
        table[k] = 0;
     
    }

    for (int k(0); k < allSquares; k++)
    {
        squares[k].setTexture(eagleTexture);
        squares[k].setTextureRect(IntRect(k % squaresH * squareSize, k / squaresH * squareSize, squareSize, squareSize));

        if (k % squaresH == 0)squares[k].setPosition(k % squaresH * squareSize + squareSize / 2, k / squaresH * squareSize + squareSize / 2), squares[k].setOrigin(squareSize / 2, squareSize / 2);
        if (k % squaresH != 0)squares[k].setPosition(k % squaresH * squareSize + squareSize / 2, k / squaresH * squareSize + squareSize / 2), squares[k].setOrigin(squareSize / 2, squareSize / 2);
        if (k / squaresH > 0)squares[k].setPosition(k % squaresH * squareSize + squareSize / 2, k / squaresH * squareSize + squareSize / 2), squares[k].setOrigin(squareSize / 2, squareSize / 2);

    }

    Clock clock;
    float timer = 0, delay = 0.0000005f;
    int actualPositionX = 0;
    int oldActualPositionX = 0;
    int actualPositionY = 0;
    int x = 0, y = 0;
    bool passed = false;
    bool once = false;

    int f = 0;
   
    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);

        float time = clock.getElapsedTime().asSeconds();
        timer += time;
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

      
        if (!checkOne(table, width) && timer > delay)
        {
           
            
            if (!passed)
            {

            table[x+y*squaresH] = 1;
            
            if (x + y * squaresH - 1 < allSquares)x++, y++;
           
            if (x == squaresH) 
            {
                
                if (actualPositionX < squaresH)actualPositionX++;            
                x = actualPositionX;
                y = 0;
               
            }
              if(actualPositionX == squaresH)
              {
                  passed = true;
                  x = squaresH - 1;
                  y = squaresV - 1;
                  oldActualPositionX = actualPositionX;
              }
  
            }
                
            else {
               table[(x-1) + y * squaresH] = 1;

                if (x + y * squaresH - 1 > 0 )x--, y--;
               
                if (x == 0) 
                {

                    if (actualPositionX > 0)--actualPositionX;

                    x = actualPositionX;
                    y = squaresV-1;
                         
                }         
                
            }


            timer = 0;
        }

        for (int k(0); k < allSquares; k++)
        {
            if (table[k]) {
              
               
                window.draw(squares[k]);
            }
        }

        window.display();
    }

    delete[] table;
    delete[] squares;
    delete[] copySquares;
   

    return 0;
}