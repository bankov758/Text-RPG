#include "Hero.h"

Hero::Hero()
{
	name = "";
	failures = 3;
	life_points = 100;
	sanity_power = 10;
	dodge_chance = 20;
	stash = {"health_potion", "health_potion", "boost_kit", "spell_book"};
}

string Hero::get_name()const
{
	return name;
}
int Hero::get_failures()const
{
	return failures;
}
double Hero::get_life_points()const
{
	return life_points;
}
double Hero::get_sanity_power()const
{
	return sanity_power;
}
double Hero::get_dodge_chance()const
{
	return dodge_chance;
}
list<string> Hero::get_stash()const
{
	return stash;
}

void Hero::set_name(string name1)
{
	this->name = name1;
}
void Hero::set_failures(int failures1)
{
	this->failures = failures1;
}
void Hero::set_life_points(double life_points1)
{
	this->life_points = life_points1;
}
void Hero::set_sanity_power(double sanity_power1)
{
	this->sanity_power = sanity_power1;
}
void Hero::set_dodge_chance(double dodge_chance1)
{
	this->dodge_chance = dodge_chance;
}
void Hero::set_stash(list<string> stash1)
{
	this->stash = stash1;
}
