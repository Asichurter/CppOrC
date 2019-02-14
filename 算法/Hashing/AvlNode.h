#include<iostream>

template <typename K, typename T> class AvlNode {
public:	
	K Key;
	T Element;
	AvlNode<K,T>* Father;
	AvlNode<K,T>* Left;
	AvlNode<K,T>* Right;
	
	AvlNode(K& key, T& ele, AvlNode<K, T>* f, AvlNode* l=NULL, AvlNode* r=NULL){
		Key = key;
		Element = ele;
		Father = f;
		Right = r;
		Left = l;
	}
		
	bool ifLeaf(){
		return Left==NULL && Right==NULL;
	}

	int hight() {
		int left = (Left == NULL ? 0 : Left->hight());
		int right = (Right == NULL ? 0 : Right->hight());
		return (left > right ? left : right) + 1;
	}

	//判断该节点是否非平衡
	bool isUnbalanced() {
		int left = (Left == NULL ? 0 : Left->hight());
		int right = (Right == NULL ? 0 : Right->hight());
		if (left - right >= 2 || left - right <= -2)
			return true;
		else return false;
	}

	//中序遍历本节点
	void traverse() {
		std::cout << Key << std::endl;
		if (Left != NULL) Left->traverse();
		if (Right != NULL) Right->traverse();
	}
};                                     
