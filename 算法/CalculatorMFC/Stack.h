template <typename T> class Stack{
	private:
		void operator =(const Stack&){}
		Stack(const Stack&){}
	public:
		Stack(){}
		virtual ~Stack(){}
		virtual T pop() = 0;
		virtual void push(const T& item) = 0;
		virtual void clear() = 0;
		virtual T& topValue() = 0;
		virtual int length() const = 0;
};
