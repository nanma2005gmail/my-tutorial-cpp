#include <stdlib.h>
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

enum_Loto enum_LotoByStr(string myLoto){
   nmUt_StringToLowerCase(myLoto);
   if(myLoto == "wi_megabucks")   return   WI_MegaBucks;
   if(myLoto == "wi_bager5"   )   return   WI_Bager5   ;
   if(myLoto == "wi_supercash")   return   WI_SuperCash;
   if(myLoto == "wi_pick4"    )   return   WI_Pick4    ;
   if(myLoto == "wi_pick3"    )   return   WI_Pick3    ;
   if(myLoto == "mega_million")   return   Mega_Million;
   if(myLoto == "power_ball"  )   return   Power_Ball;
   return Power_Ball;
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
  int special_ball_max_num;
  int special_ball_min_num;
  int max_num;
  int min_num;
private:
  enum_Month month;
  int day;
  int year;
  int arr_num[7] ;
  int cur_num_index;
  int total_num;
  int special_ball_index;
private:
  void setMonthByString(string mystr_month);
  void cLnumber_init(enum_Loto mytype){
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
    case Mega_Million:     special_ball_index=5;  special_ball_max_num=15; special_ball_max_num=1;  max_num=75; min_num=1; total_num=6; break;
    case Power_Ball:       special_ball_index=5;  special_ball_max_num=26; special_ball_max_num=1;  max_num=69; min_num=1; total_num=6; break;
    default :              special_ball_index=-1; special_ball_max_num=-1; special_ball_max_num=-1; max_num=0;  min_num=1; total_num=6; break;
    }
  }
public:
  cLnumber(enum_Loto mytype){
    cLnumber_init(mytype);
  }
  cLnumber(string mytype){
    cLnumber_init(enum_LotoByStr(mytype));
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
  int getSpecialBallIndex(){ return special_ball_index;}
  int getSpecialBall() { if(special_ball_index != -1)  return arr_num[special_ball_index]; else return -1;}
    
  void setType(enum_Loto mytype) { type=mytype; }
  bool isMatchDate(enum_Month  mymonth, int myday, int myyear) {
    return (month==mymonth) & (day==myday) & (year==myyear);
  }
  bool isMatchNum(int mynum) {
    int mysize;
    if(special_ball_index == -1){
      mysize = total_num;
    } else {
      mysize = total_num-1;
    }
    for(int i=0; i<mysize; i++){
      if(mynum == arr_num[i]){
	return true;
      }
    }
    return false;
  }
  bool isMatchSpecialNum(int mynum){
    if(special_ball_index == -1){
      printf("Error, no special ball\n");
      return false;
    }
    if(arr_num[special_ball_index] == mynum){
      return true;
    } else {
      return false;
    }
  }
  void addNewNum(int mynewNum){
    arr_num[cur_num_index]=mynewNum;
    cur_num_index++;
    //special_ball_index = myflg_special_num ? cur_num_index : -1;
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

  for(int i=0; i<mynum.getSize(); i++){
    int mycur_pick_index = rand()%mycur_max_num;
    mynum.addNewNum(myv_possible_nums[mycur_pick_index]);
    myv_possible_nums.erase(myv_possible_nums.begin()+mycur_pick_index);
    mycur_max_num--;
  }
  return mynum;
}

int checkWinning( cLnumber &mycur_num, vector <cLnumber> &myv_win_num, enum_Loto mytype = WI_MegaBucks, bool myprintMsg=true) {

  int        mycur_day   = mycur_num.getDay();
  int        mycur_year  = mycur_num.getYear();
  enum_Month mycur_month = mycur_num.getMonth();

  int i,j;
  int mytmp;
  int mycnt_match=0;
  int mycnt_special_ball_match=0;
  int mycur_special_ball_index=mycur_num.getSpecialBallIndex();
  for(cLnumber mycur_win_num : myv_win_num){
    if(mycur_win_num.isMatchDate(mycur_month, mycur_day, mycur_year)){
      if(mycur_special_ball_index != -1){
	if(mycur_win_num.isMatchSpecialNum(mycur_num.getSpecialBall())){
	  mycnt_special_ball_match = 1;
	}
      }
      for(i=0; i<mycur_num.getSize(); i++){
	if(mycur_win_num.isMatchNum(mycur_num.getNum(i))){
	  mycnt_match++;
	}
      }
      if(myprintMsg && mytype == WI_MegaBucks){
	mycur_num.print(1); cout << " <-> "; mycur_win_num.print(0); cout << "   ";
	cout << "m=" << mycnt_match;
	if      (mycnt_match <  3)  cout << " .... ";
	else if (mycnt_match == 3)  cout << " $2   ";
	else if (mycnt_match == 4)  cout << " $30  ";
	else if (mycnt_match == 5)  cout << " $500 ";
	else if (mycnt_match == 6)  cout << " JPOT ";
	else                        cout << " IVLD ";
	cout << endl;
      }
      if(myprintMsg && mytype == Power_Ball){
	mycur_num.print(1); cout << " <-> "; mycur_win_num.print(0); cout << "   ";
	cout << "m=" << mycnt_match << "  sm=" << mycnt_special_ball_match;
	if      (mycnt_match <  3 && mycnt_special_ball_match == 0)  cout << " .... ";
	else if (mycnt_match <= 1 && mycnt_special_ball_match == 1)  cout << " $4   ";
	else if (mycnt_match == 2 && mycnt_special_ball_match == 1)  cout << " $7   ";
	else if (mycnt_match == 3 && mycnt_special_ball_match == 0)  cout << " $7   ";
	else if (mycnt_match == 3 && mycnt_special_ball_match == 1)  cout << " $100 ";
	else if (mycnt_match == 4 && mycnt_special_ball_match == 0)  cout << " $100 ";
	else if (mycnt_match == 4 && mycnt_special_ball_match == 1)  cout << " $50,000";
	else if (mycnt_match == 5 && mycnt_special_ball_match == 0)  cout << " $100,000";
	else if (mycnt_match == 5 && mycnt_special_ball_match == 1)  cout << " JPOT";
	else                        cout << " IVLD ";
	cout << endl;
      }
      if(myprintMsg && mytype == Mega_Million){
	mycur_num.print(1); cout << " <-> "; mycur_win_num.print(0); cout << "   ";
	cout << "m=" << mycnt_match << "  sm=" << mycnt_special_ball_match;
	if      (mycnt_match <  3 && mycnt_special_ball_match == 0)  cout << " .... ";
	else if (mycnt_match == 0 && mycnt_special_ball_match == 1)  cout << " $1   ";
	else if (mycnt_match == 1 && mycnt_special_ball_match == 1)  cout << " $2   ";
	else if (mycnt_match == 2 && mycnt_special_ball_match == 1)  cout << " $5   ";
	else if (mycnt_match == 3 && mycnt_special_ball_match == 0)  cout << " $5   ";
	else if (mycnt_match == 3 && mycnt_special_ball_match == 1)  cout << " $50 ";
	else if (mycnt_match == 4 && mycnt_special_ball_match == 0)  cout << " $500 ";
	else if (mycnt_match == 4 && mycnt_special_ball_match == 1)  cout << " $5,000";
	else if (mycnt_match == 5 && mycnt_special_ball_match == 0)  cout << " $1,000,000";
	else if (mycnt_match == 5 && mycnt_special_ball_match == 1)  cout << " JPOT";
	else                        cout << " IVLD ";
	cout << endl;
      }
    }
  }
  return mycnt_match;
}

int read_number_file( char * myfile_name, vector <cLnumber> &myvec_ref, string myLoto_type_in_str){
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
      mytmp_num_pt = new cLnumber(myLoto_type_in_str);

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

      if(mytmp_num_pt->type == WI_MegaBucks){
	myline = myline.substr(mystr_pos+1);
	double mynxt_num1 = stof(myline, &mystr_pos);
      }
      myvec_ref.push_back(*mytmp_num_pt);
      delete mytmp_num_pt;
    }
  }
  myfile.close();


    printf("debug:\n");  
    myvec_ref[0].print(1);
    printf("debug: total_num=%d\n", myvec_ref[0].getSize());
    printf("debug: special_ball=%d\n", myvec_ref[0].getSpecialBallIndex());
  return 1;
}



int main( int argc, char *argv[]){


  vector <cLnumber> v_all_winning_num;
  vector <cLnumber> v_all_my_num;
  enum_Loto mytype = enum_LotoByStr(argv[3]);
  read_number_file(argv[1], v_all_winning_num, argv[3]);
  read_number_file(argv[2], v_all_my_num, argv[3]);  

  //  cout << "debug: all winning number\n";
  //  for(cLnumber mycur_num : v_all_winning_num){
  //    mycur_num.print(1);
  //  }
  cout << "debug: my number\n";
  for(cLnumber mycur_num : v_all_my_num){
    checkWinning(mycur_num, v_all_winning_num, mytype, true);
  }

  return 0;

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
  for(i=0; i<1000; i++){
    mycur_num = getRandomNum(WI_MegaBucks, "May", 06, 2017);
    //    cout << "debug here " << i; mycur_num.print(1); cout << endl;
    mycur_day   = mycur_num.getDay();
    mycur_month = mycur_num.getMonth();
    mycur_year  = mycur_num.getYear();

    mycur_wining_status = checkWinning(mycur_num, v_all_winning_num, WI_MegaBucks, false);
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
