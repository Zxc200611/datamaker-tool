#pragma once
#include<bits/stdc++.h>
using namespace std;
mt19937_64 Rand;
char inFile[1024],outFile[1024];
char cmd[1024];
char problemName[1024];
inline
void init(string filename="",int dataId=-1)
{
	freopen("gen.cfg","r",stdin);
	int g=0;
	cin>>g;
	freopen("gen.cfg","w",stdout);
	cout<<g+1<<endl;
	Rand=mt19937_64(g);
	if(dataId!=-1)
	{
		sprintf(inFile,"%s%d.in",filename.c_str(),dataId);
		sprintf(problemName,"%s",filename.c_str());
		freopen(inFile,"w",stdout);
		return;
	}
	freopen("data.in","w",stdout);
}
inline
void genOut(int dataId)
{
	fclose(stdout);
	sprintf(cmd,"./%s.lexe < %s%d.in > %s%d.out",problemName,problemName,dataId,problemName,dataId);
	system(cmd);
}
#define int long long
inline
int randNum(int minLimit,int maxLimit)
{
	if(minLimit==maxLimit)
		return minLimit;
	return minLimit+Rand()%(maxLimit-minLimit+1);
}
inline
pair<int,int> randInterval(int minLimit,int maxLimit)
{
	int n=maxLimit-minLimit+1;
	int l=randNum(1,n),r=randNum(1,n);
	if(r<=l)
		swap(l,r);
	return make_pair(minLimit+l-1,minLimit+r-1);
}
inline
vector<int> randSplit(int n,int sum,int minLimit=0,int maxLimit=2139062143)
{
	vector<int> ans;
	ans.clear();
	sum-=n*minLimit;
	if(sum<0||maxLimit<minLimit)
		return ans;
	maxLimit-=minLimit;
	for(int i=1;i<=n;i++)
	{
		ans.push_back(minLimit+(i==n?sum:randNum(max(0LL,sum-1LL*maxLimit*(n-i)),min(maxLimit,2*sum/(n-i+1)))));
		sum-=(ans[i-1]-minLimit);
	}
	shuffle(ans.begin(),ans.end(),Rand);
	return ans;
}
inline
vector<int> pruferDecode(vector<int> prf,int n)
{
	vector<int> fth(n+1),deg(n+1,1);
	for(int i=1;i<prf.size();i++)
		deg[prf[i]]+=1;
	int u=1;
	for(int i=1;i<prf.size();)
	{
		while(deg[u]!=1)
			u++;
		if(u==n)
			break;
		int v=u;
		while(deg[v]==1)
		{
			fth[v]=prf[i];
			deg[v]--;
			deg[prf[i]]--;
			i++;
			if(i==prf.size()||prf[i-1]>u)
				break;
			v=prf[i-1];
		}
	}
	fth[prf.back()]=n;
	return fth;
}
void orderTree(vector<vector<int>> &t,int u,int f,vector<vector<int>> &ans)
{
	for(int i=0;i<t[u].size();i++)
	{
		int v=t[u][i];
		if(v==f)
			continue;
		ans[u].push_back(v);
		orderTree(t,v,u,ans);
	}
}
inline
vector<vector<int>> randTree(int n)
{
	vector<int> prf(1,0);
	vector<vector<int>> t(n+1,vector<int>(0));
	for(int i=1;i<=n-2;i++)
		prf.push_back(randNum(1,n));
	vector<int> fth=pruferDecode(prf,n);
	for(int i=n;i>=1;i--)
	{	
		if(fth[i]==0)
			continue;
		t[fth[i]].push_back(i);
		t[i].push_back(fth[i]);
	}
	vector<vector<int>> ans(n+1,vector<int>(0));
	orderTree(t,1,0,ans);
	return ans;
}
void buildBracketString(vector<vector<int>> &t,int u,string &s)
{
	for(int i=0;i<t[u].size();i++)
	{
		s+='(';
		buildBracketString(t,t[u][i],s);
		s+=')';
	}
}
string randBracketString(int n)
{
	vector<vector<int>> t=randTree(n+1);
	string s="";
	buildBracketString(t,1,s);
	return s;
}
namespace charSet
{
	string lowLetters="abcdefghijklmnopqrstuvwxyz";
	string capLetters="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string numbers="0123456789";
}
inline
string randString(int minLen,int maxLen,string charSet)
{
	int len=randNum(minLen,maxLen);
	string ans="";
	for(int i=1;i<=len;i++)
	{
		ans+=charSet[randNum(0,charSet.size()-1)];
	}
	return ans;
}
#undef int
