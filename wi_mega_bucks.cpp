#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "nm_utilities.h"


using namespace std;

class cLnumber {
  int month;
  int day;
  int year;
  int arr_num[7] ;
  int size;
  int special_ball_index;

private:
  void setMonthByString(string mystr_month);
public:
  cLnumber(int mysize){
    month=0;
    day=0;
    year=0;
    size=0;
    special_ball_index=-1;
    //cout << "deb: cLnumber Constructor\n";
  }
  void addNewNum(int mynewNum, bool myflg_special_num=false){
    arr_num[size]=mynewNum;
    size++;
    special_ball_index = myflg_special_num ? size : -1;
  }
  void addDate(string myM, int myD, int myY) {
    setMonthByString(myM);
    day=myD;
    year=myY;
  }
  void print(int myformat = 1) {
    if(myformat == 1){
    cout << "Date:" << month << "/" << day << "/" << year;
      for(int i=0; i<size; i++){
	cout << " " << arr_num[i];
      }
      cout << " Total number: "<< size << " Special ball Index: " << special_ball_index << endl;
    }else {
      cout << "here\n";
    }
  }
  ~cLnumber(){
    //    cout << "deb: destructor cLnumber ";
    //    cout << "Date:" << month << "/" << day << "/" << year;
    //    cout << endl;
  }
};
void cLnumber::setMonthByString(string mystr_month){
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



int read_number_file(char * myfile_name, vector <cLnumber> &myvec_ref);
int main( int argc, char *argv[]){


  vector <cLnumber> v_all_winning_num;


  //--------------------------
  //trying out class of class
  cLnumber mynum(5);
  mynum.addNewNum(6);
  mynum.addNewNum(6);
  mynum.addNewNum(6);
  mynum.addNewNum(6);
  mynum.addNewNum(6, true);
  mynum.addDate("Apr", 24, 2020);
  cout << "deb: class print: ";
  mynum.print(1);
  cout << endl;
  //--------------------------
  //trying out vector of classes
  v_all_winning_num.push_back(mynum);

  cLnumber *mynum_pt;
  mynum_pt = new cLnumber(5);
  mynum_pt->addNewNum(7);
  mynum_pt->addNewNum(7);
  mynum_pt->addNewNum(7);
  mynum_pt->addNewNum(7);
  mynum_pt->addNewNum(7, true);
  mynum_pt->addDate("Apr", 24, 2021);
  v_all_winning_num.push_back(*mynum_pt);
  cout << "deb: vector class print: v0 ";
  v_all_winning_num[0].print();
  cout << endl;
  cout << "deb: vector class print: v1 ";
  v_all_winning_num[1].print();
  cout << endl;

  
  read_number_file(argv[1], v_all_winning_num);  
  cout << "deb: after function call: \n";
  v_all_winning_num[0].print(1);
  v_all_winning_num[1].print(1);
  v_all_winning_num[2].print(1);
  v_all_winning_num[3].print(1);
  v_all_winning_num[4].print(1);

  return 0;
}
int read_number_file( char * myfile_name, vector <cLnumber> &myvec_ref) {
  ifstream myfile (myfile_name);


  string myline;
  string myfirst_word;
  string::size_type mystr_pos;
  cLnumber *mytmp_num_pt;

  int mynxt_num;
  int myday;
  int myyear;

  if(myfile.is_open()){
    while( getline(myfile, myline)){
      mytmp_num_pt = new cLnumber(6);

      mystr_pos = myline.find_first_of(" ", 0);
      myfirst_word = myline.substr(0,mystr_pos);

      myline = myline.substr(mystr_pos+1);
      myday = stoi(myline, &mystr_pos);

      myline = myline.substr(mystr_pos+1);
      myyear = stoi(myline, &mystr_pos);
      mytmp_num_pt->addDate(myfirst_word, myday, myyear);


      for(int i=0; i<6; i++){
	myline = myline.substr(mystr_pos+1);
	mynxt_num = stoi(myline, &mystr_pos);
	mytmp_num_pt->addNewNum(mynxt_num);
      }

      myline = myline.substr(mystr_pos+1);
      double mynxt_num1 = stof(myline, &mystr_pos);
      //      cout << ">>last number "  <<  setw(6) << setprecision(2) << setiosflags(ios::fixed) << mynxt_num1 ;
      //      cout << endl;
      //      cout << "deb, reading files: line count: " << myvec_ref.size() << " ";
      //      cout << endl;
      //      myvec_ref.push_back(*mytmp_num_pt);
      //      myvec_ref[myvec_ref.size()-1].print();
      //cout << "deb: end line" << endl;
      //      cout << "deb, reading files: line count: " << myvec_ref.size() << " ";
      //      cout << endl;
      myvec_ref.push_back(*mytmp_num_pt);
      delete mytmp_num_pt;
      //      myvec_ref[myvec_ref.size()-1].print();
      //      cout << endl;
    }
  }
  cout << myfile_name << endl;
}
