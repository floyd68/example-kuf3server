// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.

#define _WINSOCK_DEPRECATED_NO_WARNINGS

// Windows 헤더 파일:
#include <windows.h>

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include "boost/any.hpp"

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#include <memory>

// pos f
#include <d2d1.h>

// stl
#include <iostream>
#include <vector>
#include <map>

using namespace std;

// 아래에서 필요없는 헤더 제거하기 DCAT
#include "svr_logger.h"

#include <crtdbg.h>
#include <d2d1.h>
#include <dwrite.h>
#include <deque>
#include "boost/any.hpp"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#pragma comment(lib, "d2d1.lib")
#pragma  comment(lib, "dwrite.lib")
#pragma comment(lib, "Ws2_32.lib")