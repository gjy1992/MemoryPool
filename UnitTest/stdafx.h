// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

// ���� CppUnitTest ��ͷ�ļ�
#include "CppUnitTest.h"

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <time.h>
#include <Windows.h>

inline double getMS()
{
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	return (double)t.QuadPart / (double)f.QuadPart * 1000;
}