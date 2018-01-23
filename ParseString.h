#pragma once
#include<fstream>
#include<vector>
#include<istream>
#include<iostream>
#include <sstream>
#include <list>
#include<algorithm>
#include<ctime>
#include<stack>

#define MAXINT 10

#define SINX "+ sin x y "
#define COSX "+ cos x y "
#define SINY "+ sin y x "
#define COSY "+ cos y x "

#define X "x "
#define Y "y "
#define SIMPLE_VARS "x y"

#define SIN "sin"
#define COS "cos"
#define PLUS "+"
#define MINUS "-"
#define PROD "*"
#define DIV "/"

//general types
#define ANY_TYPE -1
#define UNARY_TYPE 1
#define BINARY_TYPE 2
#define POS_NUMBER 3
#define CORR_VAR 4
#define WRONG_VAR 5

//specified types
#define SPEC_POS_NUMBER 7
#define SPEC_VAR_CORRECT 8
#define SPEC_WRONG_WAR 9

using namespace std;

class CParseString
{
public:
	friend class CTree;
	friend class CNode;
	CParseString();
	CParseString(string s_inputString);
	~CParseString();
	void vLineToVector();
	void vStringToVector(string input);
	string sGetStringFromVector(int pos);
	string sVectorToString();

	string sGenerateRandomExpr();
	void vGenerateRandomSubtree(string& s_expr);
	void CParseString::vGenerateRandomForUnary(string& expr2add);

	bool bCheckIfExprCorrect(string s_expr);

	void vResetParser();

	bool bCheckIfUnaryOperator(string input);
	bool bCheckIfBinaryOperator(string input);

	int iCheckTypeOfUnaryOperator(string op);
	int iCheckTypeOfBinaryOperator(string op);

	bool bCheckIfVarIsCorrect(string input);
	bool bCheckIfPositiveNumber(string number);
	
	void vSetArrayOfBinaryOperators();
	void vSetArrayOfUnaryOperators();
	void vSetArrayOfUnaryOperatorsWithVar();

	int iCheckTypeOfString(string input);
	int iCheckGeneralTypeOfString(string input);
	void vParse(string input);

	bool bLast();
	bool bParsedFinished();
	void vRemoveFirst();
	string sGetFirst();
	void vClear();

	vector<string> vGetVectorOfInputs();
private:
	bool b_working;
	string s_inputString;
	string a_unary_operators[2];
	string a_unary_operators_with_var[4];
	string a_binary_operators[4];
	vector<string> v_vector_of_inputs;
};

