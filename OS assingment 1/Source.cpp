#include <iostream>
#include <string>
#include <fstream>
#include<iomanip>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <sys/types.h> 
#include <string.h>
//#include <sys/wait.h>
//#include <unistd.h> 
using namespace std;

/*void printQueue(queue <char> queues)//for testing
{
	queue <char> MyQueue = queues;
	while (!MyQueue.empty())
	{
		cout << MyQueue.front();
		MyQueue.pop();
	}
	cout << '\n';
}*/

/*void printQueue2(queue <char> queues2)//for testing
{
	queue <char> MyQueue2 = queues2;
	while (!MyQueue2.empty())
	{
		cout << MyQueue2.front();
		MyQueue2.pop();
	}
	cout << '\n';
}*/

int main()
{
	string line = "";;
	/*while(cin)
	{
		getline(cin,line);
	}*/
	//string line;
	string parentString;
	ifstream file;
	//file.open("Text.txt");//here
	ifstream parentfile;

	vector<char>symbol;
	vector<int>frequency;

	int counter = 0;
	getline(cin, line, '\0');

	for (int i = 0; i < line.length(); i++)
	{

		symbol.push_back(line[i]);
	}

	sort(symbol.begin(), symbol.end());
	symbol.erase(unique(symbol.begin(), symbol.end()), symbol.end());

	for (int x = 0; x < symbol.size(); x++)
	{
		for (int y = 0; y < line.length(); y++)
		{
			if (symbol.at(x) == line[y])
			{
				counter++;
			}
		}
		frequency.push_back(counter);
		counter = 0;
	}

	vector<pair<char, int>>frequencyNums(symbol.size());

	for (int i = 0; i < frequencyNums.size(); i++)
	{
		frequencyNums[i].first = symbol.at(i);
		frequencyNums[i].second = frequency.at(i);
	}
	sort(frequencyNums.begin(), frequencyNums.end(), [](auto&left, auto &right)
	{
		return left.second > right.second;
	});
	cout << endl;

	for (int i = 0; i < frequencyNums.size(); i++)
	{
		if (frequencyNums[i].first == '\n')
		{
			cout << "<EOL> frequency: " << frequencyNums[i].second << endl;
		}
		else
		{
			cout << frequencyNums[i].first << " frequency: " << frequencyNums[i].second << endl;
		}
	}

	queue <char> queues;
	for (int i = 0; i < line.length(); i++)
	{
		queues.push(line[i]);//sends whole string
	}
	//printQueue(queues); //testing

	queue <char> queues2;
	for (int i = 0; i < frequencyNums.size(); i++)
	{
		queues2.push(frequencyNums[i].first);//sends character in order
	}


	//printQueue2(queues2); //testing

	cout << "Original Message: ";
	//cout << line;
	pid_t pid;
	string updatedInput(line);//string from file converted from char array
	int holder = queues2.size();
	int j = 0;
	char symbol_Queue2;

	for (int i = 0; i < updatedInput.length(); i++)
	{
		if (updatedInput[i] == '\n')
		{
			cout << "<EOL>";
		}
		else
		{
			cout << updatedInput[i];
		}
	}
	cout << endl;
	for (int i = 0; i < holder; i++)
	{
		j++;
		string bitMessage = "";
		string messageRemaining = "";

		symbol_Queue2 = queues2.front();//set symbol_Queue2 as first symbol
		//cout << "Symbol " << queues2.front() << " code: ";
		//queues2.pop();//pop that symbol
		for (int x = 0; x < updatedInput.length(); x++)
		{
			if (symbol_Queue2 == updatedInput[x])
			{
				bitMessage += '1';
			}
			else
			{
				bitMessage += '0';
			}
		}
		//cout << bitMessage << endl;

		for (int x = 0; x < updatedInput.length(); x++)
		{
			if (bitMessage[x] == '0')
			{
				messageRemaining += updatedInput[x];
			}
		}
		updatedInput = messageRemaining;
		if (queues2.size() != 0)
		{
			//cout << "Remaining Message: " << messageRemaining << endl;

		}

		if ((fork()) == 0)
		{
			ofstream childfile;
			childfile.open(to_string(j) + ".txt");

			if (symbol_Queue2 == '\n')
				childfile << "Symbol " << "<EOL>" << " code:     " << bitMessage << endl;
			else
				childfile << "Symbol " << symbol_Queue2 << " code:     " << bitMessage << endl;
			if (j == holder)
			{

			}
			else
			{
				childfile << "Remaining Message: ";
			}

			for (int a = 0; a < messageRemaining.length(); a++)
			{
				if (messageRemaining[a] == '\n')
					childfile << "<EOL>";
				else
					childfile << messageRemaining[a];
			}


			/*if (j <= holder)
			{
				childfile << "Symbol " << queues2.front() << " code: " << bitMessage << endl;
				if (j != holder)
				{
					childfile << "Remaining Message: " << messageRemaining << endl;
				}

			}*/
			childfile << endl;
			childfile.close();
			sleep(1);
			exit(0);
		}

		queues2.pop();
	}

	for (int i = 0; i < holder; i++)
	{
		wait(0);
	}

	for (int y = 1; y <= holder; y++)
	{
		parentfile.open(to_string(y) + ".txt");
		getline(parentfile, parentString, '\0');
		cout << parentString;
		parentfile.close();
	}

	//system("pause");
	return 0;

}

