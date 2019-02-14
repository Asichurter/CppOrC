#include "BstNode.h"
#include "ArrayQueue.h"
#include <iostream>
#include <string>

template <typename T> class BST{
	private:
		BstNode<T>* Root;
		int Size;
		
		void clearHelper(BstNode<T>* root){
			if (root == NULL) return;
			clearHelper(root->getLeft());
			clearHelper(root->getRight());
			delete root;
		}
		
		BstNode<T>* insertHelper(BstNode<T>* root, BstNode<T>* node){
			if (root == NULL)
				return node;
			if (node->getElement() >= root->getElement()){
				root->setRight(insertHelper(root->getRight(), node));	
			}
			else {
				root->setLeft(insertHelper(root->getLeft(), node));
			}
			return root;
		}
				
		void preorderTraverse(BstNode<T>* root){
			if (root == NULL) return;
			std::cout << root->getElement() << std::endl;
			preorderTraverse(root->getLeft());
			preorderTraverse(root->getRight());
		}
		
		BstNode<T>* getMin(BstNode<T>* root){
			if (root == NULL) return NULL;
			if (root->getLeft() != NULL)
				return getMin(root->getLeft());
			else return root;
		}
		
		BstNode<T>* deleteMin(BstNode<T>* root){
			if (root == NULL)
				return NULL;
			//如果没有左树，则将右树作为父节点的左节点返回 
			if (root->getLeft() == NULL){
				//如果某个节点有右节点但是没有左节点，代表该节点就是最小节点
				//那么就把该节点的右节点作为父节点的左节点 
				// 
				BstNode<T>* temp = root->getRight();
				delete root;
				return temp;
			}
			else{
				//有左树：删除左树的节点 
				root->setLeft(deleteMin(root->getLeft()));
				return root;
			} 
		}
		
		BstNode<T>* removeHelper(BstNode<T>* root, T& ele){
			if (root== NULL){
				std::cout << "没有查找到待删除的元素！" << std::endl;
				return root;
			}
			//如果待查找节点大于本节点值：在右树中继续搜索之 
			if (ele > root->getElement()){
				root->setRight(removeHelper(root->getRight(), ele));
				return root;
			}
			//如果待查找节点小于本节点值：在左树中继续搜索之 
			else if (ele < root->getElement()){
				root->setLeft(removeHelper(root->getLeft(), ele));
				return root;
			}
			//找到了元素 
			else {
				//删除该元素
				//如果待删除节点还有右树，则删除右树的最小值，用最小值代替该节点
				//返回值是删除最小值后的右树根节点 
				if (root->getRight() != NULL){
					root->setElement(getMin(root->getRight())->getElement());
					return deleteMin(root->getRight());
				}
				//如果没有右树 
				else{
					//如果连左树也没有，那么直接删除该节点，然后返回null 
					if (root->getLeft() == NULL){
						delete root;
						return NULL; 
					}
					//否则就将左树的子树作为本节点的子树，同时删除左节点
					//返回本节点，即新的左节点
					//这相当于将删除节点的左节点接在了删除节点的父节点的左树上 
					else {
						BstNode<T>* temp = root->getLeft();
						root->setRight(root->getLeft()->getRight());
						root->setElement(root->getLeft()->getElement());
						root->setLeft(root->getLeft()->getLeft());
						delete temp;
						return root;
					}
				}
			}
		}	
			
		BstNode<T>* findHelper(BstNode<T>* root, T& ele){
			if (root == NULL)
				return NULL;
			if (ele > root->getElement())
				return findHelper(root->getRight(), ele);
			else if (ele < root->getElement())
				return findHelper(root->getLeft(), ele);
			else return root;
		}
		
	public:
		BST(BstNode<T>* root=NULL){
			Root = root;
			Size = 0;	
		}
		
		~BST(){
			clearHelper(Root);
		}
		
		void clear(){
			clearHelper(Root);
			Size = 0;
			Root = NULL;
		}
		
		void insert(BstNode<T>* newNode){
			Root = insertHelper(Root, newNode);
			Size++; 
		}
		
		//按次序插入多个元素 
		void insertMany(T eles[] , int num){
			for (int i = 0; i < num; i++){
				insert(new BstNode<int>(eles[i]));
			}
		}
		
		void preorderTraverse(){
			BST::preorderTraverse(Root);
		}
		
		BstNode<T>* getMin(){
			return getMin(Root);
		}
		
		void remove(T& ele){
			if (Size == 0){
				std::cout << "BST中没有元素！" << std::endl; 
				return;
			}
			Root = removeHelper(Root, ele);
			Size--;
		}
		
		void deleteMin(){
			Root = deleteMin(Root);
		}
		
		int length(){
			return Size;
		}
		
		int getLeafNum(BstNode<T>* root){
			if (root == NULL)
				return 0;
			return (root->ifLeaf() ? 1 : 0)+ getLeafNum(root->getLeft()) + getLeafNum(root->getRight());
		}
		
		int getLeafNum(){
			return getLeafNum(Root);
		}

		int widthTraverse() {
			ArrayQueue<BstNode<T>*> queue1;
			ArrayQueue<BstNode<T>*> queue2;
			bool isFirst = true;
			queue1.enqueue(Root);
			int max = 0;
			int counter;
			while (true){
				queue2.clear();
				counter = 0;
				while (queue1.length() > 0) {
					std::cout << queue1.frontValue()->getElement() << " ";
					if (queue1.frontValue()->getLeft() != NULL)
						queue2.enqueue(queue1.frontValue()->getLeft());
					if (queue1.frontValue()->getRight() != NULL)
						queue2.enqueue(queue1.frontValue()->getRight());
					queue1.dequeue();
					counter++;
				}
				if (counter > max)
					max = counter;
				else if (counter == 0)
					break;

				queue1.clear();
				counter = 0;
				while (queue2.length() > 0) {
					std::cout << queue2.frontValue()->getElement() << " ";
					if (queue2.frontValue()->getLeft() != NULL)
						queue1.enqueue(queue2.frontValue()->getLeft());
					if (queue2.frontValue()->getRight() != NULL)
						queue1.enqueue(queue2.frontValue()->getRight());
					queue2.dequeue();
					counter++;
				}
				if (counter > max)
					max = counter;
				else if (counter == 0)
					break;
			}
			return max;
		}
		
		int widthHelper(BstNode<T>* root, int distance) {
			if (root == NULL) {
				return 0;
			}
			if (distance == 0) {
				return 1;
			}
			return widthHelper(root->getLeft(), distance-1) + widthHelper(root->getRight(), distance-1);
		}

		bool isBST(BstNode<T>* root, bool isRoot) {
			if (isRoot)
				root = Root;
			if (root == NULL)
				return true;
			return (root->getLeft() == NULL ? true : root->getElement() > root->getLeft()->getElement()) &&
				(root->getRight() == NULL ? true : root->getElement() <= root->getRight()->getElement()) &&
				isBST(root->getLeft(), false) &&
				isBST(root->getRight(), false);
		}
		/* 
		class Char{
			public:
				char letter;
				int depth;
				Char(char l, int d){
					letter = l;
					depth = d;
				}
		};
		
		void inorderTraverse(LinkedQueue<Char>& letters, BstNode<char>* root, int& maxDepth, int curDepth){
			if (root == NULL)
				return;
			if (curDepth > maxDepth)
				maxDepth = curDepth;
			inorderTraverse(root->getRight(), all, maxDepth, curDepth+1);
			letters.enqueue(new Char(root->getElement(), curDepth));
			inorderTraverse(root->getLeft(), all, maxDepth, curDepth+1);
		}
		
		void printBst(){
			int depth = 0;
			LinkerQueue<Char> allLetters = new LinkedQueue<Char>();
			inorderTraverse(allLetters, Root, depth, 0);
			while (inorderTraverse.length() > 0){
				Char temp = allLetters.dequeue();
				for (int i = 0; i <= depth; i++){
					if (i == temp.depth)
						std::cout << temp.letter;
					else std::cout << " ";
				}
				std::cout << std::endl;
			}
		}
	
		void switchLAndR(BST<T>& bst){
			if (bst->Root == NULL)
				return;
			switchLAndR(new BST<T>(bst->Root->getLeft()));
			switchLAndR(new BST<T>(bst->Root->getRight()));
			BstNode<T>* temp = bst->Root->getLeft();
			bst->Root->setLeft(bst->Root->getRight());
			bst->Root->setRight(temp);
		}
		*/
};
