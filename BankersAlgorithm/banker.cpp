#include <iostream>
#include <stdio.h>
#define maxP 100
#define maxR 100
using namespace std;
int p,r;
int processes[maxP];
int avail[maxR];

void readTable(char *s, int temp[maxP][maxR]){
	FILE *f = fopen(s,"rt");
	fflush(stdin);
	for (int i = 0; i < p; i++)
		for (int j = 0; j < r;j++)
		fscanf(f,"%d",&temp[i][j]);
	fclose(f);
}

void readTableProcesses(){
	FILE *f = fopen("tableProcesses.inp","rt");
	fscanf(f,"%d",&p);
	fscanf(f,"%d",&r);
	for (int i = 0; i < p; i++)
		fscanf(f,"%d",&processes[i]);

	for (int i = 0; i < p; i++)
		fscanf(f,"%d",&avail[i]);
	fclose(f);
}


void calculateNeed(int need[][maxR], int maxm[][maxR],
				int alloc[][maxR])
{
	for (int i = 0 ; i < p ; i++)
		for (int j = 0 ; j < r ; j++)
			need[i][j] = maxm[i][j] - alloc[i][j];
}


void InitWork(int work[maxP][maxR]){
	for (int i = 0; i < r; i++)
		work[0][i] = avail[i];
}

void InitFinish(bool finish[]){
	  for (int i = 0; i < p; i++)
        finish[i] = false;
}

void printResult(int Seq[],int work[][maxR]){
	for (int i = 0; i < p ; i++)
		cout << "P" << Seq	[i] << " ";
	
	cout<<endl<<"Table Work:"<<endl;
	for (int i = 0; i < p + 1; i++){
		for (int j = 0; j< r; j++)
			cout << work[i][j]<<" ";
		cout<<endl;
	}
}

void banker1(){
	int alloc[maxP][maxR], maxm[maxP][maxR],need[maxP][maxR],work[maxP][maxR];
	readTableProcesses();
	readTable("tableAllocation.inp",alloc);
	readTable("tableMax.inp",maxm);

	bool finish[p];
	InitWork(work);
	InitFinish(finish);
	calculateNeed(need, maxm, alloc);

    int count = 0,index = 0;
    int safeSeq[p];
	while (count < p)
	{
		bool found = false;
		for (int i = 0; i < p; i++)
		{
			if (finish[i] == false)
			{
				int j;
				for (j = 0; j < r; j++)
					if (need[i][j] >  work[index][j])
						break;

				if (j == r)
				{
					index++;
					for (int k = 0 ; k < r ; k++)
						work[index][k] = work[index - 1][k] + alloc[i][k];
					finish[i] = true;
					safeSeq[count++] = i;
					found = true;
				}
			}
		}
		if (found == false)
		{
			cout << "unsafe";
            return;
		}
	}

	printResult(safeSeq,work);
}

void banker2(){
	int alloc[maxP][maxR], request[maxP][maxR], safeSeq[p], work[maxP][maxR];
	readTableProcesses();
	readTable("tableAllocation.inp",alloc);
	readTable("tableRequest.inp",request);
	bool finish[p];

	InitWork(work);
	InitFinish(finish);

	int index = 0,count = 0;

	while (count < p)
	{
		bool found = false;
		for (int i = 0; i < p; i++)
		{
			if (finish[i] == false){
					int j;
					for (j = 0; j < r; j++)
							if (request[i][j] > work[index][j])
								break;
			
					if (j == r){
						index++;
						for (int k = 0 ; k < r ; k++)
							work[index][k] = work[index - 1][k] + alloc[i][k];
						finish[i] = 1;
						safeSeq[count++] = i;
						found = true;
					}
			}
		}	
		if (found == false)
		{
			cout << "unsafe";
			return;
		}
	}
	printResult(safeSeq,work);
}


void updateAlloc_Avail(int alloc[maxP][maxR], int work[][maxR], 
						int Request[], int pos)
{
	for (int i = 0 ; i < r ; i++){
        work[0][i] = work[0][i]- Request[i];
        alloc[pos][i] = alloc[pos][i] + Request[i];
    }
}

void banker3(){
	int alloc[maxP][maxR], maxm[maxP][maxR];
	readTableProcesses();
	readTable("tableAllocation.inp",alloc);
	readTable("tableMax.inp",maxm);
	
	int pos;
	int Request[r],work[maxP][maxR],need[maxP][maxR];
	
	FILE *f = fopen("Request.inp","rt");
	fscanf(f,"%d",&pos);
	for (int i = 0; i < r; i++)
			fscanf(f,"%d",&Request[i]);

	fclose(f);
	bool finish[p];

	InitWork(work);
	InitFinish(finish);
	updateAlloc_Avail(alloc,work,Request,pos);
	calculateNeed(need, maxm, alloc);
	
    int count = 0,index = 0;
    int safeSeq[p];
	while (count < p){
		bool found = false;
		for (int i = 0; i < p; i++)
		{
			if (finish[i] == 0)
			{
				int j;
				for (j = 0; j < r; j++)
					if (need[i][j] >  work[index][j])
						break;

				if (j == r)
				{
					index++;
					for (int k = 0 ; k < r ; k++)
						work[index][k] = work[index - 1][k] + alloc[i][k];
					finish[i] = 1;
					safeSeq[count++] = i;
					found = true;
				}
			}
		}

		if (found == false)
		{
			cout << "unsafe";
            return;
		}
	}
	printResult(safeSeq,work);
}

void choose(int temp){
	switch (temp){
		case 1:{
			banker1();
			break;
		}

		case 2:{
			banker2();
			break;
		}

		case 3:{
			banker3();
			break;
		}
		
		default:{
			cout<<"Error";
			break;
		}
	}
}

void readChoose(){
	int temp;
	cout<<"chon banker:"; cin>>temp;
	choose(temp);
}

int main(){
	readChoose();
	system("pause");
}