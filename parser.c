Node* factor(char *str, Node*, Token current_token);
Node* expr(char *str, Node*, Token current_token);
Node* term(char *str, Node*, Token current_token);
Node* biop(Node* root, Node *left, Token item, Node *right);
Node* leaf(Node* root,Token item);
void match(int current_token_type,int type);
void printInorder(Node*);

//int pos=0;
Compound* set_comp(Compound *root, Compound *child,Node *item){
	root->item=item;
	root->child=child;
	return root;
}
Node* biop(Node* root, Node *left, Token item, Node *right){
	//printf("Hi biop\n");
	root->item=item;
	root->left=left;
	root->right=right;
	//printf("Hi biop over\n");
	return root;
}
Node* leaf(Node* root,Token item){
	if(root==NULL)
		root=(Node*)malloc(sizeof(Node));
	//printf("Hi leaf\n");
	root->item=item;
	root->left=root->right=NULL;
	return root;
}
void match(int current_token_type,int type){
	if(current_token_type==type){
		pos++;
		return;
	}
	//printf("%d %d %d\n",current_token_type,type,pos);
	printf(RED"[Interpretation error]"RESET"Parse error!!\n");
	exit(0);
	//synerror();
}
Node* factor(char *str,Node *root,Token current_token){
	Token op;
	Node *temp;
	if(root==NULL)
		root=(Node*)malloc(sizeof(Node));
	if(current_token.type==SUM||current_token.type==SUB){
		pos++;
		op=current_token;
		current_token=scanner(str,str[pos]);
		//printf("%d\n",current_token.value);
		//Node *tnode=leaf(root,current_token);
		temp=biop(root,factor(str,NULL,current_token),op,NULL);
		//printf("temp inorder:\n");
		//printInorder(temp);
		//printf("result=%d op=%d c_token=%d\n",result,op.type,current_token.value);
		return temp;
	}
	if(current_token.type==LPAREN){
		pos++;
		current_token=scanner(str,str[pos]);
		temp=expr(str,root,current_token);
		current_token=scanner(str,str[pos]);
		//printf("type=%d\n",current_token.type);
		match(current_token.type,RPAREN);
		return temp;
	}
	//printf("HI\n");
	if(current_token.type==ID){
		temp=leaf(root,current_token);pos++;
		return temp;
	}
	match(current_token.type,INT);
	temp=leaf(root,current_token);
	//printf("HI factor %d\n",current_token.value);
	//printInorder(temp);
	return temp;
}

Node* term(char *str,Node *root,Token current_token){
	Token op;
	//printf("HI\n");
	root=factor(str,root,current_token);
	int rev_pos=pos;
	current_token=scanner(str,str[pos]);
	while(str[pos]!='\0' && str[pos]!='\n' && (current_token.type==MULT || current_token.type==DIV)){
		op=current_token;pos++;
		Node *temp=(Node*)malloc(sizeof(Node));
		current_token=scanner(str,str[pos]);
		root=biop(temp,root,op,factor(str,NULL,current_token));
		rev_pos=pos;
		current_token=scanner(str,str[pos]);
	}
	pos=rev_pos;
	return root;
}

Node* expr(char *str,Node *root,Token current_token){
	Token op;
	//printf("HI\n");
	root=term(str,root,current_token);
	int rev_pos=pos;
	current_token=scanner(str,str[pos]);
	//printf("%c\n",str[pos]);
	//printf("%d\n",current_token.type);
	while(str[pos]!='\0' && str[pos]!='\n' && (current_token.type==SUM || current_token.type==SUB)){
		op=current_token;pos++;
		//printf("HI while expr\n");
		Node *temp=(Node*)malloc(sizeof(Node));
		current_token=scanner(str,str[pos]);
		root=biop(temp,root,op,term(str,NULL,current_token));
		rev_pos=pos;
		//current_token=scanner(str,str[pos]);
		//root=biop(term(str,root,current_token);
		current_token=scanner(str,str[pos]);
	}
	pos=rev_pos;
	return root;
}
Node* assign(char *str,Node *root,Token current_token){
	Token token;
	root=(Node*)malloc(sizeof(Node));
	//root=set_comp(root,)
	//match(current_token.type,ID);//pos--;
	//printf("assign: %d\n",pos);
	//printf("str[pos]=%c\n",str[pos]);
	root=leaf(root,current_token);//printf("%s\n",(root->item).id);
	current_token=scanner(str,str[pos]);//printf("%d\n",current_token.value);
	match(current_token.type,ASSIGN);
	token=current_token;
	current_token=scanner(str,str[pos]);//pos++;
	Node *temp=(Node*)malloc(sizeof(Node));
	temp=biop(temp,root,token,expr(str,NULL,current_token));
	return temp;
}
Node* statement(char *str,Node *root,Token current_token){
	if(current_token.type==ID){
		root=assign(str,root,current_token);
		g_size++;
	}
	else if(current_token.type==PRINT){
		root=leaf(NULL,current_token);pos++;
		Node *temp=root;
		int rev_pos=pos;
		current_token=scanner(str,str[pos]);
		if(current_token.type==ID||current_token.type==INT){
			temp->right=(Node*)malloc(sizeof(Node));
			temp=temp->right;
			(temp->item).type=EXPR;
			temp->left=expr(str,NULL,current_token);
			temp->right=NULL;
		}
		else{
			pos++;
			temp->right=leaf(NULL,current_token);
			temp=temp->right;
		}
		current_token=scanner(str,str[pos]);
		while(current_token.type!=SEMI){
			match(current_token.type,COMMA);
			current_token=scanner(str,str[pos]);
			if(current_token.type==ID||current_token.type==INT||current_token.type==LPAREN){
				temp->right=(Node*)malloc(sizeof(Node));
				temp=temp->right;
				(temp->item).type=EXPR;
				temp->left=expr(str,NULL,current_token);
				temp->right=NULL;
			}
			else{
				temp->right=leaf(NULL,current_token);pos++;
				temp=temp->right;
			}
			current_token=scanner(str,str[pos]);
		}
	}
	else
		pos++;
	return root;
}
Compound* compound(char *str,Compound *root,Token current_token){
	root=(Compound*)malloc(sizeof(Compound));
	root=set_comp(root,NULL,statement(str,NULL,current_token));
	Compound *temp=root;
	int rev_pos=pos;
	current_token=scanner(str,str[pos]);
	while(current_token.type==SEMI){
		match(current_token.type,SEMI);
		rev_pos=pos;
		current_token=scanner(str,str[pos]);pos++;
		if (current_token.type!=ID && current_token.type!=PRINT)
			break;
		temp->child=set_comp((Compound*)malloc(sizeof(Compound)),NULL,statement(str,NULL,current_token));
		temp=temp->child;
		current_token=scanner(str,str[pos]);
	}
	pos=rev_pos;
	return root;
}
Compound* program(char *str,Compound *root,Token current_token){
	match(current_token.type,START);
	current_token=scanner(str,str[pos]);pos++;
	root=compound(str,NULL,current_token);
	current_token=scanner(str,str[pos]);
	match(current_token.type,END);
	return root;
}
void printInorder(Node* node) 
{ 
     if (node == NULL){
     	//printf("Empty ");
        return; 
     }
  	//printf("Hi inorder\n");
     /* first recur on left child */
    printInorder(node->left); 
  
     /* then print the data of node */
     //if((node->item).type==INT)
     	//printf("%d %s\n", (node->item).value,(node->item).id);
     //else   
  		printf("%d ", (node->item).type);
     /* now recur on right child */
     printInorder(node->right); 
} 
Compound* parser(char *str){
	Compound* root=NULL;
	Token current_token=scanner(str,str[pos]);
	root=program(str,root,current_token);
	//printInorder(root);
	return root;
}