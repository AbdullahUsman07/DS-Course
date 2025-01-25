
#include<iostream>


//
void ReheapUp(int arr[], int first, int last) {

	while (last>first) {

		int parent = (last - 1) / 2;

		if (arr[parent] > arr[last]) {
			std::swap(arr[parent], arr[last]);
		}
		else {
			break;
		}

		last = parent;
	}
}

void ReheapDown(int arr[], int first, int last) {

	while (true) {

		int rc = (first * 2) + 2;
		int lc = (first * 2) + 1;
		int min = (arr[lc] < arr[rc]) ? lc : rc;

		if (rc > last || lc > last) {
			return;
		}

		if (arr[first] > arr[min]) {
			std::swap(arr[min], arr[first]);
		}
		else {
			break;
		}

		first = min;
	}
}




void heap_sort(int arr[], int n) {

	for (int i = (n / 2) - 1; i >= 0; --i) {

		ReheapDown(arr,i,n-1);
	}

	for (int i = n - 1; i > 0; --i) {

		std::swap(arr[0], arr[i]);
		ReheapDown(arr, 0, i - 1);
	}
}

int main() {
	int arr[] = { 1,2,3,4,5 };
	heap_sort(arr, 5);
	for (int i = 0; i < 5; ++i) {
		std::cout << arr[i] << " ";
	}
}