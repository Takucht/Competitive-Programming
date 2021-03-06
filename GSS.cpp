#include <bits/stdc++.h>
#define maxn 50000+10
using namespace std;

struct node {
	int sum;//tong cac phan tu trong doan (u,v)
	int sumMax;//tong lon nhat cac phan tu lien tiep trong (u,v)
	int left, right;//tong lon nhat cac phan tu nam ben trai nhat/phai nhat trong (u,v)
};

node it[4*maxn];
int a[maxn];
int n;

int max(int a, int b) {
	if (a>=b) return a;
	else return b;
}

void update(int cs, int u, int v) {
	if (u==v) {
		it[cs].sum = a[u];
		it[cs].sumMax = a[u];
		it[cs].left = a[u];
		it[cs].right = a[u];
		return;
	}
	int mid = (u+v)/2;
	update(2*cs, u, mid);
	update(2*cs+1, mid+1, v);
	it[cs].sum = it[2*cs].sum + it[2*cs+1].sum;
	it[cs].left = max(it[2*cs].left, it[2*cs].sum+it[2*cs+1].left);
	it[cs].right = max(it[2*cs+1].right, it[2*cs+1].sum+it[2*cs].right);
	it[cs].sumMax = max(max(it[2*cs].sumMax, it[2*cs+1].sumMax), it[2*cs].right+it[2*cs+1].left);
}

node getSumMax(int cs, int u, int v, int l, int r) {
	node temp;
	if (r<u || v<l) {
		temp.sum = 0;
		temp.left = -1000000000;
		temp.right = -1000000000;
		temp.sumMax = -1000000000;
		return temp;
	}
	if (l<=u && v<=r) return it[cs];
	int mid = (u+v)/2;
	node left = getSumMax(2*cs, u, mid, l, r);
	node right = getSumMax(2*cs+1, mid+1, v, l, r);
	temp.sum = left.sum + right.sum;
	temp.left = max(left.left, left.sum+right.left);
	temp.right = max(right.right, right.sum+left.right);
	temp.sumMax = max(max(left.sumMax, right.sumMax), left.right+right.left);
	return temp;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int m, l , r;
	cin >> n;
	for (int i=1; i<=n; i++) cin >> a[i];
	update(1, 1, n);
	cin >> m;
	for (int i=1; i<=m; i++) {
		cin >> l >> r;
		cout <<getSumMax(1, 1, n, l, r).sumMax << endl;
	}
	return 0;
}
