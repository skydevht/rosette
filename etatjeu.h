#ifndef ETATJEU_H_INCLUDED
#define ETATJEU_H_INCLUDED

typedef struct ETATJEU
{
    int (*id)(void);
    void (*init)(void);
    void (*deinit)(void);
    int (*maj)(void);
    void (*afficher)(void);
} ETATJEU;

#endif // ETATJEU_H_INCLUDED
