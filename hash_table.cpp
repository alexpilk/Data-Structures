#include <iostream>

using namespace std;


struct HashTableElement{
    int key;
    int value;
    int* index;

    HashTableElement(){
        key = 0;
        value = 0;
        index = nullptr;
    }

    void set(int key, int value, int* index){
        this->key = key;
        this->value = value;
        this->index = index;
    }
};

class HashTable{
private:
    HashTableElement* array;
    int size;

public:
    explicit HashTable(int size){
        this->size = size;
        array = new HashTableElement[size]{};
    }

    int get(int key){
        HashTableElement* element = getElement(key);
        return element->value;
    }

    void set(int key, int value){
        int hash_value = hash(key);
        int index = findIndexByLinearProbing(key, hash_value);
        array[index].set(key, value, &index);
    }

    int remove(int key){
        HashTableElement* element = getElement(key);
        int index = *element->index;
        delete element;
        array[index] = HashTableElement();
    }

    void print(){
        if(size > 0) {
            HashTableElement* element;
            int index = 0;
            while(index < size && array[index].index != nullptr){
                element = &array[index];
                cout << "Key: " << element->key << ", value: " << element->value << endl;
                index++;
            }
        }
    }

private:
    HashTableElement* getElement(int key){
        int hash_value = hash(key);
        int possible_index = hash_value;
        for (int i = 0; i < size; i++) {
            HashTableElement* possible_element = &array[possible_index];
            if(possible_element->key == key){
                return possible_element;
            }
            possible_index++;
            possible_index %= size;
        }
        throw out_of_range("No element found for key " + key);
    }

    int findIndexByLinearProbing(int key, int hash_value){
        int possible_index = hash_value;
        for (int i = 0; i < size; i++) {
            HashTableElement* current_element = &array[possible_index];
            if(current_element->index == nullptr || current_element->key == key){
                return possible_index;
            }
            possible_index++;
            possible_index %= size;
        }
        throw out_of_range("No index found for hash value " + hash_value);
    }

    int hash(int key){
        return key % size;
    }
};

int main() {
    int size = 5;
    auto hash_table = new HashTable(size);
    hash_table->set(20, 60);
    hash_table->set(20, 70);
    hash_table->set(32, 70);
    hash_table->remove(32);
    hash_table->set(30, 70);
    hash_table->print();

    int value = hash_table->get(20);
    cout << "Got value " << value << endl;
    return 0;
}
