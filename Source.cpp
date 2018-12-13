#include <iostream>
#include <string>
#include "NodeList.h"
#include "Polynomo.h"
#include "ToolSet.h"

using namespace std;
int main() {
	TPolynomo P, Q;

	//P.loadBin("P_file.bin");
	//Q.loadBin("Q_file.bin");


	P.addElement(P.createElement(3, 5, 2, 5));
	P.addElement(P.createElement(-5, 4, 3, 3));
	P.addElement(P.createElement(7, 3, 5, 1));

	Q.addElement(Q.createElement(4, 3, 2, 6));
	Q.addElement(Q.createElement(-6, 2, 1, 8));

	TPolynomo PQ;
	PQ = (P + Q);

	cout << "    " << P.printSolve() << endl << "  +" << endl;
	cout << "    " << Q.printSolve() << endl << "  =" << endl;
	cout << "    " << PQ.printSolve() << endl << endl;
	cout << "  " << "x0 = 2:" << endl;
	cout << "  =" << to_string(PQ.calcSolve(2)) << endl << endl;

	P.saveBin("P_file.bin");
	Q.saveBin("Q_file.bin");

	system("pause");
	return 0;
}
