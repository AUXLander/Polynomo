#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include "NodeList.h"
#include "Polynomo.h"


mStruct TPolynomo::createElement(int factor, int x, int y, int z) {
	mStruct* elem = new mStruct{ factor, (x* 100 + y * 10 + z) };
	return (*elem);
}

bool TPolynomo::loadBin(std::string filepath) {
	std::ifstream openFile(filepath.c_str(), std::ios::in | std::ios::binary);
	int* fileLen = new int;
	mStruct* tempData = new mStruct;
	openFile.read((char*)fileLen, sizeof(int));
	repeat(*fileLen) {
		openFile.read((char*)tempData, sizeof(mStruct));
		addElement(*tempData);
	}
	delete tempData;
	openFile.close();
	return openFile.is_open();
}

bool TPolynomo::saveBin(std::string filepath) {
	std::ofstream saveFile(filepath.c_str(), std::ios::out | std::ios::binary);
	saveFile.write((char*)&length, sizeof(int));
	repeat(length) {
		saveFile.write((char*)&polynomoList[rep_i], sizeof(mStruct));
	}
	saveFile.close();
	return saveFile.bad();
}

TPolynomo::TPolynomo(TPolynomo& right) {
	(*this) = right;
}

TPolynomo TPolynomo::operator+(TPolynomo &right) {
	TPolynomo temp((*this));
	foreach(right) {
		temp.addElement(right.polynomoList[for_i], ADD);
	}
	return temp;
}

TPolynomo TPolynomo::operator-(TPolynomo &right) {
	TPolynomo temp((*this));
	foreach(right) {
		temp.addElement(right.polynomoList[for_i], SUB);
	}
	return temp;
}

TPolynomo TPolynomo::operator*(TPolynomo &right) {
	TPolynomo temp((*this)), temp2;
	foreach(right) {
		temp.addElement(right.polynomoList[for_i], MUL);
		repeat(temp.length) {
			temp2.addElement(temp.polynomoList[rep_i], ADD);
		}
		temp = (*this);
	}
	return temp2;
}

void TPolynomo::operator=(TPolynomo &right) {
	repeat(length) {
		polynomoList.removeNode(0);
	}
	foreach(right) {
		addElement(right.polynomoList[for_i], UNSET);
	}
}

void TPolynomo::addElement(mStruct elem, operation operation) {
	__throwif__(&elem == nullptr);

	switch (operation) {
	case SUB:
		elem.factor = -elem.factor;
	case ADD:
		foreach(polynomoList) {
			if (polynomoList[for_i].powerCombo == elem.powerCombo) {
				polynomoList.editNode(for_i, elem, operation);
				return;
			}
		}
		break;
	case MUL:
		repeat(polynomoList.length) {
			addElement(polynomoList[0] * elem);
			polynomoList.removeNode(0);
		}
		return;
	}
	polynomoList.addNode(elem);
}

std::string TPolynomo::printElem(mStruct elem) {
	int result[3]
		= {
			elem.powerCombo / 100 % 10,
			elem.powerCombo / 10 % 10,
			elem.powerCombo % 10
		};
	return	((result[0] > 0 ? "x^" + std::to_string(result[0]) : "")
			+ (result[1] > 0 ? " y^" + std::to_string(result[1]) : "")
			+ (result[2] > 0 ? " z^" + std::to_string(result[2]) : "")
			);
}

std::string TPolynomo::printElem(int index) {
	return printElem(polynomoList[index]);
}

std::string TPolynomo::printSolve() {
	if (!length) {
		return "<no data>";
	}
	int factor;
	std::string result;
	foreach(polynomoList) {
		factor = polynomoList[for_i].factor;
		if (factor == 0) {
			continue;
		}
		result += (factor < 0 ? " - " : " + ") + std::to_string(abs(factor)) + printElem(for_i);
	}
	if (result[1] == '+') {
		return result.erase(0, 3);
	}
	return result.erase(0, 1).erase(1, 1);
}

int TPolynomo::calcElem(mStruct elem, int x, int y, int z) {
	int result[3]
		= {
			elem.powerCombo / 100 % 10,
			elem.powerCombo / 10 % 10,
			elem.powerCombo % 10
		};
	return pow(x, result[0]) * pow(y, result[1]) * pow(z, result[2]);
}

int TPolynomo::calcElem(int index, int x, int y, int z) {
	return calcElem(polynomoList[index], x, y, z);
}

int TPolynomo::calcSolve(int x, int y, int z) {
	int result = 0;
	repeat(length) {
		result += polynomoList[rep_i].factor * calcElem(rep_i, x, y, z);
	}
	return result;
}