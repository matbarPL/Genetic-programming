// TreeEvaluation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" 
#include "Tree.h"
#include "TreeInterface.h"
#include "PG.h"
#include "ParseFile.h"
#include <iostream>
#include<istream>
#include<fstream>
#include<algorithm>

int main()
{
	CPG pg(100, 5, 2, 5,"sinx.txt");
	pg.iterate();

	
	getchar();
    return 0;

}


