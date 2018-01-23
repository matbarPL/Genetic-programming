#include "stdafx.h"
#include "ParseFile.h"

CParseFile::CParseFile()
{
	this->s_name = "";
}

CParseFile::CParseFile(string s_name)
{
	this->s_name = s_name;
	
}


CParseFile::~CParseFile()
{
}


void CParseFile::vParse()
{
	string input;
	ifstream file(s_name);
	int i_counter = 0;
	while (getline(file, input,';')) {
		if (i_counter == 0) {
			v_x.push_back(stod(input));
			i_counter++;
		}
		else if (i_counter == 1) {
			v_y.push_back(stod(input));
			i_counter++;
		}
		else if (i_counter == 2) {
			d_result.push_back(stod(input));
			i_counter = 0;
		}
	}
	vVectorsToString();
}

void CParseFile::vVectorsToString()
{
	int n = v_x.size();
	string input = "";
	for (int i = 0; i <n ; i++)
	{
		input = to_string(v_x[i]) + " " + to_string(v_y[i]) + " ";
		v_xy.push_back(input);
	}
}

void CParseFile::vSaveToFile(string s_expr)
{
	ofstream file;
	file.open("result.txt");
	file << s_expr;
	file.close();
}

void CParseFile::vReset()
{
	v_x.clear();
	v_y.clear();
	v_xy.clear();
	d_result.clear();
}



vector<double> CParseFile::vGetX()
{
	return v_x;
}

vector<double> CParseFile::vGetY()
{
	return v_y;
}

vector<double> CParseFile::dGetResult()
{
	return d_result;
}

vector<string> CParseFile::vGetXY()
{
	return v_xy;
}


