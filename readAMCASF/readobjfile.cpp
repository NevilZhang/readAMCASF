#include "stdafx.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "Header.h"


 
void VertexPosition::setVertex(float x,float y,float z){vx = x;vy = y;vz = z;}
float VertexPosition::getX(){return vx;};
float VertexPosition::getY(){return vy;};
float VertexPosition::getZ(){return vz;};

void TextureVertex::setTextureVertex(float x,float y,float z){vtx = x;vty = y;vtz = z;}
float TextureVertex::getTX(){return vtx;};
float TextureVertex::getTY(){return vty;};

void VertexNormal::setVertexNormal(float x,float y,float z){vnx = x;vny = y;vnz = z; } 
float VertexNormal::getVNX(){return vnx;};
float VertexNormal::getVNY(){return vny;};
float VertexNormal::getVNZ(){return vnz;};

void Vertex::setVertex(VertexPosition *pvp,TextureVertex *ptv,VertexNormal *pvn,Vertex *pnext){
	assert(pvp!=NULL);
	pVp = pvp;pTv = ptv;pVn = pvn;pNext = pnext;
}
void Vertex::setNext(Vertex *pN){ pNext = pN;}
Vertex* Vertex::getNext(){return pNext;}

Face::Face(){ vertex_num = 0;}
void Face::setFaceParameter(int vn,Vertex *v){ vertex_num = vn;pv = v;}
int  Face::getVertexNum(){ return vertex_num;}
Vertex* Face::getVertexAddress(){ return pv;}

CharacterMesh::CharacterMesh(){vertexPosition_num=0;textureVertex_num=0;vertexNormal_num=0;face_num=0;}
void CharacterMesh::addVertex(float x,float y,float z){ 
	vp[vertexPosition_num].setVertex(x,y,z); 
	vertexPosition_num++;
}
void CharacterMesh::addTextureVertex(float x,float y,float z){ 
	tv[textureVertex_num].setTextureVertex(x,y,z); 
	textureVertex_num++;
}
void CharacterMesh::addVertexNormal(float x,float y,float z){ 
	vn[vertexNormal_num].setVertexNormal(x,y,z);
	vertexNormal_num++;
}
void CharacterMesh::addFace(int numOfVertex,Vertex *v){
	f[face_num].setFaceParameter(numOfVertex,v);
	face_num++;
}	
//void changeVertexPosition(index i,float x,float y,float z){v[i].vx = x;v[i].vy = y;v[i].vz = z; }
//void changeVertexTextureCoor(index i,float x,float y,float z){v[i].vtx = x;v[i].vty = y;v[i].vtz = z;}
//void changeVertexNormal(index i,float x,float y,float z){v[i].vnx = x;v[i].vny = y;v[i].vnz = z;}
int  CharacterMesh::getVertexNum(){ return vertexPosition_num;}
int	 CharacterMesh::getTextureVertexNum(){ return textureVertex_num;}
int  CharacterMesh::getVertexNormalNum(){ return vertexNormal_num;}
int  CharacterMesh::getFaceNum(){ return face_num;}

VertexPosition* 	CharacterMesh::getVertexPositionAddressFromIndex(INDEX i){ return &vp[i];}
TextureVertex*		CharacterMesh::getTextureVertexAddressFromIndex(INDEX i){return &tv[i];}
VertexNormal*		 CharacterMesh::getVertexNormalAddressFromIndex(INDEX i){return &vn[i];}
Face*				  CharacterMesh::getFaceAddressFromIndex(INDEX i){return &f[i];}

int readObjFile(CharacterMesh *actor,char *fileName)
{
//	char fileName[28] = "e:\\mayaWorks\\polygonOBJ.obj";
	FILE *fp;
	fp = fopen(fileName,"r");
	if(fp==NULL)
		return 0;
	char keyword;
	char buf[100];
//	int v_index = -1;int vt_index= -1; int vn_index = -1;
	while(!feof(fp)){
		keyword = fgetc(fp);
		float x=0;float y=0;float z=0;
		int ivp = 0;int itv = 0;int ivn=0;//index
		Vertex *pCurrent= 0;Vertex *pPrevious=0;Vertex *pHead=0;
		int numOfVertex = 0;
		switch(keyword){
		case '#':
			fgets(buf,100,fp);
			break;
		case 'v'://for v vt vn 
			keyword = fgetc(fp);
			switch(keyword){
			case ' '://v
				fscanf(fp,"%f %f %f",&x,&y,&z);
				actor->addVertex(x,y,z);
				break;
			case 't'://vt texture vertices
				fscanf(fp,"%f %f %f",&x,&y,&z);
				actor->addTextureVertex(x,y,z);
				break;
			case 'n'://vn
				fscanf(fp,"%f %f %f",&x,&y,&z);
				actor->addVertexNormal(x,y,z);
				break;
			}
			break;
		case 'f':			
			fscanf(fp,"%d/%d/%d",&ivp,&itv,&ivn);
			pCurrent = (Vertex*)malloc(sizeof(Vertex));
			pHead = pCurrent;
			pCurrent->setVertex(actor->getVertexPositionAddressFromIndex(ivp-1), // caution ! substract one !
								actor->getTextureVertexAddressFromIndex(itv-1),
								actor->getVertexNormalAddressFromIndex(ivn-1),NULL); 
			numOfVertex++;
			while(1){
				ivp = itv = ivn = 0;
				pPrevious = pCurrent;
				fscanf(fp,"%d/%d/%d",&ivp,&itv,&ivn);
				if(ivp==0)
					break;
				pCurrent = (Vertex*)malloc(sizeof(Vertex));
				pCurrent->setVertex(actor->getVertexPositionAddressFromIndex(ivp-1), // caution ! substract one !
								actor->getTextureVertexAddressFromIndex(itv-1),
								actor->getVertexNormalAddressFromIndex(ivn-1),NULL);
				numOfVertex++;
				pPrevious->setNext(pCurrent);
			}
			actor->addFace(numOfVertex,pHead);
			break;
		case 10:
			break;
		default:
			fgets(buf,100,fp);
			break;
		}
	}
	return 1;
}