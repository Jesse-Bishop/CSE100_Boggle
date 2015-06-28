/* Jesse Bishop
 * jtbishop
 * professor: Kube
 *
 * Andrew Conegliano
 * cs100wbm
 * professor: Bandeira
 */

#include "boggleutil.h"

TST::~TST(){
  clear2(root);
}

void TST::clear2(TrieNode* curr){
  if(curr){
    if(curr->left){clear2(curr->left);}
    if(curr->mid){clear2(curr->mid);}
	 if(curr->mid){clear2(curr->right);}
    delete curr;
    curr = nullptr;
  }
}

 void TST::insertWord(string word){
  TrieNode * curr = root;
  int counter=0;
  for(unsigned int i=0;i<word.size();i++){
    if(root == nullptr){
      root = new TrieNode(word[0]);
      curr = root;
      root->left=nullptr;
      root->right=nullptr;
    }else{				
      if(i==0){
        while(curr){
          if(word[i] > curr->character){
            if(curr->right){
              curr=curr->right;
            }else{
              counter++;
              curr->right=new TrieNode(word[i]);
              curr=curr->right;
	      break;
            }
          }else if(word[i] < curr->character){
            if(curr->left){
              curr=curr->left;
          }else{
            counter++;
            curr->left=new TrieNode(word[i]);
            curr=curr->left;
            break;
          }
        }else if(word[i] == curr->character){
          i++;
          if(i == word.size()) break;
          if(curr->mid){
            curr=curr->mid;
          }else{
            counter++;										
            curr->mid=new TrieNode(word[i]);
            curr=curr->mid;
          }
        }
      }
    }else{		
      if(curr->mid){
        curr=curr->mid;
      }else{
        counter++;
        curr->mid = new TrieNode(word[i]);
        curr = curr->mid;
      }
    }
  }
  }
   curr->end=true;
   if(counter){
     size++;
   }
}

bool TST::findWord(string word, int &letter_counter){
  letter_counter = 0;
  TrieNode *curr = root;

  for(unsigned int i = 0;i < word.size();i++){
    if(curr == nullptr){
      return false;
    }
    if(curr->end && i == (word.size()-1) && curr->character == word[i]){
      letter_counter++;
      return true;
    }
    
    if(word[i] < curr->character){
      curr = curr->left;
      i--;
    }
    else if(word[i] > curr->character){
      curr = curr->right;
      i--;
    }
    else{
      curr = curr->mid;
      letter_counter++;
    }
  }
	return false;
}


