#include<iostream>
#include<forward_list>

template<typename K, typename V>
class unordered_map {
private:
	std::forward_list<std::pair<K, V>>* data;
	int total_size;


public:
	unordered_map(int size) {
		total_size = size / 5;
		data = new forward_list<K, V>[total_size];
	}

	int hash(const K& key) {
		return key / total_size;
	}

	bool insert(const std::pair<K, V>& val) {

		int index = hash(val.first);

		std::forward_list<std::pair<K, V>>::iterator it;
		it = data[index].begin();

		while (it != data[index].end()) {

			if (it->first == val.first) {
				return false;
			}
			++it;
		}
		data[index].push_front(val);
		return true;
	}

	std::pair<K,V>& find(const K& key) {

		int index = hash(key);
		std::pair<K, V> result;
		result.first = K();
		result.second = V();
		std::forward_list<std::pair<K, V>>::iterator it;

		it = data[index].begin();
		while (it != data[index].end()) {
			if (it->first == key) {
				result.first = it->first;
				result.second = it->second;
				return result;
			}
			++it;
		}
		return result;
	}

	bool delete(const K& key) {

		int index = hash(key);
		std::forward_list<std::pair<K, V>>::iterator it_1;

		it_1 = data[index].begin();

		if (it_1->first == key) {
			data[index].pop_front();
			return true;
		}
		else {
			std::forward_list<std::pair<K, V>>::iterator it_2;
			it_2 = it_1;
			++it_2;
			while (it_2 != data[index].end()) {
				if (it_2->first == key) {
					data[index].erase_after(it_1);
					return true;
				}
				++it_1;
				++it_2;
			}
		}
		return false;
	}

};