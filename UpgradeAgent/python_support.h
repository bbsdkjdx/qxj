#pragma once
#include "python.h"

#define  PY_TMP_NAME "__c2p2c__"

void PySetStr(wchar_t *arg, int idx = -1);//assign arg to TMP_NAME in python.;
void PySetInt(INT64 x, int idx = -1);//assign arg to TMP_NAME in python.;
wchar_t *PyGetStr(int idx = -1);//get value of TMP_NAME in python.;
INT64 PyGetInt(int idx=-1);//get int value of __eval_ret__ in python.;
double PyGetDouble(int idx=-1);//get double value of TMP_NAME in python.;
bool PyExecW(wchar_t *arg);
bool PyEvalW(wchar_t *arg);
bool PyEvalOrExecW(wchar_t *arg);
bool PyRunFile(wchar_t *fn);
void PySendMsg(char *msg, unsigned int p1, unsigned int p2);

//'#':'ctypes.c_void_p', 
//'s' : 'ctypes.c_char_p',        'S' : 'ctypes.c_wchar_p',
//'l' : 'ctypes.c_int32',         'u' : 'ctypes.c_uint32',
//'L' : 'ctypes.c_int64',         'U' : 'ctypes.c_uint64',
//'f' : 'ctypes.c_float',         'F' : 'ctypes.c_double' 
#define REG_EXE_FUN(fun,fmt,doc) reg_exe_fun(#fun,fmt,&fun,doc);
//example:REG_EXE_FUN(ChangeExeIcon, "#SS","void(wchar* ico,wchar* exe)");
void reg_exe_fun(char *fnn, char *fmt, void *pfn,char *doc);
