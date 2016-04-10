#include "header/AgbTypes.h"
#include "header/funcs.h"
#include "header/data.h"

u8 sm_trainer_1(void)
{
	if((u8)(pal_fade_control->mix_color>>8) & (u8)0x80)
		return 0;
	play_some_sound();
	safari_check_rbox_clear();
	overworld_free_bgmaps();
	trainer_card_malloc_stuff(c2_c5_trainer_card);
	return 1;
}

void trainer_card_malloc_stuff(void(*c2_c5)(void))
{
	(*trainer_card_data) = (struct trainer_card_t *)malloc_and_clear((0x7bd1));
	(*trainer_card_data)->ptr = c2_c5;
	(*trainer_card_data)->unk_data[5] = in_trade_center();
	(*trainer_card_data)->unk_data3[0x4B03] = (u8)2;
	sub_80898E8((*trainer_card_data)->unk_data2);
	set_callback2(c2_trainer_card);
	return;	
}

void c2_trainer_card(void)
{
	switch(super->multi_purpose_state_tracker)
	{
		case 0:
			vblank_handler_set(0);
			hblank_handler_set(0);
			lcd_io_set((u8)0, (u16)0);
			init_trainer_card_task_add();
			break;
		case 1:
			break;
		case 2:
			trainer_card_dma_oam_clear();
			break;
		case 3:
			trainer_card_dma_pram_clear();
			(super->multi_purpose_state_tracker)++;
		case 4:
			trainer_card_io_reset();
			break;
		case 5:
			trainer_card_reset();
			break;
		case 6:
			sub_80F6E9C(); //it seems to have no use. 
			break;
		case 7:
			trainer_card_change_card_colour_maybe();
			break;
		case 8:
			if(trainer_card_load_images() == 1)
				break;
			else return;			
		case 9:
			trainer_card_apply_pals();
			break;
		case 10:
			trainer_card_io_registers();
			break;
		case 11:
			trainer_card_load_strings();
			break;
		case 12:
			if(trainer_card_apply_img_pal() == 1)
				break;
			else return;
		case 13:
			break;
		default:
			trainer_card_execute();
			return;
	}
	(super->multi_purpose_state_tracker)++;
	return;
}

void trainer_card_apply_pals(void)
{
	u32 i,j;
	u32 k = 0;
	gpu_pal_apply(prizepal, 0xb0, 0x20);
	gpu_pal_apply(icon_pal_table, 0xc0, 0x20);
	gpu_pal_apply(icon_pal_table + 1, 0xd0, 0x20);
	gpu_pal_apply(icon_pal_table + 2, 0xe0, 0x20);
	gpu_copy_to_tileset((u8)3, (*trainer_card_data)->p_trainer_card_icons, (u16)0x400, (u16)0x80);
	for (i = 0; i < 6; i++)
	{	
		j = pokemon_getattr(party_pokemon + i, 0xb);
		if(j == 0)
			break;
		if(pokemon_getattr(party_pokemon + i, 0x2d) == 1)
			gpu_copy_to_tileset((u8)3, tile_egg, (u16)0x400, (u16)(0x220 + 0x10 * k));
		else
			gpu_copy_to_tileset((u8)3, *(icon_pointer_table + j), (u16)0x400, (u16)(0x220 + 0x10 * k));
		++k;
	}
	for (i = 0, k = 0; i < 6; i++)
	{	
		j = pokemon_getattr(party_pokemon + i, 0xb);
		if(j == 0)
			break;
		if(pokemon_getattr(party_pokemon + i, 0x2d) == 1)
			gpu_copy_to_tileset((u8)3, tile_egg2, (u16)0x200, (u16)(0x280 + 0x10 * k));
		else
			gpu_copy_to_tileset((u8)3, *(icon_pointer_table + j)+0x200, (u16)0x200, (u16)(0x280 + 0x10 * k));
		++k;
	}
	return;
}

void init_trainer_card_task_add(void)
{
	tasks_init();
	dp12_abort();
	task_add(trainer_card_task, 0);
	sub_808B774();
	trainer_card_check_badges();
	return;
}

u8 trainer_card_load_images(void)
{
	switch((*trainer_card_data)->unk_data[2])
	{
		case 0:
			if((*trainer_card_data)->unk_data[0x457] == 1)
				LZ77UnCompWram(trainer_card_bg2_tilemap_1, (*trainer_card_data)->p_trainer_card_bg2_tilemap);
			else
				LZ77UnCompWram(trainer_card_bg2_tilemap_2, (*trainer_card_data)->p_trainer_card_bg2_tilemap);
			break;
		case 1:
			if((*trainer_card_data)->unk_data[0x457] == 1)
				LZ77UnCompWram(trainer_card_bg0_tilemap_1_back, (*trainer_card_data)->p_trainer_card_bg0_tilemap_back);
			else
				LZ77UnCompWram(trainer_card_bg0_tilemap_2_back, (*trainer_card_data)->p_trainer_card_bg0_tilemap_back);
			break;
		case 2:
			if((*trainer_card_data)->unk_data[5])
			{
				if((*trainer_card_data)->unk_data[0x457] == 1)
					LZ77UnCompWram(trainer_card_bg0_tilemap_3_front, (*trainer_card_data)->p_trainer_card_bg0_tilemap_front);
				else
					LZ77UnCompWram(trainer_card_bg0_tilemap_4_front, (*trainer_card_data)->p_trainer_card_bg0_tilemap_front);
			}
			else
			{	
				if((*trainer_card_data)->unk_data[0x457] == 1)
					LZ77UnCompWram(trainer_card_bg0_tilemap_1_front, (*trainer_card_data)->p_trainer_card_bg0_tilemap_front);
				else
					LZ77UnCompWram(trainer_card_bg0_tilemap_2_front, (*trainer_card_data)->p_trainer_card_bg0_tilemap_front);
			}
			break;
		case 3:
			LZ77UnCompWram(lz_gym_badges, (*trainer_card_data)->p_gym_badges);
			break;
		case 4:
			if((*trainer_card_data)->unk_data[0x457] == 1)
				LZ77UnCompWram(lz_trainer_card_tiles_bg0_back, (*trainer_card_data)->p_trainer_card_tiles_bg0);
			else
				LZ77UnCompWram(lz_trainer_card_tiles_bg0_front, (*trainer_card_data)->p_trainer_card_tiles_bg0);
			break;
		case 5:
			if((*trainer_card_data)->unk_data[0x457])
				break;
			else
				LZ77UnCompWram(lz_trainer_card_icons, (*trainer_card_data)->p_trainer_card_icons);
				break;
		default:
			(*trainer_card_data)->unk_data[2] = (u8)1;
			return 1;
	}
	((*trainer_card_data)->unk_data[2])++;
	return 0;
}

void trainer_card_task(u8 task_id)
{
	switch((*trainer_card_data)->unk_data[0])
	{
		case 0:
			if(sub_8001960())
				return;
			else 
				{
					rboxid_clear_pixels(1,0);
					break;
				}
		case 1:
			if(sub_8089DC8())
				break;
			else return;
		case 2:
			sub_808ACC8(1);
			break;
		case 3:
			rboxid_clear_pixels(2, 0);
			sub_808B838();
			sub_808ACC8(2);
			break;
		case 4:
			sub_808AE94((*trainer_card_data)->p_trainer_card_bg2_tilemap);
			break;
		case 5:
			sub_808AF04((*trainer_card_data)->p_trainer_card_bg0_tilemap_front);
			break;
		case 6:
			trainer_card_render_badges_in_order();
			break;
		case 7:
			if ((*link_mode_is_wireless) == 1 && (*byte_3003F64) == 1)
				obj_80FCD74(0xe6, 0x96); //X, Y
			sub_8070588(0xFFFFFFFF, 0, 0x10, 0, 0); //something about fade
			vblank_handler_set(0x8088FF1);
			break;
		case 8:
			if(fade_and_return_progress_probably())
				return;
			else
				{
					if(sub_8001960())
						return;
					else
					{
						audio_play(0xF4);
						(*trainer_card_data)->unk_data[0] = (u8)0xA;
						return;
					}
				}
		case 9:
			if(mplay_has_finished_maybe())
				return;
			else break;
		case 10:
			if(*byte_3003F64 == 0 && (*trainer_card_data)->unk_data3[0x4B02] != 0)
			{
				trainer_card_print_time();
				graphic_change();
				sub_808ACC8(1);
				(*trainer_card_data)->unk_data3[0x4B02] = 0;
			}
			if((super->buttons3_new_remapped & (u16)1) != 0)
			{
				help_system_set_context(0xb);
				sub_808B1D4();
				audio_play(0xF2);
				(*trainer_card_data)->unk_data[0] = (u8)0xC;
				return;
			}
			else 
			{	
				if((super->buttons3_new_remapped & (u16)2) == 0)
					return;
				else
				{
					if(*byte_3003F64 != 0 && (*trainer_card_data)->unk_data[5] != 0)
					{
						if(in_trade_center() == 1)
						{
							(*trainer_card_data)->unk_data[0] = (u8)0xF;
							return;
						}
					}
					sub_8070588(0xFFFFFFFF, 0, 0, 0x10, 0);
					(*trainer_card_data)->unk_data[0] = (u8)0xE;
					return;
				}
			}
		case 11:
			if((super->buttons3_new_remapped & (u16)2) == 0)
			{
				if((super->buttons3_new_remapped & (u16)1) == 0)
					return;
				else
				{
					if (*byte_3003F64 == 0 && (*trainer_card_data)->unk_data[5] == 0 && in_trade_center() != 1)
					{
						sub_8070588(0xFFFFFFFF, 0, 0, 0x10, 0);
						(*trainer_card_data)->unk_data[0] = (u8)0xE;
						return;
					}
					else
					{
						(*trainer_card_data)->unk_data[0] = (u8)0xF;
						return;
					}
				}
			}
			else
			{
				if (*byte_3003F64 == 0)
				{
					help_system_set_context(0xA);
					sub_808B1D4();
					(*trainer_card_data)->unk_data[0] = (u8)0xD;
					audio_play(0xF2);
					return;
				}
				else
				{
					if((*trainer_card_data)->unk_data[5] == 0)
					{
						if (*byte_3003F64 == 0)
						{	
							help_system_set_context(0xA);
							sub_808B1D4();
							(*trainer_card_data)->unk_data[0] = (u8)0xD;
							audio_play(0xF2);
							return;
						}
						else
						{
							sub_8070588(0xFFFFFFFF, 0, 0, 0x10, 0);
							(*trainer_card_data)->unk_data[0] = (u8)0xE;
							return;
						}
					}
					else
					{
						if(in_trade_center() == 1)
						{
							(*trainer_card_data)->unk_data[0] = (u8)0xF;
							return;
						}
						else
						{
							if (*byte_3003F64 == 0)
							{	
								help_system_set_context(0xA);
								sub_808B1D4();
								(*trainer_card_data)->unk_data[0] = (u8)0xD;
								audio_play(0xF2);
								return;
							}
							else
							{
								sub_8070588(0xFFFFFFFF, 0, 0, 0x10, 0);
								(*trainer_card_data)->unk_data[0] = (u8)0xE;
								return;
							}	
						}
					}
				}
			}
		case 12:
			if(!sub_808B1FC())
				return;
			else
			{
				if(sub_8058244() == 1)
					return;
				else
				{
					audio_play(0xF4);
					(*trainer_card_data)->unk_data[0] = (u8)0xB;
					return;
				}
			}
				
		case 13:
			if(sub_808B1FC() == 0 || sub_8058244() == 1)
				return;
			else
				(*trainer_card_data)->unk_data[0] = (u8)0xA;
				audio_play(0xF4);
				return;
		case 14:
			if(fade_and_return_progress_probably())
				return;
			else
			{
				trainer_card_free_stuff(task_id);
				return;
			}
		case 15:
			sub_800AAC0();
			sub_80F6EE4(0, 1);
			sub_8002C48(0, 2, text_wait, 0, 1, 0xFF, 0);
			rboxid_upload_a(0, 3);
			(*trainer_card_data)->unk_data[0] = (u8)0x10;
		case 16:
			if(*byte_3003F64)
				return;
			else 
			{
				sub_8070588(0xFFFFFFFF, 0, 0, 0x10, 0);
				(*trainer_card_data)->unk_data[0] = (u8)0xE;
				return;
			}	
		default:
			return;
	}
	((*trainer_card_data)->unk_data[0])++;
	return;
}
	
void trainer_card_render_badges_in_order(void)
{
	int i;
	/*star_draw*/
	bgid_fill_rectangle(3, 0x8f, 0xb, *(byte_83CD95C + (*trainer_card_data)->unk_data[0x457]),(*trainer_card_data)->unk_data[0x45D], 1, 4);
	/*badge_draw*/
	for(i = 0; i < 8; i++)
		if((*trainer_card_data)->unk_data[0x11 + i])
			{
				bgid_fill_rectangle(3, 0xC0 + 2 * i, 4 + BADGE_FILLER * i, 0x10, 1, 1, 3);
				bgid_fill_rectangle(3, 0xC1 + 2 * i, 5 + BADGE_FILLER * i, 0x10, 1, 1, 3);
				bgid_fill_rectangle(3, 0xD0 + 2 * i, 4 + BADGE_FILLER * i, 0x11, 1, 1, 3);
				bgid_fill_rectangle(3, 0xD1 + 2 * i, 5 + BADGE_FILLER * i, 0x11, 1, 1, 3);
			}
	/*icon_draw*/
	for(i = 0; i < 6; i++)
		draw_big_rectangle(3, 0x2E0 + 0x10 * i, loc_conversion[2*i], loc_conversion[2*i+1], get_icon_pal(i));
	(*trainer_card_data)->unk_data3[0x4B04] = 1;
	bgid_send_tilemap(3);
	return;
}

void trainer_card_reset(void)
{
	u32 i;
	obj_and_aux_reset_all();
	pal_fade_control_and_dead_struct_reset();
	gpu_tile_bg_drop_all_sets(0);
	bg_vram_setup(0, unk_83CD888, 4);
	for (i = 0; i < 4; i++)
	{
		bgid_mod_x_offset(i, 0, 0);
		bgid_mod_y_offset(i, 0, 0);
	}
	sub_8002C28(rbox_8003B24(rbox_cfg));
	return;
}

u8 get_icon_pal(u8 party_index)
{
	if(pokemon_getattr(party_pokemon + party_index, 0x2d))
		return 0xd;
	else
		return (*(icon_palette_table+(pokemon_getattr(party_pokemon + party_index, 0xb))) + 0xC);
}

void draw_big_rectangle(u8 bg_id, u16 char_name, u8 x, u8 y, u8 pal)
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			bgid_fill_rectangle(bg_id, char_name++, x+j, y+i, 1, 1, pal);
	return;
}

u8 sub_808B4D8(struct task * task_addr)
{
	(*trainer_card_data)->unk_data[9] = 0;
	if((*trainer_card_data)->unk_data[8])
	{
		sub_808ACC8(2);
		sub_808AE94((*trainer_card_data)->p_trainer_card_bg2_tilemap);
		sub_808AF04((*trainer_card_data)->p_trainer_card_bg0_tilemap_front);
		trainer_card_render_badges_in_order();
	}
	sub_808ACC8(1);
	(*trainer_card_data)->unk_data[8] ^= 1;
	task_addr->priv[0]++;
	(*trainer_card_data)->unk_data[9] = 1;
	audio_play(0xF3);
	return 0;
}

void graphic_change(void)
{
	int i;
	for(i = 0; i < 6; i++)
		draw_big_rectangle(3, 0x2E0 + 0x10 * i + 0x60 * (*trainer_card_data)->unk_data3[0x4B04], loc_conversion[2*i], loc_conversion[2*i+1], get_icon_pal(i));
	(*trainer_card_data)->unk_data3[0x4B04] ^= 1;
	bgid_send_tilemap(3);
	return;
}

u8 sub_8089DC8(void)
{
	switch((*trainer_card_data)->unk_data[1])
	{
		case 0:
			trainer_card_print_name(); break;
		case 1:
			trainer_card_print_ID(); break;
		case 2:
			trainer_card_print_money(); break;
		case 3:
			trainer_card_print_dex(); break;
		case 4:
			trainer_card_print_time(); break;
		case 5:
			trainer_card_print_friend(); break;
		case 6:
			trainer_card_print_pokemon(); break;
		default:
		return 1;
	}
	(*trainer_card_data)->unk_data[1]++;
	return 0;
}

void trainer_card_print_pokemon(void)
{
	box_print(1,2,0x9E,0x1D,0x83CD8E0,0xFF,pokemon_string);
	return;
}