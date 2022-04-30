/* author: plapacz6@gmail.com; date: 2021-10-04 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <stdbool.h>
#define TESTS_ON
#define DEBUG

/** Split string to parts according to separator symbol.
 * String must '\0' ending, consists of 8bits-constant-length character (not utf8 for example).

 * This is not recurent version.
 *
 * *parray_substr content depend of splitee_chain 
 * if splitee_chain is:
 * '\0' : 1 elemenet array: 1st element is endig pointer *char type
 * 'no_separator\0' : 2 element array, 1st - copy of splitee_chain, 2st - endig pointer *char type
 * 'one separator or more separators\0' : array of substring, endig with NULL pointer *char type
 *
 * @params: pointer to array of ponters to stringZ, where result will be write
 * @params: pointer to splited stirngZ
 * @params: pointer to stringZ containing separator symbol
 * @return: number of parts, or -1 if error occured (demand free alocated memory with function free_split_stringZ_v0()
 */

//int split_stringZ_v0(char*** p_array_substr, const char* *splitee_chain, size_t str_len,  const char* *separator, size_t sep_len){
int split_stringZ_v0(char*** p_array_substr, const char* splitee_chain, const char* separator){

  typedef struct slist_tt {
    char *substr;
    struct slist_tt *next;
  } slist_t;
  
  if(*p_array_substr != NULL){
    perror("not used free_split_stringZ_ver0()"
           "after previous use of arg1 with split_strinZ_v0");
    return -1;
  }
  if(splitee_chain == NULL){
    perror("pointer to strinZ to split == NULL");
    return -1;
  }
  if(separator == NULL){
    perror("pointer to separator == NULL");
    return -1;
  }

  const char *ptr_c = splitee_chain;
  size_t sep_len = strlen( separator ); /* UNSAFE */

  slist_t *p_node_list_substr_ = NULL;
  slist_t *p_node_list_substr__head = NULL;
  slist_t *p_node_list_substr__tail = NULL;
  
  int i = 0; //index of current character of stringZ
  int j = 0;
  int k = 0;
  int counter = 0; //of substring
  bool end_of_strZ = false;
  bool sub_str_ready = false;
  
  #ifdef DEBUG
  printf("stringZ : %s\n", splitee_chain);
  #endif //DEBUG  

  i = 0;
  while(!end_of_strZ){
    
    if(*(ptr_c + i) == '\0') {
      end_of_strZ = true;
    }
    else {
      if(*(ptr_c + i) == separator[0]){ //potential sep encountered     
        
        for(j = 1; j < sep_len; j++){
          if(*(ptr_c + j) != separator[j]){
            j = 0;   //sep not found
            break; //for
          }//if
        }//for

        if(j != 0){  //*(separator) found
          sub_str_ready = true;                
        }// if(j != 0) - *(separator) was encountered

      }//if potential *(separator) encountered     
    }


    if(sub_str_ready || end_of_strZ) {  //executed when: 1. substr encouterd or 2.endof strZ encouterd

      //copy rest of the string  (ptr_c == beginnig, ptr_c + 1 ('\0')  == ending)
      
      if(p_node_list_substr_ != NULL){   //is not first node        
        p_node_list_substr_ = p_node_list_substr_->next;        
      }

      if( (p_node_list_substr_ = calloc(1, sizeof(slist_t))) == NULL) {
        perror("can't allocate memory"); 
        return(-1);
      }        
      #ifdef DEBUG
      puts("split_stringZ: malloc : slist*");
      #endif //DEBUG                

      if(p_node_list_substr__head == NULL) {  //was first node
        p_node_list_substr__tail = p_node_list_substr_;
        p_node_list_substr__head = p_node_list_substr__tail;
      }
      else{
        p_node_list_substr__tail->next = p_node_list_substr_;
        p_node_list_substr__tail = p_node_list_substr__tail->next;
      }      
      p_node_list_substr_->substr = NULL;
      p_node_list_substr_->next = NULL;
      

      /* i is index, so allocated space shoud have size i + 1 */
      if( (p_node_list_substr_->substr = calloc((unsigned)i + 1, sizeof(char))) == NULL) {
        perror("can't allocate memory"); 
        return(-1);
      }
      #ifdef DEBUG
      puts("split_stringZ: malloc : char**");
      #endif //DEBUG
      for(k = 0; k < i - 1; k++){   //one place reserved for '\0'
        p_node_list_substr_->substr[k] = *(ptr_c + k);
      }            
      p_node_list_substr_->substr[k] = '\0';
      counter++;
      
      #ifdef DEBUG
      printf("sub_stringZ : %s\n", p_node_list_substr_->substr);
      #endif //DEBUG 
      
      //setting new beginnig
      ptr_c = ptr_c + i - 1 + j;      
      
      sub_str_ready = false;
    }

    i++;              

  }//while


  //create array of substrings

  #ifdef DEBUG
  puts("create p_array_substr");
  #endif //DEBUG  
  
  p_node_list_substr_ = p_node_list_substr__head;
  
  if(( (*p_array_substr) = calloc(counter + 1, sizeof(char*))) == NULL){
  //WHY CALLOCK NOT ZEROS THIS ARRAY ???
    perror("alocate memory: p_array_substr");  
    p_node_list_substr_ = p_node_list_substr__head;
    while(p_node_list_substr_ != NULL){
      p_node_list_substr__head = p_node_list_substr_;
      p_node_list_substr_ = p_node_list_substr_->next;
      free(p_node_list_substr__head->substr);
      perror("memmory was released: p_node_list_->substr");  
      free(p_node_list_substr__head);
      perror("memmory was released: p_node_list_->next");  
      p_node_list_substr__head = NULL;
    }
    p_node_list_substr__tail = NULL;
    perror("memmory was released: p_node_list_");  
    return -1;
  }
  //ifor(k = 0; k < counter + 1; k++){
  //  (*p_array_substr)[k] = 0;
  //}
    /*
     * all elements of p_array_substr[] are set to 0 because by calloc()
     * last element: p_array_substr[counter + 1] marks the end
     */  
  
  unsigned copy_counter = 0;
  
  p_node_list_substr_ = p_node_list_substr__head;
  while(p_node_list_substr_ != NULL){

    p_node_list_substr__head = p_node_list_substr_;
    assert(copy_counter <= counter - 1);
    (*p_array_substr)[copy_counter] = p_node_list_substr_->substr;
    p_node_list_substr_ = p_node_list_substr_->next;
    free(p_node_list_substr__head);  //substr remains intact
    p_node_list_substr__head = NULL;
    copy_counter++;
  }  
  assert(copy_counter == counter);
  
  return counter;         
}
/********************************************************************/
int free_split_strinzZ_v0(char ***p_array_substr){
  /* TODO */
  if((*p_array_substr) != NULL){
    int i = 0;
    while( (*p_array_substr)[i] != NULL){
      //releasing substring
      free((*p_array_substr)[i]);
      #ifdef DEBUG
      puts("free_split_strinz_Z_p_(*p_array_substr): char**");
      #endif //DEBUG
      (*p_array_substr)[i] = NULL;
      i++;
    }
    //releasing array pointers to substrings
    free((*p_array_substr));
    (*p_array_substr) = NULL;  //local parameter
    #ifdef DEBUG
    puts("free_split_strinz_Z_p_(*p_array_substr): char*");
    #endif //DEBUG    
  }  
  return 0;
}


/********************************************************************/
#ifdef TESTS_ON
#include <stdio.h>
#include <stdlib.h>

typedef struct test_set_tt {
  char *input_string;
  char *separator;
  char **output_strings_array;
  int number_of_output_strings;
} test_set_t;

int test_split_stringZ(){
  #define TESTS_NUMBER (10)
  test_set_t *test_set =  calloc(TESTS_NUMBER, sizeof(test_set_t));

  if(test_set == NULL) {
    perror("can't allocate memory"); 
    exit(-1);
  }
  
  /* 
  //#define TV(NR, V, S, NN, R...) \
  //#define TV(NR, V, S, NN, (R)) \ //<< not allowed () on argument list (gcc c99)    
  */  
  #define TV(NR, V, S, NN, ...)   \
  test_set[NR].input_string = V; \
  test_set[NR].separator = S; \
  test_set[NR].number_of_output_strings = NN; \
  test_set[NR].output_strings_array = (char *[]) __VA_ARGS__;
  /*
  //test_set[NR].output_strings_array = (char *[]) ##__VA_ARGS__  //; <<doesn't compile (gcc c99)
  //test_set[NR].output_strings_array = (char *[])  R;//; <<doesn't compile (gcc c99)  
  http://compsci.ca/v3/viewtopic.php?t=26591 
  */
  
    //1a
    TV(0, "jednoczesciowy", " ", 1, {"jednoczesciowy",})
    //1b
    TV(1, "jedno czesciowy", "", 1, {"jedno czesciowy",})
    //1c
    TV(2,"", " ", 1, {""})
    
    //2a
    TV(3, "dwu-czesciowy", "-", 2, {"dwu", "czesciowy"})
    //2b
    TV(4, "-dwu_czesciowy", "-", 2, {"", "dwu_czesciowy"})
    //2c
    TV(5,"dwu_czesciowy-", "-", 3, {"dwu_czesciowy", ""})
    
    //3a
    TV(6,"t==rzy==czesciowy","==", 3,{"t","rzy","czesciowy"})
    //3b
    TV(7,"==trzy==czesciowy","==", 3, {"", "trzy","czesciowy"})
    //3c
    TV(8,"t==rzyczesciowy==","==", 3, {"t","rzyczesciowy", ""})
    //3d
    TV(9,"trzy====czesciowy","==", 3, {"trzy", "", "czesciowy"})
  

  int number_of_tests = TESTS_NUMBER;
  int test_succed = 0;
  int test_failure = 0;
  {
    int number_of_parts = 0;
    char **array_substr = NULL;
    int test_counter = 0;
    int i = 0;
    for(test_counter = 0; test_counter < number_of_tests; test_counter++){
      number_of_parts = 
        split_stringZ_v0(&array_substr, 
                      (const char*)(test_set[test_counter].input_string), 
                      (const char*)(test_set[test_counter].separator)
                      );
      if(number_of_parts == test_set[test_counter].number_of_output_strings){
        for(i = 0; i < test_set[test_counter].number_of_output_strings; i++){
          if(!strcmp( test_set[test_counter].output_strings_array[i], array_substr[i])){
            test_succed++;
          }
          else 
            test_failure++;
        }
      }
      else{
        test_failure++;
      }
      free_split_strinzZ_v0(&array_substr);    
    }    
  }
      
  printf("----\n  test succed  == %d\n  test_failure == %d\n====\n", 
    test_succed, test_failure);
  return 0;
}

int main(){
  test_split_stringZ();
  return 0;
}
#endif //TESTS_ON
