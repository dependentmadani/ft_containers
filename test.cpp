// #include <iostream>
// #include <vector>

// using namespace std;

// template<typename type>
// struct MyAlloc: allocator<type> {
//     type * allocate(size_t size) {
//         cout << "Allocation request size => " << size << endl;
//         return new type[size];
//     }
// };

// int main()
// {
//     vector<int, MyAlloc<int> > v1;
//     v1.push_back(10);
//     v1.push_back(20);
//     v1.push_back(30);
//     v1.push_back(40);
//     // v1.insert(v1.begin(), 8, 55);
//     ptrdiff_t i = v1.end() - v1.begin();
//     std::cout << v1.end() - v1.begin() << std::endl;
//     // v1.push_back(50);
//     // v1.push_back(60);
//     // v1.push_back(70);
//     // v1.push_back(80);
//     // v1.push_back(90);

//     // for (auto & var : v1)
//     //     cout << var << endl;

//     return 0;

// }

#include<iostream>
#include <vector>
using namespace std;
 
int main()
{
    vector<int> v;
    v.assign(7, 100);
 
    cout << "Size of first: " << int(v.capacity()) << '\n';
 
    cout << "Elements are\n";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << endl;
    
    v.push_back(15);
    v.push_back(80);
    v.push_back(20);
    cout << "Size of first: " << int(v.capacity()) << '\n';
 
    cout << "Elements are\n";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << endl;
    // modify the elements
    v.assign(3, 8);
 
    cout << "\nModified VectorElements are\n";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << endl;
    return 0;
}