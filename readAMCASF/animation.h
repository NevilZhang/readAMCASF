#pragma once
#include "posture.h"
#include "header.h"

//∂Øª≠¿‡
class animation// an animation is obtained by series of postures of a charactor
{
public:
	posture *ppos;
	int numOfPostures;
	char url[100];
public:
	animation(void);
	~animation(void);
};
//∂Øª≠’ª
class AnimationStack
{
public:
	int count;
	animation animationArray[MAX_ANIMATION_CLIP];
public:
	AnimationStack();
	~AnimationStack();
	animation* getAnimationFromIndex(int i);
	int getAnimationNumber(){return count;}
	void deleteAll(){ count=0;}
};