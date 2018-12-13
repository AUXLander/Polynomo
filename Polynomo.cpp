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
		openFile.seekg(0);
		int* fileLen = new int;
		mStruct* tempData = new mStruct;

		openFile.read((char*)fileLen, sizeof(int));

		for (uint i = 0; i < *fileLen; i++) {
			openFile.read((char*)tempData, sizeof(mStruct));
			addElement(*tempData);
		}

		delete tempData;
		openFile.close();
		return openFile.is_open();
	}

	bool TPolynomo::saveBin(string _filepath) {
		ofstream saveFile(_filepath.c_str(), ios::out | ios::binary);
		saveFile.seekp(0);
		saveFile.write((char*)&length, sizeof(int));
		for (uint i = 0; i < length; i++) {
			saveFile.write((char*)&polynomoList[i], sizeof(mStruct));
		}
		saveFile.close();
		return saveFile.bad();
	}

	TPolynomo::TPolynomo(TPolynomo& v) {
		foreach(v) {
			addElement(v.polynomoList[i]);
		}
	}

	TPolynomo& TPolynomo::operator+(TPolynomo _v) {
		TPolynomo temp;
		foreach((*this)) {
			temp.addElement(polynomoList[i]);
		}
		foreach(_v) {
			temp.addElement(_v.polynomoList[i], ADD);
		}
		return temp;
	}

	TPolynomo& TPolynomo::operator-(TPolynomo _v) {
		TPolynomo temp;
		foreach((*this)) {
			temp.addElement(polynomoList[i]);
		}
		foreach(_v) {
			temp.addElement(_v.polynomoList[i], SUB);
		}
		return temp;
	}

	TPolynomo& TPolynomo::operator*(TPolynomo _v) {
		TPolynomo temp;
		foreach((*this)) {
			temp.addElement(polynomoList[i]);
		}
		foreach(_v) {
			temp.addElement(_v.polynomoList[i], MUL);
		}
		return temp;
	}

	TPolynomo& TPolynomo::operator=(TPolynomo _v) {
		foreach(_v) {
			addElement(_v.polynomoList[i]);
		}
		return (*this);
	}

	void TPolynomo::addElement(mStruct elem, operation _oType) {
		__throwif__(&elem == nullptr);

		mStruct keyVal;
		switch (_oType) {
		case ADD:
		case SUB:
			foreach(polynomoList) {
				keyVal = polynomoList[i];

				if (keyVal.powerCombo == elem.powerCombo) {
					polynomoList.editNode(i, elem, _oType);
					return;
				}
			}
			break;
		case DIV:// Чтобы не было ошибки
		case MUL:
			foreach(polynomoList) {
				keyVal = polynomoList[i];

				if (keyVal.powerCombo == elem.powerCombo) {
					polynomoList.editNode(i, elem, _oType);
					continue;
				}
				mStruct* tNode = new mStruct(keyVal);
				(*tNode) = (*tNode) * elem;
				polynomoList.addNode(*tNode);
				delete tNode;
			}
			return;
		}
		polynomoList.addNode(elem);
	}

	string TPolynomo::printElem(mStruct _v) {
		int result[3]
			= {
				(int)(_v.powerCombo * 0.01) % 10,
				(int)(_v.powerCombo * 0.1) % 10,
				_v.powerCombo % 10
		};
		return	((result[0] > 0 ? "x^" + to_string(result[0]) : "")
			+ (result[1] > 0 ? " y^" + to_string(result[1]) : "")
			+ (result[2] > 0 ? " z^" + to_string(result[2]) : "")
			);
	}

	string TPolynomo::printElem(int _index) {
		return printElem(polynomoList[_index]);
	}

	string TPolynomo::printSolve() {
		int factor;
		string result;

		if (length == 0) {
			return "<no data>";
		}
		factor = polynomoList[0].factor;
		result = to_string(factor);

		if (factor != 0) {
			result += printElem(0);
		}

		for (uint i = 1; i < length; i++) {
			factor = polynomoList[i].factor;
			if (factor == 0) {
				continue;
			}
			result += (factor < 0 ? " - " : " + ") + to_string(abs(factor)) + printElem(i);
		}
		return result;
	}

	int TPolynomo::calcElem(mStruct _v, int x, int y, int z) {
		int result[3]
			= {
				(int)(_v.powerCombo * 0.01) % 10,
				(int)(_v.powerCombo * 0.1) % 10,
				_v.powerCombo % 10
		};
		return pow(x, result[0]) * pow(y, result[1]) * pow(z, result[2]);
	}

	int TPolynomo::calcElem(int index, int x, int y, int z) {
		return calcElem(polynomoList[index], x, y, z);
	}

	int TPolynomo::calcSolve(int x, int y, int z) {
		int result = 0;
		for (uint i = 0; i < length; i++) {
			result += polynomoList[i].factor * calcElem(i, x, y, z);
		}
		return result;
	}
}