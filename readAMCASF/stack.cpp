#include "StdAfx.h"

stack::stack(void)
{
	count = 0;
}


stack::~stack(void)
{
}
void stack::push(double *m,int width,int height){
	double *item = (double*)malloc(sizeof(double)*width*height);
	for(int i=0;i<width;i++)
		for(int j=0;j<height;j++)
			item[i*width+j]=m[i*width+j];
	mat[count++]=item;
}
void stack::pop(){
	free(mat[--count]);
}
void stack::current(double*m,int width,int height){
	for(int i=0;i<width;i++)
		for(int j=0;j<height;j++)	
			m[i*width+j]=mat[count-1][i*width+j];
}