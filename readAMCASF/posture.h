#pragma once
#include "vector.h"
#include "header.h"

//×ËÌ¬Àà
class posture
{
public:
		vector root_pos;								
		
		//Rotation (x, y, z) of all bones at a particular time frame in their local coordinate system.
		//If a particular bone does not have a certain degree of freedom, 
		//the corresponding rotation is set to 0.
		//The order of the bones in the array corresponds to their ids in .ASf file: root, lhipjoint, lfemur, ...
		vector bone_rotation[MAX_BONES];
		vector bone_translation[MAX_BONES];
		float bone_length[MAX_BONES];
public:
	posture(void);
	~posture(void);
};

