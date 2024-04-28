#pragma once
#include <iostream>
#include <cstdlib>

using namespace std;

namespace HT {
	template<typename T>
	class HashTable {
	private:
		struct Node {
			int _key;
			T _value;
			bool del;
			Node() : _key(0), del(true) {}
			Node(int key, const T& value) : _key(key), _value(value), del(false) {}
		};

		Node* table;
		int _size;
		int _capacity;

		int hash(int key) const;

		int findPosition(int key) const;

		void resize(int newSize);

	public:
		HashTable(int initialSize = 10);

		HashTable(const HashTable& other);

		~HashTable();

		HashTable& operator=(const HashTable& other) {
			if (this != &other) {
				delete[] table;
				_size = other._size;
				_capacity = other._capacity;
				table = new Node[_capacity];
				for (int i = 0; i < _capacity; ++i) {
					table[i] = other.table[i];
				}
			}
			return *this;
		}

		void print() const;

		void insert(int key, const T& value);

		void insert_or_assign(int key, const T& value);

		bool contains(const T& value) const;

		T* search(int key);

		bool erase(int key);

		int count(int key) const;
	};

	template<typename T>
	inline int HashTable<T>::hash(int key) const {
		const double A = 0.6180339887; 

		double fractionalPart = A * key - int(A * key);
		return int(_capacity * fractionalPart);
	}

	template<typename T>
	inline int HashTable<T>::findPosition(int key) const {
		int hashValue = hash(key);
		int initialPos = hashValue % _capacity;
		int pos = initialPos;

		do {
			if (table[pos]._key == key && !table[pos].del) {
				return pos;
			}
			if (table[pos].del) {
				break;
			}
			pos = (pos + 1) % _capacity;
		} while (pos != initialPos);

		return -1;
	}

	template<typename T>
	inline void HashTable<T>::resize(int newSize) {
		Node* newTable = new Node[newSize];
		for (int i = 0; i < _capacity; ++i) {
			if (!table[i].del) {
				int newPos = hash(table[i]._key) % newSize;
				while (!newTable[newPos].del) {
					newPos = (newPos + 1) % newSize;
				}
				newTable[newPos] = table[i];
			}
		}
		delete[] table;
		table = newTable;
		_capacity = newSize;
	}

	template<typename T>
	inline HashTable<T>::HashTable(int initialSize) : _size(0), _capacity(initialSize) {
		table = new Node[_capacity];
	}

	template<typename T>
	inline HashTable<T>::HashTable(const HashTable& other) : _size(other._size), _capacity(other._capacity) {
		table = new Node[_capacity];
		for (int i = 0; i < _capacity; ++i) {
			table[i] = other.table[i];
		}
	}

	template<typename T>
	inline HashTable<T>::~HashTable() {
		delete[] table;
	}

	template<typename T>
	inline void HashTable<T>::print() const {
		for (int i = 0; i < _capacity; ++i) {
			if (!table[i].del) {
				cout << "Key: " << table[i]._key << " Value: " << table[i]._value << endl;
			}
		}
	}

	template<typename T>
	inline void HashTable<T>::insert(int key, const T& value) {
		if ((double)_size / _capacity >= 0.7) {
			resize(2 * _capacity);
		}
		int pos = hash(key) % _capacity;
		while (!table[pos].del && table[pos]._key != key) {
			pos = (pos + 1) % _capacity;
		}
		if (table[pos].del) {
			++_size;
		}
		table[pos] = Node(key, value);
		table[pos].del = false;
	}

	template<typename T>
	inline void HashTable<T>::insert_or_assign(int key, const T& value) {
		if ((double)_size / _capacity >= 0.7) {
			resize(2 * _capacity);
		}
		int pos = hash(key) % _capacity;
		int initialPos = pos;
		do {
			if (table[pos]._key == key && !table[pos].del) {
				table[pos]._value = value;
				return;
			}
			pos = (pos + 1) % _capacity;
		} while (pos != initialPos && !table[pos].del);

		if (table[pos].del) {
			++_size;
		}
		table[pos] = Node(key, value);
		table[pos].del = false;
	}

	template<typename T>
	inline bool HashTable<T>::contains(const T& value) const {
		for (int i = 0; i < _capacity; ++i) {
			if (!table[i].del && table[i]._value == value) {
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline T* HashTable<T>::search(int key) {
		int pos = findPosition(key);
		if (pos != -1) {
			return &(table[pos]._value);
		}
		return nullptr;
	}

	template<typename T>
	inline bool HashTable<T>::erase(int key) {
		int pos = findPosition(key);
		if (pos != -1) {
			table[pos].del = true;
			--_size;
			if ((double)_size / _capacity < 0.3 && _capacity > 10) {
				resize(_capacity / 2);
			}
			return true;
		}
		return false;
	}

	template<typename T>
	inline int HashTable<T>::count(int key) const {
		int _count = 0;
		int pos = hash(key) % _capacity;
		while (!table[pos].del && (table[pos]._key != key || table[pos].del)) {
			if (table[pos]._key == key) {
				++_count;
			}
			pos = (pos + 1) % _capacity;
		}
		return _count;
	}
}
