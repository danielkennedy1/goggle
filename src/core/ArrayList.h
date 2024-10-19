#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <iostream>
#include <fstream>

template <typename T> class ArrayList {
public:
    int size = 1; // size of array

    ArrayList() {
        array = new T[size];
    };

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

  void update(int index, T element) {
    try
    {
      if (index >= length) {
        throw (index);
      }
      array[index] = element;
    }
    catch(int index)
    {
      std::cerr << "INDEX " << index << "IS OUT OF BOUNDS FOR ARRAY OF SIZE " << length << '\n';
    }    
  };

  T get(int index) { return array[index]; };
  void remove(int index) {
    length--;
    for (int i = index; i < length; i++)
      array[i] = array[i + 1];
  };
  void clear() { length = 0; };

    int length = 0; // number of elements

    T *array;

    T operator[](int index) { return get(index); }

    void serialize(const std::string& filename)
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr
                << "Error: Failed to open file for writing."
                << std::endl;
            return;
        }
        file.write(reinterpret_cast<const char*>(this),
                   sizeof(*this));
        file.close();
        std::cout << "Object serialized successfully." << std::endl;
    }

    static ArrayList<T> deserialize(const std::string& filename)
    {
        ArrayList<T> obj;
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr
                << "Error: Failed to open file for reading."
                << std::endl;
            return obj;
        }
        file.read(reinterpret_cast<char*>(&obj),
                    sizeof(obj));
        file.close();
        std::cout << "Object deserialized successfully." << std::endl;
        return obj;
    }

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
