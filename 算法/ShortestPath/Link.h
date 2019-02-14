
template <typename T> class Link{
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
};
