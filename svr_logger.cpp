#include "svr_logger.h"
#include "stdafx.h"

svr_logger* svr_logger::_svr_logger = nullptr;

svr_logger::svr_logger(const wchar_t* directory_name, const wchar_t* file_name)
	: logger(directory_name, file_name)
{
}

svr_logger::~svr_logger()
{
}
