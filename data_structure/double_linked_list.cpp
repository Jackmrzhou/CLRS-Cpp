#include <iostream>
using namespace std;
template<class T>
class Node
{
public:
  Node() :key() {};
  Node(T& k) : key(k){};
  T key;
  Node *next, *prev;
};
template<class T>
class List
{
public:
  List() :  __size(0){
      head->next = head;
      head->prev = head;
  };
  void push_front(const T &obj);
  size_t search(const T &k);
  T pop_front();
  size_t size() { return __size; }
  Node<T> *Head() { return head; }

private:
  Node<T> *head = new Node<T>;
  //head don't store data
  size_t __size;
};
/*
int  main()
{
    List<int> TestList;
    for (int i = 0; i < 5;++i)
        TestList.push_front(i);
    cout << TestList.size() << endl;
    cout << TestList.search(0) << endl;
    for (int i = 0; i < 5;++i)
        cout << TestList.pop_front() << ',';
    cout << endl;
    return 0;
}
*/
template<class T>
void List<T>::push_front(const T &obj)
{
    Node<T> *node = new Node<T>;
    node->key = obj;
    head->next->prev = node;
    node->next = head->next;
    node->prev = head;
    head->next = node;
    __size++;
}

template<class T>
T List<T>::pop_front()
{
    auto node = head->next;
    auto res = node->key;
    head->next = node->next;
    node->next->prev = head;
    __size--;
    delete node;
    return res;
}

template<class T>
size_t List<T>::search(const T &k)
{
    if (__size==0)
        return 0;
    //impossible
    auto p = head->next;
    size_t index = 0;
    while (p != head)
    {
        index++;
        if (k == p->key)
            return index;
        p = p->next;
    }
    return 0;
    //not found
}