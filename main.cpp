//my group mate info
//name:Tien Dat Le, student id:a1730614
using namespace std;
#include<iostream>
#include<string>
#include<bits/stdc++.h>
#include <algorithm>
#include<ctgmath>


string Addition(string a, string b, int base){

  //if the size of a,b are equal, then dont need
  while(a.length()<b.length())
  {
		a.insert(0,"0");
	}
	while(b.length()<a.length())
  {
		b.insert(0,"0");
	}

  string result = "";
  int carry = 0;

  for (int i=a.length()-1; i>=0; i--)//reverse a,b
  {
    int sum = (a[i]-'0') + (b[i]-'0') +carry;//a[i]+b[i]+c //string to int
    result += sum%base + '0'; //add int to string
    carry = sum/base; //1 or 0
  }

  if (carry==1)
  {
    result += carry +'0';
  }

  reverse(result.begin(), result.end());

  while(result[0] == '0')//delete zero
  {
     result.replace(0,1,"");
  }

  return result;
}


string subtraction(string a, string b, int base)
{
// the subtraction part was helped by my group mate Tien Dat Le

  while(a.length()<b.length())
  {
		a.insert(0,"0");
	}
	while(b.length()<a.length())
  {
		b.insert(0,"0");
	}

  int carry = 0;
  string result;

  for (int i=a.length()-1; i>=0; i--)
  {

    int sub = (a[i]-'0') - (b[i]-'0') -carry;

    if (sub<0)
    {
      result += sub + base + '0';
      carry=1;
    }else{
      result += sub +'0';
      carry=0;
    }
  }

  reverse(result.begin(),result.end());
  return result;
}


string school_multiplication(string a,string b,int base)
{

  string final_result ="0";

  for (int i=a.length()-1; i>=0; i--)//89,78
  {
    string result = "0";
    string carry = "0";

    for(int j=b.length()-1; j>=0; j--)
    {
      int product = (a[i]-'0') * (b[j]-'0');//(1).9*8==72 9*7=63
      // cout<<"product:"<<product<<endl;   //(2).8*8==64 8*7=56
      //
      result.insert(1,to_string(product%base));//(1). 2, 3, insert 3 to 02 = 32  //(2).04 64

      carry.insert(0, to_string(product/base));//(1). 70, insert 6 to 70 = 670 //(2).60 560


     }

    result = Addition(result,carry,base);//(1).32+670=702 (2).64+560=624



    //pad '0'
    for (int p=0; p<a.length()-1-i; p++){
      result.append("0");  //result+= '0'; same
      //cout<<"pad'0:"<<result<<endl;//6240
    }
    final_result = Addition(result, final_result, base);//6240+702=6942
  }
  return final_result;

}


string Karatsuba(string a,string b, int base)
{

  if(a.length()<4 && b.length()<4)
  {
    return school_multiplication(a,b,base);
  }

  while(a.length()<b.length())
  {
    a.insert(0,"0");
  }
  while(b.length()<a.length())
  {
    b.insert(0,"0");
  }

  int split = a.length()/2;//after insert 0, the length of a and b will be same

	string a0 = a.substr(split);//8
	string a1 = a.substr(0,split);//9
	string b0 = b.substr(split);//7
	string b1 = b.substr(0,split);//8

	string p0 = Karatsuba(a0,b0,base);//8*7
	string p1 = Karatsuba(Addition(a0,a1,base),Addition(b0,b1,base),base);//(8+9)*(7+8)
	string p2 = Karatsuba(a1,b1,base);//9*8

  string middle = subtraction(p1, Addition(p0, p2, base), base);

  //number of zeroes to add
  int m = split+(a.length()%2);
  //cout<<m<<endl;

	for(int i = 0; i < m*2; i++)
  {
	  p2.append("0");
	}

	for(int i = 0; i < m; i++)
  {
		middle +='0';
	}
	return Addition(p2,Addition(p0,middle,base),base);
}

int main()
{
    string n[3];
  	int i = 0;
  	while(cin>>n[i])
    {
  		i = (i+1)%3;
  		if(i==0)
      {
  			cout<<Addition(n[0],n[1],stoi(n[2]))<<" ";
        cout<<Karatsuba(n[0],n[1],stoi(n[2]))<<endl;
  		}
  	}
    return 0;
}
