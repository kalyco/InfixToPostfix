#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <string>
#include <cmath>
#include "stack.h"

using namespace std;

class calculator {

 public:

 calculator()
   : mInfixInput(""), mPostfixOutput("")
    {}

  void readInput();
  void convertInputIntoPostfix();
  void outputPostfix() const;
  void evaluatePostfixIntoResult();
  void outputResult() const;
  bool isStopCondition() const;

 private:

  // Helper functions
  bool hasHigherPrecedenceThan(int aLHS, int aRHS) const;

  bool isOperator(int c) const;
  
 private:
  string mInfixInput;
  string mPostfixOutput;
  int mResult;

};

bool calculator::isStopCondition() const
{
  return (mInfixInput == ".");
}

void calculator::readInput()
{
  mInfixInput.clear();
  mPostfixOutput.clear();
  cin >> mInfixInput;
}

void calculator::outputPostfix() const
{
  cout << "Postfix = "
       << mPostfixOutput 
       << endl;
}

void calculator::outputResult() const
{
  cout << "Result = "
       << mResult
       << endl;
}

// Returns true if aLHS has a higher precedence than aRHS.
// Otherwise, returns false.
bool calculator::hasHigherPrecedenceThan(int aLHS, int aRHS) const
{
  if ((aRHS == '+' || aRHS == '-') &&
      (aLHS == '*' || aLHS == '/' || aLHS == '^')) {
    return true;
  }
  if ((aRHS == '+' || aRHS == '-' || aRHS == '*' || aRHS == '/') &&
      (aLHS == '^')) {
    return true;
  }
  if (aLHS == '^' && aRHS == '^') {
    return true;
  }
  return false;
}

bool calculator::isOperator(int c) const
{
  return ((c == '+') ||
	  (c == '-') ||
	  (c == '*') ||
	  (c == '/') ||
	  (c == '^'));
}

void calculator::convertInputIntoPostfix()
{
  // Your implementation goes here
}

void calculator::evaluatePostfixIntoResult()
{
  // Your implementation goes here
}

int getPriority(char c) {
  if(c=='(') return 0; // highest priority
  if(c == '+' || c== '-') return 1;
  if(c == '*' || c == '/' || c =='%') return 2;
  return -1;
}

#endif
