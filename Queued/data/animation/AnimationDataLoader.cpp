#include "AnimationDataLoader.h"

AnimationDataLoader* AnimationDataLoader::self;
AnimationDataLoader* AnimationDataLoader::getInstance(){
    return AnimationDataLoader::self;
}

void AnimationDataLoader::Start()
{
    this->data = new List_T<PAnimationData>();
    this->RefreshList();
    if (this->load) {
        this->Load();
        return;
    }
    AnimationDataLoader::self = this;
}

void AnimationDataLoader::Load()
{
    DataMgr::Instance->RequestTextAsset(new String("data"), new String("AnimationData"), /*ERROR: Cannot translate: System.NotImplementedException: typeOfExpression: --> TODO: --> http://www.boost.org/doc/libs/1_55_0/doc/html/typeof/tuto.html. Node: ICSharpCode.NRefactory.CSharp.TypeOfExpression*/, new String("Animations/AnimationData.bytes"), new DataMgr::DataLoadFinishAction(this->OnAnimationDataLoaded), null);
}

void AnimationDataLoader::LoadEditor()
{
    /*ERROR: Cannot translate: System.NotImplementedException: The method or operation is not implemented.. Node: ICSharpCode.NRefactory.CSharp.UsingStatement*/;
}

void AnimationDataLoader::SaveNow()
{
    /*ERROR: Cannot translate: System.NotImplementedException: The method or operation is not implemented.. Node: ICSharpCode.NRefactory.CSharp.UsingStatement*/;
}

void AnimationDataLoader::RefreshList()
{
    this->data->Clear();
    Transform* transform = MonoBehaviour::transform;
    for (int i = 0; i < transform->childCount; i += 1) {
        Transform* child = transform->GetChild(i);
        PAnimationData pAnimationData = PAnimationData();
        pAnimationData.animation = child->gameObject;
        pAnimationData.name = child->name;
        AnimationData* component = pAnimationData.animation->GetComponent<AnimationData>();
        if (component == null) {
            Debug::Log(*(new String("AnimationData->Awake: Animation doesn't have AnimationData component attached! name: ")) + *(pAnimationData.name));
        }
        component->getId();
        this->data->Add(pAnimationData);
    }
}

void AnimationDataLoader::OnAnimationDataLoaded(BaseAssetBundleHelper* h)
{
    /*ERROR: Cannot translate: System.NotImplementedException: The method or operation is not implemented.. Node: ICSharpCode.NRefactory.CSharp.UsingStatement*/;
    this->RefreshList();
    AnimationDataLoader::self = this;
}

GameObject* AnimationDataLoader::getAnimationWithName(String* name)
{
    for (int i = 0; i < this->data->Count; i += 1) {
        if (this->data->GetData(i).name == *name) {
            return this->data->GetData(i).animation;
        }
    }
    return null;
}

GameObject* AnimationDataLoader::getAnimationWithId(int id)
{
    for (int i = 0; i < this->data->Count; i += 1) {
        if (this->data->GetData(i).id == id) {
            return this->data->GetData(i).animation;
        }
    }
    return null;
}

AnimationDataLoader::AnimationDataLoader()
{
    folder = new String("Animations");
    loadFile = new String("AnimationData");
}

