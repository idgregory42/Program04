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
      AVLTreeNode<T>* root;

      bool avlFlag;
      int sz;

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (String* key, T* item);
	  
		
      void setRootNode(AVLTreeNode<T>* tNode);  //you can get by without using these methods, refer to root directly//
	  
      AVLTreeNode<T>* getRootNode();//
	  
      int getHeight(AVLTreeNode<T>* tNode);  //from lab
	  
	  
      int isBalanced(AVLTreeNode<T>* tNode);//
	  
	  //
      bool checkBalanceFactors(AVLTreeNode<T>* tNode);
	  

      void destroyItem(AVLTreeNode<T>* tNode);//
      void destroy();//

      AVLTreeNode<T>* insertItem(AVLTreeNode<T>* tNode, T* item);//
	  
	  //
      AVLTreeNode<T>* removeItem(AVLTreeNode<T>* tNode, String* searchKey);
	  //
      AVLTreeNode<T>* removeNode(AVLTreeNode<T>* tNode);
	  //
      AVLTreeNode<T>* removeLeftMost(AVLTreeNode<T>* tNode);
	  //
      T* findLeftMost(AVLTreeNode<T>* tNode);
	  
	  //
      AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* tNode);
	  //
      AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* tNode);

      //write and use methods to do each of the four rotations (SR, SL, DLR, DRL)

	  //
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode);

	  //
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode);
	  
	  
      AVLTreeNode<T>* avlFixAddLeft(AVLTreeNode<T>* tNode);//
	  
	  //
      AVLTreeNode<T>* avlFixAddRight(AVLTreeNode<T>* tNode);
	  
	  //
      AVLTreeNode<T>* avlFixRemoveLeft(AVLTreeNode<T>* tNode);
	  
	  //
      AVLTreeNode<T>* avlFixRemoveRight(AVLTreeNode<T>* tNode);
	  
	  //
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left);  //changes balance factors, calls the other DLR to do two rotations
	  
	  //
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right);  //changes balance factors, calls the other DRL to do two rotations

      virtual void drawRec(AVLTreeNode<T>* tNode, wxDC&  dc, Line* line, int x_parent, int x_curr, int y_curr);

   public:
      
	  
	  AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));//
      ~AVLTree();
	
	  //
      int size(); //line 100
	  
	  
      void insert(T* item);//
	  
	  //
      void remove(String* sk);
	  
      T* retrieve(String* sk);//

      bool isEmpty();//
	  
	  //
      void makeEmpty();
	  
      T* getRootItem();
	  
      AVLTreeIterator<T>* iterator();

	  
      int getHeight();
	  
      bool isBalanced();
	  
	  //
      bool checkBalanceFactors();
		
	  /////////////////////////////////////////
      void draw(wxDC&  dc, int width, int height);
      void mouseClicked(int x, int y);

};

template < class T >
void AVLTree<T>::setRootNode(AVLTreeNode)
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
   if (tNode == NULL)
   {
       return 0;
   }
   else
   {
       int left = getHeight(tNode->getLeft());
       int right = getHeight(tNode->getRight());

       if (left >= right)
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
bool AVLTree<T>::isBalanced(AVLTreeNode<T>* tNode)
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
	
}

template < class T >
void AVLTree<T>::destroyItem(AVLTreeNode<T>* tNode)
{
   if (tNode != NULL)
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
	AVLTreeNode<T>* sub;
	if(tNode == NULL)
	{
		avlFlag = true;
		sze++;
		return new AVLTreeNode<T>(item);
	}
	
	T* node_items = tNode->getItem();
	int comp = (*compare_items)(item, node_items);
	
	if(comp < 0)
	{
		sub = insertItem(tNode->getLeft(), item);
		tNode->setLeft(sub);
		if(avlFlag) tNode->insertLeft();
	}
	else if(comp > 0)
	{
		sub = insertItem(tNode->getRight(), item);
		tNode->setRight(sub);
		if(avlFlag) tNode->insertRight();
	}
	else
	{
		return tNode;
	}
	
	if(tNode->getBalanceFactor() == LEFT_UNBALANCED)
	{
		tNode = avlFixAddLeft(tNode);
		avlFlag = false;
	}
	else if(tNode->getBalanceFactor() == RIGHT_UNBALANCED)
	{
		tNode = avlFixAddRight(tNode);
		avlFlag = false;
	}
	else if(tNode->getBalanceFactor() == BALANCED)
	{
		avlFlag = false;
	}
	
	return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeItem(AVLTreeNode<T>* tNode, String* searchKey)
{
	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeNode(AVLTreeNode<T>* tNode)
{
	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeLeftMost(AVLTreeNode<T>* tNode)
{
	
}

template < class T >
T* AVLTree<T>::findLeftMost(AVLTreeNode<T>* tNode)
{
	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* tNode)
{
	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* tNode)
{
	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode)
{
	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode)
{
	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddLeft(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* left = tNode->getLeft();
	AVLTreeNode<T>* sub;
	if(left->getBalanceFactor() == LEFT_HEAVY)
	{
		sub = rotateRight(tNode);
	}
	else
	{
		AVLTreeNode<T>* lf = left->getRight();
		tNode->setLeft(rotateLeft(left));
		sub = rotateRight(tNode);
		
		if(lf->getBalanceFactor() == LEFT_HEAVY)
		{
			tNode->setBalanceFactor(RIGHT_HEAVY);
			left->setBalanceFactor(BALANCED);
			lf->setBalanceFactor(BALANCED);
		}
		else if (lf->getBalanceFactor() == RIGHT_HEAVY)
		{
			tNode->setBalanceFactor(BALANCED);
			left->setBalanceFactor(LEFT_HEAVY);
			lf->setBalanceFactor(BALANCED);
		}
		else
		{
			tNode->setBalanceFactor(BALANCED);
			left->setBalanceFactor(BALANCED);
			lf->setBalanceFactor(BALANCED);
		}
	}
	return sub;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddRight(AVLTreeNode<T>* tNode)
{
	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixRemoveLeft(AVLTreeNode<T>* tNode)
{
	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixRemoveRight(AVLTreeNode<T>* tNode)
{
	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left)
{
	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right)
{
	
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

//public
template < class T >
AVLTree<T>::AVLTree(int(*comp_items)(T* item_1, T* item_2), int(*comp_keys)(String* key, T* item))
{
	sze == 0;
	avlFlag = false;
	root = NULL;
	
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
}

template < class T >
T* AVLTree<T>::retrieve(String* sk)
{
   AVLTreeNode<T>* tNode = getRootNode();

   while (tNode != NULL)
   {
      T* node_items = tNode->getItem();
      int comp = (*compare_keys) (sk, node_items);

      if (comp == 0)
      {
		return node_items;
      }
      else if (comp < 0)
      {
        tNode = tNode->getLeft();
      }
      else
      {
        tNode = tNode->getRight();
      }
   }

   return NULL;
}

template < class T >
bool AVLTree<T>::isEmpty()
{
	return sze == 0;
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
   T* rootItem = root->getItem();
   return rootItem;
}

template < class T >
AVLTreeIterator<T>* AVLTree<T>::iterator()
{
	AVLTreeIterator<T>* iter = new AVLTreeIterator<T>(root);
	return iter;
}

template < class T >
int AVLTree<T>::getHeight()
{
	return getHeight(getRootNode());
}

template < class T >
bool AVLTree<T>:: isBalanced()
{
	bool bal = isBalanced(root);
	return bal;
}

template < class T >
bool checkBalanceFactors()
{
	
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
