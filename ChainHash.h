//
//  ChainHash.cpp
//  proj3
//
//  Created by Danny Gletner on 3/23/20.
//  Copyright © 2020 Danny Gletner. All rights reserved.
//
#ifndef ChainHash_h
#define ChainHash_h
#include <stdio.h>
#include "Node.h"

class ChainHash{
public:
    ChainHash(unsigned &dicSize);
    void insert(string &word);
    bool contains(string &word);
private:
    unsigned tableSize;
    unsigned hash(string &word);
    string clean(string word);
    bool containsDash(string word);
    bool splitAndCheck(string word);
    bool containsPossessive(string word);
    string removePossessive(string word);
    Node** hashTable;
};

ChainHash::ChainHash(unsigned &dicSize){
    tableSize = dicSize;
    hashTable = new Node*[dicSize];
    for(unsigned i = 0; i < tableSize; i++){
        hashTable[i] = NULL;
    }
}

void ChainHash::insert(string &word){
    unsigned hashVal = hash(word);
    Node* newNode = new Node(word);
    
    if(hashTable[hashVal] == NULL)
        hashTable[hashVal] = newNode;
    else{
        Node *temp = hashTable[hashVal];
        while (temp->getNextPtr() != NULL) //iterates to end
            temp = temp->getNextPtr();
        temp->setNextPtr(newNode);
    }
}

bool ChainHash::contains(string &word){
    string cleanedWord = "";
    cleanedWord = clean(word);
    if(containsDash(cleanedWord))
        return splitAndCheck(cleanedWord);
    if (cleanedWord == "") //word is a number, not misspelled
        return true;
    
    unsigned hashVal = hash(cleanedWord);
    
    if (hashTable[hashVal] == NULL )
    {
        return false;
    }
    else if (hashTable[hashVal]->getObject() == cleanedWord)
    {
        return true;
    }
    else
    {
        Node *current = hashTable[hashVal];
        while (current->getNextPtr() != NULL)//iterates to end
        {
            current = current->getNextPtr();
            if (current->getObject() == cleanedWord)
                return true;
        }
        return false;
    }
}

unsigned ChainHash::hash(string &word){
    unsigned hashVal = 0;
    for( unsigned i=0; i<word.length(); i++)
        hashVal = 37 * hashVal + word[i];
    return hashVal % tableSize;
}

string ChainHash::clean(string word){
    //lowercase
    for(unsigned i = 0; i < word.size(); i++)
        word[i] = tolower(word[i]);
    
    //remove punc from back
     while(!isalpha(word[word.length()-1]))
        if(!word.empty())
            word = word.erase(word.length()-1);
        else return word;
   
    //remove punc from front
    while(!isalpha(word[0]))
        if(!word.empty())
            word.erase(word.begin());
        else return word;
    
    //check for possessive punc
    if(containsPossessive(word))
        word = removePossessive(word);
    
    return word;
}

bool ChainHash::containsDash(string word){
    for(unsigned i=0; i<word.size(); i++)
        if(word[i] == '-')
            return true;
    return false;
}

bool ChainHash::splitAndCheck(string word){
    string word1 = "", word2 = "";
    unsigned i = 0;
    while(word[i] != '-'){
        word1 += word[i];
        i++;
    }
    while(word[i] == '-'){
        i++;
    }
    for(i; i < word.length(); i++)
        word2 += word[i];
    
    if(contains(word1) && contains(word2))
        return true;
    else return false;
}

bool ChainHash::containsPossessive(string word){
    if(word[word.length()-1 == 's'] && word[word.length()-2] == '\''){
        return true;
    }
    else return false;
    
}
string ChainHash::removePossessive(string word){
    string temp = "";
    for(unsigned i = 0; i < word.length()-2; i++)
        temp+= word[i];
    return temp;
}

#endif
