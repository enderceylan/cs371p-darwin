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

// IMPLEMENTATIONS FOR DARWIN CLASS

/*
    Darwin::Darwin(int x, int y)
    Constructor for Darwin class. Initializes variables and full grid.
    Input: x is the height of the grid. y is the width of the grid.
    Output: n/a
*/
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

/*
    Darwin::addCreature(Creature c, int x, int y)
    Places a new Creature onto the grid.
    Input: c is the Creature to be placed on the grid. x and y are the coordinates
    where c will be placed.
    Output: n/a
*/
void Darwin::addCreature(Creature c, int x, int y)
{
    grid[x][y] = c;
}

/*
    Darwin::removeCreature(int x, int y)
    Removes a Creature from the grid.
    Input: x and y are the coordinates of the Creature that must be removed.
    Output: n/a
*/
void Darwin::removeCreature(int x, int y)
{
    grid[x][y] = Creature();
}

/*
    Darwin::begin()
    Outputs the first element of the grid.
    Input: n/a
    Output: Returns the first element of the grid.
*/
Creature Darwin::begin()
{
    return grid[0][0];
}

/*
    Darwin::end()
    Outputs the end of the grid.
    Input: n/a
    Output: Returns the end of the grid.
*/
Creature Darwin::end()
{
    return grid[x_size-1][y_size-1];
}

/*
    Darwin::executeTurn()
    Cycles through the entire grid and executes an instruction for each Creature in
    the grid, going from left to right, and from top to bottom.
    Input: n/a
    Output: n/a
*/
void Darwin::executeTurn(void)
{
    for (int i = 0; i < x_size; i++)
    {
        for (int j = 0; j < y_size; j++)
        {
            if (grid[i][j].isValid())
            {
                if (!grid[i][j].acted_upon(turn)) {
                    grid[i][j].executeInstruction(this, i, j);
                }
            }
        }
    }
    turn += 1;
}

/*
    Darwin::at(int x, int y)
    Returns the element that is at a specified location in the grid.
    Input: x and y are the coordinates in the grid of the element we want to retrieve.
    Output: Returns the Creature at the specified location.
*/
Creature& Darwin::at(int x, int y)
{
    return grid[x][y];
}

/*
    Darwin::printBoard()
    Prints the current status of the grid.
    Input: n/a
    Output: n/a
*/
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
            if (!grid[k][j].isValid())
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

/*
    Darwin::inBounds(int x, int y)
    Checks to see whether the given location is within the bounds of the grid.
    Input: x and y are the coordinates of the location we want to check.
    Output: Returns true is location is valid, false otherwise.
*/
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

/*
    Darwin::repeat(int x, int y)
    Prompts the Creature at the given location to repeat its turn.
    Input: x and y are the coordinates of the Creature we want to repeat its turn.
    Output: n/a
*/
void Darwin::repeat(int x, int y) {
    grid[x][y].goAgain();
}


// IMPLEMENTATIONS FOR CREATURE CLASS

/*
    Creature::Creature()
    Empty constructor for Creature class. Should be used to represent blank spaces.
    Input: n/a
    Output: n/a
*/
Creature::Creature(void)
{
    species = Species();
    direction = -1;
    program_counter = -1;
    turn_counter = -1;
}

/*
    Creature::Creature(const Creature& c)
    Copy constructor for Creature class. Should be used to peform a deep copy 
    on Creatures.
    Input: c is the Creature to be copied.
    Output: n/a
*/
Creature::Creature (const Creature& c) {
    species = Species(c.species);
    direction = c.direction;
    program_counter = c.program_counter;
    turn_counter = c.turn_counter;
}

/*
    Creature::Creature(Species s, int dir)
    Regular constructor for Creature that initializes variables.
    Input: s is the Creature's Species. dir is the Creature's direction.
    Output: n/a
*/
Creature::Creature(Species s, int dir)
{
    species = s;
    direction = dir;  //0:west, 1:north, 2:east, 3:south.
    program_counter = 0;
    turn_counter = 0;
}

/*
    Creature::acted_upon(int turn)
    Checks to see if the Creature has already fully executed its turn.
    Input: turn is the current turn on the grid.
    Output: Returns true if Creature has already acted on its turn, false otherwise.
*/
bool Creature::acted_upon(int turn) {
    if (turn_counter <= turn) {
        return false;
    }
    else {
        return true;
    }
}

/*
    Creature::isValid()
    Checks to see if the Creature is not representing a blank space.
    Input: n/a
    Output: Returns true if Creature is not blank space, false otherwise.
*/
bool Creature::isValid()
{
    if ((direction != -1) && (program_counter != -1)){
        return true;
    }
    else {
        return false;
    }
}

/*
    Creature::getNextLoc(int x, int y)
    Gets the next location in the Creature's current direction.
    Input: x and y are the Creature's current location.
    Output: Returns a set of coordinates of what the Creature's next location would be.
*/
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

/*
    Creature::goAgain()
    Prompts the Creature to reset its turn counter to execute another instruction.
    Input: n/a
    Output: n/a
*/
void Creature::goAgain() {
    program_counter += 1;
    turn_counter -= 1;
}

/*
    Creature::modify_creature(const Creature& c)
    Modifies the Creature's species in case of infection.
    Input: c is the Creature that is infecting the current Creature.
    Output: n/a
*/
void Creature::modify_creature(const Creature& c) {
    if (!species.is_equal(c.species)) {
        species = c.species;
        program_counter = 0;
    }
}

/*
    Creature::executeInstruction(Darwin* d, int x, int y)
    Executes the next instruction in the program counter.
    Input: d is the current Darwin grid. x and y are the Creature's current location.
    Output: n/a
*/
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
        if (d->inBounds(newloc.first,newloc.second) && d->at(newloc.first,newloc.second).isValid())
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
        if (d->inBounds(newloc.first, newloc.second) && !d->at(newloc.first,newloc.second).isValid())
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
        if (d->inBounds(newloc.first,newloc.second) && d->at(newloc.first,newloc.second).isValid() && !(species.is_equal(d->at(newloc.first, newloc.second).species)))
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

// IMPLEMENTATIONS FOR SPECIES CLASS

/*
    Species::Species()
    Empty constructor for Species class. Should be used to represent blank spaces.
    Input: n/a
    Output: n/a
*/
Species::Species(void)
{
    symbol = '.';
    program = {};
}

/*
    Species::Species(const Species& s)
    Copy constructor for Species class. Should be used to peform a deep copy on Species.
    Input: s is the Species to be copied.
    Output: n/a
*/
Species::Species (const Species& s) {
    program = s.program;
    symbol = s.symbol;
}

/*
    Species::Species(char c)
    Regular constructor for Species that initializes variables.
    Input: c is the character that will represent the Species on the grid.
    Output: n/a
*/
Species::Species(char c)
{
    symbol = c;
    program = {};
}

/*
    Species::addInstruction(string inst)
    Adds an instruction to the program.
    Input: inst is the instruction to be added to the program.
    Output: n/a
*/
void Species::addInstruction(string inst)
{
    program.push_back(inst);
}

/*
    Species::operator[] (int x)
    Indexing operator for Species program.
    Input: x is the number of the instruction to be retrieved.
    Output: Returns the requested instruction from the program.
*/
string& Species::operator[] (int x)
{
    return program[x];
}

/*
    Species::is_equal(const Species& other)
    Checks to see if two instances of Species are of equal types.
    Input: other is the other instance of Species to be compared.
    Output: Returns true if they are of the same type, false
*/
bool Species::is_equal(const Species& other) const{
    return symbol == other.symbol;
}