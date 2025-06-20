#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit_test.h"

Status test_init_default_returns_nonNULL(char* buffer, int length){
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if(hString == NULL){
		strncpy(buffer, "test_init_default_returns_nonNULL\n" "my_string_init_default returns NULL", length);
		return FAILURE;
	}
	else{
		my_string_destroy(&hString);
		strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
		return SUCCESS;
	}
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length){
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if(my_string_get_size(hString) != 0){
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n" "Did not receive 0 from get_size after init_default\n", length);
	}
	else{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
	}
	my_string_destroy(&hString);
	return status;
}
Status dbattell_test_get_capacity_on_init_default_returns_size_plus_one(char* buffer, int length){
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if(my_string_get_capacity(hString) != (my_string_get_size(hString) + 1)){
		status = FAILURE;
		printf("Expected a capacity of size + 1 but got %d\n", my_string_get_capacity(hString));
		strncpy(buffer, "dbattell_test_get_capacity_on_init_default_returns_size_plus_one\n" "Did not receive 0 from get_size after init_default\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "dbattell_test_get_capacity_on_init_default_returns_size_plus_one\n", length);
        }

        my_string_destroy(&hString);
        return status;
}

Status dbattell_test_get_capacity_on_null_handle(char* buffer, int length) {
	Status status;
	MY_STRING hString = my_string_init_default();
	if(my_string_get_capacity(NULL) != 0) {
		status = FAILURE;
		printf("Expected a capacity of 0 but got %d\n", my_string_get_capacity(hString));
                strncpy(buffer, "dbattell_test_get_capacity_on_null_handle\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "dbattell_test_get_capacity_on_null_handle\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status dbattell_test_init_c_string_null_correct_string(char* buffer, int length){
	MY_STRING hString = NULL;
        Status status;
        hString = my_string_init_c_string("cat");

	if(strcmp(my_string_c_str(hString), "cat") != 0){
		status = FAILURE;
                printf("Expected cat but got %s\n", my_string_c_str(hString));
                strncpy(buffer, "dbattell_test_init_c_string_null_correct_string\n", length);
	}
	else {
		status = SUCCESS;
                strncpy(buffer, "dbattell_test_init_c_string_null_correct_string\n", length);
        }

        my_string_destroy(&hString);
        return status;
}

Status dbattell_test_init_c_string_null_terminated(char* buffer, int length) {
	MY_STRING hString = NULL;
        Status status;
        hString = my_string_init_c_string("cat");

        if((my_string_at(hString, 3)) != NULL){
                status = FAILURE;
                printf("Expected '\\0' but got %s\n", my_string_at(hString, 3));
                strncpy(buffer, "dbattell_test_init_c_string_null_terminated\n", length);
        }
        else {
                status = SUCCESS;
                strncpy(buffer, "dbattell_test_init_c_string_null_terminated\n", length);
        }

        my_string_destroy(&hString);
        return status;
}

Status dbattell_test_correct_compare_evaluation_for_equal_strings(char* buffer, int length) {

	MY_STRING hRstring = my_string_init_c_string("cat");
        MY_STRING hLstring = my_string_init_c_string("cat");
	Status status;

        if((my_string_compare(hLstring, hRstring)) != 0){
                status = FAILURE;
                printf("Expected 0 but got %d\n", my_string_compare(hLstring, hRstring));
                strncpy(buffer, "dbattell_test_correct_compare_evaluation_for_equal_strings\n", length);
        }
        else {
                status = SUCCESS;
                strncpy(buffer, "dbattell_test_correct_compare_evaluation_for_equal_strings\n", length);
        }

        my_string_destroy(&hRstring);
	my_string_destroy(&hLstring);
        return status;


}

Status dbattell_test_compare_recognize_and_evaluate_correctly_null_string(char* buffer, int length){
	MY_STRING hRstring = my_string_init_c_string("cat");
        MY_STRING hLstring = my_string_init_c_string("");
        Status status;

        if((my_string_compare(hLstring, hRstring)) != -1){
                status = FAILURE;
                printf("Expected -1 but got %d\n", my_string_compare(hLstring, hRstring));
                strncpy(buffer, "dbattell_test_compare_recognize_and_evaluate_correctly_null_string\n", length);
        }
        else {
                status = SUCCESS;
                strncpy(buffer, "dbattell_test_compare_recognize_and_evaluate_correctly_null_string\n", length);
        }

        my_string_destroy(&hRstring);
        my_string_destroy(&hLstring);
        return status;

}

Status dbattell_test_string_extraction_blank_text_file(char* buffer, int length){
	MY_STRING hString = NULL;
        FILE* fp;
	Status status;
        hString = my_string_init_default();
        fp = fopen("test.txt", "r");
        if (fp == NULL){
                printf("error opening file\n");
                exit(1);
        }

        if((my_string_extraction(hString, fp)) != FAILURE) {
		status = FAILURE;
                printf("Expected nothing but got a valid string\n");
                strncpy(buffer, "dbattell_test_string_extraction_blank_text_file\n", length);
        }
        else {
                status = SUCCESS;
                strncpy(buffer, "dbattell_test_string_extraction_blank_text_file\n", length);
        }
	fclose(fp);
        my_string_destroy(&hString);
        return status;

}

Status dbattell_test_string_extraction_dynamic_resize(char* buffer, int length){
	MY_STRING hString = NULL;
        FILE* fp;
        Status status;
        hString = my_string_init_default();
        fp = fopen("long_string.txt", "r");
        if (fp == NULL){
                printf("error opening file\n");
                exit(1);
        }

        if((my_string_extraction(hString, fp)) == FAILURE) {
                status = FAILURE;
                printf("Expected supercalifragilisticexpialdocius but got something else\n");
                strncpy(buffer, "dbattell_test_string_extraction_dynamic_resize\n", length);
        }
        else {
                status = SUCCESS;
                strncpy(buffer, "dbattell_test_string_extraction_dynamic_resize\n", length);
        }
        fclose(fp);
        my_string_destroy(&hString);
        return status;
}

Status dbattell_test_string_extraction_find_all_5_letter_words(char* buffer, int length){
	MY_STRING hString = NULL;
        FILE* fp;
	Status status;
	int count = 0;
        int word_length = 0;
        
        hString = my_string_init_default();
        fp = fopen("dictionary.txt", "r");
        if (fp == NULL){
                printf("error opening file\n");
                exit(1);
        }

        while(my_string_extraction(hString, fp) == SUCCESS){
                word_length = my_string_get_size(hString);
                if (word_length == 5) {
                        count++;
                }
                word_length = 0;
        }
	if(count != 8548){
		status = FAILURE;
		printf("Expected 8548 5 letter words but got %d\n", count);
                strncpy(buffer, "dbattell_test_string_extraction_find_all_5_letter_words\n", length);
        }
        else {
                status = SUCCESS;
                strncpy(buffer, "dbattell_test_string_extraction_find_all_5_letter_words\n", length);
        }
        fclose(fp);
        my_string_destroy(&hString);
        return status;
}

Status dbattell_test_string_insertion_normal(char* buffer, int length) {
	MY_STRING hString = NULL;
        FILE* fp;
        Status status;
	Status result;
        hString = my_string_init_c_string("Hello, world!");
        fp = fopen("insertion.txt", "w");
	if (fp == NULL){
                printf("error opening file\n");
                exit(1);
        }
	result = my_string_insertion(hString, fp);
	fclose(fp);

	FILE* fp_check;
	fp_check = fopen("insertion.txt", "r");
	char file_buffer[50] = {0};
	fgets(file_buffer, 50, fp_check);
	fclose(fp_check);

	if (result != SUCCESS && strcmp(buffer, "Hello, world!") != 0){
		status = FAILURE;
		printf("Expected Hello, world! but got %s\n", file_buffer);
                strncpy(buffer, "dbattell_test_string_insertion_normal\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "dbattell_test_string_insertion_normal\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status dbattell_test_string_insertion_blank_text(char* buffer, int length) {
	MY_STRING hString = NULL;
        FILE* fp;
        Status status;
        Status result;
        hString = my_string_init_c_string(" ");
        fp = fopen("insertion2.txt", "w");
        if (fp == NULL){
                printf("error opening file\n");
                exit(1);
        }
        result = my_string_insertion(hString, fp);
        fclose(fp);

        FILE* fp_check;
        fp_check = fopen("insertion2.txt", "r");
        char file_buffer[50] = {0};
        fgets(file_buffer, 50, fp_check);
        fclose(fp_check);

        if (result != SUCCESS && strcmp(buffer, " ") != 0){
                status = FAILURE;
                printf("Expected Hello, world! but got %s\n", file_buffer);
                strncpy(buffer, "dbattell_test_string_insertion_blank_text\n", length);
        }
        else {
                status = SUCCESS;
                strncpy(buffer, "dbattell_test_string_insertion_blank_text\n", length);
        }
        my_string_destroy(&hString);
        return status;
}

Status dbattell_test_string_push_back_multiple_resize(char* buffer, int length) {
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;
	Status result;
	for (int i = 0; i < 1000; i++){
		result = my_string_push_back(hString, 'A');
	}
	if (result != SUCCESS && my_string_get_size(hString) != 1000){
		status = FAILURE;
		printf("Expected size 1000  but got %d\n", my_string_get_size(hString));
                strncpy(buffer, "dbattell_test_string_push_back_multiple_resize\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "dbattell_test_string_push_back_multiple_resize\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status dbattell_test_string_push_back_null_handle(char* buffer, int length) {
//	MY_STRING hString = NULL;
	Status status;

	if(my_string_push_back(NULL, 'A') == SUCCESS){
		status = FAILURE;
		printf("Expected FAILURE but got SUCCESS\n");
                strncpy(buffer, "dbattell_test_string_push_back_null_handle\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "dbattell_test_string_push_back_null_handle\n", length);
	}
//	my_string_destroy(&hString);
	return status;
}

Status dbattell_test_string_pop_back_empty_string(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();

	if (my_string_pop_back(hString) != FAILURE){
		status = FAILURE;
		printf("Expected FAILURE but got SUCCESS\n");
                strncpy(buffer, "dbattell_test_string_pop_back_empty_string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "dbattell_test_string_pop_back_empty_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status dbattell_test_string_pop_back_null_handle(char* buffer, int length) {
        Status status;

        if (my_string_pop_back(NULL) != FAILURE){
                status = FAILURE;
                printf("Expected FAILURE but got SUCCESS\n");
                strncpy(buffer, "dbattell_test_string_pop_back_null_handle\n", length);
        }
        else {
                status = SUCCESS;
                strncpy(buffer, "dbattell_test_string_pop_back_null_handle\n", length);
        }

        return status;
}

Status dbattell_test_my_string_at_null_handle(char* buffer, int length) {
	Status status;

	if (my_string_at(NULL, 0) != FAILURE) {
		status = FAILURE;
		printf("Expected FAILURE but got SUCCESS\n");
                strncpy(buffer, "dbattell_test_my_string_at_null_handle\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "dbattell_test_my_string_at_null_handle\n", length);
	}
	return status;
}

Status dbattell_test_my_string_at_out_of_bounds_index(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Hello, world!");

	if(my_string_at(hString, -34) != NULL) {
		status = FAILURE;
                printf("Expected FAILURE but got SUCCESS, char is %s\n", my_string_at(hString, -34));
                strncpy(buffer, "dbattell_test_my_string_at_out_of_bounds_index\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "dbattell_test_my_string_at_out_of_bounds_index\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status dbattell_test_my_string_c_str_valid_output(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Hello world!");

	if(strcmp(my_string_c_str(hString), "Hello world!") != 0) {
		status = FAILURE;
		printf("Expected Hello world! but got %s\n", my_string_c_str(hString));
                strncpy(buffer, "dbattell_test_my_string_c_str_valid_output\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "dbattell_test_my_string_c_str_valid_output\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status dbattell_test_my_string_c_str_null_handle(char* buffer, int length) {
	Status status;

	if (my_string_c_str(NULL) != NULL) {
		status = FAILURE;
		printf("Expected FAILURE but got SUCCESS\n");
                strncpy(buffer, "dbattell_test_my_string_c_str_null_handle\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "dbattell_test_my_string_c_str_null_handle\n", length);
	}
	return status;
}

Status dbattell_test_my_string_concat_empty_string(char* buffer, int length) {
	MY_STRING hString = NULL;
	MY_STRING aString = NULL;
	Status status;
	Status result;
	hString = my_string_init_c_string("Hello ");
	aString = my_string_init_c_string("");
	result = my_string_concat(hString, aString);
	if(result == FAILURE && strcmp(hString, "Hello ") != 0) {
		status = FAILURE;
		printf("Expected Hello  but got %s\n", my_string_c_str(hString));
                strncpy(buffer, "dbattell_test_my_string_concat_empty_string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "dbattell_test_my_string_concat_empty_string\n", length);
	}

	my_string_destroy(&hString);
	my_string_destroy(&aString);
	return status;
}

Status dbattell_test_my_string_concat_null_valid_handling(char* buffer, int length) {
	MY_STRING hString = NULL;
        Status status;
        Status result;
        hString = my_string_init_c_string("Hello ");
        result = my_string_concat(hString, NULL);
        if(result != FAILURE) {
                status = FAILURE;
                printf("Expected a FAILURE but got %s\n", my_string_c_str(hString));
                strncpy(buffer, "dbattell_test_my_string_concat_null_valid_handling\n", length);
        }
        else {
                status = SUCCESS;
                strncpy(buffer, "dbattell_test_my_string_concat_null_valid_handling\n", length);
        }

        my_string_destroy(&hString);
        return status;
}

Status dbattell_test_my_string_empty_on_nonempty_string(char* buffer, int length) {
	MY_STRING hString = NULL;
        Status status;
        hString = my_string_init_c_string("Hello");
	if(my_string_empty(hString) != FALSE) {
		status = FAILURE;
		printf("Expected a FAILURE but got SUCCESS");
                strncpy(buffer, "dbattell_test_my_string_empty_on_nonempty_string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "dbattell_test_my_string_empty_on_nonempty_string\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status dbattell_test_my_string_empty_on_null_handle(char* buffer, int length) {
        Status status;
        if(my_string_empty(NULL) != FALSE) {
                status = FAILURE;
                printf("Expected a FAILURE but got SUCCESS");
                strncpy(buffer, "dbattell_test_my_string_empty_on_null_handle\n", length);
        }
        else {
                status = SUCCESS;
                strncpy(buffer, "dbattell_test_my_string_empty_on_null_handle\n", length);
        }

        return status;
}
