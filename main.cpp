#include <iostream>
#include <vector>
#import <stack>
#include <algorithm>
#import <set>


#define __PROFILE__

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
bool find_odd_factor(vector<set<vertex>> &edges, vector<pair<vertex, vertex>> &result, set<vertex> &visited, vertex root){
    stack<pair<vertex, vertex>> path;
    vector<int> factors(edges.size());

    if (edges[root].empty()) {
        return false;
    } else {
        path.push(make_pair(-1, root));
        visited.insert(root);
    }

    while (!path.empty()) {

        pair<vertex, vertex> top = path.top();
        vertex current = top.second;

        // check if we have unvisited vertices
        vector<vertex> unvisited;
        set_difference(edges[current].begin(), edges[current].end(), visited.begin(), visited.end(), back_inserter(unvisited));

        // remove edges to visited vertices
        vector<vertex> to_remove;
        set_intersection(edges[current].begin(), edges[current].end(), visited.begin(), visited.end(), back_inserter(to_remove));

        for (int i = 0; i < to_remove.size(); ++i) {
            edges[current].erase(to_remove[i]);
        }

        if (!unvisited.empty()) {
            for (int i = 0; i < unvisited.size(); ++i) {
                vertex unvisited_vertex = unvisited[i];
                path.push(make_pair(current, unvisited_vertex));
                visited.insert(unvisited_vertex);
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
    set<vertex> visited;

    int vertices_count = edges.size() - 1;
    vector<vertex> difference;
    for (int i = 1; i < edges.size(); ++i) {
        difference.push_back(i);
    }

    while ( !difference.empty() ) {
        if (find_odd_factor(edges, result, visited, *difference.begin())) {

            if (vertices_count != visited.size()) {
                vector<vertex> next_difference;
                set_difference(difference.begin(), difference.end(), visited.begin(), visited.end(), back_inserter(difference));
                difference = next_difference;
            } else {
                return true;
            }

        } else {
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
