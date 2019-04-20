#include "register_types.h"

#include "entity_enums.h"
#include "item_enums.h"

#include "data/aura.h"
#include "data/data_manager.h"
#include "data/character.h"
#include "data/talent.h"
#include "data/talent_row_data.h"
#include "data/talent_rank_data.h"
#include "data/character_spec.h"
#include "data/xp_data.h"
#include "data/item_stat_modifier.h"
#include "data/item_template_stat_modifier.h"
#include "data/spell_cooldown_manipulation_data.h"

#include "data/item_template.h"
#include "data/item_data_instance.h"

#include "data/spell.h"
#include "data/icon.h"
#include "entities/stats/stat.h"
#include "entities/stats/stat_data.h"
#include "entities/player_talent.h"
#include "entities/item_instance.h"

#include "data/craft_data_attribute_helper.h"
#include "data/craft_data_attribute.h"

#include "spells/spell_cast_info.h"
#include "spells/aura_infos.h"

#include "data/aura_visual_effect.h"
#include "data/spell_visual_effect.h"

#include "pipelines/spell_damage_info.h"

#include "entities/auras/aura_data.h"
#include "entities/entity.h"
#include "entities/player.h"
#include "entities/mob.h"
#include "spells/spell_manager.h"
#include "data/aura_trigger_data.h"
#include "data/aura_stat_attribute.h"

#include "ui/unit_frame.h"

#include "drag_and_drop/es_drag_and_drop.h"

void register_entity_spell_system_types() {

	//data
	ClassDB::register_class<Icon>();
	ClassDB::register_class<CraftDataAttributeHelper>();
	ClassDB::register_class<CraftDataAttribute>();

	ClassDB::register_class<CharacterClass>();
	ClassDB::register_class<Spell>();
	ClassDB::register_class<Aura>();
	ClassDB::register_class<XPData>();
	ClassDB::register_class<ItemStatModifier>();
	ClassDB::register_class<ItemTemplateStatModifier>();
	ClassDB::register_class<ItemEnums>();
	ClassDB::register_class<ItemTemplate>();
	ClassDB::register_class<ItemDataInstance>();
	ClassDB::register_class<SpellCooldownManipulationData>();
	ClassDB::register_class<Talent>();
	ClassDB::register_class<TalentRowData>();
	ClassDB::register_class<TalentRankData>();

	ClassDB::register_class<AuraVisualEffect>();
	ClassDB::register_class<SpellVisualEffect>();

	ClassDB::register_class<DataManager>();

	//entity data
	ClassDB::register_class<EntityEnums>();

	ClassDB::register_class<StatModifier>();
	ClassDB::register_class<Stat>();
	ClassDB::register_class<StatDataEntry>();
	ClassDB::register_class<StatData>();

	ClassDB::register_class<PlayerTalent>();
	ClassDB::register_class<ItemInstance>();
	ClassDB::register_class<CharacterSpec>();


	ClassDB::register_class<SpellDamageInfo>();
	ClassDB::register_class<AuraData>();

	ClassDB::register_class<AuraTriggerData>();

	//entities
	ClassDB::register_class<Entity>();
	ClassDB::register_class<Player>();
	ClassDB::register_class<Mob>();

	//deprecated
	ClassDB::register_class<SpellManager>();

	//spellinfos
	ClassDB::register_class<SpellCastInfo>();

	//aurainfos
	ClassDB::register_class<AuraApplyInfo>();

	//UI
	ClassDB::register_class<UnitFrame>();

	ClassDB::register_class<ESDragAndDrop>();
}

void unregister_entity_spell_system_types() {

}

