#include <iostream> // cout, endl
#include <sstream>

#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

// ----
// Darwin
// ----

// ----
// constructor
// ----

TEST(Darwin_methods, constructor_1) {
	Darwin d = Darwin(1,5);
	for (int i = 0; i < 5; i++)
	{
		ASSERT_TRUE(d.inBounds(0,i));
	}
}


TEST(Darwin_methods, constructor_2) {
	Darwin d = Darwin(5,1);
	for (int i = 0; i < 5; i++)
	{
		ASSERT_TRUE(d.inBounds(i,0));
	}
}


TEST(Darwin_methods, constructor_3) {
	Darwin d = Darwin(5,5);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			ASSERT_TRUE(d.inBounds(i,j));
		}
	}
}

// ----
// addCreature
// ----

TEST(Darwin_methods, addCreature_1) {
	Darwin d = Darwin(3,3);
	Species s = Species('s');
	Creature c = Creature();
	ostringstream w;
	w << c;
	d.addCreature(c,0,0);
	ASSERT_EQ(w.str(),".");
}

TEST(Darwin_methods, addCreature_2) {
	Darwin d = Darwin(3,3);
	Species s = Species('s');
	Creature c = Creature(s,0);
	ostringstream w;
	w << c;
	d.addCreature(c,0,0);
	ASSERT_EQ(w.str(),"s");
}

TEST(Darwin_methods, addCreature_3) {
	Darwin d = Darwin(3,3);
	Species s = Species('s');
	Creature c = Creature(s,0);
	Creature a = Creature(c);
	ostringstream w;
	w << a;
	d.addCreature(a,0,0);
	ASSERT_EQ(w.str(),"s");
}

// ----
// at
// ----

TEST(Darwin_methods, at_1) {
	Darwin d = Darwin(3,3);
	Species s = Species('s');
	Creature c = Creature(s,0);
	d.addCreature(c,0,0);
	ostringstream w;
	w << d.at(0,0);
	ASSERT_EQ(w.str(),"s");
}

TEST(Darwin_methods, at_2) {
	Darwin d = Darwin(3,3);
	Species s = Species('a');
	Creature c = Creature(s,0);
	d.addCreature(c,1,1);
	ostringstream w;
	w << d.at(1,1);
	ASSERT_EQ(w.str(),"a");
}

TEST(Darwin_methods, at_3) {
	Darwin d = Darwin(3,3);
	Species s = Species('z');
	Creature c = Creature(s,0);
	d.addCreature(c,2,1);
	ostringstream w;
	w << d.at(2,1);
	ASSERT_EQ(w.str(),"z");
}

// ----
// executeTurn
// ----

TEST(Darwin_methods, executeTurn_1) {
	Darwin d = Darwin(3,3);
	Species s = Species('z');
	s.addInstruction("hop");
	s.addInstruction("go 0");
	Creature c = Creature(s,0);
	d.addCreature(c,2,1);
	d.executeTurn();
	ostringstream w;
	w << d.at(2,0);
	ASSERT_EQ(w.str(),"z");
}

TEST(Darwin_methods, executeTurn_2) {
	Darwin d = Darwin(3,3);
	Species s = Species('z');
	s.addInstruction("hop");
	s.addInstruction("go 0");
	Creature c = Creature(s,0);
	d.addCreature(c,2,2);
	d.executeTurn();
	ostringstream w;
	w << d.at(2,1);
	ASSERT_EQ(w.str(),"z");
}

TEST(Darwin_methods, executeTurn_3) {
	Darwin d = Darwin(3,3);
	Species s = Species('z');
	s.addInstruction("hop");
	s.addInstruction("go 0");
	Creature c = Creature(s,0);
	d.addCreature(c,1,1);
	d.executeTurn();
	ostringstream w;
	w << d.at(1,0);
	ASSERT_EQ(w.str(),"z");
}

// ----
// removeCreature
// ----

TEST(Darwin_methods, removeCreature_1) {
	Darwin d = Darwin(3,3);
	Species s = Species('s');
	Creature c = Creature(s,0);
	d.addCreature(c,0,0);
	d.removeCreature(0,0);
	ostringstream w;
	w << d.at(0,0);
	ASSERT_EQ(w.str(),".");
}

TEST(Darwin_methods, removeCreature_2) {
	Darwin d = Darwin(3,3);
	Species s = Species('s');
	Creature c = Creature(s,0);
	d.addCreature(c,0,1);
	d.removeCreature(0,1);
	ostringstream w;
	w << d.at(0,0);
	ASSERT_EQ(w.str(),".");
}

TEST(Darwin_methods, removeCreature_3) {
	Darwin d = Darwin(3,3);
	Species s = Species('s');
	Creature c = Creature(s,0);
	d.addCreature(c,2,0);
	d.removeCreature(2,0);
	ostringstream w;
	w << d.at(0,0);
	ASSERT_EQ(w.str(),".");
}

// ----
// inBounds
// ----

TEST(Darwin_methods, inBounds_1) {
	Darwin d = Darwin(1,5);
	for (int i = 0; i < 5; i++)
	{
		ASSERT_TRUE(d.inBounds(0,i));
	}
}


TEST(Darwin_methods, inBounds_2) {
	Darwin d = Darwin(5,1);
	for (int i = 0; i < 5; i++)
	{
		ASSERT_TRUE(d.inBounds(i,0));
	}
}


TEST(Darwin_methods, inBounds_3) {
	Darwin d = Darwin(5,5);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			ASSERT_TRUE(d.inBounds(i,j));
		}
	}
}


// ----
// Creature
// ----

// ----
// Empty Constructor
// ----

TEST(Creature_methods, empty_constructor_1) {
	Darwin d = Darwin(3,3);
	Species s = Species('s');
	Creature c = Creature();
	ostringstream w;
	w << c;
	d.addCreature(c,0,0);
	ASSERT_EQ(w.str(),".");
}

TEST(Creature_methods, empty_constructor_2) {
	Darwin d = Darwin(4,3);
	Species s = Species('s');
	Creature c = Creature();
	ostringstream w;
	w << c;
	d.addCreature(c,2,2);
	ASSERT_EQ(w.str(),".");
}

TEST(Creatureature_methods, empty_constructor_3) {
	Darwin d = Darwin(5,5);
	Species s = Species('s');
	Creature c = Creature();
	ostringstream w;
	w << c;
	d.addCreature(c,3,3);
	ASSERT_EQ(w.str(),".");
}

// ----
// Species Constructor
// ----

TEST(Creature_methods, species_constructor_1) {
	Darwin d = Darwin(3,3);
	Species s = Species('s');
	Creature c = Creature(s,0);
	Creature a = Creature(c);
	ostringstream w;
	w << a;
	d.addCreature(a,0,0);
	ASSERT_EQ(w.str(),"s");
}

TEST(Creature_methods, species_constructor_2) {
	Darwin d = Darwin(3,3);
	Species s = Species('s');
	Creature c = Creature(s,0);
	Creature a = Creature(c);
	ostringstream w;
	w << a;
	d.addCreature(a,2,0);
	ASSERT_EQ(w.str(),"s");
}

TEST(Creature_methods, species_constructor_3) {
	Darwin d = Darwin(3,3);
	Species s = Species('s');
	Creature c = Creature(s,0);
	Creature a = Creature(c);
	ostringstream w;
	w << a;
	d.addCreature(a,0,1);
	ASSERT_EQ(w.str(),"s");
}

// ----
// Copy Constructor
// ----

TEST(Creature_methods, copy_constructor_1) {
	Species s = Species('a');
	Creature c = Creature(s, 0);
	Creature x = Creature(c);

	ostringstream w;
	w << c;
	ASSERT_EQ("a", w.str());
}

TEST(Creature_methods, copy_constructor_2) {
	Species s = Species('a');
	Creature c = Creature();
	Creature x = Creature(s, 0);

	ostringstream y;
	y << x;
	ASSERT_EQ("a", y.str());
	x = Creature(c);

	ostringstream w;
	w << c;
	ASSERT_EQ(".", w.str());
}

TEST(Creature_methods, copy_constructor_3) {
	Creature c = Creature();
	Creature x = Creature(c);

	ostringstream w;
	w << c;
	ASSERT_EQ(".", w.str());
}

// ----
// isValid
// ----

TEST(Creature_methods, isValid_1) {
	Creature c = Creature();
	ASSERT_FALSE(c.isValid());
}

TEST(Creature_methods, isValid_2) {
	Species s('a');
	Creature a(s, 0);
	ASSERT_TRUE(a.isValid());
}

TEST(Creature_methods, isValid_3) {
	Species s('x');
	Creature a(s, 0);
	Creature x (a);
	ASSERT_TRUE(x.isValid());
}

// ----
// executeInstruction
// ----

TEST(Creature_methods, executeInstruction_1) {
	Darwin d = Darwin(3,3);
	Species s = Species('z');
	s.addInstruction("hop");
	s.addInstruction("go 0");
	Creature c = Creature(s,0);
	d.addCreature(c,2,1);
	d.executeTurn();
	ostringstream w;
	w << d.at(2,0);
	ASSERT_EQ(w.str(),"z");
}

TEST(Creature_methods, executeInstruction_2) {
	Darwin d = Darwin(3,3);
	Species s = Species('z');
	s.addInstruction("hop");
	s.addInstruction("go 0");
	Creature c = Creature(s,0);
	d.addCreature(c,2,2);
	d.executeTurn();
	ostringstream w;
	w << d.at(2,1);
	ASSERT_EQ(w.str(),"z");
}

TEST(Creature_methods, executeInstruction_3) {
	Darwin d = Darwin(3,3);
	Species s = Species('z');
	s.addInstruction("hop");
	s.addInstruction("go 0");
	Creature c = Creature(s,0);
	d.addCreature(c,1,1);
	d.executeTurn();
	ostringstream w;
	w << d.at(1,0);
	ASSERT_EQ(w.str(),"z");
}

// ----
// modify_creature
// ----

TEST(Creature_methods, modify_creature_1) {
	Species s = Species('a');
	Creature c = Creature(s, 0);

	Creature x = Creature();

	ostringstream t;
	t << x;
	ASSERT_EQ(".", t.str());

	x.modify_creature(c);
	ostringstream w;
	w << x;
	ASSERT_EQ("a", w.str());
}

TEST(Creature_methods, modify_creature_2) {
	Species h = Species('f');
	Creature c = Creature(h, 0);
	Species s = Species('a');
	Creature x = Creature(s, 0);

	ostringstream t;
	t << x;
	ASSERT_EQ("a", t.str());

	x.modify_creature(c);
	ostringstream w;
	w << x;
	ASSERT_EQ("f", w.str());
}

TEST(Creature_methods, modify_creature_3) {
	Creature c = Creature();
	Species s = Species('a');
	Creature x = Creature(s, 0);

	ostringstream t;
	t << x;
	ASSERT_EQ("a", t.str());

	x.modify_creature(c);
	ostringstream w;
	w << x;
	ASSERT_EQ(".", w.str());
}

// ----
// output operator
// ----

TEST(Creature_methods, output_operator_1) {
	Species s = Species();
	Creature c = Creature(s, 0);
	Creature x = Creature(c);
	ostringstream w;
	w << x;
	ASSERT_EQ(".", w.str());
}

TEST(Creature_methods, output_operator_2) {
	Species s = Species('a');
	Creature c = Creature(s, 0);
	ostringstream w;
	w << c;
	ASSERT_EQ("a", w.str());
}

TEST(Creature_methods, output_operator_3) {
	Creature c = Creature();
	ostringstream w;
	w << c;
	ASSERT_EQ(".", w.str());
}

// ----
// Species
// ----

// ----
// Empty Constructor
// ----

TEST(Species_methods, empty_constructor_1) {
	Species s = Species();
	Species x = Species();
	Species y = Species('a');
	ASSERT_TRUE(s.is_equal(x));
	ASSERT_FALSE(s.is_equal(y));
}

TEST(Species_methods, empty_constructor_2) {
	Species s = Species();
	Species x = Species();
	ASSERT_TRUE(s.is_equal(x));
}

TEST(Species_methods, empty_constructor_3) {
	Species s = Species();
	ostringstream w;
	w << s;
	ASSERT_EQ(".", w.str());
}

// ----
// char Constructor
// ----

TEST(Species_methods, char_constructor_1) {
	Species s = Species('s');
	ostringstream w;
	w << s;
	ASSERT_EQ("s", w.str());
}

TEST(Species_methods, char_constructor_2) {
	Species s = Species('t');
	Species x = Species('t');
	ASSERT_TRUE(s.is_equal(x));
}

TEST(Species_methods, char_constructor_3) {
	Species s = Species('w');
	ostringstream w;
	w << s;
	ASSERT_EQ("w", w.str());
}

// ----
// Copy Constructor
// ----

TEST(Species_methods, copy_constructor_1) {
	Species s = Species();
	Species t = Species(s);
	ASSERT_TRUE(s.is_equal(t));
}

TEST(Species_methods, copy_constructor_2) {
	Species s = Species('w');
	Species t = Species(s);
	ASSERT_TRUE(s.is_equal(t));
}

TEST(Species_methods, copy_constructor_3) {
	Species s = Species('2');
	Species t = Species(s);
	Species x = Species(t);
	ASSERT_TRUE(t.is_equal(x));
	ASSERT_TRUE(x.is_equal(s));
}

// ----
// addInstruction
// ----

TEST(Species_methods, addInstruction_1) {
	Species s = Species();
	s.addInstruction("one");
	ASSERT_EQ("one", s[0]);
}

TEST(Species_methods, addInstruction_2) {
	Species s = Species();
	s.addInstruction("one");
	s.addInstruction("two");
	s.addInstruction("three");
	ASSERT_EQ("two", s[1]);
}

TEST(Species_methods, addInstruction_3) {
	Species s = Species();
	s.addInstruction("one");
	s.addInstruction("two");
	s.addInstruction("three");
	s.addInstruction("one");
	s.addInstruction("two");
	s.addInstruction("three");
	ASSERT_EQ("three", s[5]);
}

// ----
// index operator
// ----

TEST(Species_methods, index_operator_1) {
	Species s = Species();
	s.addInstruction("one");
	ASSERT_EQ("one", s[0]);
}

TEST(Species_methods, index_operator_2) {
	Species s = Species();
	s.addInstruction("one");
	s.addInstruction("two");
	s.addInstruction("three");
	ASSERT_EQ("two", s[1]);
}

TEST(Species_methods, index_operator_3) {
	Species s = Species();
	s.addInstruction("one");
	s.addInstruction("two");
	s.addInstruction("three");
	s.addInstruction("one");
	s.addInstruction("two");
	s.addInstruction("three");
	ASSERT_EQ("three", s[5]);
}

// ----
// is_equal
// ----

TEST(Species_methods, is_equal_1) {
	Species s = Species();
	Species w = Species();
	ASSERT_TRUE(s.is_equal(w));
}

TEST(Species_methods, is_equal_2) {
	Species s = Species('s');
	Species w = Species('w');
	ASSERT_FALSE(s.is_equal(w));
}

TEST(Species_methods, is_equal_3) {
	Species s = Species('s');
	Species w = Species('s');
	ASSERT_TRUE(s.is_equal(w));
}

// ----
// output operator
// ----

TEST(Species_methods, output_operator_1) {
	Species s = Species('s');
	ostringstream w;
	w << s;
	ASSERT_EQ("s", w.str());
}

TEST(Species_methods, output_operator_2) {
	Species s = Species('w');
	ostringstream w;
	w << s;
	ASSERT_EQ("w", w.str());

}

TEST(Species_methods, output_operator_3) {
	Species s = Species();
	ostringstream w;
	w << s;
	ASSERT_EQ(".", w.str());
}