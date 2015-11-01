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
      void* current_loc = nullptr;
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
    bool has_inited = false;

    int current_size = 0;

    std::unordered_map<unsigned int, unsigned int> entity_to_index;

    void resize(int new_item_number) {
      std::cout << "Growing to size " << new_item_number << '\n';
      size_t new_size = new_item_number * type_size;
      void* new_mem = malloc(new_size);
      std::cout << "Move from " << mem << " to " << new_mem << '\n';
      if(new_mem == nullptr) {
        std::cout << "Failed to allocate memory for Bag!\n";
        return;
      }

      if(mem != NULL) {
        memcpy(new_mem, mem, current_capacity);
        free(mem);
      }

      mem = new_mem;
      next_space = static_cast<char*>(mem) + current_size * type_size;
      current_capacity = new_size;
    }

    int next_cap() {
      int current_item_cap = current_capacity / type_size;
      return current_item_cap * 2;
    }

  public:
    ~Bag() {
      std::cout << "Free " << mem << "\n";
      free(mem);
      mem = nullptr;
      next_space = nullptr;
    }

    Bag() {
    }

    Bag(Bag&& other) {  
      std::cout << "Bag move constructor\n";
      this->mem = other.mem;
      this->next_space = other.next_space;
      this->current_capacity = other.current_capacity;
      this->type_size = other.type_size;
      this->growth = other.growth;
      this->has_inited = other.has_inited;
      this->current_size = other.current_size;
      this->entity_to_index = other.entity_to_index;
      other.mem = nullptr;
      other.next_space = nullptr;
    }

    Bag& operator=(Bag&& other) {  
      std::cout << "Bag move assignment\n";
      this->mem = other.mem;
      this->next_space = other.next_space;
      this->current_capacity = other.current_capacity;
      this->type_size = other.type_size;
      this->growth = other.growth;
      this->has_inited = other.has_inited;
      this->current_size = other.current_size;
      this->entity_to_index = other.entity_to_index;
      other.mem = nullptr;
      other.next_space = nullptr;
      return *this;
    }

    Bag(const Bag& other) {
      std::cout << "Bag copy constructor\n";
      this->current_capacity = other.current_capacity;
      this->type_size = other.type_size;
      this->growth = other.growth;
      this->has_inited = other.has_inited;
      this->current_size = other.current_size;
      this->entity_to_index = other.entity_to_index;
      mem = malloc(current_capacity);
      memcpy(mem, other.mem, current_capacity);
      next_space = static_cast<char*>(mem) + current_size * type_size;
    }

    Bag& operator=(const Bag& other) {
      std::cout << "Bag copy assignment\n";
      this->current_capacity = other.current_capacity;
      this->type_size = other.type_size;
      this->growth = other.growth;
      this->has_inited = other.has_inited;
      this->current_size = other.current_size;
      this->entity_to_index = other.entity_to_index;
      mem = malloc(current_capacity);
      memcpy(mem, other.mem, current_capacity);
      next_space = static_cast<char*>(mem) + current_size * type_size;
      return *this;
    }

    template<typename T>
      void init() {
        type_size = sizeof(T);
        resize(10);
        has_inited = true;
      }

    template<typename T, typename... Rest>
      T* allocate(unsigned int entity_id, Rest&&... parameters) {
        assert(sizeof(T) == type_size);
        assert(has_inited);

        if(current_capacity < (current_size + 1) * type_size) {
          resize(next_cap());
        }

        entity_to_index[entity_id] = current_size;
        T* ret = new(next_space) T(std::forward<Rest>(parameters)...);
        ret->entity_id = entity_id;
        next_space = static_cast<T*>(next_space) + 1;
        current_size++;

        return ret;
      }

    //Remove item, and move last item in list to its position
    //Will mess up pointers, but maybe that is okay.
    template<typename T>
      void free_obj(T* ptr) {
        int last_entity = ptr->get_entity_id();
        ptr->~T();
        void* last_item = static_cast<T*>(next_space) - 1;
        if(ptr != last_item) {
          memcpy(ptr, last_item, sizeof(T));
        }
        next_space = last_item;
        current_size--;
        entity_to_index[static_cast<T*>(last_item)->get_entity_id()] = entity_to_index[last_entity];
      }

    template<typename T>
    T* get(int i) {
      return static_cast<T*>(mem) + i;
    }

    template<typename T>
    my_iterator<T> begin() {
      return my_iterator<T>(*this, mem);
    }

    template<typename T>
    my_iterator<T> end() {
      return my_iterator<T>(*this, next_space);
    }

    template<typename T>
    T* get_component_for_entity(unsigned int entity_id) {
      int index = entity_to_index[entity_id];
      return get<T>(index);
    }

    template<typename T>
    bool will_resize() {
      return current_capacity < (current_size + 1) * sizeof(T);
    }

    int size() {
      return current_size;
    }

    bool is_null() {
      return mem == nullptr;
    }
};
