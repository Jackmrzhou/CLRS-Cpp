#include <iostream>
#include <array>
#include <exception>
using namespace std;
class TestEle
{
public:
  TestEle(int k, int d) : key(k), data(d){};
  int key;
  int data;
};
template<size_t length>
class Direct_address_table
{
public:
  Direct_address_table() : data(), keys{false}{};
  void Insert(TestEle &E){
      if (keys[E.key] == true)
          throw(runtime_error("KeyError!"));
      data[E.key] = &E;
      keys[E.key] = true;
  }
  void Delete(TestEle &E){
      if (keys[E.key] == false)
          throw(runtime_error("KeyError!"));
      keys[E.key] = false;
  }
  TestEle &Search(int k){
      return *data[k];
  }
private:
  array<TestEle*, length> data;
  array<bool, length> keys;
};
template<size_t length>
class Open_addressing_table
{
public:
  Open_addressing_table():data(),keys(){
      keys.fill(-1);
  }
  size_t hash(int k, int i){
      return (h(k) + i) % length;
  }
  size_t Hash_Insert(int key);
  size_t search(int key);
  void Delete(int key);

private:
    size_t h(int k){
        return k % length;
    }
  array<int, length> data;
  array<int, length> keys;
};
template<size_t length>
size_t Open_addressing_table<length>::Hash_Insert(int key)
{
    size_t i = 0, j;
    while(i != length)
    {
        j = hash(key, i);
        if (keys[j] == -1)
        {
            data[j] = key;
            keys[j] = 1;
            return j;
        }
        i++;
    }
    throw(overflow_error("Hash Table Overflow!"));
}

template<size_t length>
size_t Open_addressing_table<length>::search(int key)
{
    size_t i = 0, j;
    while(i != length)
    {
        j = hash(key, i);
        if (keys[j] == -1)
            break;            
        if (keys[j] == 1 && data[j] == key)
            return j;
        i++;
    }
    throw(runtime_error("Not Found!"));
}

template<size_t length>
void Open_addressing_table<length>::Delete(int key)
{
    size_t i = 0, j;
    while(i != length)
    {
        j = hash(key, i);
        if (keys[j] == -1)
            break;            
        if (keys[j] == 1 && data[j] == key)
        {
            keys[j] = 0;
            return;
        }
        i++;
    }
    throw(runtime_error("Not Found!"));
}

int main()
{
    /*
    Direct_address_table<10> TestTable;
    for (int i = 0; i < 10;++i)
        TestTable.Insert(*(new TestEle(i, 10 - i)));
    for (int i = 0; i < 10;++i)
        cout << TestTable.Search(i).data << ", ";
    */
    Open_addressing_table<10> TestTable;
    for (int i = 0; i < 10;++i)
        TestTable.Hash_Insert(i);
    for (int i = 0; i < 10;++i)
        cout << TestTable.search(i) << ", ";
    cout << endl;
    return 0;
}