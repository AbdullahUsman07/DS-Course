#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<iomanip>



struct Tablet {
	int code;
	char name[30];
	float potency;
	int quantity;
};


struct Ointment {
	int code;
	char name[30];
	int weight;
	int quantity;
};


struct Syrup {
	int code;
	char name[30];
	int weight;
	int quantity;
};


class Pharmacy {
private:
	Tablet* tablets;
	Ointment* ointments;
	Syrup* syrups;

public:
	Pharmacy();
	void input_Tablets(Tablet*);
	void input_Ointments(Ointment*);
	void input_Syrups(Syrup*);
	void search(bool,bool);
	void update_tab(Tablet &);
	void update_oint(Ointment&);
	void update_syrup(Syrup& );
	bool code_validate(int);
	void write_code(int);
	void del_code(int);
	void del_tab(Tablet*,int&,int);
	void del_syp(Syrup*,int&,int);
	void del_oint(Ointment*,int&,int);
	void display_all();

	friend std::istream& operator>>(std::istream&, Pharmacy&);

	~Pharmacy();
};
void Export();
void Import(const std::string &);
