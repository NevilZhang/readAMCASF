#pragma once
//
class stack
{
public:
	int count;
	double *mat[100];
public:
	stack(void);
	~stack(void);
	void push(double *m,int =4,int =4);
	void pop();
	void current(double*,int =4,int =4);
};

