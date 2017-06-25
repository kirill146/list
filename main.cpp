#include <iostream>
#include "list.h"
using namespace std;

template <typename T>
void print(list<T> const& a) {
    typename list<T>::node_base* cur_node = a.fake_node.next;
    while (cur_node != &a.fake_node) {
        cout << static_cast<typename list<T>::node*>(cur_node)->data << ' ';
        cur_node = cur_node->next;
    }
    cout << endl;
}

template <typename T>
void print_reverse(list<T> const& a) {
    typename list<T>::node_base* cur_node = a.fake_node.prev;
    while (cur_node != &a.fake_node) {
        cout << static_cast<typename list<T>::node*>(cur_node)->data << ' ';
        cur_node = cur_node->prev;
    }
    cout << endl;
}

void T1() {
    list<int> a;
    a.push_back(100);
    a.push_back(200);
    a.push_back(300);
    print(a);
    a.pop_back();
    print(a);
    a.pop_front();
    print(a);
    a.push_front(400);
    print(a);
    a.push_back(500);
    print(a);
    cout << "------------------------\n";
}

void T2() {
    list<int> a;
    a.push_back(100);
    a.push_back(200);
    a.push_back(300);
    print(a);
    list<int>::iterator it = a.begin();
    *it = 600;
    it = a.end();
    it--;
    *it = 700;
    print(a);
    cout << "------------------------\n";
}

void T3() {
    list<int> a;
    for (int i = 0; i < 10; i++) {
        a.push_back(i);
    }
    for (list<int>::reverse_iterator it = a.rbegin(); it != a.rend(); it++) {
        cout << *it << ' ';
    }
    cout << endl;
    cout << "------------------------\n";
}

void T4() {
    list<int> a;
    for (int i = 0; i < 10; i++) {
        a.push_back(i);
    }
    a.erase(a.begin());
    list<int>::iterator it = a.begin();
    it++;
    it++;
    it = a.erase(it);
    a.insert(it, 100);
    print(a);
    cout << "------------------------\n";
}

void T5() {
    list<int> a;
    for (int i = 0; i < 10; i++) {
        a.push_back(i);
    }
    list<int>::iterator it = a.begin();
    it++;
    list<int>::iterator jt = a.end();
    jt--;
    jt--;
    a.erase(it, jt);
    print(a);
    cout << "------------------------\n";
}

void T6() {
    list<int> a;
    for (int i = 0; i < 10; i++) {
        a.push_back(i);
    }
    list<int>::iterator it = a.begin();
    it++;
    it++;
    list<int>::iterator jt = a.end();
    jt--;
    jt--;
    list<int> b;
    for (int i = 0; i < 5; i++) {
        b.push_back(i * 100);
    }
    list<int>::iterator kt = b.begin();
    kt++;
    kt++;
    b.splice(kt, a, it, jt);
    print(a); // 0 1 8 9
    print(b); // 0 100 2 3 4 5 6 7 200 300 400
    print_reverse(a);
    print_reverse(b);
    a.clear();
    print(a);
    a.push_front(100500);
    print(a);
    b.clear();
    b.insert(b.begin(), 12345);
    print(b);
    cout << "------------------------\n";
}

int main() {
    T1();
    T2();
    T3();
    T4();
    T5();
    T6();
    return 0;
}