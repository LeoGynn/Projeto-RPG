#include <stdlib.h>
#include <string.h>
#include "utils.h"


int ler_dado(const char *s) {
if (!s) return 0;
const char *p = s;
if (*p == 'd' || *p == 'D') p++;
int valor = atoi(p);
switch (valor) {
case 4: case 6: case 8: case 10: case 12: case 20:
return valor;
default: return 0;
}
}


int rolar_dado(int max) {
if (max <= 1) return 1;
return (rand() % max) + 1;
}