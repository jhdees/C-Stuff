#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, TYPE };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
int isvalid = 0;
int main(){
    int type;
    char temp[MAXTOKEN];

   isvalid = 1;
    while(gettoken() != EOF){
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if(tokentype != '\n' || !isvalid){
        }
        else if(tokentype == '\n' && !isvalid){
            printf("There was an issue with your input: %s\n", token);
            isvalid = 1;
        }
        else{
            printf("%s: %s %s\n", name, out, datatype);
            isvalid = 1;
        }
    }

    return 0;
}

void dcl(void){
    int ns;

    for(ns = 0; gettoken() == '*';){
        ns++;
    }
    dirdcl();
    while(ns-- > 0){
        strcat(out, " pointer to");
    }
}

void dirdcl(void){
    int type;

    if(tokentype == '('){
        dcl();
        if(tokentype != ')' || tokentype != TYPE){
            isvalid = 0;
            printf("missing ')'\n");
        }
    }
    else if(tokentype == NAME){
        strcpy(name, token);
    }
    else if(tokentype == TYPE){

    }
    else{
        isvalid = 0;
        printf("tokentype: %d expected name or (dcl): %s\n", tokentype, token);
    }

    while((type = gettoken()) == PARENS || type == BRACKETS){
        if(type == PARENS){
            strcat(out, " function returning");
        }
        else{
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}
int istype(char *s);
int gettoken(void){
    int c, getch(void);
    void ungetch(int);
    char *p = token;
    while( (c = getch()) == ' ' || c == '\t'){
        ;
    }

    if(c == '(') {
        if( (c = getch()) == ')' ) {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else if(isalpha(c)){
            ungetch(c);
            return gettoken();
        }
        else{
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if( c == '[' ){
        for( *p++ = c; ( *p++ = getch()) != ']';){
            ;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if( isalpha(c) ){
        for( *p++ = c; isalnum(c = getch()); ){
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        if(istype(p)){
            return tokentype = TYPE;
        }
        return tokentype = NAME;
    }
    else{
        return tokentype = c;
    }
}

int istype(char *s){
    return strcmp("int", s) == 0 || strcmp("char", s) == 0 || strcmp("float", s) == 0;
}
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if(c == EOF){
        c = ' ';
    }
    if(bufp >= BUFSIZE){
        printf("ungetch: too many characters\n");
    }
    else{
        buf[bufp++] = c;
    }
}