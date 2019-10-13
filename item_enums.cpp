#include "item_enums.h"


const String ItemEnums::BINDING_STRING_RARITY = "None,Common,Uncommon,Superior,Heroic,Mythic,Artifact";
const String ItemEnums::BINDING_STRING_RARITY_FLAG = "Common,Uncommon,Superior,Heroic,Mythic,Artifact";
const String ItemEnums::BINDING_STRING_ITEM_TYPE = "None,Equipment,Weapon,Potion,Herb,Ore,Gemstone,Food,Alchemy,Engineering,Enchanting,Tailoring,Recipe,Currency,Bag";
const String ItemEnums::BINDING_STRING_ITEM_TYPE_FLAGS = "Equipment,Weapon,Potion,Herb,Ore,Gemstone,Food,Alchemy,Engineering,Enchanting,Tailoring,Recipe,Currency,Bag";
const String ItemEnums::BINDING_STRING_ITEM_SUB_TYPE = "None,Sword,Axe,Mace,Dagger,Bow,Crossbow,Gun,Wand,Quest Item";
const String ItemEnums::BINDING_STRING_ITEM_SUB_SUB_TYPE = "None,Two Hand,One Hand,Left Hand,Right Hand";
const String ItemEnums::BINDING_STRING_EQUIP_SLOTS = "Head,Neck,Shoulders,Chest,Gloves,Belt,Legs,Feet,Ring 1,Ring 2,Trinket 1,Trinket 2,Main Hand,Off Hand,None";
const String ItemEnums::BINDING_STRING_ARMOR_TYPE = "None,Cloth,Leather,Mail,Plate";

String ItemEnums::get_equip_slot_string(int slot) {
	switch (slot) {
		case 0:
			return "head";
		case 1:
			return "neck";
		case 2:
			return "shoulders";
		case 3:
			return "chest";
		case 4:
			return "gloves";
		case 5:
			return "belt";
		case 6:
			return "legs";
		case 7:
			return "feet";
		case 8:
			return "ring_1";
		case 9:
			return "ring_2";
		case 10:
			return "trinket_1";
		case 11:
			return "trinket_2";
		case 12:
			return "main_hand";
		case 13:
			return "off_hand";
	}

	return "";
}

String ItemEnums::get_armor_type_string(int type) {
	switch (type) {
		case 0:
			return "none";
		case 1:
			return "cloth";
		case 2:
			return "leather";
		case 3:
			return "mail";
		case 4:
			return "plate";
	}

	return "";
}
