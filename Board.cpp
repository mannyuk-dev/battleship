#include "headers/Board.h"
#include <iostream>
#include <vector>
#include <iomanip> 
#include <string> 
#include <stdio.h>     
#include <stdlib.h>    
#include <time.h> 


using namespace std;

board::board() {//The constructor creates a  2D array and the game grid

    for (int i = 0; i < 10; i++)  // First loop creates a column and 2nd loop creates a row
        for (int j = 0; j < 10; j++) {
            grid[i][j] = '0'; //This sets a default position of 0 in the grid. ie. when the ship is not placed yet
        }
    }
}


void board::player_guess(char y, char x) {
    int x_cord = x - '0'; //Converts char to int
    char y_cords[] = {'A','B','C','D','E','F','G','H','I','J'};

    //So the X cords already int. This for loop goes through y_cords[] to find the proper y value
    //because the y value is passed to the function as a letter
    for (int i = 0; i < 10; i++) {
        if (y_cords[i] == y) {
            if (grid[i][x_cord] == '0') { grid[i][x_cord] = '#'; } // missing will show #
            if (grid[i][x_cord] == '+') { grid[i][x_cord] = 'X'; } // If you target a ship coord, you hit therefore an X is shwown.
        }
    }
    draw_grid(0);
}

void board::place_ships(char y, char x, char heading, int length) {//This places the ships by using cardinal coords. North, South, East and West

    int y_cord;
    char y_cords[] = { 'A','B','C','D','E','F','G','H','I','J' };
    int x_cord = x - '0';

    for (int i = 0; i < 10; i++) {
        if (y_cords[i] == y) {
            grid[i][x_cord] = '+';


            if (heading == 'N') { //N means north. therefore a ship is placed in the vertical direction upwards
                for (length; length > 0; length--) {
                    grid[i-(length-1)][x_cord] = '+'; //Subtracting the Y value goes North
                }
            }
            if (heading == 'S') { //S means north. therefore a ship is placed in the vertical direction downwards
                for (length; length > 0; length--) {
                    grid[i + (length - 1)][x_cord] = '+'; //Adding to the Y value goes South
                }
            }
            if (heading == 'E') { //E means north. therefore a ship is placed in the horizontal direction to the left
                for (length; length > 0; length--) {
                    grid[i][x_cord+(length-1)] = '+'; //Adding to the X value goes East
                }
            }
            if (heading == 'W') { //W means north. therefore a ship is placed in the horizontal direction to the right
                for (length; length > 0; length--) {
                    grid[i][x_cord-(length-1)] = '+'; //Subtracting the X values goes West
                }
            }
        }
    }
    draw_grid(1);
}

void board::draw_grid(int show_ships) { // This creates the grid by labeling axis and then coloring in coordinates based on their value
    char y_cords[] = { 'A','B','C','D','E','F','G','H','I','J' };
    cout << "  0 1 2 3 4 5 6 7 8 9" << endl; // X-cords
    for (int i = 0; i < 10; i++) {
        cout << y_cords[i] << " ";

        for (int j = 0; j < 10; j++) {
            if (grid[i][j] == 'X') { // X stands for hit
                cout << "\E[0;31m" << "\E[47m" << grid[i][j] << " " << "\E[0m";
            }
            if (grid[i][j] == '#') { // # stands for miss
                cout << "\E[0;31m" << "\E[44m" << grid[i][j] << " " << "\E[0m";
            }
            if (grid[i][j] == '+') { // + stands for there is a ship
                if (showShips == 1)
                    cout << "\E[1;37m" << "\E[47m" << grid[i][j] << " " << "\E[0m";
                else
                    cout << "\E[0;37m" << "\E[44m" << "0" << " " << "\E[0m";
            }
            if (grid[i][j] == '0') { // 0 stands for not hit, the default coordinate
                cout << "\E[0;37m" << "\E[44m" << grid[i][j] << " " << "\E[0m";
            }
        }
        cout << "\n";
    }
}


int Board::is_loser() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] == '+') {
                return 0;
            }
        }
    }

    return 1;
}


void board::random_place_ships(int length) { // this randomly places ships
    char heading;
    char y;
    char x;

    srand(time(NULL));

    char y_cords[10] = { 'A','B','C','D','E','F','G','H','I','J' };
    int RandY = rand() % 4;
    y = y_cords[RandY];

    char headings[4] = { 'N','E','S','W' };
    int RandIndex = rand() % 4;
    heading = headings[RandIndex];

    int index = rand() % 10;     //picks a value randomly  between 0 and 10    
    x = index;

    int y_cord;
    int x_cord = x - '0';

    for (int i = 0; i < 10; i++) {
        if (y_cords[i] == y) {
            grid[i][x_cord] = '+';


            if (heading == 'N') {
                //This 'draws' the full ship on the screen by drawing each square a specific length
                //away from the actual cordinates in a specific direction.
                for (length; length > 0; length--) {
                    grid[i - (length - 1)][x_cord] = '+'; //Subtracting the Y value goes North
                }
            }
            if (heading == 'E') {
                for (length; length > 0; length--) {
                    grid[i][x_cord + (length - 1)] = '+'; //Adding to the X value goes East
                }
            }
            if (heading == 'S') {
                for (length; length > 0; length--) {
                    grid[i + (length - 1)][x_cord] = '+'; //Adding to the Y value goes South
                }
            }
            if (heading == 'W') {
                for (length; length > 0; length--) {
                    grid[i][x_cord - (length - 1)] = '+'; //Subtracting the X values goes West
                }
            }
        }
    }
    draw_grid(1);
}







