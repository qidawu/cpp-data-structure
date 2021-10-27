#include <iostream>
using namespace std;

const int MAX_SIZE = 5;

/**
 * @brief 循环队列
 */
typedef struct {
  int data[MAX_SIZE];
  int head; // 指向队首元素的前一个单元（留空以便判断队满）
  int tail; // 指向队尾元素
} cycleQueue;

cycleQueue init() {
  cycleQueue queue;
  queue.head = queue.tail = 0;
  return queue;
}

/**
 * @brief 实现类自增运算
 */ 
int next(int position) {
  // 用取余运算实现 0 ~ MAX_SIZE-1 之间反复循环
  return (position + 1) % MAX_SIZE;
}

bool isEmpty(cycleQueue *queue) {
  return queue->tail == queue->head;
}

bool isFull(cycleQueue *queue) {
  // 队尾只差一步就追上队首
  return next(queue->tail) == queue->head;
}

int element(cycleQueue *queue) {
  int head = next(queue->head);
  return queue->data[head];
}

void add(cycleQueue *queue, int data) {
  if (isFull(queue)) {
    cout << "queue full, cannot add " << data << endl;
  } else {
    queue->tail = next(queue->tail);
    queue->data[queue->tail] = data;
  }
}

int remove(cycleQueue *queue) {
  if (isEmpty(queue)) {
    cout << "queue empty, cannot remove" << endl;
    return -1;
  } else {
    int data = element(queue);
    int head = next(queue->head);
    cout << "i[" << head << "]=" << data << " removed" << endl;
    queue->head = head;
    return data;
  }
}

/**
 * @brief 从队头打印到队尾
 */ 
void access(cycleQueue *queue) {
  if (isEmpty(queue)) {
    return;
  }

  int i = next(queue->head);
  while (true) {
    cout << "i[" << i << "]=" << queue->data[i];

    if (i == queue->tail) {
      break;
    } else {
      cout << ", ";
      i = next(i);
    }
  }
  cout << endl;
}

/**
 * 输出结果：
 * i[1]=0, i[2]=1, i[3]=2, i[4]=3
 * queue full, cannot add 4
 * i[1]=0 removed
 * i[2]=1, i[3]=2, i[4]=3
 * i[2]=1, i[3]=2, i[4]=3, i[0]=5
 * head of queue: 1
 * queue is not empty
 * queue is full
 */
int main() {
  cycleQueue queue = init();
  add(&queue, 0);
  add(&queue, 1);
  add(&queue, 2);
  add(&queue, 3);
  access(&queue);
  add(&queue, 4);
  
  remove(&queue);
  access(&queue);
  
  add(&queue, 5);
  access(&queue);

  cout << "head of queue: " << element(&queue) << endl;
  cout << "queue is " << (isEmpty(&queue) ? "empty" : "not empty") << endl;
  cout << "queue is " << (isFull(&queue) ? "full" : "not full") << endl;
  return 0;
}