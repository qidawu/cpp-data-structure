#include <iostream>
using namespace std;

const int MAX_SIZE = 5;

/**
 * @brief 顺序栈
 */
typedef struct {
    int data[MAX_SIZE];
    int top;  // 栈顶
} arrayStack;

arrayStack init() {
  arrayStack stack;
  stack.top = 0;
  return stack;
}

bool isEmpty(arrayStack *stack) {
  return stack->top == 0;
}

bool isFull(arrayStack *stack) {
  return stack->top == MAX_SIZE - 1;
}

int getTop(arrayStack *stack) {
  return stack->data[stack->top];
}

void push(arrayStack *stack, int data) {
  if (isFull(stack)) {
    cout << "stack full, cannot push " << data << endl;
  } else {
    stack->top++;
    stack->data[stack->top] = data;
  }
}

int pop(arrayStack *stack) {
  if (isEmpty(stack)) {
    cout << "stack empty, cannot pop" << endl;
    return -1;
  } else {
    int element = getTop(stack);
    stack->top--;
    return element;
  }
}

/**
 * @brief 从栈顶打印到栈底
 */ 
void access(arrayStack *stack) {
  for (int i = stack->top; i > 0; i--) {
    cout << "i[" << i << "] = " << stack->data[i] << endl;
  }
}

int main() {
  arrayStack stack = init();
  push(&stack, 10);
  push(&stack, 11);
  pop(&stack);
  push(&stack, 12);
  push(&stack, 13);
  pop(&stack);
  push(&stack, 14);
  push(&stack, 15);
  pop(&stack);
  push(&stack, 16);

  access(&stack);

  cout << "stack is " << (isEmpty(&stack) ? "empty" : "not empty") << endl;
  cout << "stack is " << (isFull(&stack) ? "full" : "not full") << endl;
  cout << "top of stack: " << getTop(&stack) << endl;
  return 0;
}