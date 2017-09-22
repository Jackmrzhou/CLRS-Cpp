#include <iostream>
#include <array>
#include <exception>
using namespace std;
template<class T, size_t length>
class Stack
{
public:
    Stack() : top(0),__stack_size(length), data(){};
    bool empty() { return top == 0; }
    void push(const T &v) { 
        if (top+1 == length)
            throw(overflow_error("Stack Overflow!"));
        else
            data[++top] = v;
    }
    T& pop(){
        if (top == 0)
            throw(underflow_error("Stack Underflow!"));
        else return data[top--];
    }

  private:
    size_t top;
    size_t __stack_size;
    array<T, length+1> data;    
};
int main()
{
    Stack<int, 10> TestStack;
    for (int i = 0; i < 10;++i)
        TestStack.push(i);
    for (int i = 0; i < 10;++i)
        cout << TestStack.pop() << " ";
    cout << endl;
    cout << TestStack.empty() << endl;
    return 0;
}