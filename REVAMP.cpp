#include <bits/stdc++.h>
#define maxm 50000+10
#define maxn 10000+10
#define maxk 20+5
#define maxV 1000000000000
using namespace std;

typedef pair<int, int> ii;

struct node {
	int v, next;
	long long c;
};

node graph[2*maxm];
int n, k;
long long d[maxn][maxk];
int head[maxn];
bool check[maxn][maxk];

long long min(long long a, long long b) {
	if (a<=b) return a;
	else return b;
}

bool smaller(ii u, ii v) {
	if (d[u.first][u.second]<d[v.first][v.second]) return true;
	else return false;
}

class pq {
	public: 
		ii heap[15*maxn];
		int cs[maxn][maxk];
		int heapSize;
	
	void init() {
		heapSize = 0;
		for (int i=1; i<=n; i++)
			for (int j=0; j<=k; j++)
				cs[i][j] = 0;
	}
	
	void update(ii p) {
		if (cs[p.first][p.second]==0) {
			heapSize++;
			heap[heapSize] = p;
			cs[p.first][p.second] = heapSize;
		}
		upHeap(cs[p.first][p.second]);
	}
	
	void upHeap(int index) {
		ii temp = heap[index];
		while (true) {
			int parent = index/2;
			if (parent ==0 || !smaller(temp,heap[parent])) break;
			heap[index] = heap[parent];
			cs[heap[index].first][heap[index].second] = index;
			index = parent;
		}
		heap[index] = temp;
		cs[heap[index].first][heap[index].second] = index;
	}
	
	ii peek() {
		return heap[1];
	}
	
	void poll() {
		cs[heap[1].first][heap[1].second] = 0;
		cs[heap[heapSize].first][heap[heapSize].second] = 1;
		heap[1] = heap[heapSize];
		heapSize--;
		downHeap(1);
	}
	
	void downHeap(int index) {
		ii temp = heap[index];
		while (true) {
			int child = index*2;
			if (child<heapSize && smaller(heap[child+1], heap[child])) child++;
			if (child>heapSize || !smaller(heap[child], temp)) break;
			heap[index] = heap[child];
			cs[heap[index].first][heap[index].second] = index;
			index = child;
		}
		heap[index] = temp;
		cs[heap[index].first][heap[index].second] = index;
	}
	
	bool empty() {
		return (heapSize==0);
	}
};

void dijkstra() {
	int v;
	long long res;
	for (int i=1; i<=n; i++) {
		for (int j=0; j<=k; j++) d[i][j] = maxV;
	}
	pq q;
	q.init();
	d[1][0] = 0;
	q.update(make_pair(1, 0));
	while (!q.empty()) {
		ii u = q.peek();
		q.poll();
		check[u.first][u.second] = false;
		int i = head[u.first];
		while (i!=0) {
			v = graph[i].v;
			for (int j=0; j<=1; j++) {
				if (u.second+j<=k && check[v][u.second+j]&&d[v][u.second+j]>d[u.first][u.second]+graph[i].c*(1-j)) {
					d[v][u.second+j] = d[u.first][u.second]+graph[i].c*(1-j);
					q.update(make_pair(v, u.second+j));
				}	
			}
			i = graph[i].next;
		}
	}
	res = maxV;
	for (int j=0; j<=k; j++) 
		res = min(res, d[n][j]);
	cout << res;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int m, u, v;
	long long c;
	cin >> n >> m >> k;
	for (int i=1; i<=m;  i++) {
		cin >> u >> v >> c;
		graph[2*i].v = v;
		graph[2*i].c = c;
		graph[2*i].next = head[u];
		head[u] = 2*i;
		
		graph[2*i+1].v = u;
		graph[2*i+1].c = c;
		graph[2*i+1].next = head[v];
		head[v] = 2*i+1;
	}
	for (int i=1; i<=n; i++) {
		for (int j=0; j<=k; j++) check[i][j] = true;
	}
	dijkstra();
	return 0;
}
