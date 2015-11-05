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
    cout << c << endl;
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
    for (int j = 0; j < y_size; j++)
    {
        for (int i = 0; i < x_size; i++)
        {
            if (grid[i][j].isValid(turn))
            {
                //cout << i << " and " << j << "are valid" << endl;
                grid[i][j].executeInstruction(this, i, j);
            }
        }
    }
    turn += 1;
}

Creature Darwin::at(int x, int y)
{
    if (x >= x_size || y >= y_size)
    {
        return Creature();
    }
    else
    {
        return grid[x][y];
    }
}

void Darwin::printBoard(void)
{
    cout << "Turn = " << turn << "." << endl;
    cout << " ";
    for (int i = 0; i < x_size; i++)
    {
        cout << (i % 10);
    }
    cout << endl;
    for (int j = 0; j < y_size; j++)
    {
        cout << (j % 10);
        for (int k = 0; k < x_size; k++)
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
    cout << endl;
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

// CREATURE

Creature::Creature(void)
{
    species = Species();
    direction = -1;
    program_counter = -1;
    turn_counter = -1;
}

Creature::Creature(Species s, int dir)
{
    species = s;
    direction = dir;  //0:west, 1:north, 2:east, 3:south.
    program_counter = 0;
    turn_counter = 0;
}

bool Creature::isValid(int turn)
{
    return (direction != -1) && (program_counter != -1) && (turn_counter <= turn);
}

std::pair<int, int> Creature::getNextLoc(int x, int y)
{
    std::pair<int, int> newloc;
    if (direction % 4 == 0)
    {
        newloc.first = x - 1;
        newloc.second = y;
    }
    if (direction % 4 == 1)
    {
        newloc.first = x;
        newloc.second = y - 1;
    }
    if (direction % 4 == 2)
    {
        newloc.first = x + 1;
        newloc.second = y;
    }
    if (direction % 4 == 3)
    {
        newloc.first = x;
        newloc.second = y + 1;
    }
    return newloc;
}

void Creature::executeInstruction(Darwin* d, int x, int y)
{
    string inst = species[program_counter];
    if (inst.find("hop") != string::npos) 
    {
        cout << "Current x:" << x << " , Current y:" << y << endl;
        cout << direction << endl;
        std::pair<int, int> newloc = getNextLoc(x,y);
        if (d->inBounds(newloc.first,newloc.second))
        {
            cout << newloc.first << " " << newloc.second << endl;
            d->addCreature(*this, newloc.first, newloc.second);
            d->removeCreature(x,y);
        }
        program_counter += 1;
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
    }
    else if (inst.find("infect") != string::npos) 
    {
        std::pair<int, int> newloc = getNextLoc(x,y);
        if (d->inBounds(newloc.first,newloc.second) && d->at(newloc.first,newloc.second).isValid(0))
        {
            d->removeCreature(newloc.first, newloc.second);
            d->addCreature(Creature(species,direction), newloc.first, newloc.second);
            program_counter = 0;
        }
        else
        {
            program_counter += 1;
        }
    }
    else if (inst.find("if_empty") != string::npos) 
    {
        std::pair<int, int> newloc = getNextLoc(x,y);
        string num = inst.substr(9);
        if (!d->at(newloc.first,newloc.second).isValid(0))
        {
            program_counter = (int)stoi(num);
        }
        else
        {
            program_counter += 1;
        }

    }
    else if (inst.find("if_wall") != string::npos) 
    {
        std::pair<int, int> newloc = getNextLoc(x,y);
        string num = inst.substr(8);
        if (!d->inBounds(newloc.first,newloc.second))
        {
            program_counter = (int)stoi(num);
        }
        else
        {
            program_counter += 1;
        }
    }
    else if (inst.find("if_random") != string::npos) 
    {
        std::pair<int, int> newloc = getNextLoc(x,y);
        int rand_num = rand();
        string num = inst.substr(10);
        if (rand_num % 2 == 1)
        {
            program_counter = (int)stoi(num);
        }
        else
        {
            program_counter += 1;
        }
    }
    else if (inst.find("if_enemy") != string::npos) 
    {
        std::pair<int, int> newloc = getNextLoc(x,y);
        string num = inst.substr(9);
        if (d->inBounds(newloc.first,newloc.second) && d->at(newloc.first,newloc.second).isValid(0))
        {
            program_counter = (int)stoi(num);
        }
        else
        {
            program_counter += 1;
        }
    }
    else if (inst.find("go") != string::npos) 
    {
        std::pair<int, int> newloc = getNextLoc(x,y);
        string num = inst.substr(3);
        program_counter = (int)stoi(num);
    }
    turn_counter += 1;
}



// SPECIES

Species::Species(void)
{
    symbol = '.';
    program = {};
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