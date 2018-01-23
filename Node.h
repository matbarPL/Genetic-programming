#pragma once
#include <string>
#include <vector>
#include<iostream>
#include"ParseString.h"
#define DEF_VALUE "1"
using namespace std;

class CNode
{
public:
	CNode();
	CNode(string sValueToSet);
	CNode(CNode* pcParentToSet, string sValueToSet);
	CNode(CNode& cOtherNode);

	CNode& operator=(CNode& cNode);
	bool operator==(CNode& cOtherNode);
	bool operator!=(CNode& therNode);
	~CNode();

	CNode* pcGetChild();
	CNode* pcGetChild(int pos);
	string sGetValueFromChild(int pos);

	void vAddChild();
	void vAddChild(string s_value);
	void vAddChild(CNode* parentToSet, string childValue);

	string sGetValue();

	void vSetValue(string s_value);
	void vSetParent(CNode* parentNodeToSet);

	int iGetNumberOfChildren();
	void iDeleteChildren();
	vector<CNode*> vpcGetChildren();

	bool bIsLeaf();
	CNode* pcGetLeftMostChild(CNode* node, int pos=0);
	CNode* pcGetNextChild();

	void vIncrementCounter();
	int iGetCounter();
	void iSetCounter(int c);
	void vResetCounter();

	CNode* pcGetParent();
	void vSetPtr(CNode* otherNode);

	void vLeaveOnlyValue();

private:
	string s_value;
	CNode* pc_parent;
	int i_counter;
	vector<CNode*> pc_childs_vector;
};

