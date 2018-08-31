#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "cbitset.h"

static int b_search(cBitSet *cset, int t_offset);

void bprint(int x) {
    int a;
    for (a = 7; a >= 0; a--) {
        printf("%d", !!((x << a) & 0x80));
    }
    printf("\n");
}

cBitSet *cbitset_create(int *data, unsigned int sz) {
    cBitSet *new = malloc(sizeof(cBitSet));
    new->sz = 0;
    new->set = NULL;
    
    int i;
    for (i = 0; i < sz; i++)
        cbitset_set(new, data[i]);
    
    return new;
}

void cbitset_destroy(cBitSet *t) {
    if (t->set != NULL)
        free(t->set);
    
    free(t);
}

BitChunk *cbitset_chunk(cBitSet *cset, int offset) {
    BitChunk *t_chunk;
    
    if (cset->set == NULL) {
        cset->set = malloc(sizeof(BitChunk));
        cset->sz++;
        
        t_chunk = cset->set;
    } else {
        int index = b_search(cset, offset);
        assert(index >= 0);
        
        if (index < cset->sz && cset->set[index].offset == offset)
            return &(cset->set[index]);
            
        cset->set = realloc(cset->set, (++(cset->sz)) * sizeof(BitChunk));
        
        int i;
        for (i = index + 1; i < cset->sz; i++)
            cset->set[i] = cset->set[i - 1];
        
        t_chunk = &(cset->set[index]);
    }
    
    t_chunk->offset = offset;
    memset(t_chunk->map, 0, __N);
    
    return t_chunk;
}

void cbitset_delchunk(cBitSet *cset, int offset) {
    if (cset->set == NULL)
        return;
    
    int index = b_search(cset, offset);
    assert(index >= 0);
    
    if (index >= cset->sz || cset->set[index].offset != offset)
        return;
    
    int i;
    for (i = index; i < cset->sz - 1; i++)
        cset->set[i] = cset->set[i + 1];
    
    cset->set = realloc(cset->set, (--(cset->sz)) * sizeof(BitChunk));
}

BitChunk *cbitset_getchunk(cBitSet *cset, int offset) {
    if (cset->set == NULL)
        return NULL;
    
    int index = b_search(cset, offset);
    assert(index >= 0);
    
    if (index < cset->sz && cset->set[index].offset == offset)
        return &(cset->set[index]);
        
    return NULL;
}

void cbitset_set(cBitSet *cset, int x) {
    int t_offset = CB_GETOFFSET(x);
    int t_bit = CB_GETBIT(x);
    BitChunk *t_chunk = cbitset_chunk(cset, t_offset);
    
    CB_CHUNK_SET(t_chunk, t_bit);
}

void cbitset_unset(cBitSet *cset, int x) {
    int t_offset = CB_GETOFFSET(x);
    int t_bit = CB_GETBIT(x);
    BitChunk *t_chunk = cbitset_getchunk(cset, t_offset);
    
    if (t_chunk == NULL)
        return;
     
    CB_CHUNK_UNSET(t_chunk, t_bit);
    if (CB_CHUNK_TESTZERO(t_chunk))
        cbitset_delchunk(cset, t_offset);
}

int cbitset_contains(cBitSet *cset, int x) {
    int t_offset = CB_GETOFFSET(x);
    int t_bit = CB_GETBIT(x);
    
    BitChunk *t_chunk = cbitset_getchunk(cset, t_offset);
    
    if (t_chunk == NULL)
        return 0;
    
    return CB_CHUNK_TEST(t_chunk, t_bit);
}

void cbitset_print(cBitSet *cset) {
    if (cset == NULL)
        return;
    
    printf("{ ");
    int i, j, k;
    for (i = 0; i < cset->sz; i++) {
        BitChunk *t_chunk = &(cset->set[i]);
        int offset_c = t_chunk->offset * __N*8;
        
        for (j = 0; j < __N; j++) {
            int offset_w = offset_c + j*8;
            char w = t_chunk->map[j];
            
            for (k = 0; k < 8; k++) {
                if (w & (1 << k)) {
                    int offset_b = offset_w + k;
                    printf("%d ", offset_b);
                }
            }
        }
    }
    printf("}\n");
}

// --------- Helper ---------

static int b_search( cBitSet *cset, int t_offset ) {
    int l = 0;
    int r = cset->sz - 1;
    BitChunk *arr = cset->set;

    int m;
    while( l <= r ) {
        m = l + (r-l)/2;

        if( arr[ m ].offset == t_offset )
            return m;
        else if( arr[ m ].offset > t_offset )
            r = m - 1;
        else
            l = m + 1;
    }
    return m + 1;

}