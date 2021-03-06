#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N=5e4;

struct point
{
	int p,d;
};

vector<point> saveSon[N+1];
int D[N+1],dist[N+1];   // D為子節點數 dist存距離
int minNode,min0=987654321;
int tmp,n,k,ans;
bool visit[N+1];

void dfs(int now,int father,int size0) //找重心
{
	D[now]=1;
	int minTreeNode=0;

	for(int i=0;i<saveSon[now].size();i++)
	{
		if(saveSon[now][i].p!=father && !visit[saveSon[now][i].p])
		{
			dfs(saveSon[now][i].p,now,size0);

			D[now]+=D[saveSon[now][i].p];
			minTreeNode=max(minTreeNode,D[saveSon[now][i].p]);
		}
	}

	minTreeNode=max(minTreeNode,size0-D[now]);

	if(minTreeNode<min0)
	{
		min0=minTreeNode;

		minNode=now;
	}
}

void dSearch(int now,int father,int NowDistance) //子樹中每點到根的距離
{
	dist[tmp]=NowDistance;
	tmp++;

	for(int i=0;i<saveSon[now].size();i++)
		if(!visit[saveSon[now][i].p] && saveSon[now][i].p!=father)
			dSearch(saveSon[now][i].p,now,NowDistance+saveSon[now][i].d);
}

int cal(int root,int x) //計算符合的個數
{
	int ans0=0;
	tmp=0;

	dSearch(root,0,x);

	sort(dist,dist+tmp);

	int i=0,j=tmp-1;

	while(j>i)
	{
		while(dist[i]+dist[j]>k && j>i)
		{
			j--;
		}

        //if(j>i)
            ans0+=j-i;

		i++;
	}


	return ans0;
}

void solve(int u,int size0)  //處理中心
{
	tmp=0;
	min0=987654321;

	dfs(u,0,size0);

	ans+=cal(minNode,0);
	visit[minNode]=true;

	for(int i=0;i<saveSon[u].size();i++)
	{
		if(!visit[saveSon[u][i].p])
		{
			ans-=cal(saveSon[u][i].p,saveSon[u][i].d);

			solve(saveSon[u][i].p,D[saveSon[u][i].p]);
		}
	}
}

int main()
{
	int t;

	while(cin >> n >> k && n!=0)
	{
		for(int i=0;i<=n;i++)
        {
            visit[i]=false;
            D[i]=0;
            dist[i]=0;
            saveSon[i].clear();
        }


		for(int i=0;i<n-1;i++)
		{
			int u,v,l;

			cin >> u >> v >> l;

			point tmp; tmp.p=v; tmp.d=l;

			saveSon[u].push_back(tmp);
			tmp.p=u;
			saveSon[v].push_back(tmp);
		}

		ans=0;

		solve(1,n);

		cout << ans << endl;

	}

	return 0;
}
