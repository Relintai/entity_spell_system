#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "GameObject.h"
#include "AnimSpriteSet.h"
#include "SpriteRenderer.h"
#include "WaitForSeconds.h"
#include <System/Collections/IEnumeratorCXX.h>

using namespace UnityEngine;
using namespace System::Runtime::CompilerServices;
using namespace System::Collections;
using namespace System;
class SpriteAnim : public virtual MonoBehaviour, public virtual Object
{
	public:
		GameObject* AnimatedGameObject;
	public:
		Array<AnimSpriteSet>* AnimationSets;
	private:
		int Cur_SpriteID;
	public:
		float SecsPerFrame;
	private:
		SpriteRenderer* spriteRenderer;
	private:
		WaitForSeconds* waitForSeconds;
	private:
		void Awake();
	public:
		void PlayAnimation(int ID, float secPerFrame);
	//Attribute: IteratorStateMachine*(/*ERROR: Cannot translate: System.NotImplementedException: typeOfExpression: --> TODO: --> http://www.boost.org/doc/libs/1_55_0/doc/html/typeof/tuto.html. Node: ICSharpCode.NRefactory.CSharp.TypeOfExpression*/)
	private:
		IEnumerator* AnimateSprite(int ID);
	public:
		SpriteAnim();
};
