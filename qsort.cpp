#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

int original_partion(int *A, int p, int r)
{
    int x = A[r], k = r;
    while (true)
    {
        while(A[p] <= x)
            p++;
        while (A[k] >= x)
            k--;
        if (p < k)
            swap(A[p], A[k]);
        else
            return k;
    }
}

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
void qsort(int *A, int p, int r)
{
    if (p < r)
    {
        int q = original_partion(A, p, r);
        qsort(A, p, q - 1);
        qsort(A, q+1, r);
    }
}

int main()
{
    int test[5] = {5, 1, 3, 2, 4};
    qsort(test, 0, 4);
    for (int i = 0; i < 5;++i)
        cout << test[i] << ',';
    cout << endl;
}