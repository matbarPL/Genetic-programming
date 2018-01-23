#pragma once
#include <limits>
#include "Node.h"
#define MIN_INT -2147483647
#define MAX_INT 2147483647
#define ERROR_OF_VALUE 1
#define ERROR_OF_VARS 2
#define ERROR_OF_VAR 3
#define DEFAULT_NAME "z"
#define ERROR "Error occurred. Try again."
#define VALUE_ERROR_TEXT "Wrong s_value "
#define ERROR_OF_VARS_TEXT "Wrong number of variables "
#define ERROR_OF_VAR_TEXT "Wrong variable s_name: "
#include<string>
#include<vector>
using namespace std;

class CErrorHandler {
private:
	bool b_error;
	int i_error_type;
	string s_wrong_var_name;
public:
	CErrorHandler();
	bool bCorrectIntegerInRange(string stringToVerify, int minInt = MIN_INT, int maxInt = MAX_INT);
	bool bIsNumber(const string& s);
	void vEqualSizeOfVectors(vector<string> v1, vector<CNode*> v2);
	bool bWasError();
	void bRestartErrorHandler();
	void vPrintTypeOfError();
	void vFoundErrorOfVar(string wrongVar);
	void vPrintError();	
};