#pragma once
#include "Bone.h"
#include "header.h"
#include "posture.h"

//�Ǽ���
class Character
{
public:
	//ȫ�������洢�������У��������100��
	Bone bones[MAX_BONES];
	//������������
	int boneNumber;
	//�ɻ��������
	int movableBoneNumber;
public:
	Character(void);
	~Character(void);
	//��ȡRoot�ڵ�
	Bone* getRoot();
	//���ӹ���������Ϊ ����ID���������ƣ��������ڵ㣬�������ȣ�xyz���꣬���ɶȡ�����
	void addBone(int i,char *name,vector dir,float length,float axis_x,float axis_y,float axis_z,int dof,int degreeOrder[7],bool);
	//����ID��ȡ����
	Bone *getBoneFromIndex(int );
	//���ݹ������ƻ�ȡ����
	Bone *getBoneFromName(char *name);
	//������̬
	void setPosture(posture*);
	//���ó�����̬
	void setInitialPose();
	//��ȡ����ID
	int getBoneIndex(char*);
};

