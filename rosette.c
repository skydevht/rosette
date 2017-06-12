#include "fw.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void) argv;

    if(init_fw() != ROSETTE_OK)
        return 1;

    lancer_fw();
    arreter_fw();

    return 0;
}
