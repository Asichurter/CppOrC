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
		
		const T& topValue(){
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
