#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include "NodeList.h"
#include "Polynomo.h"

namespace std {

	mStruct TPolynomo::createElement(int factor, int _x, int _y, int _z) {
		mStruct* element = new mStruct{ factor, (_x * 100 + _y * 10 + _z) };
		return (*element);
	}

	bool TPolynomo::loadBin(string _filepath) {
		ifstream openFile(_filepath.c_str(), ios::in | ios::binary);
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

	bool TPolynomo::saveBin(string _filepath) {
		ofstream saveFile(_filepath.c_str(), ios::out | ios::binary);
		saveFile.write((char*)&length, sizeof(int));
		repeat(length) {
			saveFile.write((char*)&polynomoList[rep_i], sizeof(mStruct));
		}
		saveFile.close();
		return saveFile.bad();
	}

	TPolynomo::TPolynomo(TPolynomo& _v) {
		(*this) = _v;
	}

	TPolynomo TPolynomo::operator+(TPolynomo &_v) {
		TPolynomo temp((*this));
		foreach(_v) {
			temp.addElement(_v.polynomoList[for_i], ADD);
		}
		return temp;
	}

	TPolynomo TPolynomo::operator-(TPolynomo &_v) {
		TPolynomo temp((*this));
		foreach(_v) {
			temp.addElement(_v.polynomoList[for_i], SUB);
		}
		return temp;
	}

	TPolynomo TPolynomo::operator*(TPolynomo &_v) {
		TPolynomo temp((*this)), temp2;
		foreach(_v) {
			temp.addElement(_v.polynomoList[for_i], MUL);
			repeat(temp.length) {
				temp2.addElement(temp.polynomoList[rep_i], ADD);
			}
			temp = (*this);
		}
		return temp2;
	}

	void TPolynomo::operator=(TPolynomo &_v) {
		repeat(length) {
			polynomoList.removeNode(0);
		}
		foreach(_v) {
			addElement(_v.polynomoList[for_i], UNSET);
		}
	}

	void TPolynomo::addElement(mStruct elem, operation _oType) {
		__throwif__(&elem == nullptr);

		switch (_oType) {
		case SUB:
			elem.factor = -elem.factor;
		case ADD:
			foreach(polynomoList) {
				if (polynomoList[for_i].powerCombo == elem.powerCombo) {
					polynomoList.editNode(for_i, elem, _oType);
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

	string TPolynomo::printElem(mStruct _v) {
		int result[3]
			= {
				_v.powerCombo / 100 % 10,
				_v.powerCombo / 10 % 10,
				_v.powerCombo % 10
			};
		return	( (result[0] > 0 ? "x^" + to_string(result[0]) : "")
				+ (result[1] > 0 ? " y^" + to_string(result[1]) : "")
				+ (result[2] > 0 ? " z^" + to_string(result[2]) : "")
				);
	}

	string TPolynomo::printElem(int _index) {
		return printElem(polynomoList[_index]);
	}

	string TPolynomo::printSolve() {
		if (length == 0) {
			return "<no data>";
		}

		int factor;
		string result;

		repeat(polynomoList.length) {
			factor = polynomoList[rep_i].factor;
			if (factor == 0) {
				continue;
			}
			result += (factor < 0 ? " - " : " + ") + to_string(abs(factor)) + printElem(rep_i);
		}

		if (result[1] == '+') {
			return result.erase(0, 3);
		}

		return result.erase(0,1).erase(1, 1);
	}

	int TPolynomo::calcElem(mStruct _v, int x, int y, int z) {
		int result[3]
			= {
				_v.powerCombo / 100 % 10,
				_v.powerCombo / 10 % 10,
				_v.powerCombo % 10
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
}