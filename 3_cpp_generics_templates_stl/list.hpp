#ifndef __CAP241_LIST_HPP__
#define __CAP241_LIST_HPP__

// Biblioteca C Padrão
#include <cassert>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <type_traits>

template<class T> struct list_item
{
  list_item *prev;
  list_item *next;
  T value;
  
  list_item() : prev(this), next(this) { }
      
  list_item(list_item *p, list_item* n, const T& v)
    : prev(p), next(n), value(v)
  {
  }
};

template<class T>
class list_iterator
{
public:

  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef value_type& reference;
  typedef T* pointer;   // essa linha precisa de revisão
  typedef typename std::pointer_traits<pointer>::difference_type difference_type;
  
  list_iterator()
    : item_(nullptr)
  {
  }
  
  reference operator*() const
  {
    return item_->value;
  }

  pointer operator->() const
  {
    return std::pointer_traits<pointer>::pointer_to(item_->value);
  }
  
  list_iterator& operator++()
  {
    item_ = item_->next;
    
    return *this;
  }
  
  list_iterator operator++(int)
  {
    list_iterator tmp(*this);
    
     ++(*this);
    
    return tmp;
  }

  list_iterator& operator--()
  {
    item_ = item_->prev;
    
    return *this;
  }
  
  list_iterator operator--(int)
  {
    list_iterator tmp(*this);
    
     --(*this);
    
     return tmp;
  }
  
  friend
  bool operator==(const list_iterator& x, const list_iterator& y)
  {
    return x.item_ == y.item_;
  }
  
  friend
  bool operator!=(const list_iterator& x, const list_iterator& y)
  {
    return !(x == y);
  }

private:
  
  list_item<T>* item_;
  
  explicit list_iterator(list_item<T> *item)
    : item_(item)
  {
  }
  
  template<class> friend class list;
};

template<class T>
class list
{
public:

  typedef T value_type;
  typedef std::size_t size_type;
  typedef list_iterator<T> iterator;
  typedef typename list_iterator<T>::pointer pointer;
  typedef typename list_iterator<T>::reference reference;
  typedef typename list_iterator<T>::difference_type difference_type;
  
  list();
  
  explicit list(std::initializer_list<T> init);
  
  ~list();
  
  iterator begin() const;
  
  iterator end() const;
  
  iterator insert(iterator pos, const T& v);
  
  iterator erase(iterator pos);

  // ## Operações adicionadas referentes ao exercício 01 ## //
  
  // front(): Retorna o primeiro elemento da lista
  T& front();
  // // back (): Retorna o último elemento da lista
  T& back();
  // // push_front(v): Insere o valor v na cabeça da lista.
  iterator push_front(const T& v);
  // // push_back(v): Insere o valor v no final da lista.
  iterator push_back(const T& v);
  // // pop_front(): Remove o primeiro elemento da lista.
  T pop_front();
  // // pop_back(): Remove o último elemento da lista.
  T pop_back();
  // // splice(L2): Funde os elementos da lista L2 ao final da lista operada.
  iterator splice(list& L2);
  // reverse(): reverte os elementos da lista.
  iterator reverse();
  // // merge(L 2 ): Junta duas listas ordenadas de forma ascendente em uma só, 
  // // também ordenada. A Lista L 2 ficará vazia ao final.
  iterator merge(list& L2);

  // ## Fim das operações adicionadas ## //

  void clear();
  
  bool empty() const;
  
private:
  
// no copy allowed
    list(list&);
    list& operator=(list&);

private:

    list_item<T> sentinel_;
};

template<class T>
list<T>::list()
{
}

template<class T>
list<T>::list(std::initializer_list<T> init)
{
  for(const T& v : init)
    insert(end(), v);
}

template<class T>
list<T>::~list()
{
  clear();
}

template<class T> typename list<T>::iterator
list<T>::begin() const
{
  return iterator(sentinel_.next);
}

template<class T> typename list<T>::iterator
list<T>::end() const
{
  return iterator(const_cast< list_item<T>* >(&sentinel_));
}

template<class T> bool
list<T>::empty() const
{
  return (sentinel_.next == &sentinel_);
}

template<class T> typename list<T>::iterator
list<T>::insert(iterator pos, const T& v)
{ 
  list_item<T> *new_item = new list_item<T>(pos.item_->prev, pos.item_, v);
  pos.item_->prev->next = new_item;
  pos.item_->prev = new_item;

  return iterator(new_item);
}

template<class T> typename list<T>::iterator
list<T>::erase(iterator pos)
{
  iterator retval(pos.item_->next);

  pos.item_->prev->next = pos.item_->next;
  pos.item_->next->prev = pos.item_->prev;
  
  delete pos.item_;
  
  return retval;
}

// ## Operações adicionadas referentes ao exercício 01 ## //

// front(): Retorna o primeiro elemento da lista
template <typename T>
T& list<T>::front()
{
    return sentinel_.next->value;
}
// back (): Retorna o último elemento da lista
template <typename T>
T& list<T>::back()
{
    return sentinel_.prev->value;
}
// push_front(v): Insere o valor v na cabeça da lista.
template<class T> typename list<T>::iterator
list<T>::push_front(const T& v)
{ 
  return insert(begin(), v);
}
// push_back(v): Insere o valor v no final da lista.
template<class T> typename list<T>::iterator
list<T>::push_back(const T& v)
{
  return insert(end(), v);
}
// pop_front(): Remove o primeiro elemento da lista.
template <typename T>
T list<T>::pop_front()
{
  // copia-se valor que está sendo removido para ser retornado
  T aux = sentinel_.next->value;
  // remove elemento usando operação erase(), com operação begin() como parâmetro
  erase(begin());
  return aux;
}
// pop_back(): Remove o último elemento da lista.
template <typename T>
T list<T>::pop_back()
{
  // copia-se valor que está sendo removido para ser retornado
  T aux = sentinel_.prev->value;
  // remove elemento anterior à sentinela usando operação erase()
  erase(iterator(sentinel_.prev));
  return aux;
}
// splice(L2): Funde os elementos da lista L2 ao final da lista operada.
template<class T> typename list<T>::iterator
list<T>::splice(list<T>& l2)
{
  for(const T& v : l2)
    insert(end(), v);
  // retorna iterador para começo da lista
  return begin();
}
// reverse(): reverte os elementos da lista.
template<class T> typename list<T>::iterator
list<T>::reverse()
{
  iterator pprev(end()), pnext(end()), current(begin());
  while(current != end())
  {   
    pnext.item_ = current.item_->next;
    current.item_->next = pprev.item_;
    pprev.item_ = current.item_;
    current.item_ = pnext.item_;
  }
  sentinel_.next = pprev.item_;
  return begin();
}

// merge(L2): Junta duas listas ordenadas de forma ascendente em uma só, 
// também ordenada. A Lista L2 ficará vazia ao final.
template<class T> typename list<T>::iterator
list<T>::merge(list<T>& l2)
{
  iterator current_l2(l2.begin());
  iterator current_l1(begin());
  while(current_l2 != l2.end())
  {
    while(current_l1 != end())
    {
      if(current_l2.item_->value < current_l1.item_->value) 
      {
        insert(current_l1, current_l2.item_->value);
        break;
      }
      current_l1++;
    }
  current_l2++;  
  }
  l2.clear();

  // retorna iterador para começo da lista
  return begin();
}
// ## Fim das operações adicionadas ## //

template<class T> void
list<T>::clear()
{
  if(empty())
    return;
  
  const list_item<T> *f = sentinel_.next;
  const list_item<T> *l = &sentinel_;
  
  while(f != l)
  {
    const list_item<T> *tmp = f;
    
    f = f->next;
    
    delete tmp;
  }
  
  sentinel_.prev = &sentinel_;
  sentinel_.next = &sentinel_;
}

#endif // __CAP241_LIST_HPP__