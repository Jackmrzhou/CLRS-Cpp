#include <iostream>
#include <random>
#include <algorithm>
using namespace std;
int partition(int *A, int p, int r)
{
    default_random_engine generator;
    uniform_int_distribution<int> distribution(p,r);
    int rand_num = distribution(generator); 
    swap(A[rand_num], A[r]);
    int x = A[r], i = p - 1;
    for (int j = p; j < r;++j)
    {
        if (A[j] <= x)
        {
            ++i;
            swap(A[j], A[i]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}
//same partion in quick sort

int Selection(int *A, int p, int r, int i)
//select a number in its i th position
{
    if (p == r)
        return A[p];
    auto q = partition(A, p, r);
    int k = q - p + 1;
    if (k == i)
        return A[q];
    else if (i < k)
        return Selection(A, p, q - 1, i);
    else
        return Selection(A, q+1, r, i - k);
}

int main()
{
    int test[5] = {1, 5, 3, 2, 4};
    auto res = Selection(test, 0, 4, 3);
    cout << res << endl;
    return 0;
}