#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <vector>
//#include <Windows.h>

using namespace std;

vector < unsigned int > stocking;
vector < unsigned int > suplementing;

int getNonNegativeNumber(unsigned int higher)
{
        unsigned int userValue=0;
        cin >> userValue;
 
        if (cin.fail() || userValue < 0 || userValue > higher)
        {
                cin.clear();
                cin.ignore();
                cin.sync();
                return -1;
        }
        else
                return userValue;
}
void printArray(vector < unsigned int > stocking, vector < unsigned int > suplementing)
{
	cout << "+-----+----+----+----+----+----+----+----+----+----+----+----+----+----+\n";
	cout << "|" << setw(5) << "  z  " << "|";

	unsigned int value=0;
	for(unsigned int i=0;i<stocking.size();i++) cout << setw(3) << i*25 << " |";

	cout << "\n+-----+----+----+----+----+----+----+----+----+----+----+----+----+----+\n";
	cout << "| f(z)|";
	for(unsigned int i=0;i<stocking.size();i++) cout << setw(3) << stocking[i] << " |";

	cout << "\n+-----+----+----+----+----+----+----+----+----+----+----+----+----+----+\n";
	cout << "| p(z)|";
	for(unsigned int i=0;i<=12;i++)
	{
		if (i%2 == 0) cout << setw(3) << suplementing[i/2];
		else cout << setw(3) << "-";

		cout << " |";
	}
	cout << "\n+-----+----+----+----+----+----+----+----+----+----+----+----+----+----+\n\n";
}

void printTable(unsigned int stage, unsigned int one, unsigned int two, unsigned int three, unsigned int four, unsigned int five, bool printHeader=true)
{
	if (printHeader == true)
	{
		printf("\n+-----+-----+-----+-----+-----+\n");
		printf("| x%d  | u%d  | x%d  |Cost | sum |\n", stage-1, stage, stage, stage, stage);
		printf("+-----+-----+-----+-----+-----+\n");
	}
	printf("| %3d | %3d | %3d | %3d | %3d |\n", one, two, three, four, five);
	printf("+-----+-----+-----+-----+-----+");
}

unsigned int findMin(vector < unsigned int > tmp)
{
	unsigned int min=1000;
	for(unsigned int i=0;i<tmp.size();i++)
	{
		if (tmp[i] < min) min = tmp[i];
	}
	return min;
}

vector < unsigned int > computeStep(unsigned int xPrev, vector < unsigned int > suplies, unsigned int expenses, vector < vector < unsigned int > > nextCost, unsigned int step, bool printHeader=true)
{
	vector < vector < unsigned int > > pushInto;	
	vector < unsigned int > tmp;

	for (unsigned int i=0;i<suplies.size();i++)
	{
		if (i==0 && printHeader != false) printHeader=true;
		else printHeader=false;

		pushInto.push_back(tmp);
		unsigned int state = xPrev+suplies[i]-expenses;
		unsigned int costOfStocking = stocking[state/25];
		unsigned int costOfSuplies = suplementing[suplies[i]/50];
		unsigned int cost = costOfStocking+costOfSuplies;
		unsigned int sum;
		if (step != 0) sum = cost+nextCost[i][4];
		else sum = cost;
		pushInto[i].push_back(xPrev);
		pushInto[i].push_back(suplies[i]);
		pushInto[i].push_back(state);
		pushInto[i].push_back(cost);
		pushInto[i].push_back(sum);
		switch(step)
		{
		case 0:
			step=4;
			break;
		case 1:
			step=3;
			break;
		case 2:
			step=2;
			break;
		case 3:
			step=1;
			break;
		}
		printTable(step, pushInto[i][0], pushInto[i][1], pushInto[i][2], pushInto[i][3], pushInto[i][4], printHeader);
		cout << "\n";
	}
	

	unsigned int index=0, min=1000;
	for (unsigned int j=0;j<pushInto.size();j++)
	{
		if (pushInto[j][4] < min)
		{
			min = pushInto[j][4];
			index = j;
		}
	}

	return pushInto[index];
}

vector < vector < vector < unsigned int > > > calculateCost()
{
	vector < vector < vector < vector < unsigned int > > > > tmp1;
	vector < vector < vector < unsigned int > > > table;
	vector < vector < unsigned int > > minis, zeros, toInsert;
	vector < unsigned int > tmp, data;

	unsigned int i=0, step=0, expenses;

	zeros.push_back(tmp);
	for (unsigned int i=0;i<3;i++) zeros[0].push_back(0);

	//step1	
	step = 0;
	expenses = 100;
	table.push_back(toInsert);

	data.clear();
	data.push_back(100);
	minis.push_back(computeStep(0, data, expenses, zeros, step));
	table[step].push_back(minis[i++]);

	data.clear();
	data.push_back(50);
	minis.push_back(computeStep(50, data, expenses, zeros, step, false));
	table[step].push_back(minis[i++]);

	data.clear();
	data.push_back(0);
	minis.push_back(computeStep(100, data, expenses, zeros, step, false));
	table[step].push_back(minis[i++]);

	//step2
	i = 0;
	step = 1;
	expenses = 100;
	table.push_back(toInsert);
	minis.clear();

	data.clear();
	data.push_back(100);
	data.push_back(150);
	data.push_back(200);
	minis.push_back(computeStep(0, data, expenses, table[step-1], step));
	table[step].push_back(minis[i++]);
	
	data.clear();
	data.push_back(50);
	data.push_back(100);
	data.push_back(250);
	minis.push_back(computeStep(50, data, expenses, table[step-1], step, false));
	table[step].push_back(minis[i++]);

	data.clear();
	data.push_back(0);
	data.push_back(50);
	data.push_back(100);
	minis.push_back(computeStep(100, data, expenses, table[step-1], step, false));
	table[step].push_back(minis[i++]);

	data.clear();
	data.push_back(0);
	data.push_back(50);
	minis.push_back(computeStep(150, data, expenses, table[step-1], step, false));
	table[step].push_back(minis[i++]);

	data.clear();
	data.push_back(0);
	minis.push_back(computeStep(200, data, expenses, table[step-1], step, false));
	table[step].push_back(minis[i++]);

	//Step3
	i = 0;
	step = 2;
	expenses = 50;
	table.push_back(toInsert);
	minis.clear();

	data.clear();
	data.push_back(50);
	data.push_back(100);
	data.push_back(150);
	data.push_back(200);
	data.push_back(250);
	minis.push_back(computeStep(0, data, expenses, table[step-1], step));
	table[step].push_back(minis[i++]);

	data.clear();
	data.push_back(0);
	data.push_back(50);
	data.push_back(100);
	data.push_back(150);
	data.push_back(200);
	minis.push_back(computeStep(50, data, expenses, table[step-1], step, false));
	table[step].push_back(minis[i++]);

	data.clear();
	data.push_back(0);
	data.push_back(50);
	data.push_back(100);
	data.push_back(150);
	data.push_back(200);
	minis.push_back(computeStep(100, data, expenses, table[step-1], step, false));
	table[step].push_back(minis[i++]);

	data.clear();
	data.push_back(0);
	data.push_back(50);
	data.push_back(100);
	minis.push_back(computeStep(150, data, expenses, table[step-1], step, false));
	table[step].push_back(minis[i++]);

	data.clear();
	data.push_back(0);
	data.push_back(50);
	minis.push_back(computeStep(200, data, expenses, table[step-1], step, false));
	table[step].push_back(minis[i++]);

	data.clear();
	data.push_back(0);
	minis.push_back(computeStep(250, data, expenses, table[step-1], step, false));
	table[step].push_back(minis[i++]);

	//Step4
	i = 0;
	step = 3;
	expenses = 150;
	table.push_back(toInsert);
	minis.clear();

	data.clear();
	data.push_back(50);
	data.push_back(100);
	data.push_back(150);
	data.push_back(200);
	data.push_back(250);
	data.push_back(300);
	minis.push_back(computeStep(100, data, expenses, table[step-1], step));
	table[step].push_back(minis[i++]);

	return table;
}

int main()
{
	const int higher=100;
	unsigned int value=0;
	unsigned int userValue=0;
	bool flag=false;

	while(true)
	{
		cout << "Select mode:\n"
			<< "\t(1) I want to enter whole array\n"
			<< "\t(2) I want to get predefined array\n\n"
			<< "\tSelected option: ";

		userValue = getNonNegativeNumber(2);
		if (userValue == -1)
		{
			cout << "\n\tEntered value must be lower than 0 and greater than 2. Try again\n\n";
		}
		else
			break;
	}

	if (userValue == 2)
	{

		suplementing.push_back(0);
		suplementing.push_back(22);
		suplementing.push_back(32);
		suplementing.push_back(35);
		suplementing.push_back(50);
		suplementing.push_back(70);
		suplementing.push_back(90);
		stocking.push_back(0);
		stocking.push_back(3);
		stocking.push_back(8);
		stocking.push_back(15);
		stocking.push_back(30);
		stocking.push_back(40);
		stocking.push_back(49);
		stocking.push_back(55);
		stocking.push_back(58);
		stocking.push_back(60);
		stocking.push_back(62);
		stocking.push_back(64);
		stocking.push_back(65);

	}
	else
	{
		cout << "\n\nEnter values of costs for:\n";
		for (unsigned int i=0; i<=12; i++)
		{
			value = i*25;
			while(true)
			{
				cout << "\tStocking of " << value << " items: ";
				userValue = getNonNegativeNumber(higher);
				if (userValue == -1)
				{
					cout << "\tEntered value must be lower than 0 and greater than " << higher << ". Try again\n\n";
				} else
				{
					stocking.push_back(userValue);

					if (value%50 == 0)
					{
						while(true)
						{
							cout << "\tSuplementing by " << value << " items: ";
							userValue = getNonNegativeNumber(higher);
							if (userValue == -1)
							{
								cout << "\tEntered value must be lower than 0 and greater than " << higher << ". Try again\n\n";
							} else
							{
								suplementing.push_back(userValue);
								break;
							}
						}
					}
					break;
				}
			}
		}
	}

	cout << "\n";

	cout << "Table of costs is as follows:\n\n";
	printArray(stocking, suplementing);
	vector < vector < vector < unsigned int > > > table;
	cout << "\nNow states table will be printed\n";
    //system("Pause");
	table = calculateCost();
	string one, two, three, four;

	
	for(unsigned int i=0;i<table[2].size();i++)
	{
		if (table[2][i][0] == table[3][0][2])
		{
			for (unsigned int j=0;j<table[1].size();j++)
			{
				if (table[1][j][0] == table[2][i][2])
				{
					for(unsigned int k=0;k<table[0].size();k++)
					{
						if (table[0][k][0] == table[1][k][2])
						{
							cout << "\nNow your optimal solution will be printed:\n";
                            //system("Pause");
							cout << "\n";
							printTable(4, table[0][j][0], table[0][j][1], table[0][j][2], table[0][j][3], table[0][j][4]);
							printTable(3, table[1][j][0], table[1][j][1], table[1][j][2], table[1][j][3], table[1][j][4]);
							printTable(2, table[2][i][0], table[2][i][1], table[2][i][2], table[2][i][3], table[2][i][4]);
							printTable(1, table[3][0][0], table[3][0][1], table[3][0][2], table[3][0][3], table[3][0][4]);
							cout << "\n";
                            //system("Pause");
							return 1;
						}
					}
					break;
				}
			}
			break;
		}
	}

	cout << "Error occured. Exiting.";
	return 0;
}