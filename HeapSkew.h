#if !defined HEAPSKEW_H
#define HEAPSKEW_H

#include "BinaryTree.h"
#include "wx/wx.h"

template < class T >
class HeapSkew : public Drawable
{

   private:
      BinaryTree<T>* bt;
      int sze;
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      ~HeapSkew();

      bool heapIsEmpty();
      void heapInsert(T* item);
      T* heapRemove();

      void draw(wxDC& dc, int width, int height);
      void mouseClicked(int x, int y);

};

// this is a MAXHEAP (largest items to top alphabetical order)
template < class T >
HeapSkew<T>::HeapSkew(int (*comp_items) (T* item_1, T* item_2)) : Drawable()
{ 
   bt = new BinaryTree<T>();
   sze = 0;

   compare_items = comp_items;
}

template < class T >
HeapSkew<T>::~HeapSkew() 
{ 
   delete bt;
}  

template < class T >
bool HeapSkew<T>::heapIsEmpty()
{
   return sze == 0;
}

template < class T >
BinaryTree<T>* HeapSkew<T>::merge(BinaryTree<T>* left, BinaryTree<T>* right)
{
  //DO THIS
  BinaryTree<T>* newTree;
  //int comp;
  
	if(left->isEmpty())
	{
		delete left;
		return right;
	}
	else if(right->isEmpty())
	{
		delete right;
		return left;
	}

	T* leftRootItem = left->getRootItem();
	T* rightRootItem = right->getRootItem();
	
	int comp = (*compare_items) (leftRootItem, rightRootItem);
	
	if (comp < 0)
	{
		newTree = merge(right, left);
	}
	else{
		newTree = left;
	BinaryTree<T>* LL = newTree->detachLeftSubtree();
	BinaryTree<T>* LR = newTree->detachRightSubtree();
	left->attachRightSubtree(LL);
	delete LL;
	
	if(LR->isEmpty())
	{
		newTree->attachLeftSubtree(right);
		delete LR;
		delete right;
	}
	else{
		BinaryTree<T>* temp = merge(LR,right);
		newTree->attachLeftSubtree(temp);
		delete temp;
		
	}
	}
	return newTree;
}



template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)
BinaryTree<T>* newTree = new BinaryTree<T>(item);

newTree = merge(bt, newTree);

bt = newTree;
sze++;



}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)

   T* item = bt->getRootItem();
   
   BinaryTree<T>* newTree;

   BinaryTree<T>* left = bt->detachLeftSubtree();
   BinaryTree<T>* right = bt->detachLeftSubtree();
   
   newTree = merge(left, right);
   
   bt = newTree;
   
   

return item;



}

template < class T >
void HeapSkew<T>::draw(wxDC& dc, int width, int height)
{
   bt->draw(dc, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif
