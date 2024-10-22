#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <cstddef>
#include <ios>
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
      std::cout << "updating index " << index << "with " << element << std::endl;
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

  T& get(int index) { return array[index]; };
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

        char* buffer = new char[length * sizeof(T)];

        for(int i = 0; i < length; i++) {
            char* serialized_value = reinterpret_cast<char*>(&array[i]);
            for (int j = 0; j < sizeof(T); j++) {
                buffer[i * sizeof(T) + j] = serialized_value[j];
            }
        }

        file.write(buffer, length * sizeof(T));
        file.close();
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

        file.seekg(0, std::ios::end);
        std::streamsize fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        int length = (fileSize / sizeof(T));

        char* buffer = new char[fileSize]; 
        file.read(buffer, fileSize);

        T* cast_buffer = reinterpret_cast<T*>(buffer);

        for (size_t i = 0; i < length; i++) {
            obj.append(cast_buffer[i]);
        }

        file.close();
        return obj;
    }

    void resize(int newSize) {
        T *newArray = new T[newSize](); // () 0s the elements

        for (int i = 0; i < length; i++) {
            newArray[i] = array[i];
        }
        size = newSize;
        delete[] array;
        array = newArray;
    };
};

#endif // ARRAYLIST_H
