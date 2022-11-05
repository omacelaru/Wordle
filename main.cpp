#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

using namespace std;
struct alfa
{
    float x;
    char c[2];
}e[26];

int k,okm,y,prima=1;
char s[11456][6];
int st[6],n=26,p=5,l,m,i,z,a,b,stc[6],npc=5,v_c[6],v_i[6][26],q[6];
char rez[6];
int pc_bk[3500][5],c_bk[66000][5];
char cc[6][2],cpc[6],spc[1000][6],u;

int poz(int l, int r, alfa a[])
{
    int i=l,j=r,i1=0,j1=-1,c;
    alfa aux;
    while(i<j)
    {
        if(a[i].x<a[j].x)
        {
            aux=a[j];
            a[j]=a[i];
            a[i]=aux;
            c=i1;
            i1=-j1;
            j1=-c;
        }
        i=i+i1;
        j=j+j1;
    }
    return i;
}

void quick(int l, int r)
{
    if(l<r)
    {
        k=poz(l,r,e);
        quick(l,k-1);
        quick(k+1,r);
    }
}


int caut_bin(char a[],long l, long r)
{
    if(l>r) return -1;
    long m = l + (r-l)/2;
    if(strcmp(a,s[m])==0)
        return 1;
    else if (strcmp(a,s[m])==1)
        caut_bin(a,m+1,r);
    else
        caut_bin(a,l,m-1);
}
void c_init()
{
    stc[a]=0;
}

int c_succesor()
{
    if(stc[a]<n)
    {
        stc[a]++;
        return 1;
    }
    else
        return 0;
}
int c_valid()
{
    for(b=1;b<a;b++)
        if(stc[a]==stc[b])
        return 0;
    if (a>1 && stc[a]<=stc[a-1])
        return 0;
    return 1;
}
int c_solutie()
{
    return a==p;
}
void c_tipar()
{
    for(b=1;b<=a;b++)
        cout<<stc[b]<<" ";
    cout<<endl;
}
void c_back()
{
    int ASc;
    a=1;
    c_init();
    while(a>0)
    {
        do{

        }while((ASc=c_succesor())&& !c_valid());
        if(ASc)
            if(c_solutie())
            {
                c_bk[y][0]=stc[1];
                c_bk[y][1]=stc[2];
                c_bk[y][2]=stc[3];
                c_bk[y][3]=stc[4];
                c_bk[y][4]=stc[5];
                y++;
            }
            else
            {
                a++;
                c_init();
            }
        else
            a--;
    }
}

void init()
{
    st[m]=0;
}

int succesor()
{
    if(st[m]<npc)
    {
        st[m]++;
        return 1;
    }
    else
        return 0;
}

int pc_valid()
{

    int x,v[26],nr=0,j;
    if(prima==1)
    {
        for(b=0;b<m;b++)
            if(st[m]==st[b])
            return 0;

    }

    for(b=0;b<5;b++)
        if(v_c[b]!=-1 && m==b+1)
        {
            for(i=0;i<5;i++)
            {
                if(cc[i][0]==char('A'+v_c[b]-1))
                   x=i;
            }
            if(st[m]!=x+1)
                return 0;
        }
    for(b=0;b<5;b++)
    {

        if(v_i[b][0]!=-1 && m==b+1)
        {
            nr=0;
            for(j=0;j<q[b];j++)
            {
                for(i=0;i<5;i++)
                if(cc[i][0]==char('A'+v_i[b][j]-1))
                   {v[j]=i;nr++;}


            }
            for(int w=0;w<nr;w++)
                if(st[m]==v[w]+1)
                return 0;
        }

    }
    return 1;
}
int solutie()
{
    return m==npc;
}
void tipar()
{
    for(l=1;l<=m;l++)
        cout<<st[l]<<" ";
    cout<<endl;
}
void pc_back()
{
    int AS;
    m=1;
    init();
    while(m>0)
    {
        do{

        }while((AS=succesor())&& !pc_valid());
        if(AS)
            if(solutie())
            {

                pc_bk[z][0]=st[1];
                pc_bk[z][1]=st[2];
                pc_bk[z][2]=st[3];
                pc_bk[z][3]=st[4];
                pc_bk[z][4]=st[5];
                z++;
            }
            else
            {
                m++;
                init();
            }
        else
            m--;
    }
}

int main()
{

    ifstream f("cuvinte_wordle.txt");
    ofstream g("entropie.txt");
    for(i=0;i<5;i++)v_c[i]=-1;
    for(i=0;i<5;i++)v_i[i][0]=-1;
    int c,ok;
    char t[6];
    srand(time(0));
    for(i=0;i<10;i++)
        c= rand()%11455;


    int i,j,gasitcuv=0;
    long long v[26];

    for(i=0;i<26;i++)v[i]=0;

    for(i=0;i<11456;i++)
    {
        f>>s[i];
        for(j=0;j<strlen(s[i]);j++)
            v[s[i][j]-'A']++;
    }
    for(i=0;i<26;i++)
    {
        e[i].x= log(v[i])/log(2);
        e[i].c[0]=char('A'+i);
        e[i].c[1]='\0';
        //g<<" "<<e[i].x<<endl;
    }
    for(i=0;i<5;i++)
        q[i]=0;
    int nrr=0;
    do{
        for(i=0;i<y;i++)
            for(j=0;j<5;j++)
            c_bk[i][j]=-1;
        y=0;
        n=0;
        for(i=0;i<26;i++)
            if(e[i].x!=-1)
                n++;
        c_back();
        /*
        cout<<"Comb"<<y<<endl;



        for(i=0;i<5;i++)
            cout<<v_c[i]<<" ";
        cout<<endl;
        for(i=0;i<5;i++)
        {
            for(j=0;j<=q[i];j++)
        {
            cout<<v_i[i][j]<<" ";
        }
        cout<<endl;

        }
        */


        quick(0,25);
        /* for(i=0;i<26;i++)
            cout<<e[i].c<<" "<<e[i].x<<endl;*/
        int nr=1,gasit=0;

        //cout<<z<<endl;
        for( i=0;i<y&& !gasit; i++)
        {
            for(j=0;j<5;j++)
            {
                cc[j][0]=e[c_bk[i][j]-1].c[0];
                cc[j][1]='\0';
            }
            /*
            cout<<"Literele sunt:";
            for(j=0;j<5;j++)
                cout<<cc[j]<<" ";
            cout<<endl;
            */
            z=0;
            pc_back();
            u=0;
            for(k=0;k<z;k++)
            {
                cpc[0] = cc[pc_bk[k][0]-1][0];
                cpc[1] = cc[pc_bk[k][1]-1][0];
                cpc[2] = cc[pc_bk[k][2]-1][0];
                cpc[3] = cc[pc_bk[k][3]-1][0];
                cpc[4] = cc[pc_bk[k][4]-1][0];
                cpc[5]='\0';
                if(caut_bin(cpc,0,11455)==1)
                {
                    strcpy(spc[u++],cpc);
                    gasit=1;
                }

            }
        }
        prima=0;
        if(gasit==0)
            cout<<"nu am gasit cuv"<<endl;
        
        int stg,len,lmax=-1,car,lit,poz1=0,poz2=u-1;
        for(int re=0;re<5&&poz1<poz2;re++)
        {
            i=poz1;j=poz2;lit=re;lmax=-1;
            do{
                car=int(spc[i][lit]);
                stg=i+1;
                while(stg<=j && car==int(spc[stg][lit]))
                    stg++;
                l=stg-i;
                i=stg;
                if(lmax<l)
                {
                    lmax=l;
                    poz2=stg-1;
                    poz1=stg-l;
                }
            }while(i<j);
        }
        u=0;
        cout<<spc[poz1]<<endl;
        //cout<<"#"<<endl;
        //cout<<s[c]<<endl;

        strcpy(t,spc[poz1]);
        t[5]='\0';
        if(strcmp(s[c],t)==0)
            {
                gasitcuv=1;
                for(i=0;i<5;i++)
                    cout<< t[i]<<" 1"<<endl;
                cout<<endl<<"Felicitari ai ghicit cuvantul "<< s[c] <<" din "<<nrr+1<<" incercari"<<endl;
            }
            else
            {
                for(i=0;i<5;i++)
                {
                    if(s[c][i]==t[i])
                    {
                        cout<< t[i]<<" 1"<<endl;

                        v_c[i]= int(t[i])-'A'+1;
                        for(int r=0;r<26;r++)
                            if(e[r].c[0]==t[i])
                            e[r].x=16;
                    }

                    else
                    {
                        ok=0;
                        for(j=0;j<6&&!ok;j++)
                            if(s[c][j]==t[i])
                                ok=1;
                        if(ok==1)
                        {
                            cout<<t[i]<<" 0"<<endl;


                            v_i[i][q[i]]=int (t[i])-'A'+1;
                            q[i]++;
                            for(int r=0;r<26;r++)
                                if(e[r].c[0]==t[i]&& e[r].c[0]!=16)
                                    e[r].x=15;
                        }

                        else
                        {
                            cout<<t[i]<<" -1"<<endl;
                            for(int r=0;r<26;r++)
                                if(e[r].c[0]==t[i])
                                    e[r].x=-1;
                        }


                    }
                }
            }
            cout<<endl;nrr++;
        }while(gasitcuv==0);
    return 0;
}
