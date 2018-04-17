#pragma once
#include "Bone.h"
#include "header.h"
#include "posture.h"

//π«º‹¿‡
class Character
{
public:
	Bone bones[MAX_BONES];
	int boneNumber;
	int movableBoneNumber;
public:
	Character(void);
	~Character(void);
	Bone* getRoot();
	void addBone(int i,char *name,vector dir,float length,float axis_x,float axis_y,float axis_z,int dof,int degreeOrder[7],bool);
	Bone *getBoneFromIndex(int );
	Bone *getBoneFromName(char *name);
	void setPosture(posture*);
	void setInitialPose();
	int	 getBoneIndex(char*);
};

