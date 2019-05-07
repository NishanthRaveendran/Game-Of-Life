/**
 * @file Life.cpp
 * @author Nishanth Raveendran, raveendn
 * @brief Class for game of Life game board
 */
#include "Life.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <stdexcept>
using namespace std;

Life::Life(string txtfile)
{
    for (int i = 0; i < 20; i++) {
        vector<bool> row;
        for (int j = 0; j < 20; j++) {
            row.push_back(false);
        }
        Board.push_back(row);
    }

    readInput(txtfile);
}

void Life::display()
{
    cout << "================================================================\n";
    for (int i = 0; i < 20; i++) {
        cout << "||";
        for (int j = 0; j < 20; j++) {
            if(Board[i][j]) cout << " \u25A0 ";
            else cout << " \u25A1 ";
        }
        cout << "||\n";
    }
    cout << "================================================================\n";
}

void Life::writeOutput(string outfile)
{
    ofstream myfile;
    myfile.open(outfile);

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (Board[i][j]) myfile << "1  ";
            else myfile << "0  ";
        }
        myfile << "\n";
    }
    myfile.close();
}

void Life::update()
{
    ofstream myfile;
    myfile.open("output.txt");

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (updateCell(i, j, Board[i][j])) myfile << "1  ";
            else myfile << "0  ";
            
        }
        myfile << "\n";
    }
    myfile.close();

    readInput("output.txt");   
}

void Life::simulate(int n)
{
    for(int i=0; i < n; i++) update();
}


//local functions
void Life::readInput(string infile)
{
    string line;
    ifstream myfile(infile);

    if (myfile.is_open())
    {
        int i = 0;
        while (getline(myfile, line))
        {
            istringstream iss(line);
            vector<string> inputs{istream_iterator<string>{iss}, istream_iterator<string>{}};

            if(inputs.size() != 20) throw invalid_argument("invalid number of columns, must be 20");
 
            for(int j=0; j < 20; j++) {
                if (inputs[j] != "1" && inputs[j] != "0") throw invalid_argument("invalid input, must be 1s and 0s");
                if (i > 19) throw invalid_argument("invalid number of rows, must be 20");
                if(inputs[j] == "1") Board[i][j] = true;
                else Board[i][j] = false;
            }
            i++;
        }
        myfile.close();
    } else {
        throw runtime_error("Could not find file");
    }
}

bool Life::inBoard(int x, int y)
{
    if (x >= 0 && x < 20 && y >= 0 && y < 20) return true;
    return false;
}

int Life::neighbours(int x, int y)
{
    int n = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (inBoard(x+i, y+j) && !(i == 0 && j == 0)) {
                if (Board[x+i][y+j]) n++;
            }
        }
    }
    return n;
}

bool Life::updateCell(int x, int y, bool s)
{
    if (s) {
        if (neighbours(x, y) == 2 || neighbours(x, y) == 3) return true;
        else return false;
    } else {
        if (neighbours(x, y) == 3) return true;
        else return false;
    }
}