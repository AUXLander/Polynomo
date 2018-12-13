#pragma once
#include <string>
#include "NodeList.h"
#define mStruct mStruct // dark & soft neone - Drive (2011)

struct mStruct {
	int factor;
	int powerCombo;

	mStruct& operator+(const mStruct& _v) {
		factor += _v.factor;
		return (*this);
	}
	mStruct& operator-(const mStruct& _v) {
		factor -= _v.factor;
		return (*this);
	}
	mStruct& operator*(const mStruct& _v) {
		factor *= _v.factor;
		powerCombo += powerCombo;
		return (*this);
	}
	mStruct& operator/(const mStruct& _v) {
		factor /= _v.factor;
		powerCombo -= powerCombo;
		return (*this);
	}
	mStruct& operator=(const mStruct& _v) {
		factor = _v.factor;
		powerCombo = _v.powerCombo;
		return (*this);
	}
};

namespace std {
	class TPolynomo {
		TNodeList<mStruct> polynomoList;

	public:
		TPolynomo();

		mStruct& createElement(int factor, int _x = 0, int _y = 0, int _z = 0) {
			int _powerCombo = _x * 100 + _y * 10 + _z;
			mStruct* element = new mStruct{ factor, _powerCombo };

			return (*element);
		}

		void addElement(mStruct& elem, operation _oType = UNSET) {
			__throwif__(&elem == nullptr);

			mStruct key;
			switch (_oType) {
			case ADD:
			case SUB:
				foreach(key, polynomoList) {
					key = polynomoList[i];

					if (key.powerCombo == elem.powerCombo) {
						polynomoList.editNode(i, elem, _oType);
						return;
					}
				}
				break;
			case MUL:
				foreach(key, polynomoList) {
					key = polynomoList[i];

					if (key.powerCombo == elem.powerCombo) {
						polynomoList.editNode(i, elem, _oType);
					}
					else {
						mStruct* tNode = new mStruct(key);
						(*tNode) = (*tNode) * elem;
						polynomoList.addNode(*tNode);
						delete tNode;
					}
				}
				return;
				break;
			default:
				polynomoList.addNode(elem);
				break;
			}
		}

		string decodeElem(mStruct& _v);

		string getElement(int _index);


		string getSolve();

		string getSolve(int x, int y, int z);

		

		bool loadBin(string filepath);

		bool saveBin(string filepath);

		TPolynomo& operator+(TPolynomo& v);

		TPolynomo& operator-(TPolynomo& v);

		TPolynomo& operator*(TPolynomo& v);

		//TPolynomo& operator/(TPolynomo& v);

		void print();

		~TPolynomo();
	};

}
