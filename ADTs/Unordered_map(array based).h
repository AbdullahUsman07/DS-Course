#pragma once

#include<iostream>
#include<type_traits>
#include<string>


namespace abd {
	template<typename K, typename V>
	class unordered_map {
	private:
		std::pair<K, V>* arr;
		int SIZE;  // total size
		int n;     // number of current values

	public:
		unordered_map(int size) {
			this->SIZE = 1.3 * size;
			arr = new std::pair<K, V>[this->SIZE];
			this->n = 0;

			// fill all the keys with -1
			if (std::is_same<K, std::string>::value) {
				for (int i = 0; i < this->SIZE; ++i) {
					arr[i].first = "-1";
				}
			}

			if (std::is_same<K, int >::value) {
				for (int i = 0; i < this->SIZE; ++i) {
					arr[i].first = -1;
				}
			}
		}

		~unordered_map() {
			delete[] arr;
		}

		int hash(const K& key, int size) {

			if (std::is_same<K, std::string>::value) {
				return key.length() % size; // String hashing
			}
			else {
				return key % size; // Integer hashing
			}

		}

		void insert(const std::pair<K, V> val) {

			// first find hash
			int h1 = hash(val.first, this->SIZE);
			int h2 = hash(val.first, this->SIZE - 2);


			for (int i = 0; i < this->SIZE; ++i) {
				int index = (h1 + i * (h2 + 1)) % this->SIZE;
				if (arr[index].first == -1 || arr[index].first == -2) {
					arr[index] = val;
					return;
				}
			}

			// this no empty space is found thus Hash-Table is full so
			throw "Overflow Error!";
		}

		std::pair<K, V> find(const K& key) {

			int h1 = hash(key, this->SIZE);
			int h2 = hash(key, this->SIZE - 2);


			for (int i = 0; i < this->SIZE; ++i) {
				int index = (h1 + i * (h2 + 1)) % this->SIZE;
				if (arr[i].first == key) {
					return arr[i];
				}
			}

			return std::pair<K, V>();
		}

		void erase(const K& key) {

			int h1 = hash(key, this->SIZE);
			int h2 = hash(key, this->SIZE - 2);


			for (int i = 0; i < this->SIZE; ++i) {
				int index = (h1 + i * (h2 + 1)) % this->SIZE;
				if (arr[i].first == key) {
					arr[i].first = -2;
					return;
				}
			}
		}
	};
}