//
// Created by drxu on 25.06.2017.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

template <typename T>
struct list {
private:
    struct node_base {
        node_base *prev, *next;
        node_base()
                : prev(this)
                , next(this) {}
    };

    struct node : public node_base {
        T data;
        node(T const& elem, node_base* prev, node_base* next) {
            this->data = elem;
            this->prev = prev;
            this->next = next;
        }
    };
public:
    struct const_iterator;
    struct iterator {
        friend list;
        friend const_iterator;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::bidirectional_iterator_tag iterator_category;
    private:
        node_base* p;
        iterator(node_base*);
    public:
        iterator(const_iterator it);
        iterator& operator++();
        iterator& operator--();
        iterator operator++(int);
        iterator operator--(int);
        T& operator*();

        friend bool operator==(list<T>::iterator const& a, list<T>::iterator const& b) {
            return a.p == b.p;
        }

        friend bool operator!=(list<T>::iterator const& a, list<T>::iterator const& b) {
            return a.p != b.p;
        }
    };

    struct const_iterator {
        friend list;
        friend iterator;
        typedef T const value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T const* pointer;
        typedef T const& reference;
        typedef std::bidirectional_iterator_tag iterator_category;
    private:
        node_base* p;
        const_iterator(node_base*);
    public:
        const_iterator(iterator it);
        const_iterator& operator++();
        const_iterator& operator--();
        const_iterator operator++(int);
        const_iterator operator--(int);
        T const& operator*();

        friend bool operator==(list<T>::const_iterator const& a, list<T>::const_iterator const& b) {
            return a.p == b.p;
        }

        friend bool operator!=(list<T>::const_iterator const& a, list<T>::const_iterator const& b) {
            return a.p != b.p;
        }
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


    mutable node_base fake_node;

    list();
    list(list const&);
    ~list();
    list& operator=(list const& other);
    bool empty() const;
    void clear();
    void push_back(T const&);
    void pop_back();
    T& back();
    T const& back() const;
    void push_front(T const&);
    void pop_front();
    T& front();
    T const& front() const;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    iterator insert(const_iterator, T const&);
    iterator erase(const_iterator);
    iterator erase(const_iterator first, const_iterator last);
    void splice(const_iterator pos, list& other, const_iterator first, const_iterator last);
    void swap(list& other);
};

template <typename T>
list<T>::iterator::iterator(list::node_base* p)
        :p(p)
{}

template <typename T>
list<T>::iterator::iterator(list::const_iterator it) {
    p = it.p;
}

template <typename T>
typename list<T>::iterator& list<T>::iterator::operator++() {
    p = p->next;
    return *this;
}

template <typename T>
typename list<T>::iterator& list<T>::iterator::operator--() {
    p = p->prev;
    return *this;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator++(int) {
    iterator res(*this);
    ++*this;
    return res;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator--(int) {
    iterator res(*this);
    --*this;
    return res;
}

template <typename T>
T& list<T>::iterator::operator*() {
    return static_cast<node*>(p)->data;
}


template <typename T>
list<T>::const_iterator::const_iterator(list::iterator it) {
    p = it.p;
}

template <typename T>
list<T>::const_iterator::const_iterator(list::node_base* p)
        :p(p)
{}

template <typename T>
typename list<T>::const_iterator& list<T>::const_iterator::operator++() {
    p = p->next;
    return *this;
}

template <typename T>
typename list<T>::const_iterator& list<T>::const_iterator::operator--() {
    p = p->prev;
    return *this;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::operator++(int) {
    const_iterator res(*this);
    ++*this;
    return res;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::operator--(int) {
    const_iterator res(*this);
    --*this;
    return res;
}

template <typename T>
T const& list<T>::const_iterator::operator*() {
    return static_cast<node*>(p)->data;
}


template <typename T>
typename list<T>::iterator list<T>::begin() {
    return iterator(fake_node.next);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
    return iterator(&fake_node);
}

template <typename T>
typename list<T>::reverse_iterator list<T>::rbegin() {
    return reverse_iterator(end());
}

template <typename T>
typename list<T>::reverse_iterator list<T>::rend() {
    return reverse_iterator(begin());
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const {
    return const_iterator(fake_node.next);
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const {
    return const_iterator(&fake_node);
}

template <typename T>
typename list<T>::const_reverse_iterator list<T>::rbegin() const {
    return const_reverse_iterator(end());
}

template <typename T>
typename list<T>::const_reverse_iterator list<T>::rend() const {
    return const_reverse_iterator(begin());
}










template <typename T>
list<T>::list() {

}

template <typename T>
list<T>::list(list<T> const& other) {
    if (other.empty()) {
        return;
    }
    node_base* cur_node = &fake_node;
    node_base* other_cur_node = other.fake_node.next;
    node_base* new_node;
    while (other_cur_node != &other.fake_node) {
        new_node = new node(static_cast<node*>(other_cur_node)->data, cur_node, nullptr);
        cur_node->next = new_node;
        other_cur_node = other_cur_node->next;
        cur_node = new_node;
    }
    cur_node->next = &fake_node;
    fake_node.prev = cur_node;
}

template <typename T>
list<T>::~list() {
    clear();
}

template <typename T>
bool list<T>::empty() const {
    return fake_node.prev == &fake_node;
}

template <typename T>
void list<T>::clear() {
    iterator it(fake_node.next);
    while (it != end()) {
        it = erase(it);
    }
}

template <typename T>
void list<T>::swap(list<T>& other) {
    std::swap(fake_node, other.fake_node);
}

template <typename T>
list<T>& list<T>::operator=(list<T> const& other) {
    list<T> copy(other);
    swap(copy);
    return *this;
}

template <typename T>
void list<T>::push_back(const T& elem) {
    node_base* new_node = new node(elem, fake_node.prev, &fake_node);
    fake_node.prev->next = new_node;
    fake_node.prev = new_node;
}

template <typename T>
void list<T>::pop_back() {
    node_base* p = fake_node.prev;
    fake_node.prev = p->prev;
    p->prev->next = &fake_node;
    delete p;
}

template <typename T>
T& list<T>::back() {
    return static_cast<node*>(fake_node.prev)->data;
}

template <typename T>
T const& list<T>::back() const {
    return static_cast<node*>(fake_node.prev)->data;
}

template <typename T>
void list<T>::push_front(const T& elem) {
    node_base* new_node = new node(elem, &fake_node, fake_node.next);
    fake_node.next->prev = new_node;
    fake_node.next = new_node;
}

template <typename T>
void list<T>::pop_front() {
    node_base* p = fake_node.next;
    fake_node.next = p->next;
    p->next->prev = &fake_node;
    delete p;
}

template <typename T>
T& list<T>::front() {
    return static_cast<node*>(fake_node.next)->data;
}

template <typename T>
T const& list<T>::front() const {
    return static_cast<node*>(fake_node.next)->data;
}

template <typename T>
typename list<T>::iterator list<T>::insert(list<T>::const_iterator pos, T const& elem) {
    node_base* new_node = new node(elem, pos.p->prev, pos.p);
    pos.p->prev->next = new_node;
    pos.p->prev = new_node;
    return iterator(new_node);
}

template <typename T>
typename list<T>::iterator list<T>::erase(list<T>::const_iterator pos) {
    pos.p->next->prev = pos.p->prev;
    pos.p->prev->next = pos.p->next;
    iterator res(pos.p->next);
    delete pos.p;
    return res;
}

template <typename T>
typename list<T>::iterator list<T>::erase(const_iterator first, const_iterator last) {
    while (first != last) {
        first = erase(first);
    }
    return iterator(last);
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other, const_iterator first, const_iterator last) {
    first.p->prev->next = last.p;
    node_base* p = last.p->prev;
    last.p->prev = first.p->prev;
    p->next = pos.p;
    first.p->prev = pos.p->prev;
    pos.p->prev->next = first.p;
    pos.p->prev = p;
}

#endif //LIST_LIST_H
