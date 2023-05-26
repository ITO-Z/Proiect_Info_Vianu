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

int n;
Type type[4], P1, P2;

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

    input.close();
}

int RandomNumber(){
        srand(time(0));
       return rand()%10;
}

void Game()
{
    while (P1.health > 0 && P2.health > 0)
    {
        char action[6];
        // Player 1 turn
        int ok = 0;
        while (ok == 0)
        { // Available type
            cout << "\n Player 1 turn: ";
            cin >> action;
            if (strcmp(action, "ATTACK") == 0 || strcmp(action, "HEAL") == 0)
            {
                if (strcmp(action, "ATTACK") == 0)
                {
                    int random = RandomNumber();
                    if(random <= P1.accuracy/10){
                        P2.health -= P1.attack;
                        cout << "\nPlayer 1 dealt " << P1.attack << " damage to Player 2, he now has " << P2.health << " health"<<endl;
                    }
                    else cout<<"\nPlayer 1 missed"<<endl;
                }
                else if (strcmp(action, "HEAL") == 0)
                {
                    P1.health += P1.heal;
                    cout << "\nPlayer 1 healed " << P1.heal << " health, he now has " << P1.health << " health"<<endl;
                }
                ok = 1;
            }
            if (ok == 0)
                cout << "\nThis action is not available" << endl;
        }
        if (P2.health <= 0)
            break;
        // Player 2 turn
        ok = 0;
        while (ok == 0)
        { // Available type
            cout << "\n Player 2 turn: ";
            cin >> action;
            if (strcmp(action, "ATTACK") == 0 || strcmp(action, "HEAL") == 0)
            {
                if (strcmp(action, "ATTACK") == 0)
                {
                    int random = RandomNumber();
                    if(random <= P2.accuracy/10){
                        P1.health -= P2.attack;
                        cout << "\nPlayer 2 dealt " << P2.attack << " damage to Player 1, he now has " << P1.health << " health"<<endl;
                    }
                    else cout<<"\nPlayer 2 missed"<<endl;
                }
                else if (strcmp(action, "HEAL") == 0)
                {
                    P2.health += P2.heal;
                    cout << "\nPlayer 2 healed " << P2.heal << " health, he now has " << P2.health << " health"<<endl;
                }
                ok = 1;
            }
            if (ok == 0)
                cout << "\nThis action is not available" << endl;
        }
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

    // Asign Player 1
    int ok = 0;
    while (ok == 0)
    { // Available type
        cout << "Player 1 type: ";
        cin >> userType;
        for (int i = 0; i < n; i++)
        {
            if (strcmp(userType, type[i].name) == 0)
            { // Asign player type
                strcpy(P1.name, type[i].name);
                P1.attack = type[i].attack;
                P1.health = type[i].health;
                P1.heal = type[i].heal;
                P1.accuracy = type[i].accuracy;
                ok = 1;
                break;
            }
        }
        if (ok == 0)
            cout << "This type is not available" << endl;
    }

    // Asign Player 2
    ok = 0;
    while (ok == 0)
    { // Available type
        cout << "Player 2 type: ";
        cin >> userType;
        for (int i = 0; i < n; i++)
        {
            if (strcmp(userType, type[i].name) == 0)
            { // Asign player type
                strcpy(P2.name, type[i].name);
                P2.attack = type[i].attack;
                P2.health = type[i].health;
                P2.heal = type[i].heal;
                P2.accuracy = type[i].accuracy;
                ok = 1;
                break;
            }
        }
        if (ok == 0)
            cout << "This type is not available" << endl;
    }

    cout << "\nYou can either ATTACK or HEAL";

    Game();

    if (P1.health <= 0)
        cout << "\n\n Player 2 won!" << endl;
    if (P2.health <= 0)
        cout << "\n\nPlayer 1 won!" << endl;
    return 0;
}
