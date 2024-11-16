#include"Pharmacy.h"

Pharmacy::~Pharmacy()
{
	delete[]tablets;
	delete[] ointments;
	delete[] syrups;
}

Pharmacy::Pharmacy() :tablets(nullptr), ointments(nullptr), syrups(nullptr) {
	// create the product code file if not exist
	std::fstream("ProductCodes.dat");
};

void Pharmacy::write_code(int code)
{
	std::ifstream File_C("ProductCodes.dat", std::ios::binary);

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
	std::ofstream File_c("ProductCodes.dat", std::ios::binary);
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

bool Pharmacy::code_validate(int code)
{
	// this function will check if the code input by the user already exist or not
	std::ifstream File_C("ProductCodes.dat", std::ios::binary);
	
	int size=0;
	File_C.read((char *)&size,sizeof(int));

	if (size != 0) {
		int* codes = new int[size];
		File_C.read((char*)codes, size * sizeof(int));


		for (int i = 0; i < size; i++)
		{
			if (codes[i] == code)
			{
				return true;
			}
		}
	}
	return false;

}


void Pharmacy::input_Tablets(Tablet* t)
{
	
	// the prev_size will get the size of Previously stored data in Binary File 
	// then i am storing all the previous data at some array which i will rewrite at last
	int size,prev_size=0;
	bool data_exist = false; // this flag is used to check if there exist any previous data in the file
	bool code_exist;
	Tablet* tabs=nullptr;
	std::ifstream file("Tablets.dat", std::ios::binary);
	file.read((char*)&prev_size, sizeof(int));

	// This will check if there is any previous data present or not
	if (prev_size!=0)
	{
		data_exist = true;
		tabs = new Tablet[prev_size];
		file.read((char*)tabs, prev_size * sizeof(Tablet));
	}
	file.close();

	std::cout << " Enter No of Tablets You Want to Input: ";
	std::cin >> size;

	// delete previous data
	if (t != nullptr) {
		delete[]t;
	}
	t = new Tablet[size];

	for (int i = 0; i < size; i++)
	{
		std::cout << "\n\n-------------------------------\n\n";
		std::cout << " Tablet Number " << i + 1 << "\n";
		do {
			code_exist = false;
			std::cout << " Enter Tablets's Code (Must Be Unique): ";
			std::cin >> t[i].code;
			if (code_validate(t[i].code))
			{
				code_exist = true;
			}
		} while (t[i].code < 0 || code_exist);
		write_code(t[i].code);
		std::cin.ignore();
		std::cout << " Enter Tablet Name (30 char max): ";
		std::cin.getline(t[i].name, 30);
		do {
			std::cout << " Enter its Potency (Non-negative): ";
			std::cin >> t[i].potency;
		} while ( t[i].potency<0);
		do {
			std::cout << " Enter Available Stock (Non-Negative): ";
			std::cin >> t[i].quantity;
		} while (t[i].quantity < 0);
	}

	
	std::ofstream file_T("Tablets.dat",std::ios::binary);
	int sz = size;
	// updating the size
	size = size+prev_size;
	file_T.write((char*)&size, sizeof(int));
	file_T.write((char*)t,sz * sizeof(Tablet));
	
	

	if (data_exist)
	{
		file_T.write((char*)tabs, prev_size * sizeof(Tablet));
		delete[]tabs;
	}
	file_T.close();
	
}

void Pharmacy::input_Ointments(Ointment* o)
{
	
	// the prev_size will get the size of Previously stored data in Binary File 
	// then i am storing all the previous data at some array which i will rewrite at last
	int size, prev_size = 0;
	bool data_exist = false; // this variable will check is the data previously exist in a file or not
	bool code_exist;
	Ointment* on = nullptr;
	std::ifstream file("Ointments.dat", std::ios::binary);
	file.read((char*)&prev_size, sizeof(int));

	// This will check if there is any previous data present or not
	if (prev_size != 0)
	{
		data_exist = true;
		on = new Ointment[prev_size];
		file.read((char*)on, prev_size * sizeof(Ointment));
	}
	file.close();

	std::cout << " Enter No of Ointments You Want to Input: ";
	std::cin >> size;

	// delete previous data
	if (o != nullptr) {
		delete []o;
	}
	o = new Ointment[size];

	for (int i = 0; i < size; i++)
	{
		std::cout << "\n\n-------------------------------\n\n";
		std::cout << " Ointment Number " << i + 1 << "\n";
		do {
			std::cout << " Enter Ointment's Code (Must Be Unique): ";
			std::cin >> o[i].code;
		} while (o[i].code < 0 || code_validate(o[i].code));
		write_code(o[i].code);
		std::cin.ignore();
		std::cout << " Enter Ointment's Name (30 char max): ";
		std::cin.getline(o[i].name, 30);
		do {
			std::cout << " Enter its Weight (Non-negative): ";
			std::cin >> o[i].weight;
		} while (o[i].weight < 0);
		do {
			std::cout << " Enter Available Stock (Non-Negative): ";
			std::cin >> o[i].quantity;
		} while (o[i].quantity < 0);
	}


	std::ofstream file_O("Ointments.dat", std::ios::binary);
	int sz = size;
	size = size + prev_size;
	file_O.write((char*)&size, sizeof(int));
	file_O.write((char*)o, sz * sizeof(Ointment));



	if (data_exist)
	{
		file_O.write((char*)on, prev_size * sizeof(Ointment));
		delete[]on;
	}
	file_O.close();

}

void Pharmacy::input_Syrups(Syrup*s)
{
	// the prev_size will get the size of Previously stored data in Binary File 
	// then i am storing all the previous data at some array which i will rewrite at last
	int size,prev_size=0;
	bool data_exist = false; // this variable will keep record wether any previous data exist in the file or not
	std::ifstream file("Syrups.dat", std::ios::binary);
	file.read((char*)&prev_size, sizeof(int));

	Syrup* syp = nullptr;
	if (prev_size != 0)
	{
		data_exist = true;
		syp = new Syrup[prev_size];
		file.read((char*)syp, prev_size * sizeof(Syrup));
	}
	file.close();


	std::cout << " Enter No of Syrups You Want to Input: ";
	std::cin >> size;

	//delete the previous data
	if (s != nullptr) {
		delete[] s;
	}
	s = new Syrup[size];
	 
	for (int i = 0; i < size; i++)
	{
		std::cout << "\n\n-------------------------------\n\n";
		std::cout << " Syrup Number " << i + 1 << "\n";
		do {
			std::cout << " Enter Syrups's Code (Must Be Unique): ";
			std::cin >> s[i].code;
		} while (s[i].code < 0 || code_validate(s[i].code));
		write_code(s[i].code);
		std::cin.ignore();
		std::cout << " Enter Syrup Name (30 char max): ";
		std::cin.getline(s[i].name, 30);
		do {
			std::cout << " Enter its Weight (Non-Negative): ";
			std::cin >> s[i].weight;
		} while (s[i].weight < 0);
		do {
			std::cout << " Enter Available Stock (Non-Negative): ";
			std::cin >> s[i].quantity;
		} while (s[i].quantity < 0);

	}

	std::ofstream file_S("Syrups.dat", std::ios::binary);
	int sz = size;
	size += prev_size;
	file_S.write((char*)&size, sizeof(int));
	file_S.write((char*)s, sz * sizeof(Syrup));

	if (data_exist)
	{
		file_S.write((char*)syp, prev_size * sizeof(Syrup));
		delete[] syp;
		file_S.close();
	}
	file_S.close();
}

void Pharmacy::del_code(int code)
{
	// when ever user deletes an item this fucntion will remove its code from the code file
	std::ifstream file("ProductCodes.dat", std::ios::binary);
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
		codes[i] = codes[i+1];
	}

	std::ofstream file_("ProductCodes.dat", std::ios::binary);
	size -= 1;
	file_.write((char*)&size, sizeof(int));
	file_.write((char*)codes, size * sizeof(int));

	file_.close();
}


std::istream& operator>>(std::istream& in, Pharmacy& p)
{
	std::cout << "\n\n\n\n";
	std::cout << std::setw(40) << " What to want to Enter: \n";
	std::cout << std::setw(40) << " Tablets         [T/t]: \n";
	std::cout << std::setw(40) << " Ointments       [O/o]: \n";
	std::cout << std::setw(40) << " Syrups          [S/s]: \n";
	std::cout << std::setw(40) << " Two Items       [2]:   \n";
	std::cout << std::setw(40) << " All Items       [A/a]: \n";
	std::cout << std::setw(40) << " Exit            [E/e]: \n";


	char choice;
	int SIZE_t, SIZE_o, SIZE_s;
	std::cin >> choice;

	if (choice == 'T' || choice == 't')
	{
		p.input_Tablets(p.tablets);
	}


	else if (choice == 'O' || choice == 'o')
	{
		p.input_Ointments(p.ointments);
	}

	else if (choice == 'S' || choice == 's')
	{
		p.input_Syrups(p.syrups);
	}

	else if (choice == '2')
	{

		std::cout << std::setw(40) << "Tablet & Ointment  [1]:\n";
		std::cout << std::setw(40) << "Tablet & Syrup     [2]:\n";
		std::cout << std::setw(40) << "Ointment & Tablet  [3]:\n";
		std::cout << std::setw(40) << "Exit               [E/e]: \n";
		std::cin >> choice;


		if (choice == '1')
		{
			std::cout << "\n\n";
			p.input_Tablets(p.tablets);
			std::cout << "\n-----------------------\n";
			p.input_Ointments(p.ointments);
		}
		else if (choice == '2')
		{
			std::cout << "\n\n";
			p.input_Tablets(p.tablets);
			std::cout << "\n-----------------------\n";
			p.input_Syrups(p.syrups);
		}
		else if (choice == '3')
		{
			std::cout << "\n\n";
			p.input_Ointments(p.ointments);
			std::cout << "\n-----------------------\n";
			p.input_Syrups(p.syrups);
		}
	}
	else if (choice == 'A' || choice == 'a')
	{
		std::cout << "\n-------------------------\n";
		p.input_Ointments(p.ointments);
		std::cout << "\n-------------------------\n";
		p.input_Syrups(p.syrups);
		std::cout << "\n-------------------------\n";
		p.input_Tablets(p.tablets);
	}
	else if (choice == 'E' || choice == 'e')
	{
		return in;
	}

	return in;

}


void Pharmacy::update_tab(Tablet& t)
{
	char choice;
	std::cout << std::setw(40) << "What do You Wanna Update: \n\n\n";
	std::cout << std::setw(40) << "        Name          [N/n]:\n";
	std::cout << std::setw(40) << "        Potency       [P/p]:\n";
	std::cout << std::setw(40) << "        Stock         [S/s]:\n\n";
	std::cout << std::setw(40) << "Press any key to exit [E/e]:\n";
	std::cin >> choice;

	if (choice == 'n' || choice == 'N')
	{
		std::cout << "Please Enter New Name (max 30 char): ";
		std::cin.getline(t.name, 30);
		return;
	}

	else if (choice == 'p' || choice == 'P')
	{
		do {
			std::cout << "Please Enter New Potency (Non-negative): ";
			std::cin >> t.potency;
		} while (t.potency < 0);
		return;
	}

	else if (choice == 's' || choice == 'S')
	{
		do {
			std::cout << "Please Enter New Stock Amount (Non-negative): ";
			std::cin >> t.quantity;
		} while (t.quantity < 0);
		return;
	}

	// if any other key is pressed then directly return
	else if(choice =='e' || choice =='E')
	{
		return;
	}

}
void Pharmacy::update_oint(Ointment& o)
{
	char choice;
	std::cout << std::setw(40) << "What do You Wanna Update: \n";
	std::cout << std::setw(40) << "        Name          [N/n]:\n";
	std::cout << std::setw(40) << "        Weight        [W/w]:\n";
	std::cout << std::setw(40) << "        Stock         [S/s]:\n";
	std::cout << std::setw(40) << "Press any key to exit [E/e]:\n";
	std::cin >> choice;

	if (choice == 'n' || choice == 'N')
	{
		std::cout << "Please Enter New Name (max 30 char): ";
		std::cin.getline(o.name, 30);
		return;
	}


	else if (choice == 'w' || choice == 'W')
	{
		do {
			std::cout << "Please Enter New Weight (Non-negative): ";
			std::cin >> o.weight;
		} while (o.weight < 0);
		return;
	}

	else if (choice == 's' || choice == 'S')
	{
		do {
			std::cout << "Please Enter New Stock Amount (Non-negative): ";
			std::cin >> o.quantity;
		} while (o.quantity < 0);
		return;
	}

	// if any other key is pressed then directly return
	else if (choice=='e' ||choice =='E')
	{
		return;
	}
}
void Pharmacy::update_syrup(Syrup& s)
{
	char choice;
	std::cout << std::setw(40) << "What do You Wanna Update: \n";
	std::cout << std::setw(40) << "        Name          [N/n]:\n";
	std::cout << std::setw(40) << "        Weight        [W/w]:\n";
	std::cout << std::setw(40) << "        Stock         [S/s]:\n\n";
	std::cout << std::setw(40) << "Press any key to exit [E/e]:";
	std::cin >> choice;

	if (choice == 'n' || choice == 'N')
	{
		std::cout << "Please Enter New Name (max 30 char): ";
		std::cin.getline(s.name, 30);
		return;
	}

	else if (choice == 'w' || choice == 'W')
	{
		do {
			std::cout << "Please Enter New Weight (Non-negative): ";
			std::cin >> s.weight;
		} while (s.weight < 0);
		return;
	}

	else if (choice == 's' || choice == 'W')
	{
		do {
			std::cout << "Please Enter New Stock Amount (Non-negative): ";
			std::cin >> s.quantity;
		} while (s.quantity < 0);
		return;
	}

	// if any other key is pressed then directly return
	else if(choice=='e' ||choice =='E')
	{
		return;
	}
}

void Pharmacy::search(bool update = 0,bool del =0)
{
	char choice;
	char name[30];
	std::cout << std::setw(40) << " Find What You're Looking For? \n";
	std::cout << std::setw(40) << " Tablet    [T/t]: \n";
	std::cout << std::setw(40) << " Ointment  [O/o]: \n";
	std::cout << std::setw(40) << " Syrup     [S/s]: \n";

	std::cin >> choice;
	if (choice == 'T' || choice == 't')
	{
		std::fstream file_T("Tablets.dat", std::ios::in|std::ios::binary);

		int size, tab_code;
		char option; bool repeat;
		file_T.read((char*)&size, sizeof(size));

		Tablet* tb = new Tablet[size];

		file_T.read((char*)tb, size * sizeof(Tablet));

		std::cin.ignore();

		std::cout << " Search By Name or By Code: \n\n";
		do {
			repeat = false;
			std::cout << std::setw(40) << "To Search By Tablet's Code Press     [C/c]: \n";
			std::cout << std::setw(40) << "To Search By Tablet's Name Press     [N/n]: ";
			std::cin >> option;
			if (option != 'C' && option != 'N' && option != 'c' && option != 'n')
			{
				std::cout << " InValid Option!\n";
				repeat = true;
			}
		} while (repeat);





		bool found = false;
		if (option == 'n' || option == 'N') {
			std::cout << " Please Enter Tablet's Name: ";
			std::cin.ignore();
			std::cin.getline(name, 30);

			for (int i = 0; i < size; i++)
			{

				if (strcmp(tb[i].name, name) == 0)
				{

					std::cout << " Record Found!\n";
					std::cout << " Name: " << tb[i].name << " " << tb[i].potency << " mg\n Available Stock: " << tb[i].quantity << "\n";
					found = true;
					if (update == 1)
					{
						update_tab(tb[i]);
						std::cout << " Record Updated Successfully!";
					}
					else if (del == 1)
					{
						del_tab(tb, size, i);
						std::cout << " Record Deleted Successfully!";
						del_code(tb[i].code);
					}
			       	break;
				}

				else
				{
					found = false;
				}
			}
		}

		else if (option == 'c' || option == 'C')
		{
			do {
				std::cout << " Please Enter Tablet's Code (Non-negative): ";
				std::cin >> tab_code;
			} while (tab_code < 0);

			for (int i = 0; i < size; i++)
			{

				if (tab_code == tb[i].code)
				{

					std::cout << " Record Found!\n";
					std::cout << " Name: " << tb[i].name << " " << tb[i].potency << " mg\n Available Stock: " << tb[i].quantity << "\n";
					found = true;
					if (update == 1)
					{
						update_tab(tb[i]);
						std::cout << "\n     Record Updated Successfully!\n";
					}
					else if (del = 1)
					{
						del_tab(tb, size, i);
						std::cout << "\n     Record Deleted Successfully\n";
						del_code(tb[i].code);
					}
					break;

				}

				else
				{
					found = false;
				}
			}
		}

		file_T.close();
		
		if (!found)
	    {
				std::cout << "Record Not Found!\n";
				delete[] tb;
				return;
	    }


		// finally rewrite the updated data 
		if (update) {
			std::ofstream File_T("Tablets.dat", std::ios::binary);
			File_T.write((char*)&size, sizeof(size));
			File_T.write((char*)tb, size * sizeof(Tablet));
			delete[] tb;
			File_T.close();
			return;
		}

		// after deletion writing the remaining data
		else if (del)
		{
			std::ofstream File_Tb("Tablets.dat", std::ios::binary);
			File_Tb.write((char*)&size, sizeof(size));
			File_Tb.write((char*)tb, size * sizeof(Tablet));
			delete[] tb;
			File_Tb.close();
			return;
		}
		delete[]tb;
		return;
	}


	else if (choice == 'O' || choice == 'o')
	{
		std::ifstream file_O("Ointments.dat", std::ios::binary);

		int size;
		bool repeat,found;
		char option;
		file_O.read((char*)&size, sizeof(size));

		Ointment* on = new Ointment[size];

		file_O.read((char*)on, size * sizeof(Ointment));

		std::cout << " Search By Name or By Code: \n\n";
		
		do {
			repeat = false;
			std::cout << std::setw(40) << "To Search By Ointment's Code Press     [C/c]: \n";
			std::cout << std::setw(40) << "To Search By Ointment's Name Press     [N/n]: ";
			std::cin >> option;
			if (option != 'C' && option != 'N' && option != 'c' && option != 'n')
			{
				std::cout << " InValid Option!\n";
				repeat = true;
			}
		} while (repeat);

		if (option == 'N' || option == 'n') {
			std::cin.ignore();
			std::cout << " Please Enter Name: ";
			std::cin.getline(name, 30);

			for (int i = 0; i < size; i++)
			{
				if (strcmp(on[i].name, name) == 0)
				{

					std::cout << " Record Found!\n";
					std::cout << " Name: " << on[i].name << " " << on[i].weight << " g\n Available Stock: " << on[i].quantity << "\n";
					found = true;
					if (update)
					{
						update_oint(on[i]);
						std::cout << "\n     Update Succesful!";
					}
					else if (del)
					{
						del_oint(on, size, i);
						std::cout << "\n     Record Deletion Successful!\n";
						del_code(on[i].code);
					}
					break;
				}
				else
				{
					found = false;
				}
			}
		}
		else if (option == 'c' || option == 'C')
		{
			int code;
			std::cin.ignore();
			do {
				std::cout << " Please Enter Code (Non-Negative): ";
				std::cin >> code;
			} while (code < 0);

			for (int i = 0; i < size; i++)
			{
				if (code==on[i].code)
				{

					std::cout << " Record Found!\n";
					std::cout << " Name: " << on[i].name << " " << on[i].weight << " g\n Available Stock: " << on[i].quantity << "\n";
					found = true;
					if (update)
					{
						update_oint(on[i]);
						std::cout << "\n     Update Succesful!";
					}
					else if (del)
					{
						del_oint(on, size, i);
						std::cout << "\n     Record Deletion Successful!\n";
						del_code(on[i].code);
					}
					break;
				}
				else
				{
					found = false;
				}
			}

		}
		file_O.close();
		
		if (!found)
		{
			std::cout << "Record Not Found!\n";
			delete[] on;
			return;
		}
		
		// rewriting the updated data
		if (update) {
			std::ofstream File_O("Ointments.dat", std::ios::binary);
			File_O.write((char*)&size, sizeof(size));
			File_O.write((char*)on, size * sizeof(Ointment));
			delete[] on;
			File_O.close();
			return;
		}

		if (del)
		{
			std::ofstream File_On("Ointments.dat", std::ios::binary);
			File_On.write((char*)&size, sizeof(size));
			File_On.write((char*)on, size * sizeof(Ointment));
			delete[] on;
			File_On.close();
			return;
		}

		delete[]on;
		return;
	}

	else if (choice == 'S' || choice == 's')
	{
		std::ifstream file_S("Syrups.dat", std::ios::binary);

		int size;
		bool repeat, found;
		char option;
		file_S.read((char*)&size, sizeof(size));

		Syrup* sp = new Syrup[size];

		file_S.read((char*)sp, size * sizeof(Ointment));

		std::cout << " Search By Name or By Code: \n\n";

		do {
			repeat = false;
			std::cout << std::setw(40) << "To Search By Syrup's Code Press     [C/c]: \n";
			std::cout << std::setw(40) << "To Search By Syrup's Name Press     [N/n]: ";
			std::cin >> option;
			if (option != 'C' && option != 'N' && option != 'c' && option != 'n')
			{
				std::cout << " InValid Option!\n";
				repeat = true;
			}
		} while (repeat);

		if (option == 'N' || option == 'n') {
			std::cin.ignore();
			std::cout << " Please Enter Name: ";
			std::cin.getline(name, 30);

			for (int i = 0; i < size; i++)
			{
				if (strcmp(sp[i].name, name) == 0)
				{

					std::cout << " Record Found!\n";
					std::cout << " Name: " << sp[i].name << " " << sp[i].weight << " ml\n Available Stock: " << sp[i].quantity << "\n";
					found = true;
					if (update)
					{
						update_syrup(sp[i]);
						std::cout << "\n     Update Succesful!\n";
					}
					else if (del)
					{
						del_syp(sp, size, i);
						std::cout << "\n     Record Deletion Successful!\n";
						del_code(sp[i].code);
					}
					break;
				}
				else
				{
					found = false;
				}
			}
		}
		else if (option == 'c' || option == 'C')
		{
			int code;
			std::cin.ignore();
			do {
				std::cout << " Please Enter Code (Non-Negative): ";
				std::cin >> code;
			} while (code < 0);

			for (int i = 0; i < size; i++)
			{
				if (code == sp[i].code)
				{

					std::cout << " Record Found!\n";
					std::cout << " Name: " << sp[i].name << " " << sp[i].weight << " ml\n Available Stock: " << sp[i].quantity << "\n";
					found = true;
					if (update)
					{
						update_syrup(sp[i]);
						std::cout << "\n     Update Succesful!\n";
					}
					else if (del)
					{
						del_syp(sp, size, i);
						std::cout << "\n     Record Deletion Successful!\n";
						del_code(sp[i].code);
					}
					break;
				}
				else
				{
					found = false;
				}
			}

		}
		file_S.close();
		

		if (!found)
		{
			std::cout << "Record Not Found!\n";
			delete[] sp;
			return;
		}
		// rewriting the updated data
		if (update)
		{
			std::ofstream File_S("Syrups.dat", std::ios::binary);
			File_S.write((char*)&size, sizeof(size));
			File_S.write((char*)sp, size * sizeof(Syrup));
			delete[] sp;
			File_S.close();
			return;
		}

		if (del)
		{
			std::ofstream File_Sp("Syrups.dat", std::ios::binary);
			File_Sp.write((char*)&size, sizeof(size));
			File_Sp.write((char*)sp, size * sizeof(Syrup));
			delete[] sp;
			File_Sp.close();
			return;
		}
	}
		
	else
	{
		return;
	}
}

void Pharmacy::del_tab(Tablet* t,int & size,int index)
{
	for (int i = index; i < size-1; i++)
	{
		t[i] = t[i + 1];
	}
	size--;
}

void Pharmacy::del_syp(Syrup* s,int & size,int index)
{
	for (int i = index; i < size - 1; i++)
	{
		s[i] = s[i + 1];
	}
	size--;
}

void Pharmacy::del_oint(Ointment* o,int &size,int index)
{
	for (int i = index; i < size - 1; i++)
	{
		o[i] = o[i + 1];
	}
	size--;
}



void Pharmacy::display_all()
{
	std::ifstream file_O("Ointments.dat", std::ios::binary);
	std::ifstream file_T("Tablets.dat", std::ios::binary);
	std::ifstream file_S("Syrups.dat", std::ios::binary);

	int size_t = 0, size_o = 0, size_s = 0;

	file_T.read((char*)&size_t, sizeof(int));
	file_O.read((char*)&size_o, sizeof(int));
	file_S.read((char*)&size_s, sizeof(int));


	if (size_t != 0)
	{
		this->tablets = new Tablet[size_t];
	}

	if (size_s != 0) {
		this->syrups = new Syrup[size_s];
	}

	if (size_o != 0) {
		this->ointments = new Ointment[size_o];

	}

	file_T.read((char*)this->tablets, size_t * sizeof(Tablet));
	file_O.read((char*)this->ointments, size_o * sizeof(Ointment));
	file_S.read((char*)this->syrups, size_s * sizeof(Syrup));


	std::cout << "\n---------------------------------------\n";
	std::cout << "Tablets...\n";
	for (int i = 0; i < size_t; i++)
	{
		std::cout << i + 1 << "- " << this->tablets[i].name << " " << this->tablets[i].potency << " mg  (" << this->tablets[i].code << ")\n   Available Stock : " << this->tablets[i].quantity << std::endl;
	}

	std::cout << "\n---------------------------------------\n";
	std::cout << "Ointments...\n";
	for (int i = 0; i < size_o; i++)
	{
		std::cout << i + 1 << "- " << this->ointments[i].name << " " << this->ointments[i].weight << " g  (" << this->ointments[i].code << ")\n   Available Stock: " << this->ointments[i].quantity << std::endl;
	}

	std::cout << "\n---------------------------------------\n";
	std::cout << "Syrups...\n";
	for (int i = 0; i < size_s; i++)
	{
		std::cout << i + 1 << "-  " << this->syrups[i].name << " " << this->syrups[i].weight << " ml  (" << this->syrups[i].code << ")\n   Availble Stock : " << this->syrups[i].quantity << std::endl;
	}
}


void Export()
{
	std::fstream file_T("Tablets.dat",std::ios::in | std::ios::binary);
	std::fstream file_O("Ointments.dat", std::ios::in | std::ios::binary);
	std::fstream file_S("Syrups.dat", std::ios::in | std::ios::binary);

	Tablet* tab = nullptr;
	Ointment* oint = nullptr;
	Syrup* syp = nullptr;


	int size_T = 0, size_O = 0, size_S = 0;
	file_T.read((char*)&size_T, sizeof(int));
	file_O.read((char*)&size_O, sizeof(int));
	file_S.read((char*)&size_S, sizeof(int));

	std::fstream file("Pharmacy_Data.csv",std::ios::out);

	if (size_T != 0)
	{
		tab = new Tablet[size_T];
		file_T.read((char*)tab, size_T * sizeof(Tablet));
		file << size_T << std::endl;
	    for (int i = 0; i<size_T ;i++)
	    {
		   file << tab[i].code << "," << tab[i].name << "," << tab[i].potency << "," << tab[i].quantity << std::endl;
	    }
	}

	if (size_O != 0)
	{
		oint = new Ointment[size_O];
		file_O.read((char*)oint, size_O * sizeof(Ointment));
		file << size_O << std::endl;
	    for (int i = 0; i < size_O; i++)
	    {
		  file <<oint[i].code << "," << oint[i].name << "," << oint[i].weight << "," << oint[i].quantity << std::endl;
	    }
	}

	if (size_S != 0)
	{
		syp = new Syrup[size_S];
		file_S.read((char*)syp, size_S * sizeof(Syrup));
		file << size_S << std::endl;
	    for (int i = 0; i < size_S; i++)
	    {
		  file << syp[i].code << "," << syp[i].name << "," << syp[i].weight << "," << syp[i].quantity << std::endl;
	    }
	}


	if (tab != nullptr) {
		delete[] tab;
	}
	if (oint != nullptr) {
		delete[] oint;
	}
	if (syp != nullptr) {
		delete[] syp;
	}

	file.close();
	return;

}

void Import(const std::string &file_name)

{
	// this function will import the data and transfer into binary files
	std::fstream file(file_name, std::ios::in);

	std::string data;

	Tablet* tab = nullptr;
	Ointment* oint = nullptr;
	Syrup* syp = nullptr;


	int size_T = 0, size_O = 0, size_S = 0;
	int i,j;

		// reading the size
		getline(file, data, '\n');
		size_T = std::stoi(data);
		
		if (size_T != 0)
		{
			tab = new Tablet[size_T];
			for (i = 0; i < size_T; i++) {
				getline(file, data, ',');
				tab[i].code = std::stoi(data);
				getline(file, data, ',');
				for (j = 0; data[j] != '\0'; j++)
				{
					tab[i].name[j] = data[j];
				}
				tab[i].name[j] = '\0';
				getline(file, data, ',');
				tab[i].potency = std::stoi(data);
				getline(file, data, '\n');
				tab[i].quantity = std::stoi(data);
			}
		}

		getline(file, data, '\n');
		size_O = std::stoi(data);
		
		if (size_O != 0)
		{
			oint= new Ointment[size_O];
			for (i = 0; i < size_O; i++) {
				getline(file, data, ',');
				oint[i].code = std::stoi(data);
				getline(file, data, ',');
				for (j = 0; data[j] != '\0'; j++)
				{
				     oint[i].name[j] = data[j];
				}
				oint[i].name[j] = '\0';
				getline(file, data, ',');
				oint[i].weight = std::stoi(data);
				getline(file, data, '\n');
				oint[i].quantity = std::stoi(data);
			}
		}


		getline(file, data, '\n');
		size_S = std::stoi(data);
		if (size_S != 0)
		{
			syp = new Syrup[size_S];
			for (i = 0; i < size_S; i++) {
				getline(file, data, ',');
				syp[i].code = std::stoi(data);
				getline(file, data, ',');
				for (j = 0; data[j] != '\0'; j++)
				{
					syp[i].name[j] = data[j];
				}
				syp[i].name[j] = '\0';
				getline(file, data, ',');
				syp[i].weight = std::stoi(data);
				getline(file, data, '\n');
				syp[i].quantity = std::stoi(data);
			}

		}

		std::fstream file_T("Tablets.dat", std::ios::out | std::ios::binary);
		std::fstream file_O("Ointments.dat", std::ios::out | std::ios::binary);
		std::fstream file_S("Syrups.dat", std::ios::out | std::ios::binary);

		file_T.write((char*)&size_T, sizeof(int));
		file_T.write((char*)tab, size_T * sizeof(Tablet));
		file_O.write((char*)&size_O, sizeof(int));
		file_O.write((char*)oint, size_O * sizeof(Ointment));
		file_S.write((char*)&size_S, sizeof(int));
		file_S.write((char*)syp, size_S * sizeof(Syrup));


		file.close();
		file_T.close();
		file_O.close();
		file_S.close();
	    delete[] tab;
	    delete[] oint;
	    delete[] syp;

}

int main()
{
	Pharmacy m, p;
	char choice;
	do {
		std::cout << "\n\n\n\n";
		std::cout << std::setw(30) << "****\PHARMACY MANAGEMENT SYSTEM/****\n\n";
		std::cout << std::setw(40) << "Add New Items        [A/a]:\n";
		std::cout << std::setw(40) << "Search Any Item      [S/s]:\n";
		std::cout << std::setw(40) << "Update Any Item      [U/u]:\n";
		std::cout << std::setw(40) << "Delete Any Item      [D/d]:\n";
		std::cout << std::setw(40) << "Print all Data:      [P/p]:\n";
		std::cout << std::setw(40) << "Import Data          [I/i]:\n";
		std::cout << std::setw(40) << "Export Data          [E/e]:\n";
		std::cout << std::setw(40) << "To Terminate         [T/t]:\n";
		std::cout << std::setw(40) << "Please Enter Your Choice: ";
		std::cin >> choice;


		if (choice == 'a' || choice == ' A')
		{
			std::cin >> m;

		}
		else if (choice == 's' || choice == 'S')
		{
			m.search();
		}
		else if (choice == 'u' || choice == 'U')
		{
			m.search(1);
		}
		else if (choice == 'd' || choice == 'D')
		{
			m.search(0, 1);
		}
		else if (choice == 'p' || choice == 'P')
		{
			p.display_all();
			
		}
		else if (choice == 'e' || choice == 'E')
		{
			Export();
		}
		else if (choice == 'i' || choice == 'I')
		{
			std::string file_name;
			std::cout << " Input File Path/ File Name (Must Be Valid):";
			std::cin.ignore();
			getline(std::cin,file_name);
			Import(file_name);
		}
	} while (choice != 'T' && choice != 't');

	return 0;
}

