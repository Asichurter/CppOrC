#include<iostream>
#include "List.h"

using namespace std;

template <typename T> class ArrayList: public List<T> {
	private:
		int MaxSize;
		int CurSize;
		int CurPos;
		T* Array;
	public:
		ArrayList(int size = 20){
			MaxSize = size;
			CurSize = 0;
			CurPos = 0;
			Array = new T[MaxSize];
		}
		
		~ArrayList(){
			delete [] Array;
		}
		
		void insert(const T& ele)
		{
			if (CurSize == MaxSize)
				cout << "����Ԫ��ʧ�ܣ�Ԫ�������ﵽ���ޣ�" << endl;
			else{
				for (int i = CurSize-1; i >= CurPos; i--){
					*(Array+i+1) = *(Array+i);
				}
				*(Array+CurPos) = ele;
				CurSize++;
			}	
		}
		
		T remove(){
			if (CurSize == 0)
				return NULL;
			else{
				T temp = *(Array+CurPos);
				for (int i = CurPos; i < CurSize-1; i++){
					*(Array+i) = *(Array+i+1);
				}
				CurSize--;
				return temp;
			}
		}
		
		void append(const T& ele){
			if (CurSize == MaxSize)
				cout << "���Ԫ��ʧ�ܣ�Ԫ�������ﵽ���ޣ�" << endl;
			else{
				*(Array+CurSize) = ele;
				CurSize++;
			}
		}
		
		void next()
		{
			if (CurPos < CurSize-1)
				CurPos++;
			else cout << "�Ѿ������б�ĩ�ˣ��޷�����next��" << endl;
		}
		
		void pre()
		{
			if (CurPos > 0)
				CurPos--;
			else cout << "�Ѿ������б���ǰ�ˣ��޷�����pre��" << endl;
		}
		
		void moveToStart()
		{
			CurPos = 0;
		}
		
		void moveToEnd()
		{
			CurPos = CurSize-1;
		}
		
		int length()
		{
			return CurSize;
		}
		
		int curPos()
		{
			return CurPos;
		}
		
		bool moveToPos(int pos)
		{
			if (pos < 0){
				cout << "���Ϸ���λ��ֵ��" << endl;
				return false;
			}
			else if (pos >= CurSize){
				cout << "λ��ֵ�����" << endl;
				return false;
			}
			else{
				CurPos = pos;
				return true;
			} 
		}
		
		T get () const
		{
			return *(Array+CurPos);
		}
		
		bool hasEle(T& ele)
		{
			if (CurSize == 0)
				return false;
			else {
				for (int i = 0; i < CurSize; i++){
					if (*(Array+i) == ele)
						return true;
				}
				return false;
			}
		}
		
		void showAllItems()
		{
			cout << endl;
			for (int i = 0; i < CurSize; i++){
				cout << *(Array+i) << endl;
			}
			cout << endl;
		}
};








