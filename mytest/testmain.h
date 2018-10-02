// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#include <vector>
#include <string>
#include <memory>

class CThrow
{
public:
  CThrow(int a);
  ~CThrow();
  int a = 1;
};

class Strblob
{
public:
  typedef std::vector<std::string>::size_type size_type;
  Strblob();
  Strblob(std::initializer_list<std::string> il);
  ~Strblob();
  void push_back(const std::string& t);

private:
  std::shared_ptr<std::vector<std::string>> data;
};



