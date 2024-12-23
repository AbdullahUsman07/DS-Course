#pragma once
#include<iostream>
#include<list>
#include<iomanip>
#include<iterator>
#include<fstream>
#include<string>

struct item {
	char name[20];
	int code;
	float price;
	int stock;
};

template<typename T>
class Fruit {
private:
	std::list<item> fruit;

public:

	// this function will read the data from binary file into data member fruit
	void load_data() {

		std::ifstream file_("Fruits.dat", std::ios::binary);
		int prev_size;
		file_.read((char*)&prev_size, sizeof(int));
		if (prev_size != 0) {

			// clear the previous data
			this->fruit.clear();

			item temp;
			for (int i = 0; i < prev_size; i++) {
				file_.read((char*)&temp, sizeof(item));
				this->fruit.push_front(temp);

			}
			file_.close();
		}
		else {
			return;
		}
		// now our data member contains all the data from the binary file
	}

	Fruit()
	{
		std::fstream("Fruits.dat");
		std::fstream("Codes.dat");
	}


	int get_prev_size() {
		int size = 0;

		std::fstream file("Fruits.dat", std::ios::in | std::ios::binary);
		file.read((char*)&size, sizeof(size));

		file.close();

		return size;
	}



	// this function return iterator to the Node
	std::list<item>::iterator find(int code = -1, const char name[] = "dummy") {
		std::list<item>::iterator temp;
		temp = this->fruit.begin();

		if (code != -1) {
			while (temp != this->fruit.end())
			{
				if (temp->code == code) {
					return temp;
				}
				++temp;
			}
		}

		else if (std::strcmp(name, "dummy") != 0)
		{
			while (temp != fruit.end())
			{
				if (std::strcmp(temp->name, name) == 0) {
					return temp;
				}
				++temp;
			}
		}
		//this means the value is not found
		return fruit.end();
	}

	void write_code(int code)
	{
		std::ifstream File_C("Codes.dat", std::ios::binary);

		int size = 0;
		bool exist = false; // this will check if any Product Codes exist before or not

		File_C.read((char*)&size, sizeof(int));
		int* codes = nullptr;
		if (size != 0) {
			exist = true;
			codes = new int[size];
			File_C.read((char*)codes, size * sizeof(int));
		}
		File_C.close();

		// now writing all the codes in  back again file
		std::ofstream File_c("Codes.dat", std::ios::binary);
		int new_size = size + 1;
		if (exist)
		{
			File_c.write((char*)&new_size, sizeof(int)); // new code added
			File_c.write((char*)&code, sizeof(int)); // adding the new code
			File_c.write((char*)codes, size * sizeof(int)); // adding previous codes
			delete[]codes;
			File_c.close();
			return;
		}

		File_c.write((char*)&new_size, sizeof(int)); // new code added
		File_c.write((char*)&code, sizeof(int));
		File_c.close();
		return;

	}

	bool code_validate(int code) {

		std::fstream _file("Codes.dat", std::ios::in | std::ios::binary);
		int code_size = 0;
		_file.read((char*)&code_size, sizeof(int));


		int* codes = nullptr;
		if (code_size != 0) {
			codes = new int[code_size];
			_file.read((char*)codes, sizeof(int) * code_size);

			for (int i = 0; i < code_size; i++)
			{
				if (codes[i] == code)
				{
					delete[]codes;
					return true;
				}
			}
		}

		_file.close();
		if (codes != nullptr) {
			delete[]codes;
		}
		return false;

	}

	void del_code(int code)
	{
		// when ever user deletes an item this fucntion will remove its code from the code file
		std::ifstream file("Codes.dat", std::ios::binary);
		int size;
		file.read((char*)&size, sizeof(int));

		int* codes = new int[size];
		file.read((char*)codes, size * sizeof(int));
		file.close();
		int i;
		for (i = 0; i < size; i++)
		{
			if (codes[i] == code)
			{
				break;
			}
		}

		// delete the code
		for (int index = i; i < size - 1; i++)
		{
			codes[i] = codes[i + 1];
		}

		std::ofstream file_("Codes.dat", std::ios::binary);
		size -= 1;
		file_.write((char*)&size, sizeof(int));
		file_.write((char*)codes, size * sizeof(int));

		file_.close();
	}

	void append_data(int curr_size) {


		std::fstream file("Fruits.dat", std::ios::out | std::ios::in | std::ios::binary | std::ios::ate);
		int prev_size = this->get_prev_size();
		if (prev_size != 0) {
			curr_size += prev_size;
		}

		file.seekp(0, std::ios::beg);
		file.write((char*)&curr_size, sizeof(int));

		file.seekp(0, std::ios::end);
		auto it = this->fruit.begin();

		for (int i = 0; i < (curr_size - prev_size); i++) {
			file.write((char*)&(*it), sizeof(item));
			it++;
		}

		file.close();

	}

	void add() {
		int count;
		std::cout << " How many Items You Want to input: ";
		std::cin >> count;
		item temp;


		std::fstream file("Fruits.dat", std::ios::out | std::ios::in | std::ios::binary | std::ios::ate);
		if (!file) {
			std::cout << " File Cannot be Opened!";
			return;
		}


		for (int i = 1; i <= count; i++)
		{
			std::cout << "\n" << std::setfill('-') << std::setw(20) << "" << " Item No " << i << " " << std::setfill('-') << std::setw(20) << "\n";
			do {
				std::cout << " Enter Fruit's Code (Must Be Unique): ";
				std::cin >> temp.code;
			} while (code_validate(temp.code) || temp.code < 0);
			write_code(temp.code);
			std::cout << " Enter Fruit's Name (Maximum 20 characters): ";
			std::cin >> temp.name;
			do {
				std::cout << " Enter Price per Kg (Non-Negative): ";
				std::cin >> temp.price;
			} while (temp.price < 0);
			do {
				std::cout << " Enter Stock Available (in Kgs / Non-Negative): ";
				std::cin >> temp.stock;
			} while (temp.stock < 0);
			fruit.push_front(temp);
		}

		append_data(count);
	}



	void search()
	{
		std::list<item>::iterator temp;
		char choice;

		do {
			std::cout << " Search By Name  [N/n]: \n";
			std::cout << " Search By Code  [C/c]: \n";
			std::cin >> choice;

			if (choice == 'c' || choice == 'C') {
				int code;
				std::cout << " Input Code: ";
				std::cin >> code;
				temp = find(code);
			}

			else if (choice == 'n' || choice == 'N') {
				char name[20];
				std::cin.ignore();
				std::cout << " Input Name: ";
				std::cin.getline(name, 20);
				temp = find(-1, name);
			}
		} while (choice != 'c' && choice != 'n' && choice != 'C' && choice != 'N');

		if (temp != fruit.end()) {
			std::cout << " Code:            " << temp->code << " \n";
			std::cout << " Name:            " << temp->name << " \n";
			std::cout << " Price:           " << temp->price << " \n";
			std::cout << " Available Stock: " << temp->stock << " \n";
		}
		else
		{
			std::cout << " Value Not Found!\n";
		}

	}

	void del()
	{
		char choice;

		std::list<item>::iterator it;


		int prev_size = get_prev_size();


		// this means that data exist in files
		if (prev_size != 0) {
			// this will load all the data from Binary File into data member


			do {
				std::cout << " Search By Name  [N/n]: \n";
				std::cout << " Search By Code  [C/c]: \n";

				std::cin >> choice;

				if (choice == 'c' || choice == 'C') {
					int code;
					std::cout << " Input Code: ";
					std::cin >> code;
					it = find(code);
					if (it != this->fruit.end()) {
						del_code(it->code);
						it = this->fruit.erase(it);
					}
					else {
						std::cout << "Cannot Find Item!\n";
						return;
					}
				}

				else if (choice == 'n' || choice == 'N') {
					char name[20];
					std::cin.ignore();
					std::cout << " Input Name: ";
					std::cin.getline(name, 20);
					it = find(-1, name);
					if (it != this->fruit.end()) {
						del_code(it->code);
						it = this->fruit.erase(it);
					}
					else {
						std::cout << "Cannot Find Item!\n";
						return;
					}
				}

				else
				{
					std::cout << " Invalid Choice!\n";
				}
			} while (choice != 'n' && choice != 'c' && choice != 'N' && choice != 'C');


			// removing the item from the file
			prev_size--;
			std::ofstream file("Fruits.dat", std::ios::binary | std::ios::trunc);
			file.write((char*)&prev_size, sizeof(int));
			for (it = this->fruit.begin(); it != this->fruit.end(); it++) {
				file.write((char*)&(*it), sizeof(item));
			}


			std::cout << " Item Deleted Successfully\n";
			return;

		}

		else {
			std::cout << " Nothing to Delete (Empty Files)\n";
		}



	}


	void display() {


		std::list<item>::iterator temp;
		temp = this->fruit.begin();
		int size = this->fruit.size();


		int i = 1;
		if (temp == this->fruit.end()) {
			std::cout << "Data Not Found!\n";
			return;
		}
		while (temp != this->fruit.end())
		{
			std::cout << "\n" << std::setfill('-') << std::setw(20) << "" << " Item No " << i << " " << std::setfill('-') << std::setw(20) << "\n";
			std::cout << " Code:            " << temp->code << " \n";
			std::cout << " Name:            " << temp->name << " \n";
			std::cout << " Price:           " << temp->price << " \n";
			std::cout << " Available Stock: " << temp->stock << " \n";
			++temp, i++;
		}

	}

	void update()
	{
		int prev_size = get_prev_size();
		std::list<item>::iterator it;
		char choice;
		if (prev_size != 0) {

			do {
				std::cout << " Search By Name  [N/n] \n";
				std::cout << " Search By Code  [C/c] \n";

				std::cin >> choice;

				if (choice == 'c' || choice == 'C') {
					int code;
					std::cout << " Input Code: ";
					std::cin >> code;
					it = find(code);
				}

				else if (choice == 'n' || choice == 'N') {
					char name[20];
					std::cin.ignore();
					std::cout << " Input Name: ";
					std::cin.getline(name, 20);
					it = find(-1, name);
				}

				else
				{
					std::cout << " Invalid Choice!\n";
				}
			} while (choice != 'n' && choice != 'c' && choice != 'N' && choice != 'C');
		}

		if (it != this->fruit.end()) {
			choice = '-';
			do {
				std::cout << "\n\n\t\t What Do You Want To Update? \n" <<
					"\t\t Name   [N/n]" <<
					"\t\t Price  [P/p]" <<
					"\t\t Stock  [S/s] ";

				std::cin >> choice;
			} while (choice != 'n' && choice != 'p' && choice != 's' && choice != 'N' && choice != 'P' && choice != 'S');

			switch (choice) {
			case'N':
			case'n':
			{
				std::cin.ignore();
				std::cout << " Enter New Name (20 max Length): ";
				std::cin.getline(it->name, 20);
				break;
			}


			case'P':
			case'p': {
				do {
					std::cout << " Enter New Price (Non-Negative): ";
					std::cin >> it->price;
				} while (it->price < 0);
				break;
			}

			case'S':
			case's': {
				do {
					std::cout << " Enter New Stock Amount (Non-Negative): ";
					std::cin >> it->stock;
				} while (it->stock < 0);
				break;
			}

			}

			// writing the updated data again in the file
			std::ofstream file("Fruits.dat", std::ios::binary | std::ios::trunc);
			file.write((char*)&prev_size, sizeof(int));

			it = this->fruit.begin();
			while (it != this->fruit.end()) {
				file.write((char*)&(*it), sizeof(item));
				it++;
			}
			file.close();
			std::cout << " Item Updated Successfully!\n";
			return;
		}

		else
		{
			std::cout << "Cannot Find Item!\n";
		}
	}

	void Export(const std::string& filepath) {

		std::ofstream file(filepath, std::ios::trunc);

		if (this->fruit.size() != 0) {

			// first writing the number of items 
			file << this->fruit.size() << ",";
			//moving to the next line
			file << "\n";

			file << "Code" << "," << "Name" << "," << "Price" << "," << "Stock" << "," << "\n";

			std::list<item>::iterator temp;
			temp = this->fruit.begin();
			while (temp != this->fruit.end()) {
				file << temp->code << "," << temp->name << "," << temp->price << "," << temp->stock << "," << "\n";
				temp++;
			}

			std::cout << "Data Exported Successfully\n";
		}
		else {
			std::cout << "No Data Exist in File to Export";
		}

	}

	void import(const std::string & filepath) {

		std::ifstream file(filepath);



		std::string temp;
		std::getline(file, temp, '\n');
		item F;
		int size = std::stoi(temp);
		if (size != 0) {

			// now i will read the entire line which contains the attributes like item name ,code,etc
			std::getline(file, temp, ','); //Code
			std::getline(file, temp, ','); //Name
			std::getline(file, temp, ','); //Price
			std::getline(file, temp, ','); //Stock
			temp = "-";

			for (int i = 1; i <= size; i++) {
				std::getline(file, temp, ',');
				F.code = std::stoi(temp);
				write_code(F.code);
				std::getline(file, temp, ',');
				strcpy_s(F.name, temp.c_str());
				std::getline(file, temp, ',');
				F.price = std::stoi(temp);
				std::getline(file, temp, ',');
				F.stock = std::stoi(temp);
				this->fruit.push_front(F);
			}

			std::fstream file_("Fruits.dat", std::ios::out | std::ios::binary);
			append_data(size);
			std::cout << "Data Imported Sucessfully\n";
		}
		else {
			std::cout << "File in Empty Nothing to Import\n";
		}
	}


};

void showHelp() {

	std::fstream file("Help.txt", std::ios::in);
	std::string temp;

	while (!file.eof()) {
		getline(file, temp);
		std::cout << temp << "\n";
	}
	file.close();
}
