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

  int calcPower(int base, int exp);
  
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

// Postfix notation: Write expressions without using parentheses
// 1-- Scan from left -> right
// 2-- If char is a digit, output immediately
// 3-- If operator:
// 4-- While stack !empty && operator has precedence <= top stack element, pop and output top element
// 5-- Push the operator into the stack
// 6-- Pop remaining chars in input and output them in sequence
void calculator::convertInputIntoPostfix()
{
  stack * stk = new stack();
  string postfix;
  for (int i=0; i < mInfixInput.length(); i++) {
    if (!isOperator(mInfixInput[i])) {
      postfix += mInfixInput[i];
    } else {
      while(!stk->isEmpty() && !hasHigherPrecedenceThan(mInfixInput[i], stk->top())) {
        postfix += stk->top();
        stk->pop();
      }
      stk->push(mInfixInput[i]);
    }
  }  
  while (!stk->isEmpty()) {
    postfix += stk->top();
    stk->pop();
  }
  mPostfixOutput = postfix;
  delete stk;
}

// Postfix function: evaluate into a result
// 1-- Scan from left -> right
// 2-- push operands onto stack
// 3-- When operator is encountered, pop 2 top values from stack and apply operator
// 4-- Replace operands in stack with result
void calculator::evaluatePostfixIntoResult()
{
  stack * stk = new stack();
  for (int i=0; i < mPostfixOutput.length(); i++) {
    if (!isOperator(mPostfixOutput[i])) {
      stk->push(mPostfixOutput[i]);
    } else {
      int operand1 = stk->top() - 48;
      stk->pop();
      int operand2 = stk->top() - 48;
      stk->pop();

      switch (mPostfixOutput[i]) {
        case '+': stk->push((operand1 + operand2) + 48); break;
        case '-': stk->push((operand2 - operand1) + 48); break;
        case '*': stk->push((operand1 * operand2) + 48); break;
        case '/': stk->push((operand2 / operand1) + 48); break;
        case '^': {
          int result = calcPower(operand2, operand1);
          stk->push(result + 48); break;
        }
      }
    }
  }
  mResult = stk->top() - 48;
  stk->pop();
  delete stk;
}

int calculator::calcPower(int base, int e) {
  int b = base;
  int result = base;
  for (int i=1; i < e; i++) {
    result = result * base;
  }
  return result;
}

#endif