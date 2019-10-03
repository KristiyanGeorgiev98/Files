#include <iostream>
#include "BinOrdTree.h"
#include "Student.h"
#include <string>
using namespace std;
int main()
{
	BinOrdTree<Student> tree;
	Student st;
	string operation;
	operation = "/0";
	//izlizame s exit
	while (operation != "exit")
	{
		cin >> operation;
		if (operation == "insert")
		{
			//vuvejdame nov student
			//ako veche ima student sus sushtiq FN zamenq imenata mu s novite
			cin >> st.FN >>st.firstName >> st.secondName;
			tree.addNode(st);	
			cout << "Record inserted!"<<endl;
		}
		if (operation == "delete")
		{
			//iztriva studenta s takuv FN
			//ako ne sushtestvuva takuv student izliza suobshtenie
			cin >> st.FN;
			st.firstName[0] = st.secondName[0] = '\0';
			tree.deleteNode(st);

		}
		if (operation == "find")
		{
			//ako sushtestvuva student s takuv FN izvejda samiq FN (operatora << e predefiniran da izvejda
			//samo FN zaradi traverseInorder)
			//v protiven sluchai izvejda record not found
			cin >> st.FN;
			st.firstName[0] = st.secondName[0] = '\0';
			tree.find(st);
		}
		if (operation == "traverseInorder")
		{
			//printira FN podredeni
			tree.traverseInorder();
		}
	}
}