#include <iostream>
#include <queue>
using namespace std;

template<typename T>
class List
{
public:
    List() {}
    List(T &i):id(i){}
    T id;
    List * next = nullptr;
    void add_front(T i)
    {
        auto node = new List(i);
        auto tmp = this->next;
        this->next = node;
        node->next = tmp;
    }
};

class Graph_L
//direct graph
//naive implmentation
//we can use hash to improve efficency
{
    using size_type = size_t;
public:
    Graph_L(size_type cap):capacity(cap){
        array = new List<int>[capacity];
        occu = new bool[capacity]{};
    }

    void AddEdge(pair<int, int> p)
    {
        for (size_type i = 0; i < capacity; ++i)
        {
            if (occu[i] == false)
            //empty
            {
                array[i].id = p.first;
                array[i].add_front(p.second);
                occu[i] = true;
            }
            else if (array[i].id == p.first)
                array[i].add_front(p.second);
            else 
                continue;
            break;
        }
    }

    void DFS()
    {
        auto visited = new bool[capacity]{};
        for (size_type i = 0; i < capacity; ++i)
            dfs(i, visited);
    }

    void BFS()
    {
        queue<List<int>*> Q;
        Q.push(&array[0]);
        cout << "visit: 0" << endl;
        auto visited = new bool[capacity]{};
        while (!Q.empty())
        {
            cout << "visit: ";
            for (auto i = Q.size(); i > 0; --i)
            {
                auto p = Q.front();
                Q.pop();
                auto node = p->next;
                while (node != nullptr)
                {
                    if (visited[node->id] == false)
                    {
                        cout << node->id << ' ';
                        Q.push(&array[node->id]);
                        visited[node->id] = true;
                    }
                    node = node->next;
                }
            }
            cout << endl;
        }
    }

    void print()
    {
        for (size_type i = 0; i < capacity; ++i)
        {
            auto node = &array[i];
            while (node != nullptr)
            {
                cout << node->id<< ' ';
                node = node->next;
            }
            cout << endl;
        }
    }

private:
    size_type capacity;
    List<int> *array;
    //int for test
    bool *occu;

    template<typename T1, typename T2>
    void dfs(T1 i, T2 visited)
    {
        auto node = &array[i];
        while (node != nullptr)
        {
            if (visited[node->id] == false)
            {   
                visited[node->id] = true;
                dfs(node->id, visited);
                cout << "finish: " << node->id << endl;
            }
            node = node->next;
        }
    }
};


int main()
{
    int V = 5;
    auto myGraph = Graph_L(V);
    myGraph.AddEdge({0, 1});
    myGraph.AddEdge({0, 4});
    myGraph.AddEdge({1, 2});
    myGraph.AddEdge({1, 3});
    myGraph.AddEdge({1, 4});
    myGraph.AddEdge({2, 3});
    myGraph.AddEdge({3, 4});
    myGraph.AddEdge({4, 1});
    
    myGraph.print();
    myGraph.DFS();
    myGraph.BFS();
    return 0;
}