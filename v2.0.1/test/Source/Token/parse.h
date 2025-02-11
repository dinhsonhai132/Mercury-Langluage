/*
------------------------------------------------------------
-- Mercury Language - Parser Header File                 --
------------------------------------------------------------
-- Repository: https://github.com/dinhsonhai132/Mercury-Langluage
-- Author: dinhsonhai132
------------------------------------------------------------
-- This file defines the parser for Mercury Language. 
-- It processes tokens from the lexer and constructs an 
-- Abstract Syntax Tree (AST).
------------------------------------------------------------
*/

#ifndef PARSE_H
#define PARSE_H

#include "ast.h"
#include "lexer.h"

using namespace std;


class parse {
private:
    vector<token> tokens;
    size_t tok_idx;
    lexer lex;
    string source;

    token get_current_token() { if (tok_idx < source.size() && tok_idx >= 0) return tokens[tok_idx]; };

    token get_next_token() { if (tok_idx + 1 < source.size() && tok_idx + 1 >= 0) return tokens[tok_idx++]; };

    void jump_ntok() { if (tok_idx < source.size() && tok_idx >= 0) tokens[tok_idx++]; };

    bool is_CurTokEOF(string tok) { return tok == EOF_T; };

public:
    parse(string source) : source(source), lex(lex), tok_idx(0) {}
    
    AST_Program AST_tokenize();

    statement AST_statement();

    AST_ExprStatement AST_exprstatement();

    AST_ExprStatement AST_primary_expr();

    AST_ExprStatement AST_Additive_Expression();

    AST_ExprStatement AST_Multiplicative_Expression();

    statement AST_printstatement();

    statement AST_varDeclaraion();
    
};

#endif