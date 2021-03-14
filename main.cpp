#include <iostream> // input/output
#include <stack>    // stack data structure
//#include <math.h>   // quick maths
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

    // if ASCII code doesn't match a digit
    if (letter < '0' || letter > '9') {      // checks if is digit
      // checks minus case
      if ((letter == '-' && i == 0) && s.size() > 1)
        continue;
      return false;
    }
  }
  // found an actual number
  return true;
}

// e.g. expression = "2 3 +"
int solve(string expression) {

  // big stack of numbers
  stack<int> numberStack;

  stringstream fakeCin;
  fakeCin << expression;

  string token;
  while (fakeCin >> token) {

    if (isNumber(token)) {
      //cout << token << " is number\n";
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

// list of test expressions & expected output
vector< pair<string, int> > tests{
  {"2 3 +", 5},
  {"2 3 *", 6},
  {"-123123 -123123 +", -246246},
  {"2 2 + 3 - 123 - 24 *", -2928},
  {"5 3 + 7 15 * 8 + -", -105},
};

// run test expressions
bool runTests() {
  bool success = true;

  // looping through tests
  for (auto test : tests) {
    // solve expression
    int result = solve(test.first);

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

int main() {

  // run test expressions
  bool success = runTests();

  /*
  // simple prompt
  cout << "Enter RPN: ";

  // input RPN expression
  string expression;
  getline(cin, expression);

  cout << solve(expression);
  */

  return 0;
}
