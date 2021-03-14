#include <iostream> // input/output
#include <typeinfo>
#include <stack>    // stack data structure
#include <queue>
#include <math.h>   // quick maths
#include <string>   // guess what this does?
#include <sstream>  // stringstreams

#include <vector>

using namespace std;


/*
numberStack.push(5); -> puts element into stack
numberStack.pop();   -> removes top element
numberStack.top();   -> gets top element

numberStack.size()   -> number of elements
numberStack.empty()  -> [BOOL] whether it is emtpy
*/




// Returns whether string is a number
bool isNumber(string s) {
  // looping over chars in string

  // checking for empty input
  if (s.size() == 0) return false;

  for (int i = 0; i < s.size(); i++) {
    char letter = s[i];

    // check if letter isn't digit or decimal point
    if (letter < '0' || letter > '9') {
      // checks minus case
      if ((letter == '-' && i == 0) && s.size() > 1)
        continue;
      // checks decimal point case
      if (letter == '.') continue;

      return false;
    }
  }
  // found an actual number
  return true;
}





// Splits expression into queue
queue<string> string2queue(string expression) {
  queue<string> token_queue;
  /*
  token_queue.push(3)   -> enqueues element
  token_queue.pop()     -> dequeues element
  token_queue.front()   -> gets first element
  */

  // empty string token
  string token = "";

  // iterating through expression
  for (int i = 0; i < expression.size(); i++) {
    char letter = expression[i];

    // adding letter to token
    if (letter != ' ') token += letter;
    else {      // found a whitespace char
      if (!token.empty()) { // protects against multiple whitespaces
        // ready to push token to queue
        token_queue.push(token);
        //cout << "This is token, right here: " << token << endl;
        token="";
      } // else, just another whitespace, keep going
    }
  }
  // adds token at the end of the expression (edge case)
  if ( !token.empty() ) token_queue.push(token);

  return token_queue;
}




// print elements in a queue
void print_queue(queue<string> q){
  int i = 0;
  while (!q.empty())
  {
    cout << i << "-th element: " << q.front() << endl;
    q.pop();
    i++;
  }
  cout << endl;
}




// evaluate RPN expression
double solve(string expression) {

  // generating queue of tokens
  queue<string> token_queue = string2queue(expression);

  /*
  // print copy of token_queue
  queue<string> q_copy = token_queue;
  print_queue(q_copy);
  */


  // big 'ol stack of numbers
  stack<double> numberStack;

  while (!token_queue.empty()) {
    // getting the token at the front of the queue
    string token = token_queue.front();
    token_queue.pop();

    // checking if token is a number
    if (isNumber(token)) {
      //cout << token << " is number\n";

      // Converting string token to double
      double numToken = stod(token);
      // pushing number to stack
      numberStack.push(numToken);
    } else {
      // found an operator
      if (numberStack.size() < 2) {
        cout << "SYNTAX ERROR - Not enough numbers in stack\n";
        exit(1);
      }

      // getting and popping the RH operand
      //cout << numberStack.top() << " is a: " << typeid(numberStack.top()).name() << endl;
      double b = numberStack.top() + 0.0;
      numberStack.pop();
      //cout << b << " is: " << typeid(b).name() << endl;
      // getting and popping the LH operand
      //cout << numberStack.top() << " is a: " << typeid(numberStack.top()).name() << endl;
      double a = numberStack.top() + 0.0;
      numberStack.pop();
      //cout << a << " is: " << typeid(a).name() << endl;

      // operation result
      double result = 0;

      // executing operation
      if (token == "+") result = a + b;           // addition
      else if (token == "-") result = a - b;      // subtraction
      else if (token == "*") result = a * b;      // multiplication
      else if (token == "/") result = a / b;      // division
      else if (token == "^") result = pow(a, b);  // exponentiation
      // checking for invalid operators
      else {
        cout << "INVALID INPUT - This operator doesn't exist\n";
        exit(1);
      }

      // pushing result to number stack
      numberStack.push(result);
    }
  }

  // cheking the size of the number stack
  int stackSize = numberStack.size();

  // If we got anything other than one, something went wrong.
  if (stackSize != 1) {
    cout << "SYNTAX ERROR - Not enough operators\n";
    exit(1);
  }

  // Pop result and print it
  double result = numberStack.top();
  numberStack.pop();

  return result;
}





// list of test expressions & expected output
vector< pair<string, double> > tests{
  /*1*/{"2 3 +", 5},
  /*2*/{"2 3 *", 6},
  /*3*/{"-123123 -123123 +", -246246},
  /*4*/{"2 2 + 3 - 123 - 24 *", -2928},
  /*5*/{"5 3 + 7 15 * 8 + -", -105},
  /*6*/{"2.00 3.99 +", 5.99},
  /*7*/{"4.00 2.00 /", 2.00},
  /*8*/{"2.0 5.0 ^", 32.0},
};





// run test expressions
bool runTests() {
  bool success = true;

  // looping through tests
  for (auto test : tests) {
    // solve expression
    double result = solve(test.first);

    // comparing solve() output with expected output
    if (result != test.second) {
      // current test failed
      cout << "FAILED TEST " << test.first << endl;
      cout << "EXPECTED " << test.second << " GOT " << result << endl;
      success = false;
    } else cout << "SUCCESS!\n";
  }
  return success;
}






// main program function
int main() {

  // run test expressions
  bool success = runTests();

  /*
  string expression;

  // read RPN expression
  cout << "Enter RPN: ";
  getline(cin, expression);

  // evaluate expression
  double result = solve(expression);

  // print output
  cout << result << endl;
  */

  return 0;
}
