#include <iostream>
#include "Stack.h"

using namespace std;

template <typename T> class ArrayStack: public Stack<T>{
	private:
		int MaxSize;
		int Size;
		int Top;
		T* Array;
	public:
		ArrayStack(int size = 20){
			MaxSize = size;
			Array = new T[MaxSize];
			Top = 0;
			Size = 0;
		}
		~ArrayStack(){
			delete [] Array;
		}
		
		T pop(){
			if (Size == 0){
				cout << "当前栈为空！" << endl;
				return NULL;
			}
			else return *(Array+(--Size));
		}
		
		void push(const T& ele){
			if (Size == MaxSize){
				cout << "当前栈已满！" << endl;
			}
			else {
				*(Array+(Size++)) = ele;
			}
		}
		
		void clear(){
			Size = 0;
		}
		
		const T& topValue(){
			return *(Array+Size-1);
		}
		
		int length() const{
			return Size;
		} 
		
		void showAllItems(){
			for (int i = Size-1; i >= 0; i--){
				cout << *(Array+i) << endl;
			}
		}
};
