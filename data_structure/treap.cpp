#include <iostream>
using namespace std;

template<typename T>
class Node{
public:
    Node(T d, int p):data(d), priority(p), left(nullptr), right(nullptr){}
    T data;
    int priority;
    Node * left, *right;
};

template<typename _T>
class Treap
{
public:
    void Insert(_T num){
        Insert(root, num);
    }
    void Delete(_T num){
        Delete(root, num);
    }
    void Inorder(){
        inor(root);
    }
    int Max_Height(){
        int height = 0;
        dfs(root, 1, height);
        return height;
    }
private:
    void dfs(Node<_T>* T, int depth, int &height){
        if (T != nullptr){
            height = depth > height? depth:height;
            dfs(T->left, depth + 1, height);
            dfs(T->right, depth+1, height);
        }
    }
    void inor(Node<_T> *T){
        if (T != nullptr){
            inor(T->left);
            cout << T->data<< ' ';
            inor(T->right);
        }
    }
    void Insert(Node<_T> *&T, _T num);
    void Delete(Node<_T> *&T, _T num);
    Node<_T>* left_rotate(Node<_T> *T){
        auto r = T->right;
        T->right = r->left;
        r->left = T;
        return r;
    }
    Node<_T> * right_rotate(Node<_T> *T){
        auto l = T->left;
        T->left = l->right;
        l->right = T;
        return l;
    }
    Node<_T> *root = nullptr;
};
template<typename _T>
void Treap<_T>::Insert(Node<_T> *&T, _T num)
{
    if (T == nullptr)
    {
        T = new Node<_T>(num, rand());
        return;
    }
    else if (num < T->data){
        Insert(T->left, num);
        if (T->priority > T->left->priority)
            T = right_rotate(T);
    }
    else {
        Insert(T->right, num);
        if (T->priority > T->right->priority)
            T = left_rotate(T);
    }
}

template<typename _T>
void Treap<_T>::Delete(Node<_T> *&T, _T num)
{
    if (num == T->data)
    {
        if (T->left==nullptr || T->right == nullptr)
        {
            Node<_T>* t = T;
            if (T->left == nullptr)
                T = T->right;
            else 
                T = T->left;
            delete t;
        }
        else if (T->right->priority < T->left->priority)
        {
            T = left_rotate(T);
            Delete(T->left, num);
        }
        else
        {
            T = right_rotate(T);
            Delete(T->right, num);
        }
    }
    else if (num < T->data)
        Delete(T->left, num);
    else 
        Delete(T->right, num);
}

int main()
{
    auto testTreap = new Treap<int>;
    for (int i = 0; i < 10; ++i)
        testTreap->Insert(i);
    testTreap->Inorder();
    cout << endl;
    //cout << testTreap->Max_Height() << endl;
    testTreap->Delete(5);
    testTreap->Inorder();
    cout << endl;
    return 0;
}