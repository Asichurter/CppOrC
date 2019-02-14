template <typename T> class Queue{
	private:
		void operator=(const Queue&){}
		Queue(const Queue&){}
	public:
		Queue(){}
		virtual ~Queue(){}
		
		virtual void clear() = 0;
		virtual void enqueue(const T& item) = 0;
		virtual T dequeue() = 0;
		virtual const T& frontValue() = 0;
		virtual int length() const = 0;
};
