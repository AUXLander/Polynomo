#include <string>
#include "NodeList.h"
#include "Polynomo.h"

namespace std {


	TPolynomo::TPolynomo() {

	}

	TPolynomo::~TPolynomo() {

	}

	bool TPolynomo::loadString(string _string) {
		_string = _string.rfind(' ', 0);

		size_t cSplits = 1; // count of splits
		size_t tSize = _string.length();

		for (size_t i = 0, rfind = 0; i < tSize; i++) {
			rfind = _string.rfind(' ', i);
			if (rfind != string::npos) {
				cSplits = cSplits + 1;
				i = rfind + 1;
			}
		}

		//string* stringSplit =


		return false;
	}

	void TPolynomo::addElement(mStruct& elem) {
		__throwif__(&elem == nullptr);
		polynomoList.addNode(elem);
	}

	mStruct& TPolynomo::createElement(int factor, int _x = 0, int _y = 0, int _z = 0) {
		int _powerCombo = _x * 100 + _y * 10 + _z;
		mStruct* element = new mStruct{ factor, _powerCombo };

		return *element;
	}
}