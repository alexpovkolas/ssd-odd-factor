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


void print_euler_path(vector<set<int>> &edges, vector<int> &result){
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
    cin >> n;

    vector<set<int>> edges(n + 1);
    vector<int> result;
    result.reserve(2*n-1);

    for (int i = 0; i < n - 1; ++i) {
        int vertex1 = 0;
        int vertex2 = 0;
        cin >> vertex1 >> vertex2;
        edges[vertex1].insert(vertex2);
        edges[vertex2].insert(vertex1);
    }

    print_euler_path(edges, result);

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }

#ifdef __PROFILE__

#endif

    cout << endl;

    return 0;
}
