#include "dict.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// to store a new node
#define n 26
struct Trie {
    struct Trie* child[n];
    int leaf;
};

struct Trie* create() {
    // allocating enough space for each node
    struct Trie* node = malloc(sizeof(struct Trie));
    // for loop needed to go and create all nodes
    for (int i = 0; i < n; i++) {
        // setting the nodes to null to indicate that they have no chidren
        node->child[i] = NULL;
    }
    node->leaf = 0;

    return node;
}

void insert(Trie* dict, char* str) {
    // if we dont have a tree/node wee create one
    if (dict == NULL) {
        dict = create();
    }
    int stringlength = strlen(str);
    // taking the length of the string since we need it for the for loop

    Trie* current = dict;
    // setting a temporary node because we have to go through all of them

    for (int j = 0; j < stringlength; j++) {
        if (current->child[str[j] - 'a'] == NULL) {
            current->child[str[j] - 'a'] = create();
        }
        current = current->child[str[j] - 'a'];
    }
}

bool lookup(Trie* dict, char* str) {
    int stringlength =
        strlen(str);  // get the length of the string needed for the for loop
    Trie* current = dict;  // set dict to current as a temporary node since the
                           // index is going to change everytime
    for (int i = 0; i < stringlength; i++) {
        // if the node has no children then return false
        if (current->child[str[i] - 'a'] == NULL) {
            return false;
        }
        // insert the value in the node
        current = current->child[str[i] - 'a'];
    }
    return true;
}

void destroy(Trie* dict) {
    for (int i = 0; i < n; i++) {
        if (dict->child[i] != NULL) {
            destroy(dict->child[i]);
        }
    }
    free(dict);
}
