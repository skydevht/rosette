#include <math.h>
#include "hex.h"


int hex_creer_nouveau(int q, int r, int s) {
    assert(q + r + s == 0);
    Hex hex = {q, r, s};
    return 1;
}

int hex_equivalent(Hex *a, Hex *b) {
    return (a->q == b->q && a->r == b->r && a->s == a->s);
}


int hex_to_pixel(Hex *in_hex, Point *out_point, int size) {
    if (size) {
        out_point->x = size * 3.0 / 2 * in_hex->q;
        out_point->y = size * sqrt(3.0) * (in_hex->r + in_hex->q / 2.0);
        return 1;
    }
    return 0;
}

int pixel_to_hex(Point *in_point, Hex *out_hex, int size) {
    if (size) {
        float q = (in_point->x * 2 / 3.0) / size;
        float r = ((-1) * in_point->x / 3.0 + (sqrt(3.0) / 3) * in_point->y) / size;
        out_hex->q = round(q);
        out_hex->r = round(r);
        out_hex->s = round(0 - (q + r));
        float dx = fabs(out_hex->q - q);
        float dy = fabs(out_hex->r - r);
        float dz = fabs(out_hex->s + q + r);
        if (dx > dy && dx > dz) {
            out_hex->q = 0 - out_hex->s - out_hex->r;
        }
        else if (dy > dz) {
            out_hex->r = 0 - out_hex->s - out_hex->q;
        }
        else {
            out_hex->s = 0 - out_hex->q - out_hex->r;
        }
        return 1;
    }
    return 0;
}

void hex_print(Hex *hex) {
    printf("Les coord. cubiques de l'Hexagone sont : q = %d, r = %d, s = %d\n", hex->q, hex->r, -(hex->q + hex->r));
    Point px;
    hex_to_pixel(hex, &px, 10);
    printf("Le centre de l'hexagone est au point : (%d, %d)\n", px.x, px.y);
}

void hex_hex_neighbours(Hex *in_hex, Hex out_hexes[]) {
    int i, j;
    int k = 0;
    for (i = -1; i < 2; i++) {
        for (j = -1; j < 2; j++) {
            if (i != j) {
                Hex h = {in_hex->q + i, in_hex->r + j};
                out_hexes[k] = h;
                k++;
            }
        }
    }
}

int hex_corners(Hex *hex, Vertex *vertices) {
    if (hex) {
        int i, dq, dr;
        Side s;
        for (i = 0; i < 6; i++) {
            s = (i % 2 == 0) ? L : R;
            switch (i) {
                case 0:
                    dq = dr = 0;
                    break;
                case 1:
                    dq = -1;
                    dr = 0;
                    break;
                case 2:
                    dq = 1;
                    dr = -1;
                    break;
                case 3:
                    dq = dr = 0;
                    break;
                case 4:
                    dq = 1;
                    dr = 0;
                    break;
                case 5:
                    dq = -1, dr = 1;
                    break;
            }
            vertices[i].q = hex->q + dq;
            vertices[i].r = hex->r + dr;
            vertices[i].side = s;
        }
        return 1;
    }
    return 0;
}

int adjacent_vertices(Vertex *vert, Vertex *vertices) {
    if (vert) {
        int i, dq, dr;
        Side s = (vert->side == L) ? R : L;
        for (i = 0; i < 3; i++) {
            switch (i) {
                case 0:
                    dq = (s == L) ? 2 : -1;
                    dr = (s == L) ? -1 : 1;
                    break;
                case 1:
                    dq = (s == L) ? 1 : -1;
                    dr = (s == L) ? -1 : 0;
                    break;
                case 2:
                    dq = (s == L) ? 1 : -2;
                    dr = (s == L) ? 0 : 1;
                    break;
            }
            vertices[i].q = vert->q + dq;
            vertices[i].r = vert->r + dr;
            vertices[i].side = s;
        }
        return 1;
    }
    return 0;
}

int vertex_touches(Vertex *vert, Hex *hexes) {
    if (vert) {
        int i, dq, dr;
        Side s = vert->side;
        for (i = 0; i < 3; i++) {
            switch (i) {
                case 0:
                    dq = 0;
                    dr = 0;
                    break;
                case 1:
                    dq = (s == L) ? -1 : 1;
                    dr = (s == L) ? 1 : 0;
                    break;
                case 2:
                    dq = (s == L) ? -1 : 1;
                    dr = (s == L) ? 0 : -1;
                    break;
            }
            hexes[i].q = vert->q + dq;
            hexes[i].r = vert->r + dr;
            hexes[i].s = -(hexes[i].q + hexes[i].r);
        }
        return 1;
    }
    return 0;
}

int vertex_to_pixel(Vertex *vert, Point *point, int hex_size) {
    if (vert && hex_size && point) {
        int add = 1;
        if (vert->side == L) add = -add;
        Point pt;
        Hex hex = {vert->q, vert->r, -(vert->q + vert->r)};
        hex_to_pixel(&hex, &pt, hex_size);
        point->x = pt.x + add * hex_size;
        point->y = pt.y;
        return 1;
    }
    return 0;
}

int distance_point(Point *a, Point *b) {
    int sqdx = a->x - b->x;
    sqdx *= sqdx;
    int sqdy = a->y - b->y;
    sqdy *= sqdy;
    return (int) sqrt(sqdx + sqdy);
}


