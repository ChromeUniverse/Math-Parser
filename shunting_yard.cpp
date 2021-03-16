/*
    -- Shunting Yard algorithm --

    Implementation of Dijkstra's Shunting
    Yard algorithm in C++.

    Converts infix expressions to postfix
    expressions (a.k.a. RPN).

*/


#include <iostream> // input/output
//#include <typeinfo> // object type info
//#include <math.h>   // 2 plus 2 is 4, minus 1, that's 3, quick maths
#include <string>   // guess what this does?

//#include <vector>   // glorious vectors
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
    // -> creates new token instance
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

    // returns operator precedence ranking
    // assumes it's *only* going to be called for Operator tokens

    /* Operator precedence, highest to lowest:

        ^      > exponent
        * , /  > multiplication, division
        + , -  > addition, subtraction
        =      > equals sign
        (      > L_PAREN --- overrides precedence

    */

    int getPrecedence() {
      if (tokenText == "^") return 4;
      if (tokenText == "*" || tokenText == "/") return 3;
      if (tokenText == "+" || tokenText == "-") return 2;
      if (tokenText == "=") return 1;
      if (tokenText == "(") return 0;
    }

    // useless token class destructor
    //virtual ~Token ();
};






// print elements in a queue
void print_queue(queue<Token> q_original){
  // creating a copy of the queue
  queue<Token> q = q_original;

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



// print elements in a stack
void print_stack( stack <Token> s_original ){
  // creating a copy of the stack
  stack<Token> s = s_original;

  int i = 0;
  while (!s.empty())
  {
    // get element (token) text
    Token element = s.top();
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
    s.pop();

    i++;
  }
  // line break
  cout << endl;
}










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






// shunt function
// -> converts input queue (infix) to RPN queue (postfix)

/* Operator precedence, highest to lowest:

    ^      > exponent
    * , /  > multiplication, division
    + , -  > addition, subtraction
    =      > equals sign
    (      > L_PAREN --- overrides precedence

*/


queue<Token> shunt( queue<Token> input_queue ) {

  // RPN expression will be stored in the output queue
  queue<Token> output_queue;

  // operator tokens will be stored in the operator stack
  stack<Token> operator_stack;

  // while there are still input tokens to be read
  while ( !input_queue.empty() ) {
    // get top of imput_queue
    Token input_token = input_queue.front();
    input_queue.pop();

    cout << "\nHere is input_token: " << input_token.getText() << endl;

    if (input_token.getType() == 0) {               // check if token is a number
      output_queue.push(input_token);               // numbers are always pushed to the output
      cout << "\nFound number, here is output, right now: " << endl;
      print_queue(output_queue);

    } else if (input_token.getType() == 1) {        // check if token is an operator
      int input_rank = input_token.getPrecedence();    // get operator precedence ranking

      cout << "\nFound operator " << input_token.getText() << ", of precedence " << input_rank << endl;

      while (true) {

        if ( operator_stack.empty() ){                // if there isn't anything in the stack
          operator_stack.push(input_token);           // just push that operator in there

          cout << "\nOP STACK empty, adding operator: " << input_token.getText() << endl;
          cout << "Here is the op stack:" << endl;
          print_stack(operator_stack);

          break;                                      // nothing else to do here, break out of the loop

        } else {

          cout << "\nOP STACK not empty." << endl;


          // get head of the stack
          Token stack_head = operator_stack.top();
          int head_rank = stack_head.getPrecedence();

          cout << "\nCOMPARE:\n";
          cout << input_token.getText() << " has precendence " << input_rank << endl;
          cout << stack_head.getText() << " has precendence " << head_rank << endl;
          cout << "\n";

          if ( input_rank > head_rank ) {           // if the input operator has a higher precedence than the head of the stack
            cout << "Input has higher precendece, adding it to OP stack" << endl;
            operator_stack.push(input_token);       // push it to the stack
            cout << "Here is op_stack: \n";
            print_stack(operator_stack);
            break;                                  // break out of the loop

          } else {
            cout << "Input has equal ou lower precendence, get stack head out of here" << endl;
            output_queue.push(stack_head);          // else, get the stack's head and push to the output
            operator_stack.pop();                   // pop the head of the stack

            cout << "Here is op_stack: \n";
            print_stack(operator_stack);
            cout << "\nAnd here is output:" << endl;
            print_queue(output_queue);
          }


        }

    }

    } else if (input_token.getType() == 2) {        // check if token is a L_paren
      operator_stack.push(input_token);             // no matter what, just push it to the op stack
      cout << "\nFound L_paren, adding it to op stack, no matter what" << endl;
      cout << "Here is op stack rn: " << endl;
      print_stack(operator_stack);

    } else if (input_token.getType() == 3) {        // check if token is a R_paren

      cout << "\nFound R_paren, let's search for a L_paren to close it" << endl;

      while (true) {
        // get head of the stack
        Token stack_head = operator_stack.top();
        string stack_head_text = stack_head.getText();

        cout << "Stack head rn is: " << stack_head_text << endl;

        if (stack_head_text != "(") {               // check if stack head isn't a L_paren
          cout << "Not a L_paren, push it to output" << endl;
          output_queue.push(stack_head);            // push the stack's head to the output queue
          operator_stack.pop();                     // pop the head of the stack

          cout << "here is op stack:" << endl;
          print_stack(operator_stack);
          cout << "And here is output:" << endl;
          print_queue(output_queue);

        } else {                                    // found a L_paren at the head of the stack
          cout << "Oh, wow, actually found a L_paren, get rid of it ewwwwwwwww" << endl;
          operator_stack.pop();                     // just remove it from the stack

          cout << "here is op stack:" << endl;
          print_stack(operator_stack);
          cout << "And here is output:" << endl;
          print_queue(output_queue);

          break;                                    // break out of the loop
        }
      }

    }

  } // end of input parsing

  cout << "\nDONE! No more input to parse. \n";
  //
  // dump on the operator stack onto the output queue

  cout << "\nDumping the operator stack to the output: \n";
  while ( !operator_stack.empty() ) {
    // take top element, push it to output
    Token myoperator = operator_stack.top();
    output_queue.push(myoperator);
    // remove it from the operator stack
    operator_stack.pop();
  }


  // print copy of output token queue
  print_queue(output_queue);

  // print copy of the operator stack
  print_stack(operator_stack);

  return output_queue;
}









// main program

int main() {

  // read math expression
  //cout << "Enter your math: ";
  //getline(cin, expression);

  // math expression
  string expression = "234.5 / ( -123.12 + 7.8 ) * 2.5";
  cout << "\nHere is math: " << expression << endl;

  // parse input
  queue<Token> input_queue = input(expression);

  // print copy of token queue
  cout << "\nHere is parsed input: " << endl;
  print_queue(input_queue);


  // run Shunting Yard
  queue<Token> rpn_queue = shunt(input_queue);

  return 0;
}
