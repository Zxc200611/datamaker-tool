#pragma once
#include<bits/stdc++.h>
using namespace std;
mt19937 Rand;
char inFile[1024],outFile[1024];
char cmd[1024];
char problemName[1024];
inline
void init(string filename="",int dataId=0)
{
	freopen("gen.cfg","r",stdin);
	int g=0;
	cin>>g;
	freopen("gen.cfg","w",stdout);
	cout<<g+1<<endl;
	Rand=mt19937(g);
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
	sprintf(cmd,"%s.exe < %s%d.in > %s%d.out",problemName,problemName,dataId,problemName,dataId);
	system(cmd);
}
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
	int l=randNum(1,n),r=l;
	while(r==l)
		r=randNum(1,n);
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
		ans.push_back(minLimit+(i==n?sum:randNum(max(0,sum-maxLimit*(n-i)),min(maxLimit,2*sum/(n-i+1)))));
		sum-=(ans[i-1]-minLimit);
	}
	shuffle(ans.begin(),ans.end(),Rand);
	return ans;
}
