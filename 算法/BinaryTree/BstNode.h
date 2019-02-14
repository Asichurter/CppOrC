#include<iostream>

template <typename T> class BstNode {
	private:
		T element;
		BstNode* left;
		BstNode* right;
	public:
		BstNode(T ele, BstNode* l=NULL, BstNode* r=NULL){
			element = ele;
			right = r;
			left = l;
		}
		
		void setLeft(BstNode* l){
			left = l;
		}
		
		void setRight(BstNode* r){
			right = r;
		}
		
		void setElement(T ele){
			element = ele;
		}
		
		BstNode* getLeft(){
			return left;
		}
		
		BstNode* getRight(){
			return right;
		}
		
		T getElement(){
			return element;
		}
		
		bool ifLeaf(){
			return left==NULL && right==NULL;
		}
		
		void traverseInorder(BstNode* root){
			if (root == NULL)
				return;
			traverseInorder(root->left);
			std::cout << root->element << std::endl;
			traverseInorder(root->right);
		}
};                                     
