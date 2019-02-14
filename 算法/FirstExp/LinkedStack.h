#include "Stack.h"
#include "Link.h"

using namespace std;

template <typename T> class LinkedStack: public Stack<T>{
	private:
		Link<T>* Head;
		Link<T>* Top;
		int Size;
		
		void clearHelper(){
			while (Head != NULL){
				Link<T>* ptr = Head;
				Head = Head->Next;
				delete ptr;
			}
			Size = 0;
		}
		
		void initHelper(){
			Head = Top = new Link<T>;
			Size = 0;
		}
		
	public:
		LinkedStack(){
			initHelper();
		}
		~LinkedStack(){
			clearHelper();
		}

		/*
		LinkedStack(LinkedStack<T>& src) {
			LinkedStack<T> temp;
			T* buffer = new T[src.length()];
			int i = 0;
			while (src.length() > 0) {
				T t = src.pop();
				buffer[i++] = T(t);
				temp.push(t);
			}
			while (temp.length() > 0) {
				src.push(temp.pop());
			}
			for (int i = src.length()-1; i >= 0; i--) {
				push(buffer[i]);
			}
			delete[] buffer;
		}*/
		
		T pop(){
			if (Size == 0)
				cout << "栈中没有元素！" << endl;
			else {
				Link<T>* ptr = Top;
				T ele = Top->Element;
				Top = Top->Next;
				delete ptr;
				Size--;
				return ele;
			}
		}
		
		void push(const T& item){
			Top = new Link<T>(item, Top);
			Size++;
		}
		
		void clear(){
			clearHelper(); 
		}
		
		T& topValue(){
			if (Size == 0)
				cout << "栈中没有元素！" << endl;
			else return Top->Element;
		}
		
		int length() const{
			return Size;
		}
		
		void showAllItems(){
			if (Size == 0){
				cout << "栈中没有元素！" << endl;
				return;
			}
			Link<T>* ptr = Top;
			while (ptr != Head){
				cout << ptr->Element << endl;
				ptr = ptr->Next;
			}
		}
};
