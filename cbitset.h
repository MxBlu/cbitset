#ifndef CBITSET_H
#define CBITSET_H

#define __K 2
#define __N (1 << __K)

#define CB_GETOFFSET(x) ( x >> (__K + 3) )
#define CB_GETBIT(x) ( x & ((1 << (__K + 3)) - 1) )
#define CB_CHUNK_GETWORD(x) ( x >> 3 )
#define CB_CHUNK_GETBITMASK(x) ( 1 << (x & 7) )

#define CB_CHUNK_SET(chunk, x) ( chunk->map[CB_CHUNK_GETWORD(x)] |= CB_CHUNK_GETBITMASK(x) )
#define CB_CHUNK_UNSET(chunk, x) ( chunk->map[CB_CHUNK_GETWORD(x)] &= ~(CB_CHUNK_GETBITMASK(x)) )

#define CB_CHUNK_TEST(chunk, x) ( (chunk->map[CB_CHUNK_GETWORD(x)] & CB_CHUNK_GETBITMASK(x)) != 0 )
#define CB_CHUNK_TESTZERO(chunk) ( !chunk->map[0] && !chunk->map[1] && !chunk->map[2] && !chunk->map[3] )
#define CB_CHUNK_ISSUBSET(chunk1, chunk2) ( (chunk1 - (chunk1 & chunk2)) == 0 )

typedef struct _bitChunk {
    int offset;
    char map[__N];
} BitChunk;


typedef struct _cBitSet{
    unsigned int sz;
    BitChunk *set;
} cBitSet;

cBitSet *cbitset_create(int *data, unsigned int sz);
void cbitset_destroy(cBitSet *t);

// Manipulation operations
void cbitset_set(cBitSet *cset, int x);
void cbitset_unset(cBitSet *cset, int x);

// View operations
int cbitset_contains(cBitSet *cset, int x);
int cbitset_cardinality(cBitSet *cset);
void cbitset_print(cBitSet *cset);

// Set operations
int cbitset_issubset(cBitSet *x, cBitSet *y);

#endif // CBITSET_H