#include "listNode.h"
#include "list.h"
#include <iostream>

using namespace std;

int main() {
    List<int> L;
    
    cout << "初始化后: " << L.size() << " 个元素，" << (L.empty() ? "空表" : "非空表") << endl;
    
    cout << "插入元素: " << endl;
    L.insertAsSucc(10);
    L.insertAsSucc(20);
    L.insertAsSucc(30);
    cout << "当前规模: " << L.size() << endl;
    L.output();
    
    cout << "删除第2个元素: " << endl;
    L.remove(L.header()->succ);
    cout << "删除后规模: " << L.size() << endl;
    L.output();
    
    cout << "清空列表: " << endl;
    L.clear();
    cout << "清空后规模: " << L.size() << ", " << (L.empty() ? "空表" : "非空表") << endl;
    
    cout << "Lab7 测试完成!" << endl;
    
    return 0;
}