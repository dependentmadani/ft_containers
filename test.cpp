#include <iostream>
#include <vector>

using namespace std;

template<typename type>
struct MyAlloc: allocator<type> {
    type * allocate(size_t size) {
        cout << "Allocation request size => " << size << endl;
        return new type[size];
    }
};

int main()
{
    vector<int, MyAlloc<int> > v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    // v1.insert(v1.begin(), 8, 55);
    ptrdiff_t i = v1.end() - v1.begin();
    std::cout << v1.end() - v1.begin() << std::endl;
    // v1.push_back(50);
    // v1.push_back(60);
    // v1.push_back(70);
    // v1.push_back(80);
    // v1.push_back(90);

    // for (auto & var : v1)
    //     cout << var << endl;

    return 0;

}