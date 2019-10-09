typedef struct keywords{
	char *key;
	int type;
}keywords;

const keywords keys[]={
	{"start",START},
	{"end",END},
	{"print",PRINT}
};
Token string(char *str){
	//printf("HI string\n");
	Token token;
	token.type=STRING;
	//printf("Token type: %d\n",token.type );
	int size=0,start=pos+1;
	while(str[++pos]!='"'){
		//printf("%c\n",str[pos] );
		size++;
	}
	if(size>0)
		token.id=str+(start);
	else
		token.id=NULL;
	token.value=size;
	//printf("pos after string %d\n",size);
	return token;
}
int integer(char *str){
	int i=0;	
	char *num;
	num=(char*)malloc(sizeof(char));
	num[i]=str[pos++];
	while(str[pos]!='\0' && isdigit(str[pos])){
		num=(char*)realloc(num,(++i)*sizeof(char));
		num[i]=str[pos++];
	}
	//num[++i]='\0';
	//printf("HI %s\n", num);
	if(str[pos]=='.'){
		num=(char*)realloc(num,(++i)*sizeof(char));
		num[i]=str[pos++];
		while(str[pos]!='\0' && isdigit(str[pos])){
			num=(char*)realloc(num,(++i)*sizeof(char));
			num[i]=str[pos++];
		}
		printf("%s\n", num);
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
	while(str[pos]!='\0' && isalnum(str[pos])){
		id=(char*)realloc(id,(++i)*sizeof(char));
		id[i]=str[pos++];
		//printf("%d\n", i);
	}
	pos--;
	id[++i]='\0';
	for(i=0;i<3;i++){
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
	if(ch=='\0'){
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
	if(ch==','){
		token.type=COMMA;
		token.value=0;
		token.id=NULL;
		return token;
	}
	if(ch=='"'){
		return string(str);
	}
	printf(RED"[Interpretation error]"RESET"Scan error!! '%c' cannot be recognised as token!\n",ch);
	exit(0);
	//synerror();
}