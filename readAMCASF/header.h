#pragma once
#define MAX_BONES 100
#define MAX_ANIMATION_CLIP 100
#define TRANSITION_FRAME   120

#define  INDEX int
//顶点位置类
class VertexPosition{
public:
	//顶点坐标
	float vx;
	float vy;
	float vz;
public:
	//权重
	float *weight;
public:
	void setVertex(float x,float y,float z);
	float getX();
	float getY();
	float getZ();
};
//纹理顶点类
class TextureVertex{
	float vtx;
	float vty;
	float vtz;
public:
	void setTextureVertex(float x,float y,float z);
	float getTX();
	float getTY();
};
//顶点法线类
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

//顶点类
class Vertex{
public:
	//顶点数据成员
	VertexPosition *pVp;		//位置
	TextureVertex  *pTv;		//纹理
	VertexNormal   *pVn;	//法线
	Vertex		   *pNext;		//下一个顶点
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
	int   getVertexNum();
	Vertex* getVertexAddress();
};

//角色网格
class CharacterMesh{
	//计数标记
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
	//增加数据
	void addVertex(float x,float y,float z);
	void addTextureVertex(float x,float y,float z);
	void addVertexNormal(float x,float y,float z);
	void addFace(int numOfVertex,Vertex *v);
	//void changeVertexPosition(index i,float x,float y,float z){v[i].vx = x;v[i].vy = y;v[i].vz = z; }
	//void changeVertexTextureCoor(index i,float x,float y,float z){v[i].vtx = x;v[i].vty = y;v[i].vtz = z;}
	//void changeVertexNormal(index i,float x,float y,float z){v[i].vnx = x;v[i].vny = y;v[i].vnz = z;}
	//获取
	int		getVertexNum();
	int		getTextureVertexNum();
	int		getVertexNormalNum();
	int		getFaceNum();
	VertexPosition* getVertexPositionAddressFromIndex(INDEX i);
	TextureVertex*  getTextureVertexAddressFromIndex(INDEX i);
	VertexNormal*   getVertexNormalAddressFromIndex(INDEX i);
	Face*           getFaceAddressFromIndex(INDEX i);
};
