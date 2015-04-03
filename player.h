#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Player
{
public:
    string name;
    int health;
    int damage;
    int attacks;
    int initiative;

    Player() 
    {}

    Player(Player& p)
    {
        name = p.name;
        health = p.health;
        damage = p.damage;
        attacks = p.attacks;
        initiative = p.initiative;
    }

    Player(int a, int b, int c, int d, string e)
    {
        health = a;
        damage = b;
        attacks = c;
        initiative = d;
        name = e;
    }

    void printPlayer()
    {
        cout<<"  Health:  "<<health<<endl;
        cout<<"  Damage:  "<<damage<<endl;
        cout<<"  Attacks:  "<<attacks<<endl;
    }
};


