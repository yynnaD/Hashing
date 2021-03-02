//
//  QuadHash.cpp
//  proj3
//
//  Created by Danny Gletner on 3/25/20.
//  Copyright © 2020 Danny Gletner. All rights reserved.
//

#ifndef QuadHash_h
#define QuadHash_h
#include <string>

class QuadHash{
public:
    QuadHash(unsigned &dicSize);
    void insert(string &word);
    bool contains(string &word);
    void print();
private:
    unsigned tableSize;
    string *hashTable;
    unsigned nextPrime(unsigned num);
    unsigned isPrime(unsigned num);
    
    unsigned hash(string &word);
    string clean(string word);
    bool containsDash(string word);
    bool splitAndCheck(string word);
    bool containsPossessive(string word);
    string removePossessive(string word);
    const double loadFactor = 0.5;
};

void QuadHash::print(){
    for(unsigned i = 0; i < tableSize; i++)
        cout << hashTable[i] << endl;
}

QuadHash::QuadHash(unsigned &dicSize){
    tableSize = dicSize/loadFactor;
    tableSize = nextPrime(tableSize);
    hashTable = new string[tableSize];
    for(unsigned i = 0; i < tableSize; i++)
        hashTable[i] = "";
}

unsigned QuadHash::hash(string &word){
    unsigned hashVal = 0;
    for( unsigned i=0; i<word.length(); i++)
        hashVal = 37 * hashVal + word[i];
    return hashVal % tableSize;
}

void QuadHash::insert(string &word){
    unsigned hashVal = hash(word);
    if(hashTable[hashVal] == "")
        hashTable[hashVal] = word;
    else {
        for(unsigned i = 1; hashTable[hashVal] != ""; i++){
            hashVal += i*i;
            hashVal = hashVal % tableSize;
        }
        hashTable[hashVal] = word;
    }
}

bool QuadHash::contains(string &word){
    string cleanedWord = "";
    cleanedWord = clean(word);
    
    if(containsDash(cleanedWord))
        return splitAndCheck(cleanedWord);
    if (cleanedWord == "") //word is a number, not misspelled
        return true;
    
    unsigned hashVal = hash(cleanedWord);
    unsigned i = 1; //quadratic value
    
    while(hashTable[hashVal] != cleanedWord && hashTable[hashVal] != ""){
        hashVal += i * i;
        hashVal = hashVal % tableSize;
        i++;
    }
    
    return(hashTable[hashVal] == cleanedWord);
    
}
string QuadHash::clean(string word){
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
    
    //check for possessive ('s)
    if(containsPossessive(word))
        word = removePossessive(word);
    
    return word;
}

bool QuadHash::containsDash(string word){
    for(unsigned i=0; i<word.size(); i++)
        if(word[i] == '-')
            return true;
    return false;
}

bool QuadHash::splitAndCheck(string word){
    string word1 = "", word2 = "";
    unsigned i = 0;
    while(word[i] != '-'){
        word1 += word[i];
        i++;
    }
    while(word[i] == '-'){
        i++;
    }
    for(; i < word.length(); i++)
        word2 += word[i];
    
    if(contains(word1) && contains(word2))
        return true;
    else return false;
}

bool QuadHash::containsPossessive(string word){
    if(word[word.length()-1 == 's'] && word[word.length()-2] == '\''){
        return true;
    }
    else return false;
    
}

string QuadHash::removePossessive(string word){
    string temp = "";
    for(unsigned i = 0; i < word.length()-2; i++)
        temp+= word[i];
    return temp;
}

unsigned QuadHash::nextPrime(unsigned num){
    
    if(num%2 == 0)
        num++;
    for(; isPrime(num); num+=2);
    
    return num;
}

unsigned QuadHash::isPrime(unsigned num){
    
    for (unsigned i = 2; i <= num/2; i++){
        if (num % i == 0)
            return false;
    }
    return true;
}
#endif
