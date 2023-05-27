#include <stdlib.h>
#include <string.h>
#include "openssl/crypto.h" //genRandLong()
#include "projeto.h"

BlocoNaoMinerado * inicializaGenesis() {
    BlocoNaoMinerado *novo = malloc(sizeof(BlocoNaoMinerado));
    if (!novo) return NULL;

    novo->numero = 1;
    novo->nonce = 0;
    
    // Primeiro enchemos o vetor data de 0s, depois inserimos a string inicial
    memset(novo->data, 0, sizeof(novo->data));
    memcpy(novo->data, STRING_INICIAL, strlen(STRING_INICIAL));

    return novo;
}

BlocoMinerado * mineraGenesis(BlocoNaoMinerado *gen, MTRand *r) {
    if (!gen) return NULL;
    gen->data[183] = genRandLong(r) % 256; // escolhe o minerador.
    
    BlocoMinerado *novo = malloc(sizeof(BlocoMinerado));
    if (!novo) return NULL;

    while (1) { // loop ate achar o nonce que da um hash valido
        SHA256((unsigned char *) gen, sizeof(gen), novo->hash);
        if (novo->hash[0] == 0) break; // hash valido
        gen->nonce++;
    }

    novo->bloco = *gen;
    novo->prox = NULL;
    return novo;
}
