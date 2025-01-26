#pragma once
#include<iostream>

template<typename T>
void ReheapUp(T arr[], int first, int last) {

	int parent;

	if (last == 0) {
		return;
	}

	parent = (last - 1) / 2;

	if (arr[parent] > arr[last]) {
		return;
	}
	else {
		std::swap(arr[parent], arr[last]);
		ReheapUp(arr, first, parent);
	}
}

template<typename T>
void ReheapDown(T arr[], int first, int last) {

	int lc = (first * 2) + 1;
	int rc = (first * 2) + 2;
	int max = (arr[lc] > arr[rc]) ? lc : rc;

	if (lc > last || rc > last) {
		return;
	}

	if (arr[max] <= arr[first]) {
		return;
	}

	std::swap(arr[max], arr[first]);
	ReheapDown(arr, max, last);

}


namespace cs211 {
	template<typename T>
	class priority_queue {
	private:
		T* arr;
		int total_size, n;  // n will be the number of values present in the priority queue

	public:
		priority_queue(int size = 100) {
			this->total_size = size;
			this->arr = new T[this->total_size];
			this->n = 0;
		}

		priority_queue<T>& operator=(const priority_queue<T>& other) {
			if (other.total_size == 0 || other.n == 0) {
				return *this;
			}

			delete[]this->arr;

			this->total_size = other.total_size;
			this->n = other.n;

			this->arr = new T[this->total_size];

			for (int i = 0; i < this->total_size; ++i) {
				this->arr[i] = other.arr[i];
			}

			return *this;
		}

		void push(const T& val) {
			if (this->total_size == n) {
				throw"Queue Overflow!";
			}

			arr[n] = val;
			ReheapUp(arr, 0, n);
			++n;
		}

		void pop() {
			if (n == 0) {
				throw "Queue UnderFlow!";
			}

			arr[0] = arr[n-1];
			--n;
			ReheapDown(arr, 0, n-1);
		}

		T TOP() {
			if (this->n == 0) {
				throw "Queue UnderFlow!";
			}

			return arr[0];
		}

		bool empty() {
			if (this->n == 0) {
				return true;
			}
			return false;
		}

		int SIZE() {
			return this->n;
		}

		void swap(priority_queue<T>& other) {

			std::swap(this->n, other.n);
			std::swap(this->total_size, other.total_size);
			std::swap(this->arr, other.arr);
		}

		~priority_queue() {
			if (this->total_size != 0) {
				delete[]arr;
			}
		}

		void display() {
			for (int i = 0; i < n; ++i) {
				std::cout << arr[i] << " ";
			}
			std::cout << std::endl;
		}
	};
}




