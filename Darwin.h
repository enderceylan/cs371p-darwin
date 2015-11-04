#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <cstdlib>  // rand
#include <map>
#include <cstring>
#include <vector>

using namespace std;

class Species;
class Creature;
class Darwin;

class Species
{
    public:
        Species();
        Species(char c);
        void addInstruction(string inst);
        string& operator[] (int x);
        friend std::ostream& operator<<(std::ostream& out, const Species& s)
        {
            return out << s.symbol;
        }
    private:
        std::vector<string> program;
        int inst_count;
        char symbol;
};

class Creature
{
    public:
        Creature();
        Creature(Species s, int dir);
        bool isValid();
        void executeInstruction(Darwin* d, int x, int y);
        friend std::ostream& operator<<(std::ostream& out, const Creature& c)
        {
            return out << c.species;
        }
    private:
        std::pair<int, int> getNextLoc(int x, int y);
        Species species;
        int direction;
        int program_counter;
};

class Darwin 
{
    public:
        Darwin(int x, int y);
        void addCreature(Creature c, int x, int y);
        Creature begin(void);
        Creature end(void);
        Creature at(int x, int y);
        void executeTurn(void);
        void removeCreature(int x, int y);
        void printBoard(void);
        bool inBounds(int x, int y);
    private:
        std::vector<std::vector<Creature>> grid;
        int x_size;
        int y_size;
        int turn;
};

