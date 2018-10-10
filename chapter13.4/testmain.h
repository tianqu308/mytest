#pragma once

#include <set>
#include <string>
class Folder;
class Message
{
  friend class Folder;
  friend void swap(Message& lhs, Message& rhs);
public:
  explicit Message(const std::string& str = std::string());
  Message(const Message& msg);
  Message& operator=(const Message&rhs);
  ~Message();
  
  //
  void save(Folder& folder);
  void remove(Folder& folder);
private:
  std::string content;
  std::set<Folder *> folders;
  
  void add_to_folder(const Message&);
  void remove_from_folder();
};

class Folder
{
public:
  Folder(){}
  ~Folder(){}
  
  void addMsg(Message* msg);
  void removeMsg(Message* msg);
private:
  std::set<Message*> messages;
};


class StrVec
{
public:
  StrVec():element(nullptr), first_free(nullptr), cap(nullptr){}
  StrVec(const StrVec&);
  StrVec& operator=(const StrVec&);
  
  void push_back(const std::string&);
  size_t size()const{return first_free - element;}
  size_t capacity()const {return cap- element;}
  std::string* begin()const {return element;};
  std::string* end()const{return first_free;}
  ~StrVec();
  
private:
  static std::allocator<std::string> alloc;
  
  void check_n_alloc()
  {
    if(size() == capacity())
    {
      reallocate();
    }
  }
  
  std::pair<std::string*, std::string*>alloc_n_copy(const std::string*, const std::string*);
  
  void free();
  void reallocate();
  
  
  std::string* element = nullptr;
  std::string* first_free = nullptr;
  std::string* cap = nullptr;
};
