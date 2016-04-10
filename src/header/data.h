/*macroinstructions*/
#define HERO_X 0xB
#define HERO_Y 6
#define BADGE_FILLER 2

/*structs*/
struct fade_ctrl
{
	u16 bg_pal_bitfield;
	u16 obj_pal_bitfield;
	u16 scale;
	u16 mix_color;
	u8 field_8;
	u8 field_9;
	u8 field_A;
	u8 field_B;
};

struct trainer_card_t
{
	u8 unk_data[0x458];
	void(*ptr)(void);
	u8 unk_data2[0x60];
	u8 p_trainer_card_bg0_tilemap_front[0x4B0];
	u8 p_trainer_card_bg0_tilemap_back[0x4B0];
	u8 p_trainer_card_bg2_tilemap[0x4B0];
	u8 p_gym_badges[0x400];
	u8 p_trainer_card_icons[0x200];
	u8 p_trainer_card_tiles_bg0[0x1800];
	u8 unk_data3[0x4B05];
};

struct pal_struct
{
	u16 pal[16];
};

struct oam
{
	u16 attr0;
    u16 attr1;
    u16 attr2;
    s16 fill;
};

struct obj_affine
{
	u16 fill0[3];
    s16 pa;
    u16 fill1[3];
    s16 pb;
    u16 fill2[3];
    s16 pc;
    u16 fill3[3];
    s16 pd;
};

struct rbox
{
	struct rbox_short
	{
		u8 bg_id;
		u8 x;
		u8 y;
		u8 w;
		u8 h;
		u8 unk;
		u16 vram_tileset_offset;
	};
	u32 pixels;
};

struct superstate
{
	void(*callback1)(void);
	void(*callback2)(void);
	void(*callback2backup)(void);
	void(*callback5_vblank)(void);
	void(*hblank_callback)(void);
	u32 field_14;
	u32 field_18;
	u32 bits_to_wait_for;
	u32 ptr_vblank_counter;
	u32 field_24;
	u16 buttons0_held;
	u16 buttons1_new;
	u16 buttons2_held_remapped;
	u16 buttons3_new_remapped;
	u16 buttons4_new_and_keyrepeat;
	u16 keypad_countdown;
	u32 unused_apparently;
	struct oam sprites[128];
	u8 multi_purpose_state_tracker;
	u8 gpu_sprites_upload_skip;
};

struct pokemon
{
	u32 personality_value;
	u32 OTID;
	u8 nickname[10];
	u16 language;
	u8 OT_name[7];
	u8 markings;
	u16 checksum;
	u16 padding;
	u8 enc_data[48];
	u32 status;
	u8 level;
	u8 pokerus;
	u16 cur_hp;
	u16 tot_hp;
	u16 attack;
	u16 defense;
	u16 speed;
	u16 sattack;
	u16 sdefense;
};

struct task
{
	void (*fptr) (u8);
	u8 inuse;
	u8 prev;
	u8 next;
	u8 priority;
	u16 priv[16];
};

/*offsets*/
struct fade_ctrl * pal_fade_control = (struct fade_ctrl *) 0x2037AB8;
struct trainer_card_t ** trainer_card_data = (struct trainer_card_t **) 0x20397A4;
struct superstate * super = (struct superstate *) 0x30030F0;
struct pokemon * party_pokemon =(struct pokemon *) 0x2024284;
u8 * link_mode_is_wireless = (u8 *) 0x3003F3C;
u8 * byte_3003F64 = (u8 *) 0x3003F64;
struct task * tasks = (struct task *) 0x3005090;

u8 ** icon_pointer_table = (u8 **) 0x83D37A0;
u8 * icon_palette_table = (u8 *) 0x83D3E80;
struct pal_struct * icon_pal_table = (struct pal_struct *) 0x83D3740;
u16 * prizepalptr1 = (u16 *) 0x83CD320;
u16 * prizepalptr2 = (u16 *) 0x83CD340;
u16 * prizepalptr3 = (u16 *) 0x83CD360;
u16 * prizepalptr4 = (u16 *) 0x83CD380;
u8 * trainer_card_bg2_tilemap_1 = (u8 *) 0x83CCE30;
u8 * trainer_card_bg2_tilemap_2 = (u8 *) 0x83CCEC8;
u8 * trainer_card_bg0_tilemap_1_back = (u8 *) 0x83CC8A8;
u8 * trainer_card_bg0_tilemap_2_back = (u8 *) 0x83CC984;
u8 * trainer_card_bg0_tilemap_1_front = (u8 *) 0x83CC4DC;
u8 * trainer_card_bg0_tilemap_2_front = (u8 *) 0x83CC6F0;
u8 * trainer_card_bg0_tilemap_3_front = (u8 *) 0x83CCAB0;
u8 * trainer_card_bg0_tilemap_4_front = (u8 *) 0x83CCCA4;
u8 * lz_gym_badges = (u8 *) 0x83CD5E8;
u8 * lz_trainer_card_tiles_bg0_back = (u8 *) 0x8E998CC;
u8 * lz_trainer_card_tiles_bg0_front = (u8 *) 0x8E991F8;
u8 * text_wait =(u8 *) 0x8419D89;
u8 * byte_83CD95C = (u8 *) 0x83CD95C;
u8 * tile_egg = (u8 *) 0x8E7BB88;
u8 * tile_egg2 = (u8 *) 0x8E7BD88;
u8 * unk_83CD888 = (u8 *) 0x83CD888;
//pointer: 3a7360,3CD914
//8A028: 9A
//8A144: 98
//3CD930: 45
//3CD932: 57
//3CD934: 5C

/*arrays*/
const struct rbox_short rbox_cfg[4] __attribute__((aligned(4))) = 
{
	{1,2,0xF,0x1A,4,0xF,0x241},
	{1,1,1,0x1b,0x12,0xf,1},
	{3,HERO_X,HERO_Y,9,0xa,8,0x150},
	{0xff,0,0,0,0,0,0}
};

const u32 lz_trainer_card_icons[92] __attribute__((aligned(4))) =
{
	0x00020010,0x60000008,0x66020066,0x22006600,0x22666022,0x00666066,0x66662662,0x66666262,
	0x03002261,0x00060B00,0x04006600,0x10222224,0x10076622,0x02222611,0x26267666,0x29007666,
	0x66662176,0x62662E00,0x14006622,0x22226008,0x00431062,0x66106267,0x53007000,0x66777000,
	0x76666208,0x22271022,0x26087662,0x10072222,0x76266643,0x76660000,0x07770007,0x70004100,
	0x6033667F,0x03003666,0x0033332F,0x0A00330A,0x7F400330,0x00061400,0x07666333,0x21001110,
	0x33331876,0x00032063,0x36666336,0x66363606,0x3B206336,0x14004310,0x50336667,0x2B00367F,
	0x00BA6363,0x2F10362B,0x43103F00,0x007FF066,0x00466624,0x006446FB,0x10664403,0x00664444,
	0x6666460A,0x50644064,0x666466FF,0x18644600,0x00440766,0x761F0011,0x643F4664,0x00290076,

	0x101100FF,0x1033002B,0x4310883B,0x60466700,0x664646FF,0x102B20E9,0x073B0033,0x64664310,
	0x66607F00,0x7B01FFE0,0x56605555,0x66550755,0x20666556,0x60050003,0xA201C17F,0x55071900,
	0x00066555,0x10767F1F,0x010B0003,0x4023007F,0x01C60103,0x56662DBF,0x5156FF00,0x764D007F,
	0x20DC4D00,0x07A80103,0x03005900,0x00007F70,
};

const u16 prizepal[16] __attribute__((aligned(4))) = 
{
	0x5FDF,0x7FFF,0x531F,0x770C,0x279E,0x4A0D,0x7BDD,0x737B,0,0,0,0,0,0,0,0
};

const u8 loc_conversion[12] __attribute__((aligned(4))) = 
{
	0x14,6,0x14,0xA,0x14,0xE,0x18,6,0x18,0xA,0x18,0xE
};

const u8 pokemon_string[8]= 
{
	0xCA,0xE3,0xDF,0x1B,0xE1,0xE3,0xE2,0xFF
};