#include "register_types.h"

#include "entity_enums.h"
#include "item_enums.h"

#include "data/aura.h"
#include "data/aura_stat_attribute.h"
#include "data/data_manager.h"
#include "data/talent.h"
#include "data/xp_data.h"
#include "data/item_stat_modifier.h"
#include "data/item_template_stat_modifier.h"
#include "data/spell_cooldown_manipulation_data.h"

#include "entities/data/entity_data.h"
#include "entities/data/mob_data.h"
#include "entities/data/player_character_data.h"

#include "entities/data/talent_row_data.h"
#include "entities/data/character_spec.h"

#include "data/item_visual.h"
#include "data/item_visual_entry.h"

#include "atlases/character_atlas.h"
#include "atlases/character_atlas_entry.h"

#include "skeleton/character_bones.h"

#include "data/item_template.h"
#include "data/item_instance.h"

#include "data/spell.h"
#include "entities/stats/stat.h"
#include "entities/stats/stat_modifier.h"
#include "entities/stats/stat_data.h"
#include "inventory/bag.h"
#include "inventory/inventory.h"

#include "data/craft_data_attribute_helper.h"
#include "data/craft_data_attribute.h"

#include "infos/spell_cast_info.h"
#include "infos/aura_infos.h"

#include "data/character_skeleton_visual_entry.h"

#include "pipelines/spell_damage_info.h"
#include "pipelines/spell_heal_info.h"

#include "entities/entity_resource.h"
#include "entities/auras/aura_data.h"
#include "entities/entity.h"
#include "entities/player.h"
#include "entities/mob.h"

#include "data/aura_trigger_data.h"
#include "data/aura_stat_attribute.h"

#include "ui/unit_frame.h"

#include "drag_and_drop/es_drag_and_drop.h"

#include "skeleton/character_skeleton.h"
#include "skeleton/character_skeleton_3d.h"

#include "utility/entity_create_info.h"
#include "utility/cooldown.h"
#include "utility/cooldown.h"
#include "utility/category_cooldown.h"

#include "meshes/mesh_data_resource.h"

#include "skeleton/entity_equipset.h"

#include "loot/loot_data_base.h"
#include "loot/loot_data_item.h"
#include "loot/loot_data_container.h"

#include "data/spell_effect_visual.h"
#include "data/spell_effect_visual_simple.h"
#include "data/spell_projectile_data.h"
#include "data/world_effect_data.h"

#include "spells/spell_projectile.h"
#include "spells/world_spell_effect.h"

#include "ai/ai_action.h"
#include "ai/ai_spell_action.h"
#include "ai/ai_action_container.h"

#ifdef TOOLS_ENABLED
#include "editor/editor_plugin.h"

#include "meshes/editor_plugin_collada_mdr.h"
#endif


void register_entity_spell_system_types() {
	ClassDB::register_class<SpellEnums>();

	//data
	ClassDB::register_class<CraftDataAttributeHelper>();
	ClassDB::register_class<CraftDataAttribute>();

	ClassDB::register_class<Spell>();
	ClassDB::register_class<Aura>();
	ClassDB::register_class<AuraStatAttribute>();

	ClassDB::register_class<EntityData>();
	ClassDB::register_class<MobData>();
	ClassDB::register_class<PlayerCharacterData>();
	
	ClassDB::register_class<XPData>();
	ClassDB::register_class<ItemStatModifier>();
	ClassDB::register_class<ItemTemplateStatModifier>();
	ClassDB::register_class<ItemEnums>();
	ClassDB::register_class<ItemTemplate>();
	ClassDB::register_class<ItemInstance>();
	ClassDB::register_class<SpellCooldownManipulationData>();
	ClassDB::register_class<Talent>();
	ClassDB::register_class<TalentRowData>();

	ClassDB::register_class<CharacterSkeletonVisualEntry>();

	ClassDB::register_class<DataManager>();

	ClassDB::register_class<ItemVisual>();
	ClassDB::register_class<ItemVisualEntry>();

	ClassDB::register_class<CharacterAtlas>();
	ClassDB::register_class<CharacterAtlasEntry>();

	ClassDB::register_class<CharacterBones>();

	//entity data
	ClassDB::register_class<EntityEnums>();

	ClassDB::register_class<StatModifier>();
	ClassDB::register_class<Stat>();
	ClassDB::register_class<StatDataEntry>();
	ClassDB::register_class<StatData>();

	ClassDB::register_class<CharacterSpec>();
    
	ClassDB::register_class<Bag>();
	ClassDB::register_class<Inventory>();

	ClassDB::register_class<SpellDamageInfo>();
	ClassDB::register_class<SpellHealInfo>();
	ClassDB::register_class<AuraData>();

	ClassDB::register_class<EntityResource>();

	ClassDB::register_class<AuraTriggerData>();

	//entities
	ClassDB::register_class<EntityCreateInfo>();
	ClassDB::register_class<Entity>();
	ClassDB::register_class<Player>();
	ClassDB::register_class<Mob>();

	//spellinfos
	ClassDB::register_class<SpellCastInfo>();

	//aurainfos
	ClassDB::register_class<AuraApplyInfo>();

	//UI
	ClassDB::register_class<UnitFrame>();

	ClassDB::register_class<ESDragAndDrop>();

	ClassDB::register_class<CharacterSkeleton>();
	ClassDB::register_class<CharacterSkeleton3D>();
    
    ClassDB::register_class<Cooldown>();
    ClassDB::register_class<CategoryCooldown>();

    ClassDB::register_class<EntityEquipSet>();

	ClassDB::register_class<LootDataBase>();
	ClassDB::register_class<LootDataItem>();
	ClassDB::register_class<LootDataContainter>();
   

    ClassDB::register_class<SpellEffectVisual>();
    ClassDB::register_class<SpellEffectVisualSimple>();
    ClassDB::register_class<SpellProjectileData>();
    ClassDB::register_class<WorldEffectData>();

    ClassDB::register_class<SpellProjectile>();
    ClassDB::register_class<WorldSpellEffect>();

	//AI
    ClassDB::register_class<AIAction>();
    ClassDB::register_class<AISpellAction>();
    ClassDB::register_class<AIActionContainer>();

	//meshes
	ClassDB::register_class<MeshDataResource>();

	#ifdef TOOLS_ENABLED
	EditorPlugins::add_by_type<EditorPluginColladaMdr>();
	#endif
}

void unregister_entity_spell_system_types() {

}

