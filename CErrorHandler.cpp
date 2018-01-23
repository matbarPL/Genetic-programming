#include "stdafx.h"
#include "CErrorHandler.h";
#include <typeinfo>
#include <regex>
using namespace std;

CErrorHandler::CErrorHandler() {
	b_error = false;
	i_error_type = 0;
	s_wrong_var_name = "";
}

bool CErrorHandler::bCorrectIntegerInRange(string stringToVerify, int minInt, int maxInt) 
{
	if (bIsNumber(stringToVerify)) {
		int numberToVerify = stoi(stringToVerify);
		if (numberToVerify > maxInt || numberToVerify < minInt) {
			b_error = true;
			i_error_type = ERROR_OF_VALUE;
		}
	}
	else {
		b_error = true;
		i_error_type = ERROR_OF_VALUE;
	}
	return !b_error;
}

void CErrorHandler::vEqualSizeOfVectors(vector<string> v1, vector<CNode*> v2) 
{
	if (v1.size() != v2.size()) {
		i_error_type = ERROR_OF_VARS;
		b_error = true;
	}
}

void CErrorHandler::vFoundErrorOfVar(string wrongVar)
{
	s_wrong_var_name = wrongVar;
	b_error = true;
	i_error_type = ERROR_OF_VAR;
}


void CErrorHandler::vPrintError()
{
	cout << ERROR << endl;
}


bool CErrorHandler::bWasError() 
{
	return b_error;
}

void CErrorHandler::bRestartErrorHandler()
{
	b_error = false;
}

bool CErrorHandler::bIsNumber(const string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end())
		++it;
	return !s.empty() && it == s.end();
}

void CErrorHandler::vPrintTypeOfError()
{
	switch (i_error_type)
	{
	case ERROR_OF_VALUE:
		cout << VALUE_ERROR_TEXT << endl;
		break;
	case ERROR_OF_VARS:
		cout << ERROR_OF_VARS_TEXT << endl;
		break;
	case ERROR_OF_VAR:
		cout << ERROR_OF_VAR_TEXT << s_wrong_var_name << " changed to " << DEFAULT_NAME << endl;
		break;
	}
}

