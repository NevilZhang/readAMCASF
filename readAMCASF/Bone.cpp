#include "StdAfx.h"
#include "Bone.h"
#include <string.h>
//默认构造骨骼的关节点数据为（0,0,0）
Bone::Bone(void){
	rx=ry=rz=tx=ty=tz=0;
}
Bone::~Bone(void){}

void Bone::setPosition(float x,float y, float z){
	position.setValue(x,y,z);
}
void Bone::setOrientation(float x,float y,float z){
	orientation.setValue(x,y,z);
}
void Bone::setName(char *n){
	strcpy(name,n);
}
void Bone::setChild(Bone* b){
	child = b;
}
//设置兄弟骨骼
void Bone::setSibling(Bone* b){
	if(sibling==NULL)
		sibling = b;
	else
		sibling->setSibling(b);
}