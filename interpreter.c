typedef struct Table
{
	char *id;
	int value;
}Table;
Table *sym_table;//(Table*)malloc(sizeof(Table));
int size_sym=0;
int value_expr(Node *root){
	if(root==NULL)
		return 0;
	if((root->item).type==SUB && root->right==NULL)
		return -value_expr(root->left);
	if((root->item).type==SUM && root->right==NULL)
		return +value_expr(root->left);
	if((root->item).type==SUM)
		return value_expr(root->left)+value_expr(root->right);
	if((root->item).type==SUB)
		return value_expr(root->left)-value_expr(root->right);
	if((root->item).type==MULT)
		return value_expr(root->left)*value_expr(root->right);
	if((root->item).type==DIV)
		return value_expr(root->left)/value_expr(root->right);
	if((root->item).type==ID){
		int i=0;
		while(i<size_sym){
			if(!strcmp(sym_table[i].id,(root->item).id)){
				return sym_table[i].value;
			}
			i++;
		}
		printf("%s not found!\n",sym_table[i].id );
		return '\0';
	} 
	return (root->item).value;
}
void visit_comp(Node *root){
	//printf("Hi I am running\n");
	if((root->item).type==ASSIGN){
		//printf("Hi welcome to assign\n");
		int i=0;
		while(i<size_sym){
			if(!strcmp(sym_table[i].id,((root->left)->item).id)){
				sym_table[i].value=value_expr(root->right);
				return;
			}
			i++;
		}
		if(!size_sym)
			sym_table=(Table*)malloc(sizeof(Table));
			//printf("hi\n");
		else
			sym_table=(Table*)realloc(sym_table,(i+1));
		sym_table[i].id=(char*)malloc(sizeof(((root->left)->item).id));//*(sizeof(char)));
		strcpy(sym_table[i].id,((root->left)->item).id);
		//printf("hi 2\n");
		sym_table[i].value=value_expr(root->right);
		//printf("%d\n",size_sym);
		size_sym++;
	}
}
void visit_print(Node *root){
	//printf("Hi\n");
			//printf("Hi interpreter\n");
	while(root!=NULL){
		Token token=root->item;
		if(token.type==STRING){
			int size=token.value;
			char *out=token.id;
		//printf("%d\n",token.value);
			if(out==NULL){
			//printf("NULL pointer\n",size);
				return;
			}
			for(int i=0; i<size; i++)
				printf("%c",out[i]);
			root=root->right;
		}
		if(token.type==ID){
			//int i=0;
			//printf("Hi\n");
			for(int i=0; i<size_sym; i++){
				if(!strcmp(sym_table[i].id,token.id)){
					//printf("Hi\n");
					printf("%d",sym_table[i].value);
					break;
				}
			}
			root=root->right;
			//printf("%s not found!\n",token.id );
		}
	}
	printf("\n");
}
void interprete(Compound *root){
	//printf("Hi\n");
	while(root!=NULL){
		if(((root->item)->item).type==PRINT){
			//printf("Hi\n");
			visit_print((root->item)->right);
		}
		//printf("Hi\n");
		visit_comp(root->item);
		root=root->child;
	}

}