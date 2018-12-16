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
	Node<Type>* pLast;
	Node<Type>* pFirst;
public:
	const int& length = size;

	TNodeList() {
		size = 0;
		pLast = nullptr;
		pFirst = nullptr;
	}
	TNodeList(int len, Type* vArray) {
		__throwif__(len < 0, len);
		pFirst = nullptr;
		repeat(len) {
			addNode(vArray[rep_i]);
		}
	}
	Node<Type>* addNode(Type value) {
		if (pFirst == nullptr) {
			pLast = new Node<Type>;
			pLast->value = value;
			pFirst = pLast;
		}
		else {
			pLast->pNext = new Node<Type>;
			pLast = pLast->pNext;
			pLast->value = value;
		}
		pLast->pNext = pFirst;
		size = size + 1;
		return pLast;
	}
	Node<Type>* getNode(int index){
		__throwif__(index >= size, index);
		if (index == size - 1) {
			return pLast;
		}
		if (index == 0) {
			return pFirst;
		}
		Node<Type>* tpNode = pFirst;
		repeat(index) {
			tpNode = tpNode->pNext;
		}
		return tpNode;
	}
	Node<Type>* findPrevious(Node<Type>* pNode) {
		Node<Type>* tpNode = pFirst;
		if (pNode == pFirst) {
			return pLast;
		}
		do {
			if (tpNode->pNext == pNode) {
				return tpNode;
			}
			tpNode = tpNode->pNext;
		} while (tpNode != pFirst);
		return nullptr;
	}
	Node<Type>* removeNode(Node<Type>* pNode) {
		__throwif__(isEmpty());
		__throwif__(pNode == nullptr);
		if (size == 1) {
			pFirst = nullptr;
			pLast = nullptr;
			delete pNode;
			size = 0;
			return nullptr;
		}
		Node<Type>* tpNode = findPrevious(pNode);
		if (tpNode == nullptr) {
			return nullptr;
		}
		if (tpNode->pNext == pFirst) {
			pFirst = pFirst->pNext;
		}
		if (tpNode->pNext == pLast) {
			pLast = tpNode;
		}
		tpNode->pNext = pNode->pNext;
		size = size - 1;
		delete pNode;
		return tpNode;
	}
	Node<Type>* removeNode(int index) {
		return removeNode(getNode(index));
	}
	Node<Type>* insertNodeAfter(int index, Node<Type>* newNode) {
		__throwif__(index < -1, index);
		__throwif__(index >= size, index);
		__throwif__(size == 0, size);
		if (index == size - 1) {
			return addNode(newNode.value);
		}
		Node<Type>* beforeNode;
		if (index == -1) {
			beforeNode = pLast;
		}
		else {
			beforeNode = getNode(index);
		}
		Node<Type>* afterNode = beforeNode->pNext;
		Node<Type>* insertNode = beforeNode->pNext = new Node<Type>(newNode);
		insertNode->pNext = afterNode;
		if (index == -1) {
			pFirst = insertNode;
		}
		size = size + 1;
		return insertNode;
	}
	Node<Type>* setNode(Node<Type>* pNode, Type newValue, operation operation = UNSET) {
		__throwif__(pNode == nullptr, pNode);
		switch (operation) {
		case ADD:
			pNode->value = (pNode->value + newValue); break;
		case SUB:
			pNode->value = (pNode->value - newValue); break;
		case MUL:
			pNode->value = (pNode->value * newValue); break;
		default:
			pNode->value = newValue;
		}
		return pNode;
	}
	Node<Type>* editNode(int index, Type newValue, operation operation = UNSET) {
		__throwif__(index < 0, index);
		return setNode(getNode(index), newValue, operation);
	}
	void operator=(TNodeList<Type>& right) {
		repeat(size) {
			removeNode(rep_i);
		}
		size = right.size;
		repeat(right.size) {
			addNode(right.getNodeValue(rep_i));
		}
	}
	Type getNodeValue(int index) {
		return getNode(index)->value;
	}
	Type operator[](int index){
		return getNodeValue(index);
	}
	bool isEmpty() {
		return (size < 1);
	}
	~TNodeList() {
		if (isEmpty()) {
			return;
		}
		Node<Type>* remNode;
		Node<Type>* tNode = pFirst;
		do {
			remNode = tNode;
			tNode = remNode->pNext;
			delete remNode;
		} while (tNode != pFirst);
	}
};