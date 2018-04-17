#include "stdafx.h"

#include <math.h>
#include <float.h>

//extern AnimationStack g_aniStack;
extern void printSkeletonHierachy(Bone*,int);
//extern Character g_actor;
//extern AnimationStack g_aniStack;

//..........................................................................// it's used for compute bone position
static double	g_currentMatrix[4][4]={
					{1,0,0,0},
					{0,1,0,0},
					{0,0,1,0},
					{0,0,0,1}
				};
static	stack g_MatrixStack;
//...........................................................................//
int readASFFile(Character *actor,char *name){
	printf("start reading asf file\n");
	assert(actor!=NULL);
	FILE *fp;
	if(!(fp=fopen(name,"r")))
		return 0;
	actor->boneNumber=0;
	char key[100];
	while(!feof(fp)){
		fscanf(fp,"%s",key);
		int id = 0;char name[50];vector direction=vector(0,0,0);float length=0;
		float axis_x,axis_y,axis_z;int dof=0;int degreeOrder[7];bool movable=false;
		float x,y,z;
		if(strcmp(key,"#")==0){
			fgets(key,50,fp);
			continue;
		}
		if(strcmp(key,":root")==0){
		/*	fgets(key,100,fp);
			fgets(key,100,fp);
			fgets(key,100,fp);*/
			fscanf(fp,"%s",key);
			if(strcmp(key,"order")==0)
				fgets(key,100,fp);
			fscanf(fp,"%s",key);
			if(strcmp(key,"axis")==0)
				fgets(key,100,fp);
			fscanf(fp,"%s",key);
			if(strcmp(key,"position")==0)
				fscanf(fp,"%f %f %f",actor->getRoot()->position.p,actor->getRoot()->position.p+1,actor->getRoot()->position.p+2);
			fscanf(fp,"%s",key);
			if(strcmp(key,"orientation")==0)
				fscanf(fp,"%f %f %f",actor->getRoot()->orientation.p,actor->getRoot()->orientation.p+1,actor->getRoot()->orientation.p+2);
			continue;
		}
		if(strcmp(key,":bonedata")==0){
			while(fscanf(fp,"%s",key)){

				if(strcmp(key,":hierarchy")==0){
					break;
				}
				if(strcmp(key,"begin")==0){
					continue;
				}
				if(strcmp(key,"id")==0){
					fscanf(fp,"%d",&id);
					continue;
				}
				if(strcmp(key,"name")==0){
					fscanf(fp,"%s",name);
					continue;
				}
				if(strcmp(key,"direction")==0){
					fscanf(fp,"%f %f %f",&direction.p[0],&direction.p[1],&direction.p[2]);
					continue;
				}
				if(strcmp(key,"length")==0){
					fscanf(fp,"%f",&length);
					continue;
				}
				if(strcmp(key,"axis")==0){
					fscanf(fp,"%f %f %f",&axis_x,&axis_y,&axis_z);
					continue;
				}
				if(strcmp(key,"dof")==0){
					//...........................................................//initialize dof and degreeOrder and movable
					dof = 0;
					for(int i=0;i<7;i++)
						degreeOrder[i]=0;
					movable = true;
					//...........................................................//
					char dofstring[50];
					char *t;
					fgets(dofstring,50,fp);
					t = strtok(dofstring," \n");
					while(t){
						if(strcmp(t,"rx")==0)
							degreeOrder[dof]=4;
						if(strcmp(t,"ry")==0)
							degreeOrder[dof]=5;
						if(strcmp(t,"rz")==0)
							degreeOrder[dof]=6;
						dof++;
						t=strtok(NULL," \n");
					}
					continue;
				}
				if(strcmp(key,"end")==0){
					actor->addBone(id,name,direction,length,axis_x,axis_y,axis_z,dof,degreeOrder,movable);
					movable=false;
					dof = 0;
					continue;
				}
			}

		}
		if(strcmp(key,":hierarchy")==0){
			break;
			continue;
		}
		fgets(key,100,fp);
	}
	while(!feof(fp)){
		char *parentName,*childName;Bone* parent,*child;
		fgets(key,100,fp);
		if(strcmp(key,"begin")==0){
			continue;
		}else if(strcmp(key,"end")==0){
			break;
		}else if((parentName = strtok(key," \n"))&&(parent = actor->getBoneFromName(parentName))!=NULL){			
			assert(parent!=NULL);
			while(childName=strtok(NULL," \n")){
				child = actor->getBoneFromName(childName);
				if(parent->child==NULL)
					parent->setChild(child);
				else
					parent->child->setSibling(child);
			}
		}
	}
	fclose(fp);
//	printf("%s\n",key);
//	printSkeletonHierachy(actor->getRoot(),0);
	printf("read ASF file successfully!\n");
	return 1;
}
int readAMCFile(char* name,Character* actor,AnimationStack& g_aniStack){
	if(g_aniStack.count==MAX_ANIMATION_CLIP){
		printf("animation is full\n");
		return 0;
	}
	printf("start reading amc file\n");
	int movableBoneNumber = 29;
	int boneNumber = actor->boneNumber;
	FILE *fp = fopen(name,"r");
	if(fp==NULL)
		return 0;
	int n = 0;//used for counting the lines
	char string[100];
	while(!feof(fp)){
		fgets(string,100,fp);
		if(strcmp(string,"")!=0){
			n++;
		}
	}
	int numOfFrame = (n-3)/(movableBoneNumber+1);//+1 frame number
	animation* ani = g_aniStack.getAnimationFromIndex(g_aniStack.getAnimationNumber());
	g_aniStack.count++;
	ani->numOfPostures = numOfFrame;
	ani->ppos = (posture*)malloc(sizeof(posture)*numOfFrame);
	strcpy(ani->url,name);
///	memset(g_animation.ppos,0,sizeof(posture)*numOfFrame);
	freopen(name,"r",fp);
	while (1) 
	{
		fscanf(fp,"%s",string);
		if(strcmp(string, ":DEGREES") == 0) break;
	}
	int frameNumber = 0;
	char boneName[20];
	float value  = 0;
	for(int f=0;f<numOfFrame;f++){
		value = 0;
		fscanf(fp,"%d",&frameNumber);
		for(int j = 0;j<movableBoneNumber;j++){
			fscanf(fp,"%s",&boneName);
			int i = 0;
			i = actor->getBoneIndex(boneName);
			assert(i<=boneNumber);
			Bone* bone = &(actor->bones[i]);
			for(int d = 0;d<bone->dof;d++){
				fscanf(fp,"%f",&value);
				switch(bone->degreeOrder[d]){
				case 1:ani->ppos[f].bone_translation[i].p[0] = value; break;
				case 2:ani->ppos[f].bone_translation[i].p[1] = value;break;
				case 3:ani->ppos[f].bone_translation[i].p[2] = value;break;
				case 4:ani->ppos[f].bone_rotation[i].p[0] = value;break;
				case 5:ani->ppos[f].bone_rotation[i].p[1] = value;break;
				case 6:ani->ppos[f].bone_rotation[i].p[2] = value;break;
				case 7:ani->ppos[f].bone_length[i] = value;break;
				}
			}
		}
	}
	fclose(fp);
	printf("read %s successfully!\n",name);
	printf("%d frames is read\n",frameNumber);
	return 1;
}
/*
	for example path = ./subject/01_01.amc ,i=2,name = ./subject/01_03.amc
*/
int readSequence(char *path,Character *actor,AnimationStack& g_aniStack,int indent){
	char pre[100]={0},post[100]={0},fullPath[100]={0};
	int number=0,i=0;
	while(path[i++]!='_')
		pre[i-1]=path[i-1];
	sscanf(path+i,"%d%s",&number,post);
	sprintf(fullPath,"%s_%.2d%s",pre,number+indent,post);
	if(readAMCFile(fullPath,actor,g_aniStack))
		readSequence(path,actor,g_aniStack,indent+1);
	return 1;
}
void 	readWeights(Character *actor,CharacterMesh *actorMesh,char *name){
	FILE *fp = fopen(name,"r");
	if(fp == NULL){
		printf("cannot open file %s\n",name);
		return ;
	}
	char key[100];
	fscanf(fp,"%s",key);
	printf("%s\n",key);
	int vertexNumber = 0;
	int influence = 0;
	fscanf(fp,"%d %d",&vertexNumber,&influence);
	printf("%d %d\n",vertexNumber,influence);
	INDEX *jointOrder = (INDEX*)malloc(sizeof(INDEX)*influence);
	for(int i=0;i<influence;i++){
		char jointName[20];
		fscanf(fp,"%s",jointName);
		jointOrder[i]=actor->getBoneIndex(jointName);
	}
	for(int v = 0;v<vertexNumber;v++){
		int o;//for vertex count
		fscanf(fp,"%d",&o);
		actorMesh->vp[v].weight = (float*)malloc(sizeof(float)*influence);
		for(int i=0;i<influence;i++){
			float value =0 ;
			fscanf(fp,"%f",&value);
			actorMesh->vp[v].weight[jointOrder[i]]= value;
		}
	}
	printf("read weights file successfully!\17\n");
}
void computeBonePosition(Bone* b){// it is drawBone,but doesn't draw anything just compute the position of the bone
	if(b){
		if(b->sibling)
			g_MatrixStack.push((double*)g_currentMatrix);

		double temp[4][4],m[4][4],M[4][4];
		loadIdentity(M);
		matrixPostmultiply(g_currentMatrix,b->B);
		matrixPostmultiply(g_currentMatrix,b->C);

		for(int i = 0;i<b->dof;i++){
			switch(b->degreeOrder[i]){

			case 4:rotationX(m,b->rx);matrixPremultiply(M,m);break;
			case 5:rotationY(m,b->ry);matrixPremultiply(M,m);break;
			case 6:rotationZ(m,b->rz);matrixPremultiply(M,m);break;
			case 7:break;
			}
		}

		for(int i = 0;i<b->dof;i++){
			switch(b->degreeOrder[i]){

			case 1:transition(m,b->tx,0,0);matrixPremultiply(M,m);   break;// premultiply
			case 2:transition(m,0,b->ty,0);matrixPremultiply(M,m);break;
			case 3:transition(m,0,0,b->tz);matrixPremultiply(M,m);break;

			case 7:break;
			}
		}

		matrixPostmultiply(g_currentMatrix,M);
		matrixPostmultiply(g_currentMatrix,b->Cinv);

		float o[3],e[3];

		matrix_transform_affine(g_currentMatrix,0,0,0,o);
		matrix_transform_affine(g_currentMatrix,b->direction.x()*b->length,b->direction.y()*b->length,b->direction.z()*b->length,e);

		b->setPosition(e[0],e[1],e[2]);

		if(b->child){
			computeBonePosition(b->child);
		}
		if(b->sibling){
			g_MatrixStack.current((double*)g_currentMatrix);
			g_MatrixStack.pop();
			computeBonePosition(b->sibling);
		}
	}
}
void computeActorBonePosition(Character* actor){// it is drawActor but ranamed for new use
	loadIdentity(g_currentMatrix);

	computeBonePosition(actor->getRoot());
}
double distanceBetweenPostures(Character *g1,Character *g2){
	if(g1&&g2){
		if(g1->boneNumber!=g2->boneNumber)
			return -1;
		else {
			double distance = 0;
			for(int i=0;i<=g1->boneNumber;i++){
				distance += sqrt(pow( ( g1->bones[i].position.x()-g2->bones[i].position.x()),2)+
					pow((g1->bones[i].position.y()-g2->bones[i].position.y()),2)+
					pow((g1->bones[i].position.z()-g2->bones[i].position.z()),2));
			}
			return distance;
		}
	}
}
double distanceBetweenAnimations(animation *a1,animation *a2,Character& g_actor){
	if(a1&&a2){
		Character g1,g2;
		g1 = g2 = g_actor;
		g1.setPosture(a1->ppos+a1->numOfPostures-1);
		computeActorBonePosition(&g1);
		g2.setPosture(a2->ppos+a2->numOfPostures-1);
		computeActorBonePosition(&g2);
		return distanceBetweenPostures(&g1,&g2);
	}
}
void setPlayList(int pl[],AnimationStack& g_aniStack,Character& g_actor){
	double minDist = DBL_MAX,distance=0;
	for(int i=0;i<g_aniStack.getAnimationNumber();i++)
		for(int j=0;j<g_aniStack.getAnimationNumber();j++){
			if(i!=j)
				distance = distanceBetweenAnimations(g_aniStack.getAnimationFromIndex(i),g_aniStack.getAnimationFromIndex(j),g_actor);
			else
				distance = DBL_MAX;
			if(minDist>distance){
				minDist = distance;
				pl[i] = j;
			}
		}
}
void intepolateAnimation(const animation& a1,const animation& a2,animation& transitionAnimation){

	
	posture *p;
	p = (a1.ppos)+a1.numOfPostures-1 ;
	vector rotationStep[MAX_BONES];
	vector transitionStep[MAX_BONES];

	for(int j=0;j<MAX_BONES;j++){
		rotationStep[j] = (a2.ppos->bone_rotation[j]-p->bone_rotation[j])/TRANSITION_FRAME;
	//	transitionStep[j] = (a2.ppos->bone_translation[j]-p->bone_translation[j])/TRANSITION_FRAME;
	}
	for(int j=0;j<MAX_BONES;j++){
		(transitionAnimation.ppos)->bone_rotation[j]=p->bone_rotation[j]+rotationStep[j];
		(transitionAnimation.ppos)->bone_translation[j] = a2.ppos->bone_translation[j];
	}
	for(int i=1;i<TRANSITION_FRAME;i++){
		for(int j=0;j<MAX_BONES;j++){
			(transitionAnimation.ppos+i)->bone_rotation[j]=(transitionAnimation.ppos+i-1)->bone_rotation[j]+rotationStep[j];
			(transitionAnimation.ppos+i)->bone_translation[j]=(transitionAnimation.ppos+i-1)->bone_translation[j];//把所有帧的root位移置为a2的第一帧
		}
	}
	
}

