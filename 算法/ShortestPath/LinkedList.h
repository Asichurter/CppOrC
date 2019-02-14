#include <iostream>
#include "Link.h"

using namespace std;

template <typename T> class LinkedList{
	private:
		Link<T>* Head;
		Link<T>* Cur;
		Link<T>* Tail;
		int Size;
		void clear()
		{
			while (Head != NULL){
				Cur = Head->Next;
				delete Head;
				Head = Cur;
			}
			Size = 0;
		}
		void init(){
			Cur = Tail = Head = new Link<T>;
			Size = 0;
		}
	public:
		LinkedList(){init();}
		~LinkedList(){clear();}
		
		void insert(const T& item)
		{
			Link<T>* temp = new Link<T>(item, Cur->Next);
			Cur->Next = temp;
			if (Cur == Tail) {
				Tail = Cur->Next;
			}
			Size++;
		}
		
		T remove()
		{
			if (Cur == Tail)
				cout << "��ǰλ�ô����б�ĩ�ˣ��޿��Ƴ���Ԫ�أ�" << endl;
			else {
				if (Cur->Next == Tail)
					Tail = Cur;				
				Link<T>* ptr = Cur->Next;
				T temp = Cur->Next->Element;
				Cur->Next = Cur->Next->Next;
				Size--;
				delete ptr;
				return temp;
			}
		}
		
		void append(const T& item)
		{
			Link<T>* temp = new Link<T>(item);
			Tail = Tail->Next = temp;
			Size++;
		}
		
		void next()
		{
			if (Cur == Tail)
				cout << "��ǰ�Ѿ������б�ĩ�ˣ��޷�����next��" << endl;
			else {
				Cur = Cur->Next;
			}
		}

		bool hasNext() {
			return Cur->Next != Tail || Cur==Tail;
		}
		
		void pre()
		{
			if (Cur == Head)
				cout << "��ǰ�Ѿ������б���ǰ�ˣ��޷�����pre��" << endl;
			else {
				Link<T>* temp = Head;
				while (temp->Next != Cur)
					temp = temp->Next;
				Cur = temp;
			} 
		}
		
		void moveToStart()
		{
			Cur = Head;
		}
		
		void moveToEnd()
		{
			Cur = Tail;
		}
		
		int length()
		{
			return Size;
		}
		
		int curPos()
		{
			Link<T>* temp = Head;
			int counter = 0;
			while (temp != Cur){
				temp = temp->Next;
				counter++;
			}
			return counter;
		}
		
		bool moveToPos(int pos)
		{
			if (pos < 0){
				cout << "���Ϸ���λ��ֵ��" << endl;
				return false; 
			} 
			else if (pos >= Size){
				cout << "λ�������" << endl;
				return false;
			}
			else {
				Cur = Head;
				while (pos-- > 0){
					Cur = Cur->Next;
				}
				return true;
			}
		}
		
		T& get()
		{
			return Cur->Next->Element;
		}
		
		bool hasEle(T& ele)
		{
			if (Size == 0)
				return false;
			Link<T>* temp = Head;
			while (temp != Tail){
				temp = temp->Next;
				if (temp->Element == ele)
					return true;
			}
			return false;
		}
		
		void showAllItems()
		{
			if (Size == 0){
				cout << "����Ϊ�գ�" << endl;
				return;
			}
			cout << endl;
			Link<T>* temp = Head;
			while (temp != Tail){
				temp = temp->Next;
				cout << temp->Element << endl;
			}
			cout << endl;
		}
		
		void clearLove(){
			clear();
		}
};
