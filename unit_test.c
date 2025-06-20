#include <stdio.h>
#include "unit_test.h"
int main(int argc, char* argv[]){
	Status (*tests[])(char*, int) = {test_init_default_returns_nonNULL, test_get_size_on_init_default_returns_0, 
dbattell_test_get_capacity_on_init_default_returns_size_plus_one, dbattell_test_init_c_string_null_correct_string, dbattell_test_init_c_string_null_terminated,
dbattell_test_correct_compare_evaluation_for_equal_strings, dbattell_test_compare_recognize_and_evaluate_correctly_null_string, dbattell_test_string_extraction_blank_text_file,
dbattell_test_string_extraction_find_all_5_letter_words, dbattell_test_string_extraction_dynamic_resize, dbattell_test_string_insertion_normal,
dbattell_test_string_insertion_blank_text, dbattell_test_string_push_back_multiple_resize, dbattell_test_string_push_back_null_handle, dbattell_test_string_pop_back_empty_string, 
dbattell_test_string_pop_back_null_handle, dbattell_test_my_string_at_null_handle, dbattell_test_my_string_at_out_of_bounds_index, dbattell_test_my_string_c_str_valid_output, 
dbattell_test_my_string_c_str_null_handle, dbattell_test_my_string_concat_empty_string, dbattell_test_my_string_concat_null_valid_handling, dbattell_test_my_string_empty_on_nonempty_string, 
dbattell_test_my_string_empty_on_null_handle, dbattell_test_get_capacity_on_null_handle};
	int number_of_functions = sizeof(tests) / sizeof(tests[0]);
	int i;
	char buffer[500];
	int success_count = 0;
	int failure_count = 0;
	for(i=0; i<number_of_functions; i++){
		if(tests[i](buffer, 500) == FAILURE){
			printf("FAILED: Test %d failed miserably\n", i);
			printf("\t%s\n", buffer);
			failure_count++;
		}
		else{
			// printf("PASS: Test %d passed\n", i);
			// printf("\t%s\n", buffer);
			success_count++;
		}
	}
	printf("Total number of tests: %d\n", number_of_functions);
	printf("%d/%d Pass, %d/%d Failure\n", success_count,
	number_of_functions, failure_count, number_of_functions);
	return 0;
}
