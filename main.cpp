#include <iostream> // input/output
#include <stack>    // stack data structure
//#include <math.h>   // quick maths
#include <string>   // guess what this does?
#include <sstream>  // stringstreams

using namespace std;

stack<int> numberStack;

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
  for (char letter : s) {
    // if ASCII code doesn't match a digit
    if (letter < '0' || letter > '9')
      return false;
  }
  // found an actual number
  return true;
}

int main() {

  // read RPN expression
  cout << "Enter RPN: ";
  string token;
  while (true) {
    // reading tokens
    cin >> token;

    if (token == "x") break;

    if (isNumber(token)) {
      // pushing number to stack
      int numToken = stoi(token);
      numberStack.push(numToken);
    } else {
      // found an operator
      if (numberStack.size() < 2) {
        cout << "SYNTAX ERROR - Not enough numbers in stack\n";
        return 1;
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
        return 1;
      }

      // pushing result to number stack
      numberStack.push(result);
    }
  }

  // cheking the size of the number stack
  int stackSize = numberStack.size();

  // If we got anything other than one, something went wrong.
  if (stackSize != 1) {
    cout << "SYNTAX ERROR - not enough operators\n";
    return 1;
  }

  // Pop result and print it
  int result = numberStack.top();
  numberStack.pop();

  cout << "Result: " << result << "\n";

  return 0;
}
