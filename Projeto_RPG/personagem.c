#include <string.h>
#include "personagem.h"


void copiar_personagem(Personagem *dst, const Personagem *src) {
memcpy(dst, src, sizeof(Personagem));
}