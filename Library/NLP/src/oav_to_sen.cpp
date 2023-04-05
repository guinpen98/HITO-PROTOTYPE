#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


#include "../include/oav_to_sen.h"

std::string OAVToSEN::getSen() const
{
	return sen;
}

int OAVToSEN::rdOAVFile(std::string f_name) {
	std::string line;
	std::ifstream input_file(f_name);
	if (!input_file.is_open()) {
		std::cerr << "Could not open file - " << f_name << std::endl;
		return EXIT_FAILURE;
	}
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
	input_file.close();
	return 0;
}
std::string OAVToSEN::genSen(std::string obj, std::string atrb, std::string val) {
	if (atrb == "役割") {
		if (val == "場面") return obj + "は" + val + "です。";
		else return "主役が" + obj + "場面です。";
	}
	else if (atrb == "部類") return val + "の部類です。";
	else if (atrb == "外形") return val + "の外形です。";
	else if (atrb == "値段") return "値段は"+ val + "です。";
	else if (atrb == "親分") return val + "が親分です。";
	else if (atrb == "仲間") return "仲間に" + val + "がいます。";
	else if (atrb == "目的") return "目的は" + val + "です。";
	else if (atrb == "所有") return val + "を所有しています。";
	else if (atrb == "所有2") return val + "も所有しています。";
	else if (atrb == "場所") return "いま、" + val + "にいます。";
	else if (atrb == "被道案内") return val + "に道案内してもらっています。";
	else if (atrb == "状況") return val + "状況にあります。";
	else if (atrb == "表示") return val + "と表示されています。";
	else if (atrb == "感覚") return val + "を感じています。";
	else if (atrb == "被援護") return val + "に援護してもらいます。";
	else if (atrb == "被援護2") return val + "にも援護してもらいます。";
	else if (atrb == "行動") return val + "行動をとります。";
	else if (atrb == "次の場面") return val + "のが、次の場面です。";
	else if (atrb == "観察") return val + "を観察しています。";
}
