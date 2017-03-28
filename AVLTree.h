/*
	Name       : Ian David Gregory
	Class      : CSC 2110-002
	Date       : 11-18-2016
	Instructor : Dr. Brown
*/

#if !defined (NULL)
#define NULL 0
#endif

#if !defined (AVLTREE_H)
#define AVLTREE_H

#include "Drawable.h"
#include "AVLTreeIterator.h"
#include "Line.h"

#include <iostream>
using namespace std;

template < class T >
class AVLTree : public Drawable
{
   
   private:
   
      bool avlFlag;
      int sze;
	  
	  AVLTreeNode<T>* root;

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (String* key, T* item);
	  
	  /*
		Pre :
		Post: Sets root to node
	  */	  
      void setRootNode(AVLTreeNode<T>* tNode); 	  //you can get by without using these methods, refer to root directly
	  
	  /*
		Pre :
		Post: Returns the root
	  */	  
      AVLTreeNode<T>* getRootNode(); 
	  
	  /*
		Pre :
		Post: Returns height from node
	  */	  
      int getHeight(AVLTreeNode<T>* tNode);
	  
	  /*
		Pre :
		Post: Returns if balanced or not
	  */	  
      int isBalanced(AVLTreeNode<T>* tNode);
	  
	  /*
		Pre :
		Post: Checks if balanced
	  */	  
      bool checkBalanceFactors(AVLTreeNode<T>* tNode);
	  
	  /*
		Pre :
		Post: Removes all the items from tree
	  */	  
      void destroyItem(AVLTreeNode<T>* tNode);

	  /*
		Pre :
		Post: Removes items from the root
	  */	  
      void destroy();

	  /*
		Pre :
		Post: Returns the node of the item added
	  */	  
      AVLTreeNode<T>* insertItem(AVLTreeNode<T>* tNode, T* item); 

	  /*
		 Got this from the Program 5 files
	  */	  
      AVLTreeNode<T>* removeItem(AVLTreeNode<T>* tNode, String* searchKey);

	  /*
		 Got this from the Program 5 files
	  */	  
      AVLTreeNode<T>* removeNode(AVLTreeNode<T>* tNode);

	  /*
		 Got this from the Program 5 files
	  */	  
      AVLTreeNode<T>* removeLeftMost(AVLTreeNode<T>* tNode);

	  /*
		 Got this from the Program 5 files
	  */	  
      T* findLeftMost(AVLTreeNode<T>* tNode);
	  
	  /*
		Pre :
		Post: Returns node after rotation
	  */	  	  
      AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* tNode);
	  
	  /*
		Pre :
		Post: Return node after rotation
	  */	  	  
      AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* tNode);

      //write and use methods to do each of the four rotations (SR, SL, DLR, DRL)

	  /*
		Pre :
		Post: Returns node after 2 rotations
	  */	  	  	  
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode);

	  /*
		Pre :
		Post: Returns node after 2 rotations
	  */	  	  	  
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode);
	  
	  
	  /*
		Pre :
		Post: Returns node when the rotations are complete
	  */	  
      AVLTreeNode<T>* avlFixAddLeft(AVLTreeNode<T>* tNode);
	  
	  /*
		Pre :
		Post: Returns node when the rotations are complete
	  */
      AVLTreeNode<T>* avlFixAddRight(AVLTreeNode<T>* tNode); 
	  
	  /*
		 Got this from the Program 5 files
	  */	  
      AVLTreeNode<T>* avlFixRemoveLeft(AVLTreeNode<T>* tNode);
	  
	  /*
		 Got this from the Program 5 files
	  */	  
      AVLTreeNode<T>* avlFixRemoveRight(AVLTreeNode<T>* tNode);
	  
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left); //changes balance factors, calls the other DLR to do two rotations
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right); //changes balance factors, calls the other DRL to do two rotations

      virtual void drawRec(AVLTreeNode<T>* tNode, wxDC&  dc, Line* line, int x_parent, int x_curr, int y_curr);

   public:
	
	  AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));//
      ~AVLTree();
	  
	  /*
		Pre :
		Post: Returns size
	  */
	  int size(); 
	  
	  /*
		Pre :
		Post:  insert an item in the tree
	  */	  
	  void insert(T* item);

	  /*
		Pre :
		Post: removes the key given from the tree
	  */	  
	  void remove(String* sk);

	  /*
		Pre :
		Post: returns the item given
	  */	  
      T* retrieve(String* sk);

	  /*
		Pre :
		Post: returns if tree is empty or not
	  */	  
      bool isEmpty();

	  /*
		Pre :
		Post:  removes everything from the tree
	  */	  
      void makeEmpty();
	  
	  /*
		Pre :
		Post: Returns the root item
	  */	  
      T* getRootItem();
	  
      AVLTreeIterator<T>* iterator();

	  /*
		Pre :
		Post: Return the height of the sub tree
	  */	  
      int getHeight();
	  
	  /*
		Pre :
		Post: returns if balance or not
	  */	  
      bool isBalanced();
	  
	  /*
		Pre :
		Post: returns if node is balanced or not
	  */	  
      bool checkBalanceFactors();
		
	  /////////////////////////////////////////
      void draw(wxDC&  dc, int width, int height);
      void mouseClicked(int x, int y);

};

template < class T >
void AVLTree<T>::setRootNode(AVLTreeNode<T>* tNode)
{
	root = tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::getRootNode()
{
	return root;
}

template < class T >
int AVLTree<T>::getHeight(AVLTreeNode<T>* tNode)
{
	if(tNode == NULL)
	{
		return 0;
	}
	else
	{
		int left = getHeight(tNode->getLeft());
		int right = getHeight(tNode->getRight());

		if(left >= right)
		{
			return left + 1;
		}
		else
		{
			return right + 1;
		}
	}
}

template < class T >
int AVLTree<T>::isBalanced(AVLTreeNode<T>* tNode)
{
	if(tNode == NULL) return true;
	
	AVLTreeNode<T>* left = tNode->getLeft();
	AVLTreeNode<T>* right = tNode->getRight();
	
	bool left_Bal = isBalanced(left);
	if(left_Bal == false) return false;
	
	bool right_Bal = isBalanced(right);
	if(right_Bal == false) return false;
	
	int lh = getHeight(left);
	int rh = getHeight(right);
	if(abs(lh-rh) > 1) return false;
	
	return true;
}

template < class T >
bool AVLTree<T>::checkBalanceFactors(AVLTreeNode<T>* tNode)
{
	return isBalanced(tNode);
}

template < class T >
void AVLTree<T>::destroyItem(AVLTreeNode<T>* tNode)
{
   if(tNode != NULL)
   {
       destroyItem(tNode->getLeft());
	   destroyItem(tNode->getRight());
	   delete tNode;
   }	
}

template < class T >
void AVLTree<T>::destroy()
{
	destroyItem(root);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::insertItem(AVLTreeNode<T>* tNode, T* item)
{
	
	if(tNode == NULL)
	{
		tNode = new AVLTreeNode<T>(item);
		tNode->setBalanceFactor(BALANCED);

		avlFlag = true;
		sze++;
		return tNode;
	}
	
	AVLTreeNode<T>* sub;
	T* node_items = tNode->getItem();
	int comp = (*compare_items)(item, node_items);
	
	if(comp < 0)
	{
		sub = insertItem(tNode->getLeft(), item);
		tNode->setLeft(sub);
		if(avlFlag) tNode = avlFixAddLeft(tNode);
	}
	else if(comp > 0)
	{
		sub = insertItem(tNode->getRight(), item);
		tNode->setRight(sub);
		if(avlFlag) tNode = avlFixAddRight(tNode);
	}
	else
	{
		return tNode;
	}

	return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeItem(AVLTreeNode<T>* tNode, String* searchKey)
{
	if(tNode == NULL) return tNode;
	
	AVLTreeNode<T>* sub;
	T* item = tNode->getItem();
	
	int comp = (*compare_keys)(searchKey, item);
	
	if(comp > 0)
	{
		sub = removeItem(tNode->getRight(), searchKey);
		tNode->setRight(sub);
		if(avlFlag) tNode = avlFixRemoveRight(tNode);
	}
	else if(comp < 0)
	{
		sub = removeItem(tNode->getLeft(), searchKey);
		tNode->setLeft(sub);
		if(avlFlag) tNode = avlFixRemoveLeft(tNode);
	}
	else
	{
		avlFlag = true;
		tNode = removeNode(tNode);
		sze--;
	}
	
	return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeNode(AVLTreeNode<T>* tNode)
{
   T* replacement_item;

   if ((tNode->getLeft() == NULL) && (tNode->getRight() == NULL)) 
   {
      delete tNode;
      return NULL;
   }  
   else if (tNode->getLeft() == NULL) 
   {
      AVLTreeNode<T>* temp = tNode->getRight();
      delete tNode;
      return temp;
   } 
   else if (tNode->getRight() == NULL) 
   {
      AVLTreeNode<T>* temp = tNode->getLeft();
      delete tNode;
      return temp;
   }  
   else 
   {
      replacement_item = findLeftMost(tNode->getRight());
      tNode->setItem(replacement_item);
      tNode->setRight(removeLeftMost(tNode->getRight()));
      if (avlFlag)
      {
         tNode = avlFixRemoveRight(tNode);
      }
      return tNode;
   }  
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeLeftMost(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* subtree;

   if (tNode->getLeft() == NULL) 
   {
      avlFlag = true;
      subtree = tNode->getRight();
      delete tNode;
      return subtree;
   }
   else 
   {
      tNode->setLeft(removeLeftMost(tNode->getLeft()));
      if (avlFlag) tNode = avlFixRemoveLeft(tNode);
      return tNode;
   }  
}

template < class T >
T* AVLTree<T>::findLeftMost(AVLTreeNode<T>* tNode)
{
   while(tNode->getLeft() != NULL)
   {
	   tNode = tNode->getLeft();
   }
   return tNode->getItem();	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* _right = tNode->getRight();
	AVLTreeNode<T>* rl = _right->getLeft();
	
    _right->setLeft(tNode);
	tNode->setRight(rl);
	
	return _right;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* _left = tNode->getLeft();
	AVLTreeNode<T>* lr = _left->getRight();
	
	_left->setRight(tNode);
	tNode->setLeft(lr);
	
	return _left;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* _left = tNode->getLeft();
	AVLTreeNode<T>* temp_node = rotateLeft(_left);
	
	tNode->setLeft(temp_node);
	temp_node = rotateRight(tNode);
	
	return temp_node;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* _right = tNode->getRight();
	AVLTreeNode<T>* temp_node = rotateRight(_right);
	
	tNode->setRight(temp_node);
	temp_node = rotateLeft(tNode);
	
	return temp_node;

}


template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddLeft(AVLTreeNode<T>* tNode)
{
	tNode->insertLeft();
	AVL bal_fact = tNode->getBalanceFactor();

	if(bal_fact == BALANCED) avlFlag = false;
	
	if(bal_fact == LEFT_UNBALANCED)
	{
		AVLTreeNode<T>* _left = tNode->getLeft();
		AVL left_bal_fact = _left->getBalanceFactor();
		
		_left->setBalanceFactor(BALANCED);
		tNode->setBalanceFactor(BALANCED);
		
		if(left_bal_fact == RIGHT_HEAVY) tNode = DLR(tNode, _left);
		else tNode = rotateRight(tNode);
		avlFlag = false;
	}
	return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddRight(AVLTreeNode<T>* tNode)
{
   tNode->insertRight();
   AVL bal_fact = tNode->getBalanceFactor();

   if(bal_fact == BALANCED) avlFlag = false; 
   
   if(bal_fact == RIGHT_UNBALANCED)
   {
	   AVLTreeNode<T>* _right = tNode->getRight();
       AVL right_bal_fact = _right->getBalanceFactor();
	   
       _right->setBalanceFactor(BALANCED);
	   tNode->setBalanceFactor(BALANCED);

       if(right_bal_fact == LEFT_HEAVY) tNode = DRL(tNode, _right);
       else tNode = rotateLeft(tNode);
       
	   avlFlag = false; 
   }

   return tNode;	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixRemoveLeft(AVLTreeNode<T>* tNode)
{
   tNode->removeLeft();
   AVL factor = tNode->getBalanceFactor();

   if (factor == RIGHT_HEAVY)
   {
      avlFlag = false;
   }
   else if (factor == RIGHT_UNBALANCED)
   {
      AVLTreeNode<T>* right = tNode->getRight();
      AVL RBF = right->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      right->setBalanceFactor(BALANCED);

      if (RBF == BALANCED)
      {
         tNode->setBalanceFactor(RIGHT_HEAVY);
         right->setBalanceFactor(LEFT_HEAVY);
         tNode = rotateLeft(tNode);
         avlFlag = false;  
      }
      else if (RBF == RIGHT_HEAVY)
      {
         tNode = rotateLeft(tNode);
      }
      else
      {
         tNode = DRL(tNode, right);
      }
   }

   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixRemoveRight(AVLTreeNode<T>* tNode)
{
   tNode->removeRight();
   AVL factor = tNode->getBalanceFactor();

   if (factor == LEFT_HEAVY)
   {
      avlFlag = false;
   }
   else if (factor == LEFT_UNBALANCED)
   {
      AVLTreeNode<T>* left = tNode->getLeft();
      AVL LBF = left->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      left->setBalanceFactor(BALANCED);

      if (LBF == BALANCED)
      {
         tNode->setBalanceFactor(LEFT_HEAVY);
         left->setBalanceFactor(RIGHT_HEAVY);
         tNode = rotateRight(tNode);
         avlFlag = false; 
      }
      else if (LBF == LEFT_HEAVY)
      {
         tNode = rotateRight(tNode);
      }
      else 
      {
         tNode = DLR(tNode, left);
      }
   }

   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left)
{
	AVLTreeNode<T>* lr = left->getRight();
    AVL bal_fact = lr->getBalanceFactor();
	
    lr->setBalanceFactor(BALANCED);
    
    if(bal_fact == LEFT_HEAVY)
    {
       tNode->setBalanceFactor(RIGHT_HEAVY);    
    }
	else if(bal_fact == RIGHT_HEAVY)
    {
       left->setBalanceFactor(LEFT_HEAVY);
    }

	tNode = DLR(tNode);
	
    return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right)
{
   AVLTreeNode<T>* rl = right->getLeft();
   AVL bal_fact = rl->getBalanceFactor();
   
   rl->setBalanceFactor(BALANCED);

   if (bal_fact == LEFT_HEAVY) right->setBalanceFactor(RIGHT_HEAVY);
  
   else if(bal_fact == RIGHT_HEAVY) tNode->setBalanceFactor(LEFT_HEAVY);

   
   tNode = DRL(tNode);
   
   return tNode;
}

template < class T >
void AVLTree<T>::drawRec(AVLTreeNode<T>* tNode, wxDC& dc, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(dc, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), dc, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), dc, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(dc, x_curr, y_curr);
   }
}

template < class T >
AVLTree<T>::AVLTree(int(*comp_items)(T* item_1, T* item_2), int(*comp_keys)(String* key, T* item))
{
	root = NULL;
	sze == 0;
	compare_items = comp_items;
	compare_keys = comp_keys;
}

template < class T >
AVLTree<T>::~AVLTree()
{
	destroy();
}

template < class T >
int AVLTree<T>::size()
{
	return sze;
}

template < class T >
void AVLTree<T>::insert(T* item)
{
	root = insertItem(root, item);
	avlFlag = false;
}

template < class T >
void AVLTree<T>::remove(String* sk)
{
	root = removeItem(root, sk);
	avlFlag = false;
}

template < class T >
T* AVLTree<T>::retrieve(String* sk)
{
   AVLTreeNode<T>* tNode = getRootNode();

   while(tNode != NULL)
   {
      T* node_items = tNode->getItem();
      int comp = (*compare_keys) (sk, node_items);

      if(comp == 0) return node_items;
      if(comp < 0) tNode = tNode->getLeft();
      if(comp > 0) tNode = tNode->getRight();
   }

   return NULL;
}

template < class T >
bool AVLTree<T>::isEmpty()
{
	return (sze == 0);
}

template < class T >
void AVLTree<T>::makeEmpty()
{
   destroy();
   root == NULL;
   sze = 0;	
}

template < class T >
T* AVLTree<T>::getRootItem()
{
   return root->getItem();
}

template < class T >
AVLTreeIterator<T>* AVLTree<T>::iterator()
{
	return new AVLTreeIterator<T>(root);
}

template < class T >
int AVLTree<T>::getHeight()
{
	return getHeight(root);
}

template < class T >
bool AVLTree<T>::isBalanced()
{
	return isBalanced(root);
}

template < class T >
bool AVLTree<T>::checkBalanceFactors()
{
	return checkBalanceFactors(root);
}

//the below methods have been completed for you

template < class T >
void AVLTree<T>::draw(wxDC&  dc, int width, int height)
{
	Line line(new Color(0, 0, 0), 5.0);
	drawRec(getRootNode(), dc, &line, width, width/2, 20);
}

template < class T >
void AVLTree<T>::mouseClicked(int x, int y) {}

#endif