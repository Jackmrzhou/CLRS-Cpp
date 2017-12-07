#include <iostream>
#include <queue>
using namespace std;

//using C style fashion
//works for graphs with cycles or not;
#define MaxVer 10

struct VNode
{
    int id;
    VNode *next;
};

struct Graph
{
    VNode Adj[MaxVer];
    int V,E;
};

void  BuildGraph(Graph *G)
{
    int n1,n2;
    VNode *p;
    for (int i = 0; i < G->E; ++i)
    {
        cin >> n1>>n2;
        p = &(G->Adj[n1]);
        while( p->next != nullptr)
            p = p->next;
        p->next = new VNode;
        p->next->id = n2;
        p->next->next = nullptr;
    }
}

int* Top_Sort(Graph *G)
{
    auto res = new int[G->V];
    auto indegree = new int[G->V]{0};
    int counter = 0;
    for (int i = 0; i < G->V; ++i)
    {
        auto p = G->Adj[i].next;
        while(p != nullptr)
        {
            indegree[p->id]++;
            p = p->next;
        }
    }
    //initialize indegree

    queue<int> Q;
    for (int i = 0; i < G->V; ++i)
        if (indegree[i] == 0)
            Q.push(i);
    
    while(!Q.empty())
    {
        int tmp = Q.front();
        res[counter++] = tmp;
        Q.pop();
        auto p = G->Adj[tmp].next;
        while(p != nullptr)
        {
            if (--indegree[p->id] == 0)
                Q.push(p->id);
            p = p->next;   
        }
    }
    if (counter != G->V)
        return nullptr;
    return res;
}


int main()
{
    int V,E;
    cin >> V >> E;
    Graph testG;
    for (int i = 0; i < V; ++i)
        testG.Adj[i].next = nullptr;
    testG.V = V, testG.E = E;
    BuildGraph(&testG);
    auto res = Top_Sort(&testG);
    if (res)
        for (int i =0; i < V;++i)
            cout << res[i] << ' ';
    else
        cout << "Have cycle!";
    cout << endl;
    return 0;
}