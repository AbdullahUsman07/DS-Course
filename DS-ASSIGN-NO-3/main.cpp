#include"info.h"


int main(int argc, char* argv[])
{
	char choice ;
	Fruit<item> f;
	f.load_data();

	if (argc == 1)
	{
		do {
			// display the main menu
			std::cout << "\n\n\n\n";
			std::cout << "\t\t" << std::setfill('*') << std::setw(20) << "" << " Welcome to Saddar Fruit Market " << std::setw(20) << "" << "\n";
			std::cout << "\t\t" << std::setfill(' ') << std::setw(20) << "" << " Search Item   [S/s]\n";
			std::cout << "\t\t" << std::setfill(' ') << std::setw(20) << "" << " Add Item      [A/d]\n";
			std::cout << "\t\t" << std::setfill(' ') << std::setw(20) << "" << " Delete Item   [D/d]\n";
			std::cout << "\t\t" << std::setfill(' ') << std::setw(20) << "" << " Update Item   [U/u]\n";
			std::cout << "\t\t" << std::setfill(' ') << std::setw(20) << "" << " Export Items  [E/e]\n";
			std::cout << "\t\t" << std::setfill(' ') << std::setw(20) << "" << " Import Items  [I/i]\n";
			std::cout << "\t\t" << std::setfill(' ') << std::setw(20) << "" << " Display Items [P/p]\n";
			std::cout << "\t\t" << std::setfill(' ') << std::setw(20) << "" << " Show Help     [H/h]\n";
			
			std::cout << "\t\t" << std::setfill(' ') << std::setw(20) << "" << " Terminate     [X/x] ";
			std::cin >> choice;
			if (choice == 'a' ||choice=='A') {
				f.add();
			}
			else if (choice == 'p' || choice=='P') {
				f.display();
			}
			else if (choice == 'd' || choice=='D') {
				f.del();
			}
			else if (choice == 's' || choice =='S')
			{
				f.search();
			}
			else if (choice == 'u' || choice == 'U') {
				f.update();
			}
			else if (choice == 'e' || choice == 'E') {
				std::cout << " Enter FilePath\n";
				std::cin.ignore();
				std::string filePath;
				std::getline(std::cin, filePath);
				f.Export(filePath);
			}
			else if (choice == 'i' || choice == 'I') {
				std::cout << " Enter FilePath\n";
				std::cin.ignore();
				std::string filePath;
				std::getline(std::cin, filePath);
				f.import(filePath);
			}
			else if (choice == 'h' || choice == 'H') {
				showHelp();
			}
		} while (choice != 'x' && choice != 'X');
		
	}
	else if(argc==2)
	{
		if (std::strcmp(argv[1], "display")==0) {
			f.display();
		}
		else if (std::strcmp(argv[1], "update")==0) {
			f.update();
		}
		else if (std::strcmp(argv[1], "search")==0) {
			f.search();
		}
		else if (std::strcmp(argv[1], "add")==0) {
			f.add();
		}
		else if (std::strcmp(argv[1], "delete")==0) {
			f.del();
		}
		else if (std::strcmp(argv[1], "help") == 0) {
			showHelp();
		}
		else {
			std::cout << "Cannot!\n";
		}
	}

	else if(argc==3)
	{
		if (std::strcmp(argv[1], "export") == 0)
		{
			std::string filePath = argv[2];
			f.Export(filePath);
		}
		else if (std::strcmp(argv[1], "import") == 0)
		{
			std::string filePath = argv[2];
			f.import(filePath);
		}
	}
	else {
		std::cout << "For Help Enter Command (info.exe help)\n";
	}


	return 0;
}