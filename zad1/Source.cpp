#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	string operation;
	operation = "/0";
	ofstream oFile;
	oFile.open("StudentsGrades.db", ios::app);
	ifstream inFile("StudentsGrades.db", ios::in);
	size_t FN;
	bool flag = false;
	string searchFN;
	string firstName;
	string LastName;
	size_t grade;
	while (operation != "exit")
	{
		cin >> operation;
		if (operation == "create")
		{
			//create a record in the file
			cin >> FN >> firstName >> LastName >> grade;
			oFile << FN;
			oFile << " ";
			oFile << firstName;
			oFile << " ";
			oFile << LastName;
			oFile << " ";
			oFile << grade;
			oFile << "\n";
			cout << "Record saved!"<<endl;
			oFile.close();
		}
		if (operation == "sequentialSearch")
		{
			cin >> searchFN;
			//read the file line by line and searching for match of the given Faculty number
			for (string line; getline(inFile, line); )
			{
				//if a match is found, print the record
				if (searchFN == line.substr(0,searchFN.length()))
				{
					cout << line<<endl;
					flag = true;
					break;
				}
			}		
			//else print a message
			if (flag == false)
			{
				
				cout << "Record not found!"<<endl;
			}
			inFile.clear();
			inFile.seekg(0, ios::beg);
			flag = false;
		}
	}
	inFile.close();

}