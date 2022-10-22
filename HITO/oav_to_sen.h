#ifndef HITO_OAV_TO_SEN_H
#define HITO_OAV_TO_SEN_H
#include <string>
#include <vector>
#include <fstream>

class OAVToSEN
{
public:
	OAVToSEN(std::string f_name) {
		rdOAVFile(f_name);
	}
private:
	std::vector<std::string> o;
	std::vector<std::string> a;
	std::vector<std::string> v;
	std::string sen;
	int rdOAVFile(std::string f_name);
};
#endif //!HITO_OAV_TO_SEN_H
