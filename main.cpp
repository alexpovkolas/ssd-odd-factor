#include <iostream>
#include <vector>
#import <stack>
#import <set>


//#define __PROFILE__

#ifdef __PROFILE__

#include <cstdio>
#include <fstream>

#endif

using namespace std;


bool find_odd_factor(vector<set<int>> &edges, vector<pair<int, int>> &result){
    int root = 0;
    stack<int> st;

    for (int i = 0; i < edges.size(); ++i) {
        if (!edges[i].empty()) {
            root = i;
            break;
        }
    }
    st.push(root);

    while (!st.empty()) {

        int top = st.top();
        result.push_back(top);

        if (edges[top].empty()) {
            st.pop();
        } else {
            int next = *edges[top].begin();
            st.push(next);
            edges[top].erase(edges[top].begin());
            edges[next].erase(top);
        }
    }
}

int main() {
#ifdef __PROFILE__
    ifstream in("input");
    cin.rdbuf(in.rdbuf());
#endif

    int n = 0;
    int m = 0;
    cin >> n >> m;

    vector<set<int>> edges(n);
    vector<pair<int, int>> result;

    for (int i = 0; i < m; ++i) {
        int vertex1 = 0;
        int vertex2 = 0;
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
