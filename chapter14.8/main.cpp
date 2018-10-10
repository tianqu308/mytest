//
//  main.cpp
//  chapter14.8
//
//  Created by 李勇 on 2018/10/10.
//  Copyright © 2018 liyong. All rights reserved.
//

#include <iostream>
#include <vector>
#include <functional>
class absInt
{
public:
  int operator()(int val)
  {
    return val<0? -val : val;
  }
};

class PrintString
{
public:
  PrintString(std::ostream&o = std::cout, char c = ' '): os(o), sep(c){}
  
  void operator()(const std::string& s)
  {
    os<< s<< sep;
  }
private:
  std::ostream& os;
  char sep;
};

class isShorter
{
public:
  bool operator()(const std::string&a, const std::string&b)
  {
    return a.size() < b.size();
  }
};


class SizeComp
{
public:
  SizeComp(size_t n ):sz(n){}
  
  bool operator()(const std::string& s)
  {
    return s.size() >=sz;
  }
  
private:
  size_t sz;
};


int main(int argc, const char * argv[]) {
  
  int i = -41;
  absInt absobj;
  int j = absobj(i);
  std::cout<< j <<std::endl;
  
  //
  PrintString printstring(std::cout, '\n');
  
  printstring("hello world!");
  printstring("aaa");

  
  //
  std::vector<std::string> vec= {"we","i","are","an", "fuck"};
  std::for_each(vec.begin(), vec.end(), PrintString());
  
  std::vector<int>vec2;
  
  vec2.push_back(283748);
  vec2.push_back(123);
  vec2.push_back(7582);
  
  //
//  std::sort(vec2.begin(), vec2.end(), [](const int& a, const int& b)->bool{
//    return a < b;
//  });
  
  std::sort(vec2.begin(),vec2.end(),std::less< int >() );
  
//  std::for_each(vec.begin(), vec.end(), PrintString());
  
//  std::stable_sort(vec.begin(), vec.end(), [](const std::string& a, const std::string&b)->bool{
//    return a.size()<b.size();
//  });
  
//  std::for_each(vec.begin(), vec.end(), PrintString());
  
  //
  int sz =3;
  auto iter = std::find_if(vec.begin(), vec.begin()+2, [sz](const std::string&s)->bool{
    if(s.size()>=sz)
    {
      return true;
    }
    return false;
  });
  
  std::cout<<std::endl;
  if(iter != vec.begin()+2)
  {
    std::cout<< "---"<<*iter<<std::endl;
  }
  
  iter = std::find_if(vec.begin(), vec.end(), SizeComp(3));
  if(iter != vec.begin()+1)
  {
    std::cout<<"~~~"<<*iter<<std::endl;
  }
  
  //
  std::plus<int> intadd;
  std::negate<int> intnegate;
  int sum = intadd.operator()(10,20);
  int sum2 = intadd(10,20);
  std::cout<<"sum : "<<sum<<std::endl;
  std::cout<<"sum2 : "<<sum2<<std::endl;
  
  int res = intnegate(intadd(10,30));
  
  std::cout<<"res : "<<res<<std::endl;
  return 0;
}
