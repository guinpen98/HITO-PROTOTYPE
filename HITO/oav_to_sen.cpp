#include "stdafx.h"
#include "oav_to_sen.h"

int OAVToSEN::rdOAVFile(std::string f_name) {
	std::string line;
	std::ifstream input_file(f_name);
	if (!input_file.is_open()) {
		std::cerr << "Could not open file - " << f_name << std::endl;
		return EXIT_FAILURE;
	}
	int num = 0;
	while (std::getline(input_file, line)) {
		std::stringstream sline(line);
		std::string word;
		std::getline(sline, word, ',');
		o.push_back(word);
		std::getline(sline, word, ',');
		a.push_back(word);
		std::getline(sline, word, ',');
		v.push_back(word);
	}
	return num;
}
