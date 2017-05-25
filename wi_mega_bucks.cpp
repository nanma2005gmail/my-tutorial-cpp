#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "nm_utilities.h"


using namespace std;
class sDate {
public:
  int month;
  int day;
  int year;
  sDate(string, int , int );
  void print(int);
  void monthByString(string);
    
};
sDate::sDate(string myM = "jan", int myD = 1,int myY = 1){
  day = myD;
  year = myY;
  month = 1;
}
void sDate::print(int myformat=1){
  if(myformat == 1){
    cout << "Date:" << month << "/" << day << "/" << year;
  } else {
    cout << month << "/" << day << "/" << year;
  }
}
void sDate::monthByString(string mystr_month){
  nmUt_StringToLowerCase(mystr_month);
  if     (mystr_month == "jan") month = 1;
  else if(mystr_month == "feb") month = 2;
  else if(mystr_month == "mar") month = 3;
  else if(mystr_month == "apr") month = 4;
  else if(mystr_month == "may") month = 5;
  else if(mystr_month == "jun") month = 6;
  else if(mystr_month == "jul") month = 7;
  else if(mystr_month == "aug") month = 8;
  else if(mystr_month == "sep") month = 9;
  else if(mystr_month == "oct") month = 10;
  else if(mystr_month == "nov") month = 11;
  else if(mystr_month == "dec") month = 12;
  else {
    cout << "Error translate month in string : " << mystr_month << mystr_month << endl;
  }
}

class cLnumber {
  sDate * date;
  int *arr_num ;
  int size;
  int special_ball_index;

public:
  cLnumber(int mysize){
    arr_num = new int[mysize];
    size=0;
    special_ball_index=-1;
  }

  void addNewNum(int mynewNum, bool myflg_special_num=false){
    arr_num[size]=mynewNum;
    size++;
    special_ball_index = myflg_special_num ? size : -1;
  }
  void addDate(sDate mynewDate) {
    date = &mynewDate;
  }
  void print(int myformat = 1) {
    if(myformat == 1){
      date->print();
    }else {
      cout << "here\n";
    }
  }
  ~cLnumber(){
    delete[] arr_num;
  }
};

int read_number_file(char * myfile_name, vector <cLnumber> *myvec_ref);
int main( int argc, char *argv[]){
  vector <cLnumber> * v_all_winning_num;
  read_number_file(argv[1], v_all_winning_num);  //need to figure out how to pass the ref/pt of the array of number class
  return 0;
}
int read_number_file( char * myfile_name, vector <cLnumber> *myvec_ref) {
  ifstream myfile (myfile_name);
  
  sDate mycur_date;
  string myline;
  string myfirst_word;
  string::size_type mystr_pos;
  int mycur_vec_size;
  if(myfile.is_open()){
    while( getline(myfile, myline)){
      myvec_ref->push_back(cLnumber(5));
      mycur_vec_size = myvec_ref->size();
      
      cout << myline << endl;
      mystr_pos = myline.find_first_of(" ", 0);
      myfirst_word = myline.substr(0,mystr_pos);

      cout << "here\n";
      mycur_date.monthByString(myfirst_word);
      cout << "here1\n";
      
      myline = myline.substr(mystr_pos+1);
      int mynxt_num;
      cout << "here2\n";

      mynxt_num = stoi(myline, &mystr_pos);
      myline = myline.substr(mystr_pos+1);
      mycur_date.day = mynxt_num;
      cout << "here3\n";
      
      mynxt_num = stoi(myline, &mystr_pos);
      myline = myline.substr(mystr_pos+1);
      mycur_date.year = mynxt_num;
      cout << "here4\n";

      //      myvec_ref->at(mycur_vec_size).addNewNum(30);
      //      myvec_ref->at(mycur_vec_size).addNewNum(30);
      //      myvec_ref->at(mycur_vec_size).addNewNum(30);
      //      myvec_ref->at(mycur_vec_size).addNewNum(30);
      //      myvec_ref->at(mycur_vec_size).addNewNum(30);
      //      myvec_ref->at(mycur_vec_size).addDate(mycur_date);
      //      myvec_ref->at(mycur_vec_size).print(1);      
      
      

      mynxt_num = stoi(myline, &mystr_pos);
      myline = myline.substr(mystr_pos+1);
      cout <<  setw(6) << mynxt_num ;

      mynxt_num = stoi(myline, &mystr_pos);
      myline = myline.substr(mystr_pos+1);
      cout <<  setw(6) << mynxt_num ;

      mynxt_num = stoi(myline, &mystr_pos);
      myline = myline.substr(mystr_pos+1);
      cout <<  setw(6) << mynxt_num ;

      mynxt_num = stoi(myline, &mystr_pos);
      myline = myline.substr(mystr_pos+1);
      cout <<  setw(6) << mynxt_num ;
      mynxt_num = stoi(myline, &mystr_pos);
      myline = myline.substr(mystr_pos+1);
      cout <<  setw(6) << mynxt_num ;
      mynxt_num = stoi(myline, &mystr_pos);
      myline = myline.substr(mystr_pos+1);
      cout <<  setw(6) << mynxt_num ;

      double mynxt_num1 = stof(myline, &mystr_pos);
      //      myline = myline.substr(mystr_pos+1);
      cout << " "  <<  setw(6) << setprecision(2) << setiosflags(ios::fixed) << mynxt_num1 ;

      cout << endl;
      
    }
  }
    
  
  cout << myfile_name;
}
