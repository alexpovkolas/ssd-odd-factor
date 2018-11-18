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


void unvisited_vertices(const set<vertex> &edges, const set<vertex> &visited, vector<vertex> &unvisited) {
    set<vertex> difference;
    set_difference(visited.begin(), visited.end(), edges.begin(), edges.end(), inserter(difference, difference.begin()));
    set_intersection(edges.begin(), edges.end(), difference.begin(), difference.end(), back_inserter(unvisited));
}

// find odd factor for connected component with "root"
bool find_odd_factor(vector<set<vertex>> &edges, vector<pair<vertex, vertex>> &result, set<vertex> visited, vertex root){
    stack<pair<vertex, vertex>> path;
    vector<int> factors(edges.size());

    if (edges[root].empty()) {
        return false;
    } else {
        path.push(make_pair(-1, root));
    }

    while (!path.empty()) {

        pair<vertex, vertex> top = path.top();
        vertex current = top.second;


        // check if we have unvisited vertices
        vector<vertex> unvisited;
        unvisited_vertices(edges[current], visited, unvisited);

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

    set<vertex> all_vertices;
    for (int i = 0; i < edges.size(); ++i) {
        all_vertices.insert(i);
    }

    vector<vertex> difference;
    difference.push_back(1);

    // for each connected component
    while ( !difference.empty() ) {
        if (find_odd_factor(edges, result, visited, *difference.begin())) {
            difference.resize(0);
            set_difference(visited.begin(), visited.end(), all_vertices.begin(), all_vertices.end(), back_inserter(difference));
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
