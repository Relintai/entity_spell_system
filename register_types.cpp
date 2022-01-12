/*
Copyright (c) 2019-2022 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "register_types.h"

#include "entity_enums.h"
#include "item_enums.h"

#include "singletons/ess.h"

#include "data/auras/aura_group.h"

#include "data/items/equipment_data.h"
#include "data/spells/spell_cooldown_manipulation_data.h"

#include "entities/data/entity_class_data.h"
#include "entities/data/entity_data.h"
#include "entities/data/entity_data_container.h"
#include "entities/data/item_container_data.h"
#include "entities/data/item_container_data_entry.h"
#include "entities/data/vendor_item_data.h"
#include "entities/data/vendor_item_data_entry.h"

#include "entities/skills/entity_skill.h"
#include "entities/skills/entity_skill_data.h"

#include "entities/data/character_spec.h"

#include "data/items/model_visual.h"
#include "data/items/model_visual_entry.h"

#include "data/atlases/character_atlas.h"
#include "data/atlases/character_atlas_entry.h"

#include "skeleton/character_bones.h"

#include "data/items/item_instance.h"
#include "data/items/item_template.h"

#include "data/spells/spell.h"
#include "entities/stats/complex_level_stat_data.h"
#include "entities/stats/level_stat_data.h"
#include "entities/stats/simple_level_stat_data.h"
#include "entities/stats/stat_data.h"

#include "inventory/bag.h"
//#include "inventory/inventory.h"

#include "data/items/craft_recipe.h"
#include "data/items/craft_recipe_helper.h"

#include "infos/aura_infos.h"
#include "infos/spell_cast_info.h"

#include "pipelines/spell_damage_info.h"
#include "pipelines/spell_heal_info.h"

#include "entities/resources/entity_resource.h"
#include "entities/resources/entity_resource_cost_data.h"
#include "entities/resources/entity_resource_cost_data_health.h"
#include "entities/resources/entity_resource_cost_data_resource.h"
#include "entities/resources/entity_resource_health.h"
#include "entities/resources/entity_resource_speed.h"

#include "entities/auras/aura_data.h"
#include "entities/entity.h"

#include "drag_and_drop/es_drag_and_drop.h"

#include "skeleton/character_skeleton_2d.h"
#include "skeleton/character_skeleton_3d.h"

#include "data/species/entity_species_data.h"
#include "data/species/species_instance.h"
#include "data/species/species_model_data.h"

#include "skeleton/skeleton_model_entry.h"

#include "utility/entity_create_info.h"

#include "data/loot/loot_data_base.h"

#include "data/spells/spell_effect_visual.h"
#include "data/spells/spell_effect_visual_simple.h"

#include "projectiles/3d/spell_follow_projectile_3d.h"

#include "entities/ai/entity_ai.h"

#include "formations/ai_formation.h"

#include "profiles/input/input_profile.h"
#include "profiles/input/input_profile_modifier.h"
#include "profiles/input/input_profile_modifier_entry.h"

#include "profiles/actionbar/action_bar_button_entry.h"
#include "profiles/actionbar/action_bar_entry.h"
#include "profiles/actionbar/action_bar_profile.h"

#include "profiles/class_profile.h"
#include "profiles/player_profile.h"

#include "spawners/ess_entity_spawner.h"

#include "singletons/profile_manager.h"

#include "editor/ess_editor_plugin.h"

#include "database/ess_resource_db.cpp"
#include "database/ess_resource_db_folders.h"
#include "database/ess_resource_db_map.h"
#include "database/ess_resource_db_static.h"

#include "material_cache/ess_material_cache.h"
#include "material_cache/ess_material_cache_pcm.h"

#if PROPS_PRESENT
#include "props/prop_data_entity.h"
#endif

static ESS *entity_data_manager = NULL;
static ProfileManager *profile_manager = NULL;

void register_entity_spell_system_types() {
#if PROPS_PRESENT
	ClassDB::register_class<PropDataEntity>();
#endif

	ClassDB::register_class<SpellEnums>();

	//data
	ClassDB::register_class<CraftRecipeHelper>();
	ClassDB::register_class<CraftRecipe>();

	ClassDB::register_class<Spell>();
	ClassDB::register_class<AuraGroup>();

	ClassDB::register_class<EntityData>();
	ClassDB::register_class<EntityClassData>();
	ClassDB::register_class<VendorItemData>();
	ClassDB::register_class<VendorItemDataEntry>();

	ClassDB::register_class<EntityDataContainer>();

	ClassDB::register_class<ItemContainerData>();
	ClassDB::register_class<ItemContainerDataEntry>();

	ClassDB::register_class<ItemEnums>();
	ClassDB::register_class<ItemTemplate>();
	ClassDB::register_class<ItemInstance>();
	ClassDB::register_class<SpellCooldownManipulationData>();

	ClassDB::register_class<EquipmentData>();

	ClassDB::register_class<EntitySkill>();
	ClassDB::register_class<EntitySkillData>();

	ClassDB::register_class<ModelVisual>();
	ClassDB::register_class<ModelVisualEntry>();

	ClassDB::register_class<CharacterAtlas>();
	ClassDB::register_class<CharacterAtlasEntry>();

	ClassDB::register_class<CharacterBones>();

	//entity data
	ClassDB::register_class<EntityEnums>();

	ClassDB::register_class<StatData>();

	ClassDB::register_class<LevelStatData>();
	ClassDB::register_class<SimpleLevelStatData>();
	ClassDB::register_class<ComplexLevelStatData>();

	ClassDB::register_class<CharacterSpec>();

	ClassDB::register_class<Bag>();

	ClassDB::register_class<SpellDamageInfo>();
	ClassDB::register_class<SpellHealInfo>();
	ClassDB::register_class<AuraData>();

	ClassDB::register_class<EntityResourceCostData>();
	ClassDB::register_class<EntityResourceCostDataHealth>();
	ClassDB::register_class<EntityResourceCostDataResource>();
	ClassDB::register_class<EntityResource>();
	ClassDB::register_class<EntityResourceHealth>();
	ClassDB::register_class<EntityResourceSpeed>();

	//entities
	ClassDB::register_class<EntityCreateInfo>();
	ClassDB::register_class<Entity>();

	//spellinfos
	ClassDB::register_class<SpellCastInfo>();

	//aurainfos
	ClassDB::register_class<AuraApplyInfo>();

	//UI
	ClassDB::register_class<ESDragAndDrop>();

	//Skeleton
	ClassDB::register_class<CharacterSkeleton2D>();
	ClassDB::register_class<CharacterSkeleton3D>();

	ClassDB::register_class<EntitySpeciesData>();
	ClassDB::register_class<SpeciesModelData>();
	ClassDB::register_class<SpeciesInstance>();

	ClassDB::register_class<SkeletonModelEntry>();

	ClassDB::register_class<LootDataBase>();

	ClassDB::register_class<SpellEffectVisual>();
	ClassDB::register_class<SpellEffectVisualSimple>();

	//Projectiles
	ClassDB::register_class<SpellFollowProjectile3D>();

	//AI
	ClassDB::register_class<EntityAI>();

	ClassDB::register_class<AIFormation>();

	//Resources
	ClassDB::register_virtual_class<ESSResourceDB>();
	ClassDB::register_class<ESSResourceDBStatic>();
	ClassDB::register_class<ESSResourceDBFolders>();
	ClassDB::register_class<ESSResourceDBMap>();

	//ProfileManager
	ClassDB::register_class<InputProfileModifier>();
	ClassDB::register_class<InputProfileModifierEntry>();
	ClassDB::register_class<InputProfile>();

	ClassDB::register_class<ActionBarButtonEntry>();
	ClassDB::register_class<ActionBarEntry>();
	ClassDB::register_class<ActionBarProfile>();

	ClassDB::register_class<ClassProfile>();
	ClassDB::register_class<PlayerProfile>();

	ClassDB::register_class<ProfileManager>();

	ClassDB::register_class<ESSEntitySpawner>();

	ClassDB::register_class<ESSMaterialCache>();
	ClassDB::register_class<ESSMaterialCachePCM>();

	entity_data_manager = memnew(ESS);
	ClassDB::register_class<ESS>();
	Engine::get_singleton()->add_singleton(Engine::Singleton("ESS", ESS::get_singleton()));

	profile_manager = memnew(ProfileManager);
	ClassDB::register_class<ProfileManager>();
	Engine::get_singleton()->add_singleton(Engine::Singleton("ProfileManager", ProfileManager::get_singleton()));

#ifdef TOOLS_ENABLED
	//EditorPlugins::add_by_type<ESSEditorPlugin>();
#endif
}

void unregister_entity_spell_system_types() {
	if (entity_data_manager) {
		memdelete(entity_data_manager);
	}

	if (profile_manager) {
		memdelete(profile_manager);
	}
}
