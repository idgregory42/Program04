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
      int sze;

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (String* key, T* item);
	  
	  /*
		Pre :
		Post:
	  */	  
      void setRootNode(AVLTreeNode<T>* tNode); //123	  //you can get by without using these methods, refer to root directly//
	  
	  /*
		Pre :
		Post:
	  */	  
      AVLTreeNode<T>* getRootNode(); //130
	  
	  /*
		Pre :
		Post:
	  */	  
      int getHeight(AVLTreeNode<T>* tNode);  //136
	  
	  /*
		Pre :
		Post:
	  */	  
      int isBalanced(AVLTreeNode<T>* tNode); //159
	  
	  /*
		Pre :
		Post:
	  */	  
      bool checkBalanceFactors(AVLTreeNode<T>* tNode); //180
	  
	  /*
		Pre :
		Post:
	  */	  
      void destroyItem(AVLTreeNode<T>* tNode); //186

	  /*
		Pre :
		Post:
	  */	  
      void destroy(); //197

	  /*
		Pre :
		Post:
	  */	  
      AVLTreeNode<T>* insertItem(AVLTreeNode<T>* tNode, T* item); //204

	  /*
		Pre :
		Post:
	  */	  
      AVLTreeNode<T>* removeItem(AVLTreeNode<T>* tNode, String* searchKey); //252

	  /*
		Pre :
		Post:
	  */	  
      AVLTreeNode<T>* removeNode(AVLTreeNode<T>* tNode); //258

	  /*
		Pre :
		Post:
	  */	  
      AVLTreeNode<T>* removeLeftMost(AVLTreeNode<T>* tNode); //264

	  /*
		Pre :
		Post:
	  */	  
      T* findLeftMost(AVLTreeNode<T>* tNode); //270
	  
	  /*
		Pre :
		Post:
	  */	  	  
      AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* tNode); //276
	  
	  /*
		Pre :
		Post:
	  */	  	  
      AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* tNode); //282

      //write and use methods to do each of the four rotations (SR, SL, DLR, DRL)

	  
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode); //288

	  
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode); //294
	  
	  AVLTreeNode<T>* SL(AVLTreeNode<T>* tNode);
	  
	  AVLTreeNode<T>* SR(AVLTreeNode<T>* tNode);
	  
	  /*
		Pre :
		Post:
	  */	  
      AVLTreeNode<T>* avlFixAddLeft(AVLTreeNode<T>* tNode); //300
	  
	  //
      AVLTreeNode<T>* avlFixAddRight(AVLTreeNode<T>* tNode); //337
	  
	  //
      AVLTreeNode<T>* avlFixRemoveLeft(AVLTreeNode<T>* tNode); //343
	  
	  //
      AVLTreeNode<T>* avlFixRemoveRight(AVLTreeNode<T>* tNode); //349
	  
	  //
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left); //355 //changes balance factors, calls the other DLR to do two rotations
	  
	  //
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right); //361  //changes balance factors, calls the other DRL to do two rotations

      virtual void drawRec(AVLTreeNode<T>* tNode, wxDC&  dc, Line* line, int x_parent, int x_curr, int y_curr);

   public:
	
	  AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));//
      ~AVLTree();
	  
	  /*
		Pre :
		Post:
	  */
	  int size(); 
	  
	  /*
		Pre :
		Post:
	  */	  
	  void insert(T* item);

	  /*
		Pre :
		Post:
	  */	  
	  void remove(String* sk);

	  /*
		Pre :
		Post:
	  */	  
      T* retrieve(String* sk);

	  /*
		Pre :
		Post:
	  */	  
      bool isEmpty();

	  /*
		Pre :
		Post:
	  */	  
      void makeEmpty();
	  
	  /*
		Pre :
		Post:
	  */	  
      T* getRootItem();
	  
	  /*
		Pre :
		Post:
	  */	  
      AVLTreeIterator<T>* iterator();

	  /*
		Pre :
		Post:
	  */	  
      int getHeight();
	  
	  /*
		Pre :
		Post:
	  */	  
      bool isBalanced();
	  
	  /*
		Pre :
		Post:
	  */	  
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
	return isBalanced(tNode);
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
	if(tNode == NULL) return tNode;
	
	AVLTreeNode<T>* sub;
	T* item = tNode->getItem();
	
	int comp = (*compare_keys)(sk, item);
	
	if (comp > 0)
	{
		sub = removeItem(tNode->getRight(), sk);
		tNode->setRight(sub);
		if(avlFlag) tNode = avlFixRemoveRight(tNode);
	}
	else if (comp < 0)
	{
		sub = removeItem(tNode->getLeft(), sk);
		tNode->setLeft(sub);
		if(AVLFlag) tNode = avlFixRemoveLeft(tNode);
	}
	else
	{
		AVLFlag = true;
		tNode = removeNode(tNode);
		sze--;
	}
	
	return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeNode(AVLTreeNode<T>* tNode)
{
   if (tNode->getLeft() == NULL && tNode->getRight() == NULL)
   {
	   delete tNode;
       return NULL;
   }
   else if (tNode->getLeft() == NULL)
   {
	   AVLTreeNode<T>* temp_node = tNode->getRight();
	   delete tNode;
	   return temp_node;
   }
   else if (tNode->getRight() == NULL)
   {
	   
       AVLTreeNode<T>* temp_node = tNode->getLeft();
       delete tNode;
       return temp_node;
   }
   else 
   {
	   AVLTreeNode<T>* temp_node = tNode->getRight();
	   T* temps = findLeftMost(temp_node);
	   tNode->setItem(temps);
	   AVLTreeNode<T>* sub = removeLeftMost(tNode->getRight());
	   tNode->setRight(sub);
	   if(AVLFlag) tNode = avlFixRemoveRight(tNode);
	   return tNode;
   }	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeLeftMost(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* sub;
	if(tNode->getLeft() == NULL)
	{
		avlFlag = true;
		sub = tNode->getRight();
		delete tNode;
		return sub;
	}
	else
	{
		sub = removeLeftMost(tNode->getLeft());
		tNode->setLeft(sub);
		if(avlFlag) tNode = avlFixRemoveLeft(tNode);
		return tNode;
	}

}

template < class T >
T* AVLTree<T>::findLeftMost(AVLTreeNode<T>* tNode)
{
   while(tNode->getLeft())
   {
	   tNode = tNode->getLeft();
   }
   T* item = tNode->getItem();
   return item;	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* rl = right->getLeft();
	AVLTreeNode<T>* r = tNode->getRight();
	
	r->setLeft(tNode);
	tNode->setRight(rl);

	return r;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* lr = left->getRight();
	AVLTreeNode<T>* l = tNode->getLeft();
	
	l->setRight(tNode);
	tNode->setLeft(lr);
	
	return l;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode)
{

	AVLTreeNode<T>* l = tNode->getLeft();
	AVLTreeNode<T>* temp_node = rotateLeft(l);
	tNode->setLeft(temp_node);
	temp_node = rotateRight(tNode);
	return temp_node;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* r = tNode->getRight();
	AVLTreeNode<T>* temp_node = rotateRight(r);
	tNode->setRight(temp_node);
	temp_node = rotateLeft(tNode);
	return temp_node;

}


template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddLeft(AVLTreeNode<T>* tNode)
{
	tNode->insertLeft();
	AVL bal_fact = tNode->getBalanceFactor();

	if(bal_fact == BALANCED)
	{
		avlFlag == false;
	}
	else if(bal_fact == LEFT_UNBALANCED)
	{
		AVLTreeNode<T>* l = tNode->getLeft();
		AVL left_bal_fact = l->getBalanceFactor();
		
		tNode->setBalanceFactor(BALANCED);
		l->setBalanceFactor(BALANCED);

		
		if(left_bal_fact == RIGHT_HEAVY)
		{
			tNode = DLR(tNode, l);
		}
		else
		{
			tNode = rotateRight(tNode);
		}
		avlFlag = false;
	}
	return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddRight(AVLTreeNode<T>* tNode)
{
   tNode->insertRight();
   AVL bal_fact = tNode->getBalanceFactor();

   if (bal_fact == BALANCED) 
   {
	   avlFlag = false; 
   }
   else if (bal_fact == RIGHT_UNBALANCED)
   {
      AVLTreeNode<T>* r = tNode->getRight();
      AVL right_bal_fact = r->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      r->setBalanceFactor(BALANCED);

      if (right_bal_fact == LEFT_HEAVY)
      {
        tNode = DRL(tNode, r);
      }
      else 
      {
        tNode = rotateLeft(tNode);
      }

      avlFlag = false; 
   }

   return tNode;	
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixRemoveLeft(AVLTreeNode<T>* tNode)
{
   tNode->deleteLeft();
   AVL bal_fact = tNode->getBalanceFactor();

   if (bal_fact == RIGHT_HEAVY)  
   {
      avlFlag = false;
   }
   else if (bal_fact == RIGHT_UNBALANCED)
   {
      AVLTreeNode<T>* r = tNode->getRight();
      AVL right_bal_fact = r->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      r->setBalanceFactor(BALANCED);

       if (right_bal_fact == BALANCED) 
       {
			tNode->setBalanceFactor(RIGHT_HEAVY);
			r->setBalanceFactor(LEFT_HEAVY);
			tNode = rotateLeft(tNode);
			avlFlag = false;  
       }
      else if (right_bal_fact == RIGHT_HEAVY)
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
   tNode->deleteRight();
   AVL bal_fact = tNode->getBalanceFactor();

   if (bal_fact == LEFT_HEAVY)
   {
      avlFlag = false;
   }
   else if (bal_fact == LEFT_UNBALANCED)
   {
      AVLTreeNode<T>* l = tNode->getLeft();
      AVL left_bal_fact = l->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      l->setBalanceFactor(BALANCED);

      if (left_bal_fact == BALANCED)
      {
			tNode->setBalanceFactor(LEFT_HEAVY);
			l->setBalanceFactor(RIGHT_HEAVY);
			tNode = rotateRight(tNode);
			avlFlag = false;  
      }
      else if (left_bal_fact == LEFT_HEAVY)
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

	if (bal_fact == LEFT_HEAVY)
	{
		tNode->setBalanceFactor(RIGHT_HEAVY);
	}
	else if (bal_fact == RIGHT_HEAVY)
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
	
	if(bal_fact == RIGHT_HEAVY)
	{
		tNode->setBalanceFactor(LEFT_HEAVY);
	}
	else if(bal_fact == LEFT_HEAVY)
	{
		right->setBalanceFactor(RIGHT_HEAVY);
	}
	
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

/////////////////public
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
	return new AVLTreeIterator<T>(root);
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
