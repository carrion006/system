#include<stdio.h>
#include<conio.h>
#include<string.h>
void main()
{
	char a[10],ad[10],label[10],opcode[10],operand[10],symbol[10],ch;  int st,diff,i,address,add,len,actual_len,finaddr,prevaddr,j=0;
	char mnemonic[15][15]={"LDA","STA","LDCH","STCH"};
	char code[15][15]={"33","44","53","57"};
	FILE *fp1,*fp2,*fp3,*fp4;
	clrscr();
		    fp1=fopen("ASSMLIST.DAT","w");
		      fp2=fopen("SYMTAB.DAT","r");
		        fp3=fopen("INTERMED.DAT","r");
			  fp4=fopen("OBJCODE.DAT","w");
			    fscanf(fp3,"%s%s%s",label,opcode,operand);

			      while(strcmp(opcode,"END")!=0)
				        {
						   prevaddr=address;
				fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
						        }
