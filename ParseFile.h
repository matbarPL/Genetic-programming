#pragma once
#include<iostream>
#include<vector>
#include<istream>
#include<fstream>
#include<string>
using namespace std;

class CParseFile
{
public:
	friend class CPG;
	CParseFile();
	CParseFile(string s_name);
	~CParseFile();
	void vParse();
	void vVectorsToString();
	void vSaveToFile(string tree);
	void vReset();

	vector<double> vGetX();
	vector<double> vGetY();
	vector<double> dGetResult();
	vector<string> vGetXY();
private:
	string s_name;
	vector<double> v_x;
	vector<double> v_y;
	vector<double> d_result;
	vector<string> v_xy;
};

