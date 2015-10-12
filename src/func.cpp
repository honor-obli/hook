/*
 * func.cpp
 *
 *  Created on: 2015/10/12
 *      Author: honor
 */
#include <iostream>
#include "func.h"
using namespace std;



int funcA(){
	return funcB()+1;
}

int funcB(){
	return 2;
}

int stub_funcB(){
	return 3;
}
