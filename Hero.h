#pragma once
#include<list>
#include<string>

using namespace std;

class Hero
{
public:
	Hero();

	string get_name()const;
	int get_failures()const;
	double get_life_points()const;
	double get_sanity_power()const;
	double get_dodge_chance()const;
	list<string> get_stash()const;

	void set_name(string name1);
	void set_failures(int failures1);
	void set_life_points(double life_points1);
	void set_sanity_power(double sanity_power1);
	void set_dodge_chance(double dodge_chance1);
	void set_stash(list<string> stash1);

private:
	string name;
	int failures;
	double life_points;
	double sanity_power;
	double dodge_chance;
	list<string> stash;
};
