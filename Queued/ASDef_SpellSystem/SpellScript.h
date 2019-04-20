#ifndef SPELL_SCRIPT_H
#define SPELL_SCRIPT_H

#include "core/reference.h"

class Entity;
class Spell;

class SpellScript : public Reference {
public:
    float PLAYER_HIT_RADIUS;

    //DamagePipelineData* damagePipelineData;

    virtual void StartCasting(Entity* caster, float spellScale);
    virtual void CastingFinished(Entity* caster, float spellScale);
    virtual void CastingFailed(Entity* caster);
    virtual void SpellHit(Entity* caster, Entity* target, BaseWorldSpell* worldSpell, Spell* spell, float spellScale);
    virtual void OnPlayerMove(Entity* caster);
    virtual void COnSpellCastStarted(Entity* player);
    virtual void COnSpellCastSuccess(Entity* player);
    virtual void COnSpellCastFailed(Entity* player);
    virtual void COnSpellCastEnded(Entity* player);
    virtual void OnCastStateChanged(Entity* caster);

	SpellScript();

	/*
    static void InitFactory();
    static void SSCreateFor(Spell* spell);
    SpellScript(Spell* spell);
    void TriggerGlobalCooldown(WorldEntity* player);
    bool IsCasting(WorldEntity* player);
    bool HasClobalCooldown(WorldEntity* player);
    bool IsStunned(WorldEntity* player);
    bool HasState(StateData::StateType state, WorldEntity* player);
    int GetId(WorldEntity* spell);
    bool IsSpellOnCooldown(int spellId, WorldEntity* player);
    void ApplyAura(int auraId, WorldEntity* caster, float spellScale);
    void ApplyAura(int auraId, WorldEntity* caster, WorldEntity* target, float spellScale);
    void RemoveAura(int auraId, WorldEntity* caster);
    void AddCooldown(WorldEntity* player, int spellId, float cooldown);
    void DoStartCasting(WorldEntity* player, int spellId, String* spellName, float castTime, bool addMoveHook, float spellScale);
    void DoCastFail(WorldEntity* player, bool removeHook);
    void AddOnMoveHook(WorldEntity* player);
    void RemoveOnMoveHook(WorldEntity* player);
    WorldEntity* GetTarget(WorldEntity* player);
    void DealDamage(WorldEntity* caster, WorldEntity* target, int damage);
    void DealDamage(WorldEntity* caster, WorldEntity* target, float spellScale);
    void VashDealDamage(WorldEntity* caster, WorldEntity* target, bool increased, float spellScale);
    void Heal(WorldEntity* caster, WorldEntity* target, float spellScale);
    void Heal(WorldEntity* caster, WorldEntity* target, int heal);
    bool checkParry(WorldEntity* caster, WorldEntity* target);
    //Attribute: Obsolete*
    GameObject* OldLaunchFollowProjectile(GameObject* effect, WorldEntity* caster, WorldEntity* target, float speed, float spellScale, float time = (float)0);
    //Attribute: Obsolete*
    GameObject* OldLaunchStraightProjectile(GameObject* effect, WorldEntity* caster, float speed, float time, float range, float spellScale);
    //Attribute: Obsolete*
    GameObject* OldLaunchProjectile(WorldEntity* caster, WorldEntity* target, float spellScale);
    WorldSpell* SpawnProjectile(WorldEntity* caster, WorldEntity* target, float spellScale);
    bool isInRange(WorldEntity* target, WorldEntity* player);
    bool CanCast(WorldEntity* caster, int skipCheck = 0);
    bool CanCastTarget(WorldEntity* caster, int skipCheck = 0);
    bool CanCastTargetRange(WorldEntity* caster, int skipCheck = 0);
    bool SpellCostCheckAndRemove(WorldEntity* caster);
    bool SpellCostCheck(WorldEntity* caster);
    void SpellResourceGive(WorldEntity* caster);
    void AddSpellCastEffect(WorldEntity* caster);
    void RemoveSpellCastEffects(WorldEntity* caster);
    void AddEffect(WorldEntity* player, GameObject* effectPrefab, EffectPoints bodyPart, Quaternion* rotation = );
    void AddWorldEffect(WorldEntity* location, GameObject* effectPrefab, Vector3* offset = , Quaternion* rotation = );
    void RemoveEffect(WorldEntity* player, EffectPoints bodyPart);
    String* StringifyCooldown(float cooldown);
    virtual String* GetName();
    virtual String* GetDescription(int level);
    void SpellCastSuccess(WorldEntity* caster);
    void PlaySound(String* sound);
    void PlayStandardSpellCastFinish();
    void PlayStandardSpellCastFinish(WorldEntity* caster);
    void PlayStandardIceArcherAttackSpellCastFinish(WorldEntity* caster);
    void PlayStandardBerserkerAttackSpellCastFinish(WorldEntity* caster);
    void AnimStop(WorldEntity* player);
	*/
};

#endif
