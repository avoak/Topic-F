/********************************************************************

Maximillian Brain
CSM20
BinaryNode.h
Compiling and Running

********************************************************************/

#ifndef _BINARY_NODE
#define _BINARY_NODE

template<class ItemType>
class BinaryNode
{
private:
	int					  bal = 0;		  // can be LH RH or EH
	ItemType              item;           // Data portion
	BinaryNode<ItemType>* leftChildPtr;   // Pointer to left child
	BinaryNode<ItemType>* rightChildPtr;  // Pointer to right child

public:
	BinaryNode()					   : leftChildPtr(nullptr), rightChildPtr(nullptr), bal(0)  {}
	BinaryNode(const ItemType& anItem) : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr), bal(0) {}

	BinaryNode(const ItemType& anItem, BinaryNode<ItemType>* leftPtr, BinaryNode<ItemType>* rightPtr) 
									   : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr), bal(0) {}

	BinaryNode(const BinaryNode<ItemType>& right) { *this = right; return *this; }


	void setItem(const ItemType& anItem)				  { item = anItem; }
	void setLeftChildPtr(BinaryNode<ItemType>* leftPtr)   { leftChildPtr = leftPtr; }
	void setRightChildPtr(BinaryNode<ItemType>* rightPtr) { rightChildPtr = rightPtr; }
	void setBal(const int& anInt) { bal = anInt; }


	bool isLeaf() const { return ( (leftChildPtr == nullptr) && (rightChildPtr == nullptr )); }



	ItemType getItem()						 const { return item; }
	BinaryNode<ItemType>* getLeftChildPtr()	 const { return leftChildPtr;  }
	BinaryNode<ItemType>* getRightChildPtr() const { return rightChildPtr; }
	int getBal()							 const { return  bal; }

	BinaryNode operator=(const BinaryNode<ItemType>& right);
}; // end BinaryNode

template <class ItemType>
BinaryNode<ItemType> BinaryNode<ItemType>::operator=(const BinaryNode<ItemType>& right)
{
	if (right == *this)
		return *this;
	bal = right->bal;
	leftChildPtr = right->leftChildPtr;
	rightChildPtr = right->rightChildPtr;
	item = right->item;
	return *this;
}
#endif