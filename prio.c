#include<stdio.h>
int n,avgWait,avgTurn;
struct process{
	int pid,burst,arrival,turn,wait,prio,completion;
};

struct process p[10];
struct process swaptemp;
void swap(int a,int b){
	int i,j;
	swaptemp=p[b];
	for(i=b;i>a;i--)
		p[i]=p[i-1];
	p[a]=swaptemp;
}

// void calc(){
// 	p[0].wait = 0;
// 	p[0].completion = p[0].burst;
// 	p[0].turn = p[0].burst;
// 	p[0].wait = 0;
// 	for(int i=1;i<n;i++){
// 		p[i].completion = p[i-1].completion + p[i].burst;
// 		p[i].turn = p[i].completion - p[i].arrival;
// 		p[i].wait = p[i].turn - p[i].burst;
// 	}
// }

void calc(){
	p[0].wait = 0;
	p[0].completion = p[0].burst;
	p[0].turn = p[0].burst;
	for(int i=1;i<n;i++){
		p[i].completion = p[i-1].completion + p[i].burst;
		p[i].turn = p[i].completion - p[i].arrival;
		p[i].wait = p[i].turn - p[i].burst;
		avgWait += p[i].wait;
		avgTurn += p[i].turn;
	}
}

void output(){
	
	for(int i=0;i<n;i++){
		printf("process: %d\tarrival: %d\t burst: %d\tpriority: %d\tcompletion: %d\twaiting: %d\t turnaround:%d\n", 
		p[i].pid, p[i].arrival, p[i].burst,p[i].prio,p[i].completion, p[i].wait, p[i].turn);
	}
}

void main(){
	int i,j,k,b,a,c;
	struct process temp;
	printf("Enter the number of processes:\n");
	scanf("%d",&n);

	for(i=0;i<n;i++){
		printf("Enter Arrival time,Burst time and Priority(Lower number=> Higher Priority) for process %d: ",i+1);
		scanf("%d %d %d",&a,&b,&c);
		p[i].completion=0;
		p[i].pid=i+1;
		p[i].burst=b;
		p[i].arrival=a;
		p[i].prio=c;
	}

	//sort according to prio time
	for(i=0;i<n-1;i++){
		for(j=0;j<n-i-1;j++){
			if(p[j].prio>p[j+1].prio){
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}

	// //printing the sorted
	// printf("just sorting\n");
	// for(i=0;i<n;i++){
	// 	printf("PID:%d\tArrival:%d\tBurst:%d\n",p[i].pid,p[i].arrival,p[i].burst);}

	
		printf("final\n");
	int ct=0;
	int minA;
	for(i=0;i<n;i++){
		minA=i;
		if(p[i].arrival>ct){
					
			for(j=i+1;j<n;j++){
				if(p[j].arrival<p[minA].arrival )		
					minA=j;

					if(p[minA].arrival<ct)
					break;
				
			}
			swap(i,minA);
		}

		
		ct+=p[i].burst;
	}


	calc();
	output();


}