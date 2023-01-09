#ifndef PARSER_CFG_H
#define PARSER_CFG_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <Array>

std::vector<std::vector<std::string>> genDic() {
	std::vector<std::vector<std::string>> dictionarys;
	std::array<std::string, 6> path = { "n.txt", "v.txt" , "ap.txt" , "pp.txt" , "va.txt" , "adv.txt" };

	for (int i = 0; i < 6; i++) {
		std::ifstream ifs(path[i]);
		std::string str;
		std::vector<std::string> dictionary;

		if (ifs.fail()) {
			std::cerr << "Failed to open file." << std::endl;
			return  dictionarys;
		}
		while (getline(ifs, str)) {
			dictionary.push_back(str);
		}
		dictionarys.push_back(dictionary);
	}
	return dictionarys;
}

int binarySearch(std::string target, const std::vector<std::string>& dec) {
	int left = 0, right = (int)dec.size();
	int center = (int)std::floor((left + right) / 2);
	while (left + 1 < right) {
		center = (int)std::floor((left + right) / 2);
		if (target < dec[center]) right = center;
		else left = center;
	}
	if (dec[left] == target) return left;
	else return -1;
}

std::string check(const std::vector<std::string>& input, std::string(*f1)(const std::vector<std::string>&, const std::vector<std::vector<std::string>>&), std::string(*f2)(const std::vector<std::string>&, const std::vector<std::vector<std::string>>&), const int n, const std::string name, const std::vector<std::vector<std::string>>& dic) {
	std::vector<std::string> input1(n), input2((int)input.size() - n);
	copy(input.begin(), input.begin() + n, input1.begin());
	copy(input.begin() + n, input.end(), input2.begin());
	std::string output1 = f1(input1, dic);
	if (output1.empty()) return output1;
	std::string output2 = (*f2)(input2, dic);
	if (output2.empty()) return output2;
	return name + '(' + output1 + ' ' + output2 + ')';

}
std::string isV(const std::vector<std::string>& input, const std::vector<std::vector<std::string>>& dic) {
	if (input.size() != 1) return std::string();
	if (binarySearch(input[0], dic[1]) != -1) return "(V " + input[0] + ")";
	return std::string();
}
std::string isVA(const std::vector<std::string>& input, const std::vector<std::vector<std::string>>& dic) {
	if (input.size() != 1) return std::string();
	if (binarySearch(input[0], dic[4]) != -1) return "(VA " + input[0] + ")";
	return std::string();
}
std::string isAdv(const std::vector<std::string>& input, const std::vector<std::vector<std::string>>& dic) {
	if (input.size() != 1) return std::string();
	if (binarySearch(input[0], dic[5]) != -1) return "(Adv " + input[0] + ")";
	return std::string();
}
std::string isPP(const std::vector<std::string>& input, const std::vector<std::vector<std::string>>& dic) {
	if (input.size() != 1) return std::string();
	if (binarySearch(input[0], dic[3]) != -1) return "(PP " + input[0] + ")";
	return std::string();
}
std::string isN(const std::vector<std::string>& input, const std::vector<std::vector<std::string>>& dic);
std::string isAP(const std::vector<std::string>& input, const std::vector<std::vector<std::string>>& dic) {
	const int size = (int)input.size();

	if (size == 0) return std::string();
	if (size == 1) {
		if (binarySearch(input[0], dic[2]) != -1) return "(AP " + input[0] + ")";
		return std::string();
	}

	std::string output = check(input, isN, isPP, size - 1, "AP", dic);
	if (!output.empty()) return output;

	output = check(input, isN, isV, size - 1, "AP", dic);
	if (!output.empty()) return output;

	output = check(input, isN, isV, size - 1, "AP", dic);
	if (!output.empty()) return output;

	output = check(input, isAdv, isAP, 1, "AP", dic);
	if (!output.empty()) return output;

	output = check(input, isAP, isAP, 1, "AP", dic);
	if (!output.empty()) return output;

	return std::string();
}
std::string isN(const std::vector<std::string>& input, const std::vector<std::vector<std::string>>& dic) {
	const int size = (int)input.size();

	if (size == 0) return std::string();
	if (size == 1) {
		if (binarySearch(input[0], dic[0]) != -1) return "(N " + input[0] + ")";
		return std::string();
	}
	std::string output = check(input, isAP, isN, size - 1, "N", dic);
	if (output.empty()) return std::string();
	else return output;
}
std::string isVP(const std::vector<std::string>& input, const std::vector<std::vector<std::string>>& dic) {
	const int size = (int)input.size();

	if (size < 2) return std::string();

	std::string output = check(input, isAdv, isVP, 1, "VP", dic);
	if (!output.empty()) return output;

	output = check(input, isN, isVA, size - 1, "VP", dic);
	if (!output.empty()) return output;

	return std::string();
}
std::string isNP(const std::vector<std::string>& input, const std::vector<std::vector<std::string>>& dic) {
	const int size = (int)input.size();

	if (size < 2) return std::string();

	std::string output = check(input, isN, isPP, size - 1, "NP", dic);
	if (output.empty()) return std::string();
	else return output;

}
std::string isS(const std::vector<std::string>& input, const std::vector<std::vector<std::string>>& dic) {
	const int size = (int)input.size();

	if (size < 2) return std::string();

	std::string output = check(input, isNP, isV, size - 1, "S", dic);
	if (!output.empty()) return output;

	for (int i = 2; i <= size - 1; i++) {
		output = check(input, isNP, isAP, i, "S", dic);
		if (!output.empty()) return output;
	}

	for (int i = 2; i <= size - 2; i++) {
		output = check(input, isNP, isN, i, "S", dic);
		if (!output.empty()) return output;
	}

	return std::string();
}
std::string parse(const std::string& sen, const std::vector<std::vector<std::string>>& dic) {
	std::istringstream iss(sen);
	std::string s;
	std::vector<std::string> input;
	while (iss >> s) {
		input.push_back(s);
	}
	return isS(input, dic);
}

#endif //!PARSER_CFG_H
