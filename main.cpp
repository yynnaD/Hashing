//
//  main.cpp
//  proj3
//
//  Created by Danny Gletner on 3/23/20.
//  Copyright © 2020 Danny Gletner. All rights reserved.
//

#include "main.h"

int main(int argc, const char * argv[]) {
    ifstream inFile;
    string lexicon = "/Users/danny/Desktop/DS Projects/proj3/proj3/dictionaryFile2.txt";
    string checkFile = "/Users/danny/Desktop/DS Projects/proj3/proj3/inputFile2.txt";
    string word;
    unsigned dicSize = 0;
    unsigned chainErrors = 0;
    unsigned quadErrors = 0;
    
    inFile.open(lexicon.c_str());
    if(inFile){
        while(inFile >> word)
            dicSize++;
    }
    
    /*****CHAINING HASH TABLE*****/
    ChainHash hashTable1(dicSize);
    inFile.close();
    
    inFile.open(lexicon.c_str());
    while(inFile >> word){
        hashTable1.insert(word);
    }
    inFile.close();
    
    inFile.open(checkFile.c_str());
    auto startC = chrono::high_resolution_clock().now();
    while(inFile >> word)
        if(!hashTable1.contains(word)){
            chainErrors++;
        }
    auto endC = chrono::high_resolution_clock().now();
    double runtimeC = chrono::duration_cast<std::chrono::nanoseconds>(endC-startC).count();
    inFile.close();
    
    /*****QUADRATIC HASH TABLE*****/
    QuadHash hashTable2(dicSize);
    
    inFile.open(lexicon.c_str());
    while(inFile >> word)
       hashTable2.insert(word);
    inFile.close();
    
    inFile.open(checkFile.c_str());
    auto startQ = chrono::high_resolution_clock().now();
    while(inFile >> word)
        if(!hashTable2.contains(word))
            quadErrors++;
    auto endQ = chrono::high_resolution_clock().now();
    double runtimeQ = chrono::duration_cast<std::chrono::nanoseconds>(endQ-startQ).count();
    inFile.close();
    
    /*********OUTPUT*********/
    
    cout << "Misspellings for chaining: " << chainErrors << endl;
    cout << "Runtime (ns): " << fixed << setprecision(2) << runtimeC << endl << endl;
    
    cout << "Misspellings for quadratic: " << quadErrors << endl;
    cout << "Runtime (ns): " << fixed << setprecision(2) << runtimeQ << endl << endl;
    
    if(runtimeC > runtimeQ)
        cout << "Quadratic was faster by: " << runtimeC - runtimeQ << "ns!" << endl << endl;
    else cout << "Chaining was faster by: " << runtimeQ - runtimeC << "ns!" << endl << endl;
}

