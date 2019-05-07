/**
 * @file testLife.cpp
 * @author Nishanth Raveendran, raveendn
 * @brief Test cases for Life game board
 * 
 */
#include "catch.h"
#include "Life.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <stdexcept>

using namespace std;

/**
 * @brief Checks if two text files are equal
 * 
 * @param one first text file
 * @param two second text file
 * @return true if equal
 * @return false if not equal
 */
bool checkTxt(string one, string two) 
{
    vector<vector<string>> txt1, txt2;
    string line1, line2;
    ifstream file1(one);
    ifstream file2(two);

    if (file1.is_open()) {
        while (getline(file1, line1)) {
            istringstream iss(line1);
            vector<string> inputs{istream_iterator<string>{iss}, istream_iterator<string>{}};
            txt1.push_back(inputs);
        }
        file1.close();
    } else throw runtime_error("Could not find file");

    if (file2.is_open()) {
        while (getline(file2, line2)) {
            istringstream iss(line2);
            vector<string> inputs{istream_iterator<string>{iss}, istream_iterator<string>{}};
            txt2.push_back(inputs);
        }
        file2.close();
    } else throw runtime_error("Could not find file");

    for(int i=0; i < 20; i++) {
        for(int j=0; j < 20; j++) {
            if(txt1[i][j] != txt2[i][j]) return false;
        }
    }

    return true;
}


TEST_CASE("controller for Life", "[Life]") {
    //testing if initialization is successful
    SECTION("test initilize") {
        Life game1("test/test10_0.txt");
        REQUIRE(true);
    }

    //testing for exceptions for bad initialization
    SECTION("test initilize fail: nonexistent input") {
        REQUIRE_THROWS_AS(Life("nonexistent.txt"), runtime_error);
    }

    SECTION("test initilize fail: bad input") {
        REQUIRE_THROWS_AS(Life("test/bad.txt"), invalid_argument);
    }

    //testing successful write to text file
    SECTION("test writeOutput") {
        Life game1("test/test10_0.txt");
        game1.writeOutput("test/write.txt");
        REQUIRE(!checkTxt("test/write.txt", "test/test10_1.txt"));
        REQUIRE(checkTxt("test/write.txt", "test/test10_0.txt"));

        Life game2("test/test10_10.txt");
        game2.writeOutput("test/write2.txt");
        REQUIRE(!checkTxt("test/write2.txt", "test/test10_1.txt"));
        REQUIRE(checkTxt("test/write2.txt", "test/test10_10.txt"));
    }

    //testing for successful update of game board
    SECTION("test update/simulate") {
        Life game1("test/test10_0.txt");
        game1.update();
        game1.writeOutput("test/up1.txt");
        REQUIRE(checkTxt("test/up1.txt", "test/test10_1.txt"));
        game1.update();
        game1.writeOutput("test/up2.txt");
        REQUIRE(checkTxt("test/up2.txt", "test/test10_2.txt"));
        game1.simulate(8);
        game1.writeOutput("test/up10.txt");
        REQUIRE(checkTxt("test/up10.txt", "test/test10_10.txt"));
    }
}