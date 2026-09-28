# Lab7：C++ 实现带头哨兵的单链表类

> **作业目标**：在课堂上学习的带头哨兵单链表基础上，使用 C++ 面向对象程序设计思想，用 `class` 将结点结构体和操作函数打包，实现完整的增删改查功能。重点考察：构造函数、析构函数、拷贝构造函数、赋值运算符的正确实现，以及内存管理规范（new/malloc/free/delete 配对原则）。

> **检查说明**：程序正确性将在期末统一检测。本次作业不涉及 CLion Memory View 截图，仅提交代码和书面答案。

---

## 一、CMakeLists.txt 配置

保留 Lab6，在新的 `Lab7` 目录中完成本次作业。

```cmake
cmake_minimum_required(VERSION 3.20)
project(Lab7 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(lab7_list linkedlist_cpp.cpp)

```

要求：

- `project(...)` 与前几次作业一致，同时声明 `C` 和 `CXX`。
- 有且只有 **一个** `add_executable`，目标名与源文件名完全一致。
- 源文件是 `.cpp`，按 C++17 编译。
- 保存后重新加载 CMake 项目。

---

## 二、C++ 类的设计要点

### 2.1 类的组成

```cpp
class LinkedList {
private:
    Node* head;  // 哨兵节点，不存储有效数据
    int size;    // 有效节点个数
    
public:
    // 成员函数...
};
```

- **私有成员**：`head`（哨兵指针）和 `size`（计数器），直接外不可访问。
- **公有成员**：所有操作接口，包括构造/析构、增删改查等。

### 2.2 特殊成员函数（五法则）

| 函数 | 作用 | 是否需要手动实现 |
| :--- | :--- | :--- |
| **默认构造函数** | 创建空对象 | 是（必须手动初始化 `head` 和 `size`） |
| **析构函数** | 释放动态分配的内存 | 是（必须 `delete` 每一个 `new` 出来的结点） |
| **拷贝构造函数** | 创建一个副本 | 是（必须进行**深拷贝**，分配新内存，避免双重释放） |
| **移动构造函数** (C++11) | 资源转移 | 否（可默认，但建议实现） |
| **拷贝赋值运算符** | 赋值操作 | 是（必须先释放旧内存，再深拷贝新内存，防止内存泄漏） |
| **移动赋值运算符** (C++11) | 赋值操作 | 否（可默认） |

### 2.3 内存管理原则

- **`new` 必须有 `delete`，`malloc` 必须有 `free`**
- **析构函数中**：从头遍历链表，逐个 `delete` 结点，最后 `delete` 哨兵
- **拷贝构造与赋值**：必须分配新结点，**不能直接复制指针**，否则会导致两个对象指向同一内存，释放时出现双重错误
- **不仅仅是结点**：需要考虑头节点 `head` 是否也需要 `delete`（取决于设计，本次作业中 head 也需要delete）

---

## 三、linkedlist_cpp.cpp：C++ 类的实现

### 3.1 必须使用的框架

下面的框架可以直接编译运行，把每一处 `TODO` 换成正确实现即可。不得修改类的公有接口，不得改变结点与类的定义。

```cpp
#include <iostream>

using namespace std;

// 结点：与课堂上写的完全相同，不得修改
struct Node {
    int data;           /* 数据域：保存一个整数 */
    Node* next;         /* 指针域：保存下一个结点的地址，NULL 表示没有后继 */
};

// 声明 LinkedList 类
class LinkedList {
private:
    Node* head;         /* 哨兵节点，data 不使用 */
    int size;           /* 有效结点个数，不含哨兵 */
    
public:
    // TODO: 在这里实现特殊成员函数
    
    // 构造函数
    LinkedList() {
        // TODO: 初始化 head 和 size
    }
    
    // 析构函数
    ~LinkedList() {
        // TODO: 释放所有结点
    }
    
    // 拷贝构造函数
    LinkedList(const LinkedList& other) {
        // TODO: 深拷贝
    }
    
    // 拷贝赋值运算符
    LinkedList& operator=(const LinkedList& other) {
        // TODO: 释放旧内存并深拷贝
        return *this;
    }
    
    // 公共接口
    int getSize() const {
        return size;
    }
    
    bool isEmpty() const {
        return size == 0;
    }
    
    void insertHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = head->next;
        head->next = newNode;
        size++;
    }
    
    bool removeHead(int& val) {
        if (isEmpty()) return false;
        Node* toDelete = head->next;
        val = toDelete->data;
        head->next = toDelete->next;
        delete toDelete;
        size--;
        return true;
    }
    
    void printList() const {
        Node* current = head->next;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << " -> ";
            current = current->next;
        }
        cout << "[size=" << size << "]" << endl;
    }
};

int main() {
    LinkedList list;
    cout << "After init: " << endl;
    cout << "  size=" << list.getSize() << ", empty=" << list.isEmpty() << endl;
    
    cout << "Insert 10 at head: " << endl;
    list.insertHead(10);
    list.printList();
    
    cout << "Insert 20 at head: " << endl;
    list.insertHead(20);
    list.printList();
    
    cout << "Remove from head: " << endl;
    int removedVal;
    if (list.removeHead(removedVal)) {
        cout << "Removed: " << removedVal << endl;
    }
    list.printList();
    
    return 0;
}
```

### 3.2 实现要求

1. **构造函数**：必须用 `head = new Node(0)` 立哨兵，`size = 0`；不能留空，不能使用 `NULL` 初始化 `head`。
2. **析构函数**：必须用循环或递归从头遍历链表，每个结点用 `delete` 释放，最后用 `delete head` 释放哨兵节点。**切记**：只 free/p free 是 C 语言的做法，C++ 必须用 `delete`。
3. **拷贝构造函数**：必须进行**深拷贝**。遍历原链表，为每个结点分配新内存 `new Node(data)`，链接起来。注意：`head` 也需要被深拷贝。
4. **拷贝赋值运算符**：必须先检查 `this != &other`，再释放原有的所有结点（包括头节点），然后进行深拷贝。返回 `*this`。
5. **公有接口**：`insertHead`、`removeHead`、`printList`、`getSize`、`isEmpty` 原样保留，实现 logic 由学生编写。
6. **只能包含 `<iostream>`**；不得使用 C 的 `<stdlib.h>`/`<malloc.h>`，不得使用 `free`，必须用 `delete` 配对 `new`。
7. **程序健壮性**：删除空链表不崩溃，removeHead 返回 false 不修改输出参数。

### 3.3 统一 main 函数

把下面代码**原样**放在所有函数之后。

```cpp
/* 测试 main 函数，仅作演示，正确性不代表测试用例 */
int main(void) {
    LinkedList list;
    /* 以下测试代码由阅卷教师提供，学生只需保证类的实现正确即可 */
    LinkedList list2 = list;  // 测试拷贝构造
    list2.printList();
    
    LinkedList list3;
    list3 = list;  // 测试拷贝赋值
    list3.printList();
    
    return 0;
}
```

### 3.4 期望行为与核对重点

```text
After init: size=0, empty=true

Insert 10 at head: 
10 [size=1]

Insert 20 at head: 
20 -> 10 [size=2]

Remove from head: 
Removed: 20
10 [size=1]

After destroy: destructor automatically called, memory freed
```

**核对重点**：

- 析构函数中没有内存泄漏：`listDestroy`（或对应的 C++ 析构）打印的释放节点数应正确（含哨兵或不含，取决于设计）。
- 拷贝构造后，`list2` 与 `list` 互不影响，修改一个不影响另一个。
- 拷贝赋值后，`list3` 内容等于 `list`。
- **致命错误**：析构函数中只删除了某些结点但没删除头节点，或者只 free 不 delete，或者拷贝时浅拷贝导致两个对象共享同一内存。

---

## 四、提交要求

将本文件复制到自己的 `学号姓名/Lab7/Lab7.md`，填写选择题答案和实现要点。最终只提交以下 **4 个文件**：

```text
学号姓名/
└── Lab7/
    ├── CMakeLists.txt
    ├── linkedlist_cpp.cpp
    └── Lab7.md
```

特别注意：

- `CMakeLists.txt` 必须包含 `lab7_list` 一个目标，源文件为 `linkedlist_cpp.cpp`。
- `linkedlist_cpp.cpp` 必须是完整的 C++ 程序，包含框架里的全部函数和本文给出的 original `main`，不能只提交增量片段。
- `Lab7.md` 必须保留题目结构，填写实现要点和五法则表格。
- `linkedlist_cpp.cpp` 和 `Lab7.md` 的文件名大小写必须完全一致。
- 不要提交整个 CLion 项目、`cmake-build-*`、`.idea/`、可执行文件或其他编译产物。

---

## 五、截止时间

**2026 年 9 月 28 日 24:00**（即 2026 年 9 月 29 日 00:00，北京时间）

以 GitHub 记录的最后一次向 PR 推送代码的时间为准。不晚于上述时刻创建 PR 并完成最后一次推送不算超时；超过该时刻新建 PR，或向已有 PR 推送任何修改，均算超时。审核未通过的同学请在截止前完成修改。