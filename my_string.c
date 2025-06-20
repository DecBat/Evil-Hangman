#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "generic_vector.h"

struct my_string {
	int size;
	int capacity;
	char* data;
};

typedef struct my_string My_string;

Status my_string_assignment(MY_STRING* hLeft, MY_STRING hRight) {
    if (hLeft == NULL || hRight == NULL) {
        return FAILURE; // Ensure valid inputs
    }

    My_string* lString = (My_string*)*hLeft;
    My_string* rString = (My_string*)hRight;

    // If lString is NULL, initialize it as a copy of rString
    if (lString == NULL) {
        *hLeft = my_string_init_copy(hRight);
        if (*hLeft == NULL) {
            return FAILURE; // Memory allocation failed
        }
        return SUCCESS;
    }

    // Ensure lString has enough capacity to hold rString
    if (lString->capacity < rString->size + 1) {
        char* temp = (char*)malloc((rString->size + 1) * sizeof(char));
        if (temp == NULL) {
            return FAILURE; // Memory allocation failed
        }
        free(lString->data); // Free the old data
        lString->data = temp;
        lString->capacity = rString->size + 1;
    }

    // Copy the data from rString to lString
    for (int i = 0; i < rString->size; i++) {
        lString->data[i] = rString->data[i];
    }

    // Update size and null-terminate the string
    lString->size = rString->size;
    lString->data[lString->size] = '\0';

    *hLeft = lString;
    return SUCCESS;
}

MY_STRING my_string_init_copy(MY_STRING hMy_string) {
    if (hMy_string == NULL) {
        printf("Error: NULL source string passed to my_string_init_copy\n");
        return NULL;
    }

    My_string* pString = (My_string*)hMy_string;

    // Allocate memory for the new string object
    My_string* new_string = (My_string*)malloc(sizeof(My_string));
    if (new_string == NULL) {
        printf("Error: Memory allocation failed for new string object\n");
        return NULL;
    }

    // Copy size and capacity
    new_string->size = pString->size;
    new_string->capacity = pString->capacity;

    // Allocate memory for the string data
    new_string->data = (char*)malloc(new_string->capacity * sizeof(char));
    if (new_string->data == NULL) {
        printf("Error: Memory allocation failed for string data\n");
        free(new_string);
        return NULL;
    }

    if (pString->data == NULL) {
        printf("Error: Source string data is NULL\n");
        free(new_string->data);
        free(new_string);
        return NULL;
    }

    for (int i = 0; i < pString->size; i++) {
        new_string->data[i] = pString->data[i];
    }

    new_string->data[new_string->size] = '\0';

    return (MY_STRING)new_string;
}

Boolean is_used (MY_STRING guess_list, char guess) {
	if (guess_list == NULL) {
		return FALSE; // If the guess list is NULL, assume the guess is not used
	}

	if (!isalpha(guess)) {
		return FALSE; // Invalid guess
	}

	guess = tolower(guess);

	if (guess_list == NULL) {
        return FALSE; // If the guess list is NULL, assume the guess is not used
    }

    for (int i = 0; i < my_string_get_size(guess_list); i++) {
        if (*my_string_at(guess_list, i) == guess) {
            return TRUE; // Guess has already been used
        }
    }

    return FALSE; // Guess has not been used

}

void my_string_swap(MY_STRING hLeft, MY_STRING hRight) {
	if (hLeft == NULL || hRight == NULL) {
    		printf("One of the strings is null\n");
		return;
	}

	My_string* lString = (My_string*)hLeft;
	My_string* rString = (My_string*)hRight;

	int temp_size = lString->size;
	lString->size = rString->size;
	rString->size = temp_size;

	int temp_capacity = lString->capacity;
	lString->capacity = rString->capacity;
	rString->capacity = temp_capacity;

	char* temp_data = lString->data;
	lString->data = rString->data;
	rString->data = temp_data;
}

MY_STRING my_string_init_default(void){
	My_string* pString = (My_string*)malloc(sizeof(My_string));
	if(pString != NULL){
		pString->size = 0;
		pString->capacity = 8; // Ensure a default non-zero capacity
		pString->data = (char*)malloc(sizeof(char) * (pString->capacity + 1));
		if (pString->data == NULL) {
			free(pString);
			return NULL;
		}
		pString->data[0] = '\0'; // Initialize the string with a null terminator
	}
	return ((MY_STRING)pString);
}

void my_string_destroy(MY_STRING* phMy_string){
	if (phMy_string == NULL || *phMy_string == NULL) {
        return;
    }
	My_string* pString = (My_string*)*phMy_string;
	free(pString->data);
	free(pString);
	*phMy_string = NULL;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend){
	if (hResult == NULL || hAppend == NULL) {
        	printf("Error: NULL string handle passed to my_string_concat\n");
        	return FAILURE;
    	}

	My_string* rString = (My_string*)hResult;
    	My_string* aString = (My_string*)hAppend;

	if (aString->size == 0) {
        	return SUCCESS;
    	}
	int new_size = rString->size + aString->size;
    	if (new_size >= rString->capacity) {
        	int new_capacity = (rString->capacity * 2 > new_size) ? rString->capacity * 2 : new_size + 1;
        	char* temp = (char*)malloc(new_capacity * sizeof(char));
        	if (temp == NULL) {
            		printf("Failed to allocate memory for string concatenation.\n");
            		return FAILURE;
        	}

		for (int i = 0; i < rString->size; i++) {
            		temp[i] = rString->data[i];
        	}

        	free(rString->data);
        	rString->data = temp;
        	rString->capacity = new_capacity;
    	}

	for(int j = 0; j < aString->size; j++){
		rString->data[rString->size + j] = aString->data[j];
	}

	rString->size = new_size;
    rString->data[rString->size] = '\0';
	return SUCCESS;
}


char* my_string_c_str(MY_STRING hMy_string){
	if (hMy_string == NULL) {
                printf("Error: NULL string handle passed to my_string_at\n");
                return NULL;
        }

	My_string* pString = (My_string*)hMy_string;
	if(pString->size == pString->capacity){
		pString->capacity++;
	}
	pString->data[pString->size] = '\0';
	return pString->data;
}

char* my_string_at(MY_STRING hMy_string, int index){
	if (hMy_string == NULL) {
        	printf("Error: NULL string handle passed to my_string_at\n");
        	return NULL;
    	}

	My_string* pString = (My_string*)hMy_string;
	if(index < 0 || index >= pString->size){
		return NULL;
	}
	return &(pString->data[index]);
}

Status my_string_pop_back(MY_STRING hMy_string){
	if (hMy_string == NULL) {
        	printf("Error: NULL string handle passed to pop_back\n");
        	return FAILURE;
    	}

    	My_string* pString = (My_string*)hMy_string;

    	if (pString->size == 0) {
        	printf("Error: Cannot pop from an empty string\n");
        	return FAILURE;
    	}

    	pString->size--;
    	pString->data[pString->size + 1] = '\0';

	return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item){
	if (hMy_string == NULL) {  
        	printf("Error: NULL string handle passed to my_string_push_back\n");
        	return FAILURE;
	}
	My_string* pString = (My_string*)hMy_string;

//	printf("Before push_back: Size: %d, Capacity: %d\n", pString->size, pString->capacity);

    if (pString->size > pString->capacity) {
        printf("Error: Size exceeds capacity in my_string_push_back\n");
        return FAILURE;
    }

	
	if (pString->size + 1 >= pString->capacity) {
                char* temp = (char*)malloc((pString->capacity * 2 + 1) * sizeof(char));
                if (temp == NULL){
                         printf("Failed to allocate space to temp\n");
                         return FAILURE;
                }
                for (int j = 0; j < pString->size; j++){
                        temp[j] = pString->data[j];
                }
                free(pString->data);
                pString->data = temp;
		pString->capacity = pString->capacity * 2;
        }
	pString->data[pString->size] = item;
	pString->size++;
	pString->data[pString->size] = '\0';

	//printf("After push_back: Size: %d, Capacity: %d\n", pString->size, pString->capacity);

	return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_String){
	if(hMy_String == NULL) {
		return FALSE;
	}
	My_string* pString = (My_string*)hMy_String;
	if (pString->data == NULL || my_string_get_size(hMy_String) == 0) {
        	return TRUE;
    	}
    	return FALSE;
}



MY_STRING my_string_init_c_string(const char* c_string){
	My_string* pString = (My_string*)malloc(sizeof(My_string));
	if (pString == NULL){
		printf("Allocatioon failed\n");
		return NULL;
	}
	int length = 0;
	while(c_string[length] != '\0'){
		length++;
	}

	pString->size = length;
	pString->data = (char*)malloc((length + 1) * sizeof(char));

	if (pString->data == NULL){
		free(pString);
		return NULL;
	}

	for (int i = 0; i < length; i++) {
		pString->data[i] = c_string[i];
	}
	pString->data[length] = '\0';
	pString->capacity = length + 1;
	return pString;
}

int my_string_get_size(MY_STRING hString){
	if (hString == NULL) {
		return 0;
	}
	My_string* pString = (My_string*)hString;
	return pString->size;
}

int my_string_get_capacity(MY_STRING hString){
	if(hString == NULL) {
		return 0;
	}
	My_string* pString = (My_string*)hString;
	return pString->capacity;
}

int my_string_compare(MY_STRING hLeft_String, MY_STRING hRight_String){

	My_string* plString = (My_string*)hLeft_String;
	My_string* prString = (My_string*)hRight_String;

	int size = (plString->size < prString->size) ? plString->size : prString->size;

	for (int i = 0; i < size; i++){
		if (plString->data[i] < prString->data[i]){
			return -1;
		}
		else if (plString->data[i] > prString->data[i]){
			return 1;
		}
	}
	return 0;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {
    if (hMy_string == NULL || fp == NULL) {
        return FAILURE;
    }

    My_string* pString = (My_string*)hMy_string;
    char temp;
    int result;

    // Reset the size to 0 for new input
    pString->size = 0;

    // Read the first character, skipping leading whitespace
    result = fscanf(fp, " %c", &temp);
    if (result == EOF) {
        return FAILURE;
    }

    do {
		//printf("Size: %d, Capacity: %d, Data: %s\n", pString->size, pString->capacity, pString->data);
        // Ensure there is enough capacity in the buffer
        if (pString->size + 1 >= pString->capacity) {
			int new_capacity = (pString->capacity == 0) ? 8 : pString->capacity * 2;
            char* temp_data = (char*)malloc(sizeof(char) * new_capacity);
            if (temp_data == NULL) {
                return FAILURE; // Memory allocation failed
            }

            // Copy existing data to the new buffer
            for (int i = 0; i < pString->size; i++) {
                temp_data[i] = pString->data[i];
            }
			temp_data[pString->size] = '\0';
            // Free the old buffer and update the pointer
            free(pString->data);
            pString->data = temp_data;
            pString->capacity = new_capacity;
        }

        // Add the character to the buffer
        pString->data[pString->size++] = temp;

        // Read the next character
        result = fscanf(fp, "%c", &temp);

	} while (result == 1 && temp != EOF && !isspace(temp)); // Continue until whitespace or EOF

	// Null-terminate the string
	pString->data[pString->size] = '\0';

	return (pString->size > 0) ? SUCCESS : FAILURE;
}


Status my_string_insertion(MY_STRING hString, FILE* fp){
	if (hString == NULL) {
        printf("Null string passed to insertion!\n");
        return FAILURE;
    }
	My_string* pString = (My_string*)hString;

    if (fprintf(fp, "%s", pString->data) < 0) {
    	return FAILURE; // If writing to file fails, return FAILURE
    }
	printf("\n");
	return SUCCESS;
}


Status my_string_find_char(MY_STRING hMy_string, char ch) {
    if (hMy_string == NULL) {
        return FAILURE; // Return FAILURE if the string is NULL
    }

    for (int i = 0; i < my_string_get_size(hMy_string); i++) {
        if (*my_string_at(hMy_string, i) == ch) {
            return SUCCESS; // Character found
        }
    }

    return FAILURE; // Character not found
}