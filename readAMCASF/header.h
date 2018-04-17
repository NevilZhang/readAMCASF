#pragma once
#define MAX_BONES 100
#define MAX_ANIMATION_CLIP 100
#define TRANSITION_FRAME   120

#define  INDEX int

class VertexPosition{
public:
	float vx;
	float vy;
	float vz;
public:
	float *weight;
public:
	void setVertex(float x,float y,float z);
	float getX();
	float getY();
	float getZ();
};
class TextureVertex{
	float vtx;
	float vty;
	float vtz;
public:
	void setTextureVertex(float x,float y,float z);
	float getTX();
	float getTY();
};
class VertexNormal{
	float vnx;
	float vny;
	float vnz;
public:
	void setVertexNormal(float x,float y,float z);
	float getVNX();
	float getVNY();
	float getVNZ();
};
class Vertex{
public:
	VertexPosition *pVp;
	TextureVertex  *pTv;
	VertexNormal   *pVn;
	Vertex		   *pNext;
public:
	void setVertex(VertexPosition *pvp,TextureVertex *ptv,VertexNormal *pvn,Vertex *pnext);
	void setNext(Vertex *pN);
	Vertex* getNext();
};
class Face{
	int vertex_num;
	Vertex *pv;
public:
	Face();
	void setFaceParameter(int vn,Vertex *v);
	int  getVertexNum();
	Vertex* getVertexAddress();
};
class CharacterMesh{

	int vertexPosition_num;
	int textureVertex_num;
	int vertexNormal_num;
	int face_num;
public:
	VertexPosition	vp[10000];
	TextureVertex	tv[10000];
	VertexNormal	vn[10000];
	Face   f[10000];
public:
	CharacterMesh();
	void addVertex(float x,float y,float z);
	void addTextureVertex(float x,float y,float z);
	void addVertexNormal(float x,float y,float z);
	void addFace(int numOfVertex,Vertex *v);
	//void changeVertexPosition(index i,float x,float y,float z){v[i].vx = x;v[i].vy = y;v[i].vz = z; }
	//void changeVertexTextureCoor(index i,float x,float y,float z){v[i].vtx = x;v[i].vty = y;v[i].vtz = z;}
	//void changeVertexNormal(index i,float x,float y,float z){v[i].vnx = x;v[i].vny = y;v[i].vnz = z;}
	int		getVertexNum();
	int		getTextureVertexNum();
	int		getVertexNormalNum();
	int		getFaceNum();
	VertexPosition* getVertexPositionAddressFromIndex(INDEX i);
	TextureVertex*  getTextureVertexAddressFromIndex(INDEX i);
	VertexNormal*   getVertexNormalAddressFromIndex(INDEX i);
	Face*           getFaceAddressFromIndex(INDEX i);
};
