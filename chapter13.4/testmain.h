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
