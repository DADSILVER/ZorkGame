
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "world.h"
#include "globals.h"

using namespace std;

int main()
{
	char key;
	string player_input;
	vector<string> args;
	args.reserve(10);

	cout << "Welcome to MyZork!\n" ;
	cout << "----------------";

	World* myWorld = World::getInstance();

	args.push_back("look");

	cout << "Type help to see all the actions\n";
	cout << "----------------\n";
	while (1)
	{
		if (_kbhit() != 0 && !myWorld->IsInCombat())
		{
			key = _getch();
			if (key == '\b') // backspace
			{
				if (player_input.length() > 0)
				{
					player_input.pop_back();
					//cout << BACKSPACE;
					cout << '\b';
					cout << " ";
					cout << '\b';
				}
			}
			else if (key != '\r') // return
			{
				player_input += key;
				cout << key;
			}
			else
				Tokenize(player_input, args);
		}

		if (myWorld->IsGameFinished()) 
		{
			break;
		}

		if (args.size() > 0 && Same(args[0], "quit"))
			break;

		if (myWorld->Tick(args) == false)
			cout << "\nSorry, I do not understand your command.\n";

		if (args.size() > 0)
		{
			args.clear();
			player_input = "";
			cout << "> ";
		}
	}
	cout << "\nThanks for playing, Bye!\n";
	delete myWorld;
	return 0;
    
}