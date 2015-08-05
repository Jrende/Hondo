#pragma once
template<class T>
class Component {
  private:
  public:
    static int id;
    Component() {
      hash++;
    }
};
template <class T> int Component<T>::id(0);
