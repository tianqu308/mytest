// ConsoleApplication3.cpp : Defines the entry point for the console application.
//
#ifdef _WIN32
#include "stdafx.h"
#endif
#include <iostream>
#include "testmain.h"
#include <map>
#include <memory>

using namespace std;
CThrow::CThrow(int a)
{
  if (a < 0)
  {
    throw "a < 0";
  }
  std::cout << a << std::endl;
}

CThrow::~CThrow()
{

}

Strblob::Strblob()
{

}

Strblob::Strblob(std::initializer_list<std::string> il)
{
  data = std::make_shared<std::vector<std::string>>(il);
}

Strblob::~Strblob()
{
  std::cout << "~Strblob" << std::endl;
}
void Strblob::push_back(const std::string& t)
{
  data->push_back(t);
}

typedef std::map <int, std::string >MapIdentity;
typedef std::map <int, std::string>::iterator MapIdentityIterator;

void TEST_shared_ptr()
{
  // test member data shared_ptr
  Strblob b1({ "a", "b", "c" });
  {
    Strblob b2({ "1","2","3" });
    b1 = b2;
  }
  b1.push_back("4");
}

void TEST_map()
{
  // testmap
  MapIdentity mapID = { { 1, "id1" },{ 2, "id2" },{ 3, "id3" },{ 4, "id4" } };

  std::pair<int, std::string> currID;

  currID = std::make_pair(3, "id3");

  auto iter = mapID.find(currID.first);

  if (iter == mapID.end())
  {
    std::cout << "currID worng" << std::endl;
  }
  else
  {
    if (++iter == mapID.end())
    {
      std::cout << "last ID" << std::endl;
    }
    else
    {
      currID = *iter;
      std::cout << "curr id : " << currID.first << std::endl;
      std::cout << "curr string : " << currID.second << std::endl;
    }
  }
}

void TEST_throw()
{
  // test throw if or not break
  try
  {
    CThrow* a2 = new (std::nothrow)CThrow(-1);
    if(!a2)
    {
        std::cout<< "Cthrow construct failed"<<std::endl;
    }
  }
  catch (const char*)
  {
    std::cout << "exception" << std::endl;
  }
}

std::unique_ptr<int> Clone(int p)
{
  return std::unique_ptr<int>(new int(p));
}

void TEST_unique_ptr()
{
  std::unique_ptr<std::string> p1(new std::string("TEST_unique_ptr"));
  std::unique_ptr<std::string>p2(p1.release());
  std::unique_ptr<std::string>p3(new std::string("aaa"));
  p2.reset(p3.release());

  //
  std::unique_ptr<int> p4 = Clone(4);

}

bool IsValidWeakptr(std::weak_ptr<int>&wp)
{
  if (std::shared_ptr<int>sp = wp.lock())
  {
    return true;
  }
  return false;
}

void TEST_weak_ptr()
{
  std::shared_ptr<int>p1 = std::make_shared<int>(51);


  std::weak_ptr<int>wp0 = p1;
  std::weak_ptr<int>wp1(p1);

  if (IsValidWeakptr(wp0))
  {
    std::cout << "valid" << std::endl;
  }
  else
  {
    std::cout << "Invalid" << std::endl;
  }
}

void TEST_new_array()
{
  std::string *ps = new std::string[3]{ "0","1","2" };

  delete[] ps;
}

void TEST_unique_ptr_array()
{
  std::unique_ptr<int[]>up(new int[10]{ 1 });

  for (int i = 1; i != 10; ++i)
  {
    up[i] = i;
  }

  for (size_t i = 0; i != 10; ++i)
  {
    std::cout << up[i] << std::endl;
  }
  up.release();

  std::cout << "===" << std::endl;

  std::shared_ptr<int> sp(new int[10]{ 1,4 }, [](int*p) {delete[]p; });


  for (size_t i = 0; i < 10; ++i)
  {
    std::cout << *(sp.get() + i) << std::endl;
  }
}

void TEST_allocator()
{
  std::allocator<std::string> alloc;
  size_t n = 10;
  size_t i = 0;
  std::allocator<std::string>::pointer p = alloc.allocate(n);

  auto q = p;
  for (i = 0; i < n; ++i)
  {
    alloc.construct(q++, i, '$');
  }

  auto m = p;
  for (size_t j = 0; j < 10; ++j, ++m)
  {

    std::cout << *m << std::endl;
    alloc.destroy(m);
  }


  auto s = p;
  for (size_t j = 0; j < 10; ++j, ++s)
  {

    std::cout << *s << std::endl;
  }


  alloc.deallocate(p, n);

}

struct sDecltype { double x; };

const sDecltype* a;
decltype(a->x) y;
decltype(a->x) z = y;

template<typename T, typename U>
auto add(T a, U b)
{
  return a*b;
}


void TEST_decltype()
{
  int i = 33;
  decltype(i) j = i * 2;

  std::cout << "i = " << i << ", " << "j = " << j << std::endl;

  auto f = [](int a, int b)->int
  {
    return a*b;

  };

  decltype(f) g = f;


  i = f(2, 2);
  j = g(3, 3);

  std::cout << "i = " << i << ", " << "j = " << j << std::endl;

}

class Foo
{
public:
  Foo();
  
  // 拷贝构造函数 参数是一个const 类型的引用
  Foo(const Foo& );
  
  int data[5] = {0,1,2,3,4};
};

Foo::Foo()
{
  
  data[0] = 0;
  data[1] = 1;
  data[2] = 2;
  data[3] = 3;
  data[4] = 4;
}

Foo::Foo(const Foo&)
{

}

class HasPtr
{
public:
  HasPtr();
  HasPtr(const std::string&s = std::string());
  HasPtr( const HasPtr& ptr);
  HasPtr& operator=(const HasPtr& rhs);
  std::string* GetPtr(){return ps;}
  ~HasPtr();
private:
  std::string* ps = nullptr;
  int i =-1;
};

HasPtr::HasPtr()
{
  
}

HasPtr::HasPtr(const std::string&s)
{
  ps = new std::string(s);
  i = 0;
}

HasPtr::HasPtr( const HasPtr& ptr)
{
  ps = new std::string(*ptr.ps);
  i = ptr.i;
}

HasPtr::~HasPtr()
{
  if (ps) {
    delete ps;
  }
}

HasPtr& HasPtr::operator=(const HasPtr&rhs)
{
  std::string* newps = new std::string(*rhs.ps);
  if(ps)
  {
    delete ps;
  }
  ps = newps;
  i = rhs.i;
  return *this;
}

HasPtr test_Hasptr(HasPtr hp)
{
  HasPtr ret = hp;
  return ret;
}

class HasPtrEx
{
public:
  HasPtrEx(const std::string&s= std::string()):
  ps(new std::string(s)),i(0), use(new std::size_t(1)){}
  
  HasPtrEx(const HasPtrEx&p):
  ps(p.ps), i(p.i), use(p.use){++*use;}
  
  HasPtrEx& operator=(const HasPtrEx& rhs);
private:
  std::string* ps;
  int i;
  std::size_t* use;
};

HasPtrEx& HasPtrEx::operator=(const HasPtrEx&rhs)
{
  ++*rhs.use;
  if(--*use == 0)
  {
    delete ps;
    delete use;
  }
  
  ps = rhs.ps;
  i = rhs.i;
  use = rhs.use;
  return *this;
}

void TEST_copy_constuctor()
{
  Foo a;
  Foo b(a);
  
  std::for_each(std::begin(b.data), std::end(b.data), [](int item){
    std::cout<< item<<std::endl;
  });
  
  {
    HasPtr hasPtr("hello world");
    test_Hasptr(hasPtr);
    std::string* p = hasPtr.GetPtr();
    
    std::cout<< *(p)<<std::endl;
  }
}

int main()
{
  //
  TEST_shared_ptr();

  //
  TEST_map();

  //
  TEST_throw();

  //
  TEST_unique_ptr();

  //
  TEST_weak_ptr();

  //
  TEST_new_array();

  //
  TEST_unique_ptr_array();

  //
  TEST_allocator();

  //
  TEST_decltype();

  //
  TEST_copy_constuctor();
  
  getchar();
  return 0;
}

