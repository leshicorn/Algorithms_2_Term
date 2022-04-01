#include <bits/stdc++.h>

using namespace std;


string fractionToDecimal(long a, long b) {
	//base case
    if(a==0) return "0";
    string res;
	//checking if either of the numerator or denominator is negitive
    if(a<0 ^ b<0) res='-'+res;
    a=abs(a);
    b=abs(b);
	//append the result of a/b to string
    res+=to_string(a/b);
    //cout << (double)a / (double)b << endl << endl;
	//If there is remainder for a/b then decimal point exists
    if(a%b==0) return res;
    res+=".";
    long rem=a%b;
	//map to store the index of occurance particular remainder
	//If the same remainder is seen again we will use the first occuarance of that remainder and put in paranthesis indicating that sequence is repeating
    unordered_map<long,long> m;
    while(rem){
        if(m.find(rem)!=m.end()){
            res.insert(res.begin()+m[rem],'(');
            res.push_back(')');
            break;
        }
        m[rem]=res.size();
        rem*=10;
        res+=to_string(rem/b);
        rem=rem%b;
    }
    return res;
}

int main(){
   string res;
   unsigned long long n = 0, m = 0;
   cin >> n >> m;
   res = fractionToDecimal(n, m);
   cout << res << endl;
}