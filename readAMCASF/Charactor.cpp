#include "StdAfx.h"
#include "Charactor.h"
#include "vector.h"
#include <string.h>

Character::Character(void)
{
	boneNumber = 0;
	movableBoneNumber = 1;

	Bone *root = &bones[0];
	root->setPosition(0.0,0.0,0.0);
	root->setOrientation(0.0,0.0,0.0);
	root->setName("root");
	for(int i=0;i<6;i++){
		root->degreeOrder[i] = i+1;
	}
	root->dof = 6;
}


Character::~Character(void)
{
}

Bone* Character::getRoot(void)
{
	return bones;
}
void Character::addBone(int i,char *name,vector dir,float l,float axis_x,float axis_y,float axis_z,int dof,int degreeOrder[7],bool movable){
	Bone *b;
	b = &bones[++boneNumber];
	b->id = i;
	strcpy(b->name,name);
	b->direction = dir;
	b->length=l;
	b->axis_x = axis_x;
	b->axis_y = axis_y;
	b->axis_z = axis_z;
	b->dof = dof;
	for(int i=0;i<7;i++)
		b->degreeOrder[i]=degreeOrder[i];
	if(movable)
		movableBoneNumber++;

}
Bone *Character::getBoneFromIndex(int i){
	return &bones[i];
}
Bone *Character::getBoneFromName(char *name){
	for(int i=0;i<=boneNumber;i++){
		if(strcmp(bones[i].name,name)==0){
			return &bones[i];
		}
	}
}
void Character::setPosture(posture* p){
	for(int i=0;i<=boneNumber;i++){
		bones[i].rx = p->bone_rotation[i].x();
		bones[i].ry = p->bone_rotation[i].y();
		bones[i].rz = p->bone_rotation[i].z();
		bones[i].tx = p->bone_translation[i].x();
		bones[i].ty = p->bone_translation[i].y();
		bones[i].tz = p->bone_translation[i].z();
//		bones[i].length = p->bone_length[i];//长度不能直接赋值，因为每一段骨骼的长度都很重要，如果赋了4.3e8
	}
}
void Character::setInitialPose(){
	for(int i=0;i<=boneNumber;i++){
		bones[i].rx = 0;
		bones[i].ry = 0;
		bones[i].rz = 0;
		bones[i].tx = 0;
		bones[i].ty = 0;
		bones[i].tz = 0;
//		bones[i].length = p->bone_length[i];//长度不能直接赋值，因为每一段骨骼的长度都很重要，如果赋了4.3e8
	}
}
int Character::getBoneIndex(char* n){
	for(int i=0;i<=boneNumber;i++){
		if(strcmp(bones[i].name,n)==0){
			return i;
		}
	}
}