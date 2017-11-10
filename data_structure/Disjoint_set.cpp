//
// Linked list representation of disjoint set
//
#include <iostream>
#include <unordered_map>
using namespace std;

template<typename T>
struct node;

template <typename T>
struct pivot{
    size_t size = 1;
    node<T> *head, *tail;
};

template <typename T>
struct node{
    node(T &k):key(k), parent(nullptr), next(nullptr){}  
    const T &key;
    pivot<T> *parent;
    node *next;
};


template <typename T>
class ListSets
{
public:
    using Node = node<T>;
    using PivotType = pivot<T>;
    void make_set(T &k);
    PivotType* find(T &k);
    void Union(PivotType* s1, PivotType* s2);
private:
    // hash for fast access
    unordered_map<T *, Node*> record;
};

template<typename T>
void ListSets<T>::make_set(T &k)
{
    auto newset = new PivotType;
    newset->head = new Node(k);
    newset->tail = newset->head;
    newset->head->parent = newset;
    //initialize set

    record.insert({&k, newset->head});    
    //set record
}

template<typename T>
typename ListSets<T>::PivotType* ListSets<T>::find(T &k)
{
    return record[&k]->parent;
}

template<typename T>
void ListSets<T>::Union(ListSets<T>::PivotType* p1, ListSets<T>::PivotType* p2)
{
    if (p1 == p2)
        return;
    if (p1->size > p2->size)
    {
        auto p = p2->head;
        p1->size += p2->size;
        p1->tail->next = p;
        //link chain
        
        while (p != nullptr)
        {
            p->parent = p1;
            p = p->next;
        }
        //merge
        delete p2;
    }
    else{
        auto p = p1->head;
        p2->size += p1->size;
        p2->tail->next = p;

        while (p != nullptr)
        {
            p->parent = p2;
            p = p->next;
        }
        delete p1;
    }
}

int main()
{
    int test[] = {1,2,3,4};
    ListSets<int> t;
    for (auto &i :test)
        t.make_set(i);
    t.Union(t.find(test[0]), t.find(test[1]));
    t.Union(t.find(test[2]), t.find(test[3]));
    t.Union(t.find(test[1]), t.find(test[3]));
    if(t.find(test[0]) == t.find(test[2]))
        cout << "same component" << endl;
    return 0;
}