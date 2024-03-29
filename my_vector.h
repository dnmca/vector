//
// Created by dinamic on 11/4/18.
//

#include <stdexcept>
#include <iostream>
#include <cstddef> //! OF: для size_t

#ifndef PROJECT_MY_VECTOR_H
#define PROJECT_MY_VECTOR_H

template<typename T>
class my_vector {
public:

    // typedef unsigned int size_t; //!: OF Plain wrong.
    using size_t = std::size_t; //! OF: If you insist... Але краще по іншому назвати.
    typedef T* iterator;

    // constructors

    my_vector();
    my_vector(size_t n, const T &value);
    my_vector(iterator begin, iterator end); //! OF: В тілі шаблона my_vector<T>:: є синонімом просто  my_vector::
    my_vector(std::initializer_list<T> list);

    my_vector(const my_vector<T>& obj);
    my_vector(my_vector<T>&& obj) noexcept;

    ~my_vector();

    // assignment operations

    my_vector<T>& operator=(const my_vector<T>& obj);
    my_vector<T>& operator=(my_vector<T>&& obj);

    // indexing

    T& operator[](size_t index) noexcept;
    const T& operator[](size_t index) const noexcept;
    T& at(size_t index);
    const T& at(size_t index) const;
    T& front() noexcept;
    const T& front() const noexcept;
    T& back() noexcept;
    const T& back() const noexcept;

    // iterators

    iterator begin() noexcept;
    iterator end() noexcept;
    const iterator cbegin() const noexcept;
    const iterator cend() const noexcept;
    std::reverse_iterator<iterator> rbegin();
    std::reverse_iterator<iterator> rend();
    std::reverse_iterator<const iterator> rcbegin() const;
    std::reverse_iterator<const iterator> rcend() const;

    // size manipulations

    bool is_empty() const noexcept;
    size_t size() const noexcept;
    size_t capacity() const noexcept;
    void shrink_to_fit();
    void reserve(size_t n);

    // modifications

    void swap(my_vector<T> &that);
    void resize(size_t new_size);
    void clear();

    iterator insert(const iterator target, const T &value);
    iterator insert(const iterator target, iterator begin, iterator end);
    iterator erase(const iterator target, const T &value); //! OF: а є її та наступної тести?
    iterator erase(iterator begin, iterator end);

    void pop_back();
    void push_back(const T &elem);
    template<class ... Args> void emplace_back(Args &&... args);

    // operators overloading

    bool operator==(const my_vector<T> &other) const;
    bool operator!=(const my_vector<T> &other) const;
    bool operator<(const my_vector<T> &other) const;
    bool operator<=(const my_vector<T> &other) const;
    bool operator>(const my_vector<T> &other) const;
    bool operator>=(const my_vector<T> &other) const;

private:
    size_t v_size = 0;
    size_t v_capacity = 1;
    T *array;
};

template<typename T>
my_vector<T>::my_vector() {
    array = new T[v_capacity];
}

template<typename T>
my_vector<T>::my_vector(my_vector::size_t n, const T &value) {
    v_capacity = 2 * n;
    array = new T[v_capacity];
    for (size_t i = 0; i < n; ++i) {
        *(array + i) = value;
    }
    v_size = n;
}

// TODO: Fix

template<typename T>
my_vector<T>::my_vector(typename my_vector<T>::iterator begin, typename my_vector<T>::iterator end) {
    size_t n = end - begin;
    v_capacity = 2 * n;
    array = new T[v_capacity];
    for (size_t i = 0; i < n; ++i, ++begin) {
        *(array + i) = *begin;
    }
    v_size = n;
}

template<typename T>
my_vector<T>::my_vector(std::initializer_list<T> list) {
    v_capacity = 2 * list.size();
    array = new T[v_capacity];
    for(const T& x : list){
        *(array + v_size) = x;
        v_size++;
    }
}

template<typename T>
my_vector<T>::~my_vector() {
    delete[] array;
}

template<typename T>
my_vector<T>::my_vector(const my_vector<T> &obj) {
    v_capacity = obj.v_capacity;
    array = new T[v_capacity];
    for (size_t i = 0; i < obj.v_size; ++i) {
        *(array + i) = *(obj.array + i);
    }
    v_size = obj.v_size;
}

template<typename T>
my_vector<T>::my_vector(my_vector<T> &&obj) noexcept {
//! OF: Plain wrong: тут слід перемістити вказівник на блок і розміри, а не робити те, що компілятор і сам здогадається.
//! OF: Якщо не зрозуміло, про що мова -- звертайтеся на парі.
//! OF: Так ще й про noexcept за поточної реалізації Ви обманюєте!
    v_capacity = obj.v_capacity;
    array = new T[v_capacity];
    for (size_t i = 0; i < obj.v_size; ++i) {
        *(array + i) = std::move(*(obj.array + i));
    }
    v_size = obj.v_size;
}

template<typename T>
T &my_vector<T>::operator[](my_vector::size_t index) noexcept {
    return *(array + index);
}

template<typename T>
const T &my_vector<T>::operator[](my_vector::size_t index) const noexcept {
    return *(array + index);
}

template<typename T>
T &my_vector<T>::at(my_vector::size_t index) {
    if (index >= v_size || index < 0) {
        throw std::out_of_range("No such index!");
    } else {
        return *(array + index);
    }
}

template<typename T>
const T &my_vector<T>::at(my_vector::size_t index) const {
    if (index >= v_size || index < 0) {
        throw std::out_of_range("No such index!");
    } else {
        return *(array + index);
    }
}

template<typename T>
T &my_vector<T>::front() noexcept {
    return *array;
}

template<typename T>
const T &my_vector<T>::front() const noexcept{
    return *array;
}

template<typename T>
T &my_vector<T>::back()  noexcept{
    return *(array + v_size - 1);
}

template<typename T>
const T &my_vector<T>::back() const noexcept{
    return *(array + v_size - 1);
}

template<typename T>
typename my_vector<T>::iterator my_vector<T>::begin() noexcept {
    return array;
}

template<typename T>
typename my_vector<T>::iterator const my_vector<T>::cbegin() const noexcept {
    return array;
}

template<typename T>
typename my_vector<T>::iterator my_vector<T>::end() noexcept {
    return array + v_size;
}

template<typename T>
typename my_vector<T>::iterator const my_vector<T>::cend() const noexcept {
    return array + v_size;
}

template<typename T>
std::reverse_iterator<typename my_vector<T>::iterator> my_vector<T>::rbegin() {
    return std::reverse_iterator<my_vector::iterator>(array + v_size);
}

template<typename T>
std::reverse_iterator<typename my_vector<T>::iterator> my_vector<T>::rend()  {
    return std::reverse_iterator<iterator>(array);
}

//////////////////////////////////////////////////////////////////////////////
//                 CURRENTLY DOESN'T WORK AS EXPECTED                       //
//////////////////////////////////////////////////////////////////////////////

template<typename T>
std::reverse_iterator<typename my_vector<T>::iterator const> my_vector<T>::rcbegin() const {
    return std::reverse_iterator<my_vector::iterator>(array + v_size);
}

template<typename T>
std::reverse_iterator<typename my_vector<T>::iterator const> my_vector<T>::rcend() const {
    return std::reverse_iterator<my_vector::iterator>(array);
}

//////////////////////////////////////////////////////////////////////////////


template<typename T>
bool my_vector<T>::is_empty() const noexcept {
    return v_size == 0;
}

template<typename T>
typename my_vector<T>::size_t my_vector<T>::size() const noexcept{
    return v_size;
}

template<typename T>
typename my_vector<T>::size_t my_vector<T>::capacity() const noexcept {
    return v_capacity;
}

template<typename T>
void my_vector<T>::shrink_to_fit() {
    //! OF: Ймовірно, варто спершу перевірити -- раптом розмір вже правильний.
    //! OF: Операція, все ж, дорога...
    T *dest = new T[v_size];
    for (size_t i = 0; i < v_size; ++i) {
        *(dest + i) = *(array + i);
    }
    delete[] array;
    v_capacity = v_size; //! OF: Безпечніше щод овиключень це робити тут
    array = dest;
}

template<typename T>
void my_vector<T>::reserve(my_vector::size_t n) {
    if (n > v_capacity) {
        T *dest = new T[n];
        for (size_t i = 0; i < v_size; ++i) {
            *(dest + i) = *(array + i);
        }
        delete[] array;
        v_capacity = n; //! OF: Безпечніше щод овиключень це робити тут
        array = dest;
    }
}

template<typename T>
void my_vector<T>::swap(my_vector<T> &that) {
    //! OF: Або std::swap -- це лаконічніше.
    size_t tmp_size = v_size;
    size_t tmp_capacity = v_capacity;
    T *temp = array;

    v_size = that.v_size;
    v_capacity = that.v_capacity;
    array = that.array;

    that.v_size = tmp_size;
    that.v_capacity = tmp_capacity;
    that.array = temp;
}

// TODO: Fix bug with destruction of separate elements data[i].~T();
//! OF: Ми з Вами обговорювали проблему тут! В конструкторах Ви ці об'єкти створюєте,
//! OF: в дестркторі знищуєте, але і тут знищуєте. Цей код треба впорядкувати!
template<typename T>
void my_vector<T>::resize(my_vector::size_t new_size) {
    if (new_size > v_size) {
        reserve(new_size);
    } else {
        for (size_t i = new_size; i < v_size; ++i) {
//            *(array + i).~T();
            array[i].~T();
        }
    }
    v_size = new_size;
}

template<typename T>
void my_vector<T>::clear() {
    for (size_t i = 0; i < v_size; ++i) {
//        *(array + i).~T();
        array[i].~T();
    }
    v_size = 0;
}


//////////////////////////////////////////////////////////////////////
//                          NOT DONE YET                            //
//////////////////////////////////////////////////////////////////////

template<typename T>
typename my_vector<T>::iterator my_vector<T>::insert(my_vector::iterator const target, const T &value) {
    return nullptr;
}

template<typename T>
typename my_vector<T>::iterator
my_vector<T>::insert(my_vector::iterator const target, my_vector::iterator begin, my_vector::iterator end) {
    return nullptr;
}

template<typename T>
typename my_vector<T>::iterator my_vector<T>::erase(my_vector::iterator const target, const T &value) {
    return nullptr;
}

template<typename T>
typename my_vector<T>::iterator my_vector<T>::erase(my_vector::iterator begin, my_vector::iterator end) {
    return nullptr;
}

/////////////////////////////////////////////////////////////////////

template<typename T>
void my_vector<T>::pop_back() {
//    *(array + v_size - 1).~T();
    array[v_size - 1].~T();
    --v_size;

}


// TODO: Fix v.push_back(v[5]) BUG !!!


template<typename T>
void my_vector<T>::push_back(const T &elem) {
    //! OF: той, доволі складний код, краще не дублювати, а написати раз та повторно використовувати!
    if (v_size == v_capacity) {
        T *neu = new T[2 * v_capacity];
        for (size_t i = 0; i < v_size; ++i) {
            *(neu + i) = *(array + i);
        }
        delete[] array;
        v_capacity = 2 * v_capacity;
        array = neu;
    }
    *(array + v_size) = elem;
    ++v_size;
}

template<typename T>
template<class... Args>
void my_vector<T>::emplace_back(Args &&... args) {
    //! OF: див. комент до попереднього!
    if (v_size == v_capacity) {
        v_capacity = 2 * v_capacity;
        T *neu = new T[v_capacity];
        for (size_t i = 0; i < v_size; ++i) {
            *(neu + i) = *(array + i);
        }
        delete[] array;
        array = neu;
    }
    *(array + v_size) = std::move(T(std::forward<Args>(args)...));
    ++v_size;
}

template<typename T>
bool my_vector<T>::operator==(const my_vector<T> &other) const {
    if (v_size != other.v_size) return false;
    for (size_t i = 0; i < v_size; ++i) {
        if (*(array + i) != *(other.array + i)) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool my_vector<T>::operator!=(const my_vector<T> &other) const {
    if (v_size != other.v_size) return true;
    for (size_t i = 0; i < v_size; ++i) {
        if (*(array + i) != *(other.array + i)) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool my_vector<T>::operator<(const my_vector<T> &other) const {
    size_t min = v_size < other.v_size ? v_size : other.v_size;
    for (size_t i = 0; i < min; ++i) {
        if (*(array + i) != *(other.array + i)) {
            return *(array + i) < *(other.array + i);
        }
    }
    return v_size < other.v_size;
}

template<typename T>
bool my_vector<T>::operator<=(const my_vector<T> &other) const {
    size_t min = v_size < other.v_size ? v_size : other.v_size;
    for (size_t i = 0; i < min; ++i) {
        if (*(array + i) != *(other.array + i)) {
            return *(array + i) < *(other.array + i);
        }
    }
    return v_size <= other.v_size;
}

template<typename T>
bool my_vector<T>::operator>(const my_vector<T> &other) const {
    size_t min = v_size < other.v_size ? v_size : other.v_size;
    for (size_t i = 0; i < min; ++i) {
        if (*(array + i) != *(other.array + i)) {
            return *(array + i) > *(other.array + i);
        }
    }
    return v_size > other.v_size;
}

template<typename T>
bool my_vector<T>::operator>=(const my_vector<T> &other) const {
    size_t min = v_size < other.v_size ? v_size : other.v_size;
    for (size_t i = 0; i < min; ++i) {
        if (*(array + i) != *(other.array + i)) {
            return *(array + i) > *(other.array + i);
        }
    }
    return v_size >= other.v_size;
}

// TODO: Memory leak !!!

// TODO: Can be done using swap

template<typename T>
my_vector<T> &my_vector<T>::operator=(const my_vector<T> &obj) {
    T* tmp = new T[obj.v_capacity];
    for (size_t i = 0; i < obj.v_size; ++i) {
        *(tmp + i) = *(obj.array + i);
    }
    delete [] array;
    array = tmp;
    v_capacity = obj.v_capacity; //! OF: Тут воно безпечніше.
    v_size = obj.v_size;
    return *this; //! OF: BUG was here -- forgot return!
}

template<typename T>
my_vector<T> &my_vector<T>::operator=(my_vector<T> &&obj) {
//! OF: Plain wrong: тут слід перемістити вказівник на блок і розміри, а не робити те, що компілятор і сам здогадається.
//! OF: Якщо не зрозуміло, про що мова -- звертайтеся на парі.
    v_capacity = obj.v_capacity;
    T* tmp = new T[v_capacity];
    for (size_t i = 0; i < obj.v_size; ++i) {
        *(tmp + i) = std::move(*(obj.array + i));
    }
    delete [] array;
    array = tmp;
    v_size = obj.v_size;
    return *this; //! OF: BUG was here -- forgot return!
}




#endif //PROJECT_MY_VECTOR_H
