#include "StdAfx.h"
#include "Bone.h"
#include <string.h>

Bone::Bone(void)
{
	rx=ry=rz=tx=ty=tz=0;
}


Bone::~Bone(void)
{
}
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
void Bone::setSibling(Bone* b){
	if(sibling==NULL)
		sibling = b;
	else
		sibling->setSibling(b);
}