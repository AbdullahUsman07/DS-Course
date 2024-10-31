#include<iostream>
#include<fstream>
#include<string>

struct Tablet {
	char name[30];
	int potency;
};

struct Ointment {
	char name[30];
	int weight;
};

struct Syrup {
	char name[30];
	int weight;
};


class Pharmacy {
private:
	Tablet* tablets;
	Ointment* ointments;
	Syrup* syrups;

public:
	Pharmacy() :tablets(nullptr), ointments(nullptr), syrups(nullptr) {};

	void input_Tablets(Tablet*, std::ofstream&);
	void input_Ointments(Ointment*, std::ofstream&);
	void input_Syrups(Syrup*, std::ofstream&);

	~Pharmacy()
	{
		delete[]tablets;
		delete[] ointments;
		delete[] syrups;
	}

	friend std::istream& operator>>(std::istream& in, Pharmacy& p)
	{

		std::cout << " What to want to Enter\n:";
		std::cout << " Tablets [T/t]: \n";
		std::cout << " Ointments [O/o]: \n";
		std::cout << " Syrups[S/s]:\n";
		std::cout << " Two Items[2]:\n";
		std::cout << " All Items [A/a]:\n";
		std::cout << " Exit[E/e]:\n";




		std::ofstream file_O("Ointments.dat", std::ios::binary);
		std::ofstream file_T("Tablets.dat", std::ios::binary);
		std::ofstream file_S("Syrups.dat", std::ios::binary);



		char choice;
		int SIZE_t, SIZE_o, SIZE_s;
		std::cin >> choice;

		if (choice == 'T' || choice == 't')
		{
			p.input_Tablets(p.tablets, file_T);
		}


		else if (choice == 'O' || choice == 'o')
		{
			p.input_Ointments(p.ointments, file_O);
		}

		else if (choice == 'S' || choice == 's')
		{
			p.input_Syrups(p.syrups, file_S);
		}

		else if (choice == '2')
		{

			std::cout << "Tablet & Ointment [1]:\n";
			std::cout << "Tablet & Syrup [2]:\n";
			std::cout << "Ointment & Tablet [3]:\n";
			std::cout << " Exit[E/e]: \n";
			std::cin >> choice;


			if (choice == '1')
			{
				std::cout << "\n\n";
				p.input_Tablets(p.tablets, file_T);
				std::cout << "\n-----------------------\n";
				p.input_Ointments(p.ointments, file_O);
			}
			else if (choice == '2')
			{
				std::cout << "\n\n";
				p.input_Tablets(p.tablets, file_T);
				std::cout << "\n-----------------------\n";
				p.input_Syrups(p.syrups, file_S);
			}
			else if (choice == '3')
			{
				std::cout << "\n\n";
				p.input_Ointments(p.ointments, file_O);
				std::cout << "\n-----------------------\n";
				p.input_Syrups(p.syrups, file_S);
			}
		}
		else if (choice == 'A' || choice == 'a')
		{
			std::cout << "\n-------------------------\n";
			p.input_Ointments(p.ointments, file_O);
			std::cout << "\n-------------------------\n";
			p.input_Syrups(p.syrups, file_S);
			std::cout << "\n-------------------------\n";
			p.input_Tablets(p.tablets, file_T);
		}
		else if (choice == 'E' || choice == 'e')
		{
			return in;
		}
		else
		{
			throw "Invalid Choice! ";
		}
	}

	friend std::ostream& operator <<(std::ostream& out, Pharmacy& p)
	{
		std::ifstream file_O("Ointments.dat", std::ios::binary);
		std::ifstream file_T("Tablets.dat", std::ios::binary);
		std::ifstream file_S("Syrups.dat", std::ios::binary);

		int size_t, size_o, size_s;

		file_T.read((char*)&size_t, sizeof(size_t));
		file_O.read((char*)&size_o, sizeof(size_t));
		file_S.read((char*)&size_s, sizeof(size_t));

		p.tablets = new Tablet[size_t];
		p.syrups = new Syrup[size_s];
		p.ointments = new Ointment[size_o];


		file_T.read((char*)p.tablets, size_t * sizeof(Tablet));
		file_O.read((char*)p.ointments, size_o * sizeof(Ointment));
		file_S.read((char*)p.syrups, size_s * sizeof(Syrup));


		std::cout << "\n---------------------------------------\n";
		std::cout << "Tablets...\n";
		for (int i = 0; i < size_t; i++)
		{
			out << i + 1 << "- " << p.tablets[i].name << " " << p.tablets[i].potency << "mg " << std::endl;
		}

		std::cout << "\n---------------------------------------\n";
		std::cout << "Ointments...\n";
		for (int i = 0; i < size_o; i++)
		{
			out << i + 1 << "- " << p.ointments[i].name << " " << p.ointments[i].weight << "g " << std::endl;
		}
		std::cout << "\n---------------------------------------\n";
		std::cout << "Syrups...\n";
		for (int i = 0; i < size_t; i++)
		{
			out << i + 1 << "-  " << p.syrups[i].name << " " << p.syrups[i].weight << "ml " << std::endl;
		}

		return out;
	}
};

void Pharmacy::input_Tablets(Tablet* t, std::ofstream& file) {

	int size;
	std::cout << " Enter No of Tablets You Want to Input: ";
	std::cin >> size;
	t = new Tablet[size];


	for (int i = 0; i < size; i++)
	{
		std::cin.ignore();
		std::cout << " Enter Tablet Name: ";
		std::cin.getline(t[i].name, 30);
		std::cout << " Enter its Potency: ";
		std::cin >> t[i].potency;
	}

	file.write((char*)&size, sizeof(size));
	file.write((char*)t, size * sizeof(Tablet));
}


void Pharmacy::input_Ointments(Ointment* o, std::ofstream& file)
{
	int size;
	std::cout << " Enter No of Ointments You Want to Input: ";
	std::cin >> size;
	o = new Ointment[size];


	for (int i = 0; i < size; i++)
	{
		std::cin.ignore();
		std::cout << " Enter Ointment Name: ";
		std::cin.getline(o[i].name, 30);
		std::cout << " Enter its Weight: ";
		std::cin >> o[i].weight;
	}

	file.write((char*)&size, sizeof(size));
	file.write((char*)o, size * sizeof(Ointment));
}



void Pharmacy::input_Syrups(Syrup* s, std::ofstream& file)
{
	int size;
	std::cout << " Enter No of Syrups You Want to Input: ";
	std::cin >> size;
	s = new Syrup[size];


	for (int i = 0; i < size; i++)
	{
		std::cin.ignore();
		std::cout << " Enter Syrup Name: ";
		std::cin.getline(s[i].name, 30);
		std::cout << " Enter its Weight: ";
		std::cin >> s[i].weight;
	}

	file.write((char*)&size, sizeof(size));
	file.write((char*)s, size * sizeof(Syrup));
}

int main()
{
	Pharmacy m;
	std::cout << m;
	//Pharmacy p;
	//bool flag;
	//do {
	//	try {
	//		flag = false;
	//		std::cin >> p;
	//	}
	//	catch (std::string& e)
	//	{
	//		std::cout << "Error Occured! " << e << std::endl;
	//		flag = true;
	//	}
	//} while (flag);
}