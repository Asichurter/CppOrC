#include <iostream>

template <typename K, typename T> class Link{
	public:
		K Key;
		T Element;
		Link<K,T>* Next;
		Link(K& key, T& ele=NULL, Link<K,T>* ptr=NULL){
			Key = key;
			Element = ele;
			Next = ptr;
		}
};
