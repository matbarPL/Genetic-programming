#include "stdafx.h"
#include "Tree.h"



CTree::CTree()
{
	pc_root = nullptr;
	d_result = 0;
	d_measure = 0; 
	s_expr = "";
}

CTree::CTree(string s_value)
{
	pc_root = nullptr;
	d_result = 0;
	c_parser.vParse(s_value);
	d_measure = 0;
	s_expr = "";
}

CTree& CTree::operator=(CTree& otherTree)
{
	pc_root = new CNode();
	*pc_root = *otherTree.pc_root;

	vector<CNode*>::iterator i_iter;
	vpc_leafs.erase(i_iter = vpc_leafs.begin(), i_iter = vpc_leafs.end());
	
	vSetLeafs(pc_root);
	
	d_measure = otherTree.d_measure;
	s_expr = otherTree.s_expr;
	return (*this);
}

ostream & operator<<(ostream & stream, CTree tree)
{
	stream << tree.sPreorder() << endl;
	return stream;
}

CTree CTree::operator+(CTree& otherTree)
{
	CTree resTree(*this);
	CParseString parser2;
	CNode* leftMostLeaf = resTree.pcGetLeftMostLeaf(resTree.pc_root);
	parser2.vParse(otherTree.sPostorder());
	resTree.vParseSingleTree(leftMostLeaf, parser2);
	return (resTree);
}

CTree::CTree(CTree& otherTree)
{
	pc_root = new CNode();
	*pc_root = *otherTree.pc_root;
	vector<CNode*>::iterator i_iter;
	vpc_leafs.erase(i_iter = vpc_leafs.begin(), i_iter = vpc_leafs.end());
	vSetLeafs(pc_root);
	d_measure = otherTree.d_measure;
	s_expr = otherTree.s_expr;
}

CTree::~CTree()
{
	if (pc_root != nullptr)
		delete pc_root;
	for (int i = 0; i < vpc_leafs.size(); i++)
		vpc_leafs[i] = nullptr;

}

void CTree::vDeleteVector(vector<CNode*> v)
{
	if (v.size() != 0) {
		for (vector<CNode*>::iterator i_iter = v.begin(); i_iter != v.end(); ++i_iter) {
			delete(*i_iter);
		}
		v.clear();
	}
}

void CTree::vMutate(string op)
{
	CNode* processedNode;
	int type;
	int option = stoi(op);
	int leafsNumber = rand() % vpc_leafs.size() ;
	int leafsNumber2;
	
	int nrOfNodeToChange;
	int nrOfNodeToChange2;

	vector<CNode*> nodesVec = vpcGetAllNodes();
	int allNodesSize = nodesVec.size();
	if (option == LEAF_NEW_LEAF) //replace a leaf with a new, randomly generated leaf
	{
		processedNode = vpc_leafs[rand()%vpc_leafs.size() ];
		type = c_parser.iCheckTypeOfString(processedNode->sGetValue());
		processedNode->vSetValue(to_string(rand()% MAX_INT_IN_NODE ));
	}
	else if (option == LEAF_NEW_NODE) //replace a leaf with a new, randomly generated node
	{
		CTree resTree;
		resTree.vSetRandomExpr();
		leafsNumber = rand() % vpc_leafs.size();
		processedNode = vpc_leafs[leafsNumber];
		processedNode = resTree.pcGetRoot();
	}
	else if (option == NODE_NEW_LEAF) //replace a node with a new, randomly generated
	{
		if(allNodesSize !=1)
			nodesVec.erase(nodesVec.begin());
		allNodesSize = nodesVec.size();
		nrOfNodeToChange = rand() % allNodesSize ;
		processedNode = nodesVec[nrOfNodeToChange];
		processedNode->vLeaveOnlyValue();
		processedNode->vSetValue(to_string(rand()% MAX_INT_IN_NODE)); 
	}
	else if (option == NODE_NEW_NODE) //replace an existing node with a new, randomly generated node
	{
		vector<CNode*> temp = vpcGetAllNodes();
		CTree resTree;
		resTree.vSetRandomExpr();
		allNodesSize = temp.size(); 
		nrOfNodeToChange = rand() % allNodesSize ;
		processedNode = temp[nrOfNodeToChange];
		*processedNode = *(resTree.pcGetRoot());
		vSetLeafs(pc_root);
	}
	else if (option == NODE_NODE) // swap two nodes
	{
		if (allNodesSize != 0 && allNodesSize != 1)
			nodesVec.erase(nodesVec.begin());
		allNodesSize = nodesVec.size();
		nrOfNodeToChange = rand() % allNodesSize;
		nrOfNodeToChange2 = rand() % allNodesSize;

		while (nrOfNodeToChange == nrOfNodeToChange2)
		{
			nrOfNodeToChange2 = rand() % allNodesSize;
		}
		if ( (bCheckIfDescendents(nodesVec[nrOfNodeToChange], nodesVec[nrOfNodeToChange2]))||
			(bCheckIfDescendents(nodesVec[nrOfNodeToChange2], nodesVec[nrOfNodeToChange])) ) {
			return;
		}
		else {
			CNode* tempNode = new CNode();
			*tempNode = *nodesVec[nrOfNodeToChange];
			*nodesVec[nrOfNodeToChange] = *nodesVec[nrOfNodeToChange2];
			*nodesVec[nrOfNodeToChange2] = *tempNode;
			vSetLeafs(pc_root);
		}
	}
	else if (option == LEAF_LEAF) //swap two leafs
	{
		leafsNumber2 = rand() % vpc_leafs.size(); 
		CNode* temp = new CNode(*vpc_leafs[leafsNumber]); 
		*vpc_leafs[leafsNumber] = *vpc_leafs[leafsNumber2];
		*vpc_leafs[leafsNumber2] = *temp;

	}
	else if (option == NODE_LEAF) //swap a node and a leaf
	{
		if (allNodesSize!=0 && allNodesSize !=1)
			nodesVec.erase(nodesVec.begin());
		allNodesSize = nodesVec.size();
		nrOfNodeToChange = rand() % allNodesSize;
		CNode* temp = new CNode(*vpc_leafs[leafsNumber]);
		*vpc_leafs[leafsNumber] = *nodesVec[nrOfNodeToChange];
		*nodesVec[nrOfNodeToChange] = *temp;
		vSetLeafs(pc_root);
	}
}



void CTree::vCrossover(CTree* otherTree)
{
	int firstNode, secondNode;
	vector<CNode*> vecNodes1 = vpcGetAllNodes();
	vector<CNode*> vecNodes2 = otherTree->vpcGetAllNodes();
	firstNode = rand() % vecNodes1.size();
	secondNode = rand() % vecNodes2.size();
	CNode* tempNode = new CNode(*vecNodes1[firstNode]);
	*vecNodes1[firstNode] = *vecNodes2[secondNode];
	*vecNodes2[secondNode] = *tempNode;

}

void CTree::vSetRandomExpr()
{
	vResetExpression();
	c_parser.vParse(c_parser.sGenerateRandomExpr());
	vParseTree();
}

bool CTree::bCheckIfDescendents(CNode* node1, CNode * node2) //checking if node1 is a descendent of node2
{
	bool found = false;
	vector<CNode*> node1Descendents = vpcGetAllDescendents(node1);
	int i_counter = 0;
	while (i_counter < node1Descendents.size() && !found)
	{
		if (node1Descendents[i_counter] == node2)
			found = true;
		else
			i_counter++;
	}
	return found;
}

vector<CNode*> CTree::vpcGetAllDescendents(CNode* node) //get vector of all descendents of the given node
{
	vector<CNode*> helper = node->vpcGetChildren();
	vector<CNode*> res;
	int nrOfChildren = helper.size();
	int i_counter = 0;

	while (helper.size() != 0)
	{
		for (int i = 0; i < nrOfChildren; i++)
		{
			res.push_back(helper[i]);
		}
		helper = helper[i_counter]->vpcGetChildren();
		nrOfChildren = helper.size();
		if (i_counter == nrOfChildren)
			i_counter = 0;
		else
			i_counter++;
		
	}
	return res;
}

void CTree::vRestartOldAndSetNewExpression(string s_value)
{
	vResetExpression();
	c_parser.vParse(s_value);
}

void CTree::vResetExpression()
{
	pc_root = nullptr;
	c_parser.vResetParser();
	vector<CNode*>::iterator i_iter;
	vpc_leafs.erase(i_iter = vpc_leafs.begin(), i_iter = vpc_leafs.end());
}

CNode* CTree::pcGetRoot()
{
	return pc_root;
}

void CTree::vSetRoot(CNode* rootToSet)
{
	pc_root = rootToSet;
}

void CTree::vSetLeafs(CNode* node)
{
	vector<CNode*>::iterator i_iter;
	vector<CNode*> wektor = node->vpcGetChildren();
	for (i_iter = wektor.begin(); i_iter != wektor.end(); ++i_iter) {
		vSetLeafs((*i_iter));
	}
	if (node->bIsLeaf())
		vpc_leafs.push_back(node);
}

void CTree::vSetMeasure(double d_measure)
{
	this->d_measure = d_measure;
}

double CTree::dGetMeasure()
{
	return d_measure;
}

CNode* CTree::pcGetLeftMostLeaf(CNode* node)
{
	if (vpc_leafs[0] != nullptr)
		return vpc_leafs[0];
}

void CTree::vParseTree()
{
	vParseSingleTree(pc_root, c_parser);
}

void CTree::vParseSingleTree(CNode* node, CParseString c_parser, int pos)
{
	string s_value = c_parser.sGetFirst();
	c_parser.vRemoveFirst();
	CNode* processedNode = new CNode();
	int flag = 0;
	if (node == nullptr) {
		pc_root = new CNode(s_value);
		processedNode = pc_root;
	}
	else {
		pc_root->pcGetLeftMostChild(pc_root, pos)->vSetValue(s_value);
		processedNode->vSetPtr(pc_root->pcGetLeftMostChild(pc_root,pos));
		processedNode = pc_root->pcGetLeftMostChild(pc_root,pos);
		flag = 2;
	}
	c_parser.iCheckTypeOfString(s_value);
	int type = 0;
	int i_counter = 0;
	while (!c_parser.bParsedFinished()) 
	{
		s_value = c_parser.sGetFirst();
		type = c_parser.iCheckTypeOfString(s_value);
		if (type == SINUS_TYPE || type == COSINUS_TYPE) 
		{
			//this is unary operator so we will need one child 
			processedNode->vAddChild(processedNode, s_value);
			processedNode = processedNode->pcGetNextChild();
		}
		else if (type == PLUS_TYPE || type == MINUS_TYPE || type == PRODUCT_TYPE || type == DIV_TYPE) 
		{
			//binary operator so we will need two childs
			processedNode->vAddChild(processedNode, s_value);
			processedNode = processedNode->pcGetNextChild();
		}
		else if (type == CORR_NUM_TYPE || type == CORR_VAR_TYPE) 
		{
			//number or consant so we have to check if this is proper value 
			if (!bCheckIfNodeDone(processedNode)) 
			{
				processedNode->vAddChild(processedNode, s_value);
				vpc_leafs.push_back(processedNode->pcGetChild());
				processedNode->vIncrementCounter();
			}
		}

		while (bCheckIfNodeDone(processedNode) && processedNode != pc_root) {
			processedNode = processedNode->pcGetParent();
		}
		
		c_parser.vRemoveFirst();
	}
	vReset();
	s_expr = sPreorder();
}

void CTree::vReset()
{
	vResetHelper(pc_root);
}

void CTree::vResetHelper(CNode* node)
{
	node->vResetCounter();
	vector<CNode*>::iterator i_iter;
	vector<CNode*> wektor = node->vpcGetChildren();
	for (i_iter = wektor.begin(); i_iter != wektor.end(); ++i_iter) {
		vResetHelper((*i_iter));
	}
}

void CTree::vSetValuesForVars(string input)
{
	CParseString c_parser;
	c_parser.vParse(input);
	string value1 = c_parser.sGetFirst(); //x
	c_parser.vRemoveFirst();
	string value2 = c_parser.sGetFirst(); //y
	c_parser.vRemoveFirst();
	for (int i = 0; i < vpc_leafs.size(); i++)
	{
		if (vpc_leafs[i]->sGetValue() == "x")
			vpc_leafs[i]->vSetValue(value1);
		else if (vpc_leafs[i]->sGetValue() == "y")
			vpc_leafs[i]->vSetValue(value2);
	}	
}


bool CTree::bCheckIfNodeDone(CNode* node)
{
	int type = c_parser.iCheckTypeOfString(node->sGetValue());
	if (type == SINUS_TYPE || type == COSINUS_TYPE)
		type = 1;
	else if (type == PLUS_TYPE || type == MINUS_TYPE || type == PRODUCT_TYPE || type == DIV_TYPE)
		type = 2;
	else
		type = 0;
	return type == node->iGetCounter();
}

void CTree::vEvaluateTree()
{
	stack<double> stack;
	double d_x, d_y;
	CParseString helper;
	helper.vParse(sPostorder());
	int type;
	string s_value;
	while (!helper.bParsedFinished()) {
		s_value = helper.sGetFirst();
		helper.vRemoveFirst();
		type = helper.iCheckTypeOfString(s_value);
		if (type == CORR_NUM_TYPE) {
			stack.push(stod(s_value));
		}
		else if (type == PLUS_TYPE || type == MINUS_TYPE || type == PRODUCT_TYPE || type == DIV_TYPE) {
			d_x = stack.top();
			stack.pop();
			d_y = stack.top();
			stack.pop();
			if (type == PLUS_TYPE)
				stack.push(d_x + d_y);
			else if (type == MINUS_TYPE)
				stack.push(d_y - d_x);
			else if (type == PRODUCT_TYPE)
				stack.push(d_x*d_y);
			else if (type == DIV_TYPE) {
				if(d_x !=0)
					stack.push(d_y / d_x);
				else if(d_y!=0) {
					stack.push(d_x / d_y);
				}
				else {
					stack.push(0);
				}
				
			}
		}
		else if (type == SINUS_TYPE || type == COSINUS_TYPE) {
			d_x = stack.top();
			stack.pop();
			if (type == SINUS_TYPE)
				stack.push(sin(d_x));
			else if (type == COSINUS_TYPE) {
				stack.push(cos(d_x));
			}
		}
	}
	d_result = stack.top();

}

string CTree::sPostorder()
{
	string sPostorder = "";
	return sPostorderTraversal(pc_root,sPostorder);
}

string CTree::sPostorderTraversal(CNode* node, string& sPostorder)
{
	vector<CNode*>::iterator i_iter;
	vector<CNode*> wektor = node->vpcGetChildren();
	for (i_iter = wektor.begin(); i_iter != wektor.end(); ++i_iter) {
		sPostorderTraversal(*i_iter,sPostorder);
	}
	sPostorder += node->sGetValue() + " ";
	return sPostorder;
}

string CTree::sPreorder()
{
	string sPreorder = "";
	return sPreorderTraversal(pc_root,sPreorder);
}

string CTree::sPreorderTraversal(CNode* node, string& sPreorder)
{
	sPreorder += node->sGetValue() + " ";
	vector<CNode*>::iterator i_iter;
	vector<CNode*> wektor = node->vpcGetChildren();
	for (i_iter = wektor.begin(); i_iter != wektor.end(); ++i_iter) {
		sPreorderTraversal(*i_iter,sPreorder);
	}
	return sPreorder;
}

vector<CNode*> CTree::vpcGetAllNodes()
{
	vector<CNode*> allNodes;
	allNodes.push_back(pc_root);
	return vpcGetAllNodes(pc_root, allNodes);
}

vector<CNode*> CTree::vpcGetAllNodes(CNode* node)
{
	vector<CNode*> allNodes;
	allNodes.push_back(node);
	return vpcGetAllNodes(node, allNodes);
}

vector<CNode*> CTree::vpcGetAllNodes(CNode* node, vector<CNode*>& res)
{
	CParseString c_parser;
	for (int i = 0; i < node->iGetNumberOfChildren(); i++)
	{
		if (c_parser.iCheckGeneralTypeOfString(node->vpcGetChildren()[i]->sGetValue()) ==2)
		{
			res.push_back(node->vpcGetChildren()[i]);
			vpcGetAllNodes(node->vpcGetChildren()[i], res);
		}
	}

	return res;
}

double CTree::dEvalTreeAndGetResult()
{
	vEvaluateTree();
	return d_result;
}

double CTree::dGetResult()
{
	return d_result;
}


void CTree::vCalculateMeasure(vector<string> input, vector<double> res)
{
	double tempRes = 0;
	CTree copy = CTree(*this);
	double tempMes = 0;

	for (int i = 0; i < input.size(); i++)
	{
		vSetValuesForVars(input[i]);
		tempRes = dEvalTreeAndGetResult();
		tempMes += pow(tempRes - res[i], 2);
		*this = copy;
	}
	this->vSetMeasure(tempMes);
}