#include <iostream>
using namespace std;

/**
 * @brief 双向循环链表
 */
typedef struct node {
  int data;    // 数据域
  node *prev;  // 前驱结点
  node *next;  // 后继结点
} * LinkedList;

/**
 *  @brief 创建空表
 */
LinkedList init() {
  // 新建头指针
  LinkedList head;
  // 指向头结点
  head = (node*) malloc(sizeof(node));
  head->prev = head;
  head->next = head;
  return head;
}

/**
 * @brief 求表长
 */
int length(LinkedList head) {
  int length = 0;
  // 从头结点开始遍历
  for (node *p = head; p->next != head; p = p->next) {
    length++;
  }
  return length;
}

/**
 * @brief 遍历
 */
void access(LinkedList head) {
  // 从首结点开始遍历
  for (node *p = head->next; p != head; p = p->next) {
    cout << p->data << " ";
  }
  cout << endl;
}

/**
 * @brief 按序号查找
 */
node * get(LinkedList head, int position) {
  if (position < 0) {
    return NULL;
  } else {
    // 从头结点开始遍历（空链表的首结点为 NULL）
    int i = 0;
    node *p = head;
    while (p->next != head && i < position) {
      p = p->next;
      i++;
    }
    return i == position ? p : NULL;
  }
}

/**
 * @brief 插入新结点（insert p after position）
 */
void insert(LinkedList head, int position, node *p) {
  node *q = get(head, position);
  if (q == NULL) {
    cout << "error position. could not insert after node " << position << ", current node not found" << endl;
    return;
  } else {
    // 插入口诀：先新后旧，先前再后
    p->prev = q;
    p->next = q->next;
    q->next->prev = p;
    q->next = p;
  }
}

/**
 * @brief 删除指定结点
 */
void del(LinkedList head, int position) {
  node *q = get(head, position);
  // 找不到当前结点，无法删除
  if (q == NULL) {
    cout << "error position. could not delete node " << position << ", current node not found" << endl;
    return;
  }
  // 删除当前结点
  else {
    q->prev->next = q->next;
    q->next->prev = q->prev;
  }
}

int main() {
  LinkedList head = init();
  node n1;
  node n2;
  node n3;
  n1.data = 1;
  n2.data = 2;
  n3.data = 3;
  insert(head, 1, &n1);
  insert(head, 0, &n1);
  insert(head, 0, &n2);
  insert(head, 0, &n3);
  cout << "current length: " << length(head) << endl;
  access(head);

  del(head, 5);
  del(head, 4);
  del(head, 3);
  access(head);
  del(head, 2);
  access(head);
  
  return 0;
}