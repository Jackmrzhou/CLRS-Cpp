#include <iostream>
#include <initializer_list>
#include <array>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

template<int size>
class MinHeap_partial
{
    using DataType = array<pair<int, int>, size + 1>;
    public:
        MinHeap_partial():data(), __size(0){}

        void push(int index, int weight)
        {
            data[++__size] = make_pair(index, weight);
            percolate_up(__size);
        }

        int Extract_min()
        {
            swap(data[1], data[__size]);
            __size--;
            percolate_down(1);
            return data[__size + 1].first;
        }

        bool empty()
        {
            return __size == 0;
        }

    private:
        DataType data;
        int __size;

        void percolate_up(int index)
        {
            while(index != 1 && data[index].second < data[index/2].second)
            {
                swap(data[index], data[index/2]);
                index /= 2;
            }   
        }

        void percolate_down(int index)
        {
            int left = index * 2, right = index * 2 + 1;
            auto min =index;
            if (left <= __size && data[left].second < data[min].second)
                min = left;
            if (right <= __size && data[right].second < data[min].second)
                min = right;
            if (min != index)
            {
                swap(data[min], data[index]);
                percolate_down(min);
            }
        }
};

template<int v>
class DWGraph
{
    using DataType = array<list<pair<int, int>>, v>;
    public:
        DWGraph()=default;
        void AddEdge(pair<int, int> p, int weight)
        {
            adj[p.first].push_back({p.second, weight});
        }

        array<int, v> dijkstra(int S)
        //complexity O(VlgV + E)
        {
            array<int, v> dist;
            dist.fill(-1);
            MinHeap_partial<v> Q;
            dist[S] = 0;
            Q.push(S, 0);
            while ( !Q.empty())
            {
                auto u = Q.Extract_min();
                for (auto & it : adj[u])
                {
                    if (dist[it.first] == -1)
                        Q.push(it.first, it.second);
                    if (dist[it.first] == -1 || dist[it.first] > dist[u] + it.second)
                        dist[it.first] = dist[u] + it.second;
                }
            }
            return dist;
        }

        bool bellman_ford(int S, array<int, v> &dist)
        //complexity O(V*E)
        {
            dist.fill(-1);
            dist[S] = 0;
            for (int i = 0; i < v -1; ++i)
                for (int j = 0; j < v; ++j)
                    for (auto &it : adj[j])
                        if ((dist[it.first] == -1 ||dist[it.first] > dist[j] + it.second)
                         && dist[j] != -1)
                            dist[it.first] = dist[j] + it.second;

            for (int j = 0; j < v; ++j)
                for (auto &it : adj[j])
                    if (dist[j] != -1 && dist[it.first] > dist[j] + it.second)
                    //mind the j may be unreachable
                        return false;
            return true;
        }

    private:
        DataType adj;
};

int main()
{
    auto testG = DWGraph<8>();
    int n,m,w;
    for (int i = 0; i < 10; ++i)
    {
        cin >> n>>m >> w;
        testG.AddEdge({n,m}, w);
    }
    auto dist = testG.dijkstra(3);
    for (auto d:dist)
        cout << d << ' ';
    cout << endl;

    if (testG.bellman_ford(3, dist))
    {
        for (auto d:dist)
            cout << d << ' ';
        cout << endl;
    }
    return 0;
}