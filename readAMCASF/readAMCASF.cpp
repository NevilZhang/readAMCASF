// readAMCASF.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Global variables
int winWidth = 400,winHeight = 400;
float eye[4]={48,0,48,0};
float viewPoint[4]={0,0,0,0};
float up[3] = {0,1,0};
///..............................................
Character g_actor;
CharacterMesh g_actor_mesh;
animation transitionAnimation;
AnimationStack g_aniStack;
int g_currentAnimationIndex = 0;

double	g_currentMatrix[4][4]={
	{1,0,0,0},
	{0,1,0,0},
	{0,0,1,0},
	{0,0,0,1}
};
stack g_MatrixStack;
int playList[MAX_ANIMATION_CLIP]= {
0
};
////.............................................
void printSkeletonHierachy(Bone* b,int depth);
extern void readAMCFile(char*,Character *actor,AnimationStack&);
extern int readASFFile(Character *actor,char *name);
extern int readObjFile(CharacterMesh *actor,char *fileName);
extern void 	readWeights(Character *actor,CharacterMesh *actorMesh,char *name);
extern void setPlayList(int pl[],AnimationStack&,Character&);
extern void intepolateAnimation(const animation& a1,const animation& a2,animation&);
extern int readSequence(char *path,Character *actor,AnimationStack&,int i);
///.............................................

bool bAnimated = true;
bool bDrawBone = false;
bool bLoop = true;
bool btransition = false;
static int f = 0;
//...............................................
void printSkeletonHierachy(Bone* b,int depth)
{
	if(b){
		int i = 0;
		while(i<depth){
			printf(" ");
			i++;
		}
		printf("%s\n",b->name);
		if(b->child)
			printSkeletonHierachy(b->child,depth+1);
		if(b->sibling)
			printSkeletonHierachy(b->sibling,depth);
	}
}

void computeMatrixCandCinv(Bone* b){
	if(b){
		double Rx[4][4],Ry[4][4],Rz[4][4],T[4][4],tmp1[4][4],tmp2[4][4];
		if(b->id==0){
			rotationX(Rx,b->orientation.x());
			rotationY(Ry,b->orientation.y());
			rotationZ(Rz,b->orientation.z());
	/*		matrix_mult(Rz,Ry,tmp2);
			matrix_mult(tmp2,Rx,b->C);*/
			loadIdentity(b->C);
			matrixPremultiply(b->C,Rx);
			matrixPremultiply(b->C,Ry);
			matrixPremultiply(b->C,Rz);
			//matrix_mult(Rz,Ry,tmp2);
			//matrix_mult(tmp2,Rx,b->C);

			rotationX(Rx,-b->orientation.x());
			rotationY(Ry,-b->orientation.y());
			rotationZ(Rz,-b->orientation.z());
			//matrix_mult(Rx,Ry,tmp2);
			//matrix_mult(tmp2,Rz,b->Cinv);
			loadIdentity(b->Cinv);
			matrixPostmultiply(b->Cinv,Rx);
			matrixPostmultiply(b->Cinv,Ry);
			matrixPostmultiply(b->Cinv,Rz);
			//matrix_mult(Rx,Ry,tmp2);
			//matrix_mult(tmp2,Rz,b->Cinv);
		}else{
			rotationX(Rx,b->axis_x);
			rotationY(Ry,b->axis_y);
			rotationZ(Rz,b->axis_z);
			//matrix_mult(Rz,Ry,tmp2);
			//matrix_mult(tmp2,Rx,b->C);
			loadIdentity(b->C);
			matrixPremultiply(b->C,Rx);
			matrixPremultiply(b->C,Ry);
			matrixPremultiply(b->C,Rz);

			rotationX(Rx,-b->axis_x);
			rotationY(Ry,-b->axis_y);
			rotationZ(Rz,-b->axis_z);
			//matrix_mult(Rx,Ry,tmp2);
			//matrix_mult(tmp2,Rz,b->Cinv);
			loadIdentity(b->Cinv);
			matrixPostmultiply(b->Cinv,Rx);
			matrixPostmultiply(b->Cinv,Ry);
			matrixPostmultiply(b->Cinv,Rz);
		}
		if(b->child)
			computeMatrixCandCinv(b->child);
		if(b->sibling)
			computeMatrixCandCinv(b->sibling);
	}
}
void computeMatrixBFromParent(Bone*p,Bone* c){
	if(p&&c){
		if(p->id!=0)
			transition(c->B,p->direction.x()*p->length,p->direction.y()*p->length,p->direction.z()*p->length);
		else
			transition(c->B,0,0,0);
		if(c->child)
			computeMatrixBFromParent(c,c->child);
		if(c->sibling)
			computeMatrixBFromParent(p,c->sibling);
	}
}
void computeMatrixB(Bone* b){
	if(b){
		if(b->id==0){
			transition(b->B,b->position.x(),b->position.y(),b->position.z());
			computeMatrixBFromParent(b,b->child);
		}else{

		}
	}
}

void RotateBoneDirToLocalCoordSystem(Character* actor)
{
	int i;

	for(i=1; i<=actor->boneNumber; i++) 
	{
		//Transform dir vector into local coordinate system
		vector_rotationXYZ(&actor->bones[i].direction[0], -actor->bones[i].axis_x, -actor->bones[i].axis_y, -actor->bones[i].axis_z); 
	}

}

void init(void){
	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(90,winWidth/winHeight,0,10000);
	gluLookAt(eye[0],eye[1],eye[2],viewPoint[0],viewPoint[1],viewPoint[2],up[0],up[1],up[2]);
	//读取骨架数据
	char name[100] = "./subject/01.asf";
	if(!readASFFile(&g_actor,name))
		printf("cannot read asf file!");
//	RotateBoneDirToLocalCoordSystem(&g_actor);
	computeMatrixCandCinv(g_actor.getRoot());
	computeMatrixB(g_actor.getRoot());
	//strcpy(name,"./subject/01_01.amc");
	//readAMCFile(name,&g_actor);
	//strcpy(name,"./subject/01_02.amc");
	//readAMCFile(name,&g_actor);
	//strcpy(name,"./subject/01_03.amc");
	//readAMCFile(name,&g_actor);

	//读取运动数据
	strcpy(name,"./subject/01_01.amc");
	readSequence(name,&g_actor,g_aniStack,0);
	setPlayList(playList,g_aniStack,g_actor);
	//读取Obj模型数据
	if(!readObjFile(&g_actor_mesh,"./subject/jackie.obj"))
		printf("Obj file cannot be read");
	//读取权重值数据
	strcpy(name,"./subject/skindata.txt");
	readWeights(&g_actor,&g_actor_mesh,name);

	//设置姿态存储空间
	transitionAnimation.ppos = (posture*)malloc(sizeof(posture)*TRANSITION_FRAME);
	memset(transitionAnimation.ppos,0,sizeof(posture)*TRANSITION_FRAME);
//	intepolateAnimation(g_aniStack.animationArray[0],g_aniStack.animationArray[2]);
}

void drawBone(Bone* b){
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

//		loadIdentity(M);
		matrixPostmultiply(g_currentMatrix,M);
		matrixPostmultiply(g_currentMatrix,b->Cinv);
//		matrixPostmultiply(g_currentMatrix,b->B);
		float o[3],e[3];
//		matrix_transform_affine(temp,b->B[0][3],b->B[1][3],b->B[2][3],p);
//		b->setPosition(p[0],p[1],p[2]);
//		printf("draw %s \n",b->name);
		matrix_transform_affine(g_currentMatrix,0,0,0,o);
		matrix_transform_affine(g_currentMatrix,b->direction.x()*b->length,b->direction.y()*b->length,b->direction.z()*b->length,e);
		if(bDrawBone){
			glBegin(GL_LINES);
			glVertex3fv(o);
			glVertex3fv(e);
			glEnd();
		}
		b->setPosition(e[0],e[1],e[2]);

		if(b->child){
			drawBone(b->child);
		}
		if(b->sibling){
			g_MatrixStack.current((double*)g_currentMatrix);
			g_MatrixStack.pop();
			drawBone(b->sibling);
		}
	}
}
void drawActor(Character* actor){
	loadIdentity(g_currentMatrix);

	drawBone(actor->getRoot());
}
void drawMesh(CharacterMesh* actorMesh,Character * actor,float scale = 1.0){
	int numOfFace = actorMesh->getFaceNum();
	scale = 50;
	for(int i=0;i<numOfFace;i++)
	{
//		printf("face %d ",i);
		Face* f = actorMesh->getFaceAddressFromIndex(i);
		int numOfVertex = f->getVertexNum();
		Vertex* v = f->getVertexAddress();
//		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);
			for(int j = 0;j<numOfVertex;j++)
			{
				if(v==0) break;
				float x ,y ,z;
				x = v->pVp->vx;
				y = v->pVp->vy;
				z = v->pVp->vz;
				for(int k = 0;k<=actor->boneNumber;k++){
					x += ((actor->bones[k]).position[0])*v->pVp->weight[k];
					y += (actor->bones[k].position[1])*v->pVp->weight[k];
					z += (actor->bones[k].position[2])*v->pVp->weight[k];//没有检查指针的存在性
				}
				glVertex3f(x,y,z);
//				glVertex3f(v->pVp->getX()*scale,v->pVp->getY()*scale,v->pVp->getZ()*scale);
//				printf("%f %f %f \n",v->pVp->getX(),v->pVp->getY(),v->pVp->getZ());
				v = v->getNext();
			}
		glEnd();
	}
}
void displayFcn(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0],eye[1],eye[2],viewPoint[0],viewPoint[1],viewPoint[2],up[0],up[1],up[2]);
	//{
	//	glEnable(GL_LIGHTING);
	//	float direction[4]= { viewPoint[0] - eye[0], viewPoint[1] - eye[1], viewPoint[2] - eye[2],0};
	//	float white[4] = {1,1,1,1};
	//	glLightfv(GL_LIGHT1,GL_POSITION,direction);
	//	glLightfv(GL_LIGHT1,GL_DIFFUSE,white);
	//	glEnable(GL_LIGHT1);
	//}
	if(g_aniStack.count>0)	{
		if(!btransition)
			g_actor.setPosture(g_aniStack.animationArray[g_currentAnimationIndex].ppos+f);
		else
			g_actor.setPosture(transitionAnimation.ppos+f);
	//	printf("%d\n",f);	
		if(bAnimated){
			if(!btransition)
				f = (f<g_aniStack.animationArray[g_currentAnimationIndex].numOfPostures-1?f+1:0);
			else{
				if(f==TRANSITION_FRAME-1)
					btransition = false;
				f = (f<TRANSITION_FRAME-1?f+1:0);

			}
		}

		if(bLoop){
			if(btransition == false){
				if(f == g_aniStack.animationArray[g_currentAnimationIndex].numOfPostures-1){/* 放到最后一帧 */
					btransition = true;
					/*g_currentAnimationIndex=(g_currentAnimationIndex+1)%g_aniStack.getAnimationNumber();*/
					intepolateAnimation(g_aniStack.animationArray[0],
						g_aniStack.animationArray[playList[g_currentAnimationIndex]],transitionAnimation);
					g_currentAnimationIndex = playList[g_currentAnimationIndex];
					f = 0;
					transition(g_actor.getRoot()->B,
						g_actor.getRoot()->position.x()-g_aniStack.getAnimationFromIndex(g_currentAnimationIndex)->ppos->bone_translation[0].x(),
						g_actor.getRoot()->position.y()-g_aniStack.getAnimationFromIndex(g_currentAnimationIndex)->ppos->bone_translation[0].y(),
						g_actor.getRoot()->position.z()-g_aniStack.getAnimationFromIndex(g_currentAnimationIndex)->ppos->bone_translation[0].z()
						);
					/* root.position - root.第一帧的bone_transition 计算root的B矩阵，使两clip能连续*/
				}
			}
		}
	}else 
		g_actor.setInitialPose();
	drawActor(&g_actor);
	drawMesh(&g_actor_mesh,&g_actor);
	glutSwapBuffers();
}
void winReshapeFcn(int width,int height){
	if(height==0)
		height = 1;
	winWidth = width;
	winHeight = height;
	glViewport(0,0,width,height);
	gluLookAt(eye[0],eye[1],eye[2],viewPoint[0],viewPoint[1],viewPoint[2],up[0],up[1],up[2]);
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,width/height,0,10000);
	glMatrixMode(GL_MODELVIEW);
}
void keyFcn(unsigned char key,int xMouse,int yMouse)
{
	switch(key){
	case 'a':
		eye[0]+=0.2;eye[2]+=0.2;
		break;
	case 'd':
		eye[0]-=0.2;eye[2]-=0.2;
		break;
	case 's':
		eye[0]+=(eye[0]-viewPoint[0])/5;
		eye[1]+=(eye[1]-viewPoint[1])/5;
		eye[2]+=(eye[2]-viewPoint[2])/5;
		break;
	case 'w':
		eye[0]-=(eye[0]-viewPoint[0])/5;
		eye[1]-=(eye[1]-viewPoint[1])/5;
		eye[2]-=(eye[2]-viewPoint[2])/5;
		break;
	case 18:
		printf("alt");
		break;
	}
//	printf("%f %f %f\n",eye[0],eye[1],eye[2]);
}
void mouseMotionFcn(int xMouse,int yMouse){
		static int prev_x,prev_y;
		int delt_x = 0,delt_y = 0;
		double Rx[4][4],Ry[4][4],tmp[4][4];

			delt_x = (xMouse - prev_x)*2;
			delt_y = (yMouse - prev_y)*2;
			rotationY(Ry,-delt_x);
			rotationX(Rx,delt_y);
			matrix_mult(Ry,Rx,tmp);
			matrix_transform_affine(tmp,eye[0],eye[1],eye[2],eye);
		
	//		printf("%f %f %f ",eye[0],eye[1],eye[2]);

	prev_x = xMouse;prev_y = yMouse;
}
void idle()
{
	glutPostRedisplay();
}
void printPlayList(int i,int count){
	if(!count)
		return;
	count--;
	printf("%d ",i+1);
	printPlayList(playList[i],count);
}
unsigned int __stdcall cmdThread(void *){
	char cmd[20],args[20],*fileExt,buf[100];
	int i;
	while(1){
		int index;
		scanf("%s",cmd);
		if(strcmp(cmd,"exit")==0){
			exit(0);
		}else if(strcmp(cmd,"playlist")==0){
			printPlayList(g_currentAnimationIndex,g_aniStack.getAnimationNumber());
		}
		else {
			if(strcmp(cmd,"animation")==0){
				scanf("%s",args);
				/* 停止动画或开始动画，或开始某个动画*/
				if(strcmp(args,"on")==0)
					bAnimated = true;
				else if(strcmp(args,"off")==0)
						bAnimated = false;
				else if((index=atoi(args))!=0){
					g_currentAnimationIndex = index<=g_aniStack.getAnimationNumber()&&index>0?index-1:0;
					f = 0;
				}else if(strcmp(args,"deleteall")==0){
					g_aniStack.deleteAll();
				}
			}else if(strcmp(cmd,"skeleton")==0){
				/* 画骨骼 不画骨骼*/
				scanf("%s",args);
				if(strcmp(args,"on")==0)
					bDrawBone = true;
				else if(strcmp(args,"off")==0)
						bDrawBone = false;
			}else if(strcmp(cmd,"read")==0){
				/* 读文件命令 */
				scanf("%s",args);
				i = strlen(args)-1;
				while(args[i--]!='.');
				fileExt = args+i+2;
				if(strcmp(fileExt,"amc")==0){
					readSequence(args,&g_actor,g_aniStack,0);
					setPlayList(playList,g_aniStack,g_actor);
				}
				else if(strcmp(fileExt,"asf")==0){
					if(!readASFFile(&g_actor,args))
						printf("can't read %s",args);					
					g_aniStack.deleteAll();
				}
			}else if(strcmp(cmd,"current")==0){
				/*打印当前一些信息*/
				scanf("%s",args);
				if(strcmp(args,"animation")==0)
					printf("The current animation clip is %d %s.\n",
					g_currentAnimationIndex+1,g_aniStack.getAnimationFromIndex(g_currentAnimationIndex)->url);
				else if(strcmp(args,"frame")==0)
					printf("current frame is %d\n",f);
			}else if(strcmp(cmd,"loop")==0){
				/* 停止播放列表的循环*/
				scanf("%s",args);
				if(strcmp(args,"on")==0)
					bLoop = true;
				else if(strcmp(args,"off")==0)
					bLoop = false;
			}else if(strcmp(cmd,"goto")==0){
				scanf("%s",args);
				if((index=atoi(args))!=0){
					f = (index<=(g_aniStack.getAnimationFromIndex(g_currentAnimationIndex))->numOfPostures&&index>0?index-1:0);
					bAnimated = false;
					btransition = false;
				}
			}else{
				printf("no such command!\n");
				continue;
			}
		}
	}
	return 0;
}
int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(winWidth,winHeight);
	glutCreateWindow("Character Animation");

	init();

	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMotionFunc(mouseMotionFcn);
	glutKeyboardFunc(keyFcn);
	glutIdleFunc(idle);

	_beginthreadex(0,0,cmdThread,0,0,0);
	glutMainLoop();
	return 0;
}
