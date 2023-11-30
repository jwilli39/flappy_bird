// flappyBird.h

/* a sprite is a moveable image on the screen */
struct Sprite
{
    unsigned short attribute0;
    unsigned short attribute1;
    unsigned short attribute2;
    unsigned short attribute3;
};

/* the different sizes of sprites which are possible */
enum SpriteSize
{
    SIZE_8_8,
    SIZE_16_16,
    SIZE_32_32,
    SIZE_64_64,
    SIZE_16_8,
    SIZE_32_8,
    SIZE_32_16,
    SIZE_64_32,
    SIZE_8_16,
    SIZE_8_32,
    SIZE_16_32,
    SIZE_32_64
};

/* a struct for the koopa's logic and behavior */
struct Koopa
{
    /* the actual sprite attribute info */
    struct Sprite *sprite;

    /* the x and y postion in pixels */
    int x, y;

    /* the koopa's y velocity in 1/256 pixels/second */
    int yvel;

    /* the koopa's y acceleration in 1/256 pixels/second^2 */
    int gravity;

    /* which frame of the animation he is on */
    int frame;

    /* the number of frames to wait before flipping */
    int animation_delay;

    /* the animation counter counts how many frames until we flip */
    int counter;

    /* whether the koopa is moving right now or not */
    int move;

    /* the number of pixels away from the edge of the screen the koopa stays */
    int border;

    /* if the koopa is currently falling */
    int falling;
};

/* this function checks whether a particular button has been pressed */
unsigned char button_pressed(unsigned short button);

/* return a pointer to one of the 4 character blocks (0-3) */
volatile unsigned short *char_block(unsigned long block);

/* return a pointer to one of the 32 screen blocks (0-31) */
volatile unsigned short *screen_block(unsigned long block);

/* copy data using DMA */
void memcpy16_dma(unsigned short *dest, unsigned short *source, int amount);

/* function to setup background 0 for this program */
void setup_background();

/* function to setup background 0 for this program */
void setup_background0();

// clear the background
void clear_background();

/* function to set text on the screen at a given location */
void set_text(char *str, int row, int col);

/* just kill time */
void delay(unsigned int amount);

/* function to initialize a sprite with its properties, and return a pointer */
struct Sprite *sprite_init(int x, int y, enum SpriteSize size,
                           int horizontal_flip, int vertical_flip, int tile_index, int priority);

/* update all of the spries on the screen */
void sprite_update_all();

/* setup all sprites */
void sprite_clear();

/* set a sprite postion */
void sprite_position(struct Sprite *sprite, int x, int y);

/* move a sprite in a direction */
void sprite_move(struct Sprite *sprite, int dx, int dy);

/* change the vertical flip flag */
void sprite_set_vertical_flip(struct Sprite *sprite, int vertical_flip);

/* change the vertical flip flag */
void sprite_set_horizontal_flip(struct Sprite *sprite, int horizontal_flip);

/* change the tile offset of a sprite */
void sprite_set_offset(struct Sprite *sprite, int offset);

/* setup the sprite image and palette */
void setup_sprite_image();

/* move the koopa left or right returns if it is at edge of the screen */
int koopa_left(struct Koopa *koopa);

int koopa_right(struct Koopa *koopa);

/* stop the koopa from walking left/right */
void koopa_stop(struct Koopa *koopa);

/* start the koopa jumping, unless already fgalling */
void koopa_jump(struct Koopa *koopa);

/* finds which tile a screen coordinate maps to, taking scroll into account */
unsigned short tile_lookup(int x, int y, int xscroll, int yscroll,
                           const unsigned short *tilemap, int tilemap_w, int tilemap_h);

/* update the koopa */
void koopa_update(struct Koopa *koopa, int xscroll);

/* initialize the koopa */
void koopa_init(struct Koopa *koopa);

/* check collision */
int check_collision_top(struct Koopa *koopa, int xscroll);

/* declaration of the score function */
int increment_speed(int score);

/* declaration of the score function */
int countDown(int n, int r1, int r2, int r3);
