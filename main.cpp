// lab6.7
#include <iostream>

using namespace std;

class IFilter {
public:
	virtual bool operator () (int k) = 0;
};

class FilterEven : public IFilter {
public:
	bool operator () (int k) {
		//cout << "FilterEven " << k << endl;
		return (k % 2) == 0 ;
	}
};

class FilterPositive : public IFilter {
public:
	bool operator () (int k) {
		//cout << "FilterPositive " << k << endl; 
		return k > 0;
	}
};

struct Array {
	int* start;
	int size;
};

Array Merge(Array a, Array b) {
	Array result;
	result.size = a.size + b.size;
	result.start = new int[result.size];
	int* ptr_a = a.start;
	int* ptr_b = b.start;
	int* ptr_result = result.start;
	for (; ptr_a < a.start + a.size && ptr_b < b.start + b.size; ) {
		if ((*ptr_a) > (*ptr_b)) {
			*ptr_result = *ptr_a;
			ptr_a++;
			ptr_result++;
		}
		else {
			*ptr_result = *ptr_b;
			ptr_b++;
			ptr_result++;
		}
	}
	if (ptr_a == a.start + a.size) {
		for (; ptr_b < b.start + b.size; ptr_b++, ptr_result++) {
			*ptr_result = *ptr_b;
		}
	}
	else {
		for (; ptr_a < a.start + a.size; ptr_a++, ptr_result++) {
			*ptr_result = *ptr_a;
		}
	}
	return result;
}

Array ArrayFilter(Array a, IFilter& f) {
	Array result = { new int[a.size], a.size };
	int* result_ptr = result.start;
	int* a_ptr = a.start;
	int size = 0;
	for (; a_ptr < a.start + a.size; a_ptr++) {
		if (f(*a_ptr)) {
			*result_ptr = *a_ptr;
			size++;
			result_ptr++;
		}
	}
	result.size = size;
	return result;
}

void ShowArray(Array a) {
	for (int i = 0; i < a.size; i++) {
		cout << *(a.start + i) << " ";
	}
	cout << endl;
}

Array Merge_if(Array a, Array b, IFilter& f) {
	return Merge(ArrayFilter(a, f), ArrayFilter(b, f));
}


int main() {
	Array a = { new int[5]{ 9, 7, 5, 3, 1 }, 5 };
	Array b = { new int[5]{ 8, 6, 4, 2, 0 }, 5 };
	Array r = Merge(a,b);
	ShowArray(r);
	IFilter* f = new FilterEven; 
	cout << (*f)(2) << " " << (*f)(-5) << endl;
	Array c = { new int[5]{ 3, -4, 5, -3, 1 }, 5 };
	ShowArray(ArrayFilter(c, *f));
	Array d = { new int[5]{ 10, 6, 5, -3, -5 }, 5 };
	Array e = { new int[5]{ 12, 10, 4, -7, -8 }, 5 };
	Array g = Merge_if(d, e, *f);
	ShowArray(g);
	delete[] a.start;

	return 0;
}
