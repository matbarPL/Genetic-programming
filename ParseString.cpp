#include "stdafx.h"
#include "ParseString.h"


CParseString::CParseString()
{
	s_inputString = "";
	b_working = true;
	vSetArrayOfUnaryOperators();
	vSetArrayOfUnaryOperatorsWithVar();
	vSetArrayOfBinaryOperators();
}

CParseString::CParseString(string input)
{
	s_inputString = input;
	b_working = true;
	vSetArrayOfUnaryOperators();
	vSetArrayOfUnaryOperatorsWithVar();
	vSetArrayOfBinaryOperators();
	
}

void CParseString::vParse(string input)
{
	vStringToVector(input);
}

void CParseString::vClear()
{
	v_vector_of_inputs.clear();
}

CParseString::~CParseString()
{
	v_vector_of_inputs.clear();
}

void CParseString::vSetArrayOfUnaryOperators()
{
	a_unary_operators[0] = SIN;
	a_unary_operators[1] = COS;
}

void CParseString::vSetArrayOfUnaryOperatorsWithVar()
{
	a_unary_operators_with_var[0] = SINX;
	a_unary_operators_with_var[1] = COSX;
	a_unary_operators_with_var[2] = SINY;
	a_unary_operators_with_var[3] = COSY;
}

void CParseString::vSetArrayOfBinaryOperators()
{
	a_binary_operators[0] = PLUS;
	a_binary_operators[1] = MINUS;
	a_binary_operators[2] = PROD;
	a_binary_operators[3] = DIV;
}



int CParseString::iCheckTypeOfString(string input)
{
	bool found = false;
	int type = ANY_TYPE;
	while (!found) {
		if (bCheckIfUnaryOperator(input)) {
			type = iCheckTypeOfUnaryOperator(input);
			found = true;
		}
		else if (bCheckIfBinaryOperator(input)) {
			type = iCheckTypeOfBinaryOperator(input);
			found = true;
		}
		else if (bCheckIfPositiveNumber(input)) {
			type = SPEC_POS_NUMBER;
			found = true;
		}
		else if (bCheckIfVarIsCorrect(input)) {
			type = SPEC_VAR_CORRECT;
			found = true;
		}
		else if (!bCheckIfVarIsCorrect(input)) {
			type = SPEC_WRONG_WAR;
			found = true;
		}
	}
	
	return type;
}

int CParseString::iCheckGeneralTypeOfString(string input)
{
	bool found = false;
	int type = -1;
	while (!found) {
		if (bCheckIfUnaryOperator(input)) {
			type = UNARY_TYPE;
			found = true;
		}
		else if (bCheckIfBinaryOperator(input)) {
			type = BINARY_TYPE;
			found = true;
		}
		else if (bCheckIfPositiveNumber(input)) {
			type = POS_NUMBER;
			found = true;
		}
		else if (bCheckIfVarIsCorrect(input)) {
			type = CORR_VAR;
			found = true;
		}
		else if (!bCheckIfVarIsCorrect(input)) {
			type = WRONG_VAR;
			found = true;
		}
	}

	return type;
}

bool CParseString::bCheckIfVarIsCorrect(string input)
{
	bool err = false;
	int i_counter = 0;
	string::iterator i_iter;
	for (i_iter = input.begin(); i_iter != input.end() && !err; ++i_iter) {
		if (!isalnum(*i_iter))
			err = true;
		else if (!isalpha(*i_iter))
			i_counter++;
	}
	if (input.size() - i_counter < 1)
		err = true;
	return !err;
}

bool CParseString::bCheckIfPositiveNumber(string input)
{
	bool found = false;
	string::iterator i_iter;
	for (i_iter = input.begin(); i_iter != input.end() && !found; ++i_iter) {
		if (isalpha(*i_iter))
			found = true;
	}
	if (!found){
		int number = stoi(input);
		if (number < 0)
			found = true;
	}
	return !found;
}

bool CParseString::bCheckIfUnaryOperator(string input)
{
	vector<string> vectorOfOperators(a_unary_operators, a_unary_operators + sizeof(a_unary_operators) / sizeof(string));
	bool found = false;
	if (find(vectorOfOperators.begin(), vectorOfOperators.end(), input) != vectorOfOperators.end())
		found = true;
	return found;
}

int CParseString::iCheckTypeOfUnaryOperator(string op)
{
	int pos = distance(a_unary_operators, find(a_unary_operators, a_unary_operators + 4, op));
	return pos;
}

bool CParseString::bCheckIfBinaryOperator(string input)
{
	vector<string> vectorOfOperators(a_binary_operators, a_binary_operators+sizeof(a_binary_operators)/sizeof(string));
	bool found = false;
	if (find(vectorOfOperators.begin(), vectorOfOperators.end(), input) != vectorOfOperators.end())
		found = true;
	return found;
}

int CParseString::iCheckTypeOfBinaryOperator(string op)
{
	int pos = distance(a_binary_operators, find(a_binary_operators, a_binary_operators + 4, op));
	return pos+2;
}

void CParseString::vStringToVector(string input)
{
	string::iterator i_iter;
	string word = "";
	for (i_iter = input.begin(); i_iter != input.end(); ++i_iter) {
		if (!isspace(*i_iter)) {
			word += (*i_iter);
		}
		else {
			v_vector_of_inputs.push_back(word);
			word = "";
		}
	}
}

void CParseString::vLineToVector()
{
	string line;
	getline(cin, line);
	line.push_back('\n');
	vector<string> v_vector_of_inputs;
	string::iterator i_iter;
	string word = "";
	for (i_iter = line.begin(); i_iter != line.end(); ++i_iter) {
		if (!isspace(*i_iter)) {
			word += (*i_iter);
		}
		else {
			v_vector_of_inputs.push_back(word);
			word = " ";
		}
	}
}



string CParseString::sGetStringFromVector(int pos)
{
	return v_vector_of_inputs[pos];
}

string CParseString::sVectorToString()
{
	string sVectorToString = "";
	for (vector<string>::iterator i_iter = v_vector_of_inputs.begin(); i_iter != v_vector_of_inputs.end(); ++i_iter) {
		sVectorToString += (*i_iter) + " ";
	}
	return sVectorToString;
}

string CParseString::sGenerateRandomExpr()
{
	
	bool finished = false;
	int i_counter = 0 ;
	int first = rand()%4; //generating trigonometric function with 0.25 probability
	string s_expr ="";
	int which  ;
	int whichToTryg = rand() % 2; //0 - operand 1 - operator
	int maxNodes = 10; 
	CParseString helper;

	while (!finished ) {
		if (first == 0)
		{//unary
			s_expr = a_unary_operators[rand()%2] + " ";
			
			vGenerateRandomSubtree(s_expr);
			finished = true;
		} 
		else 
		{//binary
			which = rand() % 5 - 1;

			s_expr = a_binary_operators[rand() % 4] + " ";
			if (which == -1 || which == 0) //generate two branches
			{
				vGenerateRandomSubtree(s_expr);
				vGenerateRandomSubtree(s_expr);
				finished = true;
			}
			else if(which ==1) //generate one branch, the second one is operand
			{
				vGenerateRandomSubtree(s_expr);

				s_expr += to_string(rand()%10) + " ";
				finished = true;
			}
			else if (which == 2) //two trigonometric functions
			{
				s_expr += a_unary_operators[rand() % 2] + " ";
				vGenerateRandomForUnary(s_expr);
				s_expr += a_unary_operators[rand() % 2] + " ";
				vGenerateRandomForUnary(s_expr);
				finished = true;
			}
			else if (which == 3) //subtree and unar operator
			{
				s_expr += a_unary_operators[rand() % 2] + " ";
				vGenerateRandomForUnary(s_expr);
				vGenerateRandomSubtree(s_expr);
				finished = true;
			}
			else if (which == 4) //unar operator and operand
			{
				s_expr += a_unary_operators[rand() % 2] + " ";
				vGenerateRandomForUnary(s_expr);
				s_expr += to_string(rand() % MAXINT) + " ";
				finished = true;
			}
			
		}
		helper.vParse(s_expr);
		if (helper.v_vector_of_inputs.size() > maxNodes || !bCheckIfExprCorrect(s_expr))
		{
			finished = false;
			s_expr = "";
			helper.vResetParser();
		}
	}

	return s_expr;
}

void CParseString::vGenerateRandomSubtree(string& s_expr)
{
	int type = rand()%2;
	int i_counter = 0; 
	string expr2add = "";
	string vars[2];
	vars[0] = X;
	vars[1] = Y;

	if (type == 0)
	{
		s_expr += vars[rand() % 2];
		return;
	}

	while (type != 0) //generate binary operators
	{
		expr2add += a_binary_operators[rand() % 4] + " ";
		type = rand() % 2;
		i_counter++;
	}

	int which = rand() % 3; //0 operand, 1 variable x lub y, 2 unary oprator 
	
	
	int i = 0;
	while(i<i_counter+1 ) { 
		if (which == 0) 
			expr2add += to_string(rand() % 10) + " ";
		else if (which == 1) 
			expr2add += vars[rand() % 2];
		else 
		{
			expr2add += a_unary_operators[rand() % 2] + " ";
			which = rand() % 3;
			if (which == 0)
				expr2add += to_string(rand() % MAXINT) + " "; 
			else if(which ==1)
				expr2add += vars[rand() % 2]; 
			else 
				vGenerateRandomForUnary(expr2add);
		}
		which = rand() % 3;
		i++;
	}
	
	s_expr += expr2add;
	
}

void CParseString::vGenerateRandomForUnary(string& expr2add)
{
	bool finished = false;
	int which = rand() % 2;
	int maxNodes = 2;
	int i_counter = 0;
	string vars[2];
	vars[0] = X;
	vars[1] = Y;

	while (i_counter < maxNodes)
	{
		expr2add += a_binary_operators[rand() % 4] + " ";
		i_counter++;
	}
	int i = 0;
	while (i < i_counter+1)
	{
		which = rand() % 2;
		if (which == 0)
			expr2add += to_string(rand() % MAXINT) + " ";
		else
			expr2add += vars[rand() % 2];
		i++;
	}
}

bool CParseString::bCheckIfExprCorrect(string s_expr)
{
	int counterX = 0;
	int counterY = 0;

	for (int i = 0; i < s_expr.length(); i++)
	{
		if (s_expr[i] == X[0])
			counterX++;
		if (s_expr[i] == Y[0])
			counterY++;
	}
	return counterX>0 && counterY>0;
}


void CParseString::vResetParser()
{
	b_working = true;
	v_vector_of_inputs.clear();
}

vector<string> CParseString::vGetVectorOfInputs()
{
	return v_vector_of_inputs;
}

string CParseString::sGetFirst()
{
	return v_vector_of_inputs[0];
}

void CParseString::vRemoveFirst()
{
	vector<string>::iterator i_iter = v_vector_of_inputs.begin();
	v_vector_of_inputs.erase(i_iter);
}

bool CParseString::bLast()
{
	if (v_vector_of_inputs.size() == 1)
		return true;
	return false;
}

bool CParseString::bParsedFinished()
{
	return v_vector_of_inputs.size() == 0;
}

