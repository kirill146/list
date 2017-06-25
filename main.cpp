#include <iostream>
#include "list.h"
using namespace std;

template <typename T>
void print(list<T> const& a) {
    for (typename list<T>::const_iterator it = a.begin(); it != a.end(); it++) {
        cout << *it << ' ';
    }
    cout << endl;
}

template <typename T>
void print_reverse(list<T> const& a) {
    for (typename list<T>::const_reverse_iterator it = a.rbegin(); it != a.rend(); it++) {
        cout << *it << ' ';
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
    print_reverse(a);
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

void T7() {
    list<string> a;
    a.push_front("hello");
    a.push_back("world");
    print(a); // hello world
    list<string>::iterator it = a.begin();
    it++;
    a.erase(it);
    print(a); // hello
    a.push_back("world");
    it = a.end();
    it--;
    list<string> b;
    b.push_back("abacaba");
    b.push_back("abracadabra");
    print(b); // abacaba abracadabra
    b.push_back("avadakedavra");
    list<string>::iterator jt = b.end();
    jt--;
    a.splice(it, b, b.begin(), jt);
    print(a); // hello abacaba abracadabra world
    print(b); // avadakedavra
    cout << "------------------------\n";
}

void T8() {
    list<int> a;
    for (int i = 1; i <= 4; i++) {
        a.push_back(i);
    }
    list<int> b;
    for (int i = 5; i <= 8; i++) {
        b.push_back(i);
    }
    a = b;
    print(a);
    print(b);
    cout << "------------------------\n";
}

void T9() {
    list<int> a;
    list<int> b;
    b.push_back(1);
    b.push_back(2);
    a.splice(a.begin(), b, b.begin(), b.end());
    print(a);
    print(b);
    print_reverse(a);
    print_reverse(b);
    cout << "------------------------\n";
}

void T10() {
    list<int> a;
    list<int>::iterator i1 = a.begin();
    list<int>::const_iterator i2 = a.begin();
    i1 == i2;
    i1 != i2;
    cout << "------------------------\n";
}

void T11() {
    list<int> a;
    list<int> b;
    a.push_back(1);
    a.push_back(2);
    a.splice(a.begin(), b, b.begin(), b.end());
    print(a);
    print(b);
    print_reverse(a);
    print_reverse(b);
    cout << "------------------------\n";
}

void T12() {
    list<int> a;
    list<int> b;
    for (int i = 0; i < 4; i++) {
        a.push_back(i);
    }
    swap(a, b);
    print(a);
    print(b);
    cout << a.empty() << ' ' << b.empty() << endl;
    a.clear();
    b.clear();
    swap(a, b);
    print(a);
    print(b);
    cout << a.empty() << ' ' << b.empty() << endl;
    b.push_back(42);
    swap(a, b);
    print(a);
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
    T7();
    T8();
    T9();
    T10();
    T11();
    T12();
    return 0;
}