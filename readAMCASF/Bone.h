#pragma once
#include "vector.h"

class Bone
{
public:
	vector	direction;//parent's coordinate system
	float	length;
	int		id;
	int		dof;
	int		degreeOrder[7];
//	double	coordinateTransformMetrix[4][4];
	double	C[4][4];
	double	Cinv[4][4];
	double	B[4][4];
	char	name[50];
	float	axis_x,axis_y,axis_z;
	float   rx,ry,rz;
	float   tx,ty,tz;

	vector	position;//             it's used to represent the position of a bone in world coordinate system
	vector	orientation;
	Bone	*child;
	Bone	*sibling;


public:
	Bone(void);
	~Bone(void);
	void setPosition(float x,float y,float z);
	void setOrientation(float x,float y,float z);
	void setName(char* );
	void setChild(Bone*);
	void setSibling(Bone*);
};

