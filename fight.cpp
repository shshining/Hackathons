#include "player.h"
#include "csvrow.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;


string Trim(string& str)
{
    str.erase(0,str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
    return str;
}

string fight(Player p1, Player p2)
{
    cout<<"Candidate 1:"<<endl;
    p1.printPlayer();
    cout<<endl;
    cout<<"Candidate 2:"<<endl;
    p2.printPlayer();
    
    int fround = 1;
    int symbol = 0;
    int attacks1 = p1.attacks;
    int attacks2 = p2.attacks;
    while(p1.health > 0 && p2.health > 0)
    {
        cout<<"Round "<<fround<<":"<<endl;
        if (p1.initiative >= p2.initiative)
        {
            cout<<"Candidate 1 is randomly selected to go first ("<<p1.initiative<<" >= "<<p2.initiative<<")"<<endl;
            symbol = 1;
        }
        if (p2.initiative > p1.initiative)
        {
            cout<<"Candidate 2 is randomly selected to go first ("<<p2.initiative<<" > "<<p1.initiative<<")"<<endl;
            symbol = 2;
        }
        while ((p1.attacks > 0 or p2.attacks > 0) and p1.health > 0 and p2.health > 0)
        {
            if (symbol == 1 && p1.attacks > 0)
            {
                cout<<"Candidate 1 hits candidate 2 for "<<p1.damage<<" damage ("<<p2.health<<" -> "<<(p2.health - p1.damage)<<")"<<endl;
                p2.health -= p1.damage;
                p1.attacks--;
                if (p1.health > 0 && p2.health > 0 && p2.attacks > 0)
                    symbol = 2;
                if (p2.health < 0)
                {
                    cout<<"Candidate 1 wins!"<<endl;
                    return p1.name;
                }
            }
            if (symbol == 2 && p2.attacks > 0)
            {
                cout<<"Candidate 2 hits candidate 1 for "<<p2.damage<<" damage ("<<p1.health<<" -> "<<(p1.health - p2.damage)<<")"<<endl;
                p1.health -= p2.damage;
                p2.attacks--;
                if (p1.health > 0 && p2.health > 0 && p1.attacks > 0)
                    symbol = 1;
                if (p1.health < 0)
                {
                    cout<<"Candidate 2 wins!"<<endl;
                    return p2.name;
                }

            }
            if (p1.attacks == 0 && p2.attacks == 0)
            {
                fround++;
                p1.attacks = attacks1;
                p2.attacks = attacks2;
                break;
            }
        }
    }
}

int numOfPlayer = -1;
int numOfFight = 0;
int fsignal = 0;

int main()
{
    std::ifstream file("applicants.csv");
    int health,damage,attacks,initiative = 0;
    CSVRow row;
    Player players[10];
    //numOfFight = numOfPlayer * (numOfPlayer-1) / 2;
    
    string result[45];
    int index = 0;
    while(file >> row)
    {
        string pname = row[0];
        string phealth = row[1];
        string pdamage = row[2];
        string pattacks = row[3];
        string pinitiative = row[6];
        string name = "Name";
        if (pname.compare(name))
        {
            health = std::atoi(phealth.c_str());
            damage = std::atoi(pdamage.c_str());
            attacks = std::atoi(pattacks.c_str());
            initiative = std::atoi(pinitiative.c_str());
            players[index] = Player(health,damage,attacks,initiative,pname);
            index++;
        }
        
    }
    
    for (int i =0; i<10; i++)
    {
        for (int j = i+1; j<10; j++)
        {
            result[fsignal] = fight(players[i],players[j]);
            fsignal++;
        }
    }
    string winner;
    int temp1 = 0;
    int temp2 = 0;
    for (int i=0;i<fsignal;i++)
    {
        temp2 = 1;
        for (int j = i+1;j<fsignal;j++)
        {
            if (result[i] == result[j])
                temp2++;
        }
        if (temp2 > temp1)
        {
            temp1 = temp2;
            winner = result[i];
        }
    }
    cout<<winner<<" finally wins!"<<endl;
    return 1;
}
  

