#include <iostream>

template <int N> struct A
{
  int a[N];
  int b[N];
};

int main() {
    std::cout<<"Hello, world"<<'\n';
    auto arr = A<2> {1, 2, 3, 4};
    std::cout<<arr.b[0]<<' '<<arr.a[1]<<'\n';
}