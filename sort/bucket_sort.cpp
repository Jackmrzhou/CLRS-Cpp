#include <iostream>
#include <list>
using namespace std;
void Bucket_Sort(float *A, int n)
{
    list<float> B[10]{};
    for (int i = 0; i < n;++i)
        B[static_cast<int>(n * A[i])].push_back(A[i]);
    for(auto &l : B)
        l.sort();
    int i = 0;
    while (i < n)
        for (auto &l : B)
            while(!l.empty()){
                A[i++] = l.front();
                l.pop_front();
            }
}
int main()
{
    float test[10]{.78, .17, .39, .26, .72, .94, .21, .12, .23, .68};
    Bucket_Sort(test, 10);
    for (auto i:test)
        cout << i << ", ";
    cout << endl;
    return 0;
}