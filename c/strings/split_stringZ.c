/* author: plapacz6@gmail.com; date: 2021-10-04 */

#include <string.h>
#include <malloc.h>
#define TESTS_ON

/** Split string to parts according to separator symbol
 * 
 * @params: pointer to array of ponters to stringZ, where result will be write
 * @params: pointer to splited stirngZ
 * @params: pointer to stringZ containing separator symbol
 * @return: number of parts, or -1 if error occured
 */

int split_stringZ(char** result_array, char* splited_string, char* separator){
  
}

#ifdef TESTS_ON
#include <stdio.h>
#include <stdlib.h>

typedef struct test_set_tt {
  char *input_string;
  char *separator;
  char **output_strings_array;
  int numberf_of_output_strings;
} test_set_t;

int test_split_stringZ(){
  
  test_set_t *test_set = {
    //1
    {"jednoczesciowy", " ", {"jednoczesciowy"}, 1},
    //2
    {"dwu-czesciowy", "-", {"dwu-", "czesciowy"}, 2},
    //3
    {"t==rzy==czesciowy","==", {"t","rzy","czesciowy"} ,3}
  };
  int number_of_tests = 3;
  int test_succed = 0;
  int test_failure = 0;
  {
    int number_of_parts = 0;
    char **result;
    int test_counter = 0;
    int i = 0;
    for(test_counter = 0; i < number_of_tests; i++){
      number_of_parts = 
        split_stringZ(result, 
                      test_set[test_counter].input_string, 
                      test_set[test_counter].separator);
      if(number_of_parts == test_set[test_counter].numberf_of_output_strings){
        for(i = 0; i < test_set[test_counter].numberf_of_output_strings; i++){
          if(!strcmp(test_set[test_counter].output_strings_array[i], result[i])){
            test_succed++;
          }
          else 
            test_failure++;
        }
      }
      else{
        test_failure++;
      }
    }
  }
  printf("----\n  test succed  == %d\n  test_failure == %d\n====\n", 
    test_succed, test_failure);
}

int main(){
  test_split_stringZ();
  return 0;
}
#endif //TESTS_ON
