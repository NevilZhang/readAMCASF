#include "StdAfx.h"
#include "animation.h"


animation::animation(void)
{
}


animation::~animation(void)
{
	if(ppos)
		free(ppos);
}
AnimationStack::AnimationStack()
{
	count = 0;
}
AnimationStack::~AnimationStack()
{

}
animation* AnimationStack::getAnimationFromIndex(int i){
	return &animationArray[i];
}