// ----------------------------
// projects/darwin/Darwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <map>

#include "Darwin.h"

using namespace std;

class Species
{
    public:
        Species(char c);
        void addInstruction(string inst);
        std::ostream& Species::operator<<(std::ostream& out, const Species& s);
    private:
        vector<string> program;
        char symbol;
};

class Creature
{
    public:
        Creature(Species s);
        void executeInstruction(void);
        std::ostream& Creature::operator<<(std::ostream& out, const Creature& s)
    private:
        Species species;
        uint16_t direction;
        uint16_t program_counter;
};

class Darwin 
{
    public:
        Darwin(uint16_t x, uint16_t y);
        void addCreature(Creature c, uint16_t x, uint16_t y);
        Creature* begin(void);
        Creature* end(void);
        Creature* at(uint16_t x, uint16_t y);
        void printBoard(void);
    private:
        vector<vector<Creature>> grid;
        uint16_t x_size;
        uint16_t y_size;
        uint16_t turn;
};

Darwin::Darwin(uint16_t x, uint16_t y)
{
    x_size = x;
    y_size = y;
    turn = 0;
}

void Darwin::addCreature(Creature c, uint16_t x, uint16_t y)
{
    grid[x][y] = c;
}

void Darwin::printBoard(void)
{
    cout << "Turn = " << turn << "." << endl;
    cout << "  ";
    for (int i = 0; i < x_size; i++)
    {
        cout << i;
    }
    cout << endl;
    for (int j = 0; j < y_size; j++)
    {
        cout << j;
        for (int k = 0; k < x_size; k++)
        {
            if (grid[k][j] == NULL)
            {
                cout << ".";
            }
            else
            {
                cout << grid[k][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

Creature::Creature(Species s)
{
    species = s;
    direction = 0;
    program_counter = 0;
}

std::ostream& Creature::operator<<(std::ostream& out, const Creature& c){
   return out << c.species;
}

Species::Species(char c)
{
    symbol = c;
}

std::ostream& Species::operator<<(std::ostream& out, const Species& s){
   return out << s.symbol;
}