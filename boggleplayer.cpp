#include "boggleplayer.h"

/* Jesse Bishop
 * jtbishop@ucsd.edu
 * professor: Kube
 *
 * Andrew Conegliano
 * cs100wbm
 * aconegli@eng.ucsd.edu
 * 
 * professor: Bandeira
 */


BogglePlayer::~BogglePlayer() {
  //Delete the TST
  delete head;
  
  //Delete each element of the board
  if(boardCreated){
    for(int i=0;i<row;i++)
      delete[] boggleboard[i];

  //Delete the boggle board
  delete[] boggleboard;
}

}


/* This function takes as argument a vector containing the words specifying the official 
 * lexicon to be used for the game. Each word in the set will be a string consisting of lowercase 
 * letters a-z only. This function must load the words into an efficient data structure that will be 
 * used internally as needed by the BogglePlayer.
 */

void BogglePlayer::buildLexicon(const vector<string>& word_list){
  std::vector<string>copy_of_word_list;
  for(std::vector<string>::const_iterator i = word_list.begin();i != word_list.end();i++){
    copy_of_word_list.push_back(*i);
  }

  std::random_shuffle ( copy_of_word_list.begin(), copy_of_word_list.end() );
  for(std::vector<string>::iterator i = copy_of_word_list.begin();i != copy_of_word_list.end();i++){
    head->insertWord(*i);
   }

   LexiconCreated = true;
}

/* Function that sets the dimensions of the board as well as setting
 * the appropiate pieces based on array
 * PARAMETERS: integer of rows and collumns and a diceArray
 */

void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray){
  boggleboard = new string*[rows];
  row=rows;
  col=cols;
	
  for(unsigned int i=0;i<rows;i++){
    boggleboard[i] = new string[cols];
  }

  //Index through each row and collumn to set the board
  for(unsigned int i=0;i<rows;i++){
    for(unsigned int j=0;j<cols;j++){
      boggleboard[i][j] = diceArray[i][j];
      for(unsigned int k=0;k<diceArray[i][j].size();k++){
        boggleboard[i][j][k]=tolower(boggleboard[i][j][k]);
      }
    }
  }
  boardCreated = true;
}

/* This function takes two arguments: an int specifying a minimum word length, and a 
 * pointer to a set of strings. It returns false if either setBoard() or buildLexicon() 
 * have not yet been called for this BogglePlayer. If they have both been called, it will return true, 
 * after filling the set with all the words that 
 * (1) are of at least the given minimum length, 
 * (2) are in the lexicon specified by the most recent call to buildLexicon(), and 
 * (3) can be found by following an acyclic simple path on the board specified by the most 
 * recent call to setBoard().
 */

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words){
if(!boardCreated || !LexiconCreated)
return false;

  vector<int> temp;
  char *visited = new char[row * col]();
  bool return_value = false;	

  if(minimum_word_length == 0) minimum_word_length = 1;

  //If the lecicon and board were not created, return false
  if(!LexiconCreated || !boardCreated){
    delete[] visited;
    return false;
   }

  for(unsigned int i = 0;i < row;i++){
    for(unsigned int j = 0;j < col;j++){
        if(boggleboard[i][j].size() >= minimum_word_length && isInLexicon(boggleboard[i][j])){
          return_value = true;
          words->insert(boggleboard[i][j]);
        }
        visited[i * col + j] = 1;
        neighbor_search2(i,j,visited, words, boggleboard[i][j], return_value, minimum_word_length);;
        memset(visited,0,sizeof(char)*row*col);      
    }
  }
  delete[] visited;
  return return_value;
}

/* This function takes as argument a const string passed by reference, and determines 
 * whether it be found in the lexicon specified by the most recent call to buildLexicon(). 
 * The function returns true if the word is in the lexicon, and returns false if it is not in 
 * the lexicon or if buildLexicon() has not yet been called.
 */

bool BogglePlayer::isInLexicon(const string& word_to_check){
  if(!LexiconCreated){
    return false;
  }

  //Search for the word using helper method from TST class
  return head->findWord(word_to_check, letter_counter); 
}


/* This function starts at every board piece and continues to search as long as the next
 * letter on the board is part of the original word. This is done by checking all its 
 * neighbors and keeping a matrix of visited board pieces.
 */
vector<int> BogglePlayer::isOnBoard(const string& word_to_check){
if(!boardCreated || !LexiconCreated)
return vector<int>();

  vector<int> string_indices;
  char *visited = new char[row * col]();
  unsigned int stringindex = 0;
  unsigned int counter2 = 0;

  found=false;

  for(unsigned int i = 0;i < row;i++){
    for(unsigned int j = 0;j < col;j++){
      for(unsigned int k = 0;k < boggleboard[i][j].size();k++){
        if(boggleboard[i][j][k] == word_to_check[k]){
          stringindex++;
        }else{
         break;
        }
      }
    if(boggleboard[i][j].size() == stringindex){
	string_indices.push_back(i * col + j);
	if(boggleboard[i][j] == word_to_check){
	  delete[] visited;
	  return string_indices;
	}      
      visited[i * col + j] = 1;
      neighbor_search(i,j,visited, word_to_check.size(), string_indices, stringindex, word_to_check);
      memset(visited,0,sizeof(char)*row*col); 
      if(!found){
        string_indices.pop_back();
      }
      else{
        delete[] visited;
        return string_indices;
      }
    }
      stringindex = 0;
    }
  }	
  delete[] visited;
  return string_indices;						
  
}

/* This function is a helper function that does the neighbor searching for isOnBoard */
void BogglePlayer::neighbor_search(int r, int c, char *visited, int max_iter, vector<int> &string_indices, int stringindex, string word_to_check){
  unsigned int newI, newJ, k,counter=0;
	
  if((stringindex + boggleboard[r][c].size()) > max_iter){
    return;
  }

  for(int ii = -1;ii < 2;ii++){
    for(int jj = -1;jj < 2;jj++){
      newI = r + ii;
      newJ = c + jj;
      if(!visited[newI* col + newJ] && newI >= 0 && newI < row && newJ >= 0 && newJ < col){
        for(k = 0;k < boggleboard[newI][newJ].size();k++){
          if(boggleboard[newI][newJ][k] == word_to_check[stringindex]){
	         stringindex++;
	         counter++;
          }else{
	         stringindex-=counter;
	         counter=0;
	         break;
	  }
	}
      if(k == boggleboard[newI][newJ].size()){
	     string_indices.push_back(newI * col + newJ);
        visited[newI * col + newJ] = 1;
        char *visited2 = new char[row * col];
        memcpy(visited2, visited, row * col);
        neighbor_search(newI,newJ,visited2, max_iter, string_indices, stringindex, word_to_check);
	     visited[newI * col + newJ] = 0;
        delete[] visited2;
        string b((const char *)word_to_check.c_str()+(word_to_check.size() - stringindex));
	       if(!b.compare(word_to_check) || found) {
	        found = true;
	        return;
	       }else{
	        string_indices.pop_back();
	       }
        }
      }
    }	
  }
return;

}

/*
 * This is a helper function for findallvalidwords. the difference between this and the one before is that for this case
 * we need to find all words, so we put less restrictions and allow it to check every possible word of minimum length.
 * we also tell our function to stop when the next letter isnt in our dictionary. it basically searches for prefixes too
 * which speeds up the search overall.
*/

void BogglePlayer::neighbor_search2(int r, int c, char *visited, set<string>* words, string previous_word, bool &return_value, unsigned int minimum_word_length){
  int newI, newJ;
  string insert_word;

  for(int ii = -1;ii < 2;ii++){
    for(int jj = -1;jj < 2;jj++){
      newI = r + ii;
      newJ = c + jj;

      if(!visited[newI * col + newJ] && newI >= 0 && newI < row && newJ >= 0 && newJ < col){
        insert_word = previous_word + boggleboard[newI][newJ];
	     if(isInLexicon(insert_word) && insert_word.size() >= minimum_word_length){
          return_value = true;
          words->insert(insert_word);
          visited[newI * col + newJ] = 1;
          char *visited2 = new char[row * col];
          memcpy(visited2, visited, row * col);
          neighbor_search2(newI, newJ, visited2, words, insert_word, return_value, minimum_word_length);
          visited[newI * col + newJ] = 0;
          delete[] visited2;
        }else if (letter_counter == insert_word.size()){
          visited[newI * col + newJ] = 1;
          char *visited2 = new char[row * col];
          memcpy(visited2, visited, row * col); 
          neighbor_search2(newI,newJ,visited2, words, insert_word,return_value,minimum_word_length);
	       visited[newI * col + newJ] = 0;
          delete[] visited2;
        }
      }
    }
  }
}

void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols){

printf("not implemened\n");
}
