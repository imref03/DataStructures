#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Vector {
public:
    class ConstIterator;
    class Iterator;
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = Vector::Iterator;
    using const_iterator = Vector::ConstIterator;
private:
    T* values;
    size_t sz;
    size_t max_sz;
public:
    Vector () : sz(0), max_sz(0), values(nullptr) {}
    Vector (initializer_list<T> ls) {
        sz = ls.size();
        max_sz = sz;
        try {
            values = new T[sz];
            copy(ls.begin(),ls.end(),values);
        }
        catch (const bad_alloc& b) {
            throw runtime_error("Initializer list constructor failed to allocate new speicher");
        }

    }
    Vector (size_t n) : sz(0), max_sz(n), values(nullptr) {
        try {
            values = new T[max_sz];
        } catch (const exception& e) {
            throw runtime_error("constructor failed to allocate memory");
        }        
    }
    Vector (const Vector& o) {
        sz = o.size();
        max_sz = o.capacity();
        try {
            values = new T[max_sz];
            copy(o.values, o.values + sz, values);
        } catch (const bad_alloc& b) {
            throw runtime_error("Copy constructor new alloc failed");
        }
    }
    ~Vector() {
        delete[] values;
        values = nullptr;
        sz = 0;
        max_sz = 0;
    }
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        Vector temp(other);
        swap(values,temp.values);
        swap(sz,temp.sz);
        swap(max_sz, temp.max_sz);
        return *this;
    }
    size_t capacity () const {
        return max_sz;
    }
    void reserve (size_t t) {
        if (t <= max_sz) {
            return;
        }
        T* new_values = nullptr;
        try {
            new_values = new T[t];
            for (size_t i=0;i<sz;i++) {
                new_values[i] = values[i];
            }
        } catch (const exception& e) {
            delete[] new_values;
            throw runtime_error("reserve() failed to allocate memory");
        }
        delete[] values;
        values = new_values;
        max_sz = t;
    }
    void shrink_to_fit () {
        if (sz >= max_sz) {
            return;
        }
        T* new_values = nullptr;
        try {
            new_values = new T[sz];
            for (size_t i=0;i<sz;i++) {
                new_values[i] = values[i];
            }
        } catch (const exception& e) {
            throw runtime_error("shrinktofit failed to allocate memory");
        }
        delete[] values;
        values = new_values;
        max_sz = sz;
    }
    size_t size() const {
        return sz;
    }
    bool empty() const {
        return sz == 0;
    }
    void push_back(T x) {
        if (max_sz == 0) {
            max_sz = 1;
            T* new_values = nullptr;
            try {
                new_values = new T[max_sz];
            } catch (const bad_alloc& b) {
                throw runtime_error("bad alloc push back");
            }
            delete[] values;
            values = new_values;
        }
        if (sz == max_sz) {
            reserve(max_sz*2);
        }
        values[sz] = x;
        sz++;
    }
    void pop_back() {
        if (sz == 0) {
            throw runtime_error("vector empty");
        }
        else {
            sz = sz - 1;
        }
    }
    T& operator[](size_t t) {
        if (t < sz) {
            return values[t];
        }
        else {
            throw runtime_error("invalid value");
        }
    }
    const T& operator[](size_t t) const {
        if (t < sz) {
            return values[t];
        }
        else {
            throw runtime_error("invalid value");
        }
    }
    void clear() {
        sz = 0;
    }
    friend ostream& operator<<(ostream& o, const Vector& v) {
        bool first{true};
        o << "[";
        for (size_t i=0;i<v.sz;i++) {
            if (first) {
                o << v.values[i];
                first = false;
            }
            else {
                o << ", ";
                o << v.values[i];
            }
        }
        o << "]";
        return o;
    }
    class Iterator {
    public:
        using value_type = Vector::value_type;
        using reference = Vector::reference;
        using pointer = Vector::pointer;
        using difference_type = Vector::difference_type;
        using iterator_category = std::forward_iterator_tag;
    private:
        pointer ptr;
    public:
        friend class ConstIterator;
        friend class Vector;
        Iterator () {
            ptr = nullptr;
        }
        Iterator (T* ptr) {
            if (ptr == nullptr) {
                throw runtime_error("constructor nullptr");
            }
            this->ptr = ptr;
        }
        reference operator*() const {
            if (ptr == nullptr) {
                throw runtime_error("nullptr reference");
            }
            return *ptr;
        }
        pointer operator->() const {
            if (ptr == nullptr) {
                throw runtime_error("nullptr");
            }
            return ptr;
        }
        iterator& operator++() {
            ++ptr;
            return *this;
        }
        iterator operator++(int) {
            iterator old = *this;
            ++*this;
            return old;
        }
        operator const_iterator() const {
            if (this->ptr == nullptr) {
                throw runtime_error("can't convert nullptr");
            }
            return ConstIterator(this->ptr);
        }
        bool operator==(const iterator& o) const {
            return this->ptr == o.ptr;
        }
        bool operator!=(const iterator& o) const {
            return this->ptr != o.ptr;
        }
        bool operator==(const const_iterator& o) const {
            return this->ptr == o.ptr;
        }
        bool operator!=(const const_iterator& o) const {
            return this->ptr != o.ptr;
        }
    };

    class ConstIterator {
    public:
        using value_type = Vector::value_type;
        using reference = Vector::const_reference;
        using pointer = Vector::const_pointer;
        using difference_type = Vector::difference_type;
        using iterator_category = std::forward_iterator_tag;
    private:
        const_pointer ptr;
    public:
        friend class Iterator;
        friend class Vector;
        ConstIterator () {
                ptr = nullptr;
        }
        ConstIterator (pointer ptr) {
            this->ptr = ptr;
        }
        reference operator*() const {
            if (ptr == nullptr) {
                throw runtime_error("operator* references nullptr!");
            }
            return *ptr;
        }
        pointer operator->() const {
            if (ptr == nullptr) {
                throw runtime_error("nullptr!");
            }
            return ptr;
        }
        const_iterator& operator++() {
            ptr++;
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator old = *this;
            ++*this;
            return old;             
        }
        bool operator==(const const_iterator& o) const {
            return this->ptr == o.ptr;
        }
        bool operator!=(const const_iterator& o) const {
            return this->ptr != o.ptr;
        }
        bool operator==(const iterator& o) const {
            return this->ptr == o.ptr;
        }
        bool operator!=(const iterator& o) const {
            return this->ptr != o.ptr;
        }
        friend Vector::difference_type operator-(const Vector::ConstIterator& lop, const Vector::ConstIterator& rop) {
            return lop.ptr - rop.ptr;
        }
    };
    iterator begin() {
        return iterator(values);
    }
    iterator end() {
        return iterator(values + sz);
    }
    const_iterator begin() const {
        return const_iterator(values);
    }
    const_iterator end() const {
        return const_iterator(values + sz);
    }
    iterator insert(const_iterator pos, const_reference val) {
        auto diff = pos - begin();
        if (diff < 0 || static_cast<size_type>(diff) > sz)
            throw std::runtime_error("Iterator out of bounds");
        size_type current = static_cast<size_type>(diff);
        if (sz >= max_sz)
            reserve(max_sz * 2);
        if (max_sz == 0) {
            reserve(1);
        }
        for (auto i{sz}; i-->current;)
            values[i + 1] = values[i];
        values[current] = val;
        ++sz;
        return iterator{values + current};
    }
    iterator erase(const_iterator pos) {
        auto diff = pos - begin();
        if (diff < 0 || static_cast<size_type>(diff) >= sz)
            throw std::runtime_error("Iterator out of bounds");
        size_type current{static_cast<size_type>(diff)};
        for (auto i{current}; i < sz - 1; ++i)
            values[i] = values[i + 1];
        --sz;
        return iterator{values + current};
    }
};

#endif
