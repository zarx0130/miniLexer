#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// token enum
typedef enum {
	TYPE_INTEGER,
	TYPE_FLOAT,
	TYPE_STRING,
	TYPE_CHAR,
	TYPE_COMMENT,
	TYPE_TYPE,
	TYPE_RESERVED,
	TYPE_OPERATOR,
	TYPE_IDENTIFIER
} TokenType;

typedef struct {
	TokenType type;
	char lexeme[256];
	int value;
	int line;
} Token;

// global var
char current;
char lookahead;
FILE* source_file;
int line = 1;
int isEOF = 0;

// func dec
void openFile(char* filename);
void closeFile();
void nextChar ();
void printToken(Token token);
int isOperator(char c);
int isReserved(char* word);
int isType(char* word);
Token nextToken();

int main(int argc, char* argv[]) {
	if (argc != 2) return 1;
	openFile(argv[1]);

	printf("Tokenizing: %s\n", argv[1]);
	printf("-------------------\n");

	lookahead = fgetc(source_file);
	nextChar();
	// tokenization loop
	while (!isEOF) {
		Token token = nextToken();
		printToken(token);
	}
	closeFile();
	return 0;
}

void openFile(char* filename) {
	source_file = fopen(filename, "r");
	if (!source_file) exit(1);
}

void closeFile() {
	if (source_file) fclose(source_file);
}

void nextChar() {
	if (current == '\n') line++;
	current = lookahead;

	lookahead = fgetc(source_file);
	if (lookahead == EOF) isEOF = 1;
}

void printToken(Token token) {
	const char* tokenNames[] = { "INTEGER", "FLOAT", "STRING", "CHAR", "COMMENT",
		"TYPE", "RESERVED", "OPERATOR", "IDENTIFIER" };

	//printf("--TOKEN START-- \n");
	printf("%s: %s", tokenNames[token.type], token.lexeme);

	if (token.type == TYPE_INTEGER || token.type == TYPE_FLOAT) {
		printf(" (value: %d)", token.value);
	} printf("\n");

	//printf("--TOKEN END-- \n\n");
}

int isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/' ||
		c == '(' || c == ')' || c == '{' || c == '}' ||
		c == ';' || c == ',' || c == '=' || c == '<' || c == '>' ||
		c == '!' || c == '&' || c == '|');
}

int isReserved(char* word) {
	const char* reserve[] = {
   "break","case", "continue", "class", "catch",
   "do", "default", "def","else", "enum", "extends", "for",
   "false", "if", "import", "main", "new", "private",
   "public", "protected", "return", "static", "struct", "switch",
   "super", "this", "try", "while", "boolean", "char", "const",
   "double", "float", "int","long", "short", "void", "volatile", NULL };

	// check if curr word == reserve
	for (int i = 0; reserve[i] != NULL; i++) {
		if (strcmp(word, reserve[i]) == 0) {
			return 1;
		}
	} return 0;
}

int isType(char* word) {
	const char* types[] = { "boolean", "char", "const", "double", "float", "int",
		"long", "short", "void", "volatile", NULL };

	for (int i = 0; types[i] != NULL; i++) {
		if (strcmp(word, types[i]) == 0) {
			return 1;
		}
	} return 0;
}

Token nextToken() {
	Token token;
	memset(token.lexeme, 0, sizeof(token.lexeme));
	token.value = 0;
	token.line = line;

	// skip whitespace & handle EOF
	while (isspace(current)) nextChar();
	if (current == 0 && isEOF) {
		token.type = TYPE_OPERATOR;
		strcpy(token.lexeme, "EOF");
		return token;
	}

	// handle nums
	if (isdigit(current)) {
		int i = 0;
		int decimal = 0;

		while (isdigit(current) || current == '.') {
			if (current == '.') {
				if (decimal) break;
				decimal = 1;
			}
			token.lexeme[i++] = current; // handle lookahead
			nextChar();
		}
		token.lexeme[i] = '\0';
		if (decimal) {
			token.type = TYPE_FLOAT;
			token.value = atof(token.lexeme);
		} else {
			token.type = TYPE_INTEGER;
			token.value = atoi(token.lexeme);
		} return token;
	}

	// handle string
	if (current == '"') {
		int i = 0;
		nextChar();

		while (current != '"' && !isEOF) {
			token.lexeme[i++] = current;
			nextChar();
		}
		nextChar();
		token.lexeme[i] = '\0';
		token.type = TYPE_STRING;

		return token;
	}

	// handle char
	if (current == '\'') {
		int i = 0;
		nextChar();

		token.lexeme[i] = current;
		token.lexeme[i++] = '\0';
		nextChar();

		if (current == '\'') nextChar();
		token.type = TYPE_CHAR;

		return token;
	}

	// handle comment
	if (current == '/' && lookahead == '/') {
		while (current != '\n' && !isEOF) nextChar();
		token.type = TYPE_COMMENT;
		strcpy(token.lexeme, "//...");
		return token;
	} else if (current == '/' && lookahead == '*') {
		token.type = TYPE_COMMENT;
		strcpy(token.lexeme, "/*...*/");
		return token;
	} else if (current == '*' && lookahead == '/') {
		token.type = TYPE_COMMENT;
		strcpy(token.lexeme, "/*...*/");
		return token;
	} 

	// handle reserved/type/identifier
	if (isalpha(current) || current == '_') {
		int i = 0;
		while (isalnum(current) || current == '_') {
			token.lexeme[i++] = current;
			nextChar();
		} token.lexeme[i] = '\0';

		if (isReserved(token.lexeme)) {
			token.type = TYPE_RESERVED;
		} else if (isType(token.lexeme)) {
			token.type = TYPE_TYPE;
		} else {
			token.type = TYPE_IDENTIFIER;
		} return token;
	}

	// handle operator
	if (isOperator(current)) {
		token.lexeme[0] = current;

		switch (current) {
		case '=':
			if (lookahead == '=') {
				strcpy(token.lexeme, "==");
				nextChar();
			} break;
		case '!':
			if (lookahead == '=') {
				strcpy(token.lexeme, "!=");
				nextChar();
			} break;
		case '+':
			if (lookahead == '=') {
				strcpy(token.lexeme, "+=");
				nextChar();
			} else if (lookahead == '+') {
				strcpy(token.lexeme, "++");
				nextChar();
			} break;
		case '-':
			if (lookahead == '=') {
				strcpy(token.lexeme, "-=");
				nextChar();
			} else if (lookahead == '-') {
				strcpy(token.lexeme, "--");
				nextChar();
			} break;
		case '>':
			if (lookahead == '=') {
				strcpy(token.lexeme, ">=");
				nextChar();
			} break;
		case '<':
			if (lookahead == '=') {
				strcpy(token.lexeme, "<=");
				nextChar();
			} break;
		case '&':
			if (lookahead == '&') {
				strcpy(token.lexeme, "&&");
				nextChar();
			} break;
		case '|':
			if (lookahead == '|') {
				strcpy(token.lexeme, "||");
				nextChar();
			} break;
		default: // single op
			token.lexeme[1] = '\0';
			break;
		}

		token.type = TYPE_OPERATOR;
		nextChar();
		return token;
	}
}