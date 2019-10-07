typedef struct keywords{
	char *key;
	int type;
}keywords;

const keywords keys[]={
	{"start",START},
	{"end",END},
};
int integer(char *str){
	int i=0;	
	char *num;
	num=(char*)malloc(sizeof(char));
	num[i]=str[pos++];
	while(str[pos]!=EOF && isdigit(str[pos])){
		num=(char*)realloc(num,(++i)*sizeof(char));
		num[i]=str[pos++];
		//printf("%d\n", i);
	}
	pos--;
	num[++i]='\0';
	//printf("%s\n",num);
	return atoi(num);
}
Token get_id(char *str){
	//printf("Hi\n");
	int i=0;	
	char *id;
	Token token;
	id=(char*)malloc(sizeof(char));
	id[i]=str[pos++];
	while(str[pos]!=EOF && isalnum(str[pos])){
		id=(char*)realloc(id,(++i)*sizeof(char));
		id[i]=str[pos++];
		//printf("%d\n", i);
	}
	pos--;
	id[++i]='\0';
	for(i=0;i<2;i++){
		//printf("Hi\n");
		if(!strcmp(id,keys[i].key)){
			token.id=id;
			token.type=keys[i].type;
			token.value=0;
			//printf("Hi token is %s\n",id);
			return token;
		}
	}
	//printf("Hi token is %s\n",id);
	token.id=id;
	token.type=ID;
	token.value=0;
	return token;		
	//printf("%s\n",num);
}

Token scanner(char *str,char ch){
	Token token;
	//printf("ch=%c\n",ch);
	while(ch== ' '||ch=='\n'){
		ch=str[++pos];
		//printf("%c\n",ch);
	}
	if(ch==';'){
		//token=(ASSGN,0,NULL);
		token.type=SEMI;
		token.value=0;
		token.id=NULL;
		return token;
	}
	if(ch=='='){
		//token=(ASSGN,0,NULL);
		token.type=ASSIGN;
		token.value=0;
		token.id="=";
		return token;
	}
	if(ch== '\n'||ch==EOF){
		token.type=EOF;
		token.value=EOF;
		token.id=NULL;
		return token;
		//printf("%c\n",ch);
	}
	if(ch=='('){
		token.type=LPAREN;
		token.value='(';
		return token;
	}
	if(ch==')'){
		token.type=RPAREN;
		token.value=')';
		token.id=NULL;
		return token;
	}
	if(isalpha(ch)){
		//token.type=ID;
		//Token token=get_id(str);
		//printf("%s",token.id);
		return get_id(str);//token;
	}
	if(isdigit(ch)){
		token.type=INT;
		token.value=integer(str);
		token.id=NULL;
		return token;
	}
	if(ch=='+'){
		token.type=SUM;
		token.value='+';
		token.id=NULL;
		return token;
	}
	if(ch=='-'){
		token.type=SUB;
		token.value='-';
		token.id=NULL;
		return token;
	}
	if(ch=='*'){
		token.type=MULT;
		token.value='*';
		token.id=NULL;
		return token;
	}
	if(ch=='/'){
		token.type=DIV;
		token.value='/';
		token.id=NULL;
		return token;
	}
	printf(RED"[Interpretation error]"RESET"Scan error!! '%c' cannot be recognised as token!\n",ch);
	//exit(0);
	//synerror();
}