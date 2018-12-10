#pragma once
#include "ToolSet.h"

template<typename Type>
struct Node {
	Type value;
	Node* pNext;
};

template<class Type>
class TNodeList {
	int size;
	int lastOut;// try to optimize
	Node<Type>* pLast;
	Node<Type>* pFirst;
	Node<Type>* pLastOut;// try to optimize

public:
	TNodeList() {
		size = 0;
		lastOut = 0;
		pLastOut = nullptr;
	}
	TNodeList(int _size, Type* _vArray) {
		__throwif__(_size < 0, _size);

		for (size_t i = 0; i < _size; i++) {
			addNode(_vArray[i]);
		}

		lastOut = 0;
		pLastOut = pFirst;
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

	Node<Type>* getNode(int _index) {
		__throwif__(_index >= size, _index);

		if (_index == size - 1) {
			return pLast;
		}

		if (_index == 0) {
			return pFirst;
		}

		int i = 0;
		Node<Type>* tpNode = pFirst;

		if (lastOut < _index) {
			i = lastOut;
			tpNode = pLastOut;
		}

		for (; i < _index; lastOut = i++) {
			pLastOut = tpNode = tpNode->pNext;
		}

		return tpNode;
	}

	Node<Type>* findNode(Type _value) {
		Node<Type>* tpNode = pFirst;

		do {
			if (tpNode->value == _value) {
				return tpNode;
			}
			tpNode = tpNode->pNext;
		} while (tpNode != pFirst);

		return nullptr;
	}

	Node<Type>* removeNode(Node<Type>* _pNode) {
		__throwif__(size == 0);

		if (_pNode == pLastOut) {
			pLastOut = pFirst;
			lastOut = 0;
		}

		if (size == 1) {
			pFirst = nullptr;
			pLast = nullptr;
			delete _pNode;
			size = size - 1;
			return nullptr;
		}

		Node<Type>* tcNode = pLast;
		do {
			if (tcNode->pNext == _pNode) {
				tcNode->pNext = _pNode->pNext;

				if (_pNode == pFirst) {
					pFirst = tcNode->pNext;
				}
				if (_pNode == pLast) {
					pLast = tcNode;
				}
				delete _pNode;
				size = size - 1;

				return tcNode;
			}
			tcNode = tcNode->pNext;
		} while (tcNode->pNext != pFirst);

		return nullptr;
	}

	Node<Type>* insertNodeAfter(int _index, Node<Type>& _v) {
		__throwif__(_index < -1, _index);
		__throwif__(_index >= size, _index);
		__throwif__(size == 0, size);

		if (_index == size - 1) {
			lastOut = 0;
			pLastOut = pFirst;
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

		lastOut = 0;
		pLastOut = pFirst;
		return insertNode;
	}

	Type getNodeValue(int _index) {
		return getNode(_index)->value;
	}

	size_t getSize() {
		return size;
	}

	~TNodeList(){
		Node<Type>* remNode;
		Node<Type>* tNode = pFirst;
		do {
			remNode = tNode;
			tNode = remNode->pNext;
			delete remNode;
		} while (tNode != pFirst);
	}
};