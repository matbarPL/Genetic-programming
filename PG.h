#pragma once
#include "Tree.h"
#include"ParseFile.h"
#include<vector>
#include<string>
#include<cmath>
#include<math.h>
#define TRIES 100

using namespace std;
class CPG
{
public:
	CPG();
	CPG(int i_pop, int i_iter, int cross_pob, int d_mut_prob, string filename);
	~CPG();
	void vInit();
	void vGetAllPopTrees();
	void vpcGetAllDescendents();
	void vEvaluate();
	CTree& cGetBestTree();
	void vSelection();
	void vCrossover();
	void vMutate();
	void vMakePairs();
	void vChangePopulation();
	void iterate();
	void vDeleteVectorOfPtr(vector<CTree*> vToRemove);
	set<int> sGetDiffRandomInRange(int min, int max, int quantity);
private:
	int i_pop;
	int i_iter;
	double d_cross_prob;
	double d_mut_prob;
	
	CParseFile c_file_parser;
	vector<CTree*> vpc_init_pop;
	vector<double> v_tree_res;
	vector<CTree*> vpc_parents;
	vector<pair<CTree*, CTree*>> vpc_pairs;
	vector<CTree*> vpc_descendents;
};

