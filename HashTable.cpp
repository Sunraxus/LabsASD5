#include "HashTable.h"
#include <string>
#include <chrono>
#include <fstream>
#include <ctime>

using namespace HT;
using namespace std;

void test() {
    cout << "Данные для пустой таблицы:  " << endl;
    HT::HashTable<int> hashTable;
    cout << "Размер таблицы (максимальный)  " << hashTable.get_capacity() << endl;
    cout << "Реальный размер таблицы " << hashTable.get_size() << endl;
    hashTable.print();
    cout << "----------------------------------------" << endl;
    cout << "Данные для таблицы с двумя значениями:  " << endl;
    hashTable.insert(11, 45);
    hashTable.insert(1, 25);
    cout << "Размер таблицы (максимальный)  " << hashTable.get_capacity() << endl;
    cout << "Реальный размер таблицы  " << hashTable.get_size() << endl;
    hashTable.print();
    cout << "----------------------------------------" << endl;
    cout << "Данные для таблицы с 9 значенями:  " << endl;
    hashTable.insert(21, 500);
    hashTable.insert(26, 600);
    hashTable.insert(31, 700);
    hashTable.insert(36, 800);
    hashTable.insert(53, 950);
    hashTable.insert(42, 1000);
    hashTable.insert(67, 910);
    cout << "Размер таблицы (максимальный)  " <<  hashTable.get_capacity() << endl;
    cout << "Реальный размер таблицы " <<  hashTable.get_size() << endl;
    hashTable.print();
    cout << "----------------------------------------" << endl;
    cout << "Проверка работы insert для существующего ключа и метода insert_or_assign:  " << endl;
    hashTable.insert_or_assign(53, 11111);
    hashTable.insert_or_assign(42, 451);
    hashTable.insert_or_assign(68, 9100);
    hashTable.insert(31, 1700);
    hashTable.insert(36, 1800);
    cout << "Размер таблицы (максимальный)  " << hashTable.get_capacity() << endl;
    cout << "Реальный размер таблицы  " << hashTable.get_size() << endl;
    hashTable.print();
    cout << "----------------------------------------" << endl;
    cout << "Тест функции contains:  " << endl;
    if (hashTable.contains(910)) cout << "Элемент со значением 910 есть" << endl;
    else cout << "Элемента со значением 910 нету" << endl;
    if (hashTable.contains(917)) cout << "Элемент со значением 917 есть" << endl;
    else cout << "Элемента со значением 917 нету" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Тест функции search:  " << endl;
    int* foundValue = hashTable.search(67);
    if (foundValue) {
        cout << "Элемент с ключом " << 67 << " найден. Значение: " << *foundValue << endl;
    }
    else {
        cout << "Элемент с ключом " << 67 << " не найден." << endl;
    }
    foundValue = hashTable.search(55);
    if (foundValue) {
        cout << "Элемент с ключом " << 55 << " найден. Значение: " << *foundValue << endl;
    }
    else {
        cout << "Элемент с ключом " << 55 << " не найден." << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "Проверка работы erase:  " << endl;
    cout << "Данные для таблицы с 4 значенями после удаления элементов:  " << endl;
    hashTable.erase(36);
    hashTable.erase(53);
    hashTable.erase(26);
    hashTable.erase(1);
    hashTable.erase(21);
    hashTable.erase(11);
    cout << "Размер таблицы (максимальный)  " << hashTable.get_capacity() << endl;
    cout << "Реальный размер таблицы " << hashTable.get_size() << endl;
    hashTable.print();
    cout << "----------------------------------------" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    test();
    srand(time(0)); 

    const int numElements = 22; 
    const int minKey = 1; 
    const int maxKey = 500; 

    for (int capacity = 25; capacity <= 475; capacity += 50) {
        HT::HashTable<int> ht(capacity); 
        int collisionCount = 0; 
        for (int i = 0; i < numElements; ++i) {
            int key = minKey + rand() % (maxKey - minKey + 1); 
            int value = rand(); 
            int pos = ht.calculateHash(key) % capacity; 
            ht.insert(key, value);
            if (pos != ht.findKeyPosition(key)) {
                collisionCount++;
            }
        }
        cout << "Размер: " << capacity << ", Количество коллизий: " << collisionCount << endl;
    }
    return 0;
}