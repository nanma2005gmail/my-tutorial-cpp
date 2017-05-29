//#include <stdlib.h>
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
  default  :     return "IVD";
  }
}
enum_Month enum_MonthByStr(string myMonth){
  nmUt_StringToLowerCase(myMonth);
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

//-----------------------------------------------------------
//begin clnumber
class cLnumber {
public:
  enum_Loto type;
  int special_ball_index;
  int special_ball_max_num;
  int special_ball_min_num;
  int max_num;
  int min_num;
  int total_num;
private:
  enum_Month month;
  int day;
  int year;
  int arr_num[7] ;
  int cur_num_index;
private:
  void setMonthByString(string mystr_month);
public:
  cLnumber(enum_Loto mytype){
    type = mytype;
    month= jan_m;
    day=0;
    year=0;
    cur_num_index=0;
    switch (type) {
    case WI_MegaBucks:     special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=49; min_num=1; total_num=6; break;
    case WI_Bager5:        special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=31; min_num=1; total_num=6; break;
    case WI_SuperCash:     special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=39; min_num=1; total_num=6; break;
    case WI_Pick4:         special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=9;  min_num=0; total_num=6; break;
    case WI_Pick3:         special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=9;  min_num=0; total_num=4; break;
    case Mega_Million:     special_ball_index=5;  special_ball_max_num=15; special_ball_max_num=1;  max_num=75; min_num=1; total_num=3; break;
    case Power_Ball:       special_ball_index=5;  special_ball_max_num=26; special_ball_max_num=1;  max_num=69; min_num=1; total_num=6; break;
    default :              special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=0;  min_num=1; total_num=6; break;
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
  int getSize() { return total_num;}
  int getNum(int i) { return arr_num[i];}
  void setType(enum_Loto mytype) { type=mytype; }
  bool isMatchDate(enum_Month  mymonth, int myday, int myyear) {
    return (month==mymonth) & (day==myday) & (year==myyear);
  }
  bool isMatchNum(int mynum) {
    for(int i=0; i<total_num; i++){
      if(mynum == arr_num[i]){
	return true;
      }
    }
    return false;
  }
  void addNewNum(int mynewNum, bool myflg_special_num=false){
    arr_num[cur_num_index]=mynewNum;
    cur_num_index++;
    special_ball_index = myflg_special_num ? cur_num_index : -1;
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
    for (int i=0; i<total_num; i++ ) {
      cout << " " << setw(2) << setfill('0')  << arr_num[i];
    }
  }
};
void cLnumber::setMonthByString(string mystr_month){
  month = enum_MonthByStr(mystr_month);
}

//end clnumber
//-----------------------------------------------------------








cLnumber getRandomNum(enum_Loto mytype, string myMonth, int myDay, int myYear ){
  cLnumber mynum(mytype);
  mynum.addDate(myMonth, myDay, myYear);


  vector <int> myv_possible_nums;
  for(int i=0; i<mynum.max_num; i++){
    myv_possible_nums.push_back(i+mynum.min_num);
  }

  int mycur_max_num = mynum.max_num;
  //  cout << "myhere0\n";

  for(int i=0; i<mynum.total_num; i++){
    int mycur_pick_index = rand()%mycur_max_num;
    mynum.addNewNum(myv_possible_nums[mycur_pick_index]);
    //    cout << "vector_size bef: " << myv_possible_nums.size() << " pick_index: "<< mycur_pick_index << "\n";
    myv_possible_nums.erase(myv_possible_nums.begin()+mycur_pick_index);
    //    cout << "vector_size aft: " << myv_possible_nums.size() << "\n";
    //    cout << "myhere2\n";
    mycur_max_num--;
  }
  //  cout << "myhere3\n";
  return mynum;
}

int wi_megabuck_count_winning( cLnumber &myc_num, cLnumber &myc_win_num, bool myprintMsg=true) {
  int i,j;
  int mytmp;
  int mycnt_match=0;
  for(i=0; i<myc_num.getSize(); i++){
    if(myc_win_num.isMatchNum(myc_num.getNum(i))){
      mycnt_match++;
    }
  }
  if(myprintMsg){
    myc_num.print(1); cout << " <-> "; myc_win_num.print(0); cout << "   ";
    cout << "m=" << mycnt_match;
    if      (mycnt_match <  3)  cout << " .... ";
    else if (mycnt_match == 3)  cout << " $2   ";
    else if (mycnt_match == 4)  cout << " $30  ";
    else if (mycnt_match == 5)  cout << " $500 ";
    else if (mycnt_match == 6)  cout << " JPOT ";
    else                        cout << " IVLD ";
    cout << endl;
  }
  return mycnt_match;
}

int read_number_file(char * myfile_name, vector <cLnumber> &myvec_ref);
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
	wi_megabuck_count_winning(mycur_num, mycur_win_num);
	break;
      }
    }
  }


  cLnumber mycur_num(WI_MegaBucks);
  int mycur_day;
  enum_Month mycur_month;
  int mycur_year;
  int i;
  int mycur_wining_status;
  int myfirst_win_index    = -1;
  int mywin_cnt=0;
  int myfirst_3_match_draw = -1;
  int myfirst_4_match_draw = -1;
  int myfirst_5_match_draw = -1;
  int myfirst_6_match_draw = -1;
  int mytotal_3_match_draw = 0;
  int mytotal_4_match_draw = 0;
  int mytotal_5_match_draw = 0;
  int mytotal_6_match_draw = 0;
  srand (time(NULL));
  //  for(i=0; myfirst_6_match_draw == -1; i++){
  for(i=0; i<100000000; i++){
    mycur_num = getRandomNum(WI_MegaBucks, "May", 06, 2017);
    //    cout << "debug here " << i; mycur_num.print(1); cout << endl;
    mycur_day   = mycur_num.getDay();
    mycur_month = mycur_num.getMonth();
    mycur_year  = mycur_num.getYear();


    for(cLnumber mycur_win_num : v_all_winning_num){
      if( mycur_win_num.isMatchDate(mycur_month, mycur_day, mycur_year)){
	mycur_wining_status = wi_megabuck_count_winning(mycur_num, mycur_win_num, false);
	if(mycur_wining_status >= 3){
	  mywin_cnt++;;
	  if( myfirst_win_index==-1 )  myfirst_win_index = i;
	}
	if(mycur_wining_status == 3 ){
	  if(myfirst_3_match_draw == -1 ) myfirst_3_match_draw =i;
	  mytotal_3_match_draw++;
	}
	if(mycur_wining_status == 4 ){
	  if(myfirst_4_match_draw == -1 ) myfirst_4_match_draw =i;
	  mytotal_4_match_draw++;
	}
	if(mycur_wining_status == 5 ){
	  if(myfirst_5_match_draw == -1 ) myfirst_5_match_draw =i;
	  mytotal_5_match_draw++;
	}
	if(mycur_wining_status == 6 ){
	  if(myfirst_6_match_draw == -1 ) myfirst_6_match_draw =i;
	  mytotal_6_match_draw++;
	}
	break;
      }
    }
  }

  int mywinning = 	 mytotal_3_match_draw*2 + mytotal_4_match_draw*30 + mytotal_5_match_draw*500 + mytotal_6_match_draw*1000000;
  printf("total draws         :%10d\n", i);
  printf("total winning draws :%10d  first:%10d %6.5f\n", mywin_cnt,            myfirst_win_index,     (double)mywin_cnt/i            );
  printf("total winning draw 3:%10d  first:%10d %6.5f\n", mytotal_3_match_draw, myfirst_3_match_draw,  (double)mytotal_3_match_draw/i );
  printf("total winning draw 4:%10d  first:%10d %6.5f\n", mytotal_4_match_draw, myfirst_4_match_draw,  (double)mytotal_4_match_draw/i );
  printf("total winning draw 5:%10d  first:%10d %6.5f\n", mytotal_5_match_draw, myfirst_5_match_draw,  (double)mytotal_5_match_draw/i );
  printf("total winning draw 6:%10d  first:%10d %6.5f\n", mytotal_6_match_draw, myfirst_6_match_draw,  (double)mytotal_6_match_draw/i );
  printf("total wining:        %10d         %6.5f\n", mywinning, mywinning/(i*0.5));

	 
  return 0;
}
