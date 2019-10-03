#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Student
{
	int FN;
	char firstName[14];
	char secondName[14];
	int grade;
	Student()
	{
		FN = 00000;
		firstName[0] = '/0';
		secondName[0] = '/0';
		grade = 2;
	}
};
int main()
{
	//suzdavane na fail sus 100 000 zapisa
	/*
	fstream File("StudentsGrades.db", ios::out);
	int* studentArray=new int[100000];
	for (int i = 0; i<100000; i++)
	{
		Student st;
		st.FN = rand() % 1000000 + 12132;
		for (int j = i - 1; j > -1; j--)
		{
			while (st.FN == studentArray[j])
			{
				st.FN = rand() % 1000000 + 12131;
			}
		}

		st.grade = rand() % 4 + 2;
		for (int j = 0; j < 14; j++)
		{
			st.firstName[j] = rand() % 26 + 'a';
		}
		st.firstName[13] = '\0';
		for (int j = 0; j < 14; j++)
		{
			st.secondName[j] = rand() % 26 + 'a';
		}
		st.secondName[13] = '\0';
		studentArray[i] = st.FN;
		File << st.FN << " " << st.firstName << " " << st.secondName << " " << st.grade << "\n";
	}
	*/
	string operation;
	operation = "/0";
	fstream file;
	bool flag = false;
	bool flag2 = false;
	bool flag3 = false;
	string searchFN;
	char grade;
	int FN;
	fstream tempFile("tempFile.db", ios::out);
	file.open("StudentsGrades.db");
	while (operation != "exit")
	{
		cin >> operation;
		if (operation == "update")
		{
			cin >> searchFN >> grade;
				//read the file line by line and searching for match of the given Faculty number
				for (string line; getline(file, line); )
				{

					//if a match is found, replace the grade with the new one
					if (searchFN == line.substr(0, searchFN.length()))
					{
						tempFile << line.substr(0, searchFN.length() + 29) << grade<<endl;
						flag2 = true;
					}
					else tempFile << line << endl;
				}
				tempFile.seekg(0, ios::beg);
				file.seekg(0, ios::beg);
			
		}
		if (operation == "update")
		{
			fstream newMain("StudentsGrades.db", ios::out);
			fstream readFromTemp("tempFile.db");
			char ch;
			while (!readFromTemp.eof())
			{
				readFromTemp.get(ch);
				newMain << ch;
			}
			if (flag2 == false)
			{

				cout << "Record not found!" << endl;
			}
			if (flag2 == true)
			{
				cout << "Record saved!" << endl;
			}
			flag = false;
			newMain.clear();
			readFromTemp.clear();
			readFromTemp.seekg(0, ios::beg);
			newMain.seekg(0, ios::beg);
		}
		if (operation == "delete")
		{
			cin >> searchFN;
			
			//read the file line by line and searching for match of the given Faculty number
			for (string line; getline(file, line); )
			{

				//if a match is found, omit the line
				if (searchFN != line.substr(0, searchFN.length()))
				{
					tempFile << line << endl;
				}
				else flag = true;
			}
			tempFile.seekg(0, ios::beg);
			file.seekg(0, ios::beg);
		}
		if (operation == "delete")
		{
			fstream newMain("StudentsGrades.db", ios::out);
			fstream readFromTemp("tempFile.db");
			char ch;
			while (!readFromTemp.eof())
			{
				readFromTemp.get(ch);
				newMain << ch;
			}
			if (flag == false)
			{

				cout << "Record not found!" << endl;
			}
			if (flag == true)
			{
				cout << "Record deleted!" << endl;
			}
			flag = false;
			newMain.clear();
			readFromTemp.clear();
			readFromTemp.seekg(0, ios::beg);
			newMain.seekg(0, ios::beg);
		}
		if (operation == "sequentialSearch")
			{

			cin >> searchFN;
			//read the file line by line and searching for match of the given Faculty number
			for (string line; getline(file, line); )
				{
					//if a match is found, print the record
					if (searchFN == line.substr(0, searchFN.length()))
					{
						cout << line << endl;
						flag2 = true;
						break;
					}
				}
				//else print a message
			if (flag2 == false)
			{

					cout << "Record not found!" << endl;
			}
			file.clear();
			file.seekg(0, ios::beg);
			flag2 = false;
		}
	}
	
	file.close();
}