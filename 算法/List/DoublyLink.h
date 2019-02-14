#include <iostream>

template <typename T> class DoublyLink{
	public:
		DoublyLink<T>* Pre;
		DoublyLink<T>* Next;
		T Element;
		
		DoublyLink(const T& ele, DoublyLink<T>* n=NULL, DoublyLink<T>* p=NULL){
			Pre = p;
			Next = n;
			Element = ele;
		}
		
		DoublyLink(DoublyLink<T>* p=NULL, DoublyLink<T>* n=NULL){
			Pre = p;
			Next = n;
		}
};
