#include <iostream>
#include <thread>
#include <map>
#include <string>
using namespace std::chrono_literals;


void my_function1(char c){
  for(int i = 0; i < 200; i++){
    std::cout << c;
  }
}

void monitoringPogody(std::map<std::string, int> mapaPog){
  while(true){
    for(auto &item: mapaPog){
      item.second++;
      std::cout << item.first << "-" << item.second << std::endl;
    }
    std::this_thread::sleep_for(2000ms);
  }
}

int main(){

  std::map<std::string, int> mapaPogody = {
    {"New York", 15},
    {"Bombay", 20},
    {"Berlin", 18}
  };

  std::thread my_thread1(my_function1, '+');
  std::thread my_thread2(my_function1, 'o');
  my_thread1.join();
  my_thread2.join();
  std::thread prognozaPogody(monitoringPogody, mapaPogody);
  prognozaPogody.join();
  
  //system("sleep 1");
  return 0;
}

/*
kompilacja
g++ plik.cpp  -pthread -o wynik
*/
