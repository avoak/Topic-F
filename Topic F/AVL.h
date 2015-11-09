#ifndef _AVL
#define _AVL

#include "BinaryNode.h"

#include <iostream>

using namespace std;

/*	AVL Tree Library.
	Written by: G & F
	Date:       2/98
	
	Revised:    4/99 Converted to C++

	Brooks/Cole
	A division of Thomson Learning
	Copyright(c) 2001. All Rights Reserved

	
	Working And Compiling:	Maximillian Brain 
							CSM20
							11/15 
*/

//	==================== Static Global Variables  ====================
const static int LH = 1;     // Left High 
const static int EH = 0;     // Even High 
const static int RH = -1;    // Right High 

// Class Declaration
template <class ItemType, class ItemType2> 
class AvlTree
	{
		friend std::ostream &operator<<(std::ostream &, const AvlTree<ItemType,ItemType2> &);
	private:
	    int count;
		
	    BinaryNode<ItemType>  *tree;

	    BinaryNode<ItemType>  *Insert(BinaryNode<ItemType>  *root, BinaryNode<ItemType> *newPtr, bool &taller);

	    BinaryNode<ItemType>  *LeftBalance(BinaryNode<ItemType>  *root, bool& taller);
		BinaryNode<ItemType>  *RightBalance(BinaryNode<ItemType>  *root, bool& taller);

	    BinaryNode<ItemType>  *RotateLeft(BinaryNode<ItemType>  *root);
	    BinaryNode<ItemType>  *RotateRight(BinaryNode<ItemType>  *root);

	    BinaryNode<ItemType>  *Delete(BinaryNode<ItemType>  *root, ItemType2 dltKey, bool& shorter, bool& success);
		BinaryNode<ItemType>  *DltLeftBalance(BinaryNode<ItemType>  *root, bool& smaller);
	    BinaryNode<ItemType>  *DltRightBalance(BinaryNode<ItemType>  *root, bool& shorter);

	    BinaryNode<ItemType>  *Retrieve(ItemType2 key, BinaryNode<ItemType>  *root);
	                                  
	    void  Traversal(void (*process)(ItemType dataProc), BinaryNode<ItemType> *root); 
	    void  DestroyAVL(BinaryNode<ItemType>  *root);

	 public:
	    AvlTree() : count(0) , tree(nullptr) { }
		~AvlTree() { DestroyAVL(tree); }

	    bool  Insert(ItemType dataIn); 
	    bool  Delete(ItemType2  dltKey);
	    bool  Retrieve(ItemType2  key,     ItemType& dataOut);
	    void  Traverse (void (*process)(ItemType  dataProc));

	    bool  isEmpty() { return count == 0; }
	    bool  isFull();
		int   Count() { return count; }
	} ; // class AvlTree
	


/*	==================== Insert ==================== 
	This function inserts new data into the tree.
	   Pre    dataIn contains data to be inserted
	   Post   data have been inserted or memory overflow 
	   Return success (true) or overflow (false)
*/


template <class ItemType, class ItemType2>
bool   AvlTree<ItemType, ItemType2>::Insert(ItemType dataIn) 
{
//	Local Definitions 
	BinaryNode<ItemType>  *newPtr;
	bool         taller;

//	Statements 
	if (!(newPtr = new BinaryNode<ItemType>))
	   return false;
	newPtr->setBal(EH);
	newPtr->setRightChildPtr(nullptr);
	newPtr->setLeftChildPtr(nullptr);
	newPtr->setItem(dataIn);
   
	tree = Insert(tree, newPtr, taller);
	count++;
	return true;
}	//  Avl_Insert   

/*	======================= Insert =======================
	This function uses recursion to Insert the new data into 
	a leaf BinaryNode in the AVL tree.
	   Pre    application has called Insert, which passes 
	          root and data pointers
	   Post   data have been inserted
	   Return pointer to [potentially] new root
*/

template <class ItemType, class ItemType2>
BinaryNode<ItemType>*  AvlTree<ItemType, ItemType2>::Insert(BinaryNode<ItemType> *root, BinaryNode<ItemType> *newPtr, bool& taller)
{
//	Statements   
	if (!root)
	   {
	    root    = newPtr;
	    taller  = true;
	    return  root;
	   } //  if nullptr tree 
 
	if (newPtr->getItem() < root->getItem())
	   {
	    root->setLeftChildPtr(Insert(root->getLeftChildPtr(), newPtr, taller));
	    if (taller)
	       //  Left subtree is taller 
	       switch (root->getBal())
	          {
	           case LH: // Was leftChild high--rotate 
	                    root = LeftBalance (root, taller);
	                    break;

	           case EH: // Was balanced--now LH 
	                    root->setBal(LH);
	                    break;

	           case RH: // Was rightChild high--now EH 
	                    root->setBal(EH);
	                    taller = false;
	                    break;
	          } // switch 
	   } //  new < BinaryNode 
	else 
	   //  new data >= root data 
	   {
	    root->setRightChildPtr(Insert (root->getRightChildPtr(), newPtr, taller));
	    if (taller)
	       // Right subtree is taller
	       switch (root->getBal())
	           {
	            case LH: // Was leftChild high--now EH 
	                     root->setBal(EH);
	                     taller    = false;
	                     break;
	            
	            case EH: // Was balanced--now RH
						root->setBal(RH);
	                     break;
	
	            case RH: // Was rightChild high--rotate 
	                     root = RightBalance (root, taller);
	                     break;
	           } //  switch 
	   } //  else new data >= root data 
	return root;
}	//  Insert 

/*	===================== LeftBalance ===================== 
	The tree is out of balance to the leftChild. This function 
	rotates the tree to the rightChild.
	   Pre     the tree is leftChild high 
	   Post    balance restored  
	   Returns potentially new root 
*/

template <class ItemType, class ItemType2>
BinaryNode<ItemType>  *AvlTree<ItemType, ItemType2>:: LeftBalance(BinaryNode<ItemType> *root,bool& taller) 
{
// 	Local Definitions 
	BinaryNode<ItemType>  *rightTree;
	BinaryNode<ItemType>  *leftTree;

//	Statements 
	leftTree = root->getLeftChildPtr();
	switch (leftTree->getBal())
	   {
	    case LH: // Left High--Rotate Right 
					root->setBal(EH);
	                leftTree->setBal(EH);
	             
	             // Rotate Right 
	                root     = RotateRight (root);
	                taller   = false;
	             break;
	    case EH: // This is an error 
	                cout <<"\n\a\aError in LeftBalance\n";
	                exit (100); 
	    case RH: // Right High - Requires double rotation: 
	             // first leftChild, then rightChild 
	                rightTree = leftTree->getRightChildPtr();
	                switch (rightTree->getBal())
	                   {
	                    case LH: root->setBal(RH);
	                             leftTree->setBal(EH);
	                             break;
	                    case EH: root->setBal(EH);
	                             leftTree->setBal(EH);
	                             break;
	                    case RH: root->setBal(EH);
	                             leftTree->setBal(LH);
	                             break;
	                   } //  switch rightTree 
	             
	                rightTree->setBal(EH);
	                //  Rotate Left 
	                root->setLeftChildPtr(RotateLeft (leftTree));
	             
	                // Rotate Right 
	                root    = RotateRight (root);
	                taller  = false;
	   } // switch leftTree
	return root;
}	// LeftBalance 

/*	===================== RotateLeft ====================== 
	This function exchanges pointers so as to rotate the  
	tree to the leftChild.
	   Pre  root points to tree to be rotated 
	   Post BinaryNode rotated and new root returned 
*/

template <class ItemType, class ItemType2>
BinaryNode<ItemType>*  AvlTree<ItemType, ItemType2>::RotateLeft(BinaryNode<ItemType>  *root) 
{
//	Local Definitions 
	BinaryNode<ItemType>  *tempPtr;

//	Statements 
	tempPtr        = root->getRightChildPtr();
	root->setLeftChildPtr(tempPtr->getLeftChildPtr());
	tempPtr->setLeftChildPtr(root);

	return tempPtr;
}	//  RotateLeft 

/*	===================== RotateRight ===================== 
	This function exchanges pointers to rotate the tree
	to the rightChild.
	   Pre   root points to tree to be rotated 
	   Post  BinaryNode rotated and new root returned 
*/

template <class ItemType, class ItemType2>
BinaryNode<ItemType>*  AvlTree<ItemType, ItemType2>::RotateRight(BinaryNode<ItemType> *root) 
{
//	Local Definitions 
	BinaryNode<ItemType>  *tempPtr;

//	Statements 
	tempPtr         = root->getLeftChildPtr();
	root->setLeftChildPtr(tempPtr->getRightChildPtr());
	tempPtr->setRightChildPtr(root);

	return tempPtr;
}	//  RotateRight  

/*	====================  RightBalance ===================
	The tree is out-of-balance to the rightChild. This function 
	rotates the tree to the leftChild.
	   Pre     The tree is rightChild high 
	   Post    Balance restored 
	   Returns potentially new root 
*/

template <class ItemType, class ItemType2>
BinaryNode<ItemType>* AvlTree<ItemType, ItemType2>::RightBalance(BinaryNode<ItemType> *root, bool& taller) 
{
//	Local Definitions 
	BinaryNode<ItemType> *rightTree(root->getRightChildPtr());
	BinaryNode<ItemType> *leftTree;
 
//	Statements 
	//rightTree = root->rightChild;
	switch (rightTree->getBal())
	   {
	    case LH: // Left High - Requires double rotation:
	             //             first rightChild, then leftChild 
	                leftTree = rightTree->getLeftChildPtr();
  	 	 			
	                //  First Rotation - Left 
	                switch (leftTree->getBal()) 
	                   {
	                    case RH: root->setBal(LH);
	                             rightTree->setBal(EH);
	                             break;

	                    case EH: root->setBal(EH);
	                             rightTree->setBal(EH);
	                             break;
	
	                    case LH: root->setBal(EH);
	                             rightTree->setBal(RH);
	                             break;
	                   } //  switch 
  	 	 			leftTree->setBal(EH);
  	 	 			
	                root->setRightChildPtr(RotateRight (rightTree));
	                root          = RotateLeft  (root);
	                taller        = false;
	                break;

	     case EH: // Deleting from balanced BinaryNode 
				     root->setBal(EH);
	                 taller    = false;
	                 break;
						 	 
   	 	 case RH: // Right High - Rotate Left 
	                 root->setBal(EH);
	                 rightTree->setBal(EH);
	                 root            = RotateLeft (root);
	                 taller          = false;
	                 break;
  	 	} // switch 
	return root;
}	//  RightBalance   

/*	====================== Delete ====================== 
	This function deletes a BinaryNode from the tree and rebalances 
	it if necessary. 
	   Pre    dltKey contains key to be deleted
	   Post   the BinaryNode is deleted and its space recycled
	          -or- an error code is returned 
	   Return success (true) or not found (false)
*/

template <class ItemType, class ItemType2>
bool  AvlTree <ItemType, ItemType2>::Delete(ItemType2  dltKey)
{
//	Local Definitions 
	bool shorter;
	bool success;

	BinaryNode<ItemType>  *newRoot;

//	Statements 
	newRoot = Delete (tree, dltKey, shorter, success);
	if (success)
	   {
	    tree = newRoot;
	    count--;
	   } // if 
	return success;
}	// Delete

/*	======================== Delete ======================= 
	This function deletes a BinaryNode from the tree and rebalances 
	it if necessary. 
	   Pre    dltKey contains key of BinaryNode to be deleted
	          shorter is Boolean indicating tree is shorter
	   Post   the BinaryNode is deleted and its space recycled
	          -or- if key not found, tree is unchanged 
	   Return true if deleted, false if not found
	          pointer to root
*/

template <class ItemType, class ItemType2>
BinaryNode<ItemType>* AvlTree<ItemType, ItemType2>::Delete(BinaryNode<ItemType> *root, ItemType2 dltKey, bool& shorter, bool& success)
{
//  Local Definitions 
	BinaryNode<ItemType> *dltPtr;
	BinaryNode<ItemType> *exchPtr;
	BinaryNode<ItemType> *newRoot;

// 	Statements 
	if (!root)
	   {
	    shorter = false;
	    success = false;
	    return nullptr;
	   } //  if -- base case 
	
	if ( root->getItem() > dltKey)
	    {
	     root->setLeftChildPtr(Delete (root->getLeftChildPtr(), dltKey, 
	                           shorter,    success));
	     if (shorter)
	         root   = DltRightBalance (root, shorter);
	    } // if less 
	else if (root->getItem() < dltKey)
	    {
	     root->setRightChildPtr(Delete (root->getRightChildPtr(), dltKey,
	                            shorter,     success));
	     if (shorter)
	         root = DltLeftBalance (root, shorter);
	    } //  if greater 
	else
	    //  Found equal BinaryNode 
	    {
	     dltPtr  = root;
	     if (!root->getRightChildPtr())
	         // Only leftChild subtree 
	         {
	          newRoot  = root->getLeftChildPtr();
	          success  = true;
	          shorter  = true;
	          delete (dltPtr);
	          return newRoot;            //  base case 
	         } //  if true 
	     else
	         if (!root->getLeftChildPtr())
	             //  Only rightChild subtree 
	             {
	              newRoot  = root->getRightChildPtr();
	              success  = true;
	              shorter  = true;
	              delete (dltPtr);
	              return newRoot;        // base case 
	            } //  if 
	         else
	             //  Delete BinaryNode has two subtrees 
	             {
	              exchPtr = root->getLeftChildPtr();
	              while (exchPtr->getRightChildPtr())
	                  exchPtr = exchPtr->getRightChildPtr();
	                  
	              root->setItem(exchPtr->getItem());
				  delete(root->getLeftChildPtr());
	              if (shorter)
	                  root = DltRightBalance (root, shorter); 
	             } //  else 
	
	    } // equal BinaryNode 
	return root; 
}	// Delete 

  // ================== DltLeftBalance ==================
/*	The tree is out-of-balance to the leftChild (leftChild high)--
	rotates the tree to the rightChild.
	   Pre     The tree is leftChild high 
	   Post    Balance has been restored 
	   Returns potentially new root 
*/

template <class ItemType, class ItemType2>
BinaryNode<ItemType>*  AvlTree<ItemType, ItemType2>::DltLeftBalance(BinaryNode<ItemType> *root, bool &smaller) 
{
//	Local Definitions 
	BinaryNode<ItemType>  *rightTree;
	BinaryNode<ItemType>  *leftTree;
  	 
//	Statements 
	switch (root->getBal())
	    {
	     case RH:  root->setBal(EH);
	               break;
  	 	 			
	     case EH:  // Delete occurred on rightChild 
		           root->setBal(LH);
		           smaller    = false;
		           break;
						  	 	 
	     case LH:  leftTree = root->getLeftChildPtr();
		           switch (leftTree->getBal()) 
		              {
		               case LH:
		               case EH: // Rotate Single Left 
		                        if (leftTree->getBal()  == EH)
		                           {
		                            root->setBal(LH);
		                            leftTree->setBal(RH);
		                            smaller       = false;
		                           } // if
		                        else
		                           {
		                            root->setBal(EH);
		                            leftTree->setBal(EH);
		                           } // else

		                        root = RotateRight (root);
		                        break;
  	 	 				 			
		               case RH:	//Double Rotation 
		                        rightTree = leftTree->getRightChildPtr();
		                        switch (rightTree->getBal())
		                           {
		                            case LH: root->setBal(RH);
		                                     leftTree->setBal(EH);
		                                     break;
		                            case EH: root->setBal(EH);
		                                     leftTree->setBal(EH);
		                                     break;
		                            case RH: root->setBal(EH);
		                                     leftTree->setBal(LH);
		                                     break;
		                           } //  switch 
		                        rightTree->setBal(EH);
		                        root->setLeftChildPtr(RotateLeft (leftTree));
		                        root           = RotateRight (root);
		                        break;
		              } //  switch : leftTree->bal  
  	 	 				   	 	 			
 	 	} //  switch : root->bal 
	return root; 
}	// DltLeftBalance 

/*	=================== DltRightBalance ==================  
	The tree is shorter after a delete on the leftChild. 
	Adjust the balance factors and rotate the tree 
	to the leftChild if necessary.
	   Pre     the tree is shorter 
	   Post    balance factors adjusted and balance restored 
	   Returns potentially new root 
*/

template <class ItemType, class ItemType2>
BinaryNode<ItemType>*  AvlTree<ItemType,  ItemType2>::DltRightBalance (BinaryNode<ItemType>  *root, bool& shorter) 
{
//  Local Definitions 
	BinaryNode<ItemType>  *rightTree;
	BinaryNode<ItemType>  *leftTree;
	
//	Statements
	switch (root->getBal())
	   {
	    case LH: //  Deleted Left--Now balanced 
	             root->setBal(EH);
	             break;
	    case EH: //  Now Right high 
	             root->setBal(RH);
	             shorter    = false;
	             break;
	    case RH: //  Right High - Rotate Left 
	             rightTree = root->getRightChildPtr();
	             if (rightTree->getBal() == LH)
	                 // Double rotation required 
	                 {
	                  leftTree  = rightTree->getLeftChildPtr();
	               
	                  switch (leftTree->getBal())
	                      {
	                       case LH: rightTree->setBal(RH);
	                                root->setBal(EH);
	                                break;
	                       case EH: root->setBal(EH);
	                                rightTree->setBal(EH);
	                                break;
	                       case RH: root->setBal(LH);
	                                rightTree->setBal(EH);
	                                break;
	                      } // switch 
	                   
	                  leftTree->setBal(EH);
	               
	                  // Rotate Right then Left 
	                  root->setRightChildPtr(RotateRight (rightTree));
	                  root        = RotateLeft  (root);
	                 } //  if rightTree->bal == LH 
	             else
	                {
	                 //  Single Rotation Only 
	                 switch (rightTree->getBal())
	                    {
	                     case LH:
	                     case RH: root->setBal(EH);
	                              rightTree->setBal(EH);
	                              break;
	                     case EH: root->setBal(RH);
	                              rightTree->setBal(LH);
	                              shorter        = false;
	                              break;
	                    } // switch rightTree->bal 
	                 root = RotateLeft (root);
	                } // else 
	    } //  switch root bal 
	return root;
}	//  DltRightBalance 

/*	==================== Retrieve ===================  
	Retrieve BinaryNode searches the tree for the BinaryNode containing 
	the requested key and returns pointer to its data.
	   Pre     dataOut is variable to receive data
	   Post    tree searched and data returned
	   Return  true if found, false if not found
*/

template <class ItemType, class ItemType2>
bool   AvlTree<ItemType, ItemType2>::Retrieve(ItemType2 key, ItemType& dataOut)
{
//	Local Definitions
	BinaryNode<ItemType> *BinaryNode;
	
//	Statements 
	if (!tree)
	   return false;
	   
	BinaryNode    = Retrieve (key, tree);
	if (BinaryNode)
	   {
	    dataOut = BinaryNode->getItem();
	    return true;
	   } // if found
	else
	   return false;
}	//  Retrieve 

/*	===================== Retrieve ===================== 
	Retrieve searches tree for BinaryNode containing requested 
	key and returns its data to the calling function.
	   Pre     Retrieve called: passes key to be located 
	   Post    tree searched and data pointer returned 
	   Return  address of matching BinaryNode returned 
	           if not found, NULL returned 
*/

template <class ItemType, class ItemType2>
BinaryNode<ItemType>*  AvlTree<ItemType, ItemType2>::Retrieve(ItemType2 key, BinaryNode<ItemType> *root)
{
//	Statements 
	if (root)
	    {
	     if (root->getItem() > key)
	         return Retrieve (key, root->getLeftChildPtr());
	     else if (root->getItem() < key)
	         return Retrieve (key, root->getRightChildPtr());
	     else
	         // Found equal key 
	         return (root);
	    } // if root 
	else
	    //Data not in tree 
	    return root;
}	//  Retrieve 

/*	==================== Traverse ==================== 
	Process tree using inorder traversal. 
	   Pre   process used to "visit" BinaryNodes during traversal 
	   Post  all BinaryNodes processed in LNR (inorder) sequence 
*/

template <class ItemType, class ItemType2>
void  AvlTree<ItemType, ItemType2>::Traverse(void(*process) (ItemType dataProc))
{
//	Statements 
	Traversal (process, tree);
	return;
}	// end Traverse 

/*	===================== Traversal ===================== 
	Traverse tree using inorder traversal. To process a
	BinaryNode, we use the function passed when traversal is called.
	   Pre   tree has been created (may be null) 
	   Post  all BinaryNodes processed 
*/

template <class ItemType, class ItemType2>
void  AvlTree<ItemType, ItemType2>:: Traversal(void(*process)(ItemType dataproc),BinaryNode<ItemType> *root)
{
//	Statements 
	if (root)
	   {
	    Traversal  (process, root->leftChild);
	    process     (root->data);
	    Traversal  (process, root->rightChild);
	   } //  if 
	return;
}	//  Traversal 

/*	=================== isFull =================== 
	If there is no room for another BinaryNode, returns true.
	   Pre      tree has been created
	   Returns  true if no room, false if room 
*/

template <class ItemType, class ItemType2>
bool AvlTree<ItemType, ItemType2>::isFull()
{
//	Local Definitions 
	BinaryNode<ItemType>  *newPtr;
	
//	Statements 
	newPtr = new BinaryNode<ItemType>;
	if (newPtr)
	   {
	    delete  newPtr;
	    return false;
	   } // if
	else
	   return true;
}	//  isFull 


/*	=================== DestroyAVL =================== 
	Deletes all data in tree and recycles memory.
	The BinaryNodes are deleted by calling a recursive
	function to traverse the tree in postorder sequence.   
	   Pre   tree is being destroyed 
	   Post  all data have been deleted 
*/

template <class ItemType, class ItemType2>
void  AvlTree<ItemType, ItemType2>:: DestroyAVL(BinaryNode<ItemType>  *root)
{
//	Statements 
	if (root)
	   {
	    DestroyAVL (root->getLeftChildPtr());
	    DestroyAVL (root->getRightChildPtr());
	    delete root;
	   } // if 
	return;
}	//  DestroyAVL

template<class ItemType, class ItemType2>
ostream &operator<<(ostream& out, const AvlTree<ItemType, ItemType2>& anAvlTree)
{
	out << anAvlTree.Count() << endl;
	return out;
}

#endif

