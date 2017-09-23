#include <iostream>
#include "double_linked_list.cpp"
#include <exception>
using namespace std;
template<typename T>
class Mergeable_Heap
{
public:
	Mergeable_Heap() {};
	void make_heap(const List<T> &l) {
		data = l;
	}
	void insert(const T &v) {
		data.push_front(v);
	}
	const T minimum() {
		if (data.size() == 0)
			throw(underflow_error("Empty Heap!"));
		auto p = data.Head()->next;
		auto min = p->key;
		while (p != data.Head())
		{
            if (min > p->key)
				min = p->key;
			p = p->next;
		}
		return min;
	}

	const T extract_min() {
        auto min = minimum();
        auto index = data.search(min);
        auto p = data.Head();
		while (index-->0)
			p = p->next;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		return min;
	}
	Node<T>* Head() { return data.Head(); }
	size_t size() { return data.size(); }

	void Union(Mergeable_Heap<T> &H) {
		if (H.size() == 0)
            return;
        auto last = H.Head()->prev;
        data.Head()->prev->next = H.Head()->next;
        H.Head()->prev = data.Head()->prev;
        data.Head()->prev = last;
        last->next = data.Head();
    }

private:
	List<T> data;
};
int main()
{
	List<int> TestList1, TestList2;
	for (int i = 0; i < 10; ++i)
	{
		TestList1.push_front(i);
		TestList2.push_front(i + 10);
	}
	Mergeable_Heap<int> TestHeap1, TestHeap2;
	TestHeap1.make_heap(TestList1);
    TestHeap2.make_heap(TestList2);
    TestHeap1.Union(TestHeap2);
    for (int i = 0; i < 20; ++i)
		cout << TestHeap1.extract_min() << ",";
	cout << endl;
	return 0;
}