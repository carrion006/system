#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 10
struct estab
{
	char csect[10];
	char sym_name[10];
	long int add;
	int length;
}table[MAX];
void main()
{
	FILE *fp1,*fp2;
	char input[10];
	long int i,count=0,start,length,loc;

	printf("\t\t\tPass1 of Direct Linking Loader\n");
	printf("\t\t\t------------------------------\n");
	fp1=fopen("link1in.txt","r");
	fp2=fopen("link1out.txt","w");
	printf("Enter the location where the program has to be loaded:");
	scanf("%lx",&start);
	printf("The intermediate file of pass1 of DLL is:\n\n");
	fprintf(fp2,"CSECT\tSymname\tAddress\tLength\n");
	printf("CSECT\tSymname\tAddress\tLength\n");
	rewind(fp1);
	while(!feof(fp1))
	{
		fscanf(fp1,"%s",input);
		if(strcmp(input,"H")==0)
		{
			fscanf(fp1,"%s",input);
			strcpy(table[count].csect,input);
			strcpy(table[count].sym_name,"\0");
			fscanf(fp1,"%s",input);
			table[count].add=atoi(input)+start;
			fscanf(fp1,"%s",input);
			length=atoi(input);
			table[count++].length=atoi(input);                                                           
				fscanf(fp1,"%s",input);                                                    
		}                                                                                                         
		if(strcmp(input,"D")==0)
		{
			fscanf(fp1,"%s%lx",input,&loc);                                   
				while((strcmp(input,"R")!=0))
				{                          
					strcpy(table[count].csect,"\0");            
						strcpy(table[count].sym_name,input);                                                                                    
						table[count].add=loc+start;                                                            

						table[count++].length=0;                                         

						fscanf(fp1,"%s%lx",input,&loc);                                       

				}                                            
			while(strcmp(input,"T")!=0)
				fscanf(fp1,"%s",input);
		}                                  
		if(strcmp(input,"T")==0)
			while(strcmp(input,"E")!=0)                
				fscanf(fp1,"%s",input);
		start=start+length;
	}
	for(i=0;i<count;i++)
	{
		fprintf(fp2,"%s\t%s\t%lx\t%d\n",table[i].csect,table[i].sym_name,table[i].add,table[i].length);
		printf("%s\t%s\t%lx\t%d\n",table[i].csect,table[i].sym_name,table[i].add,table[i].length);
	}
}
