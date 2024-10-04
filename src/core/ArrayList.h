#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template <typename T> class ArrayList {
public:
  ArrayList() { array = new T[size]; };

  void append(T element) {
    if (length == size)
      resize(size << 1);
    array[length] = element;
    length++;
  };
  void insert(T element, int index) {
    if (length == size)
      resize(size << 1);

    if (index == length) {
      append(element);
      return;
    }

    if (index > size || index < 0) {
      while (size <= index)
        resize(size << 1);
    }

    for (int i = index + 1; i < length; i++) {
      array[i] = array[i - 1];
    }

    array[index] = element;

    length++;
  };
  T get(int index) { return array[index]; };
  void remove(int index) {
    length--;
    for (int i = index; i < length; i++)
      array[i] = array[i + 1];
  };
  void clear() { length = 0; };

  int size = 1;   // size of array
  int length = 0; // number of elements

  T *array;

private:
  void resize(int newSize) {
    T *newArray = new T[newSize](); // () 0s the elements

    for (int i = 0; i < size; i++) {
      newArray[i] = array[i];
    }
    size = newSize;
    delete[] array;
    array = newArray;
  };
};

#endif // ARRAYLIST_H
