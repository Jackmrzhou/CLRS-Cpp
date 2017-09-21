#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
using namespace std;
bool func(pair<int, int> i,pair <int, int> j)
{
    return i.second < j.second;
}
void Radix_Sort(int *A, int n)
{
    pair<int, int> d[n];
    int max_len = 0;
    for (int j = 0; j < n;++j)
    {
        auto i = A[j];
        int count = 0;
        while(i)
        {
            count++;
            i /= 10;
        }
        max_len = count > max_len ? count : max_len;
    }
    for (int i = 0; i < max_len;++i)
    {
        for (int j = 0; j < n;++j)
            d[j] = make_pair(A[j], (A[j] / (int)pow(10, i)) % 10);
        stable_sort(d, d+n, func);
        for (int j = 0; j < n;++j)
            A[j] = d[j].first;
    }
}

int main()
{
    int test[5] = {123, 12, 4555, 456, 234};
    Radix_Sort(test, 5);
    for (auto i:test)
        cout << i << ',';
    cout << endl;
    return 0;
}