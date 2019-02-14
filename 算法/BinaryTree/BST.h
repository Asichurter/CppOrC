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
			//���û����������������Ϊ���ڵ����ڵ㷵�� 
			if (root->getLeft() == NULL){
				//���ĳ���ڵ����ҽڵ㵫��û����ڵ㣬����ýڵ������С�ڵ�
				//��ô�ͰѸýڵ���ҽڵ���Ϊ���ڵ����ڵ� 
				// 
				BstNode<T>* temp = root->getRight();
				delete root;
				return temp;
			}
			else{
				//��������ɾ�������Ľڵ� 
				root->setLeft(deleteMin(root->getLeft()));
				return root;
			} 
		}
		
		BstNode<T>* removeHelper(BstNode<T>* root, T& ele){
			if (root== NULL){
				std::cout << "û�в��ҵ���ɾ����Ԫ�أ�" << std::endl;
				return root;
			}
			//��������ҽڵ���ڱ��ڵ�ֵ���������м�������֮ 
			if (ele > root->getElement()){
				root->setRight(removeHelper(root->getRight(), ele));
				return root;
			}
			//��������ҽڵ�С�ڱ��ڵ�ֵ���������м�������֮ 
			else if (ele < root->getElement()){
				root->setLeft(removeHelper(root->getLeft(), ele));
				return root;
			}
			//�ҵ���Ԫ�� 
			else {
				//ɾ����Ԫ��
				//�����ɾ���ڵ㻹����������ɾ����������Сֵ������Сֵ����ýڵ�
				//����ֵ��ɾ����Сֵ����������ڵ� 
				if (root->getRight() != NULL){
					root->setElement(getMin(root->getRight())->getElement());
					return deleteMin(root->getRight());
				}
				//���û������ 
				else{
					//���������Ҳû�У���ôֱ��ɾ���ýڵ㣬Ȼ�󷵻�null 
					if (root->getLeft() == NULL){
						delete root;
						return NULL; 
					}
					//����ͽ�������������Ϊ���ڵ��������ͬʱɾ����ڵ�
					//���ر��ڵ㣬���µ���ڵ�
					//���൱�ڽ�ɾ���ڵ����ڵ������ɾ���ڵ�ĸ��ڵ�������� 
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
		
		//�����������Ԫ�� 
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
				std::cout << "BST��û��Ԫ�أ�" << std::endl; 
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
