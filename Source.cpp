#include <iostream>
#include <string>
#include "NodeList.h"
#include "Polynomo.h"
#include "ToolSet.h"

using namespace std;
int main() {
	int test[3] = { 1, 2, 3 };
	
	TPolynomo pol;
	mStruct t = pol.createElement(1, 3);
	pol.addElement(t);

	system("pause");

	return 0;
}
