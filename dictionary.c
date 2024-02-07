#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define HASHMAP_SIZE 64
#define HASHMAP_SIZE_LIST 1

struct aiv_dictionary_item
{
    const char *key;
    const char *value;
    size_t key_len;
};

struct aiv_dictionary
{
    struct aiv_dictionary_item hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST];
};

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

void aiv_dictionary_insert(struct aiv_dictionary *dictionary, const char *key,const char *value)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (dictionary->hashmap[index][i].key_len == 0)
        {
            dictionary->hashmap[index][i].key = key;
            dictionary->hashmap[index][i].value = value;
            dictionary->hashmap[index][i].key_len = key_len;
            printf("added %s at index %llu slot %llu\n", key, index, i);
            return;
        }
    }

    printf("COLLISION! for %s with value %s (index %llu)\n", key, value, index);
}

int main(int argc, char **argv)
{
    struct aiv_dictionary myset;
    
    aiv_dictionary_insert(&myset,"Prova","Provissima");

    return 0;
}
