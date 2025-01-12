#include<iostream>
#include<fstream>
#include<string>
#include<map>


std::string remove_punc(std::string& word) {
	
	std::string new_word;
	for (int i = 0; word[i] != '\0'; i++)
	{
		if (!ispunct(word[i])) {
			new_word += word[i];
		}
	}
	return new_word;
}

std::string convert_lower_C(std::string& word) {
	std::string new_word;
	for (int i = 0; word[i] != '\0'; i++) {
		new_word += tolower(word[i]);
	}
	return new_word;
}

bool is_stopWord(std::map<std::string,int> _map, const std::string& word) {

	std::map<std::string, int> ::iterator it;
	it = _map.begin();

	while (it != _map.end()) {
		if (word == it->first) {
			return true;
		}
		++it;
	}

	return false;
}

int main(int argc,char *argv[]) {

	std::string word;
	std::string file_path;
	std::map<std::string,int> stop_map;
	std::map<std::string, int> word_map;
	//std::map<std::string, int>::iterator it_s;
	std::map<std::string, int>::iterator it_w;

	if (argc == 1) {
		std::cout << " Input File Path: ";
		getline(std::cin, file_path);
	}
	else {
		file_path = argv[1];
		file_path += '/0';
	}

	std::ifstream stop_file("StopWords.txt");
	std::ifstream word_file(file_path);

	if (!word_file.is_open() || !stop_file.is_open()) {
		std::cout << " File Not Found / Incorrect File Path\n";
		return 1;
	}

	// reading all the stop-words from the file and 
	// storing them inside a map
	while (stop_file.good()) {
		getline(stop_file, word);
		stop_map.insert({word,1});
	}

	word = "";
	while (word_file.good()) {
		word_file >> word;
		word = remove_punc(word);

		// now check if this word is a stop word 
		if (!is_stopWord(stop_map, word)) {

			word = convert_lower_C(word);
			it_w = word_map.find(word);
			if (it_w != word_map.end()) {
				// this means that the word exist in the map
				// so we increase its frequency
				it_w->second++;
			}
			else {
				word_map.insert({ word,1 });
			}
		}
	}

	// displaying word frequency
	it_w = word_map.begin();
	while (it_w!=word_map.end()) {
		std::cout << " Word: " << it_w->first << "   Frequency: " << it_w->second << "\n";
		++it_w;
	}

	// now to generate word cloud
	it_w = word_map.begin();
	std::fstream cloud("WordCloud.html", std::ios::out);
	cloud << "<html>" << std::endl;
	cloud << "<body>" << std::endl;
	

	// Bonus no 2
	while (it_w != word_map.end()) {
		cloud << "<font size=\"" << it_w->second << "\">" << it_w->first << "</font>\n";
		++it_w;
	}
	cloud << "</body>\n";
	cloud << "</html>\n";
	return 0;


}
