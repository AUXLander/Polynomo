#pragma once
#include <string>
#include "NodeList.h"

struct mStruct {
	int factor;
	int powerCombo;
	mStruct operator+(mStruct right) {
		mStruct temp(*this);
		temp.factor += right.factor;
		return temp;
	}
	mStruct operator-(mStruct right) {
		mStruct temp(*this);
		temp.factor -= right.factor;
		return temp;
	}
	mStruct operator*(mStruct right) {
		mStruct temp(*this);
		temp.factor *= right.factor;

		int clonePower[2] = { powerCombo, right.powerCombo };
		int cloneCombo[3] = { 0,0,0 };

		cloneCombo[2] = ((clonePower[0] % 10) + (clonePower[1] % 10)) % 10;
		clonePower[0] /= 10; clonePower[1] /= 10;

		cloneCombo[1] = ((clonePower[0] % 10) + (clonePower[1] % 10)) % 10;
		clonePower[0] /= 10; clonePower[1] /= 10;

		cloneCombo[0] = ((clonePower[0] % 10) + (clonePower[1] % 10)) % 10;
		clonePower[0] /= 10; clonePower[1] /= 10;

		temp.powerCombo = cloneCombo[0] * 100 + cloneCombo[1] * 10 + cloneCombo[2];
		return temp;
	}
	mStruct operator=(mStruct right) {
		factor = right.factor;
		powerCombo = right.powerCombo;
		return (*this);
	}
	mStruct operator*(int right) {
		mStruct temp(*this);
		temp.factor *= right;
		return temp;
	}
	mStruct operator-(int right) {
		mStruct temp(*this);
		temp.factor -= right;
		return temp;
	}
	mStruct operator+(int right) {
		mStruct temp(*this);
		temp.factor += right;
		return temp;
	}
	const bool operator==(const mStruct &right) const {
		if (factor == right.factor) {
			if (powerCombo == right.powerCombo) {
				return true;
			}
		}
		return false;
	}
};

class TPolynomo {
	TNodeList<mStruct> polynomoList;
public:
	TPolynomo() {};
	~TPolynomo() {};
	TPolynomo(TPolynomo&);
	mStruct createElement(int, int = 0, int = 0, int = 0);
	void addElement(const mStruct, operation = UNSET);
	int calcElem(mStruct, int = 1, int = 1, int = 1);
	int calcElem(int, int = 1, int = 1, int = 1);
	int calcSolve(int = 1, int = 1, int = 1);
	std::string printElem(mStruct);
	std::string printElem(int);
	std::string printSolve();
	bool loadBin(std::string);
	bool saveBin(std::string);
	TPolynomo operator+(TPolynomo&);
	TPolynomo operator-(TPolynomo&);
	TPolynomo operator*(TPolynomo&);
	void operator=(TPolynomo&);

	const int& length = polynomoList.length;
};
