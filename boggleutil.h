#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


/* Jesse Bishop
 * jtbishop
 * professor: Kube
 *
 * Andrew Conegliano
 * cs100wbm
 * professor: Bandeira
 */

using namespace std;

class TrieNode{
public:
  char character; //char to add to tree
  TrieNode* left; //pointer to left child
  TrieNode* mid;  //pointer to middle child
  TrieNode* right;//pointer to right child
  bool end;       //bit that ends sequence	
  
  //TrieNode constructor
  TrieNode(char character,
    TrieNode* left = nullptr,
    TrieNode* mid = nullptr,
    TrieNode* right = nullptr,
    bool end = false)
    :character(character), left(left),mid(mid),right(right), end(end){ }
};

class TST{
public:
  TrieNode* root;  //Define the root of the TST
  unsigned int size = 0;
public:

  /*TST constructor*/
  explicit TST(): root(NULL){ }

  /*Destructor for the TST*/
  ~TST();

  /*Function to insert a new word in a TST*/
  void insertWord(string word);

  /*Function to find a word in the tree*/
  bool findWord(string word, int &letter_counter);

  /*Clear function for TST*/
  //void clear() { clear2(root);}
  void clear2(TrieNode* curr);

};



#endif //BOGGLEUTIL_H
