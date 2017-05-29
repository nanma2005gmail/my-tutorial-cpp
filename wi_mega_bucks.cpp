#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "nm_utilities.h"


using namespace std;

enum enum_Loto {WI_MegaBucks=0, WI_Bager5, WI_SuperCash, WI_Pick4, WI_Pick3,Mega_Million, Power_Ball};
enum enum_Month {jan_m=1, feb_m, mar_m, apr_m, may_m, jun_m, jul_m, aug_m, sep_m, oct_m, nov_m, dec_m};

string enum_LotoToStr(enum_Loto mytype){
  switch (mytype) {
  case WI_MegaBucks: return "WI_MegaBucks";
  case WI_Bager5:    return "WI_Bager5";
  case WI_SuperCash: return "WI_SuperCash";
  case WI_Pick4:     return "WI_Pick4";
  case WI_Pick3:     return "WI_Pick3";
  case Mega_Million: return "Mega_Million";
  case Power_Ball:   return "Power_Ball";
  default :          return "INVALID";
  }
}
string enum_MonthToStr(enum_Month myMonth ){
  switch (myMonth) {
  case jan_m :   return "Jan";
  case feb_m :   return "Feb";
  case mar_m :   return "Mar";
  case apr_m :   return "Apr";
  case may_m :   return "May";
  case jun_m :   return "Jun";
  case jul_m :   return "Jul";
  case aug_m :   return "Aug";
  case sep_m :   return "Sep";
  case oct_m :   return "Oct";
  case nov_m :   return "Nov";
  case dec_m :   return "Dec";
  default  :   return "IVD";
  }
}
enum_Month enum_MonthByStr(string myMonth){
  if(myMonth == "jan")   return jan_m;
  if(myMonth == "feb")   return feb_m;
  if(myMonth == "mar")   return mar_m;
  if(myMonth == "apr")   return apr_m;
  if(myMonth == "may")   return may_m;
  if(myMonth == "jun")   return jun_m;
  if(myMonth == "jul")   return jul_m;
  if(myMonth == "aug")   return aug_m;
  if(myMonth == "sep")   return sep_m;
  if(myMonth == "oct")   return oct_m;
  if(myMonth == "nov")   return nov_m;
  if(myMonth == "dec")   return dec_m;
  return jan_m;
}
class cLnumber {
  enum_Loto type;
  enum_Month month;
  int day;
  int year;
  int arr_num[7] ;
  int size;
  int special_ball_index;
  int special_ball_max_num;
  int special_ball_min_num;
  int max_num;
  int min_num;
private:
  void setMonthByString(string mystr_month);
public:
  cLnumber(enum_Loto mytype){
    type = mytype;
    month= jan_m;
    day=0;
    year=0;
    size=0;
    switch (type) {
    case WI_MegaBucks:     special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=49; max_num=1; break;
    case WI_Bager5:        special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=31; max_num=1; break;
    case WI_SuperCash:     special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=39; max_num=1; break;
    case WI_Pick4:         special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=9;  max_num=0; break;
    case WI_Pick3:         special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=9;  max_num=0; break;
    case Mega_Million:     special_ball_index=5;  special_ball_max_num=15; special_ball_max_num=1;  max_num=75; max_num=1; break;
    case Power_Ball:       special_ball_index=5;  special_ball_max_num=26; special_ball_max_num=1;  max_num=69; max_num=49;break;
    default :              special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=0;  max_num=0; break;
    }
  }
  ~cLnumber( ){
    //    cout << "deb: destructor cLnumber ";
    //    cout << "Date:" << month << "/" << day << "/" << year;
    //    cout << endl;
  }
  int getDay () { return day; }
  enum_Month getMonth() { return month; }
  int getYear() { return year;}
  int getSize() { return size;}
  int getNum(int i) { return arr_num[i];}
  void setType(enum_Loto mytype) { type=mytype; }
  bool isMatchDate(enum_Month  mymonth, int myday, int myyear) {
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
      cout << enum_LotoToStr(type) << " Date:" << setw(2) << setfill('0') << enum_MonthToStr(month) << "." << setw(2) << setfill('0') << day << "." << year;
    }
    for (int i=0; i<size; i++ ) {
      cout << " " << setw(2) << setfill('0')  << arr_num[i];
    }
  }
};
void cLnumber::setMonthByString(string mystr_month){
  nmUt_StringToLowerCase(mystr_month);
  month = enum_MonthByStr(mystr_month);
}
cLnumber getRandomNum(enum_Loto mytype, enum_Month myMonth, int myDay, int myYear ){
  cLnumber mynum(mytype);
  
  
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
    enum_Month mycur_month = mycur_num.getMonth();
    int mycur_year  = mycur_num.getYear();

    for(cLnumber mycur_win_num : v_all_winning_num){
      if(mycur_win_num.isMatchDate(mycur_month, mycur_day, mycur_year)){
	mycur_num.print(1); cout << " <-> "; mycur_win_num.print(0); cout << "   ";
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
      mytmp_num_pt = new cLnumber(WI_MegaBucks);

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
