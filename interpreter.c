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
void visit_assign(Node *root){
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
void interprete(Compound *root){
	while(root!=NULL){
		visit_assign(root->item);
		root=root->child;
	}

}