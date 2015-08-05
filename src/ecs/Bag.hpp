#pragma once
#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <list>
#include <string.h>
#include <iterator>
class Bag {
  private:
    
    template<typename T>
    struct my_iterator: std::iterator<std::bidirectional_iterator_tag, T> {
      const Bag& bag;
      void* current_loc;
      my_iterator(const Bag& bag, void* current_loc):
        bag(bag),
        current_loc(current_loc)
      { }
      //my_iterator(const my_iterator&);
      //~my_iterator();
      //my_iterator& operator=(const my_iterator&);
      my_iterator& operator++() {
        current_loc += sizeof(T);
      }
      my_iterator& operator--() {
        current_loc -= sizeof(T);
      }
      T& operator*() const {
        return *static_cast<T*>(current_loc);
      }
      my_iterator operator++(int) {
        current_loc += sizeof(T);
      }

      /*
      T operator*() const {
        return *static_cast<T>(current_location);
      }
      */

      T* operator->() const {
        return static_cast<T*>(current_loc);
      }

      friend bool operator==(const my_iterator& left, const my_iterator& right) {
        return left.current_loc == right.current_loc;
      }

      friend bool operator!=(const my_iterator& left, const my_iterator& right) {
        return left.current_loc != right.current_loc;
      }
    };

    void* mem = nullptr;
    void* next_space = nullptr;

    size_t current_capacity = 0;
    size_t type_size = 0;
    int growth = 2;

    int current_size = 0;

    void resize(int new_item_number) {
      std::cout << "Resize\n";
      size_t new_size = new_item_number * type_size;
      void* new_mem = malloc(new_size);
      if(new_mem == nullptr) {
        std::cout << "Failed to allocate memory for Bag!\n";
        return;
      }

      memcpy(new_mem, mem, current_capacity);
      free(mem);

      mem = new_mem;
      next_space = mem + current_capacity;
      current_capacity = new_size;
    }

    int next_cap() {
      int current_item_cap = current_capacity / type_size;
      return current_item_cap + pow(current_item_cap, growth);
    }

  public:
    ~Bag() {
      free(mem);
    }

    template<typename T>
      void init() {
        type_size = sizeof(T);
        resize(1);
        next_space = mem;
      }

    template<typename T, typename... Rest>
      T* allocate(Rest... parameters) {
        if(current_capacity < (current_size + 1) * type_size) {
          resize(next_cap());
        }

        T* ret = new(next_space) T(parameters...);
        next_space += sizeof(T);
        current_size++;

        return ret;
      }

    //Remove item, and move last item in list to its position
    //Will mess up pointers, but maybe that is okay.
    template<typename T>
      void free_obj(T* ptr) {
        ptr->~T();
        void* last_item = next_space - sizeof(T);
        if(ptr != last_item) {
          memcpy(ptr, last_item, sizeof(T));
        }
        next_space = last_item;
        current_size--;
      }

    template<typename T>
    T* get(int i) {
      return static_cast<T*>(mem + i * sizeof(T));
    }

    template<typename T>
    my_iterator<T> begin() {
      return my_iterator<T>(*this, mem);
    }

    template<typename T>
    my_iterator<T> end() {
      std::cout << "End!!\n";
      return my_iterator<T>(*this, next_space);
    }

};
