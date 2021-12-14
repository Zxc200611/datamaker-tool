#include<bits/stdc++.h>
using namespace std;
mt19937 Rand(114514);
char inFile[1024],outFile[1024];
char cmd[1024];
char problemName[1024];
inline
void init(string filename="",int dataNum=0)
{
	freopen("gen.cfg","r",stdin);
	int g=0;
	cin>>g;
	freopen("gen.cfg","w",stdout);
	cout<<g+1<<endl;
	srand(g);
	if(dataNum!=-1)
	{
		sprintf(inFile,"%s%d.in",filename.c_str(),dataNum);
		sprintf(problemName,"%s",filename.c_str());
		freopen(inFile,"w",stdout);
		return;
	}
	freopen("data.in","w",stdout);
}
inline
void genOut(int t)
{
	fclose(stdout);
	sprintf(cmd,"%s.exe < %s%d.in > %s%d.out",problemName,problemName,t,problemName,t);
	system(cmd);
}
inline
int randNum(int l,int r)
{
	if(l==r)
		return l;
	return l+Rand()%(r-l+1);
}
inline
pair<int,int> randInterval(int a,int b)
{
	int n=b-a+1;
	int l=randNum(1,n),r=l;
	while(r==l)
		r=randNum(1,n);
	if(r<=l)
		swap(l,r);
	return make_pair(a+l-1,a+r-1);
}
inline
vector<int> randSplit(int n,int sum,int minLimit)
{
	vector<int> ans;
	ans.clear();
	sum-=n*minLimit;
	if(sum<0)
		return ans;
	for(int i=1;i<=n;i++)
	{
		ans.push_back(minLimit+(i==n?sum:randNum(0,2*sum/(n-i+1))));
		sum-=(ans[i-1]-minLimit);
	}
	shuffle(ans.begin(),ans.end(),Rand);
	return ans;
}