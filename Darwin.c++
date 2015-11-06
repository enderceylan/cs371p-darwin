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
#include <utility>  // make_std::pair, std::pair
#include <cstdlib>  // rand
#include <map>
#include <cstring>
#include <vector>

#include "Darwin.h"

using namespace std;

Darwin::Darwin(int x, int y)
{
    x_size = x;
    y_size = y;
    turn = 0;
    for (int i = 0; i < x_size; i++)
    {
        vector<Creature> temp;
        for (int j = 0; j < y_size; j++)
        {
            temp.push_back(Creature());
        }
        grid.push_back(temp);
    }
}

void Darwin::addCreature(Creature c, int x, int y)
{
    grid[x][y] = c;
}

void Darwin::removeCreature(int x, int y)
{
    grid[x][y] = Creature();
}

Creature Darwin::begin()
{
    return grid[0][0];
}

Creature Darwin::end()
{
    return grid[x_size-1][y_size-1];
}

void Darwin::executeTurn(void)
{
    for (int i = 0; i < x_size; i++)
    {
        for (int j = 0; j < y_size; j++)
        {
            if (grid[i][j].isValid(turn))
            {
                if (!grid[i][j].acted_upon(turn)) {
                    grid[i][j].executeInstruction(this, i, j);
                }
            }
        }
    }
    turn += 1;
}

Creature& Darwin::at(int x, int y)
{
    return grid[x][y];
}

void Darwin::printBoard(void)
{
    cout << "Turn = " << turn << "." << endl;
    cout << "  ";
    for (int i = 0; i < y_size; i++)
    {
        cout << (i % 10);
    }
    cout << endl;
    for (int k = 0; k < x_size; k++)
    {
        cout << (k % 10) << " ";
        for (int j = 0; j < y_size; j++)
        {
            if (!grid[k][j].isValid(turn))
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
}

bool Darwin::inBounds(int x, int y)
{
    if (x >= x_size || x < 0 || y >= y_size || y < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Darwin::repeat(int x, int y) {
    grid[x][y].goAgain();
}


// CREATURE

Creature::Creature(void)
{
    species = Species();
    direction = -1;
    program_counter = -1;
    turn_counter = -1;
}

Creature::Creature (const Creature& c) {
    species = Species(c.species);
    direction = c.direction;
    program_counter = c.program_counter;
    turn_counter = c.turn_counter;
}

Creature::Creature(Species s, int dir)
{
    species = s;
    direction = dir;  //0:west, 1:north, 2:east, 3:south.
    program_counter = 0;
    turn_counter = 0;
}

bool Creature::acted_upon(int turn) {
    if (turn_counter <= turn) {
        return false;
    }
    else {
        return true;
    }
}

bool Creature::isValid(int turn)
{
    if ((direction != -1) && (program_counter != -1)){
        return true;
    }
    else {
        return false;
    }
}


std::pair<int, int> Creature::getNextLoc(int x, int y)
{
    std::pair<int, int> newloc;
    if (direction % 4 == 0)
    {
        newloc.first = x;
        newloc.second = y - 1;
    }
    if (direction % 4 == 1)
    {
        newloc.first = x - 1;
        newloc.second = y;
    }
    if (direction % 4 == 2)
    {
        newloc.first = x;
        newloc.second = y + 1;
    }
    if (direction % 4 == 3)
    {
        newloc.first = x + 1;
        newloc.second = y;
    }
    return newloc;
}

void Creature::goAgain() {
    program_counter += 1;
    turn_counter -= 1;
}

void Creature::modify_creature(const Creature& c) {
    if (!species.is_equal(c.species)) {
        species = c.species;
        program_counter = 0;
    }
}

void Creature::executeInstruction(Darwin* d, int x, int y)
{
    turn_counter += 1;
    string inst = species[program_counter];
    if (inst.find("hop") != string::npos) 
    {
        std::pair<int, int> newloc = getNextLoc(x,y);
        if (d->inBounds(newloc.first,newloc.second))
        {
            d->addCreature(Creature(*this), newloc.first, newloc.second);
            d->removeCreature(x,y);
            (*d).repeat(newloc.first, newloc.second);
            d->at(newloc.first,newloc.second).executeInstruction(d,newloc.first, newloc.second);
        }
        else
        {
            d->at(x,y).goAgain();
            d->at(x,y).executeInstruction(d,x,y);
        }
    } 
    else if (inst.find("left") != string::npos) 
    {
        if (direction == 0)
        {
            direction = 3;
        }
        else
        {
            direction -= 1;
        }
        program_counter += 1;
        turn_counter -= 1;
        executeInstruction(d,x,y);
    }
    else if (inst.find("right") != string::npos) 
    {
        if (direction == 3)
        {
            direction = 0;
        }
        else
        {
            direction += 1;
        }
        program_counter += 1;
        turn_counter -= 1;
        executeInstruction(d,x,y);
    }
    else if (inst.find("infect") != string::npos) 
    {
        std::pair<int, int> newloc = getNextLoc(x,y);
        if (d->inBounds(newloc.first,newloc.second) && d->at(newloc.first,newloc.second).isValid(0))
        {   
            d->at(newloc.first, newloc.second).modify_creature(*this);
            program_counter += 1;
            turn_counter -= 1;
            executeInstruction(d,x,y);
        }
        else
        {
            program_counter += 1;
            turn_counter -= 1;
            executeInstruction(d,x,y);
        }
    }
    else if (inst.find("if_empty") != string::npos) 
    {
        std::pair<int, int> newloc = getNextLoc(x,y);
        string num = inst.substr(9);
        if (d->inBounds(newloc.first, newloc.second) && !d->at(newloc.first,newloc.second).isValid(0))
        {
            program_counter = (int)stoi(num);
            turn_counter -= 1;
            executeInstruction(d,x,y);
        }
        else
        {
            program_counter += 1;
            turn_counter -= 1;
            executeInstruction(d,x,y);
        }
    }
    else if (inst.find("if_wall") != string::npos) 
    {
        std::pair<int, int> newloc = getNextLoc(x,y);
        string num = inst.substr(8);
        if (!d->inBounds(newloc.first,newloc.second))
        {
            program_counter = (int)stoi(num);
            turn_counter -= 1;
            executeInstruction(d,x,y);
        }
        else
        {
            program_counter += 1;
            turn_counter -= 1;
            executeInstruction(d,x,y);
        }
    }
    else if (inst.find("if_random") != string::npos) 
    {
        int rand_num = rand();
        string num = inst.substr(10);
        if (rand_num % 2 == 1)
        {
            program_counter = (int)stoi(num);
            turn_counter -= 1;
            executeInstruction(d,x,y);
        }
        else
        {
            program_counter += 1;
            turn_counter -= 1;
            executeInstruction(d,x,y);
        }
    }
    else if (inst.find("if_enemy") != string::npos) 
    {
        std::pair<int, int> newloc = getNextLoc(x,y);
        string num = inst.substr(9);
        if (d->inBounds(newloc.first,newloc.second) && d->at(newloc.first,newloc.second).isValid(0) && !(species.is_equal(d->at(newloc.first, newloc.second).species)))
        {
            program_counter = (int)stoi(num);
            turn_counter -= 1;
            executeInstruction(d,x,y);
        }
        else
        {
            program_counter += 1;
            turn_counter -= 1;
            executeInstruction(d,x,y);
        }
    }
    else if (inst.find("go") != string::npos) 
    {
        string num = inst.substr(3);
        program_counter = (int)stoi(num);
    }
}



// SPECIES

Species::Species(void)
{
    symbol = '.';
    program = {};
}

Species::Species (const Species& s) {
    program = s.program;
    symbol = s.symbol;
}

Species::Species(char c)
{
    symbol = c;
    program = {};
}

void Species::addInstruction(string inst)
{
    program.push_back(inst);
}

string& Species::operator[] (int x)
{
    return program[x];
}

bool Species::is_equal(const Species& other) const{
    return symbol == other.symbol;
}