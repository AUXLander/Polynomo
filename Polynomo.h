#pragma once
#include <string>
#include "NodeList.h"
#define mStruct mStruct // Welcome to the dark neone love - Drive (2011)

struct mStruct {
	int factor;
	int powerCombo;
};

namespace std {
	class TPolynomo {
		TNodeList<mStruct> polynomoList;

	public:
		TPolynomo();

		mStruct& createElement(int factor, int _x = 0, int _y = 0, int _z = 0);

		void addElement(mStruct& elem);

		bool loadString(string _string);

		string saveString();

		~TPolynomo();
	};

}