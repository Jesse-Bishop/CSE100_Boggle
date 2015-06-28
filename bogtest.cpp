#include "iboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>

int main (int argc, char* argv[]) {

  IBogglePlayer * p = new BogglePlayer();
  vector<string> lex;
  string wordA("rally");
  string wordX("andrews");
  lex.push_back(wordA);
  lex.push_back("zebra");
  string row0[] = {"d","c","A","X","m"};
  string row1[] = {"n","T","y","l","R"};
 string row2[] = {"I","c","V","Q","A"};
 string row3[] = {"O","i","y","l","l"};
 string row4[] = {"P","c","A","q","c"};


  string* board[] = {row0,row1,row2,row3,row4};
  set<string> words;
  vector<int> locations;
  p->buildLexicon(lex);

  p->setBoard(5,5,board);

  if(p->isInLexicon(wordA)) {
    std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
    return -1;
  }
  if(!p->isInLexicon(wordA)) {
    std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
    return -1;
  }

  if(p->isOnBoard(wordA).size() > 0) {
    std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
    return -1;
  }

  locations.clear();
  locations = p->isOnBoard(wordA);
  if(locations.size() != 1 || locations[0] != 3) {
    std::cerr << "Apparent problem with isOnBoard #2." << std::endl;
    //return -1;
  }
  
  
  if(!p->getAllValidWords(0,&words)) {
    std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
    //return -1;
  };
  if(words.size() != 1 || words.count(wordA) != 1) {
    std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
    //return -1;
  }

  delete p;
  return 0;

}
