#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Type
{
    char name[10];
    int health;
    int attack;
    int heal;
    int accuracy;
};

int n, m;
Type type[4], P, enemy[5], E;

void Read()
{
    fstream input;
    input.open("Types.txt", ios::in);
    input >> n;
    for (int i = 0; i < n; i++)
    {
        input >> type[i].name;
        input >> type[i].attack;
        input >> type[i].health;
        input >> type[i].heal;
        input >> type[i].accuracy;
    }
    input >> m;
    for(int i = 0; i < m; i++){
        input >> enemy[i].name;
        input >> enemy[i].attack;
        input >> enemy[i].health;
        input >> enemy[i].heal;
        input >> enemy[i].accuracy;
    }
    input.close();
}

int RandomNumber(){
        srand(time(0));
       return rand()%100;
}

void Game()
{
    int i = 0;
    while (P.health > 0 && i < m){
        strcpy(E.name, enemy[i].name);
        E.attack = enemy[i].attack;
        E.health = enemy[i].health;
        E.heal = enemy[i].heal;
        E.accuracy = enemy[i].accuracy;
        cout << "You are now fighting the " << E.name << " that has " << E.attack << " attack, " << E.health << " health, " << E.heal << " heal and " << E.accuracy << "% accuracy." << endl;
        while(E.health > 0 && P.health > 0){
            char action[6];
            int ok = 0;
            while (ok == 0)
            { // Available type
                cout << "\nWhat do you want to do?" << endl;
                cin >> action;
                if (strcmp(action, "ATTACK") == 0 || strcmp(action, "HEAL") == 0)
                {
                    if (strcmp(action, "ATTACK") == 0)
                    {
                        int random = RandomNumber();
                        if(random <= P.accuracy){
                            E.health -= P.attack;
                            cout << "\nPlayer dealt " << P.attack << " damage to "<< E.name << ", he now has " << E.health << " health"<<endl;
                        }
                    else cout<<"\nPlayer missed"<<endl;
                }
                else if (strcmp(action, "HEAL") == 0)
                {
                    P.health += P.heal;
                    cout << "\nPlayer healed " << P.heal << " health, he now has " << P.health << " health"<<endl;
                }
                ok = 1;
                }
                if (ok == 0)
                    cout << "\nThis action is not available" << endl;
            }
            if (E.health <= 0)
                break;
            int Eaction;
            Eaction = RandomNumber() % 3;
            if(Eaction == 0 || Eaction == 1){
                int random = RandomNumber();
                if(random <= E.accuracy){
                    P.health -= E.attack;
                    cout << "\n" << E.name << " dealt " << E.attack << " damage, you now have " << P.health << " health" << endl;
                } else
                    cout << E.name << " missed" << endl;
            } else if(Eaction == 2){
                E.health += E.heal;
                cout << "\n" << E.name << " healed " << E.heal << " health, he now has " << E.health << " health" << endl;
            }
        }
        if(E.health <= 0){
            cout << "You deafeted the " << E.name << endl;
            cout << "You have gained 10 health and 3 upgrades" << endl;
            cout << "You can upgrade you ATTACK, your HEAL or your ACCURACY" << endl;
            P.health += 10;
            cout << "What do you want to upgrade" << endl;
            int ct = 3;
            char upgrade[10];
            while(ct > 0){
                cin >> upgrade;
                if(strcmp(upgrade, "ATTACK") == 0){
                    P.attack += 4;
                    cout << "You upgraded your ATTACK, it is now " << P.attack << endl;
                    ct--;
                } else if(strcmp(upgrade, "HEAL") == 0){
                    P.heal += 3;
                    cout << "You upgraded your HEAL, it is now " << P.heal << endl;
                    ct--;
                } else if(strcmp(upgrade, "ACCURACY") == 0 && P.accuracy < 100){
                    P.accuracy += 5;
                    cout << "You upgraded your ACCURACY, it is now " << P.accuracy << endl;
                    ct--;
                } else if(strcmp(upgrade, "ACCURACY") == 0 && P.accuracy >= 100)
                    cout << "Your accuracy is already maxed, you can no longer upgrade it" << endl;
                else
                    cout << "This upgrade is not available" << endl;
            }
        }
        i++;
    }
}

int main()
{
    Read();
    char userType[10];
    cout << "\nPlayer Types: " << endl
         << endl;
    for (int i = 0; i < n; i++)
    {
        cout << type[i].name << " attack:" << type[i].attack << " health:" << type[i].health << " heal:" << type[i].heal << " accuracy: " << type[i].accuracy << "%"<< endl;
    }
    cout << endl;

    // Asign Player
    int ok = 0;
    while (ok == 0)
    { // Available type
        cout << "Player type: ";
        cin >> userType;
        for (int i = 0; i < n; i++)
        {
            if (strcmp(userType, type[i].name) == 0)
            { // Asign player type
                strcpy(P.name, type[i].name);
                P.attack = type[i].attack;
                P.health = type[i].health;
                P.heal = type[i].heal;
                P.accuracy = type[i].accuracy;
                ok = 1;
                break;
            }
        }
        if (ok == 0)
            cout << "This type is not available" << endl;
    }

    cout << "\nYou can either ATTACK or HEAL" << endl;

    Game();

    if (P.health <= 0)
        cout << "\n\n You lost!" << endl;
    else
        cout << "\n\n You won!" << endl;
    return 0;
}
