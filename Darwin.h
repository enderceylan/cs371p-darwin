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
        Species(const Species& s);
        void addInstruction(string inst);
        string& operator[] (int x);
        bool is_equal(const Species&) const;
        friend std::ostream& operator<<(std::ostream& out, const Species& s)
        {
            return out << s.symbol;
        }
    private:
        std::vector<string> program;
        char symbol;
};

class Creature
{
    public:
        Creature();
        Creature(Species s, int dir);
        Creature(const Creature& c);
        bool isValid();
        void executeInstruction(Darwin* d, int x, int y);
        bool acted_upon(int turn);
        void goAgain();
        void modify_creature(const Creature& c);
        friend std::ostream& operator<<(std::ostream& out, const Creature& c)
        {
            return out << c.species;
        }
    private:
        std::pair<int, int> getNextLoc(int x, int y);
        Species species;
        int direction;
        int program_counter;
        int turn_counter;
};

class Darwin 
{
    public:
        Darwin(int x, int y);
        void addCreature(Creature c, int x, int y);
        Creature begin(void);
        Creature end(void);
        Creature& at(int x, int y);
        void executeTurn(void);
        void removeCreature(int x, int y);
        void printBoard(void);
        bool inBounds(int x, int y);
        void repeat(int x, int y);
    private:
        std::vector<std::vector<Creature>> grid;
        int x_size;
        int y_size;
        int turn;
};

