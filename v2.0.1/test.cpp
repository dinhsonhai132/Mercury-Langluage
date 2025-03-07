#include <vector>
#include <string>
#include <iostream>
#include <string.h>
using namespace std;

#define Program "Program"
#define PrintStatement "PrintStatement"
#define LetStatement "LetStatement"
#define ExpressionStatement "ExpressionStatement"
#define BlockStatement "BlockStatement"
#define ReturnStatement "ReturnStatement"
#define Expression "Expression"
#define FunctionStatement "FunctionStatement"
#define FunctionCallExpression "FunctionCallExpression"
#define CallExpression "CallExpression"
#define Identifier_ "Identifier"
#define Literal "Literal"
#define IntegerLiteral "IntegerLiteral"
#define StringLiteral "StringLiteral"
#define BinaryExpression "BinaryExpression"
#define StringExpression "StringExpression"

#define EOF_T "EOF"
#define ASSIGN "ASSIGN"
#define MOD "MOD"
#define INT_ "INT_"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define DIV "DIV"
#define TIME "TIME"
#define VARIABLE "VARIABLE"
#define STRING "STRING"
#define PRINT "PRINT"
#define LET "LET"
#define DOT "DOT"
#define COMMA "COMMA"
#define ASSIGN "ASSIGN"
#define IF "IF"
#define ELSE "ELSE"
#define FOR "FOR"
#define WHILE "WHILE"
#define RETURN "RETURN"
#define FUNCTION "FUNCTION"
#define LEFT_PAREN "LEFT_PAREN"
#define RIGHT_PAREN "RIGHT_PAREN"
#define LEFT_BRACKET "LEFT_BRACKET"
#define RIGHT_BRACKET "RIGHT_BRACKET"
#define LEFT_BRACE "LEFT_BRACE"
#define RIGHT_BRACE "RIGHT_BRACE"
#define EQUAL "EQUAL"
#define NOT_EQUAL "NOT_EQUAL"
#define LESS "LESS"
#define LESS_EQUAL "LESS_EQUAL"
#define GREATER "GREATER"
#define GREATER_EQUAL "GREATER_EQUAL"
#define AND "AND"
#define OR "OR"
#define NOT "NOT"
#define BREAK "BREAK"
#define CONTINUE "CONTINUE"
#define CLASS "CLASS"
#define INTERFACE_ "INTERFACE_"
#define STRUCT "STRUCT"
#define NEW "NEW"
#define DELETE_ "DELETE_"
#define CAST "CAST"
#define FLOAT_ "FLOAT"
#define DOUBLE_ "DOUBLE"
#define CHAR_ "CHAR"
#define SHORT_ "SHORT"
#define LONG_ "LONG"
#define AUTO_ "AUTO"
#define VOID_ "VOID"
#define BOOL_ "BOOL"
#define SEMICOLON "SEMICOLON"
#define COLON "COLON"
#define ARROW "ARROW"
#define COMMENT "COMMENT"
#define INCLUDE "INCLUDE"
#define EXTERN "EXTERN"
#define USING "USING"
#define POW "POW"
#define CONST_ "CONST"
#define ARG "ARG"
#define KWARG "KWARG"
#define FUNCTION_CALL "FUNCTION_CALL"

#define INT_T "INT_T"
#define FLOAT_T "FLOAT_T"
#define DOUBLE_T "DOUBLE_T"
#define STRING_T "STRING_T"
#define AUTO_T "AUTO_T"
#define NULL_T "NULL_T"
#define VOID_T "VOID_T"
#define BOOL_T "BOOL_T"
#define CHAR_T "CHAR_T"
#define SHORT_T "SHORT_T"
#define LONG_T "LONG_T"
#define LITERAL_T "LITERAL_T"
#define FUNCTION_T "FUNCTION_T"
#define ARRAY_T "ARRAY_T"
#define STRUCT_T "STRUCT_T"
#define POINTER_T "POINTER_T"
#define CLASS_T "CLASS_T"
#define INTERFACE__T "INTERFACE__T"

#define MAX 1024

#define LITERAL {INT_, FLOAT_, DOUBLE_}
#define IDENTIFIER {DIV, MOD, PLUS, TIME, MINUS}
#define EXPR {PLUS, MINUS, DIV, TIME, MOD, INT_, FLOAT_, DOUBLE_}
#define TYPE {INT_T, FLOAT_T, DOUBLE_T, CHAR_T, SHORT_T, LONG_T, AUTO_T, VOID_T, BOOL_T, STRING_T, STRUCT_T, CLASS_T}

struct token {
    string tok;
    string type;
    float value;

    string name;
    string symbol;
    string string_iden;

    token() : tok(""), type(""), value(0.0), name(""), symbol(""), string_iden("") {};
    token(string tok, string type, float value, string name, string symbol, string string_iden) : tok(tok), type(type), value(value), name(name), symbol(symbol), string_iden(string_iden) {}
};


static inline bool isskippable(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
};

static inline bool is_potential_identifier_char(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

static inline string get_2_char(char c1, char c2)
{
    switch (c1)
    {
    case '=':
        if (c2 == '=')
            return EQUAL;
        break;
    case '<':
        if (c2 == '=')
            return LESS_EQUAL;
        if (c2 == '>')
            return NOT_EQUAL;
        break;
    case '>':
        if (c2 == '=')
            return GREATER_EQUAL;
        break;
    case '&':
        if (c2 == '&')
            return AND;
        break;
    case '|':
        if (c2 == '|')
            return OR;
        break;
    case '*':
        if (c2 == '*')
            return POW;
        break;
    case '!':
        if (c2 == '=')
            return NOT_EQUAL;
        break;
    }
    return "";
}

static inline string get_1_char(char c)
{
    switch (c) {
        case '=':
            return ASSIGN;
        case '<':
            return LESS;
        case '>':
            return GREATER;
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '/':
            return DIV;
        case '*':
            return TIME;
        case '!':
            return NOT;
        case '(':
            return LEFT_PAREN;
        case ')':
            return RIGHT_PAREN;
        case '{':
            return LEFT_BRACE;
        case '}':
            return RIGHT_BRACE;
        case '[':
            return LEFT_BRACKET;
        case ']':
            return RIGHT_BRACKET;
        case ',':
            return COMMA;
        case ';':
            return SEMICOLON;
        case ':':
            return COLON;
        case '.':
            return DOT;
        case '%':
            return MOD;
    }

    return "";
}

static inline bool is_identifier(string iden)
{
    vector<string> state = {"LET", "PRINT", "IF", "ELSE", "FOR",
                            "WHILE", "RETURN", "FUNC", "INT", "FLOAT", "DOUBLE", "CHAR",
                            "SHORT", "LONG", "AUTO", "VOID", "BOOL", "CHAR", "STRING",
                            "STRUCT", "CLASS", "INTER", "NEW", "DELETE_", "CAST",
                            "TRUE", "", "BREAK", "CONTINUE"};
    for (string s : state)
    {
        if (iden == s)
            return true;
    }
    return false;
}

static inline string return_identifier(string iden) {
    if (iden == "LET")
        return LET;
    else if (iden == "PRINT")
        return PRINT;
    else if (iden == "IF")
        return IF;
    else if (iden == "ELSE")
        return ELSE;
    else if (iden == "FOR")
        return FOR;
    else if (iden == "WHILE")
        return WHILE;
    else if (iden == "RETURN")
        return RETURN;
    else if (iden == "FUNC")
        return FUNCTION;
    else if (iden == "INT")
        return INT_;
    else if (iden == "FLOAT")
        return FLOAT_;
    else if (iden == "DOU")
        return DOUBLE_;
    else if (iden == "CHAR")
        return CHAR_;
    else if (iden == "SHORT")
        return SHORT_;
    else if (iden == "LONG")
        return LONG_;
    else if (iden == "AUTO")
        return AUTO_;
    else if (iden == "VOID")
        return VOID_;
    else if (iden == "BOOL")
        return BOOL_;
    else if (iden == "CHAR")
        return CHAR_;
    else if (iden == "STR")
        return STRING;
    else if (iden == "STRUCT")
        return STRUCT;
    else if (iden == "CLASS")
        return CLASS;
    else if (iden == "INTER")
        return INTERFACE_;
    else if (iden == "NEW")
        return NEW;
    else if (iden == "DEL")
        return DELETE_;
    else if (iden == "CAST")
        return CAST;
    else if (iden == "BRK")
        return BREAK;
    else if (iden == "CONT")
        return CONTINUE;
    else if (iden == "INC")
        return INCLUDE;
    else if (iden == "EXT")
        return EXTERN;
    else if (iden == "USING")
        return USING;
    else if (iden == "CONS")
        return CONST_;

    return "";
}

static inline bool is_keyword(char c)
{
    vector<char> keyword = {
        '+', '-', '*', '/', '(', ')', '{', '}',
        '[', ']', ',', ';', ':', '=', '!', '<',
        '>', '&', '|'};
    for (char k : keyword)
    {
        if (c == k)
            return true;
    }
    return false;
}


vector<token> MerLexer_tokenize(string source)
{
    int idx = 0;
    vector<token> tokens;
    while (idx < source.length())
    {
        char c = source[idx];

        if (is_potential_identifier_char(c))
        { // execute char identifier and syntax
            string iden = "";
            bool found = false;

            while (is_potential_identifier_char(c))
            {
                iden += c;
                idx++;
                if (idx >= source.length())
                    break;
                c = source[idx];
            }

            if (is_identifier(iden))
            {
                tokens.push_back(token(return_identifier(iden), NULL_T, 0.0, "", iden.c_str(), ""));
            }
            else
            {
                tokens.push_back(token(VARIABLE, NULL_T, 0.0, "", iden.c_str(), ""));
            }
        }
        else if (isdigit(c))
        { // execute number
            string num = "";
            int dot_count = 0;
            while (isdigit(c) || c == '.')
            {
                if (c == '.')
                {
                    dot_count++;
                    if (dot_count > 1)
                        break;
                }
                num += c;
                idx++;
                if (idx >= source.length())
                    break;
                c = source[idx];
            }

            float num_value = atof(num.c_str());
            tokens.push_back(token(dot_count == 0 ? INT_ : FLOAT_,
                                   dot_count == 0 ? INT_T : FLOAT_T, num_value, "", num.c_str(), ""));
        }
        else if (c == '"')
        { // execute string
            string str = "";
            idx++;
            while (source[idx] != '"')
            {
                str += source[idx];
                idx++;
            }
            tokens.push_back(token(STRING, STRING_T, 0.0, "", "", str.c_str()));
            idx++;
        } else if (c == '!')
        { //define function call
            char c2 = source[idx + 1];
            string name;
            if (is_potential_identifier_char(c2)) {
                idx++;
                while (is_potential_identifier_char(c2)) {
                    name += c2;
                    idx++;
                    if (idx >= source.length()) {
                        break;
                    }
                    c2 = source[idx];
                }
            }
            tokens.push_back(token(FUNCTION_CALL, AUTO_T, 0.0, name.c_str(), name.c_str(), name.c_str()));
        }
        else if (is_keyword(c))
        { // execute keyword
            char c2 = source[idx + 1];
            if (is_keyword(c2))
            {
                string keyword = string(1, c) + string(1, c2);
                tokens.push_back(token(get_2_char(c, c2), NULL_T, 0.0, "", keyword.c_str(), ""));
                idx += 2;
            }
            else
            {
                tokens.push_back(token(get_1_char(c), NULL_T, 0.0, "", string(1, c), ""));
                idx++;
            }
        }
        else if (isskippable(c))
        {
            idx++;
        }
        else
        {
            idx++;
        }
    }
    tokens.push_back(token(EOF_T, NULL_T, 0.0, "", "\n", ""));
    return tokens;
}

// ast
struct AST_node {
    string type;
    string tok;
    float value = 0.0;
    string string_iden;
    AST_node *poutput;

    bool is_constant;
    bool is_global;
    bool is_local;
    bool is_list;
    string var_name;
    string data_type;
    AST_node *var_value;
    vector<AST_node*> elements;
    bool is_None;

    string func_name;
    vector<AST_node*> body;
    vector<AST_node*> args;
    int args_size;
    AST_node *calle;
    float return_value;
    string func_type;

    string func_call;

    string op;
    AST_node* left;
    AST_node* right;
    bool condtion;

    string list_name;
    string list_type;
    vector<AST_node*> list;

    vector<AST_node*> children;
};

AST_node *MerAST_make(string type, string tok, float value, string dt) {
    AST_node* node = new AST_node();
    node->tok = tok;
    node->value = value;
    node->data_type = dt;
    node->type = type;
    return node;
}

AST_node *MerAST_make_parent(string type) {
    AST_node* node = new AST_node();
    node->type = type;
    return node;
}

bool Is_tok_eof(token tok) {
    return tok.tok == EOF_T;
}

bool Is_tok_type(token tok) {
    for (auto &tk : TYPE) {
        if (tk == tok.tok) {
            return true;
        }
    }
    return false;
}

bool Is_tok_literal(string tok) {
    for (auto &tk : LITERAL) {
        if (tk == tok) {
            return true;
        }
    }
    return false;
}

bool Is_tok_identifier(string tok) {
    for (auto &tk : IDENTIFIER) {
        if (tk == tok) {
            return true;
        }
    }
    return false;
}

bool Is_tok_expression(string tok) {
    for (auto &tk : EXPR) {
        if (tk == tok) {
            return true;
        }
    }
    return false;
}

// Parser
class Parser {
private:
    vector<token> tokens;
    int idx;
    token cur_tok;
    AST_node *program;

public:
    Parser(vector<token> tokens) : tokens(tokens), idx(0) {}

    bool look_ahead(string tok, int n);

    token get_ctok();
    token get_ntok();
    token jump_tok(int n);

    AST_node *MerParser_program();
    AST_node *MerParser_primary();
    AST_node *MerParser_additive_expression();
    AST_node *MerParser_multiplicative_expression();
    AST_node *MerParser_function_call_statement();
    AST_node *MerParser_let_statement();
    AST_node *MerParser_statement();
    AST_node *MerParser_binary_expression(AST_node *left, AST_node *right, string op);
};

token Parser::get_ctok() {
    if (idx >= tokens.size()) {
        return tokens[tokens.size() - 1];
    }
    return cur_tok = tokens[idx];
}

token Parser::get_ntok() {
    idx++;
    if (idx >= tokens.size()) {
        return tokens[tokens.size() - 1];
    }
    return cur_tok = tokens[idx];
}

token Parser::jump_tok(int n) {
    idx += n;
    if (idx >= tokens.size()) {
        return tokens[tokens.size() - 1];
    }

    return cur_tok = tokens[idx];
}

bool Parser::look_ahead(string tok, int n) {
    return tokens[idx + n].tok == tok;
}

AST_node *Parser::MerParser_program() {
    program = MerAST_make_parent(Program);
    cur_tok = get_ctok();

    program->children.push_back(MerParser_statement());
    return program;
}

AST_node *Parser::MerParser_statement() {
    AST_node *node = MerAST_make_parent(ExpressionStatement);
    cur_tok = get_ctok();
    while (!Is_tok_eof(cur_tok)) {
        if (cur_tok.tok == LET) {
            node->children.push_back(MerParser_let_statement());
            cur_tok = get_ntok();
        } else if (cur_tok.tok == FUNCTION_CALL) {
            node->children.push_back(MerParser_function_call_statement());
            cur_tok = get_ntok();
        } else {
            node->children.push_back(MerParser_additive_expression());
        }
    }
    return node;
}

AST_node *Parser::MerParser_primary() {
    cur_tok = get_ctok();
    
    if (Is_tok_identifier(cur_tok.tok)) {
        return MerAST_make(Identifier_, cur_tok.tok, cur_tok.value, cur_tok.type);
    } else if (Is_tok_literal(cur_tok.tok)) {
        return MerAST_make(Literal, cur_tok.tok, cur_tok.value, cur_tok.type);
    }
    cerr << "Lỗi: Token không hợp lệ!\n";
    return nullptr;
}

AST_node *Parser::MerParser_let_statement() {
    AST_node *node = MerAST_make_parent(LetStatement);
    cur_tok = get_ctok();
    
    if (cur_tok.tok == LET) {  
        node->is_local = true;
    } else if (cur_tok.tok == CONST_) {
        node->is_constant = true;
    } else {
        throw runtime_error("Error: Invalid token LET | CONST " + cur_tok.tok + "!");
    }

    cur_tok = get_ntok();
    if (Is_tok_identifier(cur_tok.tok)) {
        node->var_name = cur_tok.name;
        cur_tok = get_ntok();
        if (cur_tok.tok == ASSIGN) {
            cur_tok = get_ntok();
            if (cur_tok.tok == LEFT_BRACE) {
                node->is_list = true;
                while (cur_tok.tok != RIGHT_BRACE) {
                    if (cur_tok.tok == COMMA) {
                        cur_tok = get_ntok();
                    } else {
                        node->elements.push_back(MerParser_additive_expression());
                        cur_tok = get_ntok();
                    }
                }
            } else {
                node->var_value = MerParser_additive_expression();
            }
        } else {
            node->is_None = true;
            node->var_value = nullptr;
        }
    }
    node->data_type = AUTO_T;
    return node;
}

AST_node *Parser::MerParser_function_call_statement() {
    AST_node *node = MerAST_make_parent(FunctionCallExpression);
    cur_tok = get_ctok();
    if (cur_tok.tok == FUNCTION_CALL) {
        node->func_call = cur_tok.name;
        cur_tok = get_ntok();
        if (cur_tok.tok == LEFT_PAREN) {
            cur_tok = get_ntok();
            while (cur_tok.tok != RIGHT_PAREN) {
                if (cur_tok.tok == COMMA) {
                    cur_tok = get_ntok();
                } else {
                    node->args.push_back(MerParser_additive_expression());
                    cur_tok = get_ntok();
                }
            }
        }
    }
    node->func_type = AUTO_T;
    return node;
}

AST_node *Parser::MerParser_additive_expression() {
    AST_node *left = MerParser_multiplicative_expression();

    while (cur_tok.tok == PLUS || cur_tok.tok == MINUS) {
        string op = cur_tok.tok;
        cur_tok = get_ntok();

        if (Is_tok_eof(cur_tok)) {
            cout << "Lỗi: Phép toán " << op << " thiếu toán hạng bên phải!\n";
            return left;
        }

        AST_node *right = MerParser_multiplicative_expression();
        left = MerParser_binary_expression(left, right, op);
    }
    return left;
}

AST_node *Parser::MerParser_multiplicative_expression() {
    AST_node *left = MerParser_primary();

    cur_tok = get_ntok();
    while (cur_tok.tok == TIME || cur_tok.tok == DIV || cur_tok.tok == MOD) {
        string op = cur_tok.tok;
        cur_tok = get_ntok();

        if (Is_tok_eof(cur_tok)) {
            cout << "Lỗi: Phép toán " << op << " thiếu toán hạng bên phải!\n";
            return left;
        }

        AST_node *right = MerParser_primary();
        left = MerParser_binary_expression(left, right, op);
        cur_tok = get_ntok();
    }
    return left;
}

AST_node *Parser::MerParser_binary_expression(AST_node *left, AST_node *right, string op) {
    if (!left || !right) {
        cout << "Lỗi: Biểu thức nhị phân " << op << " bị thiếu toán hạng!\n";
        return nullptr;
    }

    AST_node *node = MerAST_make_parent(BinaryExpression);
    node->left = left;
    node->right = right;
    node->op = op;
    return node;
}

AST_node *MerAST_make_ast(vector<token> tokens) {
    Parser parser(tokens);
    return parser.MerParser_program();
}

// object

#define SUCCESS 0;
#define FAILURE 1;

struct MerObject {
    
    string file_name;
    string objtype;
    int ovalue;

    bool is_mom;
    string mom_name;
    string mom_t;

    string iden;
    float rvalue;
    float fvalue;
    string svalue;
    double dvalue;
    bool bvalue;

    float args_value;
    string args_type;
    bool is_func_v;

    bool is_constant;
    bool is_args;
    bool is_kwargs;
    bool is_global;
    bool iserrt;
    MerObject *objv;
};

MerObject *MerObject_new(void);
int MerObject_free(MerObject *obj);


MerObject *MerObject_new(void) {
    MerObject *obj = (MerObject *)malloc(sizeof(MerObject));
    obj->objtype = "";
    obj->file_name = "";
    obj->ovalue = 0;
    obj->is_mom = false;
    obj->mom_name = "";
    obj->mom_t = "";
    obj->iden = "";
    obj->rvalue = 0.0;
    obj->fvalue = 0.0;
    obj->svalue = "";
    obj->dvalue = 0.0;
    obj->bvalue = false;
    obj->args_value = 0.0;
    obj->args_type = "";
    obj->is_func_v = false;
    obj->is_constant = false;
    obj->is_args = false;
    obj->is_kwargs = false;
    obj->is_global = false;
    obj->iserrt = false;
    obj->objv = NULL;
    return obj;
}


int MerObject_free(MerObject *obj) {
    if (obj->iserrt) {
        return FAILURE
    }

    free(obj);
    return SUCCESS;
}

// run time
#define Number "number"
#define Null "null"
#define String "string"

struct RunTimeVal {
    string type;
    float value;
    string svalue;

    MerObject *ovalue;
    string string_iden;
};

RunTimeVal valuelize(string type, float value);
RunTimeVal *valuelize_as_ptr(string type, float value);

RunTimeVal valuelize(string type, float value) {
    RunTimeVal val;
    val.type = type;
    val.value = value;
    return val;
}

RunTimeVal *valuelize_as_ptr(string type, float value) {
    RunTimeVal *val;
    val->type = type;
    val->string_iden = value;
    return val;
}
// variable

struct Variable {
    string name;
    RunTimeVal *value;
    AST_node *nvalue;
    MerObject *ovalue;
};

bool is_declared(string name, vector<Variable> *variables);
Variable declared(string name, RunTimeVal *value, vector<Variable> *variables);
RunTimeVal *lookup(string name, vector<Variable> *variables);
Variable make_variable(string name, RunTimeVal *value);

Variable make_variable(string name, RunTimeVal *value) {
    if (!value) {
        throw runtime_error("Variable value is null: " + name);
    }
    return { name, value };
}

Variable declared(string name, RunTimeVal *value, vector<Variable> *variables) {
    if (is_declared(name, variables)) {
        throw runtime_error("Variable already declared: " + name);
    }
    
    Variable variable = make_variable(name, value);
    variables->push_back(variable);
    return variable;
}

RunTimeVal *lookup(string name, vector<Variable> *variables) {
    for (auto& var : *variables) {
        if (var.name == name) return var.value;
    }

    throw runtime_error("Variable not found: " + name);
}

bool is_declared(string name, vector<Variable> *variables) {
    for (const auto& var : *variables) {
        if (var.name == name) return true;
    }
    return false;
}
// envi

class Envi {
private:
    Envi *parent;
    vector<Variable> variables;
public:

    Envi (Envi *parentENV) {
        this->parent = parentENV;
        this->variables = vector<Variable>();
    }

    RunTimeVal *MerEnvi_declare_var(string name, RunTimeVal *value, vector<Variable> *variables);
    RunTimeVal *MerEnvi_assign_var(string name, RunTimeVal *value, vector<Variable> *variables);
    Envi MerEnvi_resolve(string name, vector<Variable> &variables);
    RunTimeVal *MerEnvi_lookup(string name, vector<Variable> &variables);
};
    

RunTimeVal *Envi::MerEnvi_declare_var(string name, RunTimeVal *value, vector<Variable> *variables) {
    Variable var = declared(name, value, variables);
    return value;
}

RunTimeVal *Envi::MerEnvi_assign_var(string name, RunTimeVal *value, vector<Variable> *variables) {
    const Envi env = MerEnvi_resolve(name, *variables);
    return {};
}

Envi Envi::MerEnvi_resolve(string name, vector<Variable> &variables) {
    if (is_declared(name, &variables)) {
        return *this;
    }

    throw runtime_error("Variable not found: " + name);
    return Envi::MerEnvi_resolve(name, variables);
}

// eval

RunTimeVal MVM_valuelize(string type, float value);
RunTimeVal MVM_evaluate(AST_node *node);
RunTimeVal MVM_evaluate_binary_expression(AST_node *node);
RunTimeVal MVM_evaluate_program(AST_node *node);
RunTimeVal MVM_evaluate_expression_statement(AST_node *node);
RunTimeVal MVM_evaluate_total_expression(AST_node *node);
RunTimeVal MVM_evaluate_AST(AST_node *node);

RunTimeVal MVM_valuelize(string type, float value) {
    return RunTimeVal {
        .type = type, 
        .value = value
    };
}

RunTimeVal MVM_evaluate(AST_node *node) {
    if (node->type == Literal) {
        return MVM_valuelize(Number, node->value);
    } else if (node->type == Program) {
        return MVM_evaluate_program(node);
    } else if (node->type == ExpressionStatement) {
        return MVM_evaluate_expression_statement(node);
    } else if (node->type == BinaryExpression) {
        return MVM_evaluate_binary_expression(node);
    }
    else {
        return MVM_valuelize(Null, 0.0);
    }
}

RunTimeVal MVM_evaluate_program(AST_node *node) {
    vector<AST_node*> statements = node->children;
    RunTimeVal result = MVM_valuelize(Null, 0.0);
    for (auto &statement : statements) {
        result = MVM_evaluate(statement);
    }
    return result;
}

RunTimeVal MVM_evaluate_total_expression(AST_node *node) {
    if (node->type == ExpressionStatement) {
        return MVM_evaluate_expression_statement(node);
    } 
    return MVM_valuelize(Null, 0.0);
}

RunTimeVal MVM_evaluate_expression_statement(AST_node *node) {
    if (node->children[0]->type == BinaryExpression) {
        return MVM_evaluate_binary_expression(node->children[0]);
    } else {
        return MVM_evaluate_total_expression(node->children[0]);
    }
    return MVM_valuelize(Null, 0.0);
}

RunTimeVal MVM_evaluate_binary_expression(AST_node *expr) {
    RunTimeVal left = MVM_evaluate(expr->left);
    RunTimeVal right = MVM_evaluate(expr->right);

    if (left.type != Number || right.type != Number) {
        return MVM_valuelize(Null, 0.0);
    }

    if (expr->op == PLUS) {
        return MVM_valuelize(Number, left.value + right.value);
    } else if (expr->op == MINUS) {
        return MVM_valuelize(Number, left.value - right.value);
    } else if (expr->op == TIME) {
        return MVM_valuelize(Number, left.value * right.value);
    } else if (expr->op == DIV) {
        return MVM_valuelize(Number, left.value / right.value);
    }
    return MVM_valuelize(Null, 0.0);
}

RunTimeVal MVM_evaluate_AST(AST_node *node) {
    return MVM_evaluate_program(node);
}

// compile

#define BYTECODE_SIZE 1024
#define BYTECODE_INTERGER_CODE_SIZE 1024
#define BYTECODE_IDENTIFIER_CODE_SIZE 1024
#define BYTECODE_CALL_FUNCTION_SIZE 1024

char* MVM_compile_program(AST_node *ast);
char* MVM_compile_ast(AST_node *ast);
char* MVM_compile_ast_binary_expression(AST_node *ast);
char* MVM_compile_ast_call_expression(AST_node *ast);
char* MVM_compile_ast_function_call_expression(AST_node *ast);
char* MVM_compile_ast_function_statement(AST_node *ast);
char* MVM_compile_ast_identifier(AST_node *ast);
char* MVM_compile_ast_literal(AST_node *ast);
char* MVM_compile_ast_return_statement(AST_node *ast);
char* MVM_compile_ast_string_expression(AST_node *ast);


char *MVM_compile_ast(AST_node *ast)
{
    if (!ast) return nullptr;

    if (ast->type == Identifier_) return MVM_compile_ast_identifier(ast);
    if (ast->type == Literal) return MVM_compile_ast_literal(ast);
    if (ast->type == ExpressionStatement) return MVM_compile_statement(ast);
    if (ast->type == CallExpression) return MVM_compile_ast_call_expression(ast);
    if (ast->type == FunctionCallExpression) return MVM_compile_ast_function_call_expression(ast);
    if (ast->type == StringExpression) return MVM_compile_ast_string_expression(ast);
    if (ast->type == BinaryExpression) return MVM_compile_ast_binary_expression(ast);
    if (ast->type == ReturnStatement) return MVM_compile_ast_return_statement(ast);
}

char *MVM_compile_program(AST_node *ast)
{
    if (!ast) return nullptr;

    char *bytecoden = new char[BYTECODE_SIZE];
    memset(bytecoden, 0, BYTECODE_SIZE);
    strcpy(bytecoden, "PROGRAM_START\n");

    if (ast->children[0]->type == ExpressionStatement) {
        for (auto &node : ast->children) {
            char *stmt_code = MVM_compile_statement(node);
            if (stmt_code) {
                strcat(bytecoden, stmt_code);
                delete[] stmt_code;
            }
        }
    }

    strcat(bytecoden, "PROGRAM_END\n");
    return bytecoden;
}

char *MVM_compile_statement(AST_node *ast) {
    if (!ast) return nullptr;

    char *bytecoden = new char[BYTECODE_SIZE];
    memset(bytecoden, 0, BYTECODE_SIZE);

    for (auto &node : ast->children) {
        char *code = MVM_compile_ast(node);
        if (code) {
            strcat(bytecoden, code);
            delete[] code;
        }
    }

    return bytecoden;
}

char *MVM_compile_ast_literal(AST_node *ast)
{
    if (!ast) return nullptr;

    char *value = new char[BYTECODE_INTERGER_CODE_SIZE];
    snprintf(value, BYTECODE_INTERGER_CODE_SIZE, "PUSH_FLOAT %f\n", ast->value);
    return value;
}

char *MVM_compile_ast_identifier(AST_node *ast)
{
    if (!ast) return nullptr;

    char *value = new char[BYTECODE_IDENTIFIER_CODE_SIZE];
    snprintf(value, BYTECODE_IDENTIFIER_CODE_SIZE, "LOAD_IDENTIFIER %s\n", ast->string_iden.c_str());
    return value;
}

char *MVM_compile_ast_call_expression(AST_node *ast)
{
    if (!ast) return nullptr;

    char *value = new char[BYTECODE_CALL_FUNCTION_SIZE];
    snprintf(value, BYTECODE_CALL_FUNCTION_SIZE, "LOAD_GLOBAL %s\n", ast->string_iden.c_str());
    return value;
}

char *MVM_compile_ast_binary_expression(AST_node *ast)
{
    if (!ast) return nullptr;

    const char *oper;
    if (ast->op == PLUS) oper = "BINARY_ADD";
    if (ast->op == MINUS) oper = "BINARY_SUB";
    if (ast->op == TIME) oper = "BINARY_MUL";
    if (ast->op == DIV) oper = "BINARY_DIV";
    return nullptr;

    char *left = MVM_compile_ast(ast->left);
    char *right = MVM_compile_ast(ast->right);
    
    if (!left || !right) {
        delete[] left;
        delete[] right;
        return nullptr;
    }

    char *value = new char[BYTECODE_INTERGER_CODE_SIZE];
    snprintf(value, BYTECODE_INTERGER_CODE_SIZE, "%s\n%s\n%s\n", left, right, oper);

    delete[] left;
    delete[] right;
    return value;
}

char *MVM_compile_ast_function_call_expression(AST_node *ast) {
    return strdup("FUNC_CALL\n");
}

char *MVM_compile_ast_string_expression(AST_node *ast) {
    return strdup("PUSH_STRING\n");
}

char *MVM_compile_ast_return_statement(AST_node *ast) {

}

char *MVM_compile_ast_function_statement(AST_node *ast) {
    return strdup("DEFINE_FUNC\n");
}

// shell
void print_token(string source) {
    for (auto &tok : MerLexer_tokenize(source)) {
        cout << "{ tok: " << tok.tok << ", type: " << tok.type << ", value: " << tok.value << ", name: " << tok.name << ", symbol: " << tok.symbol << ", string_iden: " << tok.string_iden << " }" << endl;
    }
}

void print_compile_output(string source) {
    vector <token> tokens = MerLexer_tokenize(source);
    AST_node *ast = MerAST_make_ast(tokens);
    
}

void print_ast(AST_node *node, int indent = 0) {
    if (!node) return;

    cout << string(indent, ' ') << "{ type: " << node->type;

    if (node->type == LetStatement) {
        cout << ", var_name: " << node->var_name;
        print_ast(node->var_value, indent + 2);
    } else if (node->type == FunctionCallExpression) {
        cout << ", name: " << node->func_call << ", type: " << node->func_type;
        cout << ", args: [\n";
        for (auto &arg : node->args) {
            print_ast(arg, indent + 4);
        }
        cout << string(indent + 2, ' ') << "]\n";
    }

    cout << ", value: " << node->value << ", tok: " << node->tok << " }\n";

    if (node->type == BinaryExpression) {
        cout << string(indent + 2, ' ') << "left: ";
        print_ast(node->left, indent + 2);
        cout << string(indent + 2, ' ') << "right: ";
        print_ast(node->right, indent + 2);
    } else if (node->type == LetStatement) {
        cout << string(indent + 2, ' ') << "value: ";
        print_ast(node->var_value, indent + 2);
    } else if (node->type == FunctionCallExpression) {
        cout << string(indent + 2, ' ') << "args: [\n";
        for (auto &arg : node->args) {
            print_ast(arg, indent + 4);
        }
        cout << string(indent + 2, ' ') << "]\n";
    }

    for (auto &child : node->children) {
        print_ast(child, indent + 2);
    }
}

void Shell() {
    cout << "v2.0.1" << endl;
    for (;;) {
        string source;
        cout << ">> ";
        getline(cin, source);
        if (source == "exit") {
            break;
        }

        vector <token> tokens = MerLexer_tokenize(source);
        AST_node *ast = MerAST_make_ast(tokens);
        RunTimeVal result = MVM_evaluate_AST(ast);
        cout << "{ type: " << result.type << ", value: " << result.value << " }" << endl;
    }
}

void MerCoreCompiler_ast() {
    cout << "Repl v2.0.1" << endl;
    for (;;) {
        string source;
        cout << ">> ";
        getline(cin, source);
        if (source == "exit") {
            break;
        } else if (source == "shell") {
            Shell();
            continue;
        } else if (source == "credit") {
            
        }

        vector <token> tokens = MerLexer_tokenize(source);
        AST_node *ast = MerAST_make_ast(tokens);
        RunTimeVal result = MVM_evaluate_AST(ast);
        print_ast(ast);
    }
}

void MerCoreCompiler_token() {
    cout << "Repl v2.0.1" << endl;
    for (;;) {
        string source;
        cout << ">> ";
        getline(cin, source);
        if (source == "exit") {
            break;
        }
        print_token(source);
    }
}

void credit() {
    cout << "Mer v2.0.1" << endl;
    cout << "Credit: " << endl;
    cout << "Author: Hai" << endl;
    cout << "Date: 2021" << endl;
}

void MerCompiler() {
    cout << "Repl v2.0.1" << endl;
    for (;;) {
        string source;
        cout << ">> ";
        getline(cin, source);
        if (source == "exit") {
            break;
        } else if (source == "shell") {
            Shell();
            continue;
        } else if (source == ":credit") {
            credit();
        } else if (source == ":ast") {
            MerCoreCompiler_ast();
        } else if (source == ":token") {
            MerCoreCompiler_token();
        }

        vector <token> tokens = MerLexer_tokenize(source);
        AST_node *ast = MerAST_make_ast(tokens);
        RunTimeVal result = MVM_evaluate_AST(ast);
        cout << result.value << endl;
    }
}

int main() {
    MerCompiler();
    return 0;
}
