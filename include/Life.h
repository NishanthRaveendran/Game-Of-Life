/**
 * @file Life.h
 * @author Nishanth Raveendran, raveendn
 * @brief Class for game of Life game board
 */
#ifndef A4_LIFE_H_
#define A4_LIFE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

/**
 * @brief game board of the Game of Life
 * 
 */
class Life
{
    private:
        vector<vector<bool>> Board;

        /**
         * @brief reads a textfile input to initialize the state of the board
         * 
         * @param txtfile Input textfile to initialize board
         */
        void readInput(string infile);

        /**
         * @brief checks if coordinates are in the gameboard
         * 
         * @param x row position
         * @param y column position
         * @return true if the coordinates are valid and in the board
         * @return false if the coordinates are not a valid position in the board
         */
        bool inBoard(int x, int y);

        /**
         * @brief provides the number of neighbours a cell has
         * 
         * @param x row position of the cell
         * @param y column position of the cell
         * @return int number of neighbours for the cell
         */
        int neighbours(int x, int y);

        /**
         * @brief returns the new state of a cell
         * 
         * @param x row position of cell
         * @param y column position of cell
         * @param s current state of cell (alive/dead)
         * @return true if the next state of the cell is alive
         * @return false if the next state of the cell is dead
         */
        bool updateCell(int x, int y, bool s);


      public:
        /**
         * @brief Construct a new Life object
         * 
         * @param txtfile input textfile to initialize board
         */
        Life(string txtfile);

        /**
         * @brief displays the state of the board using ASCII graphics
         * 
         */
        void display();

        /**
         * @brief Outputs the state of the board to a textfile
         * 
         * @param outfile desired textfile to output to
         */
        void writeOutput(string outfile);

        /**
         * @brief Updates the state of the board
         * 
         */
        void update();

        /**
         * @brief Updates the board for a number of rounds
         * 
         * @param n number of rounds
         */
        void simulate(int n);
};

#endif