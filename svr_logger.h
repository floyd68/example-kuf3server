#pragma once

#include "logger.h"

class svr_logger : public logger
{
public:
	static void create(const wchar_t* directory_name, const wchar_t* file_name)
	{
		_svr_logger = new svr_logger(directory_name, file_name);
	}

	static void destroy()
	{
		delete _svr_logger;
	}

	static svr_logger* get_inst()
	{
		return _svr_logger;
	}

	svr_logger(svr_logger const&) = delete;
	void operator=(svr_logger const&) = delete;

private:
	svr_logger(const wchar_t* directory_name, const wchar_t* file_name);
	virtual ~svr_logger();

	static svr_logger* _svr_logger;
};


#define WIDE_STR_(s) L ## s
#define log_write(lv, x, ...) svr_logger::get_inst()->write(lv, __FUNCTIONW__, __LINE__, WIDE_STR_(x), __VA_ARGS__);
#define log_info(x, ...) svr_logger::get_inst()->write(log_level::info, __FUNCTIONW__, __LINE__, WIDE_STR_(x), __VA_ARGS__);
#define log_warn(x, ...) svr_logger::get_inst()->write(log_level::warn, __FUNCTIONW__, __LINE__, WIDE_STR_(x), __VA_ARGS__);
#define log_debug(x, ...) svr_logger::get_inst()->write(log_level::debug, __FUNCTIONW__, __LINE__, WIDE_STR_(x), __VA_ARGS__);
#define log_error(x, ...) svr_logger::get_inst()->write(log_level::error, __FUNCTIONW__, __LINE__, WIDE_STR_(x), __VA_ARGS__);
#define log_critical(x, ...) svr_logger::get_inst()->write(log_level::critical, __FUNCTIONW__, __LINE__, WIDE_STR_(x), __VA_ARGS__);