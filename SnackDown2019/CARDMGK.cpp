/*
Author: Dung Tuan Le
University of Rochester
*/

#include <bits/stdc++.h>
#define fio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define FOR(i, l, r) for (int i=l; i<=r; i++)
#define REP(i, r, l) for (int i=r; i>=l; i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define eps 1e-9

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pii;
typedef pair<long, long> pll;
typedef pair<ll, ll> pllll;
typedef pair<ld, ld> Point;
typedef pair<Point, Point> line;
struct strLine { ld a, b, c; };

typedef vector<int> vi;
typedef vector<long> vl;
typedef vector<ll> vll;

const double pi = 3.141592653589793;

ll gcd(ll a, ll b) { return (b==0)?a:gcd(b, a%b); } 
ll lcm(ll a, ll b) { return (a*b)/gcd(a, b); }
ll max(ll a, ll b) { return (a>=b)?a:b; }
ll min(ll a, ll b) { return (a<=b)?a:b; }

#define maxn 100000+10
long a[maxn];

int main() {
	fio;
	
	long test_cases, anchor, n;
	cin >> test_cases;
	FOR(current_test, 1, test_cases) {
		cin >> n;
		FOR(i, 1, n) cin >> a[i];
		
		a[0] = 0;
		anchor = 0;
		REP(i, n - 1, 0)
			if (a[i] > a[i + 1]) {
				anchor = i + 1;
				break;
			}
		
		bool flag = true;
		FOR(i, 1, anchor - 1) {
			if (a[n] > a[i]) {
				flag = false;
				break;
			}
			if (i < anchor - 1 && a[i] > a[i + 1]) {
				flag = false;
				break;
			}
		} 
		
		cout << ((flag) ? "YES" : "NO") << "\n";
	}
	
	return 0;
}
