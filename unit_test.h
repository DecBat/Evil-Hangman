#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"
	Status test_init_default_returns_nonNULL(char* buffer, int length);
	Status test_get_size_on_init_default_returns_0(char* buffer, int length);
	Status dbattell_test_get_capacity_on_init_default_returns_size_plus_one(char* buffer, int length);
	Status dbattell_test_get_capacity_on_null_handle(char* buffer, int length);
	Status dbattell_test_init_c_string_null_correct_string(char* buffer, int length);
	Status dbattell_test_init_c_string_null_terminated(char* buffer, int length);
	Status dbattell_test_correct_compare_evaluation_for_equal_strings(char* buffer, int length);
	Status dbattell_test_compare_recognize_and_evaluate_correctly_null_string(char* buffer, int length);
	Status dbattell_test_string_extraction_blank_text_file(char* buffer, int length);
	Status dbattell_test_string_extraction_dynamic_resize(char* buffer, int length);
	Status dbattell_test_string_extraction_find_all_5_letter_words(char* buffer, int length);
	Status dbattell_test_string_insertion_normal(char* buffer, int length);
	Status dbattell_test_string_insertion_blank_text(char* buffer, int length);
	Status dbattell_test_string_push_back_multiple_resize(char* buffer, int length);
	Status dbattell_test_string_push_back_null_handle(char* buffer, int length);
	Status dbattell_test_string_pop_back_empty_string(char* buffer, int length);
	Status dbattell_test_string_pop_back_null_handle(char* buffer, int length);
	Status dbattell_test_my_string_at_null_handle(char* buffer, int length);
	Status dbattell_test_my_string_at_out_of_bounds_index(char* buffer, int length);
	Status dbattell_test_my_string_c_str_valid_output(char* buffer, int length);
	Status dbattell_test_my_string_c_str_null_handle(char* buffer, int length);
	Status dbattell_test_my_string_concat_empty_string(char* buffer, int length);
	Status dbattell_test_my_string_concat_null_valid_handling(char* buffer, int length);
	Status dbattell_test_my_string_empty_on_nonempty_string(char* buffer, int length);
	Status dbattell_test_my_string_empty_on_null_handle(char* buffer, int length);
#endif

