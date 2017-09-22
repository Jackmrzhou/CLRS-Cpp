#include <iostream>
#include <array>
using namespace std;
array<int,2> Brute_Force(array<int,17> &data)
{
    int max = 0;
    array<int, 2> res;
    for (unsigned int i = 0; i != data.size();++i)
        for (auto j = i; j != data.size();++j)
            if(data[j]-data[i] > max)
                res[0] = i, res[1] = j, max = data[j] - data[i];
    return res;
}
array<int, 3> Find_Max_Cross(array<int, 17> &data, int low, int mid, int high)
{
    int left_max, right_max, sum = 0, left_sum, right_sum;
    for (int i = mid; i >= low;--i)
    {
        sum += data[i];
        if (i == mid || sum > left_sum)
            left_sum = sum, left_max = i;
    }
    sum = 0;
    for (int i = mid + 1; i <= high;++i)
    {
        sum += data[i];
        if (i == mid+1 || sum > right_sum)
            right_sum = sum, right_max = i;
    }
    return array<int, 3>{left_max, right_max, left_sum + right_sum};
}
array<int, 3> Find_Max_Subarray(int low, int high, array<int, 17> &data)
{
    if (low == high)
        return array<int, 3>{low, high, data[low]};
    int mid = (low + high) / 2;
    auto l = Find_Max_Subarray(low, mid, data);
    auto r = Find_Max_Subarray(mid + 1, high, data);
    auto c = Find_Max_Cross(data, low, mid, high);
    if (l[2] >= r[2] && l[2] >= c[2])
        return l;
    else if (r[2] >= l[2] && r[2] >= c[2])
        return r;
    else return c;
}
int main()
{
    array<int, 17> Data{100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97};
    auto res = Brute_Force(Data);
    cout << res[0] << ',' << res[1] << endl;
    array<int, 17> data;
    for (unsigned int i = 0; i != Data.size() - 1;++i)
        data[i+1] = Data[i + 1] - Data[i];
    //only after first day can exsist a increment
    auto ans = Find_Max_Subarray(1, 16, data);
    //the start day should be asn[0] - 1
    cout << ans[0] << ',' << ans[1] << endl;
    return 0;
}