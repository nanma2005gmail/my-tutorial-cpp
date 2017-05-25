#include <iostream>
#include <string>

int nmUt_StringToLowerCase (std::string &mystr){
  int i;
  for(i=0; mystr[i]; i++) {
    mystr[i] = tolower(mystr[i]);
    //    std::cout << "debug: " << i << mystr[i] << "<\n";
  }
  return i;
}
