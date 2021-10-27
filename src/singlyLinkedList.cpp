#include <iostream>
using namespace std;

/**
 * @brief 带尾结点的单向链表
 */
typedef struct node {
  int data;    // 数据域
  node *next;  // 后继结点
  node *rear;  // 尾结点
  int length;  // 链表实际长度
} * LinkedList;

/**
 *  @brief 创建空表
 */
LinkedList init() {
  // 新建头指针
  LinkedList head;
  // 指向头结点
  head = (node*) malloc(sizeof(node));
  head->next = NULL;
  head->rear = head;
  head->length = 0;
  return head;
}

/**
 * @brief 求表长
 */
int length(LinkedList head) {
  int length = 0;
  // 从头结点开始遍历
  for (node *p = head; p->next != NULL; p = p->next) {
    length++;
  }
  return length;
}

/**
 * @brief 遍历
 */
void access(LinkedList head) {
  // 从首结点开始遍历
  for (node *p = head->next; p != NULL; p = p->next) {
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
  }
  else if (position == 0) {
    return head;
  } else {
    // 从首结点开始遍历
    node *p = head->next;
    int i = 1;
    while (p != NULL && i < position) {
      p = p->next;
      i++;
    }
    return i == position ? p : NULL;
  }
}

/**
 * @brief 追加新结点（尾插法）
 */
void append(LinkedList head, node *p) {
  p->next = head->rear->next;
  head->rear->next = p;
  head->rear = p;
  head->length++;
}

/**
 * @brief 插入新结点（insert p before position）
 */
void insert(LinkedList head, int position, node *p) {
  // 能找到找到 N-1 结点，才能插入到 N
  node *q = get(head, position - 1);
  if (q == NULL) {
    cout << "error position. could not insert before node " << position << ", previous node not found" << endl;
    return;
  } else {
    // 插入口诀：先新后旧
    p->next = q->next;
    q->next = p;
    // 新结点是否是尾结点
    if (p->next == NULL) {
      head->rear = p;
    }
    head->length++;
  }
}

/**
 * @brief 删除指定结点
 */
void del(LinkedList head, int position) {
  // 能找到找到 N-1 结点，才能删除到 N
  node *q = get(head, position - 1);
  if (q == NULL) {
    cout << "error position. could not delete node " << position << ", previous node not found" << endl;
    return;
  }
  // 找不到当前结点，无法删除
  else if (q->next == NULL) {
    cout << "error position. could not delete node " << position << ", current node not found" << endl;
    return;
  }
  // 删除当前结点
  else {
    q->next = q->next->next;
    // N-1 结点是否是尾结点
    if (q->next == NULL) {
      head->rear = q;
    }
    head->length--;
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
  
  access(head);
  cout << "rear: " << head->rear->data << endl;
  append(head, &n1);
  access(head);
  cout << "rear: " << head->rear->data << endl;
  append(head, &n2);
  access(head);
  cout << "rear: " << head->rear->data << endl;
  insert(head, 3, &n3);
  access(head);
  cout << "rear: " << head->rear->data << endl;

  cout << "current length: " << head->length << endl;

  del(head, 4);
  del(head, 1);
  access(head);
  cout << "rear: " << head->rear->data << endl;
  del(head, 2);
  access(head);
  cout << "rear: " << head->rear->data << endl;
  del(head, 1);
  access(head);
  cout << "rear: " << head->rear->data << endl;

  return 0;
}