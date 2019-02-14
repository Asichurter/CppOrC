#pragma once
#include "AvlNode.h"
#include "ArrayStack.h"
#include "ArrayQueue.h"

/********************************
	AVL二叉平衡树
	2018.12.2
*********************************/

template <typename K, typename T, typename COMP> class AVL {
private:
	//检查旋转的类型
	//1：右右
	//2：右左
	//3：左左
	//4: 左右
	//-1: 错误
	int checkRotateType(AvlNode<K, T>* node_1, AvlNode<K, T>* node_2, AvlNode<K, T>* node_3) {
		if (node_1->Right == node_2) {
			if (node_2->Right == node_3)
				return 1;
			else if (node_2->Left == node_3)
				return 2;
		}
		else if (node_1->Left == node_2) {
			if (node_2->Left == node_3)
				return 3;
			else if (node_2->Right == node_3)
				return 4;
		}
		return -1;
	}

	//右右型，需要左旋
	bool rotate_rr(AvlNode<K, T>* node_1, AvlNode<K, T>* node_2) {
		bool root_switch = false;
		//将1号节点移动到2号节点的左节点上
		node_1->Right = node_2->Left;
		if (node_2->Left != NULL) node_2->Left->Father = node_1;
		node_2->Left = node_1;
		//判断node_1是其父节点的左还是右节点
		//true: 右 
		//false:左
		if (node_1->Father != NULL) {
			bool node_1_vs_father = COMP::compare(node_1->Key, node_1->Father->Key);
			(node_1_vs_father ? node_1->Father->Right : node_1->Father->Left) = node_2;
		}//调整父节点关系
		//如果1号节点没有父节点，代表根节点需要改换
		else root_switch = true;
		node_2->Father = node_1->Father;
		node_1->Father = node_2;
		return root_switch;
	}

	//右左型，需要右左旋转
	bool rotate_rl(AvlNode<K, T>* node_1, AvlNode<K, T>* node_2, AvlNode<K, T>* node_3) {
		bool root_switch = false;
		//将2号节点移动到3号节点的右节点上去
		node_2->Left = node_3->Right; 
		//检查3号节点的左右节点是否为空，如果是的话就不用改变其父节点的属性
		if (node_3->Right != NULL) node_3->Right->Father = node_2;
		node_3->Right = node_2;
		node_2->Father = node_3;
		//将3号节点的父节点设置为1号节点的父节点，继承父节点
		if (node_1->Father != NULL){
			bool node_1_vs_father = COMP::compare(node_1->Key, node_1->Father->Key);
			(node_1_vs_father ? node_1->Father->Right : node_1->Father->Left) = node_3;
		}//将1号节点设置为3号节点的左节点
		//如果1号节点没有父节点，代表根节点需要改换
		else root_switch = true;
		node_3->Father = node_1->Father;
		node_1->Right = node_3->Left;
		if (node_3->Left != NULL) node_3->Left->Father = node_1;
		node_3->Left = node_1;
		node_1->Father = node_3;
		return root_switch;
	}

	//左左型，需要右旋
	bool rotate_ll(AvlNode<K, T>* node_1, AvlNode<K, T>* node_2) {
		bool root_switch = false;
		node_1->Left = node_2->Right;
		if (node_2->Right != NULL) node_2->Right->Father = node_1;
		node_2->Right = node_1;
		if (node_1->Father != NULL){
			bool node_1_vs_father = COMP::compare(node_1->Key, node_1->Father->Key);
			(node_1_vs_father ? node_1->Father->Right : node_1->Father->Left) = node_2;
		}
		//如果1号节点没有父节点，代表根节点需要改换
		else root_switch = true;
		node_2->Father = node_1->Father;
		node_1->Father = node_2;
		return root_switch;
	}

	//左右型，需要左右旋转
	bool rotate_lr(AvlNode<K, T>* node_1, AvlNode<K, T>* node_2, AvlNode<K, T>* node_3) {
		bool root_switch = false;
		//将2号节点移动到3号节点的右节点上去
		node_2->Right = node_3->Left;
		//检查3号节点的左右节点是否为空，如果是的话就不用改变其父节点的属性
		if (node_3->Left != NULL) node_3->Left->Father = node_2;
		node_3->Left = node_2;
		node_2->Father = node_3;
		//将3号节点的父节点设置为1号节点的父节点，继承父节点
		if (node_1->Father != NULL){
			bool node_1_vs_father = COMP::compare(node_1->Key, node_1->Father->Key);
			(node_1_vs_father ? node_1->Father->Right : node_1->Father->Left) = node_3;
		}//将1号节点设置为3号节点的左节点
		//如果1号节点没有父节点，代表根节点需要改换
		else root_switch = true;
		node_3->Father = node_1->Father;
		node_1->Left = node_3->Right;
		if (node_3->Right != NULL) node_3->Right->Father = node_1;
		node_3->Right = node_1;
		node_1->Father = node_3;
		return root_switch;
	}

	//返回值：
	//1：2为中心，将1,2压栈 2:需改变根节点
	//-1: 3为中心，将1,3压栈 -2：需改变根节点
	//0：发生错误
	int rotate(AvlNode<K, T>* node_1, AvlNode<K, T>* node_2, AvlNode<K, T>* node_3) {
		switch (checkRotateType(node_1, node_2, node_3)) {
		case 1:
			if (rotate_rr(node_1, node_2))
				return 2;
			else return 1;
		case 2:
			if (rotate_rl(node_1, node_2, node_3))
				return -2;
			else return -1;
		case 3:
			if (rotate_ll(node_1, node_2))
				return 2;
			else return 1;
		case 4:
			if (rotate_lr(node_1, node_2, node_3))
				return -2;
			else return -1;
		default:
			return 0;
		}
	}

	//递归调用的AVL树平衡检查方法
	bool checkBalancedHelper(AvlNode<K, T>* root) {
		if (root == NULL) return true;
		if (root->isUnbalanced()) return false;
		else return checkBalancedHelper(root->Left) && checkBalancedHelper(root->Right);
	}

public:
	AvlNode<K,T>* Root;
	
	AVL() {Root = NULL;}

	//向AVL中插入一条记录
	bool insert(K& key, T& ele) {
		if (Root == NULL) {
			Root = new AvlNode<K, T>(key, ele, NULL);
			return true;
		}
		else {
			AvlNode<K, T>* cur = Root;
			//记录路径上经过的节点
			ArrayStack<AvlNode<K, T>*> path;
			path.push(Root);
			//二叉树的前进方向：true向右
			//比较的是键值才对
			bool dir = COMP::compare(key, cur->Key);
			//1.将cur移动至待插入的位置
			while ((dir && cur->Right != NULL) || (!dir && cur->Left != NULL)) {
				path.push(dir ? cur->Right : cur->Left);
				cur = (dir ? cur->Right : cur->Left);
				dir = COMP::compare(key, cur->Key);
			}
			//2.插入节点到AVL的正确位置上去
			AvlNode<K,T>* last_node = new AvlNode<K,T>(key, ele, cur);
			(dir ? cur->Right : cur->Left) = last_node;
			//最新的节点也要算作路径
			path.push(last_node);
			//记录已经走过的节点
			ArrayStack<AvlNode<K,T>*> back_path;
			if (path.length() < 3)
				return true;
			//3.回溯历史路径，检查平衡性
			while (path.length() != 0) {
				AvlNode<K, T>* point_1 = path.pop();
				//若树不平衡，则使用3个之前走过的路径的节点，进行旋转
				if (point_1->isUnbalanced()) {
					if (back_path.length() < 2)
						return false;
					AvlNode<K,T>* point_2 = back_path.pop();
					AvlNode<K,T>* point_3 = back_path.pop();
					int rotate_identifier = rotate(point_1, point_2, point_3);
					if (rotate_identifier > 0) {
						//先将1号入栈，再将新子树的根节点2号节点入栈
						back_path.push(point_1);
						back_path.push(point_2);
						//检查是否需要改换根节点
						if (rotate_identifier == 2)
							Root = point_2;
					}
					else if (rotate_identifier < 0) {
						//先将1号节点入栈，再将子树的新根节点3号节点入栈
						back_path.push(point_1);
						back_path.push(point_3);
						//检查是否需要改换根节点
						if (rotate_identifier == -2)
							Root = point_3;
					}
					//旋转特征码出现异常，说明AVL的三节点的特征识别失败
					else return false;
				}
				//该节点平衡，直接压入路径栈中
				else back_path.push(point_1);
			}
			return true;
		}
	}

	//普通前序遍历
	void traverse() {
		Root->traverse();
	}

	//双队列交叉的宽度遍历（未修改）
	//无节点的位置使用-1代替，只有有父节点的地方的子节点才会标注-1
	int widthTraverse() {
		ArrayQueue<AvlNode<int,int>*> queue1;
		ArrayQueue<AvlNode<int,int>*> queue2;
		bool isFirst = true;
		queue1.enqueue(Root);
		int max = 0;
		int counter;
		while (true) {
			queue2.clear();
			counter = 0;
			while (queue1.length() > 0) {
				std::cout << queue1.frontValue()->Key << " ";
				if (queue1.frontValue()->Left != NULL)
					queue2.enqueue(queue1.frontValue()->Left);
				else if (queue1.frontValue()->Key != -1) {
					int r = -1;
					AvlNode<int, int>* interval = new AvlNode<int, int>(r, r, NULL);
					queue2.enqueue(interval);
				}
				if (queue1.frontValue()->Right != NULL)
					queue2.enqueue(queue1.frontValue()->Right);
				else if (queue1.frontValue()->Key != -1) {
					int r = -1;
					AvlNode<int, int>* interval = new AvlNode<int, int>(r, r, NULL);
					queue2.enqueue(interval);
				}
				counter++;
				queue1.dequeue();
			}
			std::cout << std::endl;
			if (counter > max)
				max = counter;
			else if (counter == 0)
				break;

			queue1.clear();
			counter = 0;
			while (queue2.length() > 0) {
				std::cout << queue2.frontValue()->Key << " ";
				if (queue2.frontValue()->Left != NULL)
					queue1.enqueue(queue2.frontValue()->Left);
				else if (queue2.frontValue()->Key != -1){
					int r = -1;
					AvlNode<int, int>* interval = new AvlNode<int, int>(r, r, NULL);
					queue1.enqueue(interval);
				}
				if (queue2.frontValue()->Right != NULL)
					queue1.enqueue(queue2.frontValue()->Right);
				else if (queue2.frontValue()->Key != -1){
					int r = -1;
					AvlNode<int, int>* interval = new AvlNode<int, int>(r, r, NULL);
					queue1.enqueue(interval);
				}
				counter++;
				queue2.dequeue();
			}
			if (counter > max)
				max = counter;
			else if (counter == 0)
				break;
			std::cout << std::endl;
		}
		return max;
	}

	//检查AVL整棵树是否平衡
	void checkBalanced() {
		if (checkBalancedHelper(Root))
			cout << "树平衡！" << endl;
		else cout << "树不平衡！" << endl;
	}
};