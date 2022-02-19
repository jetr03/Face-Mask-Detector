#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
const ll mod = 1e9 + 7;
long long gcd(long long int a, long long int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
long long lcm(ll a, ll b)
{
    return (a / gcd(a, b)) * b;
}
bool isPrime(int x) {
    if(x<2){
        return false;
    }
    for (int d = 2; d * d <= x; d++) {
        if (x % d == 0)
            return false;
    }
    return true;
}
ll nCrModp(ll n, ll r, ll p)
{
    // Optimization for the cases when r is large
    if (r > n - r)
        r = n - r;
 
    // The array C is going to store last row of
    // pascal triangle at the end. And last entry
    // of last row is nCr
    ll C[r + 1];
    memset(C, 0, sizeof(C));
 
    C[0] = 1; // Top row of Pascal Triangle
 
    // One by constructs remaining rows of Pascal
    // Triangle from top to bottom
    for (ll i = 1; i <= n; i++) {
 
        // Fill entries of current row using previous
        // row values
        for (ll j = min(i, r); j > 0; j--)
 
            // nCj = (n-1)Cj + (n-1)C(j-1);
            C[j] = (C[j] + C[j - 1]) % p;
    }
    return C[r];
}
ll printNcR(ll n, ll r)
{
 
    long long p = 1, k = 1;
    if (n - r < r)
        r = n - r;
 
    if (r != 0) {
        while (r) {
            p *= n;
            k *= r;
            long long m = __gcd(p, k);
            p /= m;
            k /= m;
            n--;
            r--;
        }
    }
 
    else
        p = 1;
 
    return p;
}
ll modFact(ll n, ll p)
{
    if (n >= p)
        return 0;
 
    ll result = 1;
    for (int i = 1; i <= n; i++)
        result = (result * i) % p;
 
    return result;
}
ll modPow(ll a, ll x, ll p) {
    //calculates a^x mod p in logarithmic time.
    ll res = 1;
    while(x > 0) {
        if( x % 2 != 0) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        x /= 2;
    }
    return res;
}
 
ll modInverse(ll a, ll p) {
    //calculates the modular multiplicative of a mod m.
    //(assuming p is prime).
    return modPow(a, p-2, p);
}
ll modBinomial(ll n, ll k, ll p) {
// calculates C(n,k) mod p (assuming p is prime).
 
    ll numerator = 1; // n * (n-1) * ... * (n-k+1)
    for (ll i=0; i<k; i++) {
        numerator = (numerator * (n-i) ) % p;
    }
 
    ll denominator = 1; // k!
    for (ll i=1; i<=k; i++) {
        denominator = (denominator * i) % p;
    }
 
    // numerator / denominator mod p.
    return ( numerator* modInverse(denominator,p) ) % p;
}
int power(long long x, unsigned int y, int p)
{
    int res = 1;     // Initialize result
 
    x = x % p; // Update x if it is more than or
                // equal to p
  
    if (x == 0) return 0; // In case x is divisible by p;
 
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}
set<int> all_primes(){
    const int N = 1000;
    vector<int> lp(N+1);
    vector<int> pr;
    for (int i=2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.pb(i);
        }
        for (int j=0; j < (int)pr.size() && pr[j] <= lp[i] && i*pr[j] <= N; ++j) {
            lp[i * pr[j]] = pr[j];
        }
    }
    set<int> s;
    for(auto x : pr){
        s.insert(x);
    }
    return s;
}
string decToBinary(ll n)
{
    string s = bitset<64> (n).to_string();
    if(s.size()<10){
        while(s.size()!=10){
            s+='0';
        }
    }
    return s;
} 
 
ll binaryToDecimal(string n)
{
    string num = n;
    ll dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    ll base = 1;
 
    ll len = num.length();
    for (ll i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
 
    return dec_value;
}

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    set<int> s = all_primes();
    int a,b,c,d;
    int aoki=0;
    cin>>a>>b>>c>>d;
    for(int i=a;i<=b;i++){
        for(int j=c;j<=d;j++){
            if(s.find(i+j)!=s.end()){
                aoki++;
                break;
            }
        }
    }
    if(aoki>=b-a+1){
        cout<<"Aoki";
    }else{
        cout<<"Takahashi";
    }

 
}