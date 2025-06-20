#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "generic_vector.h"
#include "associative_array.h"

void read_dictionary(GENERIC_VECTOR vector_array_words[]);
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);
void driver(void);
GENERIC_VECTOR *initialize_dic_vector(void);
Boolean continue_game(void);
Boolean running_total(void);
char get_guess(void);
int number_of_guesses(void);
int get_word_length(void);
void clear_keyboard_buffer(void);


int main(int argc, char* argv[]){
    
    GENERIC_VECTOR *beginning_dic = initialize_dic_vector();
    for(int i = 0; i < 30; i++) {
        printf("There are %d words of length %d\n", generic_vector_get_size(beginning_dic[i]), i);
    }
    for (int i = 0; i < 30; i++) {
        generic_vector_destroy(&beginning_dic[i]);
    }
    free(beginning_dic);

	do {
		driver();
	} while(continue_game() == TRUE);
	return 0;
    
}




void driver(void) {
    GENERIC_VECTOR *dictionary = initialize_dic_vector();
    TREE associative_array = avl_tree_init_default();
    MY_STRING word_key = my_string_init_default();
    MY_STRING guess_list = my_string_init_c_string(" ");
    MY_STRING word_family = my_string_init_default();
    int word_length = 0;
    int guess_number = 0;
    int i = 0;
    Boolean running_status;
    char guess;

    // Get user inputs for word length and number of guesses
    word_length = get_word_length();
    guess_number = number_of_guesses();
    running_status = running_total();

    // Initialize the word key with dashes
    for (i = 0; i < word_length; i++) {
        my_string_push_back(word_key, '-');
    }
    for (int i = 0; i < word_length; i++) {
        my_string_push_back(word_family, '-');
    }

    do {
        printf("You have %d guesses left\nLetters used:", guess_number);
        my_string_insertion(guess_list, stdout);
        printf("\nWord: ");
        my_string_insertion(word_key, stdout);
        printf("\n");

        do {
            guess = get_guess();
        } while (is_used(guess_list, guess) == TRUE);

        my_string_push_back(guess_list, guess);
        my_string_push_back(guess_list, ' ');

        avl_tree_destroy(&associative_array);
        associative_array = avl_tree_init_default();


        for (i = 0; i < generic_vector_get_size(dictionary[word_length]); i++) {
            MY_STRING word = (MY_STRING)generic_vector_at(dictionary[word_length], i);
            if (word == NULL) {
                printf("Error: NULL word found at index %d in dictionary[%d]\n", i, word_length);
                continue;
            }

            if (get_word_key_value(word_family, word_key, word, guess) == FAILURE) {
                printf("Error: get_word_key_value failed for word at index %d\n", i);
                continue;
            }

            if (avl_tree_push_back(associative_array, word_family, word) == FAILURE) {
                printf("Error: Failed to push to AVL tree\n");
                continue;
            }
        }

        MY_STRING largest_family_key = avl_tree_get_largest_family_key(associative_array);
        if (largest_family_key == NULL) {
            printf("Error: No largest family key found\n");
            break;
        }
        // Update the word list to only include words from the largest family
        Node* largest_family_node = avl_tree_find_node(associative_array, largest_family_key);
        if (largest_family_node == NULL) {
            printf("Error: Could not find the largest family node.\n");
            break;
        }

        // Clear the current word list and replace it with the largest family
        generic_vector_destroy(&dictionary[word_length]);
        dictionary[word_length] = generic_vector_init_default(my_string_init_copy, my_string_destroy);

        for (int i = 0; i < generic_vector_get_size(largest_family_node->data); i++) {
            MY_STRING word = (MY_STRING)generic_vector_at(largest_family_node->data, i);
            generic_vector_push_back(dictionary[word_length], word);
        }
    
        my_string_assignment(&word_family, largest_family_key);
        my_string_assignment(&word_key, largest_family_key);


        if (running_status == TRUE) {
            Node* largest_family_node = avl_tree_find_node(associative_array, largest_family_key);
            if (largest_family_node != NULL) {
                int total_words = generic_vector_get_size(largest_family_node->data);
                printf("There are %d possible words remaining.\n", total_words);
            } else {
                printf("Error: Could not find the largest family node.\n");
            }

            Associative_array* pTree = (Associative_array*)associative_array;
            if (pTree != NULL && pTree->root != NULL) {
                avl_tree_print_keys_and_word_counts(pTree->root);
            }
        }

        // Check if the guess was correct
        if (my_string_find_char(largest_family_key, guess) == FAILURE) {
            printf("Incorrect guess!\n");
            printf("The letter '%c' is not in the word.\n", guess); 
            if (running_status == TRUE) {
                int total_words = generic_vector_get_size(largest_family_node->data);
                printf("There are %d possible words remaining.\n", total_words);
            }
            guess_number--;
        } else {
            printf("Correct guess!\n");
        }

        // Check if the player has guessed the word
        if (my_string_find_char(word_key, '-') == FAILURE) {
            printf("Congratulations! You guessed the word: ");
            my_string_insertion(word_key, stdout);
            printf("\n");
            break;
        }
    } while (guess_number > 0);

    if (guess_number == 0) {
        printf("Game over! You ran out of guesses. The word was: ");
        MY_STRING final_word = avl_tree_get_random_word(associative_array);
        my_string_insertion(final_word, stdout);
        printf("\n");
    }

    avl_tree_destroy(&associative_array);
    my_string_destroy(&word_key);
    my_string_destroy(&guess_list);
    my_string_destroy(&word_family);
    for (i = 0; i < 30; i++) {
        generic_vector_destroy(&dictionary[i]);
    }
    free(dictionary);
	
}

GENERIC_VECTOR* initialize_dic_vector(void) {
    GENERIC_VECTOR* hgVector = (GENERIC_VECTOR*)malloc(30 * sizeof(GENERIC_VECTOR));
    if (hgVector == NULL) {
        printf("FAILED TO ALLOCATE SPACE FOR hgVector\n");
        exit(1);
    }

    FILE* fp = fopen("dictionary.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        free(hgVector);
        exit(1);
    }

    for (int i = 0; i < 30; i++) {
        hgVector[i] = generic_vector_init_default(my_string_init_copy, my_string_destroy);
        if (hgVector[i] == NULL) {
            printf("FAILED TO ALLOCATE SPACE AT %d\n", i);
            for (int j = 0; j < i; j++) {
                generic_vector_destroy(&hgVector[j]);
            }
            free(hgVector);
            fclose(fp);
            exit(1);
        }
    }
	//MY_STRING hStringCopy = my_string_init_default();
    MY_STRING hString = my_string_init_default();
    if (hString == NULL) {
        printf("FAILED TO ALLOCATE SPACE FOR hString\n");
        for (int i = 0; i < 30; i++) {
            generic_vector_destroy(&hgVector[i]);
        }
        free(hgVector);
        fclose(fp);
        exit(1);
    }

    while (my_string_extraction(hString, fp)) {
        int word_size = my_string_get_size(hString);
        if (word_size > 0 && word_size < 30) {
           // hStringCopy = my_string_init_copy(hString);
            if (hString == NULL) {
                printf("Error: Failed to copy string\n");
                continue;
            }
            generic_vector_push_back(hgVector[word_size], hString);
        }
    }

    fclose(fp);
    my_string_destroy(&hString);

    return hgVector;
}



void read_dictionary(GENERIC_VECTOR vector_array_words[]) {
	MY_STRING hMy_string = NULL;
	FILE* fp;
	int i = 0;
    hMy_string = my_string_init_default();
    fp = fopen("dictionary.txt", "r");
    if (fp == NULL){
		printf("error opening file\n");
        exit(1);
    }

	while (my_string_extraction(hMy_string, fp)) {
		int word_len = my_string_get_size(hMy_string);
        if (word_len > 0 && word_len < 30) {
            generic_vector_push_back(vector_array_words[word_len], hMy_string);
        }
	}

	for (i = 0; i < generic_vector_get_size(vector_array_words[29]); i++) {
		MY_STRING temp = (MY_STRING) *generic_vector_at(vector_array_words[29], i);
        my_string_insertion(temp, stdout);
		printf("\n");
	}

	fclose(fp);
	my_string_destroy(&hMy_string);

}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess) {
    guess = tolower(guess); // Ensure the guess is lowercase
    if (current_word_family == NULL || new_key == NULL || word == NULL) {
        return FAILURE; // Ensure all inputs are valid
    }

    if (my_string_get_size(current_word_family) != my_string_get_size(word)) {
        printf("Error: Mismatched sizes in get_word_key_value (word: %d, current: %d)\n",
               my_string_get_size(word), my_string_get_size(current_word_family));
        return FAILURE;
    }

    my_string_assignment(&current_word_family, new_key); // Ensure assignment is safe
    for (int i = 0; i < my_string_get_size(word); i++) {
        char* char_at_word = my_string_at(word, i);
        if (char_at_word == NULL) {
            return FAILURE; // Ensure valid access
        }
        if (*char_at_word == guess) {
            char* char_at_family = my_string_at(current_word_family, i);
            if (char_at_family != NULL) {
                *char_at_family = guess; // Update the key
            }
        }
    }
    return SUCCESS;
}

int number_of_guesses(void) {
	int n = 0;
	do {
		printf("Please enter the number of guesses you want\n");
		scanf(" %d", &n);
		clear_keyboard_buffer();
	} while(n <= 0 || n > 30);

	return n;

}

char get_guess(void) {
	char c = ' ';
    while (1) {
        printf("Please enter a valid letter guess (a-z): ");
        scanf(" %c", &c);
        clear_keyboard_buffer();

        if (isalpha(c)) {
            return tolower(c);
        } else {
            printf("Invalid input. Please enter a letter.\n");
        }
    }
}

int get_word_length(void) {
	int n = 0;
	do {
		printf("Please enter your chosen word length\n");
		if(scanf(" %d", &n) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_keyboard_buffer();
            continue;
        }
		clear_keyboard_buffer();
	} while(n < 2 || n > 29 || (n == 27 || n == 26));

	return n;
}

Boolean continue_game(void) {
	char c = ' ';
    while (1) {
        printf("Would you like to continue? (y/n)\n");
        scanf(" %c", &c);
        clear_keyboard_buffer();
        c = tolower(c);

        if (c == 'y') {
            return TRUE;
        } else if (c == 'n') {
            return FALSE;
        } else {
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        }
    }
}

Boolean running_total(void) {
	char c = ' ';
	printf("Would you like a running total? (y/n)\n");
	scanf(" %c", &c);
	clear_keyboard_buffer();
	c = tolower(c);

	if (c == 'y') {
		return TRUE;
	}
	if (c == 'n') {
		return FALSE;
	}
	else {
		return running_total();
	}
	return FALSE;

}
void clear_keyboard_buffer(void) {
	char c = ' ';
	scanf("%c", &c);
	while (c != '\n') {
		scanf("%c", &c);
	}
}