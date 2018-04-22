#pragma once
#include "vector.h"

class Bone
{
public:
	vector	direction;	//父坐标系
	float		length;		//骨骼长度
	int		id;				//骨骼ID
	int		dof;			//自由度
	int		degreeOrder[7];	//维度顺序
//	double	coordinateTransformMetrix[4][4];
	double	C[4][4];
	double	Cinv[4][4];
	double	B[4][4];
	char	name[50];		//骨骼名称
	float	axis_x,axis_y,axis_z;	//x，y，z轴
	float   rx,ry,rz;
	float   tx,ty,tz;

	vector	position;	//它用来表示骨骼在世界坐标系中的位置。
	vector	orientation;//方向
	//骨骼数据结构使用的是树状结构，采用深度遍历的方式
	Bone	*child;			//子骨骼节点
	Bone	*sibling;		//兄弟骨骼节点


public:
	Bone(void);
	~Bone(void);
	//设置骨骼位置坐标
	void setPosition(float x,float y,float z);
	//设置骨骼方向
	void setOrientation(float x,float y,float z);
	//设置骨骼名称
	void setName(char* );
	//设置子骨骼节点
	void setChild(Bone*);
	//设置兄弟骨骼节点
	void setSibling(Bone*);
};

