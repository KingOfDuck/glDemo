#include "log.h"

#include <iostream>

std::unordered_map<int, const char*> Log::_transMes;

void Log::initMessage() {
	_transMes[GLDEMO_MES_TIP] = "[LOG] ";
	_transMes[GLDEMO_MES_NOT_EXIST] = "Message do not exist:";
	_transMes[GLDEMO_MES_WINDOW_INIT_FAIL] = "Fail to initialize window.";
	_transMes[EXDATA_FILE_NOT_EXIST_MATERIAL] = "Cannot open external material data.";
}

void Log::log(int mes) {
	if (_transMes[mes])
		std::cout << _transMes[GLDEMO_MES_TIP] << _transMes[mes] << std::endl;
	else
		std::cout << _transMes[GLDEMO_MES_NOT_EXIST] << std::endl;
 }
