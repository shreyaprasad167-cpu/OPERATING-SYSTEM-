#include<stdio.h>
#define MAX 100

void inputProcesses(int n,int arrival[],int burst[],int remaining[]);
void simulateSRTF(int n, int arrival[],int burst[],int remaining[],int finish[],int waiting[],int turnaround[],float *total_wait,float *total_turnaround);
void displayResults(int n, int arrival[],int burst[],int finish[],int turnaround[],int waiting[],float total_wait,float total_turnaround);

int main(){
	int n;
	int arrival[MAX],burst[MAX],remaining[MAX];
	int finish[MAX],waiting[MAX],turnaround[MAX];
	float total_wait=0,total_turnaround=0;
	printf("Enter number of processes: ");
	scanf("%d",&n);
	inputProcesses(n,arrival,burst,remaining);
	simulateSRTF(n,arrival,burst,remaining,finish,waiting,turnaround,&total_wait,&total_turnaround);
	displayResults(n,arrival,burst,finish,turnaround,waiting,total_wait,total_turnaround);
	return 0;
}

void inputProcesses(int n,int arrival[],int burst[],int remaining[]){
	for(int i=0;i<n;i++){
		printf("Enter arrival time and burst time for Process %d: ",i+1);
		scanf("%d%d",&arrival[i],&burst[i]);
		remaining[i] = burst[i];
	}
}

void simulateSRTF(int n,int arrival[],int burst[],int remaining[],int finish[],int waiting[],int turnaround[],float *total_wait,float *total_turnaround){
	int time=0,completed=0;
	while (completed!=n){
		int idx=-1;
		int min_time=1e9;
		//Find processes with shortest remaining time
		for (int i=0;i<n;i++){
			if (arrival[i] <= time && remaining[i] > 0 && remaining[i] < min_time){
				min_time=remaining[i];
				idx=i;
			}
		}
		if (idx!=-1){
			remaining[idx]--;
			time++;
			if (remaining[idx] == 0){
				completed++;
				finish[idx]=time;
				turnaround[idx]=finish[idx]-arrival[idx];
				waiting[idx]=turnaround[idx]-burst[idx];
				*total_wait += waiting[idx];
				*total_turnaround += turnaround[idx];
				
			}
		}
		else{
			time++;
		}
	}
}

void displayResults(int n, int arrival[],int burst[],int finish[],int turnaround[],int waiting[],float total_wait,float total_turnaround){
	printf("\nProcess\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n");
	for (int i=0;i<n;i++){
		printf("P%d\t%d\t%d\t%d\t%d\t\t%d\n",i+1,arrival[i],burst[i],finish[i],turnaround[i],waiting[i]);
	}
	printf("\n Average waiting Time : %.2f\n",total_wait/n);
	printf("\n Average Turnaround Time : %.2f\n",total_turnaround/n);
}	
	
