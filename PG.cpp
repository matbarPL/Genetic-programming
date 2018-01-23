#include "stdafx.h"
#include "PG.h"
#include <time.h> 

CPG::CPG()
{
}

CPG::CPG(int i_pop, int i_iter, int d_cross_prob, int d_mut_prob, string filename)
{
	this->i_pop = i_pop;
	this->i_iter = i_iter;
	this->d_cross_prob = d_cross_prob;
	this->d_mut_prob = d_mut_prob;
	c_file_parser = CParseFile(filename);
	srand(time(NULL));
}


CPG::~CPG()
{
	vDeleteVectorOfPtr(vpc_init_pop);
	vDeleteVectorOfPtr(vpc_parents);
	vDeleteVectorOfPtr(vpc_descendents);
	for (int i = 0; i < vpc_pairs.size(); i++)
	{
		delete vpc_pairs[i].first;
		delete vpc_pairs[i].second;
	}
}

void CPG::vDeleteVectorOfPtr(vector<CTree*> vToRemove)
{
	for (int i = 0; i < vToRemove.size(); i++)
		delete vToRemove[i];
}


void CPG::vInit()
{
	for (int i = 0; i < i_pop; i++)
	{
		CTree* tree = new CTree();
		tree->vSetRandomExpr();
		vpc_init_pop.push_back(tree);
	}
}

void CPG::vGetAllPopTrees()
{
	for (int i = 0; i < i_pop; i++)
	{
		cout << vpc_init_pop[i]->sPreorder()<< endl;
	}
}

void CPG::vpcGetAllDescendents()
{
	for (int i = 0; i < vpc_descendents.size(); i++)
	{
		cout << vpc_descendents[i]->sPreorder() << endl;
	}
}

void CPG::iterate()
{
	vInit();
	vGetAllPopTrees();
	vEvaluate();
	for (int i = 0; i < i_iter; i++)
	{
		vSelection();
		vMakePairs();
		vCrossover();
		vMutate();
		vChangePopulation();
		vEvaluate();

	}
	cout <<endl << endl << "Best tree: " <<endl << cGetBestTree().sPreorder() << endl << " with d_measure " << to_string(cGetBestTree().dGetMeasure()) << endl;
	c_file_parser.vSaveToFile(cGetBestTree().sPreorder() + to_string(cGetBestTree().dGetMeasure()));

}


void CPG::vEvaluate()
{
	c_file_parser.vParse();
	for (int i = 0; i < i_pop; i++)
	{
		vpc_init_pop[i]->vCalculateMeasure(c_file_parser.vGetXY(),c_file_parser.dGetResult());
	}
	c_file_parser.vReset();
}

CTree & CPG::cGetBestTree()
{
	double min = 1000000;
	int index = 0;
	for (int i = 0; i < i_pop; i++)
	{
		if (vpc_init_pop[i]->dGetMeasure() < min)
		{
			min = vpc_init_pop[i]->dGetMeasure();
			index = i;
		}
	}
	return *(vpc_init_pop[index]);
}

void CPG::vSelection()
{
	CTree* firstTree;
	CTree* secondTree;
	for (int i = 0; i < i_pop; i++)
	{
		set<int> s = sGetDiffRandomInRange(0, i_pop, 2);
		firstTree = vpc_init_pop[*s.begin()];
		secondTree = vpc_init_pop[*s.begin() + 1];
		if (firstTree->dGetMeasure() < secondTree->dGetMeasure())
			vpc_parents.push_back(new CTree(*firstTree));
		else 
			vpc_parents.push_back(new CTree(*secondTree));
	}
}

void CPG::vCrossover()
{
	int number;
	for (int i = 0; i < vpc_pairs.size(); i++)
	{
		number = rand()% TRIES;
		pair<CTree*, CTree*> p_tree = vpc_pairs[i];
		if (number == d_cross_prob) 
		{
			p_tree.first->vCrossover(p_tree.second);
			vpc_descendents.push_back(new CTree(*p_tree.first));
			vpc_descendents.push_back(new CTree(*p_tree.second));

		}
		else
		{
			vpc_descendents.push_back(new CTree(*p_tree.first));
			vpc_descendents.push_back(new CTree(*p_tree.second));
		}
	}
}

void CPG::vMutate()
{
	int mutate_option = rand() % 7 + 1;
	int number;
	for (int i = 0; i < vpc_descendents.size(); i++)
	{
		number = rand()% TRIES;
		if(number == d_mut_prob)
			vpc_descendents[i]->vMutate(to_string(mutate_option));
	}
}

void CPG::vChangePopulation()
{
	vpc_init_pop.erase(vpc_init_pop.begin(), vpc_init_pop.end());
	for (int i = 0; i < vpc_descendents.size(); i++)
	{
		vpc_init_pop.push_back(new CTree(*vpc_descendents[i]));
	}
}

void CPG::vMakePairs()
{
	pair<CTree*, CTree*> p;
	for (int i = 2; i < i_pop +2 ; i++)
	{
		if (i % 2 == 0)
		{
			p = make_pair(vpc_parents[i-2], vpc_parents[i -1]);
			vpc_pairs.push_back(p);
		}
	}
}

set<int> CPG::sGetDiffRandomInRange(int min, int max, int quantity)
{
	set<int> s_rand;
	while (s_rand.size() < quantity)
	{
		s_rand.insert(rand() % max + min);
	}
	return s_rand;
}



