#pragma once
#include "vector.h"
#include "header.h"

//姿态类
class posture
{
public:
		//root骨头节点		
		vector root_pos;
								
		
		//Rotation (x, y, z) of all bones at a particular time frame in their local coordinate system.
		//If a particular bone does not have a certain degree of freedom, 
		//the corresponding rotation is set to 0.
		//The order of the bones in the array corresponds to their ids in .ASf file: root, lhipjoint, lfemur, ...
		//骨骼旋转变换
		vector bone_rotation[MAX_BONES];
		//骨骼位置变换
		vector bone_translation[MAX_BONES];
		//骨骼长度
		float bone_length[MAX_BONES];
public:
	posture(void);
	~posture(void);
};

