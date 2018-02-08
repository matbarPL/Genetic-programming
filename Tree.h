#pragma once
#include"ParseString.h"
#include "Node.h"
#include "CErrorHandler.h"
#include <stack>
#include <set>
#include<iostream>
#define DEFAULT_NAME "z"
#define SINUS_TYPE 0
#define COSINUS_TYPE 1
#define PLUS_TYPE 2
#define MINUS_TYPE 3
#define PRODUCT_TYPE 4
#define DIV_TYPE 5
#define CORR_NUM_TYPE 7
#define CORR_VAR_TYPE 8 
#define INCORR_VAR_TYPE 9

//mutation option
#define LEAF_NEW_LEAF 1
#define LEAF_NEW_NODE 2
#define NODE_NEW_LEAF 3
#define NODE_NEW_NODE 4 
#define NODE_NODE 5
#define LEAF_LEAF 6 
#define NODE_LEAF 7

#define MAX_INT_IN_NODE 10


class CTree
{
public:
	
	CTree();
	CTree(string s_expr);
	CTree(CTree&  tree);
	CTree operator+(CTree& otherTree);
	CTree& operator=(CTree& otherTree);
	friend ostream& operator<<(ostream& stream, CTree tree);
	~CTree();

	void vRestartOldAndSetNewExpression(string s_value);
	void vSetRandomExpr();
	void vResetExpression();

	void vMutate(string option);
	void CTree::vCrossover(CTree* otherTree);

	bool bCheckIfDescendents(CNode* node1, CNode* nod2);
	vector<CNode*> vpcGetAllDescendents(CNode* node);
	
	CNode* pcGetRoot();
	void vSetRoot(CNode* rootToSet);
	void vDeleteVector(vector<CNode*> v);

	void vParseTree();
	void vParseSingleTree(CNode* node, CParseString c_parser, int pos = 0);
	bool bCheckIfNodeDone(CNode* node);
	
	CNode* pcGetLeftMostLeaf(CNode* node);
	void vSetLeafs(CNode* node);
	void vResetHelper(CNode* node);
	void vReset();

	string sPostorderTraversal(CNode* node, string& sPostorder);
	string sPostorder();
	
	string sPreorderTraversal(CNode* node, string& sPostorder);
	string sPreorder();

	vector<CNode*> vpcGetAllNodes(CNode* node, vector<CNode*>& res);
	vector<CNode*> vpcGetAllNodes(CNode* node);
	vector<CNode*> vpcGetAllNodes();

	void vEvaluateTree();
	void vSetValuesForVars(string input);
	double dEvalTreeAndGetResult();
	double dGetResult();

	void vCalculateMeasure(vector<string> input, vector<double> res);

	void vSetMeasure(double d_measure);
	double dGetMeasure();
private:
	string s_expr;
	double d_measure;
	CNode* pc_root;
	CParseString c_parser;
	double d_result;
	vector<CNode*> vpc_leafs;
};

