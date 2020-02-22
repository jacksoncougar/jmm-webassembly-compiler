

%union {
    struct ASTNode *a;
}

%token <a> NUMBER
%token EOL

%type <a> exp factor term

%%

