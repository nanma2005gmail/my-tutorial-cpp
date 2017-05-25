#include <iostream>
#include <string>
int myf_test_string ( void );

int main (){
  myf_test_string();
}

int myf_test_string ( void ){
  int myint;
  std::string mystr0 = "nop";
  std::string mystr1 = "nop";
  
  std::cout << "hello c++\n";
  
  std::cin >> myint;
  std::cin >> mystr0;

  mystr0 = mystr0 + " "  + std::to_string(myint);
  
  std::cout << "length:    " << mystr0.length() << std::endl
	    << "size:      " << mystr0.size()   << std::endl
	    << "Empyt?:    " << mystr0.empty()  << std::endl
	    << "FirstChar: " << mystr0.front()  << std::endl
	    << "lastChar:  " << mystr0.back()   << std::endl
	    << "total str: " << mystr0;
  
}
