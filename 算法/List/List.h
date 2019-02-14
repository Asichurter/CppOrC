#include<iostream>

using namespace std;

template <typename T> class List{
	private :
		void operator = (const List&){};
		List(const List&){};
	public :
		List(){};
		virtual ~List(){};
		
		virtual void insert(const T& item) = 0;
		virtual T remove() = 0;
		virtual void append(const T& item) = 0;
		virtual void next() = 0;
		virtual void pre() = 0;
		virtual void moveToStart() = 0;
		virtual void moveToEnd() = 0;
		virtual int length() = 0;
		virtual int curPos() = 0;
		virtual bool moveToPos(int pos) = 0;
		virtual T get() const = 0;
		virtual bool hasEle(T& ele) = 0; 
};
