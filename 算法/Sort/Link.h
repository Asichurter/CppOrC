#include <iostream>

template <typename T> class Link{
	private:
		//使用了freelist的link节点 
		//static Link<T>* FreeList;
	public:
		T Element;
		Link<T>* Next;
		Link(const T& ele, Link<T>* ptr=NULL){
			Element = ele;
			Next = ptr;
		}
		Link(Link<T>* ptr=NULL){
			Next = ptr;
		}
		/*
		void* operator new(size_t){
			if (Link::FreeList == NULL)
				return ::new Link<T>;
			Link<T>* temp = FreeList;
			Link::FreeList = Link::FreeList->Next;
			return temp;
		}
		
		void operator delete(void* ptr){
			((Link<T>*)ptr)->Next = Link::FreeList;
			Link::FreeList = (Link<T>*)ptr;
		}
		*/
};
