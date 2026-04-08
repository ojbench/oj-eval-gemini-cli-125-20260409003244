#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_BUF = 1 << 20;
char buf[MAX_BUF], *p1 = buf, *p2 = buf;
inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline int read() {
    int x = 0;
    char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == EOF) return -1;
        ch = gc();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = gc();
    }
    return x;
}

struct Constraint {
    int i, j, e;
};

const int MAXN = 2000005;
Constraint constraints[MAXN];
int vars[MAXN * 2];
int parent_node[MAXN * 2];
int rank_node[MAXN * 2];

int find_set(int v) {
    int root = v;
    while (root != parent_node[root]) {
        root = parent_node[root];
    }
    int curr = v;
    while (curr != root) {
        int nxt = parent_node[curr];
        parent_node[curr] = root;
        curr = nxt;
    }
    return root;
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank_node[a] < rank_node[b]) {
            swap(a, b);
        }
        parent_node[b] = a;
        if (rank_node[a] == rank_node[b]) {
            rank_node[a]++;
        }
    }
}

void solve() {
    int n = read();
    if (n == -1) return;
    int num_vars = 0;
    for (int k = 0; k < n; ++k) {
        constraints[k].i = read();
        constraints[k].j = read();
        constraints[k].e = read();
        vars[num_vars++] = constraints[k].i;
        vars[num_vars++] = constraints[k].j;
    }
    
    sort(vars, vars + num_vars);
    num_vars = unique(vars, vars + num_vars) - vars;
    
    for (int k = 0; k < num_vars; ++k) {
        parent_node[k] = k;
        rank_node[k] = 0;
    }
    
    for (int k = 0; k < n; ++k) {
        if (constraints[k].e == 1) {
            int u = lower_bound(vars, vars + num_vars, constraints[k].i) - vars;
            int v = lower_bound(vars, vars + num_vars, constraints[k].j) - vars;
            union_sets(u, v);
        }
    }
    
    bool possible = true;
    for (int k = 0; k < n; ++k) {
        if (constraints[k].e == 0) {
            int u = lower_bound(vars, vars + num_vars, constraints[k].i) - vars;
            int v = lower_bound(vars, vars + num_vars, constraints[k].j) - vars;
            if (find_set(u) == find_set(v)) {
                possible = false;
                break;
            }
        }
    }
    
    if (possible) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

int main() {
    int t = read();
    if (t <= 0) return 0;
    while (t--) {
        solve();
    }
    return 0;
}
