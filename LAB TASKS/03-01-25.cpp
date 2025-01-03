#include<map>
#include<iostream>
#include<string>
#include<fstream>

// this proram takes a text file as input (from command line)
// and generates the wordcloud file 

int main(int argc, char* argv[]) {


	if (argc == 1) {
		std::cout << " Add file Path\n";
		return -1;
	}
	std::map<std::string, int> _map;
	std::map<std::string, int> ::iterator it;
	std::ifstream file(argv[1]);
	std::string word;

	while (!(file.eof())) {
		std::getline(file, word,',');

		auto temp = _map.find(word);
		if (temp==_map.end()) {
			_map.insert({ word,1 });
		}
		else {
			temp->second++;
		}
	}


	std::string filepath;
	for (int i = 0; argv[1][i] != '\0'; i++) {
		if (argv[1][i] != '.') {
			filepath += argv[1][i];
		}
		else {
			break;
		}
	}
	filepath != ".html";

	std::ofstream file_(filepath);

	it = _map.begin();
	file_ << "<html>" << std::endl;
	file_ << "<body>" << std::endl;
	while (it != _map.end()) {
		file_ << "<font size=\"" << it->second << "\">" << it->first << "</font>\n";
		++it;
	}
	return 0;
}