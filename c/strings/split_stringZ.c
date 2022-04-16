/* author: plapacz6@gmail.com; date: 2021-10-04 */

#include <string.h>
#include <malloc.h>
#define TESTS_ON

/** Split string to parts according to separator symbol.
 * String must '\0' ending, consists of 8bits-constant-length character (not utf8 for example).
 * This is not recurent version.
 * @params: pointer to array of ponters to stringZ, where result will be write
 * @params: pointer to splited stirngZ
 * @params: pointer to stringZ containing separator symbol
 * @return: number of parts, or -1 if error occured (demand free alocated memory with function free_split_stringZ_result()
 */

int split_stringZ(char** result_array, char* splited_string, char* separator){
  typedef struct slist_tt {
    char *part;
    slist_t *next;
  } slist_t;
  
  char *ptr_c = &splited_string[0];
  size_t sep_len = len(separator);
  slist_t ptr_part = NULL;
  slist_t ptr_part_head = NULL;
  
  int i = 0;
  int j = 0;
  
  
  i = 0;
  while(*(ptr_c + i) != '\0'){
        
    if(*(ptr_c + i) == *separator[0]){
      for(j = 1; j < sep_len; j++){
        if(*ptr_c != *separator[j]{
          j = 0;
          break; //for
        }//if
      }//for
      if(j != 0){
        if(ptr_part != NULL){
          ptr_part = ptr_part->next;
        }
        if( (ptr_part = calloc(1, sizeof(slist_t))) == NULL) {
          perror("can't allocate memory"); return(-1);
        }  
        if(ptr_part_head == NULL) {
          ptr_part_head = ptr_part;
        }
        ptr_part->part = NULL;
        ptr_part->next = NULL;
        if( (ptr_part->part = calloc(i, sizeof(char)) == NULL) {
          perror("can't allocate memory"); return(-1);
        }
        for(k = 0; k < i; k++){
          ptr_part->part[k] = *(ptr_c + k);
        }
        //strncpy(ptr_part->part, ptr_c, j);
        ptr_part->part[k] = '\0';
        ptr_c = ptr_c + i + j;
        i = 0;
      }// if(j != 0)     
    }//if
    i++;    
           
  }//while
  //copy rest of te string
           
}

int free_split_strinzZ_result(char **result){
  if(result != NULL){
    int i = 0;
    while(*(result + i) != NULL){
      free(*(result + i));
      //*(result + 1) = NULL;
      i++;
    }
    free(result);
    result = NULL;
  }  
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
    //1a
    {"jednoczesciowy", " ", {"jednoczesciowy"}, 1},
    //1b
    {"jedno czesciowy", "", {"jedno czesciowy"}, 1},
    //1c
    {"", " ", {""}, 1},
    
    //2a
    {"dwu-czesciowy", "-", {"dwu", "czesciowy"}, 2},
    //2b
    {"-dwu_czesciowy", "-", {"", "dwu_czesciowy"}, 2},
    //2c
    {"dwu_czesciowy-", "-", {"dwu_czesciowy", ""}, 2},
    
    //3a
    {"t==rzy==czesciowy","==", {"t","rzy","czesciowy"} ,3}
    //3b
    {"==trzy==czesciowy","==", {"", "trzy","czesciowy"} ,3}
    //3c
    {"t==rzyczesciowy==","==", {"t","rzyczesciowy", ""} ,3}
    //3d
    {"trzy====czesciowy","==", {"trzy", "", "czesciowy"} ,3}
  };
  int number_of_tests = 10;
  int test_succed = 0;
  int test_failure = 0;
  {
    int number_of_parts = 0;
    char **result = NULL;
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
  
  free_split_stringZ_result(result);
    
  printf("----\n  test succed  == %d\n  test_failure == %d\n====\n", 
    test_succed, test_failure);
}

int main(){
  test_split_stringZ();
  return 0;
}
#endif //TESTS_ON
