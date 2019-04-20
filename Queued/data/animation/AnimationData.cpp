#include "AnimationData.h"

int AnimationData::getId()
{
    return this->id;
}

void AnimationData::setId(int value)
{
    this->id = value;
}

bool AnimationData::getAnimStop()
{
    return this->animStop;
}

void AnimationData::setAnimStop(bool value)
{
    this->animStop = value;
}

float AnimationData::getAnimStopTime()
{
    return this->animStopTime;
}

void AnimationData::setAnimStopTime(float value)
{
    this->animStopTime = value;
}

int AnimationData::getWeaponType()
{
    return this->weaponType;
}

void AnimationData::setWeaponType(int value)
{
    this->weaponType = value;
}

String* AnimationData::getAnimationName()
{
    return this->animationName;
}

void AnimationData::setAnimationName(String* value)
{
    this->animationName = value;
}

int AnimationData::getPriority()
{
    return this->priority;
}

void AnimationData::setPriority(int value)
{
    this->priority = value;
}

void AnimationData::FromJSON()
{
    /*
    while (r->Read()) {
        if (r->TokenType == JsonToken::PropertyName) {
            String* a = (String*)(r->Value);
            if (!*a == *(new String("Id"))) {
                if (!*a == *(new String("AnimStop"))) {
                    if (!*a == *(new String("AnimStopTime"))) {
                        if (!*a == *(new String("WeaponType"))) {
                            if (!*a == *(new String("AnimationName"))) {
                                if (*a == *(new String("Priority"))) {
                                    ad->setPriority(r->ReadAsInt32()->Value);
                                }
                            }
                            else {
                                ad->setAnimationName(r->ReadAsString());
                            }
                        }
                        else {
                            ad->setWeaponType(r->ReadAsInt32()->Value);
                        }
                    }
                    else {
                        ad->setAnimStopTime((float)(r->ReadAsDouble()->Value));
                    }
                }
                else {
                    ad->setAnimStop(r->ReadAsBoolean()->Value);
                }
            }
            else {
                ad->setId(r->ReadAsInt32()->Value);
            }
        }
        else {
            if (r->TokenType == JsonToken::EndObject) {
                break;
            }
        }
    }
    */
}

void AnimationData::ToJSON()
{
    /*
    w->WritePropertyName(new String("AnimationData"));
    w->WriteStartObject();
    w->WritePropertyName(new String("Id"));
    w->WriteValue(ad->getId());
    w->WritePropertyName(new String("AnimStop"));
    w->WriteValue(ad->getAnimStop());
    w->WritePropertyName(new String("AnimStopTime"));
    w->WriteValue(ad->getAnimStopTime());
    w->WritePropertyName(new String("WeaponType"));
    w->WriteValue(ad->getWeaponType());
    w->WritePropertyName(new String("AnimationName"));
    w->WriteValue(ad->getAnimationName());
    w->WritePropertyName(new String("Priority"));
    w->WriteValue(ad->getPriority());
    w->WriteEndObject();
    */
}

