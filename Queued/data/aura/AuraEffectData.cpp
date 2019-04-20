#include "AuraEffectData.h"

int AuraEffectData::getEffectId(){
    return this->effectId;
}

void AuraEffectData::setEffectId(int value)
{
    this->effectId = value;
}

bool AuraEffectData::getEnabled()
{
    return this->enabled;
}

void AuraEffectData::setEnabled(bool value)
{
    this->enabled = value;
}

GameObject* AuraEffectData::getEffectPrefab()
{
    return this->effectPrefab;
}

void AuraEffectData::setEffectPrefab(GameObject* value)
{
    this->effectPrefab = value;
}

EffectPoints AuraEffectData::getEffectPoint1()
{
    return this->effectPoint1;
}

void AuraEffectData::setEffectPoint1(EffectPoints value)
{
    this->effectPoint1 = value;
}

EffectPoints AuraEffectData::getEffectPoint2()
{
    return this->effectPoint2;
}

void AuraEffectData::setEffectPoint2(EffectPoints value)
{
    this->effectPoint2 = value;
}

void AuraEffectData::Set(String* effectPoint1, String* effectPoint2)
{
    this->effectPoint1 = AuraEffectData::GetEffectPoint(effectPoint1);
    this->effectPoint2 = AuraEffectData::GetEffectPoint(effectPoint2);
}

EffectPoints AuraEffectData::GetEffectPoint(String* effectPoint)
{
    uint num = <PrivateImplementationDetails>::ComputeStringHash(effectPoint);
    if (num <= 1486530497u) {
        if (num <= 900739000u) {
            if (num != 811237315u) {
                if (num == 900739000u) {
                    if (*effectPoint == *(new String("LEFT_HAND"))) {
                        return EffectPoints::LEFT_HAND;
                    }
                }
            }
            else {
                if (*effectPoint == *(new String("HEAD"))) {
                    return EffectPoints::HEAD;
                }
            }
        }
        else {
            if (num != 1475309447u) {
                if (num == 1486530497u) {
                    if (*effectPoint == *(new String("WEAPON"))) {
                        return EffectPoints::WEAPON;
                    }
                }
            }
            else {
                if (*effectPoint == *(new String("RIGHT_EYE"))) {
                    return EffectPoints::RIGHT_EYE;
                }
            }
        }
    }
    else {
        if (num <= 2140681907u) {
            if (num != 1932136219u) {
                if (num == 2140681907u) {
                    if (*effectPoint == *(new String("RIGHT_HAND"))) {
                        return EffectPoints::RIGHT_HAND;
                    }
                }
            }
            else {
                if (*effectPoint == *(new String("NONE"))) {
                    return EffectPoints::NONE;
                }
            }
        }
        else {
            if (num != 2237933493u) {
                if (num != 3179538642u) {
                    if (num == 3916618584u) {
                        if (*effectPoint == *(new String("BASE"))) {
                            return EffectPoints::BASE;
                        }
                    }
                }
                else {
                    if (*effectPoint == *(new String("LEFT_EYE"))) {
                        return EffectPoints::LEFT_EYE;
                    }
                }
            }
            else {
                if (*effectPoint == *(new String("BODY"))) {
                    return EffectPoints::BODY;
                }
            }
        }
    }
    return EffectPoints::NONE;
}

String* AuraEffectData::GetEffectPointString(EffectPoints effectPoint)
{
    switch (effectPoint) {
        case EffectPoints::NONE:
            return new String("NONE");

        case EffectPoints::WEAPON:
            return new String("WEAPON");

        case EffectPoints::BASE:
            return new String("BASE");

        case EffectPoints::BODY:
            return new String("BODY");

        case EffectPoints::RIGHT_HAND:
            return new String("RIGHT_HAND");

        case EffectPoints::LEFT_HAND:
            return new String("LEFT_HAND");

        case EffectPoints::HEAD:
            return new String("HEAD");

        case EffectPoints::RIGHT_EYE:
            return new String("RIGHT_EYE");

        case EffectPoints::LEFT_EYE:
            return new String("LEFT_EYE");

        default:
            return new String("NONE");
    }
}

void AuraEffectData::LoadEffect()
{
    if (this->getEnabled()) {
        EffectLoader::getInstance()->GetData(this->getEffectId())->RegisterOnAssetLoaded(new EffectLoaderHelper::AssetLoadedAction(DELEGATE_FUNC(AuraEffectData::OnAuraEffectLoaded, _1)));
    }
}

void AuraEffectData::OnAuraEffectLoaded(EffectLoaderHelper* he)
{
    this->setEffectPrefab(he->Asset);
}

void AuraEffectData::FromJSON(JsonReader* r)
{
    while (r->Read()) {
        if (r->TokenType == JsonToken::PropertyName) {
            String* a = (String*)(r->Value);
            if (!*a == *(new String("EffectId"))) {
                if (!*a == *(new String("EffectPoint1"))) {
                    if (*a == *(new String("EffectPoint2"))) {
                        this->effectPoint2 = AuraEffectData::GetEffectPoint(r->ReadAsString());
                    }
                }
                else {
                    this->effectPoint1 = AuraEffectData::GetEffectPoint(r->ReadAsString());
                }
            }
            else {
                this->setEffectId(r->ReadAsInt32()->Value);
            }
        }
        else {
            if (r->TokenType == JsonToken::EndObject) {
                break;
            }
        }
    }
    this->LoadEffect();
}

void AuraEffectData::ToJSON(JsonWriter* w)
{
    w->WritePropertyName(new String("AuraEffectAttribute"));
    w->WriteStartObject();
    w->WritePropertyName(new String("EffectId"));
    w->WriteValue(this->getEffectId());
    w->WritePropertyName(new String("EffectPoint1"));
    w->WriteValue(AuraEffectData::GetEffectPointString(this->effectPoint1));
    w->WritePropertyName(new String("EffectPoint2"));
    w->WriteValue(AuraEffectData::GetEffectPointString(this->effectPoint2));
    w->WriteEndObject();
}

