// For this project use DEVC++ IDE

#include<bits/stdc++.h>
#include<string>
#include<mysql.h>
#include<mysqld_error.h>
using namespace std;

//-------------------------------------------------------------
MYSQL *obj;
MYSQL_ROW row;
MYSQL_RES *res;
int state;
//---------------------------------------------------------------
string fn,ln,address,ph,s;                                    //variables
int proof,age;
//---------------------------------------------------------------
void prt(){                                                 //   function which prints the rating of other customers from database
	string mn;
	stringstream f;
	f<<"select rating from feed";
	string j = f.str();
	const char *F = j.c_str();
	state = mysql_query(obj,F);
	if(!state){
		res = mysql_use_result(obj);
		while(row = mysql_fetch_row(res)){
		  mn = row[0];	
		}
	}
	cout<<"Our Rating from customers(1-5): "<<mn<<endl;
}
//--------------------------------------------------------------
string findf(int f){                                     // returning a string
	string ft;
	if(f==100)
	 ft = "f1";
	else if(f==200)
	 ft = "f2";
	else if(f==300)
	  ft = "f3";
	else if(f==400)
	   ft = "f4";
	else
	   ft = "f5";
 return ft;
}
//------------------------------------------------------------------
string ssearch(int r);
void bill(string fn,string ln,string phn,string Cd,string addr,int Ty,int n1,int nd);
int CI(string s);
string CS(int i);
//---------------------------------------------------------------
void feed(){                                                      // Function which takes feedback from the customer
	int sum = 0,q,s,st,cl,td,fd,hn,rn;
	string rt,nu;
	cout<<"---Feedback Form---"<<endl;
	cout<<"How was the quality of the rooms(1-5): ";
	cin>>q;
	cout<<"How was the room service(1-5): ";
	cin>>s;
	cout<<"How was our staff(1-5): ";
	cin>>st;
	cout<<"Cleanliness of the hotel(1-5): ";
	cin>>cl;
	cout<<"Travel Desk(1-5): ";
	cin>>td;
	cout<<"Food(1-5): ";
	cin>>fd;
	sum = q+s+st+cl+td+fd;
	sum = sum/6;
	stringstream l;
	l<<"select rating,num from feed";
	string L = l.str();
	const char *k = L.c_str();
	state = mysql_query(obj,k);
	if(!state){
		res = mysql_use_result(obj);
		while(row = mysql_fetch_row(res)){
			rt = row[0];
			nu = row[0];
		}
	}
	rn = CI(rt);
	hn = CI(nu);
	hn = hn+1;
	sum = sum + rn;
	sum = sum/hn;
	stringstream f;
	f<<"update feed set rating = '"<<sum<<"',num = '"<<hn<<"'";
	string j = f.str();
	const char *F = j.c_str();
	state = mysql_query(obj,F);
	cout<<"Thank you for your feedback"<<endl;
}
//---------------------------------------------------------------
void nuroom(int p,int f,int l){                                 // Function which allots new room
	int c = 0;
	for(int i =0;i<20 && c<l;i++ ){
		int op = i + f;
		string s = ssearch(op);
		if(s=="0"){
			stringstream ss;
			ss<<"insert into stay(roo,pd) values('"<<op<<"','"<<p<<"')";
			string query = ss.str();
			const char *q = query.c_str();
			state = mysql_query(obj,q);
			c++;
			cout<<op<<" ";
		}
		else{
			continue;
		}
	}
}
//---------------------------------------------------------
string CS(int n){      // Function which converts int to string
	stringstream sso;
	sso << n;
	string sr = sso.str();
	return sr;
}
//-----------------------------------------------------------
int CI(string s){         // Function which converts string to int
	stringstream ssi(s);
	int ir = 0;
	ssi >> ir;
	return ir;
}
//-------------------------------------------------------------
string search(int id){                                   // Function which searches whether a customer is staying in our hotel or not
	string s;
		stringstream ss;
	ss<<"select EXISTS(select * from customer where pid ='"<<id<<"')";
	string query = ss.str();
		const char *q = query.c_str();
		state = mysql_query(obj,q);
	
		if(!state){
			
			res = mysql_use_result(obj);
		    
			while((row = mysql_fetch_row(res) )!=NULL){
				s = row[0];
			}
            }
            return s;
}
//--------------------------------------------------------------
string ssearch(int r){       // Checks whether room is booked or not
	string s;
			stringstream ss;
	ss<<"select EXISTS(select *from stay where roo ='"<<r<<"' )";
	string query = ss.str();
		const char *q = query.c_str();
		state = mysql_query(obj,q);
	
		if(!state){
			
			res = mysql_use_result(obj);
		    
			while((row = mysql_fetch_row(res) )!=NULL){
				s = row[0];
			}
            }
            return s;
}
//--------------------------------------------------------------
int get_val(string s,int f){  //Function which gets the available number of rooms on that particular day
	
string dt;
stringstream ss;
ss<<"select EXISTS(select *from avail where chin = '"<<s<<"')";
string query = ss.str();
const char *q = query.c_str();
state = mysql_query(obj,q);
if(!state){
	res = mysql_use_result(obj);
	while(row = mysql_fetch_row(res)){
		dt = row[0];
	}
}
string ft = findf(f);
string gt;
if(dt=="0"){
	return 20;
}
else{
	stringstream qt;
	qt<<"select "<<ft<<" from avail where chin = '"<<s<<"' ";
	string Qt = qt.str();
	const char *qT = Qt.c_str();
	state = mysql_query(obj,qT);
	if(!state){
		res = mysql_use_result(obj);
		while(row = mysql_fetch_row(res)){
		 gt = row[0];	
		}
	}
}
int x = CI(gt);
return x;
}
//----------------------------------------------------------------
void avail_update(string s,int f,int nd,int  w,int l){  //Function which updates the available number of rooms
	for(int i=0;i<nd;i++){
	
	string dt,Sm;
	stringstream ret;
	ret<<"select DATE_ADD('"<<s<<"', INTERVAL '"<<i<<"' DAY)";
	string Ret = ret.str();
	const char *re = Ret.c_str();
	state = mysql_query(obj,re);
	if(!state){
		res = mysql_use_result(obj);
		while(row = mysql_fetch_row(res)){
			Sm = row[0];
		}
		
	}

stringstream ss;
ss<<"select EXISTS(select *from avail where chin = '"<<Sm<<"')";
string query = ss.str();
const char *q = query.c_str();
state = mysql_query(obj,q);
if(!state){
	res = mysql_use_result(obj);
	while(row = mysql_fetch_row(res)){
		dt = row[0];
	}
}
string ft = findf(f);


if(dt=="0"){
	stringstream ins;
	ins<<"insert into avail(chin) values('"<<Sm<<"')";
	string sq = ins.str();
	const char *qs = sq.c_str();
	state = mysql_query(obj,qs);
	  
	  stringstream op;
	  op<<"update avail set f1 = 20,f2 = 20,f3=20,f4=20,f5=20 where chin = '"<<Sm<<"' ";
	  string Op = op.str();
	  const char *oP = Op.c_str();
	  state = mysql_query(obj,oP);
	  	  
	stringstream sj;
	sj<<"update avail set "<<ft<<" = '"<<w<<"' where chin = '"<<Sm<<"' ";
	string Sj = sj.str();
	const char *SJ = Sj.c_str();
	state = mysql_query(obj,SJ);
}
else{
	string E;
	stringstream uk;
	uk<<"select "<<ft<<" from avail where chin = '"<<Sm<<"' ";
	 string Uk = uk.str();
	 const char *uK = Uk.c_str();
	 state = mysql_query(obj,uK);
	 if(!state){
	 	res = mysql_use_result(obj);
	 	while(row = mysql_fetch_row(res)){
	 		E = row[0];
		 }
	 }
	 cout<<mysql_error(obj)<<endl;
	 int oop = CI(E);
	 oop = oop-l;
		stringstream sj;
	sj<<"update avail set "<<ft<<" = '"<<oop<<"' where chin = '"<<Sm<<"' " ;
	string Sj = sj.str();
	const char *SJ = Sj.c_str();
	state = mysql_query(obj,SJ);
}
}
}
string st(){
    string s;
    
  cout<<"Enter checkin date(yyyy-mm-dd): ";
   cin>>s;
   
   while(s.length()!=10){
       cout<<"Enter correct format like 1979-01-03"<<endl;
       cout<<"Enter checkin date(dd-mm-yy): ";
       cin>>s;
   }
    return s;
}
//------------------------------------------------------------------
int date(int d,int m,int y){  // Function which checks if the date is valid or not
        time_t now = time(0);
    tm*dt = localtime(&now);
    int s = (1900 + dt->tm_year);
    int s1 = (1 + dt->tm_mon);
    int s2 = (dt->tm_mday);
   if(m<1 || m>12){
       return 22;
   }
   if(d<1 || d>31){
       return 22;
   }
   if (m == 4 || m == 6 ||
        m == 9 || m == 11){
            if(d>30){
       return 22;
   }
        }
        if(m==2){
            if(((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)){
                if(d>29){
                    return 22;
                }
            }
            else{
                if(d>28){
                    return 22;
                }
            }
        }
      if(m<s1){
        if(y>s){
            if(s1==11 && m==1 &&d>s2){
                return 23;
            }
            else if(s1==11 &&  m>1){
           return 23;}
           else if(s1==11 && d<=s2&&m==1){
               return 21;
           }
           else if(s1==12 && d>s2 && m==2){
               return 23;
           }
           else if(s1==12 && m>2){
            return 23;}
            else if(s1 ==12 && d<=s2 && m<=2){
                return 21;
            }
            else{
                return 22;
            }
        }
        return 22;
      }
      else if(m==s1){
          if(y>s){
              return 23;
          }
          if(y<s){
              return 22;
          }
          if(y==s){
          if(d<s2)
            return 22;
         else if(d>=s2)
           return 21;
          }
      }
      else{
      if(y>s){
          return 23;
      }
      if(y<s){
          return 22;
      }
      if(y==s){
      if(d>s2 && m==(s1+2)){
          return 23;
      } 
      else if(d>s2 && m>s1+2)
       return 23;
      }
      else if(d<=s2 && m==s1+2)
        return 21;
      }
          
    return 21;
}
//------------------------------------------------------------------
void boo(int f){                    // Function which books room by checking the rooms avialable using nuroom function
    int l,d,m,ye,d1,d2,m1,m2,y1,y2,y3,y4,y5,nd,w;
    string y,name,s,mj;
        s = st();
    d1 = s[8]-48;
     d2 = s[9]-48;
     d = d1*10 + d2;
     m1 = s[5]-48;
     m2 = s[6]-48;
     m = m1*10 + m2;
     y1 = s[0]-48;
     y2 = s[1]-48;
     y3 = y1*10 + y2;
     y4 = s[2]-48;
     y5 = s[3]-48;
     ye = y3*100 +((y4*10)+y5);
   cout<<endl;
        int c = date(d,m,ye);
        if(c==21){
        	w = get_val(s,f);
                if(w==0){   
         cout<<"Sorry, All the rooms are booked"<<endl;
            }
            else{
       cout<<"Available number of rooms: "<<w<<endl;     
       cout<<"Number of room needed: ";
       cin>>l;
       if(l>w){
        cout<<"Number of rooms entered is more than the available"<<endl;
       }
       else{
           cout<<"would like to book(y or n): ";
           cin>>y;
           if(y=="y"|| y=="Y"){
                cout<<"Your First Name: ";
               cin>>fn;
               cout<<"Your last Name: ";
               cin>>ln;
               name = fn + ln;
               getline(cin,mj);
               cout<<"Your address: ";
               getline(cin,address);
               cout<<"Your phone number: ";
               cin>>ph;
               cout<<"Your age: ";
                cin>>age;
               cout<<"your proof id: ";
               cin>>proof;
               cout<<"Staying number of days: ";
               cin>>nd;
               stringstream ss;
ss<<"insert into customer(fname,lname,address,phone,age,pid,nrooms,typ,chi,ndays) values('"<<fn<<"','"<<ln<<"','"<<address<<"','"<<ph<<"','"<<age<<"','"<<proof<<"','"<<l<<"','"<<f<<"','"<<s<<"','"<<nd<<"')";
               string query = ss.str();
				const char *q = query.c_str();
             state = mysql_query(obj,q);
            cout<<"Your room numbers are: ";
            nuroom(proof,f,l);
           cout<<endl;
           w = w-l;
//           int no = get_val(f,w);
            avail_update(s,f,nd,w,l);
           }
            }
    }
}
else if(c==23){
    cout<<"Booking before 2 months isn't possible"<<endl;
}
else{
    cout<<"Invalid date"<<endl;
}
}
//----------------------------------------------------------------
void alloc(){                          // Displays types of room
            int c;
            do{
            cout<<endl;
            cout<<"Which type of room do you want?"<<endl;
            cout<<"1) Normal rooms  2) Queen bedroom"<<endl;
            cout<<"3) King rooms    4) Apartment type"<<endl;
            cout<<"5) Deluxe room"<<endl;
            cout<<endl;
            cout<<"Enter your choice(as number): ";
            cin>>c;
            cout<<endl;
            switch(c){
                case 1: boo(100);
                        break;
                case 2: boo(200);
                        break;
                case 3: boo(300);
                        break;
                case 4: boo(400);
                        break;
                case 5: boo(500);
                        break;
                default: cout<<"Incorrect option"<<endl;
            }
            }while(c>5);
 
    }
//----------------------------------------------------------------
void cancel(){                // Function for Room Cancellation
	int n,n1,n2,n3;
	string s;
	cout<<"------CANCELLATION-------"<<endl;
	cout<<"Enter your first name: ";
	cin>>fn;
	cout<<"Enter your last name: ";
	cin>>ln;
	cout<<"Enter your given proof id: ";
	cin>>proof;
	cout<<"Number of rooms to be cancelled: ";
	cin>>n;
	s = search(proof);
	if(s=="0")
	 cout<<"No such customer is found"<<endl;
	 else{
	 	string nro,ty,Cd,Nd,nr;
	 	stringstream ss;
	 	ss<<"select nrooms,typ,chi,ndays from customer where pid = '"<<proof<<"'";
	 	string qu = ss.str();
		const char *u = qu.c_str();
		state = mysql_query(obj,u);
		if(!state){
			res = mysql_use_result(obj);
			while(row = mysql_fetch_row(res)){
				nro = row[0];
				ty = row[1];
				Cd = row[2];
				Nd = row[3];
			}
		}

		n1 = CI(nro);
		
		if(n1 == n){
			string mn;
			stringstream del;
			del<<"delete from customer where pid = '"<<proof<<"'";
			string d =del.str();
			const char *qd = d.c_str();
			state = mysql_query(obj,qd);
			
				stringstream lk;
				lk<<"delete from stay where pd ='"<<proof<<"'";
				string lk1 = lk.str();
				const char *lk2 = lk1.c_str();
				state = mysql_query(obj,lk2);
				
				int nd = CI(Nd);
				int Ty = CI(ty);
				string tY = findf(Ty);
				for(int i=0;i<nd;i++){
					string val;
					stringstream cl;
					cl<<"select "<<tY<<" from avail where chin = (select DATE_ADD('"<<Cd<<"',INTERVAL '"<<i<<"' DAY))";
					string Cl = cl.str();
					const char *cL = Cl.c_str();
					state = mysql_query(obj,cL);
					if(!state){
						res = mysql_use_result(obj);
						while(row = mysql_fetch_row(res)){
							val = row[0];
						}
					}
					int Val = CI(val);
					 Val = Val + n1;
					 val = CS(Val);
					 stringstream np;
					 np<<"update avail set "<<tY<<" = '"<<val<<"' where chin = (select DATE_ADD('"<<Cd<<"',INTERVAL '"<<i<<"' DAY))";
					 string Np = np.str();
					 const char *NP = Np.c_str();
					 state = mysql_query(obj,NP);
				}
				if(state == 0)
				cout<<"Cancelled successfully"<<endl;	
				else
				 cout<<"Something went wrong...";
				}
		else if(n < n1){
                int nd = CI(Nd);
				int Ty = CI(ty);
				string tY = findf(Ty);
				for(int i=0;i<nd;i++){
					string val;
					stringstream cl;
					cl<<"select "<<tY<<" from avail where chin = (select DATE_ADD('"<<Cd<<"',INTERVAL '"<<i<<"' DAY))";
					string Cl = cl.str();
					const char *cL = Cl.c_str();
					state = mysql_query(obj,cL);
					if(!state){
						res = mysql_use_result(obj);
						while(row = mysql_fetch_row(res)){
							val = row[0];
						}
					}
					int Val = CI(val);
					 Val = Val + n;
					 val = CS(Val);
					 stringstream np;
					 np<<"update avail set "<<tY<<" = '"<<val<<"' where chin = (select DATE_ADD('"<<Cd<<"',INTERVAL '"<<i<<"' DAY))";
					 string Np = np.str();
					 const char *NP = Np.c_str();
					 state = mysql_query(obj,NP);
				}
				n2 = n1 - n;
				nr = CS(n2);
				stringstream del;
			del<<"update customer set nrooms = '"<<nr<<"'where pid = '"<<proof<<"'";
			string d =del.str();
			const char *qd = d.c_str();
			state = mysql_query(obj,qd);
			
				stringstream lk;
				lk<<"delete from stay where pd ='"<<proof<<"' limit "<<n<<" ";
				string lk1 = lk.str();
				const char *lk2 = lk1.c_str();
				state = mysql_query(obj,lk2);
				
				if(state == 0)
				cout<<"Cancelled successfully"<<endl;
				else
				cout<<"Something went wrong..."<<endl;
		}
		else{
			cout<<"Invalid number of rooms"<<endl;
		}
	 }
}
//-------------------------------------------------------------
void checko(){         //Function for Checkout
	cout<<"----CHECKOUT-----"<<endl;
	cout<<"Enter first name: ";
	cin>>fn;
	cout<<"Enter last name: ";
	cin>>ln;
	cout<<"Enter proof: ";
	cin>>proof;
	string s = search(proof);
	if(s=="0"){
		cout<<"No such customer found"<<endl;
	}
	
	else{
		
		string nro,ty,Cd,Nd,addr,phn;
		stringstream ss;
	 	ss<<"select nrooms,typ,chi,ndays,address,phone from customer where pid = '"<<proof<<"'";
	 	string q = ss.str();
		const char *u = q.c_str();
		state = mysql_query(obj,u);
		if(!state){
			res = mysql_use_result(obj);
			while(row = mysql_fetch_row(res)){
				nro = row[0];
				ty = row[1];
				Cd = row[2];
				Nd = row[3];
			    addr = row[4];
				phn = row[5];
			}
		}
		        int n1 = CI(nro);
				 int nd = CI(Nd);
				 int Ty = CI(ty);
				string tY = findf(Ty);
				for(int i=0;i<nd;i++){
					string val;
					stringstream cl;
					cl<<"select "<<tY<<" from avail where chin = (select DATE_ADD('"<<Cd<<"',INTERVAL '"<<i<<"' DAY))";
					string Cl = cl.str();
					const char *cL = Cl.c_str();
					state = mysql_query(obj,cL);
					if(!state){
						res = mysql_use_result(obj);
						while(row = mysql_fetch_row(res)){
							val = row[0];
						}
					}
					int Val = CI(val);
					 Val = Val + n1;
					 val = CS(Val);
					 stringstream np;
					 np<<"update avail set "<<tY<<" = '"<<val<<"' where chin = (select DATE_ADD('"<<Cd<<"',INTERVAL '"<<i<<"' DAY))";
					 string Np = np.str();
					 const char *NP = Np.c_str();
					 state = mysql_query(obj,NP);
				}
				
		stringstream s;
		s<<"delete from customer where pid = '"<<proof<<"'";
		string d = s.str();
		const char *qd = d.c_str();
		state = mysql_query(obj,qd);
		
	    stringstream lk;
				lk<<"delete from stay where pd ='"<<proof<<"'";
				string lk1 = lk.str();
				const char *lk2 = lk1.c_str();
				state = mysql_query(obj,lk2);
				
	    if(state==0)
	     cout<<"Checked out successfully"<<endl;
	    else
	      cout<<"Something went wrong...";
	      
	      bill(fn,ln,phn,Cd,addr,Ty,n1,nd);
	      	string fd;
		cout<<"Would you like to give your feedback about our services?(y or n): "<<endl;
		cin>>fd;
		if(fd == "y"|| fd== "Y"){feed();}
}
}
//-----------------------------------------------------------------------------------
void bill(string fn,string ln,string phn,string Cd,string addr,int Ty,int n1,int nd){       // Function which prints the bill
	    srand(time(0));
    int v = rand()%1000 +1;
    string name = fn+ln;
    int m = 0;
    cout<<endl;
        cout<<"--------------------------"<<endl;
    cout<<"---XYZ HOTEL---"<<endl;
    cout<<"----------------"<<endl;
    cout<<"Bill To          "<<name<<"  "<<"Receipt Number  "<<v<<endl;
    cout<<"Phone Number     "<<phn<<"    "<<"checkin date    "<<Cd<<endl;
    cout<<"Address          "<<addr<<endl;
    cout<<"Payment Method: "<<"Cash"<<endl;
    if(Ty==100){
    cout<<"Type of Room: "<<"Normal Room"<<endl;
     m=1000;}
     if(Ty==200){
         cout<<"Type of Room: "<<"Queen Room"<<endl;
     m=1500;}
     if(Ty==300){
         cout<<"Type of Room: "<<"King Room"<<endl;
     m= 2100;}
     if(Ty==400){
         cout<<"Type of Room: "<<"Apartment"<<endl;
     m = 3700;}
     if(Ty==500){
         cout<<"Type of Room: "<<"Deluxe Room"<<endl;
     m=4000;}
     cout<<"Number of Rooms: "<<n1<<endl;
     cout<<"Number of nights: "<<nd<<endl;
     cout<<"Price per night(Rs): "<<m<<endl;
     double l =n1*nd*m + (n1*nd*m)*0.18;
     cout<<"Total Amount(Rs): "<<l<<endl;
    cout<<"**NOTE: Prices includes Room serivces and GST"<<endl;
    cout<<"--------------------------"<<endl;
  
}
//-------------------------------------------------------------------
void Food(){           //Function which displays Food Menu
    cout<<endl;
    cout<<"---------MENU---------"<<endl;
    cout<<"1) Idli"<<endl;
    cout<<"2) Dosa"<<endl;
    cout<<"3) Fried rice"<<endl;
    cout<<"4) Chappati"<<endl;
    cout<<"5) Briyani chicken"<<endl;
    cout<<"6) Veg-Briyani"<<endl;
    cout<<"9) Juices"<<endl;
    cout<<"10 Icecreams"<<endl;
    cout<<"----------------------"<<endl;
    cout<<"Note: Bill for food should be payed after eating"<<endl;
    cout<<"----------------------"<<endl;
}
//------------------------------------------------------------------
void det(){                        // Function which prints customer details
	string f,l;
	int id;
	cout<<"Enter First name: ";
	cin>>f;
	cout<<"Enter last name: ";
	cin>>l;
	cout<<"Enter given proof id: ";
	cin>>id;
	cout<<endl;
	cout<<"------------DETAILS------------"<<endl;
       s = search(id);
		   if(s=="1"){
		   stringstream s;
		   s<<"select address,phone,age from customer where pid = '"<<id<<"'";
		   string qu = s.str();
		   const char *u = qu.c_str();
		   state = mysql_query(obj,u);
		if(!state){
			res = mysql_store_result(obj);
			cout<<"Name: "<<f<<" "<<l<<endl;
			while(row = mysql_fetch_row(res)){
			cout<<"Address: "<<row[0]<<endl;
			cout<<"phone number: "<<row[1]<<endl;
			cout<<"Age: "<<row[2]<<endl;	
			}
		}
		stringstream ss;
		ss<<"select roo from stay where pd = '"<<id<<"'";
		string query = ss.str();
		const char *q = query.c_str();
		state = mysql_query(obj,q);
		if(!state){
			res = mysql_use_result(obj);
			cout<<"Alloted Room Numbers: ";
			while((row = mysql_fetch_row(res))!=NULL){
				cout<<row[0]<<" ";
			}
		}
	}
	else{
		cout<<"No such customer found"<<endl;
	}
	cout<<endl;		
}
//------------------------------------------------------------------
void Charg(){                             // Function for prints charges
    cout<<"Type of Room"<<" |"<<"Price per Night(Rs)"<<endl;
    cout<<"-------------|-----------------------"<<endl;
    cout<<"Normal Room"<<"  |   "<<"1000"<<endl;
    cout<<"Queen Room"<<"   |   "<<"1500"<<endl;
    cout<<"King Room"<<"    |   "<<"2100"<<endl;
    cout<<"Apartment"<<"    |   "<<"3700"<<endl;
    cout<<"Deluxe Room"<<"  |   "<<"4000"<<endl;
}
//--------------------------------------------------------------------
int main(){                                                       //Main Function
	obj = mysql_init(0);
obj = mysql_real_connect(obj,"localhost","root","danny","HRA",3306,NULL,0);  // Forming conncetion with DB
 int n;
  do{
  cout<<"---------Welcome To XYZ----------"<<endl;
  cout<<"1) Room Booking    2) Room Cancellation"<<endl;
  cout<<"3) Check out       4) Food"<<endl; 
  cout<<"5) details         6) Charges"<<endl;
  cout<<"7) Exit"<<endl;
  cout<<endl;
  prt();
  cout<<"Enter your choice(as number): ";
  cin>>n;
switch(n){
    case 1: alloc();
            cout<<"Thank you for your visit"<<endl;
            cout<<endl;
            break;
    case 2: cancel();
            cout<<"Thank you for your visit"<<endl;
            cout<<endl;
            break;
    case 3: checko();
            cout<<"Thank you for your visit"<<endl;
            cout<<endl;
            break;
    case 4: Food();
            cout<<"Thank you for your visit"<<endl;
            cout<<endl;
            break;
    case 5: det();
            break;
    case 6: Charg();
            cout<<"Thank you for your visit"<<endl;
            cout<<endl;
            break;
    case 7: cout<<"Thank you for your visit"<<endl;
            break;
    default: cout<<"Incorrect option"<<endl;
}
  }while(n!=7);	
}
