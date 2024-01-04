#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;

    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int find_set(vector<int>& parent, int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent, parent[v]);
}

void union_sets(vector<int>& parent, vector<int>& rank, int a, int b) {
    a = find_set(parent, a);
    b = find_set(parent, b);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

void make_set(vector<int>& parent, vector<int>& rank, int v) {
    parent[v] = v;
    rank[v] = 0;
}

int main() {
    vector<Edge> edges;
    edges.push_back({ 0, 1, 2 });//AB 0 1 2 3 4 5 6
    edges.push_back({ 1, 4, 3 });//BE A B C D E F G
    edges.push_back({ 4, 6, 7 });//EG
    edges.push_back({ 5, 6, 6 });//GF
    edges.push_back({ 3, 5, 1 });//FD
    edges.push_back({ 2, 5, 6 });//FC
    edges.push_back({ 0, 2, 4 });//AC
    edges.push_back({ 0, 3, 7 });//AD
    edges.push_back({ 3, 6, 6 });//DG
    edges.push_back({ 1, 6, 8 });//GB
    edges.push_back({ 1, 3, 6 });//DB
    edges.push_back({ 0, 5, 5 });//AF

    int n = 7;
    vector<int> parent(n), rank(n);
    for (int i = 0; i < n; i++) {
        make_set(parent, rank, i);
    }

    sort(edges.begin(), edges.end());

    int cost = 0;
    vector<Edge> result;
    for (Edge e : edges) {
        if (find_set(parent, e.u) != find_set(parent, e.v)) {
            cost += e.weight;
            result.push_back(e);
            union_sets(parent, rank, e.u, e.v);
        }
    }

    cout << "Минимальное остовное дерево: " << cost << endl;
}