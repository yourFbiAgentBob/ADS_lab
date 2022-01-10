// Given a boolean 2D matrix, find the number of islands.
// A group of connected 1s forms an island. For example, the below matrix contains 5 
// islands
// {1, 1, 0, 0, 0},
// {0, 1, 0, 0, 1},
// {1, 0, 0, 1, 1},
// {0, 0, 0, 0, 0},
// {1, 0, 1, 0, 1} 
// A cell in the 2D matrix can be connected to 8 neighbours.
// Use disjoint sets to implement the above scenario.

#include<iostream>
#include<bits/stdc++.h>
#include<vector>
using namespace std;
class dsuf
{
vector<int> rank;
vector<int> parent;

public:
int n;
dsuf(int n)
{
this->n=n;
parent.resize(n);//adjusting size of vector to n if greater 
rank.resize(n);
fill(rank.begin(),rank.end(),0);
fill(parent.begin(),parent.end(),-1);//initializing parent and rank

}
void Union(int x,int y)
{
int absx=Find(x);
int absy=Find(y);
if(absx==absy)
{
    return;//abs parents same means they belong to same set
}
if(rank[absx]<rank[absy])
{
  parent[absx]=absy;
}
else if(rank[absx]>rank[absy])
{
    parent[absy]=absx;
}
//last case is if equal
else
{
parent[absy]=absx;
//taking union of equal rank sets means rank of set joined to increases 
rank[absx]=rank[absx]+1;
}

}
int Find(int x)
{
   if(parent[x]==-1)
   {
    return x;
   }
return parent[x]=Find(parent[x]);
}
};

int count_of_islands(vector<vector<int>> islands,int rows,int cols)
{
    dsuf *uf=new dsuf(rows*cols);
for(int i=0;i<rows;i++)
 {
  for(int j=0;j<cols;j++)
  {//exploring all neighbours
  if(islands[i][j]==1)
  {
  if(i<rows-1 && islands[i+1][j])//down
  {
   uf->Union((i*cols)+j,(i+1)*cols+j);//element coordinate in 1-D,coordinate of down element in 1-D array
  }
  if(i>0 && islands[i-1][j])//up
  {
    uf->Union((i*cols+j),(i-1)*cols+j);
  }
  if(j>0 && islands[i][j-1])//left
  {
   uf->Union((i*cols)+j,(i*cols)+j-1);
  }
  if(j<cols-1 && islands[i][j+1])//right
  {
   uf->Union((i*cols)+j,(i*cols)+j+1);
  }
  if(j>0 && i<rows-1 && islands[i+1][j-1])//lower left diagonal
  {
   uf->Union((i*cols)+j,(i+1)*cols+j-1);
  }
  if(j<cols-1 &&i<rows-1&& islands[i+1][j+1])//lower right diagonal
  {
   uf->Union((i*cols)+j,(i+1)*cols+j+1);
  }
  if(i>0 && j>0 && islands[i-1][j-1])//upper left diagonal
  {
   uf->Union((i*cols)+j,(i-1)*cols+j-1);
  }
  if(i>0 && j<cols-1 && islands[i-1][j+1])//upper right diagonal
  {
   uf->Union((i*cols+j),(i-1)*cols+j+1);
  }
  }
 }
}

    
int *c=new int[rows*cols];
int count=0;
for(int i=0;i<rows;i++)
{
    for(int j=0;j<cols;j++)
    {
        if(islands[i][j]==1)
        {
            int x=uf->Find(i*cols+j);//calc coordinate wrt to 1D. We are finding abs root if they are same it means elements belong to same set
           if(c[x]==0)//if frequency is 0 then we will update island count since it indicates a new set
           {
              count++;
              c[x]++;
           }
           else
           c[x]++;
        }
    }
}

return count;
}

int main()
{
    int rows,cols;
    cout<<"Enter no of rows:"<<endl;
    cin>>rows;
    cout<<"Enter no of columns:"<<endl;
    cin>>cols;
    vector<vector<int>> islands;
    
    int val;
    cout<<"Enter 1 for island 0 for water:"<<endl;
    for(int i=0;i<rows;i++)
    {
        vector <int> island_row;//should be created for every row otherwise w3ill overwrite prev value
        for(int j=0;j<cols;j++)
        {
        cin>>val;
        island_row.push_back(val);
        }
        cout<<endl;
        islands.push_back(island_row);
    }   
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
        cout<<islands[i][j];
        
        }
        cout<<endl;
        }   
    cout<<"No of islands is:"<<count_of_islands(islands,rows,cols)<<endl;

    return 0;
}