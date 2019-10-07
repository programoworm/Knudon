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
	char string[100];
	while(1){
		pos=0;
		//FILE *fp=fopen("test.k","r");
		printf(GREEN"Knudon>> "RESET);
		//if(fp==NULL)
		//	printf("File not found!\n");
		fgets(string,100,stdin);
		//	printf("Error\n");
		string[strlen(string)]=EOF;
		//puts(string);
		Compound *root=parser(string);
		//printf("HI %d\n", string[pos]);//(root->item).value);
		//Compound *temp=root;
		/*while(temp->child!=NULL){
			printInorder(temp->item);
			temp=temp->child;
		}*/
		interprete(root);//printf("\n%d")
		//printf("Hi I am finished\n");
		//printf("global scope size: %d\n",g_size);
		//for(int i=0;i<g_size;i++)
			//printf("%s %d\n",sym_table[i].id,sym_table[i].value);
	}
	return 0;
}