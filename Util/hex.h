#ifndef HEX_H_INCLUDED
#define HEX_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef enum
{
    L = 0,
    R = 1
} Side;

typedef enum
{
    W =0,
    N = 1,
    E = 2
} Direction;

typedef struct {
    int q, r, s;
} Hex;

typedef struct
{
    float x, y;
} Point;

typedef struct
{
    int q, r;
    Side side;
} Vertex;

typedef struct
{
    int q, r;
    Direction dir;
} Edge;

/** \brief
 *
 * \param q int
 * \param r int
 * \param s int
 * \return Hex*
 *
 */


int hex_creer_nouveau(int q, int r, int s);

/** \brief vrai si a est equivalent a b
 *
 * \param a Hex*
 * \param b Hex*
 * \return bool
 *
 */
int hex_equivalent(Hex *a, Hex *b);

int pixel_to_hex(Point *in_point, Hex *out_hex, int size);
int hex_to_pixel(Hex *in_hex, Point *out_point, int size);
void hex_hex_neighbours(Hex *in_hex, Hex * out_hexes);

int hex_corners(Hex *hex, Vertex *vertices);
int adjacent_vertices(Vertex *vert, Vertex *vertices);
int vertex_touches(Vertex *vert, Hex *hexes);

int vertex_to_pixel(Vertex *vert, Point *out_pt, int hex_size);

int distance_point(Point *a, Point *b);


#endif // HEX_H_INCLUDED
