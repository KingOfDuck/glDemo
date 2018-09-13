#ifndef __EXDATA_H
#define __EXDATA_H

#include <vector>
#include <map>
#define FILE_MATERIAL_DATA "res/materials.dat"
/*
* External Data
* Used to load external data into the program
*/
class ExData {
private:
	static std::map<std::string, std::vector<float>> materialsdata;
public:

	static std::vector<float> getMaterialsData(const char* name);

	static void init();

private:
	static void initMaterialsData();
};
#endif