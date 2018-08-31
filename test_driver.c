#include <stdio.h>
#include <assert.h>
#include "cbitset.h"

int main (int argc, char *argv[]) {
   
    assert(CB_GETOFFSET(0) == 0);
    assert(CB_GETOFFSET(31) == 0);
    assert(CB_GETOFFSET(32) == 1);
    assert(CB_GETOFFSET(63) == 1);
    assert(CB_GETOFFSET(1000) == 31);
    assert(CB_GETOFFSET(-1) == -1);
    assert(CB_GETOFFSET(-32) == -1);
    assert(CB_GETOFFSET(-63) == -2);
    assert(CB_GETOFFSET(-64) == -2);
    assert(CB_GETOFFSET(-65) == -3);
    assert(CB_GETOFFSET(-1000) == -32);
    
    assert(CB_GETBIT(0) == 0);
    assert(CB_GETBIT(31) == 31);
    assert(CB_GETBIT(32) == 0);
    assert(CB_GETBIT(63) == 31);
    assert(CB_GETBIT(1000) == 8);
    assert(CB_GETBIT(-1) == 31);
    assert(CB_GETBIT(-32) == 0);
    assert(CB_GETBIT(-63) == 1);
    assert(CB_GETBIT(-64) == 0);
    assert(CB_GETBIT(-65) == 31);
    assert(CB_GETBIT(-1000) == 24);
    
    assert(CB_CHUNK_GETWORD(0) == 0);
    assert(CB_CHUNK_GETWORD(1) == 0);
    assert(CB_CHUNK_GETWORD(2) == 0);
    assert(CB_CHUNK_GETWORD(3) == 0);
    assert(CB_CHUNK_GETWORD(4) == 0);
    assert(CB_CHUNK_GETWORD(5) == 0);
    assert(CB_CHUNK_GETWORD(6) == 0);
    assert(CB_CHUNK_GETWORD(7) == 0);
    assert(CB_CHUNK_GETWORD(8) == 1);
    assert(CB_CHUNK_GETWORD(9) == 1);
    assert(CB_CHUNK_GETWORD(10) == 1);
    assert(CB_CHUNK_GETWORD(11) == 1);
    assert(CB_CHUNK_GETWORD(12) == 1);
    assert(CB_CHUNK_GETWORD(13) == 1);
    assert(CB_CHUNK_GETWORD(14) == 1);
    assert(CB_CHUNK_GETWORD(15) == 1);
    assert(CB_CHUNK_GETWORD(16) == 2);
    assert(CB_CHUNK_GETWORD(17) == 2);
    assert(CB_CHUNK_GETWORD(18) == 2);
    assert(CB_CHUNK_GETWORD(19) == 2);
    assert(CB_CHUNK_GETWORD(20) == 2);
    assert(CB_CHUNK_GETWORD(21) == 2);
    assert(CB_CHUNK_GETWORD(22) == 2);
    assert(CB_CHUNK_GETWORD(23) == 2);
    assert(CB_CHUNK_GETWORD(24) == 3);
    assert(CB_CHUNK_GETWORD(25) == 3);
    assert(CB_CHUNK_GETWORD(26) == 3);
    assert(CB_CHUNK_GETWORD(27) == 3);
    assert(CB_CHUNK_GETWORD(28) == 3);
    assert(CB_CHUNK_GETWORD(29) == 3);
    assert(CB_CHUNK_GETWORD(30) == 3);
    assert(CB_CHUNK_GETWORD(31) == 3);
    
    assert(CB_CHUNK_GETBITMASK(0) == 0b00000001);
    assert(CB_CHUNK_GETBITMASK(1) == 0b00000010);
    assert(CB_CHUNK_GETBITMASK(2) == 0b00000100);
    assert(CB_CHUNK_GETBITMASK(3) == 0b00001000);
    assert(CB_CHUNK_GETBITMASK(4) == 0b00010000);
    assert(CB_CHUNK_GETBITMASK(5) == 0b00100000);
    assert(CB_CHUNK_GETBITMASK(6) == 0b01000000);
    assert(CB_CHUNK_GETBITMASK(7) == 0b10000000);
    assert(CB_CHUNK_GETBITMASK(8) == 0b00000001);
    assert(CB_CHUNK_GETBITMASK(9) == 0b00000010);
    assert(CB_CHUNK_GETBITMASK(10) == 0b00000100);
    assert(CB_CHUNK_GETBITMASK(11) == 0b00001000);
    assert(CB_CHUNK_GETBITMASK(12) == 0b00010000);
    assert(CB_CHUNK_GETBITMASK(13) == 0b00100000);
    assert(CB_CHUNK_GETBITMASK(14) == 0b01000000);
    assert(CB_CHUNK_GETBITMASK(15) == 0b10000000);
    assert(CB_CHUNK_GETBITMASK(16) == 0b00000001);
    assert(CB_CHUNK_GETBITMASK(17) == 0b00000010);
    assert(CB_CHUNK_GETBITMASK(18) == 0b00000100);
    assert(CB_CHUNK_GETBITMASK(19) == 0b00001000);
    assert(CB_CHUNK_GETBITMASK(20) == 0b00010000);
    assert(CB_CHUNK_GETBITMASK(21) == 0b00100000);
    assert(CB_CHUNK_GETBITMASK(22) == 0b01000000);
    assert(CB_CHUNK_GETBITMASK(23) == 0b10000000);
    assert(CB_CHUNK_GETBITMASK(24) == 0b00000001);
    assert(CB_CHUNK_GETBITMASK(25) == 0b00000010);
    assert(CB_CHUNK_GETBITMASK(26) == 0b00000100);
    assert(CB_CHUNK_GETBITMASK(27) == 0b00001000);
    assert(CB_CHUNK_GETBITMASK(28) == 0b00010000);
    assert(CB_CHUNK_GETBITMASK(29) == 0b00100000);
    assert(CB_CHUNK_GETBITMASK(30) == 0b01000000);
    assert(CB_CHUNK_GETBITMASK(31) == 0b10000000);
    
    int t1_nums[] = {0, 1, 2, 40, 32, 9, 1000, 63};
    cBitSet *t1 = cbitset_create(t1_nums, 8);
    cbitset_print(t1);
    
    assert(cbitset_contains(t1, 0) == 1);
    assert(cbitset_contains(t1, 1) == 1);
    assert(cbitset_contains(t1, 2) == 1);
    assert(cbitset_contains(t1, 3) == 0);
    assert(cbitset_contains(t1, 8) == 0);
    assert(cbitset_contains(t1, 9) == 1);
    assert(cbitset_contains(t1, 32) == 1);
    assert(cbitset_contains(t1, 39) == 0);
    assert(cbitset_contains(t1, 40) == 1);
    assert(cbitset_contains(t1, 256) == 0);
    assert(cbitset_contains(t1, 63) == 1);
    assert(cbitset_contains(t1, 1000) == 1);
    
    assert(cbitset_cardinality(t1) == 8);
    
    cbitset_unset(t1, 0);
    cbitset_unset(t1, 1);
    cbitset_unset(t1, 1000);
    cbitset_unset(t1, 63);
    
    assert(cbitset_contains(t1, 0) == 0);
    assert(cbitset_contains(t1, 1) == 0);
    assert(cbitset_contains(t1, 2) == 1);
    assert(cbitset_contains(t1, 3) == 0);
    assert(cbitset_contains(t1, 8) == 0);
    assert(cbitset_contains(t1, 9) == 1);
    assert(cbitset_contains(t1, 32) == 1);
    assert(cbitset_contains(t1, 39) == 0);
    assert(cbitset_contains(t1, 40) == 1);
    assert(cbitset_contains(t1, 256) == 0);
    assert(cbitset_contains(t1, 63) == 0);
    assert(cbitset_contains(t1, 1000) == 0);
    
    assert(cbitset_cardinality(t1) == 4);
    
    cbitset_unset(t1, 32);
    cbitset_unset(t1, 40);
    
    assert(cbitset_contains(t1, 0) == 0);
    assert(cbitset_contains(t1, 1) == 0);
    assert(cbitset_contains(t1, 2) == 1);
    assert(cbitset_contains(t1, 3) == 0);
    assert(cbitset_contains(t1, 8) == 0);
    assert(cbitset_contains(t1, 9) == 1);
    assert(cbitset_contains(t1, 32) == 0);
    assert(cbitset_contains(t1, 39) == 0);
    assert(cbitset_contains(t1, 40) == 0);
    assert(cbitset_contains(t1, 256) == 0);
    assert(cbitset_contains(t1, 63) == 0);
    assert(cbitset_contains(t1, 1000) == 0);
    
    assert(cbitset_cardinality(t1) == 2);
    
    cbitset_destroy(t1);
    
    int t2_nums[] = { -1000, -240, -256, -64, -33, -1, 25, 1000 };
    cBitSet *t2 = cbitset_create(t2_nums, 8);
    cbitset_print(t2);
    
    assert(cbitset_contains(t1, 0) == 0);
    assert(cbitset_contains(t2, -1000) == 1);
    assert(cbitset_contains(t2, -240) == 1);
    assert(cbitset_contains(t2, -256) == 1);
    assert(cbitset_contains(t2, -64) == 1);
    assert(cbitset_contains(t2, -33) == 1);
    assert(cbitset_contains(t2, -1) == 1);
    assert(cbitset_contains(t2, 25) == 1);
    assert(cbitset_contains(t2, 1000) == 1);
    assert(cbitset_contains(t2, -220) == 0);
    assert(cbitset_contains(t2, -2500) == 0);
    assert(cbitset_contains(t2, -32) == 0);
    
    assert(cbitset_cardinality(t1) == 8);
    
    cbitset_destroy(t2);
    
    return 0;
}