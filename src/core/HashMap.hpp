template <typename K, typename V> struct MapNode {
    K key;
    V value;
    MapNode<K, V> *next;
    MapNode<K, V>(K key, V value) : key(key), value(value), next(nullptr) {};
    ~MapNode<K, V>() {
        if (next != nullptr) {
            delete next;
        }
    }
};

template <typename K, typename V> class HashMap {
public:
    HashMap<K, V>() {
        table = new MapNode<K, V> *[size];
        for (int i = 0; i < size; i++)
            table[i] = nullptr;
    }

    int size = 4;
    MapNode<K, V> **table;
    int count = 0;
    double loadFactorTolerance = 0.5f;

    void rehash(int newSize) {
        MapNode<K, V> **oldTable = table;
        int oldSize = size;
        size = newSize;
        table = new MapNode<K, V> *[size];
        for (int i = 0; i < size; i++)
            table[i] = nullptr;
        count = 0;

        for (int i = 0; i < oldSize; i++) {
            MapNode<K, V> *node = oldTable[i];
            while (node != nullptr) {
                put(node->key, node->value);
                MapNode<K, V> *prev = node;
                node = node->next;
                delete prev;
            }
        }
        delete[] oldTable;
    }

    void put(K key, V value) {
        if (count >= size * loadFactorTolerance) {
            rehash(size * 2);
        }
        unsigned int hashValue = hash(key);
        MapNode<K, V> *prev = nullptr;
        MapNode<K, V> *node = table[hashValue];

        while (node != nullptr && node->key != key) {
            prev = node;
            node = node->next;
        }

        if (node == nullptr) {
            MapNode<K, V> *entry = new MapNode<K, V>(key, value);
            count++;
            if (prev == nullptr) {
                table[hashValue] = entry;
            } else {
                prev->next = entry;
            }
        } else {
            node->value = value;
        }
    }


    void remove(const K &key) {
        unsigned long hashValue = hash(key);
        MapNode<K, V> *prev = nullptr;
        MapNode<K, V> *entry = table[hashValue];

        while (entry != nullptr && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            return;
        }

        else {
            if (prev == nullptr) {
                if (entry->next != nullptr) {
                    table[hashValue] = entry->next;
                } else {
                    table[hashValue] = nullptr;
                }
            } else {
                prev->next = entry->next;
            }
            delete entry;
        }
    }

    bool lookup(K key, V &output) {
        unsigned int location = hash(key);
        MapNode<K, V> *node = table[location];

        while (node != nullptr) {
            if (node->key == key) {
                output = node->value;
                return true;
            }
            node = node->next;
        }

        return false;
    }

    unsigned int hash(K key) {
        const char *s = reinterpret_cast<const char *>(&key);
        unsigned int result = 0;
        for (int i = 0; i < sizeof(key); ++i) {
            result = result * 101 + s[i];
        }
        return result % size;
    };
};
