#pragma once
#include "Bone.h"
#include "header.h"
#include "posture.h"

//骨架类
class Character
{
public:
	//全部骨骼存储在数组中，最大上限100个
	Bone bones[MAX_BONES];
	//计数骨骼数量
	int boneNumber;
	//可活动骨骼数量
	int movableBoneNumber;
public:
	Character(void);
	~Character(void);
	//获取Root节点
	Bone* getRoot();
	//增加骨骼：参数为 骨骼ID，骨骼名称，骨骼父节点，骨骼长度，xyz坐标，自由度。。。
	void addBone(int i,char *name,vector dir,float length,float axis_x,float axis_y,float axis_z,int dof,int degreeOrder[7],bool);
	//根据ID获取骨骼
	Bone *getBoneFromIndex(int );
	//根据骨骼名称获取骨骼
	Bone *getBoneFromName(char *name);
	//设置姿态
	void setPosture(posture*);
	//设置出事姿态
	void setInitialPose();
	//获取骨骼ID
	int getBoneIndex(char*);
};

