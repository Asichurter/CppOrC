#pragma once
#include "AvlNode.h"
#include "ArrayStack.h"
#include "ArrayQueue.h"

/********************************
	AVL����ƽ����
	2018.12.2
*********************************/

template <typename K, typename T, typename COMP> class AVL {
private:
	//�����ת������
	//1������
	//2������
	//3������
	//4: ����
	//-1: ����
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

	//�����ͣ���Ҫ����
	bool rotate_rr(AvlNode<K, T>* node_1, AvlNode<K, T>* node_2) {
		bool root_switch = false;
		//��1�Žڵ��ƶ���2�Žڵ����ڵ���
		node_1->Right = node_2->Left;
		if (node_2->Left != NULL) node_2->Left->Father = node_1;
		node_2->Left = node_1;
		//�ж�node_1���丸�ڵ�������ҽڵ�
		//true: �� 
		//false:��
		if (node_1->Father != NULL) {
			bool node_1_vs_father = COMP::compare(node_1->Key, node_1->Father->Key);
			(node_1_vs_father ? node_1->Father->Right : node_1->Father->Left) = node_2;
		}//�������ڵ��ϵ
		//���1�Žڵ�û�и��ڵ㣬������ڵ���Ҫ�Ļ�
		else root_switch = true;
		node_2->Father = node_1->Father;
		node_1->Father = node_2;
		return root_switch;
	}

	//�����ͣ���Ҫ������ת
	bool rotate_rl(AvlNode<K, T>* node_1, AvlNode<K, T>* node_2, AvlNode<K, T>* node_3) {
		bool root_switch = false;
		//��2�Žڵ��ƶ���3�Žڵ���ҽڵ���ȥ
		node_2->Left = node_3->Right; 
		//���3�Žڵ�����ҽڵ��Ƿ�Ϊ�գ�����ǵĻ��Ͳ��øı��丸�ڵ������
		if (node_3->Right != NULL) node_3->Right->Father = node_2;
		node_3->Right = node_2;
		node_2->Father = node_3;
		//��3�Žڵ�ĸ��ڵ�����Ϊ1�Žڵ�ĸ��ڵ㣬�̳и��ڵ�
		if (node_1->Father != NULL){
			bool node_1_vs_father = COMP::compare(node_1->Key, node_1->Father->Key);
			(node_1_vs_father ? node_1->Father->Right : node_1->Father->Left) = node_3;
		}//��1�Žڵ�����Ϊ3�Žڵ����ڵ�
		//���1�Žڵ�û�и��ڵ㣬������ڵ���Ҫ�Ļ�
		else root_switch = true;
		node_3->Father = node_1->Father;
		node_1->Right = node_3->Left;
		if (node_3->Left != NULL) node_3->Left->Father = node_1;
		node_3->Left = node_1;
		node_1->Father = node_3;
		return root_switch;
	}

	//�����ͣ���Ҫ����
	bool rotate_ll(AvlNode<K, T>* node_1, AvlNode<K, T>* node_2) {
		bool root_switch = false;
		node_1->Left = node_2->Right;
		if (node_2->Right != NULL) node_2->Right->Father = node_1;
		node_2->Right = node_1;
		if (node_1->Father != NULL){
			bool node_1_vs_father = COMP::compare(node_1->Key, node_1->Father->Key);
			(node_1_vs_father ? node_1->Father->Right : node_1->Father->Left) = node_2;
		}
		//���1�Žڵ�û�и��ڵ㣬������ڵ���Ҫ�Ļ�
		else root_switch = true;
		node_2->Father = node_1->Father;
		node_1->Father = node_2;
		return root_switch;
	}

	//�����ͣ���Ҫ������ת
	bool rotate_lr(AvlNode<K, T>* node_1, AvlNode<K, T>* node_2, AvlNode<K, T>* node_3) {
		bool root_switch = false;
		//��2�Žڵ��ƶ���3�Žڵ���ҽڵ���ȥ
		node_2->Right = node_3->Left;
		//���3�Žڵ�����ҽڵ��Ƿ�Ϊ�գ�����ǵĻ��Ͳ��øı��丸�ڵ������
		if (node_3->Left != NULL) node_3->Left->Father = node_2;
		node_3->Left = node_2;
		node_2->Father = node_3;
		//��3�Žڵ�ĸ��ڵ�����Ϊ1�Žڵ�ĸ��ڵ㣬�̳и��ڵ�
		if (node_1->Father != NULL){
			bool node_1_vs_father = COMP::compare(node_1->Key, node_1->Father->Key);
			(node_1_vs_father ? node_1->Father->Right : node_1->Father->Left) = node_3;
		}//��1�Žڵ�����Ϊ3�Žڵ����ڵ�
		//���1�Žڵ�û�и��ڵ㣬������ڵ���Ҫ�Ļ�
		else root_switch = true;
		node_3->Father = node_1->Father;
		node_1->Left = node_3->Right;
		if (node_3->Right != NULL) node_3->Right->Father = node_1;
		node_3->Right = node_1;
		node_1->Father = node_3;
		return root_switch;
	}

	//����ֵ��
	//1��2Ϊ���ģ���1,2ѹջ 2:��ı���ڵ�
	//-1: 3Ϊ���ģ���1,3ѹջ -2����ı���ڵ�
	//0����������
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

	//�ݹ���õ�AVL��ƽ���鷽��
	bool checkBalancedHelper(AvlNode<K, T>* root) {
		if (root == NULL) return true;
		if (root->isUnbalanced()) return false;
		else return checkBalancedHelper(root->Left) && checkBalancedHelper(root->Right);
	}

public:
	AvlNode<K,T>* Root;
	
	AVL() {Root = NULL;}

	//��AVL�в���һ����¼
	bool insert(K& key, T& ele) {
		if (Root == NULL) {
			Root = new AvlNode<K, T>(key, ele, NULL);
			return true;
		}
		else {
			AvlNode<K, T>* cur = Root;
			//��¼·���Ͼ����Ľڵ�
			ArrayStack<AvlNode<K, T>*> path;
			path.push(Root);
			//��������ǰ������true����
			//�Ƚϵ��Ǽ�ֵ�Ŷ�
			bool dir = COMP::compare(key, cur->Key);
			//1.��cur�ƶ����������λ��
			while ((dir && cur->Right != NULL) || (!dir && cur->Left != NULL)) {
				path.push(dir ? cur->Right : cur->Left);
				cur = (dir ? cur->Right : cur->Left);
				dir = COMP::compare(key, cur->Key);
			}
			//2.����ڵ㵽AVL����ȷλ����ȥ
			AvlNode<K,T>* last_node = new AvlNode<K,T>(key, ele, cur);
			(dir ? cur->Right : cur->Left) = last_node;
			//���µĽڵ�ҲҪ����·��
			path.push(last_node);
			//��¼�Ѿ��߹��Ľڵ�
			ArrayStack<AvlNode<K,T>*> back_path;
			if (path.length() < 3)
				return true;
			//3.������ʷ·�������ƽ����
			while (path.length() != 0) {
				AvlNode<K, T>* point_1 = path.pop();
				//������ƽ�⣬��ʹ��3��֮ǰ�߹���·���Ľڵ㣬������ת
				if (point_1->isUnbalanced()) {
					if (back_path.length() < 2)
						return false;
					AvlNode<K,T>* point_2 = back_path.pop();
					AvlNode<K,T>* point_3 = back_path.pop();
					int rotate_identifier = rotate(point_1, point_2, point_3);
					if (rotate_identifier > 0) {
						//�Ƚ�1����ջ���ٽ��������ĸ��ڵ�2�Žڵ���ջ
						back_path.push(point_1);
						back_path.push(point_2);
						//����Ƿ���Ҫ�Ļ����ڵ�
						if (rotate_identifier == 2)
							Root = point_2;
					}
					else if (rotate_identifier < 0) {
						//�Ƚ�1�Žڵ���ջ���ٽ��������¸��ڵ�3�Žڵ���ջ
						back_path.push(point_1);
						back_path.push(point_3);
						//����Ƿ���Ҫ�Ļ����ڵ�
						if (rotate_identifier == -2)
							Root = point_3;
					}
					//��ת����������쳣��˵��AVL�����ڵ������ʶ��ʧ��
					else return false;
				}
				//�ýڵ�ƽ�⣬ֱ��ѹ��·��ջ��
				else back_path.push(point_1);
			}
			return true;
		}
	}

	//��ͨǰ�����
	void traverse() {
		Root->traverse();
	}

	//˫���н���Ŀ�ȱ�����δ�޸ģ�
	//�޽ڵ��λ��ʹ��-1���棬ֻ���и��ڵ�ĵط����ӽڵ�Ż��ע-1
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

	//���AVL�������Ƿ�ƽ��
	void checkBalanced() {
		if (checkBalancedHelper(Root))
			cout << "��ƽ�⣡" << endl;
		else cout << "����ƽ�⣡" << endl;
	}
};