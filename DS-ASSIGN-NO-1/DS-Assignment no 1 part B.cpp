#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<time.h>
#include<chrono>

// I swap the two variales without taking a temporary third variable
void swap(int& a, int& b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}

 //In this Bubble Sort Algorithm i take a bool variable that checks if there is any swap happened or not 
 //If no Swap Happened in the first complete execution of the first loop that means that array is sorted 
 //thus i return the function making its time complexity O(n) linear time
 //A means it will sort the array in ascending order

void Bubble_sort_A(int* arr, int size)
{
	int i, j,no_of_swaps=0,none_swap=false;
	for (i = 0; i < size - 1; i++)
	{
		none_swap = true;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j+1])
			{

				none_swap= false;
				swap(arr[j], arr[j + 1]);
				no_of_swaps++;
			}
		}
	}
	if (none_swap)
	{
		return;
	}
}





// Wrong implemementation of the Selection sort in which O(n^2) swaps will happend in every case 

void Selection_Sort_w(int* arr, int size)
{
	int i, j,min_value_index,
		no_of_swaps=0;

	for (i = 0; i < size - 1; i++)
	{
		min_value_index = i;
		for (j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min_value_index])
			{
				min_value_index = j;
				swap(arr[min_value_index], arr[i]);
				no_of_swaps++;
			}
		}
		
	}

}

 //Correct Implementation of Selection Sor in which the program terminates when no swap happens in the first iteraion of the loop
void Selection_Sort_r(int* arr, int size)
{
	int i, j, min_value_index,
		no_of_swaps = 0;
	bool none_swap = false;
	for (i = 0; i < size - 1; i++)
	{
		min_value_index = i;
		none_swap = true;
		for (j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min_value_index])
			{
				none_swap = false;
				min_value_index = j;
			}
		}
		if (none_swap)
		{
			return;
		}
		
		swap(arr[min_value_index], arr[i]);
		no_of_swaps++;
		
	}

	std::cout << "\n No of Swaps: " << no_of_swaps << std::endl;
}


void insertion_sort(int* arr, int size)
{
	int j, i;
	for (i = 1; i <= size - 1; i++)
	{
		int key = arr[i];
		for (j = i - 1;  arr[j] > key && j >= 0 ; j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}


void display_array(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void generate_array(int* arr, int size,int range)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % range;
	}
}

void ascending_array(int* arr, int size,int num=0)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = i + 1+num;
	}
}

void deascending_array(int* arr, int size,int num=0)
{
	for (int i = size; i > 0; i--)
	{
		arr[size- i] = i+num;
	}
}



int main()
{

	std::fstream file("Algorithms.csv", std::ios::out);
	
	srand(time(0));

	int array_size = 1000;
	int* arr_A = new int[array_size];
	int* arr_B = new int[array_size];
	int* arr_C = new int[array_size]; 

	/* In this array i will store all the average times taken by different Algorithms to Sort Array A
	 Since there are 4 algos so each index will store its average time taken*/
	double avg_time_A[4] = { 0,0,0,0 };
	double avg_time_B[4] = { 0,0,0,0 };
	double avg_time_C[4] = { 0,0,0,0 };


	/* we need to claculate the average execution-time of 10 runs. I will take a binary file and store the values in each run 
	 when the program will run again it will read the previous average values and calculate the new ones*/


	std::fstream File_("Average_time.dat", std::ios::in,std::ios::binary);
	int no_of_times = 0; // this will read how many times the program is runned
	File_.read((char*)&no_of_times, sizeof(int));
	no_of_times++;
	std::cout << no_of_times << std::endl;
	
	// create temporary arrays to store the previous average values
	double temp_A[4] = {0,0,0,0};
    double temp_B[4] = {0,0,0,0};
	double temp_C[4] = { 0,0,0,0 };
	if (no_of_times != 1)
	{
		File_.read((char*)temp_A, 4 * sizeof(double));
		File_.read((char*)temp_B, 4 * sizeof(double));
		File_.read((char*)temp_C, 4 * sizeof(double));
	}

	File_.close();
	
	// Checking the time for Array_A. How much time did Correct Selection Sort Take to Sort a random generated array
	generate_array(arr_A, array_size,500);
	const auto start_1 = std::chrono::high_resolution_clock::now();
	Selection_Sort_r(arr_A, array_size);
	const auto end_1 = std::chrono::high_resolution_clock::now();
	avg_time_A[0] = std::chrono::duration_cast<std::chrono::milliseconds>(end_1 - start_1).count();
	std::cout << "\nFor Array A Correct Selection Sort took:  "
		<< avg_time_A[0] << " milli seconds \n";

	std::cout << "\n\n\n--------------------------------------------------\n\n\n";

	// Checking the time for Array_A. How much time did Wrong Selection Sort Take to Sort a random generated array
	generate_array(arr_A, array_size,500);
	const auto start_2 = std::chrono::high_resolution_clock::now();
	Selection_Sort_w(arr_A, array_size);
	const auto end_2 = std::chrono::high_resolution_clock::now();
	avg_time_A[1] = std::chrono::duration_cast<std::chrono::milliseconds>(end_2 - start_2).count();
	std::cout << "\nFor Array A Wrong Selection Sort took:  "
		<< avg_time_A[1] << " milli seconds \n";

	std::cout << "\n\n\n--------------------------------------------------\n\n\n";
	

	// Checking the time for Array_A. How much time did Bubble Sort Take to Sort a random generated array
    generate_array(arr_A, array_size,500);
	const auto start_3 = std::chrono::high_resolution_clock::now();
	Bubble_sort_A(arr_A, array_size);
	const auto end_3 = std::chrono::high_resolution_clock::now();
	avg_time_A[2] = std::chrono::duration_cast<std::chrono::milliseconds>(end_3 - start_3).count();
	std::cout << "\nFor Array A Bubble Sort took:  "
			<< avg_time_A[2]<< " milli seconds \n";
	
	std::cout << "\n\n\n--------------------------------------------------\n\n\n";

	
	

	// Checking the time for Array_A. How much time did Insertion Sort Take to Sort a random generated array
	generate_array(arr_A, array_size,500);
	const auto start_4 = std::chrono::high_resolution_clock::now();
	insertion_sort(arr_A, array_size);
	const auto end_4 = std::chrono::high_resolution_clock::now();
	avg_time_A[3] = std::chrono::duration_cast<std::chrono::milliseconds>(end_4 - start_4).count();
	std::cout << "\nFor Array A Insertion Sort took:  "
		<< avg_time_A[3] << " milli seconds \n";

	std::cout << "\n\n\n--------------------------------------------------\n\n\n";
	



	// Checking the time for Array_B. How much time did Correct Selection Sort Take to Sort an already Sorted array
	ascending_array(arr_B, array_size,no_of_times);
	const auto start_5 = std::chrono::high_resolution_clock::now();
	Selection_Sort_r(arr_B, array_size);
	const auto end_5 = std::chrono::high_resolution_clock::now();
	avg_time_B[0] = std::chrono::duration_cast<std::chrono::milliseconds>(end_5 - start_5).count();
	std::cout << "\nFor Array B Correct Selection Sort took:  "
		<< avg_time_B[0] << " milli seconds \n";

	std::cout << "\n\n\n--------------------------------------------------\n\n\n";

	// Checking the time for Array_B. How much time did Wrong Selection Sort Takes to Sort an already Sorted array
	ascending_array(arr_B, array_size,no_of_times);
	const auto start_6 = std::chrono::high_resolution_clock::now();
	Selection_Sort_w(arr_B, array_size);
	const auto end_6 = std::chrono::high_resolution_clock::now();
	avg_time_B[1] = std::chrono::duration_cast<std::chrono::milliseconds>(end_6 - start_6).count();
	std::cout << "\nFor Array B Wrong Selection Sort took:  "
		<< avg_time_B[1] << " milli seconds \n";
	std::cout << "\n\n\n--------------------------------------------------\n\n\n";


	// Checking the time for Array_B. How much time did Bubble Sort Take to Sort an already Sorted array
	ascending_array(arr_B, array_size,no_of_times);
	const auto start_7 = std::chrono::high_resolution_clock::now();
	Bubble_sort_A(arr_B, array_size);
	const auto end_7 = std::chrono::high_resolution_clock::now();
	avg_time_B[2] = std::chrono::duration_cast<std::chrono::milliseconds>(end_7 - start_7).count();
	std::cout << "\nFor Array B Bubble Sort took:  "
		<< avg_time_B[2] << " milli seconds \n";

	std::cout << "\n\n\n--------------------------------------------------\n\n\n";

	// Checking the time for Array_B. How much time did Insertion Sort Take to Sort an already Sorted array
	ascending_array(arr_B, array_size,no_of_times);
	const auto start_8= std::chrono::high_resolution_clock::now();
	insertion_sort(arr_B, array_size);
	const auto end_8 = std::chrono::high_resolution_clock::now();
	avg_time_B[3] = std::chrono::duration_cast<std::chrono::milliseconds>(end_8 - start_8).count();
	std::cout << "\nFor Array B Insertion Sort took:  "
		<< avg_time_B[3] << " milli seconds \n";

	std::cout << "\n\n\n--------------------------------------------------\n\n\n";

	
	// Checking the time for Array_C.How much time did Correct Selection Sort Take to Sort an already Sorted array in deascending order
	deascending_array(arr_C, array_size,no_of_times);
	const auto start_9 = std::chrono::high_resolution_clock::now();
	Selection_Sort_r(arr_C, array_size);
	const auto end_9 = std::chrono::high_resolution_clock::now();
	avg_time_C[0] = std::chrono::duration_cast<std::chrono::milliseconds>(end_9 - start_9).count();
	std::cout << "\nFor Array C Correct Selection Sort took:  "
		<< avg_time_C[0] << " milli seconds \n";

	std::cout << "\n\n\n--------------------------------------------------\n\n\n";

	// Checking the time for Array_C.How much time did Wrong Selection Sort Take to Sort an already Sorted array in deascending order
	deascending_array(arr_C, array_size,no_of_times);
	const auto start_10 = std::chrono::high_resolution_clock::now();
	Selection_Sort_w(arr_C, array_size);
	const auto end_10 = std::chrono::high_resolution_clock::now();
	avg_time_C[1] = std::chrono::duration_cast<std::chrono::milliseconds>(end_10 - start_10).count();
	std::cout << "\nFor Array C Wrong Selection Sort took:  "
		<< avg_time_C[1] << " milli seconds \n";
	std::cout << "\n\n\n--------------------------------------------------\n\n\n";

	// Checking the time for Array_C.How much time did Bubble Sort Take to Sort an already Sorted array in deascending order
	deascending_array(arr_C, array_size,no_of_times);
	const auto start_11 = std::chrono::high_resolution_clock::now();
	Bubble_sort_A(arr_C, array_size);
	const auto end_11 = std::chrono::high_resolution_clock::now();
	avg_time_C[2] = std::chrono::duration_cast<std::chrono::milliseconds>(end_11 - start_11).count();
	std::cout << "\nFor Array C Bubble Sort took:  "
		<< avg_time_C[2] << " milli seconds \n";

	std::cout << "\n\n\n--------------------------------------------------\n\n\n";

	// Checking the time for Array_C.How much time did Insertion Sort Take to Sort an already Sorted array in deascending order
	deascending_array(arr_C, array_size,no_of_times);
	const auto start_12 = std::chrono::high_resolution_clock::now();
	insertion_sort(arr_C, array_size);
	const auto end_12 = std::chrono::high_resolution_clock::now();
	avg_time_C[3] = std::chrono::duration_cast<std::chrono::milliseconds>(end_12 - start_12).count();
	std::cout << "\nFor Array C Insertion Sort took:  "
		<< avg_time_C[3] << " milli seconds \n";

	std::cout << "\n\n\n--------------------------------------------------\n\n\n";


	for (int i = 0; i < 4; i++)
	{
		std::cout << "arr_A[" << i << "]: " << avg_time_A[i] << "\n";
	}

	for (int i = 0; i < 4; i++)
	{
		std::cout << "arr_B[" << i << "]: " << avg_time_B[i] << "\n";
	}
	for (int i = 0; i < 4; i++)
	{
		std::cout << "arr_C[" << i << "]: " << avg_time_C[i] << "\n";
	}


	
	// adding all the average values
	for (int i = 0; i < 4; i++)
	{
	     avg_time_A[i] += temp_A[i];
		avg_time_B[i]+= temp_B[i];
		avg_time_C[i] += temp_C[i];

	}
	// rewriting all the average execution times back to file
	std::fstream file_("Average_time.dat", std::ios::out|std::ios::binary);
	file_.write((char*)&no_of_times, sizeof(int));
	file_.write((char*)avg_time_A, 4 * sizeof(double));
	file_.write((char*)avg_time_B, 4 * sizeof(double));
	file_.write((char*)avg_time_C, 4 * sizeof(double));
	file_.close();

	

	
	// when the program runs on the tenth time it will write all the average times in CSV file
	if (no_of_times == 10) {
		file << "Program Execution no " << "," << no_of_times << "\n";
		file << "Algorithm's Name " << "," << "Array Type " << "," << " Array Size" << "," << "Average Time Taken" << "\n";

		file << "Correct Selection Sort" << "," << "Random Generated" << "," << array_size << "," << avg_time_A[0] / 10 << " ms\n";
		file << "Incorrect Selection Sort" << "," << "Random Generated" << "," << array_size << "," << avg_time_A[1] / 10 << " ms\n";
		file << "Bubble Sort" << "," << "Random Generated" << "," << array_size << "," << avg_time_A[2] / 10 << " ms\n";
		file << "Insertion Sort" << "," << "Random Generated" << "," << array_size << "," << avg_time_A[3] / 10 << " ms\n";

		file << "Correct Selection Sort" << "," << "Ascending Sort" << "," << array_size << "," << avg_time_B[0] / 10 << " ms\n";
		file << "Incorrect Selection Sort" << "," << "Ascending Sort" << "," << array_size << "," << avg_time_B[1] / 10 << " ms\n";
		file << "Bubble Sort" << "," << "Ascending Sort" << "," << array_size << "," << avg_time_B[2] / 10 << " ms\n";
		file << "Insertion Sort" << "," << "Ascending Sort" << "," << array_size << "," << avg_time_B[3] / 10 << " ms\n";


		file << "Correct Selection Sort" << "," << "Deascending Sort" << "," << array_size << "," << avg_time_C[0] / 10 << " ms\n";
		file << "Incorrect Selection Sort" << "," << "Deascending Sort" << "," << array_size << "," << avg_time_C[1] / 10 << " ms\n";
		file << "Bubble Sort" << "," << "Deascending Sort" << "," << array_size << "," << avg_time_C[2] / 10 << " ms\n";
		file << "Insertion Sort" << "," << "Deascending Sort" << "," << array_size << "," << avg_time_C[3] / 10 << " ms\n";
	}
	
	//file.close();

	delete[] arr_A;
	delete[]arr_B;
	delete[] arr_C;
}
