/*
    -- Shunting Yard algorithm --

    Implementation of Dijkstra's Shunting
    Yard algorithm in C++.

    Converts infix expressions to postfix
    expressions (a.k.a. RPN).

*/


#include <iostream> // input/output
#include <typeinfo> // object type info
#include <math.h>   // 2 plus 2 is 4, minus 1, that's 3, quick maths
#include <string>   // guess what this does?

#include <vector>   // glorious vectors
#include <stack>    // stack data structure
#include <queue>    // queue data structure

using namespace std;





// Token class
// -> for tokens in math expressions

class Token {

  private:
    // data attributes
    int tokenType;        // 0 -> number token
                          // 1 -> operator token
                          // 2 -> L_paren
                          // 3 -> R_paren

    string tokenText;     // token's text

  public:
    // class constructor
    // creates new token instance
    Token (string text, int type) {
      tokenType = type;
      tokenText = text;
    };

    // returns type of token
    int getType () {
      return tokenType;
    }

    // returns token's text
    string getText () {
      return tokenText;
    }

    // useless token class destructor
    //virtual ~Token ();
};








// findType function
// -> takes in token text and returns token type

int findType (string s) {

  // checking for empty input
  if (s.size() == 0) return false;

  for (int i = 0; i < s.size(); i++) {
    char c = s[i];

    // check if letter is a digit
    if (c >= '0' && c <= '9') return 0; // found a number
    else {
      // check for L_paren and R_paren
      if (c == '(') return 2;
      if (c == ')') return 3;

      // check for a preceding minus sign
      if ((c == '-' && i == 0) && s.size() > 1) continue;
      // checks for a decimal point
      if (c == '.') continue;

      // checking for arithmetic operators
      if (c == '^') return 1;
      if (c == '*') return 1;
      if (c == '/') return 1;
      if (c == '+') return 1;
      if (c == '-') return 1;

    }
    // end of not-number logic case
    return false;

  } // end of for loop

}






// input function
// -> parses math input, converts to input queue

// e.g. 2 + ( 3 * 7 ) -> queue[ 2, +, (, 3, *, 7, ) ]

queue<Token> input(string expression) {

  queue<Token> input_queue;

  /*
  input_queue.push(3)   -> enqueues element
  input_queue.pop()     -> dequeues element
  input_queue.front()   -> gets first element
  */

  // token parameters
  string token_text = "";
  int token_type;

  // parsing the input expression

  for (int i = 0; i < expression.size(); i++) {
    // get current letter
    char letter = expression[i];

    // didn't find a whitespace char
    if (letter != ' ') {
      token_text += letter;
    }

    // found a whitespace or reached end of expression
    if (letter == ' ' || i == expression.size()-1){
      // find out what the token type is
      token_type = findType(token_text);
      // create token instance
      Token newToken(token_text, token_type);
      // push it on the queue
      input_queue.push(newToken);
      // clear current token text buffer
      token_text = "";
    }
  }

  return input_queue;

}




/*

// shunt function
// -> converts input queue (infix) to RPN queue (postfix)

// Operator perecedence

queue<Token> shunt(queue<Token> input_queue) {

  // RPN expression will be stored in the output queue
  queue<Token> output_queue;

  while (!input_queue.empty()) {
    // get top of imput_queue
    Token token = input_queue.front();
    input_queue.pop();

    if (token.getType() == 0) {           // check if token is a number
      // push it to the output
      output_queue.push(token);
    } else if (token.getType() == 1) {    // check if token is an operator

    }

  }

  return output_queue;
}

*/






// print elements in a queue
void print_queue(queue<Token> q){
  int i = 0;
  while (!q.empty())
  {
    // get element (token) text
    Token element = q.front();
    string t_text = element.getText();
    int t_type = element.getType();

    // print out type properly
    string type_text = "";
    if (t_type == 0) type_text = "NUMBER";
    if (t_type == 1) type_text = "OPERATOR";
    if (t_type == 2) type_text = "L_PAREN";
    if (t_type == 3) type_text = "R_PAREN";
    // print it out
    cout << "Element #" << i+1 <<": " << t_text << " is of type " << type_text << endl;
    // pop it!
    q.pop();

    i++;
  }
  // line break
  cout << endl;
}






// main program

int main() {

  string expression;

  // read math expression
  cout << "Enter your math: ";
  getline(cin, expression);

  // parse input
  queue<Token> input_queue = input(expression);

  // run Shunting Yard
  //queue<Token> rpn_queue = shunt(input_queue);

  // print copy of token queue
  queue<Token> q_copy = input_queue;
  print_queue(q_copy);
  
  return 0;
}
