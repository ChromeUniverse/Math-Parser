#include <iostream> // input/output
#include <stack>    // stack data structure
//#include <math.h>   // quick maths
#include <string>   // guess what this does?
#include <sstream>  // stringstreams

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

  for (int i = 0; i < s.size(); i++) {
    char letter = s[i];

    // if ASCII code doesn't match a digit
    if (letter < '0' || letter > '9') {      // checks if is digit
      if (letter == '-' && i == 0) continue; // checks minus case
      return false;
    }
  }
  // found an actual number
  return true;
}

// e.g. expression = "2 3 +"
int resolve(string expression) {

  stack<int> numberStack;

  stringstream fakeCin;
  fakeCin << expression;

  string token;
  while (fakeCin >> token) {

    if (isNumber(token)) {
      // pushing number to stack
      int numToken = stoi(token);
      numberStack.push(numToken);
    } else {
      // found an operator
      if (numberStack.size() < 2) {
        cout << "SYNTAX ERROR - Not enough numbers in stack\n";
        exit(1);
      }

      // getting and popping the RH operand
      int b = numberStack.top();
      numberStack.pop();
      // getting and popping the LH operand
      int a = numberStack.top();
      numberStack.pop();

      // operation result
      int result = 0;

      // executing operation
      if (token == "+") result = a + b;
      else if (token == "-") result = a - b;
      else if (token == "*") result = a * b;
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
  int result = numberStack.top();
  numberStack.pop();

  return result;
}

int main() {
  // simple prompt
  cout << "Enter RPN: ";

  // input RPN expression
  string expression;
  getline(cin, expression);

  string e1 = "2 3 +";
  if (resolve(e1) != 5) {
    cout << "FAILED TEST\n";
  }

  cout << resolve(expression);

  return 0;
}
