#include <iostream>
#include <vector>
#import <stack>
#include <algorithm>
#import <set>


//#define __PROFILE__

#ifdef __PROFILE__

#include <cstdio>
#include <fstream>

#endif

typedef unsigned int vertex;

using namespace std;

#ifdef __PROFILE__

void print_set(const set<vertex> &vertices, const string &name){
    cout << name << " size - " << vertices.size() << endl;
    for (auto v = vertices.begin(); v != vertices.end(); ++v){
        cout << *v << endl;
    }
}

#endif

// find odd factor for connected component with "root"
bool find_odd_factor(vector<set<vertex>> &edges, vector<pair<vertex, vertex>> &result, set<vertex> &unvisited, vector<int> &factors){
    stack<pair<vertex, vertex>> path;

    vertex root = *unvisited.begin();
    if (edges[root].empty()) {
        return false;
    } else {
        path.push(make_pair(-1, root));
        unvisited.erase(root);
    }

    while (!path.empty()) {

        pair<vertex, vertex> top = path.top();
        vertex current = top.second;

        // check if we have unvisited vertices
        vector<vertex> vertices_to_visit;
        set_intersection(edges[current].begin(), edges[current].end(), unvisited.begin(), unvisited.end(), back_inserter(vertices_to_visit));

        if (!vertices_to_visit.empty()) {
            for (int i = 0; i < vertices_to_visit.size(); ++i) {
                vertex vertex_to_visit = vertices_to_visit[i];
                path.push(make_pair(current, vertex_to_visit));
                unvisited.erase(vertex_to_visit);
            }
        } else {
            path.pop();
            if (path.empty()) {
                return factors[top.second] % 2 == 1;
            }

            int factor = factors[current];
            if (factor % 2 == 0) {
                result.push_back(top);
                factors[top.first]++;
            }
        }
    }

    return false;
}

bool find_odd_factor(vector<set<vertex>> &edges, vector<pair<vertex, vertex>> &result){
    set<vertex> unvisited;
    vector<int> factors(edges.size());
    for (int i = 1; i < edges.size(); ++i) {
        unvisited.insert(i);
    }

    int root = 1;
    // for each connected component
    while ( !unvisited.empty() ) {
        if (!find_odd_factor(edges, result, unvisited, factors)) {
            return false;
        }
    }

    return true;
}

int main() {
#ifdef __PROFILE__
    ifstream in("input");
    cin.rdbuf(in.rdbuf());
#endif

    int n = 0;
    int m = 0;
    cin >> n >> m;

    // first vertex has index 1
    vector<set<vertex>> edges(n + 1);
    vector<pair<vertex, vertex>> result;

    for (int i = 0; i < m; ++i) {
        vertex vertex1 = 0;
        vertex vertex2 = 0;
        cin >> vertex1 >> vertex2;
        edges[vertex1].insert(vertex2);
        edges[vertex2].insert(vertex1);
    }


    if (find_odd_factor(edges, result)) {
        cout << result.size() << endl;
        for (int i = 0; i < result.size(); ++i) {
            cout << result[i].first << " " << result[i].second << endl;
        }
    } else {
        cout << -1 << endl;
    };

    return 0;
}