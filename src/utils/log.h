#ifndef __LOG_H
#define __LOG_H

#define GLDEMO_MES_TIP -2
#define GLDEMO_MES_NOT_EXIST -1
#define GLDEMO_MES_WINDOW_INIT_FAIL 0
#define EXDATA_FILE_NOT_EXIST_MATERIAL 1
#include <unordered_map>

class Log {
private:
	static std::unordered_map<int, const char*> _transMes;
public:
	static void initMessage();
	static void log(int mes);
};
#endif