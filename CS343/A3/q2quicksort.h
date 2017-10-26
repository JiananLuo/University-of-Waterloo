#ifndef __QUICKSORT__
#define __QUICKSORT__

template<typename T> _Task Quicksort {
	private:
		T * values;
		unsigned int low, high, depth;
		void swap(TYPE* a, TYPE* b);
		void quickSort();
		void main();

	public:
		Quicksort(T values[], unsigned int low, unsigned int high, unsigned int depth) : values(values), low(low), high(high), depth(depth) {}
};

#endif
