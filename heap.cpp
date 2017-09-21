#include <iostream>
#include <array>
#include <algorithm>
#include <exception>
using namespace std;
template <class T, size_t length>
class Heap
{
  public:
    Heap() : __Length(length),__heap_size(length), Data(){};
    Heap(const array<T, length> &d) : __Length(length),__heap_size(length), Data(d){};
    inline size_t Parent(int i);
    inline size_t Left(int i);
    inline size_t Right(int i);
    inline size_t Length();
    inline const array<T, length> &data();
    inline T Heap_Maximum();
    void Max_Heapify(int i);
    //assumes that the binary trees rooted at LEFT[i] and RIGHT[i] are maxheaps
    //but that A[i] might be smaller than its children
    void build_max_heap();
    void HeapSort();
    T Extract_Max();

  private:
    size_t __Length;
    size_t __heap_size;
    array<T, length> Data;
};
int main()
{
    Heap<int, 10> TestHeap(array<int, 10>{4, 1, 3, 2, 16, 9, 10, 14, 8, 7});
    //cout << TestHeap.Length() << endl;
    //TestHeap.build_max_heap();
    //TestHeap.HeapSort();
    //for_each(TestHeap.data().begin(), TestHeap.data().end(), [](const int &n) { cout << n << ' '; });
    //cout << endl;
    TestHeap.build_max_heap();
    try{
        for (int i = 0; i < 11; ++i)
            cout << TestHeap.Extract_Max() << ' ';
    }
    catch(underflow_error &e){
        cout << e.what() << endl;
    }
    return 0;
}

template <class T, size_t length>
inline size_t Heap<T, length>::Length()
{
    return __Length;
}

template <class T, size_t length>
inline size_t Heap<T, length>::Parent(int i)
{
    return i >> 1;
}

template <class T, size_t length>
inline size_t Heap<T, length>::Left(int i)
{
    return i << 1;
}

template <class T, size_t length>
inline size_t Heap<T, length>::Right(int i)
{
    return (i << 1) + 1;
}

template <class T, size_t length>
inline const array<T, length> &Heap<T, length>::data()
{
    return Data;
}

template <class T, size_t length>
void Heap<T, length>::Max_Heapify(int i)
{
    size_t largest;
    auto l = Left(i);
    auto r = Right(i);
    if (l <= __heap_size && Data[l - 1] > Data[i - 1])
        largest = l;
    else
        largest = i;
    if (r <= __heap_size && Data[r - 1] > Data[largest - 1])
        largest = r;
    if (largest != i)
    {
        swap(Data[i - 1], Data[largest - 1]);
        Max_Heapify(largest);
    }
}

template <class T, size_t length>
void Heap<T, length>::build_max_heap()
{
    for (int i = length / 2; i >= 1; --i)
        Max_Heapify(i);
    //bottom-up
}

template <class T, size_t length>
void Heap<T, length>::HeapSort()
{
    build_max_heap();
    for (auto i = __Length; i > 1; --i)
    {
        swap(Data[0], Data[i - 1]);
        __heap_size--;
        Max_Heapify(1);
    }
}

template <class T, size_t length>
inline T Heap<T, length>::Heap_Maximum()
{
    return Data[1];
}

template <class T, size_t length>
T Heap<T, length>::Extract_Max()
{
    if (__heap_size < 1)
        throw(underflow_error("Heap Underflow!"));
    auto max = Data[0];
    Data[0] = Data[__heap_size - 1];
    __heap_size--;
    Max_Heapify(1);
    return max;
}