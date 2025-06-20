#include <stdio.h>
#include <stdlib.h>
#include "associative_array.h"

TREE avl_tree_init_default(void) {
    Associative_array* pTree = (Associative_array*)malloc(sizeof(Associative_array));
    if (pTree == NULL){
        printf("FAILED TO ALLOCATE TREE\n");
        return NULL;
    }
    pTree->root = NULL;
    return pTree;
}

Status avl_tree_push_back(TREE hMy_tree, MY_STRING key, MY_STRING item) {
    int val;
    if (hMy_tree == NULL) {
        return FAILURE;
    }

    Associative_array* pTree = (Associative_array*)hMy_tree;
    if (pTree->root == NULL) {
        pTree->root = (Node*)malloc(sizeof(Node));
        if(pTree->root == NULL) {
            return FAILURE;
        }
        pTree->root->left = NULL;
        pTree->root->right = NULL;
        pTree->root->key = my_string_init_c_string(my_string_c_str(key));
    
        pTree->root->data = generic_vector_init_default(my_string_init_copy, my_string_destroy);
        generic_vector_push_back(pTree->root->data, item);
    } 
    else {
        val = my_string_compare(pTree->root->key, key);

        if (val == 1) {
            pTree->root = insert_node(pTree->root, key, item);
        } 
        else if (val == 0) {
            generic_vector_push_back(pTree->root->data, item);
        } 
        else if (val == -1) {
            pTree->root = insert_node(pTree->root, key, item);
        } 
        else {
            return FAILURE ;
        }
    }
    return SUCCESS;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int get_balance(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node* insert_node(Node* root, MY_STRING key, MY_STRING item) {
    int cmp;
    if (root == NULL) {
        root = (Node*)malloc(sizeof(Node));
        if (root == NULL) return NULL;
        root->left = root->right = NULL;
        root->key = my_string_init_c_string(my_string_c_str(key));
        root->data = generic_vector_init_default(my_string_init_copy, my_string_destroy);
        generic_vector_push_back(root->data, item);
        root->height = 1;
        return root;
    }

    cmp = my_string_compare(key, root->key);
    if (cmp < 0) {
        root->left = insert_node(root->left, key, item);
    } else if (cmp > 0) {
        root->right = insert_node(root->right, key, item);
    } else {
        generic_vector_push_back(root->data, item);
        return root;
    }

    // Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // Get balance factor
    int balance = get_balance(root);

    // Balance the tree
    if (balance > 1 && root->left != NULL && my_string_compare(key, root->left->key) < 0) {
        return right_rotate(root);
    }

    if (balance < -1 && root->right != NULL && my_string_compare(key, root->right->key) > 0) {
        return left_rotate(root);
    }

    if (balance > 1 && root->left != NULL && my_string_compare(key, root->left->key) > 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && root->right != NULL && my_string_compare(key, root->right->key) < 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

Node* left_rotate(Node* y) {
    if (y == NULL || y->right == NULL) {
        return y; // No rotation possible
    }

    Node* x = y->right;
    Node* T2 = x->left;

    // Perform rotation
    x->left = y;
    y->right = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

Node* right_rotate(Node* y) {
    if (y == NULL) {
        printf("Error: Attempted right rotation on NULL node\n");
        return NULL;
    }
    if (y->left == NULL) {
        printf("Error: Attempted right rotation on node with NULL left child\n");
        return y;
    }

    Node* x = y->left;
    Node* T2 = x->right;
    

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

void print_avl_tree(Node* root) {
    if (root == NULL) {
        return;
    }
    
    // In-order traversal: left, root, right
    print_avl_tree(root->left);
    
    // Print the key and associated data
    printf("Word: ");
    my_string_insertion(root->key, stdout);
    printf("\nAssociated data:\n");
    for (int i = 0; i < generic_vector_get_size(root->data); i++) {
        MY_STRING word = generic_vector_at(root->data, i);
        my_string_insertion(word, stdout);
        printf("\n");
    }
    
    print_avl_tree(root->right);
}

void avl_tree_print_keys_and_word_counts(Node* root) {
    if (root == NULL) {
        return;
    }
    avl_tree_print_keys_and_word_counts(root->left);
    printf("%s %d\n", my_string_c_str(root->key), generic_vector_get_size(root->data));
    avl_tree_print_keys_and_word_counts(root->right);
}

MY_STRING avl_tree_get_random_word(TREE hMy_tree) {
    if (hMy_tree == NULL) {
        return NULL; 
    }

    Associative_array* pTree = (Associative_array*)hMy_tree;
    if (pTree->root == NULL) {
        return NULL; 
    }

    MY_STRING largest_family_key = avl_tree_get_largest_family_key(hMy_tree);
    if (largest_family_key == NULL) {
        return NULL; 
    }

    Node* current = pTree->root;
    while (current != NULL) {
        int cmp = my_string_compare(largest_family_key, current->key);
        if (cmp == 0) {
            break;
        } else if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL || current->data == NULL) {
        return NULL; 
    }

    int size = generic_vector_get_size(current->data);
    if (size == 0) {
        return NULL; 
    }

    int random_index = rand() % size;
    return (MY_STRING)generic_vector_at(current->data, random_index);
}

Node* avl_tree_find_node(TREE hMy_tree, MY_STRING key) {
    if (hMy_tree == NULL) {
        return NULL;
    }

    Associative_array* pTree = (Associative_array*)hMy_tree;
    Node* current = pTree->root;

    while (current != NULL) {
        int cmp = my_string_compare(key, current->key);
        if (cmp == 0) {
            return current; 
        } else if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL; 
}

void find_largest_family(Node* node, MY_STRING* largest_key, int* max_size) {
    if (node == NULL) {
        return;
    }

    int current_size = generic_vector_get_size(node->data);
    if (current_size > *max_size) {
        *max_size = current_size;
        *largest_key = node->key; 
    }

    find_largest_family(node->left, largest_key, max_size);
    find_largest_family(node->right, largest_key, max_size);
}

MY_STRING avl_tree_get_largest_family_key(TREE hMy_tree) {
    if (hMy_tree == NULL) {
        return NULL; 
    }

    Associative_array* pTree = (Associative_array*)hMy_tree;
    if (pTree->root == NULL) {
        return NULL; 
    }

    MY_STRING largest_key = NULL;
    int max_size = 0;

    find_largest_family(pTree->root, &largest_key, &max_size);

    return largest_key;
}

void avl_tree_destroy(TREE *phMy_tree) {
    if (phMy_tree == NULL || *phMy_tree == NULL) {
        return;
    }
    Associative_array* pTree = (Associative_array*)*phMy_tree;
    if (pTree != NULL && pTree->root != NULL) {
        avl_tree_destroy_node(pTree->root);
    }
    free(pTree);
    *phMy_tree = NULL;
}

void avl_tree_destroy_node(Node *pNode) {
    if (pNode == NULL){
        return;
    }
    if(pNode->key != NULL){
        my_string_destroy(&(pNode->key));
    }
    if(pNode->data != NULL){
        generic_vector_destroy(&(pNode->data));
    }
    
    avl_tree_destroy_node(pNode->left);
    avl_tree_destroy_node(pNode->right);
    free(pNode);
}

