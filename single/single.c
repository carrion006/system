#include<stdio.h>
#include<string.h>
FILE *src_fp,*hexsheet_fp,*symtab_fp;
char sfname[25],label[10],opcode[10],operand[10];
char hexname[25],mnemonics[10];
char symbol[10];
int code,startaddr,locctr,saddr,len;
void main()
{
	printf("\t\t\tSINGLE PASS ASSEMBLER\n");
	printf("\t\t\t----------------------\n");
	printf("\tINPUT\n");
	printf("\t------\n");
	printf("Enter the source file name\n");
	scanf("%s",sfname);
	src_fp=fopen(sfname,"r");
	while(fscanf(src_fp,"%s%s%s",label,opcode,operand)!=EOF)
		printf("\t%s\t%s\t%s\n",label,opcode,operand);
	fclose(src_fp);
	printf("Enter the hexcode sheet file\n");
	scanf("%s",hexname);
	hexsheet_fp=fopen(hexname,"r");
	while(fscanf(hexsheet_fp,"%s%x",mnemonics,&code)!=EOF)
		printf("\t%s\t%x\n",mnemonics,code);
	fclose(hexsheet_fp);
	printf("Enter the starting memory address\n");
	scanf("%x",&startaddr);
	locctr=startaddr;
	src_fp=fopen(sfname,"r");
	symtab_fp=fopen("symtab.txt","w");
	fscanf(src_fp,"%s%s%s",label,opcode,operand);
	while(fscanf(src_fp,"%s%s%s",label,opcode,operand)!=EOF)
	{
		if(strcmp(label,"0")!=0)
			fprintf(symtab_fp,"%s\t%x\n",label,locctr);
		if(strcmp(opcode,"WORD")==0)
			locctr=locctr+3;
		else if(strcmp(opcode,"BYTE")==0)
			locctr=locctr+1;
		else if(strcmp(opcode,"END")==0)
			locctr=locctr;
		else
			locctr=locctr+3;
	}
	fclose(symtab_fp);
	fclose(src_fp);
	printf("\t\t\tOUTPUT\n");
	printf("\t\t\t-------\n");
	printf("Symbol table:\n");
	symtab_fp=fopen("symtab.txt","r");
	while(fscanf(symtab_fp,"%s%x",symbol,&saddr)!=EOF)
		printf("\n\t%s\t%x",symbol,saddr);
	fclose(symtab_fp);
	len=locctr-startaddr;
	printf("\n\nObject Program:\n");
	src_fp=fopen(sfname,"r");
	fscanf(src_fp,"%s%s%s",label,opcode,operand);
	if(strcmp(opcode,"START")==0)
		printf("\nH\t%s\t%x\t%x",label,startaddr,len);
	printf("\nT\t%x\t%x\t",startaddr,len);
	while(fscanf(src_fp,"%s%s%s",label,opcode,operand)!=EOF)
	{
		if((strcmp(opcode,"BYTE")!=0)
				&&(strcmp(opcode,"WORD")!=0)&&(strcmp(opcode,"END")!=0))
		{
			hexsheet_fp=fopen(hexname,"r");
			while(fscanf(hexsheet_fp,"%s%x",mnemonics,&code)!=EOF)
			{if(strcmp(opcode,mnemonics)==0)
				{
					printf("%x",code);
					symtab_fp=fopen("symtab.txt","r");
					while(fscanf(symtab_fp,"%s%x",symbol,&saddr)!=EOF)
					{
						if(strcmp(operand,symbol)==0)
							printf("%x\t",saddr);
					}
					fclose(symtab_fp);
				}
			}
			fclose(hexsheet_fp);
		}
		else if(strcmp(opcode,"END")==0)
			printf("\nE\t%x\n",startaddr);
	}
	fclose(src_fp);
}


