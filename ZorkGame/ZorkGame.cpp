
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
	cout << "----------------\n";
	cout << "You are the captain of an underwater base located in the depths of the Mariana Trench, that studies algae and living beings in the area. Together with your colleagues, Dolores and Jonny, you have discovered an algae that may have the ability to cure cancer. While you are sleeping peacefully in your cabin, you hear a loud noise and screams of 'HELP!' that seems to come from the crew room.\n";

	cout << "\nFrom here, your story begins : \n\n";


	args.push_back("look");
	cout << "----------------\n";
	cout << "Type help to see all the actions\n";
	cout << "----------------\n";
	while (1)
	{
		if (_kbhit() != 0 && !World::getInstance().IsPlayerInCombat())
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

		if (World::getInstance().IsGameFinished())
		{
			break;
		}

		if (args.size() > 0 && Same(args[0], "quit"))
		{
			break;
		}

		if (World::getInstance().Tick(args) == false)
		{
			cout << "\nSorry, I do not understand your command.\n";
		}

		if (args.size() > 0)
		{
			args.clear();
			player_input = "";
			cout << "> ";
		}
	}
	cout << "\nThanks for playing, Bye!\n";
	
	return 0; 
}