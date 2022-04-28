#ifndef __CAP241_STACK_HPP__
#define __CAP241_STACK_HPP__

// C++ Standard Library
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>

template <class T>
class stack
{
public:
  
  stack();
  
  ~stack();
  
  void push(const T& elem);
 
  void pop();
 
  T top() const;
 
  bool empty() const;
 
  std::size_t size() const;
  
private:
  
// no copy allowed
  stack(const stack&);
  stack& operator=(const stack&);

  private:
  
    std::unique_ptr<T[]> elements_;
    std::size_t top_;
    std::size_t size_;
};

template<class T>
stack<T>::stack()
  : elements_(nullptr),
    top_(0),
    size_(0)
{
  elements_.reset(new T[2]);
 
  assert(elements_ != nullptr);
 
  size_ = 2;
}

template<class T>
stack<T>::~stack()
{
}

template<class T>
void stack<T>::push(const T& elem)
{
  ++top_;
 
  if(top_ > size_)
  {
    std::size_t new_size = 5 + size_;
    
    std::unique_ptr<T[]> tmp(new T[new_size]);

    std::copy(elements_.get(), elements_.get() + top_ - 1, tmp.get());
    
    std::swap(elements_, tmp);
  }
 
  elements_[top_ - 1] = elem;
}

template<class T> inline
void stack<T>::pop()
{
  assert(top_ > 0);

  --top_;
}

template<class T> inline
T stack<T>::top() const
{
  assert(top_ > 0);

  return elements_[top_ - 1];
}

template<class T> inline
bool stack<T>::empty() const
{
  return top_ == 0;
}

template<class T> inline
std::size_t stack<T>::size() const
{
  return top_;
}

#endif // __CAP241_STACK_HPP__