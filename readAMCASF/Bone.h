#pragma once
#include "vector.h"

class Bone
{
public:
	vector	direction;	//������ϵ
	float		length;		//��������
	int		id;				//����ID
	int		dof;			//���ɶ�
	int		degreeOrder[7];	//ά��˳��
//	double	coordinateTransformMetrix[4][4];
	double	C[4][4];
	double	Cinv[4][4];
	double	B[4][4];
	char	name[50];		//��������
	float	axis_x,axis_y,axis_z;	//x��y��z��
	float   rx,ry,rz;
	float   tx,ty,tz;

	vector	position;	//��������ʾ��������������ϵ�е�λ�á�
	vector	orientation;//����
	//�������ݽṹʹ�õ�����״�ṹ��������ȱ����ķ�ʽ
	Bone	*child;			//�ӹ����ڵ�
	Bone	*sibling;		//�ֵܹ����ڵ�


public:
	Bone(void);
	~Bone(void);
	//���ù���λ������
	void setPosition(float x,float y,float z);
	//���ù�������
	void setOrientation(float x,float y,float z);
	//���ù�������
	void setName(char* );
	//�����ӹ����ڵ�
	void setChild(Bone*);
	//�����ֵܹ����ڵ�
	void setSibling(Bone*);
};

