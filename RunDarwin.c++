// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    Species food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    Species hopper('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    Species rover('r');
    rover.addInstruction("if_enemy 9");
    rover.addInstruction("if_empty 7");
    rover.addInstruction("if_random 5");
    rover.addInstruction("left");
    rover.addInstruction("go 0");
    rover.addInstruction("right");
    rover.addInstruction("go 0");
    rover.addInstruction("hop");
    rover.addInstruction("go 0");
    rover.addInstruction("infect");
    rover.addInstruction("go 0");

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    Species trap('t');
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    // -----
    // best
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    Species best('b');
    best.addInstruction("if_enemy 9");
    best.addInstruction("if_empty 7");
    best.addInstruction("if_random 5");
    best.addInstruction("left");
    best.addInstruction("go 0");
    best.addInstruction("right");
    best.addInstruction("go 0");
    best.addInstruction("hop");
    best.addInstruction("go 0");
    best.addInstruction("infect");
    best.addInstruction("go 0");

    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    srand(0);
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */

    //0:west, 1:north, 2:east, 3:south.

    Darwin map1(8,8);
    Creature a1(food, 2);
    map1.addCreature(a1, 0, 0);
    Creature a2(hopper, 1);
    map1.addCreature(a2, 3, 3);
    Creature a3(hopper, 2);
    map1.addCreature(a3, 3, 4);
    Creature a4(hopper, 3);
    map1.addCreature(a4, 4, 4);
    Creature a5(hopper, 0);
    map1.addCreature(a5, 4, 3);
    Creature a6(food, 1);
    map1.addCreature(a6, 7, 7);

    for (int i = 0; i <= 5; i++)
    {
        map1.printBoard();
        map1.executeTurn();
        cout << endl;
    }

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    /*
    7x9 Darwin 
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */

    Darwin map2(7,9);
    Creature b1(trap, 3);
    map2.addCreature(b1, 0, 0);
    Creature b2(hopper, 2);
    map2.addCreature(b2, 3, 2);
    Creature b3(rover, 1);
    map2.addCreature(b3, 5, 4);
    Creature b4(trap, 0);
    map2.addCreature(b4, 6, 8);

    for (int i = 0; i <= 5; i++)
    {
        map2.printBoard();
        map2.executeTurn();
        cout << endl;
    }

    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    Darwin map3(72,72);
    for (int i = 0; i < 10; i++)
    {
        int position = rand()%5184;
        int direction = rand()%4;
        map3.addCreature(Creature(food, direction), position/72, position-72*(position/72));
    }
    for (int i = 0; i < 10; i++)
    {
        int position = rand()%5184;
        int direction = rand()%4;
        map3.addCreature(Creature(hopper, direction), position/72, position-72*(position/72));
    }
    for (int i = 0; i < 10; i++)
    {
        int position = rand()%5184;
        int direction = rand()%4;
        map3.addCreature(Creature(rover, direction), position/72, position-72*(position/72));
    }
    for (int i = 0; i < 10; i++)
    {
        int position = rand()%5184;
        int direction = rand()%4;
        map3.addCreature(Creature(trap, direction), position/72, position-72*(position/72));
    }
    for (int i = 0; i <= 1000; i++)
    {
        if (i <= 10 || i % 100 == 0)
        {
            map3.printBoard();
            cout << endl;
        }
        map3.executeTurn();
    }

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    Darwin map4(72,72);
    for (int i = 0; i < 10; i++)
    {
        int position = rand()%5184;
        int direction = rand()%4;
        map4.addCreature(Creature(food, direction), position/72, position-72*(position/72));
    }
    for (int i = 0; i < 10; i++)
    {
        int position = rand()%5184;
        int direction = rand()%4;
        map4.addCreature(Creature(hopper, direction), position/72, position-72*(position/72));
    }
    for (int i = 0; i < 10; i++)
    {
        int position = rand()%5184;
        int direction = rand()%4;
        map4.addCreature(Creature(rover, direction), position/72, position-72*(position/72));
    }
    for (int i = 0; i < 10; i++)
    {
        int position = rand()%5184;
        int direction = rand()%4;
        map4.addCreature(Creature(trap, direction), position/72, position-72*(position/72));
    }
    for (int i = 0; i < 10; i++)
    {
        int position = rand()%5184;
        int direction = rand()%4;
        map4.addCreature(Creature(best, direction), position/72, position-72*(position/72));
    }
    for (int i = 0; i <= 1000; i++)
    {
        if (i <= 10 || i % 100 == 0)
        {
            map4.printBoard();
            if (i != 1000)
                cout << endl;
        }
       map4.executeTurn();
    }

    return 0;}