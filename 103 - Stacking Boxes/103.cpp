#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <deque>
#include <climits>

using namespace std;

struct Box
{
	int id;
	vector<int> ds;
};

struct Edge
{
	Edge(const int &x, const int &y, const int &w) : 
		x(x), y(y), weight(w) {}

	int x, y, weight;
};

class EdgeWeightedDigraph
{
public:
    EdgeWeightedDigraph(const int &v) : m_v(v)
    {
        m_g.reserve(m_v);
        for (int i = 0; i < m_v; ++i) m_g.push_back({});
    }
    
    ~EdgeWeightedDigraph() { for (auto ed : edges) delete ed; }
    
    void addEdge(Edge *ed) 
    { 
		edges.push_back(ed);

		m_g[ed->x].push_back(ed);
	}
    
    vector<Edge*> adj(const int &v) const { return m_g[v]; }
    
    int size() const { return m_v; }
    
    void print() 
    {
        for (int i = 0; i < m_v; ++i) {
            cout << i << " : ";
            for (const auto &ed : adj(i)) cout << ed->y << "(" << ed->weight << ") ";
             
            cout << endl;
        }
    }
    
private:
    const int m_v;
    vector< vector<Edge*> > m_g;
    vector<Edge*> edges;
};

class Topological 
{
public:
	Topological(const EdgeWeightedDigraph &g)
	{
		for (int i = 0; i < g.size(); ++i) {
			marked.push_back(false);
		}
		
		for (int u = 0; u < g.size(); ++u) {
			if (!marked[u]) dfs(g, u);
		}
	}

	deque<int> order; // used as stack
	
private:
	void dfs(const EdgeWeightedDigraph &g, const int &v)
	{
		marked[v] = true;
		
		for (const auto w : g.adj(v)) {
			if (!marked[w->y]) {
				dfs(g, w->y);
			}
		}
		
		order.push_front(v);
	}

	vector<bool> marked;
};

class AcyclicSP
{
public:
	AcyclicSP(EdgeWeightedDigraph &g, int source)
	{
		edgeTo.reserve(g.size());
		distTo.reserve(g.size());
		
		for (int i = 0; i < g.size(); i++) {
			edgeTo.push_back(nullptr);
			distTo.push_back(INT_MAX);
		}
		
		distTo[source] = 0;
		
		Topological topo(g);
		
		for (const auto &v : topo.order) {
			for (const auto ed : g.adj(v)) relax(ed);
		}
	}
	
	int distanceTo(const int &v) const { return distTo[v]; }
	
	deque<Edge*> pathTo(const int &v)
	{
		deque<Edge*> path;
		
		for (auto ed = edgeTo[v]; ed != nullptr; ed = edgeTo[ed->x]) {
			path.push_front(ed);
		}
		
		return path;
	}
	
private:
	void relax(Edge *ed)
	{
		if (distTo[ed->y] > distTo[ed->x] + ed->weight) {
			distTo[ed->y] = distTo[ed->x] + ed->weight;
			edgeTo[ed->y] = ed;
		}
	}

	vector<Edge*> edgeTo;
	vector<int> distTo;
};

bool canFit(Box *a, Box *b)
{
	auto itr = b->ds.begin();
	
	for (auto &m : a->ds) {
		if (*itr <= m) return false;
		itr++;
	}
	
	return true;
}

int main()
{
    int k, n; 
    
    while (cin >> k >> n) {
		vector<Box*> boxes;
		int c, m, p;
		
		c = 1;
		p = k;
		
		/** add and sort boxes **/
		while (p--) {
			Box *b = new Box();
			boxes.push_back(b);
			
			b->id = c++;
			for (int i = 0; i < n; i++) {
				cin >> m;
				b->ds.push_back(m);
			}
			
			sort(b->ds.begin(), b->ds.end());
		}
		
		sort(boxes.begin(), boxes.end(), [](Box *a, Box *b)->bool { return a->ds < b->ds; });
		
		/** add edges to digraph **/
		EdgeWeightedDigraph g(k+2);
		
		int last = boxes.size()-1;
		for (int i = 0; i < last; i++) {
			for (int j = i+1; j < boxes.size(); j++) {
				if (canFit(boxes[i], boxes[j])) {
					g.addEdge(new Edge(boxes[i]->id, boxes[j]->id, -1));
				}
			}
		}
		
		// add edges to source (start) and sink (end) vertex
		for (int i = 1; i < k+1; i++) {
			g.addEdge(new Edge(0, i, 0)); 
			g.addEdge(new Edge(i, k+1, 0));
		}
		
		//~ g.print(); cout << endl;
		
		/** find the longest path **/
		AcyclicSP asp(g, 0);
		auto path = asp.pathTo(k+1); // last vert in graph is k+1
		
		// when we print we don't include the last vert
		p = path.size() - 1;
		cout << p << endl;
		for (auto ed : path) if (p--) cout << ed->y << " ";
		cout << endl;
		
		for (auto b : boxes) { 
			//~ cout << b->id << ": ";
			//~ for (auto &r : b->ds) cout << r << " ";
			//~ cout << endl;
			delete b; 
		}
	}
}
