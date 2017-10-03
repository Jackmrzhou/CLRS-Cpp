#include <iostream>
using namespace std;
using _color_type = bool;
constexpr _color_type Red = true;
constexpr _color_type Black = false;
template<typename T>
class Node
{
public:
  Node(int k, const T &v) : key(k), value(v), left(nullptr), right(nullptr),color(Red){}
  //new nodes are always red
  int key;
  //integer key for demo
  T value;
  Node<T> *left, *right;
  _color_type color;
};
template <typename T>
class LL_RB_Tree
{
public:
    LL_RB_Tree():root(nullptr){}
    void Insert(int key, const T &value){
        root = Insert(root, key, value);
        root->color = Black;
    }
    void inorder_print(){
        inorder_print(root);
    }
    void inorder_print(Node<T> *x){
        if (x != nullptr)
        {
            inorder_print(x->left);
            cout << x->key << ": "<<x->value<<", ";
            inorder_print(x->right);
        }
    }
private:
  Node<T>* Insert(Node<T> *h, int key, const T &value);
  void colorFilp(Node<T> *h){
      h->color = !h->color;
      h->left->color = !h->left->color;
      h->right->color = !h->right->color;
  }
  Node<T> *leftRotate(Node<T> *h);
  Node<T> *rightRotate(Node<T> *h);
  bool isRed(Node<T> *h);
  Node<T> *root;
};

template<typename T>
bool LL_RB_Tree<T>::isRed(Node<T> *h)
{
    if (h==nullptr)
        return false;
    else
        return h->color == Red;
}

template<typename T>
Node<T> *LL_RB_Tree<T>::rightRotate(Node<T> *h){
    auto x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = Red;
    return x;
}

template<typename T>
Node<T> *LL_RB_Tree<T>::leftRotate(Node<T> *h){
    auto x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = Red;
    return x;
}

template<typename T>
Node<T>* LL_RB_Tree<T>::Insert(Node<T> *h, int key, const T &value)
{
    if (h == nullptr)
        return new Node<T>(key, value);
    if (isRed(h->left) && isRed(h->right))
        colorFilp(h);
    if (key < h->key)
        h->left = Insert(h->left, key, value);
    else if(key > h->key)
        h->right = Insert(h->right, key, value);
    else 
        h->value = value;
    if (!isRed(h->left) && isRed(h->right))
        h = leftRotate(h);
    if (isRed(h->left) &&  h->left != nullptr && isRed(h->left->left))
        h = rightRotate(h);
    return h;
}

int main()
{
    LL_RB_Tree<char> TestRB;
    for (int i = 0; i < 10;++i)
        TestRB.Insert(i, i+65);
    TestRB.inorder_print();
    return 0;
}