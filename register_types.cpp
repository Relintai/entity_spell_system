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

void initialize_entity_spell_system_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
#if PROPS_PRESENT
		GDREGISTER_CLASS(PropDataEntity);
#endif

		GDREGISTER_CLASS(SpellEnums);

		//data
		GDREGISTER_CLASS(CraftRecipeHelper);
		GDREGISTER_CLASS(CraftRecipe);

		GDREGISTER_CLASS(Spell);
		GDREGISTER_CLASS(AuraGroup);

		GDREGISTER_CLASS(EntityData);
		GDREGISTER_CLASS(EntityClassData);
		GDREGISTER_CLASS(VendorItemData);
		GDREGISTER_CLASS(VendorItemDataEntry);

		GDREGISTER_CLASS(EntityDataContainer);

		GDREGISTER_CLASS(ItemContainerData);
		GDREGISTER_CLASS(ItemContainerDataEntry);

		GDREGISTER_CLASS(ItemEnums);
		GDREGISTER_CLASS(ItemTemplate);
		GDREGISTER_CLASS(ItemInstance);
		GDREGISTER_CLASS(SpellCooldownManipulationData);

		GDREGISTER_CLASS(EquipmentData);

		GDREGISTER_CLASS(EntitySkill);
		GDREGISTER_CLASS(EntitySkillData);

		GDREGISTER_CLASS(ModelVisual);
		GDREGISTER_CLASS(ModelVisualEntry);

		GDREGISTER_CLASS(CharacterAtlas);
		GDREGISTER_CLASS(CharacterAtlasEntry);

		GDREGISTER_CLASS(CharacterBones);

		//entity data
		GDREGISTER_CLASS(EntityEnums);

		GDREGISTER_CLASS(StatData);

		GDREGISTER_CLASS(LevelStatData);
		GDREGISTER_CLASS(SimpleLevelStatData);
		GDREGISTER_CLASS(ComplexLevelStatData);

		GDREGISTER_CLASS(CharacterSpec);

		GDREGISTER_CLASS(Bag);

		GDREGISTER_CLASS(SpellDamageInfo);
		GDREGISTER_CLASS(SpellHealInfo);
		GDREGISTER_CLASS(AuraData);

		GDREGISTER_CLASS(EntityResourceCostData);
		GDREGISTER_CLASS(EntityResourceCostDataHealth);
		GDREGISTER_CLASS(EntityResourceCostDataResource);
		GDREGISTER_CLASS(EntityResource);
		GDREGISTER_CLASS(EntityResourceHealth);
		GDREGISTER_CLASS(EntityResourceSpeed);

		//entities
		GDREGISTER_CLASS(EntityCreateInfo);
		GDREGISTER_CLASS(Entity);

		//spellinfos
		GDREGISTER_CLASS(SpellCastInfo);

		//aurainfos
		GDREGISTER_CLASS(AuraApplyInfo);

		//UI
		GDREGISTER_CLASS(ESDragAndDrop);

		//Skeleton
		GDREGISTER_CLASS(CharacterSkeleton2D);
		GDREGISTER_CLASS(CharacterSkeleton3D);

		GDREGISTER_CLASS(EntitySpeciesData);
		GDREGISTER_CLASS(SpeciesModelData);
		GDREGISTER_CLASS(SpeciesInstance);

		GDREGISTER_CLASS(SkeletonModelEntry);

		GDREGISTER_CLASS(LootDataBase);

		GDREGISTER_CLASS(SpellEffectVisual);
		GDREGISTER_CLASS(SpellEffectVisualSimple);

		//Projectiles
		GDREGISTER_CLASS(SpellFollowProjectile3D);

		//AI
		GDREGISTER_CLASS(EntityAI);

		GDREGISTER_CLASS(AIFormation);

		//Resources
		GDREGISTER_VIRTUAL_CLASS(ESSResourceDB);
		GDREGISTER_CLASS(ESSResourceDBStatic);
		GDREGISTER_CLASS(ESSResourceDBFolders);
		GDREGISTER_CLASS(ESSResourceDBMap);

		//ProfileManager
		GDREGISTER_CLASS(InputProfileModifier);
		GDREGISTER_CLASS(InputProfileModifierEntry);
		GDREGISTER_CLASS(InputProfile);

		GDREGISTER_CLASS(ActionBarButtonEntry);
		GDREGISTER_CLASS(ActionBarEntry);
		GDREGISTER_CLASS(ActionBarProfile);

		GDREGISTER_CLASS(ClassProfile);
		GDREGISTER_CLASS(PlayerProfile);

		GDREGISTER_CLASS(ProfileManager);

		GDREGISTER_CLASS(ESSEntitySpawner);

		GDREGISTER_CLASS(ESSMaterialCache);
		GDREGISTER_CLASS(ESSMaterialCachePCM);

		entity_data_manager = memnew(ESS);
		GDREGISTER_CLASS(ESS);
		Engine::get_singleton()->add_singleton(Engine::Singleton("ESS", ESS::get_singleton()));

		profile_manager = memnew(ProfileManager);
		GDREGISTER_CLASS(ProfileManager);
		Engine::get_singleton()->add_singleton(Engine::Singleton("ProfileManager", ProfileManager::get_singleton()));
	}

#ifdef TOOLS_ENABLED
	if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
		EditorPlugins::add_by_type<ESSEditorPlugin>();
	}
#endif
}

void uninitialize_entity_spell_system_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		if (entity_data_manager) {
			memdelete(entity_data_manager);
		}

		if (profile_manager) {
			memdelete(profile_manager);
		}
	}
}
