//
//  main.cpp
//  chapter13.6
//
//  Created by 李勇 on 2018/10/4.
//  Copyright © 2018 liyong. All rights reserved.
//
#include "main.h"
#include <iostream>
#include <utility>
#include <vector>



int function()
{
  return 0;
}

//左值表达式的求值结果是一个对象或者函数，然而以常量对象为代表的某些左值实际上不能作为赋值语句的左侧运算符对象。
//总结，当一个值被用作右值时，用的是对象的值；当对象被用作左值时，用的是对象的身份（在内存中的位置）
//一个重要原则是在需要右值的地方可以使用左值来代替，但是不能把右值当成左值使用。
int main(int argc, const char * argv[]) {
  int i = 42;
  int &r =i;
  int &&rr = i*1;
  
  std::cout<<"rr :"<<rr<<std::endl;
  const int &s = i*2;
  std::cout<<"s :" <<s<<std::endl;
  
  int &&ss = std::move(rr);
  std::cout<<"ss :"<<ss<<std::endl;
  
  r = 41;
  std::cout<<"r :"<< r<< i<<std::endl;
  
  r = rr;
  std::cout<<"r :"<<r <<std::endl;
  rr = i;
  std::cout<<"rr :"<<rr<<std::endl;
  std::cout<<"i :"<<i<<std::endl;
  
  ///
  std::vector<int>vec(100);
  
  
  int &&r1 = function();
  std::cout<<"r1 :"<<r1<<std::endl;
  
  int &r2 = vec[0];
  std::cout<<"r2 :"<<r2<<std::endl;
  
  int &r3 = r1;
  std::cout<<"r3 :"<<r3<<std::endl;
  
  int &&r4 = function() * vec[0];
  std::cout<<"r4 :"<<r4<<std::endl;
  
  ////
  Y y1;
  Y y2 = y1;
  hasY hasy1;
  //hasY hasy2 = hasy1;
  hasY hasy3 = std::move(hasy1);
  getchar();
  return 0;
}


StrVec::StrVec(StrVec &&s) noexcept :
  element(s.element),
  first_free(s.first_free),
  cap(s.cap)
{
  s.element = s.first_free = s.cap = nullptr;
}


StrVec::~StrVec() { 
  ;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept { 
  if(this != &rhs)
  {
    //释放已有元素、
    //free
    
    element = rhs.element;
    first_free = rhs.first_free;
    cap = rhs.cap;
    
    rhs.element = rhs.first_free = rhs.cap = nullptr;
  }
  return *this;
}

