#pragma once
#include "ToolSet.h"

enum operation { UNSET, ADD, SUB, MUL };

template<typename Type>
struct Node {
	Type value;
	Node* pNext;
};

template<class Type>
class TNodeList {
	int size;
	int lastOut;// for optimize
	Node<Type>* pLast;
	Node<Type>* pFirst;
	Node<Type>* pLastOut;// for optimize
public:
	const int& length = size;

	TNodeList() {
		size = 0;
		pLast = nullptr;
		pFirst = nullptr;
	}
	TNodeList(int _size, Type* _vArray) {
		__throwif__(_size < 0, _size);
		pFirst = nullptr;

		repeat(_size) {
			addNode(_vArray[rep_i]);
		}
	}
	Node<Type>* addNode(Type _value) {
		if (pFirst == nullptr) {
			pLast = new Node<Type>;
			pLast->value = _value;
			pFirst = pLast;
		}
		else {
			pLast->pNext = new Node<Type>;
			pLast = pLast->pNext;
			pLast->value = _value;
		}

		pLast->pNext = pFirst;
		size = size + 1;

		return pLast;
	}
	Node<Type>* getNode(int _index){
		__throwif__(_index >= size, _index);

		if (_index == size - 1) {
			return pLast;
		}
		if (_index == 0) {
			return pFirst;
		}

		Node<Type>* tpNode = pFirst;
		repeat(_index) {
			tpNode = tpNode->pNext;
		}
		return tpNode;
	}
	Node<Type>* findPrevious(Node<Type>* _pNode, uint* index = nullptr) {
		Node<Type>* tpNode = pFirst;

		if (_pNode == pFirst) {
			(*index) = size - 1;
			return pLast;
		}

		do {
			if (tpNode->pNext == _pNode) {
				return tpNode;
			}
			if (index != nullptr) {
				++(*index);
			}
			tpNode = tpNode->pNext;
		} while (tpNode != pFirst);

		return nullptr;
	}

	Node<Type>* removeNode(Node<Type>* _pNode) {
		__throwif__(size == 0);
		__throwif__(_pNode == nullptr);

		if (size == 1) {
			pFirst = nullptr;
			pLast = nullptr;
			delete _pNode;
			size = 0;
			return nullptr;
		}

		uint *index = new uint;
		*index = 0;
		Node<Type>* tpNode = findPrevious(_pNode, index);

		if (tpNode == nullptr) {
			return nullptr;
		}

		if (tpNode->pNext == pFirst) {
			pFirst = pFirst->pNext;
		}
		
		if (tpNode->pNext == pLast) {
			pLast = tpNode;
		}

		tpNode->pNext = _pNode->pNext;
		size = size - 1;

		delete index, _pNode;
		return tpNode;
	}
	Node<Type>* removeNode(int _index) {
		return removeNode(getNode(_index));
	}
	Node<Type>* insertNodeAfter(int _index, Node<Type>* _v) {
		__throwif__(_index < -1, _index);
		__throwif__(_index >= size, _index);
		__throwif__(size == 0, size);

		if (_index == size - 1) {
			return addNode(_v.value);
		}

		Node<Type>* beforeNode;
		if (_index == -1) {
			beforeNode = pLast;
		}
		else {
			beforeNode = getNode(_index);
		}

		Node<Type>* afterNode = beforeNode->pNext;
		Node<Type>* insertNode = beforeNode->pNext = new Node<Type>(_v);
		insertNode->pNext = afterNode;

		if (_index == -1) {
			pFirst = insertNode;
		}

		size = size + 1;

		return insertNode;
	}
	Node<Type>* setNode(Node<Type>* _pNode, Type _newValue, operation _oType = UNSET) {
		__throwif__(_pNode == nullptr, _pNode);

		switch (_oType) {
		case ADD:
			_pNode->value = (_pNode->value + _newValue); break;
		case SUB:
			_pNode->value = (_pNode->value - _newValue); break;
		case MUL:
			_pNode->value = (_pNode->value * _newValue); break;
		default:
			_pNode->value = _newValue;
		}
		return _pNode;
	}
	Node<Type>* editNode(int _index, Type _newValue, operation _oType = UNSET) {
		__throwif__(_index < 0, _index);
		return setNode(getNode(_index), _newValue, _oType);
	}
	Type getNodeValue(int _index) {
		return getNode(_index)->value;
	}
	Type operator[](int _index){
		return getNodeValue(_index);
	}
	~TNodeList() {
		Node<Type>* remNode;
		Node<Type>* tNode = pFirst;
		do {
			remNode = tNode;
			tNode = remNode->pNext;
			delete remNode;
		} while (tNode != pFirst);
	}
};