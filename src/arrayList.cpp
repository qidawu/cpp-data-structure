#include <iostream>
using namespace std;

const int MAX_SIZE = 7;

typedef struct {
    int num;
} DataType;

/**
 * @brief 顺序表
 */
typedef struct {
    DataType data[MAX_SIZE];
    int length;  // 实际长度
} ArrayList;

/**
 * @brief 创建空表
 * 
 * @return ArrayList 顺序表
 */
ArrayList init() {
    ArrayList list;
    list.length = 0;
    return list;
}

/**
 * @brief 获取顺序表的总长度
 * 
 * @param list 顺序表
 * @return int 总长度
 */
int length(ArrayList &list) {
    return sizeof(list.data) / sizeof(list.data[0]);
}

/**
 * @brief 获取顺序表指定索引的元素
 * 
 * @param list 顺序表
 * @param index 指定索引
 * @return DataType 返回元素
 */
DataType get(ArrayList &list, int index) {
    return list.data[index];
}

/**
 * @brief 访问顺序表的每个元素
 * 
 * @param list 顺序表
 */
void access(ArrayList &list) {
    for (int i = 0; i < list.length; i++) {
        DataType item = get(list, i);
        cout << "i[" << i << "]=" << item.num << " ";
    }
    cout << endl;
}

/**
 * @brief 动态扩容（实现在顺序表的第 i 个元素之前，插入一个新元素）
 * 
 * @param list 顺序表
 * @param data 新元素
 * @param i 指定位置
 */
void insert(ArrayList &list, int i, DataType data) {
    if (list.length == MAX_SIZE) {
        // 解决方案是扩容：新建更大的数组，并进行数组拷贝
        cout << "list full. insert error." << endl;
    } else if (i < 1 || i > list.length + 1) {
        cout << "error position. could not insert into " << i << ", list current length: " << list.length << endl;
    } else {
        // 插入操作要向后搬移元素个数为：x = length - i + 1（+ 1 表示第 i 个元素自身也需要向后搬移）
        // if i = 1，x = 3。即全部向后搬移：
        //   a[3] = a[2]
        //   a[2] = a[1]
        //   a[1] = a[0]
        // if i = 3，x = 1。即只需向后搬移最后一个元素：
        //   a[3] = a[2]
        // if i = 4，x = 0。即无需向后搬移，追加到末尾即可
        int opt = 0;
        for (int j = list.length; j >= i; j--) {
            list.data[j] = list.data[j - 1];
            opt++;
        }
        // cout << "insert: length=" << list.length << ", i=" << i << ", x=" << opt << endl;
        // 覆盖掉第 i 个元素
        list.data[i - 1] = data;
        list.length++;
    }
}

/**
 * @brief 动态缩容（实现删除顺序表指定位置的元素，从 1 开始）
 * 
 * @param list 顺序表
 * @param i 指定位置
 */
void del(ArrayList &list, int i) {
    if (list.length == 0) {
        cout << "list empty, delete error" << endl;
    } else if (i < 1 || i > list.length) {
        cout << "error position. could not delete " << i << ", list current length: " << list.length << endl;
    } else {
        // 删除操作要向前搬移元素个数为：x = length - i
        // if i = 1, x = 2。即删除第一个元素，即全部向前搬移：
        //   a[0] = a[1]
        //   a[1] = a[2]
        // if i = 2，x = 1。即只需向前搬移最后一个元素：
        //   a[1] = a[2]
        // if i = 3，x = 0。即无需向前搬移
        int opt = 0;
        for (int j = i; j < list.length; j++) {
            list.data[j - 1] = list.data[j];
            opt++;
        }
        // cout << "del: length=" << list.length << ", i=" << i << ", x=" << opt << endl;
        list.length--;
    }
}

int main() { 
    ArrayList list = init();
    DataType d1;
    DataType d2;
    DataType d3;
    d1.num = 1;
    d2.num = 2;
    d3.num = 3;
    insert(list, 2, d1);
    insert(list, 1, d1);
    insert(list, 1, d2);
    insert(list, 1, d3);
    cout << "total length: " << length(list) << ", actual length: " << list.length << endl;
    access(list);

    del(list, 5);
    del(list, 4);
    del(list, 1);
    access(list);
    del(list, 1);
    access(list);

    return 0;
}