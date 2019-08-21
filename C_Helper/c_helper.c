#include <stdlib.h>
#include <stdio.h>
#include "c_helper.h"

void error(char *msg)
{
    perror(msg);
    exit(1);
}
