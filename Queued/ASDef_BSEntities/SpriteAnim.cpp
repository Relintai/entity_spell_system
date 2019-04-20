#include "SpriteAnim.h"
void SpriteAnim::Awake(){
	this->spriteRenderer = MonoBehaviour::GetComponent<SpriteRenderer>();
	this->Cur_SpriteID = 0;
	if (!this->AnimatedGameObject){
		this->AnimatedGameObject = MonoBehaviour::gameObject;
	}
	this->PlayAnimation(0, (float)0.25);
}
void SpriteAnim::PlayAnimation(int ID, float secPerFrame)
{
	this->SecsPerFrame = secPerFrame;
	this->waitForSeconds = new WaitForSeconds(secPerFrame);
	MonoBehaviour::StopCoroutine(new String("AnimateSprite"));
	this->Cur_SpriteID = 0;
	this->spriteRenderer->sprite = this->AnimationSets->GetData(ID)->Anim_Sprites->GetData(this->Cur_SpriteID);
	MonoBehaviour::StartCoroutine(new String("AnimateSprite"), BOX<int>(ID));
}
//Attribute: IteratorStateMachine*(/*ERROR: Cannot translate: System.NotImplementedException: typeOfExpression: --> TODO: --> http://www.boost.org/doc/libs/1_55_0/doc/html/typeof/tuto.html. Node: ICSharpCode.NRefactory.CSharp.TypeOfExpression*/)
IEnumerator* SpriteAnim::AnimateSprite(int ID){
	SpriteAnim::<AnimateSprite>d__8* expr_06 = new SpriteAnim::<AnimateSprite>d__8(0);
	expr_06-><>4__this = this;
	expr_06->ID = ID;
	return expr_06;
}
SpriteAnim::SpriteAnim()
{
	SecsPerFrame = (float)0.25;
}

