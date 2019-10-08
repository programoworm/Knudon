#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"colors.h"
#include"keywords.h"
#include"scanner.h"
#include"parser.c"
#include"interpreter.c"
int main(){
	//char string[100];
	//while(1){
	pos=0;
	FILE *fp=fopen("test.k","r");
		//printf(GREEN"Knudon>> "RESET);
		//if(fp==NULL)
		//	printf("File not found!\n");
		//fgets(string,100,stdin);
	fseek(fp,0,SEEK_END);
	int len=ftell(fp);
	fseek(fp,0,SEEK_SET);
	char *buffer=malloc(len);
	fread(buffer,1,len-1,fp);
		//	printf("Error\n");
		//buffer[strlen(buffer)]=EOF;
		//puts(buffer);
	Compound *root=parser(buffer);
		//printf("HI %d\n", string[pos]);//(root->item).value);
		//Compound *temp=root;
		/*while(temp->child!=NULL){
			printInorder(temp->item);
			temp=temp->child;
		}*/
		//printInorder(root->item);
	interprete(root);//printf("\n%d")
		//printf("Hi I am finished\n");
		//printf("global scope size: %d\n",g_size);
		//for(int i=0;i<g_size;i++)
		//	printf("%s %d\n",sym_table[i].id,sym_table[i].value);
	//}
	return 0;
}