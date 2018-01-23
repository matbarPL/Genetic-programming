#include "stdafx.h"
#include "Node.h"


CNode::CNode()
{
	pc_parent = nullptr;
	s_value = "";
	i_counter = 0;
}

CNode::CNode(string valueToSet)
{
	pc_parent = nullptr;
	s_value = valueToSet;
	i_counter = 0;
}

CNode::CNode(CNode* parentToSet, string valueToSet) {
	pc_parent = parentToSet;
	s_value = valueToSet;
	i_counter = 0;
}

CNode::CNode(CNode& otherNode) {
	if (otherNode.pc_parent != nullptr)
		pc_parent = new CNode(*otherNode.pc_parent);
	else
		pc_parent = nullptr;
	s_value = otherNode.s_value;
	i_counter = otherNode.i_counter;
	vector<CNode*>::iterator i_iter;
	pc_childs_vector.erase(i_iter = pc_childs_vector.begin(), i_iter = pc_childs_vector.end());
	for (int i = 0; i < otherNode.pc_childs_vector.size(); i++) {
		CNode* node = new CNode();
		node->vSetParent(otherNode.pc_childs_vector[i]->pc_parent);
		node->iSetCounter(otherNode.pc_childs_vector[i]->i_counter);
		node->vSetValue(otherNode.pc_childs_vector[i]->s_value);
		pc_childs_vector.push_back(node);
	}
}

CNode& CNode::operator=(CNode& otherNode)
{
	if (otherNode.pc_parent != nullptr)
		pc_parent = new CNode(*otherNode.pc_parent);
	else
		pc_parent = nullptr;
	s_value = otherNode.s_value;
	i_counter = otherNode.i_counter;
	vector<CNode*>::iterator i_iter;
	pc_childs_vector.erase(i_iter = pc_childs_vector.begin(), i_iter = pc_childs_vector.end());
	for (int i = 0; i < otherNode.pc_childs_vector.size(); i++) {
		CNode* node = new CNode();
		*node = *otherNode.pc_childs_vector[i];
		node->vSetParent(otherNode.pc_childs_vector[i]->pc_parent);
		node->iSetCounter(otherNode.pc_childs_vector[i]->i_counter);
		node->vSetValue(otherNode.pc_childs_vector[i]->s_value);
		pc_childs_vector.push_back(node);
	}
	
	return (*this);
}


CNode::~CNode()
{
	if (pc_parent != nullptr)
		pc_parent = nullptr;
	for (int i = 0; i < pc_childs_vector.size(); i++)
		pc_childs_vector[i] = nullptr;
}

void CNode::vSetPtr(CNode* otherNode)
{
	pc_parent = otherNode->pc_parent;
	s_value = otherNode->s_value;
	i_counter = otherNode->i_counter;
	pc_childs_vector = otherNode->pc_childs_vector;
}

void CNode::vLeaveOnlyValue()
{
	CNode* newNode = new CNode(*&this->pc_parent, *&this->s_value);
	*this = *newNode;
}

bool CNode::operator==(CNode& otherNode)
{
	bool equalVector = equal(begin(pc_childs_vector), end(pc_childs_vector), begin(otherNode.pc_childs_vector), end(otherNode.pc_childs_vector),
		[](const CNode* one, const CNode* two) {return one == two;});
	return pc_parent == otherNode.pc_parent && s_value == otherNode.s_value && equalVector;
}

bool CNode::operator!=(CNode& otherNode)
{
	bool equalVector = equal(begin(pc_childs_vector), end(pc_childs_vector), begin(otherNode.pc_childs_vector), end(otherNode.pc_childs_vector),
		[](const CNode* one, const CNode* two) {return one == two;});
	if (s_value == otherNode.s_value && pc_parent == otherNode.pc_parent && equalVector)
		return true;
	else
		return false;
}

string CNode::sGetValue()
{
	return s_value;
}

void CNode::vSetValue(string valueToSet)
{
	s_value = valueToSet;
}

void CNode::vAddChild()
{
	pc_childs_vector.push_back(new CNode());
}

void CNode::iDeleteChildren()
{
	for (vector<CNode*>::iterator i_iter = pc_childs_vector.begin(); i_iter != pc_childs_vector.end(); ++i_iter) {
		delete(*i_iter);
	}
	pc_childs_vector.clear();
}

void CNode::vAddChild(string childValue)
{
	pc_childs_vector.push_back(new CNode(childValue));
}

void CNode::vAddChild(CNode* parentToSet, string childValue)
{
	pc_childs_vector.push_back(new CNode(parentToSet, childValue));
}

int CNode::iGetNumberOfChildren()
{
	return pc_childs_vector.size();
}

void CNode::vIncrementCounter()
{
	i_counter++;
}

int CNode::iGetCounter()
{
	return i_counter;
}

void CNode::iSetCounter(int c)
{
	i_counter = c;
}

CNode* CNode::pcGetChild()
{
	if (pc_childs_vector.size() == 0)
		return nullptr;
	else
		return pc_childs_vector[pc_childs_vector.size() - 1];
}

CNode* CNode::pcGetChild(int pos)
{
	if (pos < pc_childs_vector.size())
		return pc_childs_vector[pos];
	else
		return nullptr;
}

string CNode::sGetValueFromChild(int pos)
{
	if (pos < pc_childs_vector.size())
		return pc_childs_vector[pos]->sGetValue();
	else
		return "";
}

void CNode::vSetParent(CNode* parentNode)
{
	pc_parent = parentNode;
}

bool CNode::bIsLeaf()
{
	return pc_childs_vector.size() == 0;
}

CNode* CNode::pcGetLeftMostChild(CNode* node,int pos)
{
	vector<CNode*> wektor = pc_childs_vector;
	CNode* helpNode = node;
	while (wektor.size() != 0) {
		helpNode = wektor[0];
		wektor = helpNode->pc_childs_vector;
	}
	return helpNode;
}


CNode* CNode::pcGetNextChild()
{
	CNode* child = pc_childs_vector[i_counter];
	i_counter++;
	return child;
}

vector<CNode*> CNode::vpcGetChildren()
{
	vector<CNode*> empty;
	if (pc_childs_vector.size() != 0)
		return pc_childs_vector;
	else
		return empty;
}

CNode* CNode::pcGetParent()
{
	if (pc_parent != nullptr)
		return pc_parent;
}

void CNode::vResetCounter()
{
	i_counter = 0;
}

