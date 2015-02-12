#ifndef RO_PACKET_ENUM_H_INCLUDED
#define RO_PACKET_ENUM_H_INCLUDED


enum RO_PACKET_CONST_VALUE
{
	PLT_UNDEFINED=0,
	PLT_DEFAULT=2,
	PLT_AID_THROUGH=4,

	SEARCH_RANGE=0x00030000,
};


enum RO_LOG_TYPE
{
	SYS_PLAIN,
	SYS_MVP,
	SYS_ZC_ENTER_ACK,

	CHAT_NOR,
	CHAT_NOR_THIS=CHAT_NOR,
	CHAT_PRT,
	CHAT_GLD,
	CHAT_WIS_S,
	CHAT_WIS_R,
	CHAT_WIS_E,
	CHAT_GBC,
	CHAT_LBC,
};

////////////////////////////////////////////////////////////////////////////////


enum RO_CONDITION
{
	CI_NONE=0xFFFF,

	CI_HALLUCINATION=0x0022,	// NPC_HALLUCINATION
	CI_ELEMENTALCONV=0x0040,	// SA_ELEMENT???
	CI_ELEMENT_FIRE=0x005A,		// SA_FLAMELAUNCHER
	CI_ELEMENT_WATER,			// SA_FROSTWEAPON
	CI_ELEMENT_WIND,			// SA_LIGHTNINGLOADER
	CI_ELEMENT_GROUND,			// SA_SEISMICWEAPON
	CI_BERSERK=0x006B,			// LK_BERSERK
	CI_ASSUMPTIO=0x006E,		// HP_ASSUMPTIO
	CI_MAGICPOWER=0x0071,		// HW_MAGICPOWER
	CI_ELEMENT_SHADOW=0x0092,	// TK_SEVENWIND
	CI_ELEMENT_GHOST=0x0094,	// TK_SEVENWIND
	CI_SOULLINK,				// SL_???
	CI_KAITE=0x0099,			// SL_KAITE
	CI_KAUPE=0x009E,			// SL_KAUPE
	CI_TRUESIGHT=0x00B8,		// ???
	CI_CLOSECONFINE_OWN=0x00C8,	// RG_CLOSECONFINE
	CI_CLOSECONFINE_TGT,		// RG_CLOSECONFINE

	CI_MAX=0xFF,
};

////////////////////////////////////////////////////////////////////////////////


enum RO_PACKET
{
	PACKET_CA_AUTH_ENQ=0x0064,
	PACKET_CC_ENTER,
	PACKET_CC_SELECT,
	PACKET_CC_MAKE,
	PACKET_CC_DEL,
	PACKET_AC_AUTH_ACK,
	PACKET_AC_AUTH_NAK,
	PACKET_CC_ENTER_ACK,
	PACKET_CC_SELECT_NAK,
	PACKET_CC_MAKE_ACK,
	PACKET_CC_MAKE_NAK,
	PACKET_CC_DEL_ACK,
	PACKET_CC_DEL_NAK,
	PACKET_CC_SELECT_ACK,
	PACKET_CZ_ENTER,
	PACKET_ZC_ENTER_ACK,
	__PACKET_UK_0074,
	__PACKET_UK_0075,
	__PACKET_UK_0076,
	__PACKET_UK_0077,
	PACKET_ZC_ACTOR,
	PACKET_ZC_ACTOR_SPAWN,
	__PACKET_UK_007A,
	PACKET_ZC_ACTOR_MOVING,
	PACKET_ZC_ACTOR_NPC,
	PACKET_CZ_LOADED,
	PACKET_CZ_SYNC,
	PACKET_ZC_SYNC_ACK,
	PACKET_ZC_ERASE_ACTOR,
	PACKET_ZC_AUTH_ACK,
	PACKET_CZ_MOV=0x0085,
	__PACKET_UK_0086,
	PACKET_ZC_MOV_ACK,
	PACKET_ZC_MOVESTOP,				// PACKET_ZC_STOP_ACTOR,
	PACKET_CZ_ACT,
	PACKET_ZC_ACT_ACK,
	__PACKET_UK_008B,
	PACKET_CZ_CHAT,
	PACKET_ZC_CHAT,
	PACKET_ZC_CHAT_THIS,
	__PACKET_UK_008F,
	PACKET_CZ_NPC,
	PACKET_ZC_MAPCHANGE,
	PACKET_ZC_MAPCHANGE_IP,
	__PACKET_UK_0093,
	PACKET_CZ_NAME_ENQ,
	PACKET_ZC_NAME_ACK,
	PACKET_CZ_WHISPER,
	PACKET_ZC_WHISPER,
	PACKET_ZC_WHISPER_ACK,
	PACKET_CZ_BROADCAST,
	PACKET_ZC_BROADCAST,
	PACKET_CZ_SETDIR,
	PACKET_ZC_SETDIR,
	PACKET_ZC_DROPPED_ITEM1,
	PACKET_ZC_DROPPED_ITEM2,
	PACKET_CZ_PICKUP_ITEM,
	PACKET_ZC_PICKUP_ITEM_ACK,
	PACKET_ZC_ERAESE_ITEM,
	PACKET_CZ_DROP_ITEM,
	PACKET_ZC_ITEM1,
	PACKET_ZC_ITEM2,
	PACKET_ZC_STORAGEITEM1,
	PACKET_ZC_STORAGEITEM2,
	PACKET_CZ_USEITEM,
	PACKET_ZC_USEITEM_ACK,
	PACKET_CZ_EQUIP,
	PACKET_ZC_EQUIP_ACK,
	PACKET_CZ_UNEQUIP,
	PACKET_ZC_UNEQUIP_ACK,
	PACKET_UK_00AD,
	PACKET_UK_00AE,
	PACKET_ZC_DEC_ITEM,
	PACKET_ZC_STATUS1,
	PACKET_ZC_STATUS2,
	PACKET_CZ_RESTART_ENQ,
	PACKET_ZC_RESTART_ACK,

	PACKET_CZ_00BA=0x00BA,
	PACKET_CZ_STUP,
	PACKET_ZC_STUP_ACK,
	PACKET_ZC_STINFO,
	PACKET_ZC_STINFO_UPVAL,
	PACKET_CZ_EMOTION,
	PACKET_ZC_EMOTION,
	PACKET_CZ_WHO_ENQ,
	PACKET_ZC_WHO_ACK,
	PACKET_ZC_VIEWINFO,

	PACKET_CZ_GMCMD_00CC=0x00CC,	// PACKET_CZ_GMCMD_KILL,
	PACKET_ZC_GMCMD_00CC_ACK,		// PACKET_ZC_GMCMD_KILL_ACK,
	PACKET_CZ_GMCMD_00CE,			// PACKET_CZ_GMCMD_KILLALL,

	PACKET_CZ_PARTYCHAT=0x0108,
	PACKET_ZC_PARTYCHAT,
	PACKET_ZC_MVPITEM,
	PACKET_ZC_MVPEXP,
	PACKET_ZC_MVP,
	PACKET_ZC_MVP_WARNING,
	PACKET_ZC_SKINFO_REFLESH,
	PACKET_ZC_SKINFO,
	PACKET_ZC_SKILL_NCK,
	PACKET_ZC_SKINFO_ADD,
	PACKET_CZ_SKUP,
	PACKET_CZ_SKILL,
	PACKET_ZC_SKILL_ACK1,
	PACKET_ZC_SKILL_ACK2,
	PACKET_CZ_SKILL_GRD,			// PACKET_CZ_SKGRD,
	PACKET_ZC_SKILL_ACK3,			// PACKET_ZC_SKGRD_ACK,
	PACKET_CZ_SKILL_CANCEL,
	PACKET_ZC_OPTION,
	PACKET_ZC_SKILL_ACK4,
	PACKET_CZ_PORTAL_ACK,
	PACKET_ZC_PORTAL,
	PACKET_CZ_PORTAL_REG,
	PACKET_ZC_PORTAL_REG_ACK,
	PACKET_ZC_OBJECT,
	PACKET_ZC_OBJECT_RELEASE,

	PACKET_CZ_GUILDCHAT=0x017E,
	PACKET_ZC_GUILDCHAT,

	PACKET_CZ_NAME_ENQ2=0x0193,
	PACKET_ZC_NAME_ACK2,
	PACKET_ZC_NAME_ACK3,
	PACKET_ZC_CONDITION,
	PACKET_CZ_GMCMD_0197,
	PACKET_CZ_GMCMD_0198,
	PACKET_ZC_MAPMODE,
	PACKET_ZC_MAPRANK,
	PACKET_ZC_EFFECT,
	PACKET_CZ_BROADCAST2,
	PACKET_CZ_GMHIDE,

	PACKET_CZ_GMCMD_01C0=0x01C0,
	PACKET_ZC_01C1,
	PACKET_ZC_NONE,
	PACKET_ZC_BROADCAST2,
	PACKET_ZC_STORAGEITEM3,
	PACKET_ZC_STORAGEITEM4,
	__PACKET_UK_01C6,
	__PACKET_UK_01C7,
	PACKET_ZC_USEITEM_ACK2,
	PACKET_ZC_OBJECT2,

	PACKET_ZC_ACTOR2=0x01D8,
	PACKET_ZC_ACTOR2_SPAWN,
	PACKET_ZC_ACTOR2_MOVING,
	PACKET_CA_SEED_ENQ,
	PACKET_AC_SEED_ACK,
	PACKET_CA_AUTH2_ENQ,
	PACKET_ZC_SKILL_ACK5,

	PACKET_CZ_GMCMD_0212=0x0212,
	PACKET_CZ_GMCMD_0213,
	PACKET_ZC_STATUS3,
	PACKET_ZC_NOTICE1,				// PACKET_ZC_CONDITION2
	PACKET_ZC_NOTICE2,				// PACKET_ZC_ADOPTED
	PACKET_CZ_BSRANK_ENQ,
	PACKET_CZ_AMRANK_ENQ,
	PACKET_ZC_BSRANK,
	PACKET_ZC_AMRANK,
	PACKET_ZC_BSPOINT,
	PACKET_ZC_AMPOINT,
	PACKET_CZ_IS_EFFECT,
	PACKET_UK_021E,
	PACKET_ZC_021F,
	PACKET_ZC_0220,
	PACKET_ZC_REFINE,
	PACKET_CZ_REFINE_ENQ,
	PACKET_ZC_REFINE_ACK,
	PACKET_ZC_TKPOINT,
	PACKET_CZ_TKRANK_ENQ,
	PACKET_ZC_TKRANK,
	PACKET_NC_NPROTECT_0227,
	PACKET_CN_NPROTECT_0228,
	PACKET_ZC_OPTION2,
	PACKET_ZC_ACTOR3,
	PACKET_ZC_ACTOR3_SPAWN,
	PACKET_ZC_ACTOR3_MOVING,

	PACKET_ZC_PKPOINT=0x0236,
	PACKET_CZ_PKRANK_ENQ,
	PACKET_ZC_PKRANK,
	__PACKET_UK_0239,
	PACKET_ZC_STORAGEPASS_ENQ,
	PACKET_CZ_STORAGEPASS_ACK,
	PACKET_ZC_STORAGEPASS_ACK,
	__PACKET_UK_023D,
	PACKET_CC_CHARPASS_ENQ,

	PACKET_ZC_TKSKILL_ENQ=0x0253,
	PACKET_CZ_TKSKILL_ACK,

	PACKET_CN_NPROTECT_0258=0x0258,
	PACKET_NC_NPROTECT_0259,

	PACKET_ZC_NOTICE3=0x027B,
	PACKET_CA_AUTH3_ENQ,
	PACKET_ZC_027D,
	__PACKET_UK_027E,
	__PACKET_UK_027F,
	PACKET_ZC_TMPOINT,
	PACKET_CZ_TMRANK_ENQ,
	PACKET_ZC_TMRANK,
	__PACKET_UK_0283,
	PACKET_ZC_EFFECT2,
	PACKET_ZC_NOTICE4,
};


enum RO_PACKET_DERIVERD
{
	PACKET_ZC_ACTOR_STOP	= PACKET_ZC_MOVESTOP,
	PACKET_CZ_SKGRD			= PACKET_CZ_SKILL_GRD,
	PACKET_ZC_SKGRD_ACK		= PACKET_ZC_SKILL_ACK3,

//	PACKET_CZ_DEBUG			= PACKET_CZ_GMCMD_0213,
	PACKET_CZ_DEBUG			= PACKET_CZ_WHO_ENQ,
};


#endif	// #ifndef RO_PACKET_ENUM_H_INCLUDED