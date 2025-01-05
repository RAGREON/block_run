#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE get_bytes_mb(5 * 1024)

long long int get_bytes_kb(int kb) {
    return kb * 1024;
}

long long int get_bytes_mb(int mb) {
    return get_bytes_kb(mb * 1024);
}

long long int get_bytes_gb(int gb) {
    return get_bytes_mb(gb * 1024);
}

typedef struct mem_block {
    char*               memory_block;
    struct mem_block*   next_block;
} mem_block;

void write_to_file(const char* file, const char* string) {
    FILE* w_file = fopen(file, "a");
    
    fputs(string, w_file);
}

mem_block* create_memblock(size_t size) {
    mem_block* block = (mem_block*)malloc(sizeof(mem_block));
    block->memory_block = (char*)calloc(size, sizeof(char));

    for (int i = 0; i < size - 1; i++)
        block->memory_block[i] = '-';

    block->memory_block[size - 1] = '\0';

    write_to_file("./result.txt", block->memory_block);

    return block;
}

void create_chain_block(mem_block* block) {
    while (1) {
        block->next_block = create_memblock(BLOCK_SIZE);
        block = block->next_block;
    }
}

int main(int argc, char** argv) {

    long long int mb_bytes = get_bytes_mb(1024);
    
    mem_block* block = create_memblock(mb_bytes);
    long long block_size = sizeof(block->memory_block);

    printf("2 gb to bytes: %lli\nblock size: %lli", mb_bytes, block_size);

    create_chain_block(block);

    getchar();

    return 0;
}