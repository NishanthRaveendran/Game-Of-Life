/**
 * @file main.cpp
 * @author Nishanth Raveendran, raveendn
 * @brief experimenting for Life game board
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <stdexcept>

#include "Life.h"
using namespace std;

bool checkTxt(string one, string two)
{
    vector<vector<string>> txt1, txt2;
    string line1, line2;
    ifstream file1(one);
    ifstream file2(two);

    if (file1.is_open())
    {
        while (getline(file1, line1))
        {
            istringstream iss(line1);
            vector<string> inputs{istream_iterator<string>{iss}, istream_iterator<string>{}};
            txt1.push_back(inputs);
        }
        file1.close();
    }
    else
        throw runtime_error("Could not find file");

    if (file2.is_open())
    {
        while (getline(file2, line2))
        {
            istringstream iss(line2);
            vector<string> inputs{istream_iterator<string>{iss}, istream_iterator<string>{}};
            txt2.push_back(inputs);
        }
        file2.close();
    }
    else
        throw runtime_error("Could not find file");

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (txt1[i][j] != txt2[i][j])
                return false;
        }
    }

    return true;
}

int main()
{
    cout << "working .... \n";
    Life game1("experiment/test10_0.txt");
    Life game2("experiment/write.txt");
    game1.display();
    game2.display();
    game2.writeOutput("experiment/fresh.txt");
    game1.writeOutput("experiment/fre.txt");

    cout << "\n" << checkTxt("experiment/test10_0.txt", "experiment/write.txt") << "\n";
}