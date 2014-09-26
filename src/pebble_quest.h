/******************************************************************************
   Filename: pebble_quest.h

     Author: David C. Drake (http://davidcdrake.com)

Description: Header file for the 3D, first-person, fantasy RPG PebbleQuest,
             developed for the Pebble smartwatch (SDK 2.0). Copyright 2014,
             David C. Drake. More information available online:
             http://davidcdrake.com/pebblequest
******************************************************************************/

#ifndef PEBBLE_QUEST_H_
#define PEBBLE_QUEST_H_

#include <pebble.h>

/******************************************************************************
  Constants
******************************************************************************/

#define SCROLL_STR_LEN                  250
#define SCROLL_TEXT_LAYER_FRAME         GRect(3, 0, SCREEN_WIDTH - 6, SCROLL_STR_LEN * 4)
#define SCROLL_HEIGHT_OFFSET            10 // Ensures descenders (e.g., 'y') are fully visible.
#define SCROLL_FONT                     fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD)
#define MENU_HEADER_STR_LEN             23
#define MENU_TITLE_STR_LEN              13
#define MENU_SUBTITLE_STR_LEN           21
#define SCREEN_WIDTH                    144
#define SCREEN_HEIGHT                   168
#define SCREEN_CENTER_POINT_X           (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_POINT_Y           (SCREEN_HEIGHT / 2 - STATUS_BAR_HEIGHT * 0.75)
#define SCREEN_CENTER_POINT             GPoint(SCREEN_CENTER_POINT_X, SCREEN_CENTER_POINT_Y)
#define STATUS_BAR_HEIGHT               16 // Applies to top and bottom status bars.
#define FULL_SCREEN_FRAME               GRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - STATUS_BAR_HEIGHT)
#define STATUS_BAR_FRAME                GRect(0, GRAPHICS_FRAME_HEIGHT, GRAPHICS_FRAME_WIDTH, STATUS_BAR_HEIGHT)
#define STATUS_BAR_FONT                 fonts_get_system_font(FONT_KEY_GOTHIC_14)
#define COMPASS_RADIUS                  5
#define STATUS_METER_PADDING            4
#define STATUS_METER_WIDTH              (GRAPHICS_FRAME_WIDTH / 2 - COMPASS_RADIUS - 2 * STATUS_METER_PADDING)
#define STATUS_METER_HEIGHT             (STATUS_BAR_HEIGHT - STATUS_METER_PADDING * 2)
#define NO_CORNER_RADIUS                0
#define SMALL_CORNER_RADIUS             3
#define NINETY_DEGREES                  (TRIG_MAX_ANGLE / 4)
#define DEFAULT_ROTATION_RATE           (TRIG_MAX_ANGLE / 30) // 12 degrees per rotation event
#define MULTI_CLICK_MIN                 2
#define MULTI_CLICK_MAX                 2 // We only care about double-clicks.
#define MULTI_CLICK_TIMEOUT             0
#define LAST_CLICK_ONLY                 true
#define LONG_CLICK_DELAY                0    // milliseconds
#define MIN_MOVEMENT_INTERVAL           1000 // milliseconds per step
#define MAX_MOVEMENT_INTERVAL           200  // milliseconds per step
#define PLAYER_TIMER_DURATION           20   // milliseconds
#define FLASH_TIMER_DURATION            20   // milliseconds
#define MAX_INT_VALUE                   9999
#define MAX_INT_DIGITS                  4
#define FIRST_WALL_OFFSET               STATUS_BAR_HEIGHT
#define MIN_WALL_HEIGHT                 STATUS_BAR_HEIGHT
#define GRAPHICS_FRAME_WIDTH            SCREEN_WIDTH
#define GRAPHICS_FRAME_HEIGHT           (SCREEN_HEIGHT - 2 * STATUS_BAR_HEIGHT)
#define GRAPHICS_FRAME                  GRect(0, 0, GRAPHICS_FRAME_WIDTH, GRAPHICS_FRAME_HEIGHT)
#define LOCATION_WIDTH                  15
#define LOCATION_HEIGHT                 LOCATION_WIDTH
#define MAX_VISIBILITY_DEPTH            6 // Helps determine no. of cells visible in a given line of sight.
#define MIN_VISIBILITY_DEPTH            2 // Min. no. of cells visible in a given line of sight.
#define DEFAULT_VISIBILITY_DEPTH        (MAX_VISIBILITY_DEPTH + MIN_VISIBILITY_DEPTH) / 2 + (MAX_VISIBILITY_DEPTH + MIN_VISIBILITY_DEPTH) % 2;
#define STRAIGHT_AHEAD                  (MAX_VISIBILITY_DEPTH - 1) // Index value for "g_back_wall_coords".
#define TOP_LEFT                        0                          // Index value for "g_back_wall_coords".
#define BOTTOM_RIGHT                    1                          // Index value for "g_back_wall_coords".
#define RANDOM_POINT_NORTH              GPoint(rand() % LOCATION_WIDTH, 0)
#define RANDOM_POINT_SOUTH              GPoint(rand() % LOCATION_WIDTH, LOCATION_HEIGHT - 1)
#define RANDOM_POINT_EAST               GPoint(LOCATION_WIDTH - 1, rand() % LOCATION_HEIGHT)
#define RANDOM_POINT_WEST               GPoint(0, rand() % LOCATION_HEIGHT)
#define MAIN_MENU_NUM_ROWS              4
#define AD_HOC_MENU_NUM_ROWS            4
#define DEFAULT_BASE_STAT_VALUE         1
#define DEFAULT_PHYSICAL_POWER          10
#define DEFAULT_PHYSICAL_DEFENSE        10
#define DEFAULT_MAGICAL_POWER           10
#define DEFAULT_MAGICAL_DEFENSE         10
#define DEFAULT_SPEED                   30
#define DEFAULT_MAX_HP                  30
#define DEFAULT_MAX_MP                  30
#define DEFAULT_STAT_BOOST              5
#define RANDOM_GOLD_AMOUNT              (rand() % 20 + 1)
#define DEFAULT_QUEST_REWARD            (25 * (rand() % 10 + 1))
#define NUM_PLAYER_ANIMATIONS           2 // No. of steps in the player's attack animation.
#define HP_RECOVERY_RATE                1 // HP per second.
#define MP_RECOVERY_RATE                1 // MP per second.
#define MIN_DAMAGE                      2
#define MP_LOSS_PER_SPELL               -2
#define STORAGE_KEY                     841
#define MAX_HEAVY_ITEMS                 6
#define NUM_HEAVY_ITEM_TYPES            11 // ROBE, SHIELD, and armor/weapons.
#define NUM_SPECIAL_ITEM_TYPES          3  // GOLD, KEY, and ARTIFACT.
#define NUM_POTION_TYPES                2  // HP_POTION and MP_POTION.
#define NUM_PEBBLE_TYPES                7
#define CHEAP_ITEM_VALUE                50
#define EXPENSIVE_ITEM_VALUE            100
#define VERY_EXPENSIVE_ITEM_VALUE       150
#define PEBBLE_VALUE                    200
#define PLAYER_INVENTORY_SIZE           (NUM_SPECIAL_ITEM_TYPES + NUM_PEBBLE_TYPES + NUM_POTION_TYPES + MAX_HEAVY_ITEMS)
#define MERCHANT_INVENTORY_SIZE         (NUM_POTION_TYPES + NUM_HEAVY_ITEM_TYPES)
#define MAX_INFUSED_PEBBLES             2
#define MAX_NPCS_AT_ONE_TIME            3
#define MIN_NPCS_PER_QUEST              10
#define MAX_NPCS_PER_QUEST              30
#define ANIMATED                        true
#define NOT_ANIMATED                    false

/******************************************************************************
  Enumerations (replaced with #defines to save memory)
******************************************************************************/

// Quest types:
#define FIND_PEBBLE           0 // Find one of the legendary Pebbles of Power!
#define FIND_ITEM             1 // Find a valuable item for someone.
#define RECOVER_ITEM          2 // Find a lost object (or gold) for someone.
#define ESCORT                3 // Lead people safely from point A to point B.
#define RESCUE                4 // Find people and get them to safety.
#define ASSASSINATE           5 // Kill a specific enemy.
#define EXTERMINATE           6 // Kill all enemies.
#define ESCAPE                7 // You've been captured. Get out alive!
#define MAIN_QUEST_CONCLUSION 8 // Defeat the traitorous Archmage.
#define NUM_QUEST_TYPES       9

// Location types:
#define CAVE               0
#define TUNNEL             1
#define TOWN               2
#define CASTLE             3
#define TOWER              4
#define NUM_LOCATION_TYPES 5

// Cell types, including loot/item types:
#define CLOSED_DOOR         0
#define LOCKED_DOOR         1
#define SOLID               2
#define EMPTY               3
#define CAPTIVE             4
#define LOOT                5 // Plus item type value (see below).

// Item types:
#define GOLD                0
#define KEY                 1
#define ARTIFACT            2
#define HP_POTION           3
#define MP_POTION           4
#define PEBBLE_OF_FIRE      5
#define PEBBLE_OF_ICE       6
#define PEBBLE_OF_LIGHTNING 7
#define PEBBLE_OF_LIFE      8
#define PEBBLE_OF_DEATH     9
#define PEBBLE_OF_LIGHT     10
#define PEBBLE_OF_DARKNESS  11
#define ROBE                12
#define LIGHT_ARMOR         13
#define HEAVY_ARMOR         14
#define SHIELD              15
#define DAGGER              16
#define SWORD               17
#define AXE                 18
#define STAFF               19
#define MACE                20
#define FLAIL               21
#define BOW                 22

#define FIRST_HEAVY_ITEM_INDEX ROBE

// Equip targets (i.e., places where an item may be equipped):
#define BODY              0
#define RIGHT_HAND        1
#define LEFT_HAND         2
#define NUM_EQUIP_TARGETS 3

// NPC types:
#define ARCHMAGE        0
#define MAGE            1
#define THIEF           2
#define WARRIOR         3
#define BAT             4
#define WOLF            5
#define BEAR            6
#define GOBLIN          7
#define ORC             8
#define OGRE            9
#define TROLL           10
#define SLIME           11
#define SKELETON        12
#define ZOMBIE          13
#define WRAITH          14
#define FIRE_ELEMENTAL  15
#define ICE_ELEMENTAL   16
#define STORM_ELEMENTAL 17
#define NUM_NPC_TYPES   18

// Character stats (order here matters for the stats menu):
#define STRENGTH            0
#define AGILITY             1
#define INTELLECT           2
#define MAX_HP              3
#define MAX_MP              4
#define PHYSICAL_POWER      5
#define PHYSICAL_DEFENSE    6
#define MAGICAL_POWER       7
#define MAGICAL_DEFENSE     8
#define CURRENT_HP          9
#define CURRENT_MP          10
#define NUM_CHARACTER_STATS 11

// Status effects:
#define BURNED             0
#define FROZEN             1
#define SHOCKED            2
#define BLIND              3
#define SCARED             4
#define STUNNED            5
#define BLEEDING           6
#define NUM_STATUS_EFFECTS 7

// Perks:
#define DUAL_WIELDING_WEAPONS 0
#define DUAL_WIELDING_PEBBLES 1
#define FAST_RECOVERY_HP      2
#define FAST_RECOVERY_MP      3
#define SUPER_STRENGTH        4
#define SUPER_AGILITY         5
#define SUPER_INTELLECT       6
#define GLADIATOR             7
#define DEFENDER              8
#define MARKSMAN              9
#define NINJA                 10
#define MAGUS                 11
#define HEALER                12
#define DESTROYER             13
#define SPELL_RESISTANCE      14
#define SPELL_ABSORPTION      15
#define NUM_PERKS             16

// Scroll types:
#define MAIN_QUEST_SCROLL_1 0
#define MAIN_QUEST_SCROLL_2 1
#define MAIN_QUEST_SCROLL_3 2
#define RANDOM_QUEST_SCROLL 3
#define FAILURE_SCROLL      4
#define VICTORY_SCROLL      5
#define DEATH_SCROLL        6
#define NUM_SCROLL_TYPES    7

// Game modes:
#define ACTIVE_MODE          0
#define SCROLL_MODE          1
#define MAIN_MENU_MODE       2
#define INVENTORY_MODE       3
#define EQUIP_OPTIONS_MODE   4
#define PEBBLE_OPTIONS_MODE  5
#define PEBBLE_INFUSION_MODE 6
#define MARKET_MODE          7
#define BUYING_MODE          8
#define SELLING_MODE         9
#define LOOT_MODE            10
#define REPLACE_ITEM_MODE    11
#define SHOW_STATS_MODE      12
#define LEVEL_UP_MODE        13
#define NUM_GAME_MODES       14

// Directions:
#define NORTH          0
#define SOUTH          1
#define EAST           2
#define WEST           3
#define NUM_DIRECTIONS 4

/******************************************************************************
  Structures
******************************************************************************/

typedef struct Item {
  int16_t n, // "Type" for heavy items (0 == "none"), "quantity" for others.
          infused_pebbles[MAX_INFUSED_PEBBLES];
} __attribute__((__packed__)) item_t;

typedef struct NonPlayerCharacter {
  GPoint position;
  int16_t type,
          stats[NUM_CHARACTER_STATS],
          status_effects[NUM_STATUS_EFFECTS];
  struct NonPlayerCharacter *next;
} __attribute__((__packed__)) npc_t;

typedef struct PlayerCharacter {
  GPoint position;
  int16_t direction,
          stats[NUM_CHARACTER_STATS],
          status_effects[NUM_STATUS_EFFECTS],
          level,
          exp_points,
          num_quests_completed,
          num_pebbles_found,
          equipped_item_indices[NUM_EQUIP_TARGETS];
  item_t *inventory[PLAYER_INVENTORY_SIZE];
} __attribute__((__packed__)) player_t;

typedef struct Quest {
  int16_t type,
          reward,
          primary_npc_type,
          num_npcs,
          kills,
          cells[LOCATION_WIDTH][LOCATION_HEIGHT],
          entrance_direction,
          exit_direction;
  GPoint starting_point,
         ending_point;
  npc_t *npcs;
  bool completed;
} __attribute__((__packed__)) quest_t;

/******************************************************************************
  Global Variables
******************************************************************************/

Window *g_menu_window,
       *g_scroll_window,
       *g_graphics_window;
InverterLayer *g_inverter_layer;
ScrollLayer *g_scroll_scroll_layer;
MenuLayer *g_menu_layer;
TextLayer *g_scroll_text_layer;
AppTimer *g_player_timer,
         *g_flash_timer;
GPoint g_back_wall_coords[MAX_VISIBILITY_DEPTH - 1]
                         [(STRAIGHT_AHEAD * 2) + 1]
                         [2];
int16_t g_game_mode,
        g_current_scroll,
        g_player_animation_mode;
GPath *g_compass_path;
quest_t *g_quest;
player_t *g_player;

static const GPathInfo COMPASS_PATH_INFO = {
  .num_points = 4,
  .points = (GPoint []) {{-3, -3},
                         {3, -3},
                         {0, 6},
                         {-3, -3}}
};

/******************************************************************************
  Function Declarations
******************************************************************************/

void set_game_mode(const int16_t mode);
void set_player_direction(const int16_t new_direction);
void move_player(const int16_t direction);
void move_npc(npc_t *npc, const int16_t direction);
void determine_npc_behavior(npc_t *npc);
void damage_player(int16_t damage);
void damage_npc(npc_t *npc, const int16_t damage);
bool adjust_item_quantity(const int16_t item, const int16_t amount);
void adjust_player_current_hp(const int16_t amount);
void remove_npc(npc_t *npc);
void adjust_player_current_mp(const int16_t amount);
void end_quest(void);
void add_new_npc(const int16_t npc_type, const GPoint position);
int16_t get_random_npc_type(void);
GPoint get_npc_spawn_point(void);
GPoint get_floor_center_point(const int16_t depth, const int16_t position);
GPoint get_cell_farther_away(const GPoint reference_point,
                             const int16_t direction,
                             const int16_t distance);
int16_t get_pursuit_direction(const GPoint pursuer, const GPoint pursuee);
int16_t get_direction_to_the_left(const int16_t reference_direction);
int16_t get_direction_to_the_right(const int16_t reference_direction);
int16_t get_opposite_direction(const int16_t direction);
int16_t get_boosted_stat_value(const int16_t stat_index,
                               const int16_t boost_amount);
int16_t get_item_value(const int16_t item_type);
int16_t get_inventory_size(void);
int16_t get_heavy_inventory_size(void);
int16_t get_cell_type(const GPoint cell);
void set_cell_type(GPoint cell, const int16_t type);
npc_t *get_npc_at(const GPoint cell);
bool out_of_bounds(const GPoint cell);
bool occupiable(const GPoint cell);
bool touching(const GPoint cell, const GPoint cell_2);
void show_scroll(const int16_t scroll);
void show_window(Window *window, bool animated);
static void menu_draw_header_callback(GContext* ctx,
                                      const Layer *cell_layer,
                                      uint16_t section_index,
                                      void *data);
static void menu_draw_row_callback(GContext *ctx,
                                   const Layer *cell_layer,
                                   MenuIndex *cell_index,
                                   void *data);
void menu_select_callback(MenuLayer *menu_layer,
                          MenuIndex *cell_index,
                          void *data);
static int16_t menu_get_header_height_callback(MenuLayer *menu_layer,
                                               uint16_t section_index,
                                               void *data);
static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer,
                                           uint16_t section_index,
                                           void *data);
void draw_scene(Layer *layer, GContext *ctx);
void draw_player_action(GContext *ctx);
void draw_floor_and_ceiling(GContext *ctx);
void draw_cell_walls(GContext *ctx,
                     const GPoint cell,
                     const int16_t depth,
                     const int16_t position);
void draw_cell_contents(GContext *ctx,
                        const GPoint cell,
                        const int16_t depth,
                        const int16_t position);
void draw_shaded_quad(GContext *ctx,
                      const GPoint upper_left,
                      const GPoint lower_left,
                      const GPoint upper_right,
                      const GPoint lower_right,
                      const GPoint shading_ref);
void fill_quad(GContext *ctx,
               const GPoint upper_left,
               const GPoint lower_left,
               const GPoint upper_right,
               const GPoint lower_right,
               const GColor color);
void draw_status_bar(GContext *ctx);
void draw_status_meter(GContext *ctx,
                       const GPoint origin,
                       const float ratio);
void flash_screen(void);
static void flash_timer_callback(void *data);
static void player_timer_callback(void *data);
static void graphics_window_appear(Window *window);
static void graphics_window_disappear(Window *window);
void graphics_up_single_repeating_click(ClickRecognizerRef recognizer,
                                        void *context);
void graphics_up_multi_click(ClickRecognizerRef recognizer, void *context);
void graphics_down_single_repeating_click(ClickRecognizerRef recognizer,
                                          void *context);
void graphics_down_multi_click(ClickRecognizerRef recognizer, void *context);
void graphics_select_single_click(ClickRecognizerRef recognizer,
                                  void *context);
void graphics_click_config_provider(void *context);
void scroll_select_single_click(ClickRecognizerRef recognizer, void *context);
void scroll_click_config_provider(void *context);
void app_focus_handler(const bool in_focus);
void strcat_item_name(char *dest_str, const int16_t item);
void strcat_magic_type(char *dest_str, const int16_t magic_type);
void strcat_stat_name(char *dest_str, const int16_t stat);
void strcat_stat_value(char *dest_str, const int16_t stat);
void strcat_int(char *dest_str, int16_t integer);
void assign_minor_stats(int16_t *stats_array);
void add_item_to_inventory(const int16_t type);
void equip(const item_t *item, const int16_t equip_target);
void init_player(void);
void deinit_player(void);
void init_npc(npc_t *npc, const int16_t type, const GPoint position);
void init_item(item_t *item, const int16_t n);
void init_wall_coords(void);
void init_quest(const int16_t type);
void init_quest_location(void);
void deinit_quest(void);
void init_scroll(void);
void deinit_scroll(void);
void init_graphics(void);
void deinit_graphics(void);
void init_menu(void);
void deinit_menu(void);
void init(void);
void deinit(void);
int main(void);

#endif // PEBBLE_QUEST_H_
