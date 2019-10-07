enum Reserved {INT=10,ID,SUM,SUB,MULT,DIV,LPAREN,RPAREN,START,END,ASSIGN,SEMI};
typedef struct token{
	int type;
	int value;
	char *id;
}Token;
typedef struct Node{
	Token item;
	struct Node *left,*right;
}Node;
typedef struct compound{
	Node *item;
	struct compound *child;
}Compound;
int g_size=0;
int pos=0;