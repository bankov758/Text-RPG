#pragma once
#include<list>
#include<string>

using namespace std;

class NPCs
{
public:
	NPCs();
	NPCs(string, bool, int, list<string>);

	string get_type()const;
	bool get_title()const;
	int get_attack_points()const;
	list<string> get_bonuses()const;

	void set_type(string type1);
	void set_title(bool title1);
	void set_attack_points(int attack_points1);
	void set_bonuses(list<string> bonuses1);

private:
	string type;
	bool title;        //true - monster leader, false - monster
	int attack_points;
	list<string> bonuses;
};
