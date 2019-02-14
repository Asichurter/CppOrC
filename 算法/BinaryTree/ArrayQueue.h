#include <iostream>
#include "Queue.h"

using namespace std;

template <typename T> class ArrayQueue: public Queue<T>{
	private:
		int Front;
		int Rear;
		int MaxSize;
		T* Array;
	public:
		ArrayQueue(int size = 20){
			Front = 1;
			Rear = 0;
			MaxSize = size;
			Array = new T[size+1];
		}
		
		~ArrayQueue(){
			delete [] Array;
		}
		
		void clear(){
			Rear = 0;
			Front = 1;
		}
		
		void enqueue(const T& item){
			if ((Rear+2)%MaxSize == Front)
				cout << "队列已满" << endl;
			else {
				Rear = (Rear+1)%MaxSize;
				*(Array+Rear) = item;
			}
		}
		
		T dequeue(){
			if ((Rear+1)%MaxSize == Front){
				cout << "队列为空！" << endl;
				return NULL;
			}
			else {
				T temp = *(Array+Front);
				Front = (Front+1)%MaxSize;
				return temp;
			}
		}
		
		const T& frontValue(){
			if ((Rear+1)%MaxSize == Front){
				cout << "队列为空！" << endl;
				return NULL;
			}
			else return *(Array+Front);
		}
		
		int length() const{
			return (Rear+MaxSize-Front+1)%MaxSize;
		}
		
		void showAllItems(){
			int i = length();
			int j = 0;
			const int I = i;
			while (i > 0){
				cout << "第" << I-i << "个元素：" << *(Array+((Front+j)%MaxSize)) << endl;
				j++;
				i--;
			}
		}
};
