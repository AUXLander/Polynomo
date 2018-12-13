#pragma once
#include <string>
#include "NodeList.h"
#define mStruct mStruct // dark & soft neone - Drive (2011)

struct mStruct {
	int factor;
	int powerCombo;

	const mStruct& operator+(const mStruct& _v) {
		factor += _v.factor;
		return (*this);
	}
	const mStruct& operator-(const mStruct& _v) {
		factor -= _v.factor;
		return (*this);
	}
	const mStruct& operator*(const mStruct& _v) {
		int cPower[3];

		factor *= _v.factor;

		cPower[0] = (int)((powerCombo + _v.powerCombo) * 0.01) % 10;
		cPower[1] = (int)((powerCombo + _v.powerCombo) * 0.1) % 10;
		cPower[2] = (powerCombo + _v.powerCombo) % 10;

		powerCombo = cPower[0] * 100 + cPower[1] * 10 + cPower[2];

		//powerCombo += powerCombo;
		return (*this);
	}
	const mStruct& operator/(const mStruct& _v) {
		factor /= _v.factor;

		powerCombo -= powerCombo;
		return (*this);
	}
	const mStruct& operator=(const mStruct& _v) {
		factor = _v.factor;
		powerCombo = _v.powerCombo;
		return (*this);
	}
};

namespace std {
	class TPolynomo {

		TNodeList<mStruct> polynomoList;


	public:
		TPolynomo() {};

		TPolynomo(TPolynomo& v);

		mStruct createElement(int factor, int _x = 0, int _y = 0, int _z = 0);

		void addElement(mStruct elem, operation _oType = UNSET);

		int calcElem(mStruct _v, int x = 1, int y = 1, int z = 1);

		int calcElem(int index, int x = 1, int y = 1, int z = 1);

		int calcSolve(int x = 1, int y = 1, int z = 1);

		string printElem(mStruct _v);

		string printElem(int _index);

		string printSolve();

		bool loadBin(string filepath);

		bool saveBin(string filepath);

		TPolynomo& operator+(TPolynomo v);

		TPolynomo& operator-(TPolynomo v);

		TPolynomo& operator*(TPolynomo v);

		TPolynomo& operator=(TPolynomo v);

		~TPolynomo() {}

		const int& length = polynomoList.length;
	};

}