#include "ops/gol.h"

#include "helpers.h"
#include "teletype.h"
#include "teletype_io.h"

static void op_GOL_GEN_get(const void* NOTUSED(data), scene_state_t* ss, exec_state_t* NOTUSED(es), command_state_t* NOTUSED(cs))
{
    gol_next_gen(ss);
    tele_gol_updated();
}

// Get
static int16_t gol_get(scene_state_t *ss, int16_t x, int16_t y) {
    //add limiter functions limit x y to 0-63/0-31
    return gol_isalive(ss_gol_grid_ptr(ss), x, y);
}

static void op_GOL_get(const void *NOTUSED(data), scene_state_t *ss,
                      exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);
    cs_push(cs, gol_get(ss, x, y));
}

// Set
static void gol_set(scene_state_t *ss, int16_t x, int16_t y, int16_t val) {
   //add limiter functions if needed x y 0-1 
    if (val == 0) {
    gol_flip_off(ss_gol_grid_ptr(ss), x, y);
    }
    else {
    gol_flip_on(ss_gol_grid_ptr(ss), x, y);
    }
    tele_gol_updated();
}

static void op_GOL_set(const void *NOTUSED(data), scene_state_t *ss,
                      exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);
    int16_t z = cs_pop(cs);
    gol_set(ss, x, y, z);
}

// Make ops
const tele_op_t op_GOL_GEN = MAKE_GET_OP(GOL.GEN, op_GOL_GEN_get, 0, false);
const tele_op_t op_GOL = MAKE_GET_SET_OP(GOL, op_GOL_get, op_GOL_set, 2, true);