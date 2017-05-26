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
  ~cLnumber( ){
    //    cout << "deb: destructor cLnumber ";
    //    cout << "Date:" << month << "/" << day << "/" << year;
    //    cout << endl;
  }
  int getDay () { return day; }
  int getMonth() { return month; }
  int getYear() { return year;}
  int getSize() { return size;}
  int getNum(int i) { return arr_num[i];}
  bool isMatchDate(int mymonth, int myday, int myyear) {
    return (month==mymonth) & (day==myday) & (year==myyear);
  }
  bool isMatchNum(int mynum) {
    for(int i=0; i<size; i++){
      if(mynum == arr_num[i]){
	return true;
      }
    }
    return false;
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
      cout << "Date:" << setw(2) << setfill('0') << month << "." << setw(2) << setfill('0') << day << "." << year;
      for (int i=0; i<size; i++ ) {
	cout << " " << setw(2) << setfill('0')  << arr_num[i];
      }
	  //cout << " Total number: "<< size << " Special ball Index: " << special_ball_index << endl;
    } else {
	cout << "here\n";
      }
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

void wi_megabuck_count_winning( cLnumber &myc_num, cLnumber &myc_win_num) {
  int i,j;
  int mytmp;
  int mycnt_match=0;
  for(i=0; i<myc_num.getSize(); i++){
    if(myc_win_num.isMatchNum(myc_num.getNum(i))){
      mycnt_match++;
    }
  }
  cout << "m=" << mycnt_match;
  if      (mycnt_match <  3)  cout << " .... ";
  else if (mycnt_match == 3)  cout << " $2   ";
  else if (mycnt_match == 4)  cout << " $30  ";
  else if (mycnt_match == 5)  cout << " $500 ";
  else if (mycnt_match == 6)  cout << " JPOT ";
  else                        cout << " IVLD ";
  
}

int read_number_file(char * myfile_name, vector <cLnumber> &myvec_ref);
int main( int argc, char *argv[]){


  vector <cLnumber> v_all_winning_num;
  vector <cLnumber> v_all_my_num;

  read_number_file(argv[1], v_all_winning_num);  
  read_number_file(argv[2], v_all_my_num);  

  //  cout << "debug: all winning number\n";
  //  for(cLnumber mycur_num : v_all_winning_num){
  //    mycur_num.print(1);
  //  }
  cout << "debug: my number\n";
  for(cLnumber mycur_num : v_all_my_num){
    int mycur_day   = mycur_num.getDay();
    int mycur_month = mycur_num.getMonth();
    int mycur_year  = mycur_num.getYear();

    for(cLnumber mycur_win_num : v_all_winning_num){
      if(mycur_win_num.isMatchDate(mycur_month, mycur_day, mycur_year)){
	mycur_num.print(1); cout << " <-> "; mycur_win_num.print(1); cout << "   ";
	wi_megabuck_count_winning(mycur_num, mycur_win_num);
	cout << endl;
      }
    }
  }

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
  //  cout << myfile_name << endl;
  myfile.close();
}
