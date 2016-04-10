void play_some_sound(void);
void safari_check_rbox_clear(void);
void overworld_free_bgmaps(void);
void c2_c5_trainer_card(void);
void * malloc_and_clear(u32);
u8 in_trade_center(void);
void sub_80898E8(void *);
void set_callback2(void(*)(void));
void vblank_handler_set(u32);
void hblank_handler_set(u32);
void lcd_io_set(u8, u16);
u16 lcd_io_get(u8);
void init_trainer_card_task_add(void);
void trainer_card_execute(void);
void trainer_card_dma_oam_clear(void);
void trainer_card_dma_pram_clear(void);
void trainer_card_io_reset(void);
void trainer_card_reset(void);
void sub_80F6E9C(void);
void trainer_card_change_card_colour_maybe(void);
void trainer_card_io_registers(void);
void gpu_pal_apply(void *, u16, u16);
void gpu_copy_to_tileset(u8, void *, u16, u16);
void LZ77UnCompWram(void *, void *);
u32 pokemon_getattr(void *, u8);
void trainer_card_malloc_stuff(void(*)(void));
void c2_trainer_card (void);
u8 trainer_card_load_images(void);
void trainer_card_apply_pals(void);
void trainer_card_load_strings(void);
u8 trainer_card_apply_img_pal(void);
void tasks_init(void);
void dp12_abort(void);
u8 sub_8001960(void);
void rboxid_clear_pixels(u8, u8);
u8 sub_8089DC8(void);
void sub_808ACC8(u8);
void sub_808B838(void);
void sub_808AE94(void *);
void sub_808AF04(void *);
void obj_80FCD74(u8, u8);
void sub_8070588(u32, u8, u8, u8, u16);
void sub_8088FF0(void);
u8 fade_and_return_progress_probably(void);
void audio_play(u16);
u8 mplay_has_finished_maybe(void);
void trainer_card_print_time(void);
void help_system_set_context(u8);
void sub_808B1D4(void);
void trainer_card_free_stuff(u8);
u8 sub_808B1FC(void);
u8 sub_8058244(void);
void sub_800AAC0(void);
void sub_80F6EE4(u8, u8);
u16 sub_8002C48(u8, u8, u8 *, u8, u8, u8, u32);
void rboxid_upload_a(u8, u8);
void bgid_fill_rectangle(u8, u16, u8, u8, u8, u8, u8);
void bgid_send_tilemap(u8);
void obj_and_aux_reset_all(void);
void pal_fade_control_and_dead_struct_reset(void);
void gpu_tile_bg_drop_all_sets(u32);
void bg_vram_setup(u8, void *, u8);
u32 bgid_mod_x_offset(u8, u32, u8);
u32 bgid_mod_y_offset(u8, u32, u8);
u8 rbox_8003B24(void *);
void sub_8002C28(u8);
void trainer_card_print_name(void);
void trainer_card_print_ID(void);
void trainer_card_print_money(void);
void trainer_card_print_dex(void);
void trainer_card_print_friend(void);
void box_print(u8, u8, u8, u8, u32, u8, u8 *);
void trainer_card_task(u8);
u8 task_add(void(*)(u8), u8);
void sub_808B774(void);
void trainer_card_check_badges(void);
void trainer_card_render_badges_in_order(void);
u8 get_icon_pal(u8);
void draw_big_rectangle(u8, u16, u8, u8, u8);
void graphic_change(void);
void trainer_card_print_pokemon(void);