#include "ops/gol.h"

#include "helpers.h"
#include "teletype.h"
#include "teletype_io.h"

static void op_GOL_GEN_get(const void* NOTUSED(data), scene_state_t* ss, exec_state_t* NOTUSED(es), command_state_t* NOTUSED(cs))
{
    gol_next_gen(ss);
    tele_gol_updated();
}


//GOL X, Y, 0-1
// Get
static int16_t gol_get(scene_state_t *ss, int16_t x, int16_t y) {
    //need add limiter functions limit x y to 0-63/0-31?
    return gol_cell_isalive(ss_gol_grid_ptr(ss), x, y);
}

static void op_GOL_get(const void *NOTUSED(data), scene_state_t *ss,
                      exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);
    cs_push(cs, gol_get(ss, x, y));
}

// Set
static void gol_set(scene_state_t *ss, int16_t x, int16_t y, int16_t val) {
   //add limiter functions if needed x y 0-1?
    if (val == 0) {
    gol_cell_off(ss_gol_grid_ptr(ss), x, y);
    }
    else {
    gol_cell_on(ss_gol_grid_ptr(ss), x, y);
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

//GOL.TR X, Y, 0-8
// Get
static void op_GOL_TR_get(const void *NOTUSED(data), scene_state_t *ss,
                      exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);
    cs_push(cs, gol_get_tr(ss, x, y));
}

// Set
static void op_GOL_TR_set(const void *NOTUSED(data), scene_state_t *ss,
                      exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);
    int16_t z = cs_pop(cs);
    gol_cell_tr(ss, x, y, z);

    tele_gol_updated();
}


//GOL TRIGGER CLEAR
static void op_GOL_TRCLR_get(const void* NOTUSED(data), scene_state_t* ss, exec_state_t* NOTUSED(es), command_state_t* NOTUSED(cs))
{
    for (size_t i = 0; i < GOL_X; i++)
    {
        for (size_t j = 0; j < GOL_Y; j++)
        {
            gol_cell_tr(ss,i,j,0);
        }
        
    }
    
    tele_gol_updated();
}
//GOL CELL CLEAR
static void op_GOL_CLR_get(const void* NOTUSED(data), scene_state_t* ss, exec_state_t* NOTUSED(es), command_state_t* NOTUSED(cs))
{
    for (size_t i = 0; i < GOL_X; i++)
    {
        for (size_t j = 0; j < GOL_Y; j++)
        {
            gol_set(ss,i,j,0);
        }
        
    }
    
    tele_gol_updated();
}


// Make ops
const tele_op_t op_GOL = MAKE_GET_SET_OP(GOL, op_GOL_get, op_GOL_set, 2, true);
const tele_op_t op_GOL_TR = MAKE_GET_SET_OP(GOL.TR, op_GOL_TR_get, op_GOL_TR_set, 2, true);
const tele_op_t op_GOL_GEN = MAKE_GET_OP(GOL.GEN, op_GOL_GEN_get, 0, false);
const tele_op_t op_GOL_TRCLR = MAKE_GET_OP(GOL.TRCLR, op_GOL_TRCLR_get, 0, false);
const tele_op_t op_GOL_CLR = MAKE_GET_OP(GOL.CLR, op_GOL_CLR_get, 0, false);
