#include <iostream>
using namespace std;
void Counting_Sort(int *A,int k, int n)
{
    int B[k+1]{};
    for (int i = 0; i < n;++i)
        B[A[i]]++;
    int i = 0, j = 0;
    while(i <= k)
    {
        while (B[i]-- > 0)
            A[j++] = i;
        ++i;
    }
}
int main()
{
    int test[8] = {2, 5, 3, 0, 2, 3, 0, 3};
    Counting_Sort(test, 5, 8);
    for (auto i:test)
        cout << i << ',';
    cout << endl;
    return 0;
}