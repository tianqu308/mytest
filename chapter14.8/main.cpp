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
#include <map>
#include <string>

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

void TEST_function_object()
{
  std::plus<int> intadd;
  std::minus<int> intminus;
  std::multiplies<int> intmultiplies;
  std::divides<int> intdivides;
  std::modulus<int> intmodulus;
  std::negate<int> intnegate;
  
  int sum = intadd.operator()(10,20);
  int sum2 = intadd(10,20);
  std::cout<<"sum : "<<sum<<std::endl;
  std::cout<<"sum2 : "<<sum2<<std::endl;
  
  int minus = intminus(10,2);
  std::cout<<"minus : "<<minus<<std::endl;
  
  int multiplies = intmultiplies(10,4);
  std::cout<<"multiplies : "<<multiplies<<std::endl;
  
  int divides = intdivides(5,3);
  std::cout<<"divides : "<<divides<<std::endl;
  
  int modulus = intmodulus(5,3);
  std::cout<<"modulus : "<<modulus<<std::endl;
  
  int negate = intnegate(intadd(10,30));
  std::cout<<"negate : "<<negate<<std::endl;

  //
  std::equal_to<int> intequal_to;
  bool bequal = intequal_to(5,5);
  std::cout<<"bequal : "<<bequal<<std::endl;
  
  std::not_equal_to<int> intnotequalto;
  bool bnotequal = intnotequalto(5,4);
  std::cout<<"bnotequal : "<<bnotequal<<std::endl;
  
  std::less<int> intless;
  bool bless1 = intless(5,4);
  std::cout<<"bless (5,4) : "<<bless1<<std::endl;
  bool bless2 = intless(4,5);
  std::cout<<"bless(4,5) : "<<bless2<<std::endl;
  
  std::greater<int> intgreater;
  bool bgreater = intgreater(5,4);
  std::cout<<"bgreater(5,4) : "<<bgreater<<std::endl;
  
  //
  std::logical_and<int> intlogical_and;
  std::logical_or<int> intlogical_or;
  std::logical_not<int> intlogical_not;
  int logicaland = intlogical_and(2,0);
  int logicalor = intlogical_or(2,0);
  bool logicalnot = intlogical_not(0);
  std::cout<<"logical and : "<<logicaland<<std::endl;
  std::cout<<"logical or : "<<logicalor<<std::endl;
  std::cout<<"logical not : "<<logicalnot<<std::endl;
}

int add(int a, int b)
{
  return a+b;
}

auto mod = [](int a, int b){
  return a%b;
};

struct divide
{
public:
  int operator()(int denominator, int divisor)
  {
    return denominator/divisor;
  }
};

void TEST_function()
{
  std::map<std::string, int(*)(int,int)> binops;
  
  binops.insert(std::make_pair("+", add));
  binops.insert({"%", mod});
//  binops.insert({"/", divide()});
  
  std::map<std::string, std::function<int(int,int)>>binops2;
  typedef std::function<int(int,int)> functionInt;
  functionInt f1= add;
  functionInt f2 = divide();
  functionInt f3 = mod;
  functionInt f4 = std::minus<int>();
  functionInt f5 = [](int a, int b )->int{
    return a*b;
  };
  
  binops2.insert({"+", f1});
  binops2.insert({"/", f2});
  binops2.insert({"%", f3});
  binops2.insert({"-", f4});
  binops2.insert({"*", f5});
  
  std::cout << "3 +5 : " <<binops2["+"](3,5) << std::endl;
  std::cout << "3/5 : " <<binops2["/"](3,5) << std::endl;
  std::cout << "50 %4 :" <<binops2["%"](50, 4)  << std::endl;
  std::cout << "43 - 22 : " <<binops2["-"](43, 22)  << std::endl;
  std::cout << "33 * 11 : " << binops2["*"](33,11) << std::endl;
  
}

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
  TEST_function_object();
  
  TEST_function();
  return 0;
}
