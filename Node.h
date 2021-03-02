//
//  Node.cpp
//  proj3
//
//  Created by Danny Gletner on 3/23/20.
//  Copyright © 2020 Danny Gletner. All rights reserved.
//

#ifndef Node_h
#define Node_h
#include <string>

using namespace std;

class Node{
public:
    Node(string object);
    void setObject(string &object);
    void setNextPtr(Node* next);
    bool hasNext();
    string getObject();
    Node* getNextPtr() const;
private:
    string object;
    Node* next;
};

Node::Node(string object){
    this->object = object;
    this->next = NULL;
}

void Node::setObject(string &object){
    this->object = object;
}

string Node::getObject(){
    return object;
}

void Node::setNextPtr(Node* next){
    this->next = next;
}

Node* Node::getNextPtr() const {
    return next;
}
#endif
