#ifndef AVL_H
#define AVL_H
#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"

typedef void *TREE;

typedef struct node Node;

typedef struct node {
    Node* parent;
    Node* left;
    Node* right;
    int height;
    MY_STRING key;
    GENERIC_VECTOR data;
} Node;

typedef struct associative_array Associative_array;

typedef struct associative_array {
    Node* root;
} Associative_array;

TREE avl_tree_init_default(void);

int max(int a, int b);

int height(Node* node);

int get_balance(Node* node);

void avl_tree_print_keys_and_word_counts(Node* root);

Node* avl_tree_find_node(TREE hMy_tree, MY_STRING key);

MY_STRING avl_tree_get_random_word(TREE hMy_tree);

void find_largest_family(Node* node, MY_STRING* largest_key, int* max_size);

MY_STRING avl_tree_get_largest_family_key(TREE hMy_tree);

Node* insert_node(Node* root, MY_STRING key, MY_STRING item);

Node* left_rotate(Node* y);

Node* right_rotate(Node* y);

void print_avl_tree(Node* root);

Status avl_tree_push_back(TREE hMy_tree, MY_STRING key, MY_STRING item);

void avl_tree_destroy(TREE *phMy_tree);

void avl_tree_destroy_node(Node *pNode);
#endif