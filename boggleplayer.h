#include "iboggleplayer.h"
#include "boggleutil.h"
#include <algorithm>
#include <string.h>

/* Jesse Bishop
 * jtbishop
 * professor: Kube
 *
 * Andrew Conegliano
cs100wbm
 * 
 * professor: Bandeira
 */

class BogglePlayer : public IBogglePlayer{
public:
  BogglePlayer() {
    head = new TST;
  }

  ~BogglePlayer();
  virtual void buildLexicon(const vector<string>& word_list);
  virtual void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
  virtual bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
  virtual bool isInLexicon(const string& word_to_check);
  virtual vector<int> isOnBoard(const string& word_to_check);
  virtual void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);
  void neighbor_search(int r, int c, char *visited, int max_iter, vector<int> &string_indices, int stringindex, string word_to_check);
  void neighbor_search2(int r, int c, char *visited, set<string>* words, string previous_word, bool &return_value, unsigned int minimum_word_length);
public:
  TST *head;
  bool LexiconCreated = 0, boardCreated = 0;
  string **boggleboard;
  unsigned int row,col;
  int letter_counter = 0;
  bool found = false;

};
