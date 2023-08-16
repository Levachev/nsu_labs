#include <iostream>
//#include<stdlib.h>
#include"BigInt.hpp"
int main()
{
  std::string firstStr,secondstr;
  std::cin>>firstStr>>secondstr;
  BigInt a(firstStr);
  BigInt b(secondstr);
  std::cout<<"a - "<<a<<std::endl;
  std::cout<<"b - "<<b<<std::endl;
  BigInt c=a/b;
  std::cout<<"c - "<<c<<std::endl;
    return 0;
}
