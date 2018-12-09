#include <iostream>
#include "NodeList.h"
#include "ToolSet.h"

using namespace std;
int main() {
	int test[3] = { 1, 2, 3 };

	TNodeList<int> List(3, test);
	List.removeNode(List.getNode(0));
	cout << List.getNodeValue(0);
	//Node<int> t = { 0, nullptr };
	//List.insertNodeAfter(-1, t);
	cout << List.getNodeValue(1);
	//cout << List.getNodeValue(2);

	system("pause");

	return 0;
}
