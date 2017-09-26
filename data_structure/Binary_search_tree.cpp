#include <iostream>
#include <random>
using namespace std;
template<typename T>
class Node
{
public:
  Node() : key(), left(nullptr), right(nullptr), p(nullptr){};
  Node(const int &v):key(v),data(v+10), left(nullptr), right(nullptr), p(nullptr){};  
  //data is int and key+10 for test
  int key;
  T data;
  Node<T> *left, *right, *p;
};
template<typename T>
class Binary_search_tree
{
public:
  void Insert(Node<T> &&v);
  Node<T>* search(int key, Node<T>* n);
  void inorder_print(const Node<T> *x);
  void inorder_print(){
      inorder_print(root);
  }
  Node<T>* search(int key){
      return search(key, root);
  }
  Node<T> *maximum(Node<T> *x){
      while (x->right != nullptr)
          x = x->right;
      return x;
  }
  Node<T>* minimum(Node<T> *x){
      while(x->left != nullptr)
          x = x->left;
      return x;
  }
  Node<T> *successor(Node<T> *x);
  void Delete(int key);
  void Transplant(Node<T> *u, Node<T> *v);

private:
  Node<T> *root=nullptr;
};
int main()
{
    Binary_search_tree<int> TestTree;
    //default_random_engine generator;
    //uniform_int_distribution<int> distribution(0, 20);
    for (int i = 0; i < 10;++i)
    {
        //int rand_num = distribution(generator);
        TestTree.Insert(Node<int>(i));
    }
    TestTree.inorder_print();
    cout << TestTree.search(5)->data << endl;
    cout << TestTree.successor(TestTree.search(5))->key << endl;
    TestTree.Delete(5);
    TestTree.inorder_print();
    return 0;
}

template<typename T>
void Binary_search_tree<T>::Insert(Node<T> && v)
{
    auto vv = new Node<T>(v);
    Node<T> *y = nullptr;
    auto x = root;
    while(x != nullptr)
    {
        y = x;
        if (vv->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    vv->p = y;
    if(y == nullptr)
        root = vv;
    else if (vv->key < y->key)
        y->left = vv;
    else
        y->right = vv;
}

template<typename T>
void Binary_search_tree<T>::inorder_print(const Node<T> *x)
{
    if (x != nullptr)
    {
        inorder_print(x->left);
        cout << x->key << " ";
        inorder_print(x->right);
    }
}

template<typename T>
Node<T>* Binary_search_tree<T>::search(int key, Node<T> *n)
{
    if (n == nullptr || n->key == key)
        return n;
    if (key < n->key)
        return search(key, n->left);
    else
        return search(key, n->right);
}

template<typename T>
Node<T>* Binary_search_tree<T>::successor(Node<T> *x)
{
    if (x->right != nullptr)
        return minimum(x->right);
    auto y = x->p;
    while (y != nullptr && x == y->right)
    {
        x = y;
        y = y->p;
    }
    return y;
}

template<typename T>
void Binary_search_tree<T>::Delete(int key)
{
    auto z = search(key, root);
    if (z->left == nullptr)
        Transplant(z, z->right);
    else if (z->right == nullptr)
        Transplant(z, z->right);
    else 
    {
        auto y = minimum(z->right);
        if (y->p != z)
        {
            Transplant(y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        Transplant(z, y);
        y->left = z->left;
        y->left->p = y;
    }
}

template<typename T>
void Binary_search_tree<T>::Transplant(Node<T> *u, Node<T> *v)
{
    if (u->p == nullptr)
        root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    if (v != nullptr)
        v->p = u->p;
}