// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#define _WINSOCK_DEPRECATED_NO_WARNINGS

// Windows ��� ����:
#include <windows.h>

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include "boost/any.hpp"

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#include <memory>

// pos f
#include <d2d1.h>

// stl
#include <iostream>
#include <vector>
#include <map>

using namespace std;

// �Ʒ����� �ʿ���� ��� �����ϱ� DCAT
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