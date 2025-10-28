#include<iostream>
#include <string>
using namespace std;

int processNums(string dance, int& pos)                      //This is the function to read a string of numbers and turn it into an integer 
{
	string num_str = "";                                     
	while (isdigit(dance[pos]))                              //while loop to read as far as the digits go
	{
		num_str = num_str + dance[pos];
		pos++;
	}
	
	return stoi(num_str);                                    //string to integer conversion
}
int processDir(string dance, string& instructions, int& hold, int& pos, int& beatNum)        //helps process beat by beat
{
	char dir = dance[pos];                                                                   //gets the direction by looking at the letter of the current beat
	if (hold == 1) {                                                                         //for the case when the starting number is ommited in the string. hold is by default 1 until the previous function has read a number
		beatNum++;
		if (dance[pos] == 'U' || dance[pos] == 'u')                                          //four cases for the four possible directions. it moves the position pointer down the string twice because it skips the current direction char and the subsequent '/' char
		{
			pos++;
			pos++;
			instructions = instructions + 'u';
			return -1;
		}
		if (dance[pos] == 'D' || dance[pos] == 'd')
		{
			pos++;
			pos++;
			instructions = instructions + 'd';
			return -1;
		}
		if (dance[pos] == 'R' || dance[pos] == 'r')
		{
			pos++;
			pos++;
			instructions = instructions + 'r';
			return -1;
		}
		if (dance[pos] == 'l' || dance[pos] == 'L')
		{
			pos++;
			pos++;
			instructions = instructions + 'l';
			return -1;
		}
		else return -1;
	}
	while (hold > 0)                                                                        //this is for when the beat is frozen. converts direction to upper case.
	{
		dir = toupper(dir);
		//cout << dir << endl;
		instructions = instructions + dir;                                                  //while there is still more beats left to hold, we add the char to instructions, and shift the pointer P down the string. 
		hold--;
		pos++;
		if (pos == dance.size())return -2;
		if (dance[pos] != '/') return beatNum+1;                                              // all the while we keep track of the number of beats in this dance. if we see something other than '/' in a hold we break and return the number of beats we are at
		else {
			beatNum++;
		}
	}
	
	pos++;
	
	return -1;

}
bool symbol(char c)
{
	if (c != 'U' && c != 'u' && c != 'D' && c != 'd' && c != 'L' && c != 'l' && c != 'R' && c != 'r')return false;
	return true;
}
bool isSyntacticallyCorrect(string dance)
{
	if (dance.size() == 0)return false;
	int pos = 0;
	while (pos < dance.size())
	{

		if (!isdigit(dance[pos]) && !symbol(dance[pos]) && dance[pos] != '/')
		{
			cout << "random symbol" << endl;
			return false;
		}
		if (islower(dance[pos]) || isupper(dance[pos]))
		{

			if (pos + 1 == dance.size() || dance[pos + 1] != '/')
			{
				cout << "ends without slash";
				return false;
			}
			pos = pos + 1;
		}
		else if (dance[pos] == '/')
		{
			pos++;
		}
		else if (isdigit(dance[pos]))
		{
			if (dance[pos] == '0')
			{
				if (isdigit(dance[pos + 2]))return false;
			}
			if (processNums(dance, pos) >= 100)
			{
				cout << "3digit";
				return false;

			}
			cout << dance[pos];
			if (pos >= dance.size())
			{
				cout << "ends with num";
				return false;
			}
			if (!symbol(dance[pos]))
			{
				cout << "not valid direction";
				return false;
			}
		}
		
	}
	return true;
}

int translateDance(string dance, string& instructions, int& badBeat)
{
	int str_ind = 0;
	int hold = 0;
	int beatnum = 0;
	while (str_ind < dance.size())

	{
		
		if (isupper(dance[str_ind]) || islower(dance[str_ind]))
		{
			if (hold == 0)hold = 1;
			badBeat=processDir(dance, instructions, hold, str_ind, beatnum);
			if (badBeat == -2)
			{
				badBeat = beatnum + 1;
				return 4;
			}
			if (badBeat != -1)return 3;
		}
		if (isdigit(dance[str_ind]))
		{
			hold = processNums(dance, str_ind);
			
			
			if (hold < 2)
			{
				badBeat = hold;
				return 2;
			}

		}
		if (dance[str_ind] == '/')
		{
			instructions = instructions + '.';
			str_ind++;
			beatnum++;
		}
	}
	if (hold != 0)
	{
		badBeat = beatnum + 1;
		return 4;
	}
	return 0;
}






int main()
{
	int badbeat = 0;
	string dance = "03u///3g/";
	string instructions = "";
	int i= translateDance(dance, instructions, badbeat);
	cout << isSyntacticallyCorrect(dance);

}