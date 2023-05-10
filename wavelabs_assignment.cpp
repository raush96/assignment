// Time complexity - O(V+E), where V is the number of vertices and E is the number of edges in the graph.
// space complexity - O(V+E)

#include <bits/stdc++.h>
using namespace std;

void dfs(int s, vector<bool>&vis, vector<int>adj[],int &ver,int &edges) {
    vis[s] = true;
    ver++;
    
    for(auto &it : adj[s]) {
        edges++;
        if(!vis[it])
            dfs(it, vis, adj,ver,edges);
    }
}
int solve(int n, vector<vector<int>>& connections) {
    // creating the adjacentry list
    vector<int> adj[n];
    for(auto &it : connections) {
        int u = it[0], v = it[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool>vis(n, false);
    vector<pair<int,int>>components;  // stores the number of vertices and no. of edges as a pair for each connected component in graph.
    for(int i=0;i<n;i++){
        if(!vis[i]){
            int ver=0,edges=0;
            dfs(i,vis,adj,ver,edges); // dfs to calculate the number of vertices and no. of edges for each component.
            components.push_back({ver,edges/2});
        }
    }
    
    // calulating the extra edges in each component
    int extra=0;
    for(int i=0;i<components.size();i++){
        extra+=(components[i].second-(components[i].first-1));
    }
    
    // if no.of extra edges is greater or equal than the number of connected components than (no. of component -1) is min operation required 
    // otherwise it is not possible to connect all the components directly so return -1
    if(extra>=components.size()-1) return components.size()-1;
    return -1;
    
}
int main() {
    // n -> number of workstations
    // m -> number of connections
	int n,m;
	cin>>n>>m;
	vector<vector<int>>connections;
	for(int i=0;i<m;i++){
	    int ai,bi;  // ai,bi edges 
	    cin>>ai>>bi;
	    connections.push_back({ai,bi});
	}
	cout<<solve(n,connections);
	return 0;
}