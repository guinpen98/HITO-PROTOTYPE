#ifndef HITO_OAV_TO_SEN_H
#define HITO_OAV_TO_SEN_H
#include <string>
#include <vector>
#include <fstream>

class OAVToSEN
{
public:
	OAVToSEN(std::string f_name, int num) {
		rdOAVFile(f_name);
		if (num >= 0 && num < o.size()) sen = genSen(o[num], a[num], v[num]);
	}
	std::string getSen()const;
	std::string genSen(std::string obj, std::string atrb, std::string val);
private:
	std::vector<std::string> o;
	std::vector<std::string> a;
	std::vector<std::string> v;
	std::string sen = "初期化";
	int rdOAVFile(std::string f_name);
};
#endif //!HITO_OAV_TO_SEN_H
