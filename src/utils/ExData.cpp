#define _CRT_SECURE_NO_WARNINGS
#include "ExData.h"
#include "log.h"

#include <stdio.h>


std::map<std::string, std::vector<float>> ExData::materialsdata;

void ExData::init() {
	initMaterialsData();
}

void ExData::initMaterialsData() {
	FILE *f;
	char buffer[20] = {};
	float fbuffer;
	std::string name;
	std::vector<float> data;
	data.resize(10);

	f = fopen(FILE_MATERIAL_DATA, "r");
	if (!f)
		Log::log(EXDATA_FILE_NOT_EXIST_MATERIAL);

	while (!feof(f)) {
		fscanf(f, "%s", buffer);
		name = buffer;
		for (int i = 0; i < 20; ++i)
			buffer[i] = 0;
		for (int i = 0; i < 10; ++i) {
			fscanf(f, "%f", &fbuffer);
			data[i] = fbuffer;
		}
		materialsdata.insert(std::pair<std::string, std::vector<float>>(name, data));
	}
}

//·µ»Ø¿½±´
std::vector<float> ExData::getMaterialsData(const char* name) {
	std::vector <float> res;
	res.clear();
	if (materialsdata.find(name) == materialsdata.end()) {
		return res;
	}
	else {
		return materialsdata[name];
	}
}