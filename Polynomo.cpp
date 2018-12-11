#include <string>
#include <iostream>
#include <fstream>
#include "NodeList.h"
#include "Polynomo.h"

namespace std {

	TPolynomo::TPolynomo() {

	}

	TPolynomo::~TPolynomo() {

	}

	bool TPolynomo::loadBin(string filepath) {
		fstream openFile;
		openFile.open(filepath, ios::binary);

		return openFile.is_open();
	}

	bool TPolynomo::saveBin(string filepath) {
		fstream openFile;
		openFile.open(filepath, ios::binary);

		return openFile.is_open();
	}

	TPolynomo& TPolynomo::operator+(TPolynomo& _v) {
		for (int i = 0; i < _v.polynomoList.length; i++) {
			addElement(_v.polynomoList.getNodeValue(i), ADD);
		}
		return (*this);
	}

	TPolynomo& TPolynomo::operator-(TPolynomo& _v) {
		for (int i = 0; i < _v.polynomoList.length; i++) {
			addElement(_v.polynomoList.getNodeValue(i), SUB);
		}
		return (*this);
	}

	TPolynomo& TPolynomo::operator*(TPolynomo& _v) {
		for (int i = 0; i < _v.polynomoList.length; i++) {
			addElement(_v.polynomoList.getNodeValue(i), MUL);
		}
		return (*this);
	}

	void TPolynomo::print() {
		mStruct key;
		foreach(key, polynomoList) {
			key = polynomoList[i];
			cout << key.factor << endl;
		}
	}

	string TPolynomo::decodeElem(mStruct& _v) {
		return	( " x^" + to_string(_v.powerCombo / 100 % 10)
				+ " y^" + to_string(_v.powerCombo / 10 % 10)
				+ " z^" + to_string(_v.powerCombo % 10)
				);
	}

	string TPolynomo::getElement(int _index) {
		return decodeElem(polynomoList.getNodeValue(_index));
	}

	string TPolynomo::getSolve() {
		return string();
	}

	string TPolynomo::getSolve(int x, int y, int z) {
		return string();
	}
}