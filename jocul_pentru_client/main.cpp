#include <iostream>
#include <string.h>
#include <fstream>
#include <time.h>

using namespace std;

int main()
{
    ifstream f("cuvinte_wordle.txt");
    int i,j,ok,c,k,gasit=0,intr=0;
    char s[11456][6],t[10],ent[]="\n";
    for(i=0;i<11456;i++)
        f>>s[i];
    srand(time(0));
    c= rand()%11456;
    cout<<"Am ales un cuvant! Incearca sa-l ghicesti! Nu uita sa folosesti litere mari!"<<endl;
    cout<<"Pentru fiecare incercare iti voi da detalii despre literele folosite:"<<endl;
    cout<<"1 - litera apartine cuvantului ales si este pe pozitia corecta"<<endl;
    cout<<"0 - litera apartine cuvantului ales si NU este pe pozitia corecta"<<endl;
    cout<<"-1 - litera NU apartine cuvantului ales"<<endl;
    cout<<s[c]<<endl;
    k=0;
    do{
        k++;
        do
        {
            cin.get(t,10);cin.get();
            if(strlen(t)<1)
            {
                cout<<"Ai tastat un carcater nepermis.. ai distrus jocul"<<endl;
                intr=1;
                break;
            }

            if(strlen(t)==5)
            {
                ok=0;i=0;
                while(!ok && i<11455)
                {
                    if(stricmp(s[i],t)==0)
                        ok=1;
                    i++;
                }

                if(ok==1)
                    break;
                else
                    cout<<"Nu ai introdus un cuvant din baza de date!Incearca din nou!"<<endl;
            }
            else
                cout<<"Nu ai introdus un cuvant de 5 litere.Incearca din nou!"<<endl;
        }while(1);
        if(intr==1)
            break;
        for(i=0;i<strlen(t);i++)
            if(t[i]>='a'&&t[i]<='z')
                t[i]-=32;
        if(stricmp(s[c],t)==0)
        {
            gasit=1;
            cout<<"Felicitari ai ghicit cuvantul "<<s[c]<<" din "<< k+1<<" incercari"<<endl;
        }
        else
        {
            for(i=0;i<5;i++)
            {
                if(s[c][i]==t[i])
                    cout<< t[i]<<" 1"<<endl;
                else
                {
                    ok=0;
                    for(j=0;j<6&&!ok;j++)
                        if(s[c][j]==t[i])
                            ok=1;
                    if(ok==1)
                        cout<<t[i]<<" 0"<<endl;
                    else
                        cout<<t[i]<<" -1"<<endl;

                }
            }
        }
        cout<<endl;


    }while(gasit==0 && k<6);

    return 0;
}

