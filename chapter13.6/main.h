#pragma once
#include <string>

class StrVec
{
public:
  StrVec(StrVec&&)noexcept;
  ~StrVec();
  StrVec& operator=(StrVec&&rhs)noexcept;
  
private:
  std::string* element;
  std::string* first_free;
  std::string* cap;
};

///

class Y
{
public:
  Y():a(0){}
  Y(const Y&r)
  {
    a =r.a;
  }

//  Y( const Y&){}
//  Y(Y&&){}
  ~Y(){}
  int a;
};

class hasY
{
public:
  hasY()=default;
  hasY(hasY &&) =default;
  Y m_y;
};



