#include <iostream>
#include <array>
#include <exception>
using namespace std;
template<class T, size_t length>
class Queue
{
    #define length  (length + 1)
    //make the capacity be real length
public:
    Queue() : head(0), tail(0), data(){};
    bool empty() { return head == tail; }
    void enqueue(const T &v)
    {
        if ((tail + 1) % length == head)
            throw(overflow_error("Queue Overflow!"));
        else
        {
            tail = (tail + 1) % length;
            data[tail] = v;
        }
  }
  T &dequeue() {
      if(empty())
          throw(underflow_error("Queue Underflow!"));
      else
          head = (head + 1) % length;
      return data[head];
  }

private:
  size_t head, tail;
  array<T, length> data;
};
int main()
{
    Queue<int, 10> TestQueue;
    for (int i = 0; i < 10 ;++i)
        TestQueue.enqueue(i);
    for (int i = 0; i < 10;++i)
        cout << TestQueue.dequeue() << " ";
    cout << endl << TestQueue.empty() << endl;
    return 0;
}