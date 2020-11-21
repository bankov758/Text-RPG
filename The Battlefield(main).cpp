#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <queue>
#include <list>
#include "Hero.h"
#include "NPCs.h"

#pragma warning(disable : 4996) //for strcpy()

using namespace std;

void fill_map(list<queue<string>>& newlist)
{
	ifstream read; 
	read.open("map.txt"); 
	string input;  
	while (1)
	{
		if (newlist.size() == 5) //one entry is 5 days
		{
			break;
		}
		queue<string> day; 
		while (read >> input) 
		{
			if (input == "NEWDAY") 
			{
				day.push(input);
				break;
			}
			day.push(input);
		}

		newlist.push_back(day); 

		while (!day.empty())  
		{
			day.pop();
		}
	}
}

int randomNum(int min, int max) //range : [min, max)
{
	static bool first = true;  // we use static because we need "first" to be true only the first time to put the seed
	if (first)				   // then we use the changed to false variable
	{
		srand(time(NULL));
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

void enter_round(Hero& hero, NPCs attacker)
{
	cout << hero.get_name() << " enters the " << attacker.get_type() << " lair." << endl;
	if (attacker.get_title())
	{
		cout << "The " << attacker.get_type() << " attacks." << endl;
	}
	else
	{
		cout << "The " << attacker.get_type() << " attacks." << endl;
	}

	int i = 0;
	while (i < 4) // every battle is 4 rounds 
	{
		double damage;
		double p1, p2; 
		double chance = (double)randomNum(1, 101); 

		if (attacker.get_title()) 
		{
			p1 = (double)randomNum(80, 101) / 100;
		}
		else 
		{
			p1 = (double)randomNum(60, 101) / 100;
		}

		p2 = (double)randomNum(40, 101) / 100;

		if (chance < hero.get_dodge_chance())
		{
			cout << hero.get_name() << " dodges the attack." << endl;
			damage = (p1 - 0.25) * attacker.get_attack_points() - p2 * hero.get_sanity_power(); 
			if (damage < 0)
			{
				damage = 0;  //if sanity power becomes too much 
			}
		}
		else
		{
			cout << hero.get_name() << " doesn't dodge the attack." << endl;
			damage = p1 * attacker.get_attack_points() - p2 * hero.get_sanity_power(); 
			if (damage < 0)
			{
				damage = 0;
			}
		}

		cout << "The damage dealt is " << damage << endl;
		hero.set_life_points(hero.get_life_points() - damage);
		i++;
	}

	// HEROES' BONUSES
	if (hero.get_life_points() > 0)
	{
		list<string> bonuses = attacker.get_bonuses(); 
		list<string>::iterator i = bonuses.begin();			  
		while (i != bonuses.end())                            
		{
			string s = *i;
			char* bonus = new char[s.length() + 1];  
			strcpy(bonus, s.c_str());

			char num[3];
			int k = 0;
			for (int t = 0; t < strlen(bonus); t++)  
			{
				if (isdigit(bonus[t]))
				{
					num[k] = bonus[t];
					k++;
				}
			}

			int j = 0;
			int n = 0;
			while (num[j] - '0' > -1 && num[j] - '0' < 10)  
			{
				n = (num[j] - '0') + (n * 10);
				j++;
			}

			
			if (bonus[0] == 'S')
			{
				hero.set_sanity_power(hero.get_sanity_power() + (double)n);
			}
			if (bonus[0] == 'L')
			{
				hero.set_life_points(hero.get_life_points() + (double)n);
			}
			if (bonus[0] == 'D')
			{
				hero.set_dodge_chance(hero.get_dodge_chance() + ((double)n / 100));
			}

			i++;
		}
	}
}



bool itemPossession(string item, list<string> stash)
{
	list<string>::iterator i = stash.begin();  
	while (i != stash.end())				 
	{
		if (*i == item)
		{
			return true;       
		}
		i++;
	}

	return false; 
}

void print_Slist(list<string> List)
{
	cout << "Stash: " << endl;
	list<string>::iterator i = List.begin();  
	while (i != List.end())
	{
		cout << *i << endl;
		cout << endl;
		i++;
	}
}

void using_actions(Hero& hero, int numOfactions)
{
	int choice;
	while (numOfactions > 0)
	{
		cout << "Available actions: " << numOfactions << endl;
		cout << "Choose an option:" << endl
			<< "1 -> Meditation (-1 action, +5 LP)" << endl
			<< "2 -> Use an item from the stash (-1 action)" << endl
			<< "3 -> Eating (-2 actions, +15 LP)" << endl
			<< "4 -> Eavesdropping on a group of magicians (-2 actions, +1.5% dodge chance)" << endl
			<< "5 -> Health potion purchase (-2 actions, +3 health potions)" << endl
			<< "6 -> Taking a nap (-3 actions, +20 LP)" << endl
			<< "7 -> Learning a spell (-3 actions, +4 sanity power, +0.5% dodge chance)" << endl;
		do
		{									
			cin >> choice;
		} while (choice < 1 && choice > 7);

		if (choice == 1)
		{
			hero.set_life_points(hero.get_life_points() + 5);						
			cout << hero.get_name() << " chose to meditate and regained 5 LP."		
				<< hero.get_name() << "'s LP are " << hero.get_life_points() << endl;
			numOfactions = numOfactions - 1;			
		}
		if (choice == 2)
		{
			string item;
			print_Slist(hero.get_stash());  
			cout << "Choose an item: ";
			cin >> item;  

			if (itemPossession(item, hero.get_stash())) 
			{
				if (item == "health_potion")
				{
					hero.set_life_points(hero.get_life_points() + 9); 
					list<string> newStash1 = hero.get_stash(); 

					list<string>::iterator i = newStash1.begin(); 
					while (i != newStash1.end())				  
					{											  
						if (*i == "health_potion")					  
						{
							newStash1.erase(i);
							break;
						}
						i++;
					}

					hero.set_stash(newStash1); 
					cout << hero.get_name() << " drank a health potion and gained 9 LP." 
						<< hero.get_name() << "'s LP are " << hero.get_life_points() << endl;
				}
				if (item == "spell_book") 
				{
					hero.set_sanity_power(hero.get_sanity_power() + 2);
					hero.set_dodge_chance(hero.get_dodge_chance() + 0.2);
					list<string> newStash2 = hero.get_stash();
					newStash2.remove("spell_book");                

					cout << hero.get_name() << " read a spell book and gained 2 sanity power and 0.2% dodge chance."
						<< hero.get_name() << "'s sanity power is " << hero.get_sanity_power()
						<< " and dodge chance " << hero.get_dodge_chance() << endl;
					hero.set_stash(newStash2);
				}
				if (item == "boost_kit")
				{
					hero.set_life_points(hero.get_life_points() + 6);
					hero.set_sanity_power(hero.get_sanity_power() + 2);
					list<string> newStash3 = hero.get_stash();
					newStash3.remove("boost_kit");            

					cout << hero.get_name() << " used a boost kit and gained 6 LP and 2 sanity power."
						<< hero.get_name() << "'s sanity power is " << hero.get_sanity_power()
						<< " and LP are " << hero.get_life_points() << endl;
					hero.set_stash(newStash3);
				}
				numOfactions = numOfactions - 1; 
			}
			else
			{
				cout << "You do not possess this item !" << endl; 
			}
		}
		if (choice == 3)
		{
			if (numOfactions < 2) 
			{
				cout << "Not enaugh actions for this choice!!" << endl;
				continue;
			}
			cout << hero.get_name() << " chose to eat and regained 15 LP" << endl;
			hero.set_life_points(hero.get_life_points() + 15);
			cout << hero.get_name() << "'s LP are " << hero.get_life_points() << endl;
			numOfactions = numOfactions - 2;
		}
		if (choice == 4)
		{
			if (numOfactions < 2)
			{
				cout << "Not enaugh actions for this choice!!" << endl;
				continue;
			}
			hero.set_dodge_chance(hero.get_dodge_chance() + 1.5);
			cout << hero.get_name() << " chose to eavesdrop on a group of magicians and gained 1.5% dodge chance."
				<< hero.get_name() << "'s dodge chance is " << hero.get_dodge_chance() << endl;
			numOfactions = numOfactions - 2;
		}
		if (choice == 5)
		{
			if (numOfactions < 2)										
			{														
				cout << "Not enaugh actions for this choice!!" << endl;  
				continue;												
			}															
			list<string> newStash = hero.get_stash();  
			newStash.push_back("health_potion");
			newStash.push_back("health_potion");
			newStash.push_back("health_potion");
			hero.set_stash(newStash);      
			cout << hero.get_name() << " chose to buy 3 health potions"
				<< hero.get_name() << " has " << hero.get_stash().size() << " items." << endl;
			numOfactions = numOfactions - 2;
		}
		if (choice == 6)
		{
			if (numOfactions < 3)
			{
				cout << "Not enaugh actions for this choice!!" << endl;
				continue;
			}
			hero.set_life_points(hero.get_life_points() + 20);
			cout << hero.get_name() << " chose to take a nap and gained 20 LP."
				<< hero.get_name() << "'s LP are " << hero.get_life_points() << endl;
			numOfactions = numOfactions - 3;
		}
		if (choice == 7)
		{
			if (numOfactions < 3)
			{
				cout << "Not enaugh actions for this choice!!" << endl;
				continue;
			}
			hero.set_sanity_power(hero.get_sanity_power() + 4);
			hero.set_dodge_chance(hero.get_dodge_chance() + 0.5);
			cout << hero.get_name() << " chose to learn a spell and gained 4 sanity power and 0.5% dodge chance."
				<< hero.get_name() << "'s sanity power is " << hero.get_sanity_power()
				<< " and dodge chance is " << hero.get_dodge_chance() << endl;
			numOfactions = numOfactions - 3;
		}
	}
}

int main()
{
	list<queue<string>> week; 
	fill_map(week);

	Hero hero;
	string s_name;
	cout << "Nickname: ";
	getline(cin, s_name);
	hero.set_name(s_name);

	int record = 0;   //the number of enemies the hero slayed

				// S->sanity power, L->life points, D->dodge chance(x*100)
	NPCs fire_monster("fire monster", false, 21, { "S +1", "L +5", "D +5" });
	NPCs fire_monster_leader("fire monsters' leader", true, 29, { "S +2", "LP +3", "D +10" });

	NPCs water_monster("water monster", false, 21, { "S +2", "L +4", "Q +7" });
	NPCs water_monster_leader("water monsters' leader", true, 23, { "S +2", "L +3", "D +20" });

	NPCs earth_monster("earth monster", false, 20, { "S +2", "L +3", "D +20" });
	NPCs earth_monster_leader("earth monsters' leader", true, 25, { "S +1", "L +5", "D +1" });

	cout << hero.get_name() << " starts a new day..." << endl;
	while (hero.get_failures() > 0)
	{
		list<queue<string>>::iterator i = week.begin();
		while (i != week.end()) 
		{
			queue<string> day = *i; 
			while (!day.empty())    
			{
				if (hero.get_life_points() <= 0)
				{
					cout << hero.get_name() << " is defeated and goes home." << endl;
					cout << hero.get_name() << " will be back tomorrow with 60% LP." << endl;
					hero.set_failures(hero.get_failures() - 1);
					cout << "Remaining failures: " << hero.get_failures() << endl << endl;
					hero.set_life_points(60); //60% of 100 = 60

					while (!day.empty())  //skips the rest of the day
					{
						day.pop();
					}
					break;
				}

				if (hero.get_failures() <= 0)
				{
					break;
				}
											
				if (day.front() == "traveler's_inn")
				{
					cout << endl;
					cout << hero.get_name() << " sleeps in a traveler's inn." << endl;
					using_actions(hero, 4);
					day.pop();
				}
				if (day.front() == "tavern")
				{
					cout << endl;
					cout << hero.get_name() << " drinks in a tavern." << endl;
					using_actions(hero, 2);
					day.pop();
				}
				if (day.front() == "a_place_to_rest")
				{
					cout << endl;
					cout << hero.get_name() << " finds a place to rest." << endl;
					using_actions(hero, 1);
					day.pop();
				}
				if (day.front() == "NEWDAY")
				{
					cout << endl;
					cout << hero.get_name() << " starts a new day..." << endl;
					day.pop();
				}
				else                                                        
				{                                                           
					if (day.front() == "swamp(boss)")
					{
						enter_round(hero, water_monster_leader);
						record++;
						day.pop();
					}
					if (day.front() == "swamp(monster)")
					{
						enter_round(hero, water_monster);
						record++;
						day.pop();
					}
					if (day.front() == "dragon's_nest(boss)")
					{
						enter_round(hero, fire_monster_leader);
						record++;
						day.pop();
					}
					if (day.front() == "dragon's_nest(monster)")
					{
						enter_round(hero, fire_monster);
						record++;
						day.pop();
					}
					if (day.front() == "troll's_cave(boss)")
					{
						enter_round(hero, earth_monster_leader);
						record++;
						day.pop();
					}
					if (day.front() == "troll's_cave(monster)")
					{
						enter_round(hero, earth_monster);
						record++;
						day.pop();
					}
				}
			}

			i++;
		}
	}

	cout << hero.get_name() << " slayed " << record << " enemies !!" << endl;

	return 0;
}
