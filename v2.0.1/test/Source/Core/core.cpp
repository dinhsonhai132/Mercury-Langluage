#include "core.h"
#include "ast.h"
#include "envi.h"

RunTimeVal evaluate_program(AST_Program prog, Environment& envi) {
    RunTimeVal last_eval;

    for (const auto &state : prog.statements) {
        last_eval = evaluate(state, envi);
    }
    return last_eval;
}

RunTimeVal evaluate_binary_expr(AST_BinaryExpression binexpr, Environment& envi) {
    RunTimeVal lhs = evaluate(binexpr.left, envi);
    RunTimeVal rhs = evaluate(binexpr.right, envi);

    if (lhs.type == _Number && rhs.type == _Number) { 
        return eval_num_expr(lhs, rhs, binexpr.op);
    }
    return {};
}

RunTimeVal eval_num_expr(RunTimeVal left, RunTimeVal right, string op_tok) {
    NumberVal left_num = static_cast<NumberVal&>(left);
    NumberVal right_num = static_cast<NumberVal&>(right);

    if (op_tok == PLUS) {
        return NumberVal {
            .type = _Number,
            .value = left_num.value + right_num.value
        };
    } else if (op_tok == MINUS) {
        return NumberVal {
            .type = _Number,
            .value = left_num.value - right_num.value
        };
    } else if (op_tok == TIME) {
        return NumberVal {
            .type = _Number,
            .value = left_num.value * right_num.value
        };
    } else if (op_tok == DIV) {
        return NumberVal {
            .type = _Number,
            .value = left_num.value / right_num.value
        };
    }
    return {};
}

RunTimeVal evaluate_identifier(AST_Identifier iden, Environment& envi) {
    return envi.lookupVar(iden.name);
}

RunTimeVal evaluate(statement state, Environment& envi) {
    if (state.type == Literal) {
        AST_Literal li = static_cast<AST_Literal&>(state);
        return NumberVal {
            .type = _Number,
            .value = li.value
        };
    } else if (state.type == BinaryExpression) {
        AST_BinaryExpression bin = static_cast<AST_BinaryExpression&>(state);
        return evaluate_binary_expr(bin, envi);
    } else if (state.type == Program) {
        AST_Program prog = static_cast<AST_Program&>(state);
        return evaluate_program(prog, envi);
    } else if (state.type == NullExpression) {
        return NullVal {
            .type = _Null,
            .value = NULL
        };
    } else if (state.type == VarDeclaraion) {
        AST_VarDeclaraion var = static_cast<AST_VarDeclaraion&>(state);
        return eval_var_declaraion(var, envi);
    } else {
        return NullVal {
            .type = _Null,
            .value = NULL
        };
    }
}

RunTimeVal eval_var_declaraion(AST_VarDeclaraion var, Environment& envi) {
    throw runtime_error("Unimplemented");
}
