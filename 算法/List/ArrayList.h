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
				cout << "插入元素失败！元素数量达到上限！" << endl;
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
				cout << "添加元素失败！元素数量达到上限！" << endl;
			else{
				*(Array+CurSize) = ele;
				CurSize++;
			}
		}
		
		void next()
		{
			if (CurPos < CurSize-1)
				CurPos++;
			else cout << "已经到了列表末端！无法继续next！" << endl;
		}
		
		void pre()
		{
			if (CurPos > 0)
				CurPos--;
			else cout << "已经到了列表最前端，无法继续pre！" << endl;
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
				cout << "不合法的位置值！" << endl;
				return false;
			}
			else if (pos >= CurSize){
				cout << "位置值溢出！" << endl;
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








