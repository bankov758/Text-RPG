#include "NPCs.h"

NPCs::NPCs()
{
	type = nullptr;
	title = false;
	attack_points = 0;
	bonuses = { "" };
}
NPCs::NPCs(string new_type, bool new_title, int new_attack_points, list<string> new_bonuses)
{
	this->type = new_type;
	this->title = new_title;
	this->attack_points = new_attack_points;
	this->bonuses = new_bonuses;
}

string NPCs::get_type()const
{
	return type;
}
bool NPCs::get_title()const
{
	return title;
}
int NPCs::get_attack_points()const
{
	return attack_points;
}
list<string> NPCs::get_bonuses()const
{
	return bonuses;
}

void NPCs::set_type(string type1)
{
	this->type = type1;
}
void NPCs::set_title(bool title1)
{
	this->title = title1;
}
void NPCs::set_attack_points(int attack_points1)
{
	this->attack_points = attack_points1;
}
void NPCs::set_bonuses(list<string> bonuses1)
{
	this->bonuses = bonuses1;
}
