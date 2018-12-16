#pragma once
#include <string>
#include "NodeList.h"
#define mStruct mStruct // dark & soft neone - Drive (2011)

struct mStruct {
	int factor;
	int powerCombo;
	mStruct operator+(mStruct _v) {
		mStruct temp(*this);
		temp.factor += _v.factor;
		return temp;
	}
	mStruct operator-(mStruct _v) {
		mStruct temp(*this);
		temp.factor -= _v.factor;
		return temp;
	}
	mStruct operator*(mStruct _v) {
		mStruct temp(*this);
		temp.factor *= _v.factor;

		int clonePower[2] = { powerCombo, _v.powerCombo };
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
	mStruct operator=(mStruct _v) {
		factor = _v.factor;
		powerCombo = _v.powerCombo;
		return (*this);
	}
	mStruct operator*(int _v) {
		mStruct temp(*this);
		temp.factor *= _v;
		return temp;
	}
	mStruct operator-(int _v) {
		mStruct temp(*this);
		temp.factor -= _v;
		return temp;
	}
	mStruct operator+(int _v) {
		mStruct temp(*this);
		temp.factor += _v;
		return temp;
	}
};

namespace std {
	class TPolynomo {
		TNodeList<mStruct> polynomoList;
	public:
		TPolynomo() {};
		~TPolynomo() {};
		TPolynomo(TPolynomo &v);
		mStruct createElement(int factor, int _x = 0, int _y = 0, int _z = 0);
		void addElement(const mStruct elem, operation _oType = UNSET);
		int calcElem(mStruct _v, int x = 1, int y = 1, int z = 1);
		int calcElem(int index, int x = 1, int y = 1, int z = 1);
		int calcSolve(int x = 1, int y = 1, int z = 1);
		string printElem(mStruct _v);
		string printElem(int _index);
		string printSolve();
		bool loadBin(string filepath);
		bool saveBin(string filepath);
		TPolynomo operator+(TPolynomo &v);
		TPolynomo operator-(TPolynomo &v);
		TPolynomo operator*(TPolynomo &v);
		void operator=(TPolynomo &v);

		const int& length = polynomoList.length;
	};
}