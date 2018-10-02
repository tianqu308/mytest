//
//  main.cpp
//  chapter13.4
//
//  Created by 李勇 on 2018/10/2.
//  Copyright © 2018 liyong. All rights reserved.
//
#include "testmain.h"
#include <iostream>




int main(int argc, const char * argv[]) {
  Folder folder1;
  Folder folder2;
  
  Message msg1("msg1");

  
  msg1.save(folder1);
  msg1.save(folder2);
  
}

void swap(Message& lhs, Message& rhs)
{
  using std::swap;
  
  for(auto f : lhs.folders)
  {
    f->removeMsg(&lhs);
  }
  
  for(auto f : rhs.folders)
  {
    f->removeMsg(&rhs);
  }
  
  swap(lhs.folders, rhs.folders);
  swap(lhs.content, rhs.content);
  
  for(auto f : lhs.folders)
  {
    f->addMsg(&lhs);
  }
  
  for (auto f : rhs.folders) {
    f->addMsg(&rhs);
  }
}

Message::~Message() {
  remove_from_folder();
}

Message::Message(const std::string &str) {
  content = str;
}

void Message::remove(Folder &f) {
  folders.erase(&f);
  f.removeMsg(this);
}


void Message::save(Folder &f) {
  folders.insert(&f);
  f.addMsg(this);
}


Message &Message::operator=(const Message &rhs) {
  remove_from_folder();
  content = rhs.content;
  folders = rhs.folders;
  add_to_folder(rhs);
  return *this;
}


Message::Message(const Message &msg):content(msg.content),folders(msg.folders) {
  add_to_folder(msg);
}

void Message::remove_from_folder() { 
  for(auto f : folders)
  {
    f->removeMsg(this);
  }
}


void Message::add_to_folder(const Message &m) {
  for(auto f : m.folders)
  {
    f->addMsg(this);
  }
}

/////

void Folder::removeMsg(Message *msg) { 
  messages.erase(msg);
}


void Folder::addMsg(Message *msg) {
  messages.insert(msg);
}
