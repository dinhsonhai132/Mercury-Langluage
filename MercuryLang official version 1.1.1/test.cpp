#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>
#include <variant>
using namespace std;

enum VerType {
    INT, PLUS, MINUS, TIME, DIV, NONE, MEMORY, PRINT, STRING, STRUCT, ENUM, BLOCK, PORT, DOT, TRUE, FALSE,
    TEMPORARY_MEMORY, BIGGER, SMALLER, EQUAL, BE, SE, DIFFERENCES, IF, ELSE, ELIF, PARAMATER_KWARGS, GLOBAL_VAR,
    THEN, LP, RP, FOR, PP, MM, WHILE, LET, ASSIGN, GOTO, INPUT, LIST, RETURN_FUNC, POP, PUSH, AT, REPAIR,
    FUNCTION, PARAMATER, FUNCTION_CALL, COMMA, DOUBLE_COLON, COMMAND, CIN, CLASS, LAMBDA, MAXTRIX, IMPORT, 
    DO, VECTOR, SPARE_LP, SPARE_RP, LIST_NAME, ARROW_TOKEN, RANGE, FOR_LOOP, IN, TO, END, NUM_TYPE, STRING_TYPE, 
    NULL_TYPE, LOCAL, GLOBAL, HEAP, STACK, REGISTER, CONSTANT, LOCAL_VAR, HEAP_VAR, STACK_VAR, VOID_TOK, AUTO_TOK, 
    CONST_VAR, VOLATILE_TOK, STATIC_TOK,
};

enum VerLibrary_type {
    MERCURY_MATH, MERCURY_FILE, MERCURY_TIME, 
    MERCURY_RANDOM, MERCURY_INPUT_OUTPUT,
};

enum Mercury_type {
    FLOAT, DOUBLE, CHAR, BOOL, LONG, SHORT, UNSIGNED, SIGNED, 
    VOID, AUTO, CONST, VOLATILE, STATIC, EXTERN, REGISTER_, MUTABLE, STRING_TYPE_
};

enum port_address {
    PORT_1, PORT_2, PORT_3, PORT_4, PORT_5, PORT_6, PORT_7, PORT_8, PORT_9, PORT_10, PORT_NULL
};

struct port {
    string name = "";
    int value = 0;
    vector<int> values = {};
    port_address address = PORT_NULL;
};

struct enumerate {
    string name;
    int order;
    int value;
};

struct store_var {
    string name;
    int val;
    string string_val;
    Mercury_type type;
    bool check_string;
};

struct Parameter {
    string name;
    int val;
    Mercury_type type = AUTO;
};

struct Parameter_kwargs {
    string name;
    vector<int> vec;
    Mercury_type type = AUTO;
};

struct datatype {
    VerType type;
    int value;
    string name;
};

struct store_list {
    string name;
    vector<int> list;
    Mercury_type type = AUTO;
};

struct function_ {
    string function_name;
    vector<Parameter> Parameters;
    vector<datatype> store_tokens;
    vector<Parameter_kwargs> parameter_kwargs;
    int value = 0;
    bool return_func = false;
    Mercury_type type = AUTO;
};

struct class_type {
    string class_name;
    vector<store_var> variables;
    vector<store_list> lists;
    vector<function_> functions;
};

struct struct_type {
    string struct_name;
    vector<store_var> variables;
    vector<store_list> lists;
};

struct enum_type {
    string enum_name;
    vector<enumerate> enums;
};

vector<store_var> variables;
vector<store_var> tempotary_variables;
vector<store_list> lists;
vector<function_> functions;
vector<VerLibrary_type> libraries;

class lexer {
private:
    string input;
    size_t pos;
    char cur;
    vector<datatype> tokens;
public:
    lexer(string input) : input(input), pos(0), cur('\0') {}

    void advance() {
        if (pos < input.size()) {
            pos++;
            cur = input[pos];
        } else {
            cur = '\0';
        }
    }

    void advance_to(int a) {
        if (pos < input.size()) {
            pos += a;
            cur = input[pos];
        } else {
            cur = '\0';
        }
    }

    vector<datatype> token() {

        while (pos < input.size()) {
            cur = input[pos];
            if (cur == '/' && input[pos + 1] == '*') {
                advance_to(2);
                while (pos < input.size() && !(cur == '*' && input[pos + 1] == '/')) {
                    advance();
                }
                advance_to(2);
            } else if (cur == '-' && input.substr(pos, 2) == "->") {
                tokens.push_back({ARROW_TOKEN, 0, ""});
                advance_to(2);
            } else if (cur == '*') {
                tokens.push_back({TIME, 0, ""});
                advance();
            } else if (cur == '/') {
                tokens.push_back({DIV, 0, ""});
                advance();
            } else if (isdigit(cur)) {
                int num = 0;
                while (isdigit(input[pos]) && pos < input.size()) {
                    num = num * 10 + (input[pos] - '0');
                    advance();
                }
                tokens.push_back({INT, num, ""});
            } else if (cur == ';') {
                tokens.push_back({NONE, 0, ""});
                advance();
            } else if (cur == '+' && input.substr(pos, 2) == "++") {
                tokens.push_back({PP, 0, ""});
                advance_to(2);
            } else if (cur == '-' && input.substr(pos, 2) == "--") {
                tokens.push_back({MM, 0, ""});
                advance_to(2);
            } else if (cur == '+') {
                tokens.push_back({PLUS, 0, ""});
                advance();
            } else if (cur == '-') {
                tokens.push_back({MINUS, 0, ""});
                advance();
            } else if (cur == 'E' && input.substr(pos, 3) == "END") {
                tokens.push_back({END, 0, ""});
                advance_to(3);
            } else if (cur == 'L' && input.substr(pos, 3) == "LET") {
                tokens.push_back({LET, 0, ""});
                advance_to(3);
            } else if (cur == 'P' && input.substr(pos, 5) == "PRINT") {
                tokens.push_back({PRINT, 0, ""});
                advance_to(5);
                token();
            } else if (cur == 'R' && input.substr(pos, 6) == "RETURN") {
                tokens.push_back({RETURN_FUNC, 0, ""});
                advance_to(6);
            } else if (isspace(cur)) {
                advance();
            } else if (cur == '<') {
                tokens.push_back({SMALLER, 0, ""});
                advance();
            } else if (cur == '>') {
                tokens.push_back({BIGGER, 0, ""});
                advance();
            } else if (cur == '"') {
                string name = "";
                advance();
                while (cur != '"' && cur != '\0' && cur != '\n') {
                    name += input[pos];
                    advance();
                }
                if (!name.empty() && cur == '"') {
                    tokens.push_back({STRING, 0, name});
                }
                advance();
            } else if (cur == '=' && input[pos + 1] == '=') {
                tokens.push_back({EQUAL, 0, ""});
                advance_to(2);
            } else if (cur == '>' && input[pos + 1] == '=') {
                tokens.push_back({BE, 0, ""});
                advance_to(2);
            } else if (cur == '<' && input[pos + 1] == '=') {
                tokens.push_back({SE, 0, ""});
                advance_to(2);
            } else if (cur == '!' && input[pos + 1] == '=') {
                tokens.push_back({DIFFERENCES, 0, ""});
                advance_to(2);
            } else if (cur == 'I' && input.substr(pos, 2) == "IF") {
                tokens.push_back({IF, 0, ""});
                advance_to(2);
            } else if (cur == '(') {
                tokens.push_back({LP, 0, ""}); 
                advance();
            } else if (cur == ')') {
                tokens.push_back({RP, 0, ""});
                advance();
            } else if (cur == ']') {
                tokens.push_back({SPARE_RP, 0, ""});
                advance();
            } else if (cur == '[') {
                tokens.push_back({SPARE_LP, 0, ""});
                advance();
            } else if (cur == 'T' && input.substr(pos, 2) == "TO") {
                tokens.push_back({TO, 0, ""});
                advance_to(2);
            } else if (cur == 'F' && input.substr(pos, 3) == "FOR") {
                tokens.push_back({FOR_LOOP, 0, ""});
                advance_to(3);
            } else if (cur == 'I' && input.substr(pos, 2) == "IN") {
                tokens.push_back({IN, 0, ""});
                advance_to(2);
            } else if (cur == 'L' && input.substr(pos, 4) == "LIST") {
                tokens.push_back({LIST, 0, ""});
                advance_to(4);
            } else if (cur == 'T' && input.substr(pos, 4) == "THEN") {
                 tokens.push_back({THEN, 0, ""});
                 advance_to(4);
            } else if (cur == 'E' && input.substr(pos, 4) == "ELSE") {
                tokens.push_back({ELSE, 0, ""});
                advance_to(4);
            } else if (cur == 'E' && input.substr(pos, 4) == "ELIF") {
                tokens.push_back({ELIF, 0, ""});
                advance_to(4);
            } else if (cur == 'F' && input.substr(pos, 4) == "FUNC") {
                advance_to(5);
                string name = "";
                while (isspace(cur)) {
                    advance();
                }
                while (isalpha(cur)) {
                    name += cur;
                    advance();
                }
                tokens.push_back({FUNCTION, 0, name});
            } else if (cur == 'P' && input.substr(pos, 3) == "POP") {
                advance_to(3);
                tokens.push_back({POP, 0, ""});
            } else if (cur == 'P' && input.substr(pos, 4) == "PUSH") {
                advance_to(4);
                tokens.push_back({PUSH, 0, ""});
            } else if (cur == 'A' && input.substr(pos, 2) == "AT") {
                advance_to(2);  
                tokens.push_back({AT, 0, ""});
            } else if (cur == 'R' && input.substr(pos, 5) == "REPAIR") {
                advance_to(5);
                tokens.push_back({REPAIR, 0, ""});
            } else if (cur == 'C' && input.substr(pos, 3) == "CIN") {
                advance_to(3);
                tokens.push_back({CIN, 0, ""});
            } else if (cur == 'C' && input.substr(pos, 5) == "CLASS") {
                advance_to(5);
                tokens.push_back({CLASS, 0, ""});
            } else if (cur == 'I' && input.substr(pos, 3) == "INT") {
                advance_to(3);
                tokens.push_back({NUM_TYPE, 0, ""});
            } else if (cur == 'S' && input.substr(pos, 6) == "STRING") {
                advance_to(6);
                tokens.push_back({STRING, 0, ""});
            } else if (cur == 'N' && input.substr(pos, 4) == "NULL") {
                advance_to(4);
                tokens.push_back({NULL_TYPE, 0, ""});
            } else if (cur == 'I' && input.substr(pos, 6) == "IMPORT") {
                advance_to(6);
                tokens.push_back({IMPORT, 0, ""});
            } else if (cur == 'V' && input.substr(pos, 6) == "VECTOR") {
                advance_to(6);
                tokens.push_back({VECTOR, 0, ""});
            } else if (cur == 'M' && input.substr(pos, 6) == "MAXTRIX") {
                advance_to(6);
                tokens.push_back({MAXTRIX, 0, ""});
            } else if (cur == 'E' && input.substr(pos, 4) == "ENUM") {
                advance_to(4);
                tokens.push_back({ENUM, 0, ""});
            } else if (cur == 'S' && input.substr(pos, 6) == "STRUCT") {
                advance_to(6);
                tokens.push_back({STRUCT, 0, ""});
            } else if (cur == 'B' && input.substr(pos, 4) == "BLOCK") {
                advance_to(4);
                tokens.push_back({BLOCK, 0, ""});
            } else if (cur == 'P' && input.substr(pos, 4) == "PORT") {
                advance_to(4);  
                tokens.push_back({PORT, 0, ""});
            } else if (cur == '.') {
                advance();
                tokens.push_back({DOT, 0, ""});
            } else if (cur == '&') {
                advance();
                string name;
                while (isalpha(cur)) {
                    name += cur;
                    advance();
                }
                tokens.push_back({PARAMATER, 0, name});
            } else if (cur == '%') {
                advance();
                string name;
                while (isalpha(cur)) {
                    name += cur;
                    advance();
                }
                tokens.push_back({PARAMATER_KWARGS, 0, name});
            } 
            else if (cur == ',') {
                tokens.push_back({COMMA, 0, ""});
                advance();
            } else if (cur == ':') {
                tokens.push_back({DOUBLE_COLON, 0, ""});
                advance();
            } else if (cur == '!') {
                advance();
                string name = "";
                while (isalpha(cur)) {
                    name += input[pos];
                    advance();
                }
                tokens.push_back({FUNCTION_CALL, 0, name});
            } else if (cur == 'D' && input.substr(pos, 2) == "DO") {
                advance_to(2);
                tokens.push_back({DO, 0, ""});
            } else if (cur == 'W' && input.substr(pos, 5) == "WHILE") {
                advance_to(5);
                tokens.push_back({WHILE, 0, ""});
            } else if (cur == '@') {
                advance();
                string name = "";
                while (isalpha(cur)) {
                    name += input[pos];
                    advance();
                }
                tokens.push_back({LIST_NAME, 0, name});
            } else if (isalpha(cur)) {
                string name = "";
                while (isalpha(cur)) {
                    name += input[pos];
                    advance();
                }
                tokens.push_back({TEMPORARY_MEMORY, 0, name});
            } else if (cur == '=') {
                tokens.push_back({ASSIGN, 0, ""});
                advance();
            } else {
                advance();
            }
        }
        return tokens;
    }
};

class parser {
private:
    size_t tok_idx;
    datatype cur_idx;
    vector<datatype> tokenize;
    string var;
    int val;
public:
    parser(vector<datatype> tokenize) : tokenize(tokenize), tok_idx(0) {}

    float make_float() {
        int left = 0, right = 0;
        int pos = tok_idx;
        cur_idx = get_next_tok();
        if (cur_idx.type == INT) {
            left = cur_idx.value;
            cur_idx = get_next_tok();
            if (cur_idx.type == DOT) {
                cur_idx = get_next_tok();
                if (cur_idx.type == INT) {
                    right = cur_idx.value;
                } else {
                    cout << "Error: Expected integer after dot" << endl;
                    return 0;
                }
            } else {
                cout << "Error: Expected dot after integer" << endl;
                return 0;
            }
        } else {
            cout << "Error: Expected integer at the beginning" << endl;
            return 0;
        }
        tok_idx = pos + 3;
        string val = to_string(left) + "." + to_string(right);
        return stof(val);
    }

    int get_tempotary_variable(string name) {
        bool found = false;

        for (auto &variable: tempotary_variables) {
            if (variable.name == name) {
                found = true;
                return variable.val;
            }
        }

        if (!found) {
            cout << "Error: can't found the paramater name" << endl;
        }

        return 0;
    }

    int get_variable(string name) {
        bool found = false;
        for (auto &variable: variables) {
            if (variable.name == name) {
                found = true;
                return variable.val;
            }
        }
        if (!found) {
            cout << "Error: can't found the variable name" << endl;
        }
        return 0;
    }

    vector<int> get_list(string name) {
        bool found = false;
        for (auto &list : lists) {
            if (list.name == name) {
                found = true;
                return list.list;
            }
        }
        if (!found) {
            cout << "Error: can't found the list" << endl;
        }
        return {0};
    }

    int extract() {
        auto tok = get_next_tok();
        if (tok.type == LIST_NAME) {
            auto list = get_list(tok.name);
            tok = get_next_tok();
            if (tok.type == ARROW_TOKEN) {
                tok = get_next_tok();
                if (tok.type == INT) {
                    int order = tok.value;
                    if (order > list.size()) {
                        cout << "Error: index out of range" << endl;
                        return 0;
                    } else if (order < 1) {
                        cout << "Error: order can't below 1" << endl;
                        return 0;
                    }
                    auto element = list[tok.value - 1];
                    return element;
                } else if (tok.type == TEMPORARY_MEMORY) {
                    int val = get_variable(tok.name);
                    if (val > list.size()) {
                        cout << "Error: index out of range, please change the another variable" << endl;
                        return 0;
                    } else if (val < 1) {
                        cout << "Error: order can't below 1, please change the another variable" << endl;
                        return 0;
                    }
                    int element = list[val - 1];
                    return element;
                }
            }
        } else {
            cout << "Error: can't ARROW_TOKEN the value from the list" << endl;
        }
        return 0;
    }

    datatype get_next_tok() {
        if (tok_idx < tokenize.size()) {
            return tokenize[tok_idx++];
        }
        return {NONE, 0, ""};
    }

    datatype get_next_tok_to(int s) {
        if (tok_idx < tokenize.size()) {
            tok_idx += s;
            return tokenize[tok_idx];
        }
        return {NONE, 0, ""};
    }

    int get_value_func(string name) {
        for (auto &func : functions) {
            if (func.function_name == name) {
                return func.value;
            }
        }
        return 0;
    }

    void update_pp() {
        cur_idx = get_next_tok();
        if (cur_idx.type == TEMPORARY_MEMORY) {
            for (auto &variable: variables) {
                if (variable.name == cur_idx.name) {
                    variable.val += 1;
                    break;
                }
            }
        } else if (cur_idx.type == INT) {
            cur_idx.value += 1;
        }
    }

    void update_mm() {
        cur_idx = get_next_tok();
        if (cur_idx.type == TEMPORARY_MEMORY) {
            for (auto &variable: variables) {
                if (variable.name == cur_idx.name) {
                    variable.val -= 1;
                    break;
                }
            }
        } else if (cur_idx.type == INT) {
            cur_idx.value -= 1;
        }
    }

    string get_string_variable(string name) {
        for (auto &variable: variables) {
            if (variable.name == name) {
                return variable.string_val;
                break;
            }
        }
    }

    void imprort_library() {
        cur_idx = get_next_tok();
        if (cur_idx.type == IMPORT) {
            cur_idx = get_next_tok();
            if (cur_idx.type == STRING) {
                string name = cur_idx.name;
                if (name == "MERCURY_MATH") {
                    #include "C:\Users\hadin\Desktop\MercuryLang version 1.1.1\MercuryLang official version 1.1.1\MercuryLibrary\MercuryMath.cpp"
                } else if (name == "MERCURY_FILE") {
                    #include "C:\Users\hadin\Desktop\MercuryLang version 1.1.1\MercuryLang official version 1.1.1\MercuryLibrary\MercuryFile.cpp"
                } else if (name == "MERCURY_TIME") {
                    #include "C:\Users\hadin\Desktop\MercuryLang version 1.1.1\MercuryLang official version 1.1.1\MercuryLibrary\MercuryTime.cpp"
                } else if (name == "MERCURY_RANDOM") {
                    #include "C:\Users\hadin\Desktop\MercuryLang version 1.1.1\MercuryLang official version 1.1.1\MercuryLibrary\MercuryRandom.cpp"
                } else if (name == "MERCURY_INPUT_OUTPUT") {
                    #include "C:\Users\hadin\Desktop\MercuryLang version 1.1.1\MercuryLang official version 1.1.1\MercuryLibrary\MercuryInputOutput.cpp"
                }
            }
        }
    }
    
    float factor() {
        cur_idx = get_next_tok();
        if (cur_idx.type == INT && tokenize[tok_idx + 1].type != DOT) {
            return cur_idx.value;
        } else if (cur_idx.type == INT && tokenize[tok_idx + 1].type == DOT) {
            tok_idx--;
            return make_float();
        } else if (cur_idx.type == FUNCTION_CALL) {
            return get_value_func(cur_idx.name);
        } else if (cur_idx.type == TEMPORARY_MEMORY) {
            return get_variable(cur_idx.name);
        } else if (cur_idx.type == PARAMATER) {
            return get_tempotary_variable(cur_idx.name);
        } else if (cur_idx.type == PP) {
            update_pp();
        } else if (cur_idx.type == MM) {
            update_mm();
        } else if (cur_idx.type == LIST_NAME) {
            tok_idx--;
            return extract();
        } else if (cur_idx.type == NONE || cur_idx.type == COMMA) {
            tok_idx++;
        }
        return 0;
    }   

    int term() {
        int result = factor();
        while (true) {
            cur_idx = get_next_tok();
            if (cur_idx.type == DIV) {
                int divisor = factor();
                if (divisor == 0) {
                    cout << "Error: Division by zero" << endl;
                    return 0;
                }
                result /= divisor;
            } else if (cur_idx.type == TIME) {
                result *= factor();
            }
            else {
                tok_idx--;
                break;
            }
        }
        return result;
    }

    int expr() {
        int result = term();
        while (true) {
            cur_idx = get_next_tok();
            if (cur_idx.type == PLUS) {
                result += term();
            } else if (cur_idx.type == MINUS) {
                result -= term();
            } else {
                tok_idx--;
                break;
            }
        }
        return result;
    }

    void make_list() {
        string name;
        vector<int> the_list;
        auto tok = get_next_tok();
        if (tok.type == LIST) {
            tok = get_next_tok();
            if (tok.type == TEMPORARY_MEMORY) {
                name = tok.name;
                tok = get_next_tok();
                if (tok.type == ASSIGN) {
                    tok = get_next_tok();
                    if (tok.type == SPARE_LP) {
                        while (tok_idx < tokenize.size() && tokenize[tok_idx].type != SPARE_RP) {
                            if (tokenize[tok_idx].type == INT) {
                                the_list.push_back(tokenize[tok_idx].value);
                                tok_idx++;
                            } else if (tokenize[tok_idx].type == COMMA) {
                                tok_idx++;
                            }
                        }
                    }
                } else {
                    cout << "Error: '=' not found" << endl;
                }
            } else {
                cout << "Error: Expected list name after 'LIST'" << endl;
            }
        }

        if (!name.empty()) {
            lists.push_back({name, the_list});
        } else {
            cout << "Error: name not found" << endl;
        }
    }

    void make_function() {
        cur_idx = get_next_tok();
        string name_func;
        vector<Parameter> paras;
        vector<Parameter_kwargs> paras_kwargs;
        vector<datatype> store_tokens;
        if (cur_idx.type == FUNCTION) {
            name_func = cur_idx.name;
            cur_idx = get_next_tok();
            if (cur_idx.type == LP) {

                bool found = false;
                if (tokenize[tok_idx + 1].type == PARAMATER_KWARGS) {
                    paras_kwargs.push_back({tokenize[tok_idx + 1].name, {}});
                    found = true;
                } else {
                    while (tok_idx < tokenize.size() && cur_idx.type != RP) {
                        if (cur_idx.type == PARAMATER) {
                            paras.push_back({cur_idx.name, 0});
                        }
                        cur_idx = tokenize[tok_idx++];
                    }
                }

                if (found) {
                    cur_idx = get_next_tok_to(3);
                } else {
                    cur_idx = get_next_tok();
                }

                if (cur_idx.type == DO) {
                    while (tok_idx < tokenize.size() && cur_idx.type != END
                    || tok_idx < tokenize.size()) {
                        store_tokens.push_back(cur_idx);
                        cur_idx = tokenize[tok_idx++];
                    }
                }

            } else {
                cout << "Error: missing left parent" << endl;
            }
        }
        else {
            cout << "Error: function name failed" << endl;
        }
        
        if (paras_kwargs.empty()) {
            functions.push_back({name_func, paras, store_tokens});
        } else {
            functions.push_back({name_func, {}, store_tokens, paras_kwargs});
        }
    }

    vector<datatype> get_tokens(string name) {
        for (auto &func : functions) {
            if (func.function_name == name) {
                return func.store_tokens;
            }
        }
        return {};
    }

    vector<Parameter> get_para(string name) {
        for (auto &func : functions) {
            if (func.function_name == name) {
                return func.Parameters;
            }
        }
        return {};
    } 

    auto make_return() {
        cur_idx = get_next_tok();
        if (cur_idx.type == RETURN_FUNC) {
            return expr();
        }
        return 0;
    }

    bool check_val_func(string name) {
        for (auto &func : functions) {
            if (func.function_name == name) {
                if (func.return_func) {
                    return true;
                }
            }
        }
        return false;
    }

    auto execute(string function_name) {
        vector<datatype> tokens = get_tokens(function_name);
        vector<Parameter> paras = get_para(function_name);

        if (tokens.empty()) {
            cout << "Error: can't found the function name" << endl;
            return 0;
        }

        if (!paras.empty()) {
            for (auto &para : paras) {
                tempotary_variables.push_back({para.name, para.val});
            }
        }

        tok_idx = 0;
        tokenize = tokens;
        cur_idx = tokenize[tok_idx];

        while (tok_idx < tokenize.size()) {
            cur_idx = tokenize[tok_idx];
            if (cur_idx.type == PRINT) {
                print_func();
                tok_idx++;
            } else if (cur_idx.type == LET) {
                make_var();
                tok_idx++;
            } else if (cur_idx.type == NONE || cur_idx.type == COMMA) {
                tok_idx++;
            } else if (cur_idx.type == IF) {
                condition();
                tok_idx++;
            } else if (cur_idx.type == LIST) {
                make_list();
                tok_idx++;
            } else if (cur_idx.type == FOR_LOOP) {
                for_loop();
            } else if (cur_idx.type == WHILE) {
                while_loop();
            } else if (cur_idx.type == FUNCTION_CALL) {
                call_function();
                tok_idx++;
            } else if (cur_idx.type == FUNCTION) {
                make_function();
                tok_idx++;
            } else if (cur_idx.type == RETURN_FUNC) {
                int value = make_return();
                for (auto &func : functions) {
                    if (func.function_name == function_name) {
                        func.value = value;
                        func.return_func = true;
                    }
                }
                tempotary_variables = {};
                return value;
            } else if (cur_idx.type == IMPORT) {
                cout << "Error: can't use 'IMPORT' in the function" << endl;
            } else {
                expr();
            }
        }
        tempotary_variables = {};
        return 0;
    }

    int call_function() {
        cur_idx = get_next_tok();
        string name;
        vector<int> values;
        vector<Parameter> paras;
        if (cur_idx.type == FUNCTION_CALL) {
            name = cur_idx.name;
            cur_idx = get_next_tok();
            if (cur_idx.type == LP) {
                paras = get_para(name);
                while (tok_idx < tokenize.size() && cur_idx.type != RP) {
                    if (cur_idx.type == INT) {
                        values.push_back(cur_idx.value);
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        values.push_back(get_variable(cur_idx.name));
                    } else if (cur_idx.type == PARAMATER) {
                        values.push_back(get_tempotary_variable(cur_idx.name));
                    }
                    cur_idx = tokenize[tok_idx++];
                }

                for (int i = 0; i < paras.size(); i++) {
                    paras[i].val = values[i];
                }

                for (auto &func : functions) {
                    if (func.function_name == name) {
                        func.Parameters = paras;
                    }
                }

                cur_idx = get_next_tok();
                if (cur_idx.type == ARROW_TOKEN) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == NUM_TYPE) {
                        int val = execute(name);
                        return val;
                    }
                }

                int pos = tok_idx;
                execute(name);
                tok_idx = pos;

            } else {
                cout << "Error: missing left parent" << endl;
            }
        }
        return 0;
    }

    void for_loop() {
        cur_idx = get_next_tok();
        int left, right;
        string name;
        bool list_found = false;
        if (cur_idx.type == FOR_LOOP) {
            cur_idx = get_next_tok();
            if (cur_idx.type == TEMPORARY_MEMORY) {
                name = cur_idx.name;
                variables.push_back({name, 0});
                cur_idx = get_next_tok();
                if (cur_idx.type == IN) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int left = cur_idx.value;
                        cur_idx = get_next_tok();
                        if (cur_idx.type == TO) {
                            cur_idx = get_next_tok();
                            if (cur_idx.type == INT) {
                                right = cur_idx.value;
                                cur_idx = get_next_tok();
                                if (cur_idx.type == DO) {
                                    int cur_tok_idx = tok_idx;
                                    for (;left < right; left++) {
                                        for (auto &variable : variables) {
                                            if (variable.name == name) {
                                                variable.val = left;
                                            }
                                        }
                                        do_block();
                                        tok_idx = cur_tok_idx;
                                    }
                                }
                            } else if (cur_idx.type == TEMPORARY_MEMORY) {
                                right = get_variable(cur_idx.name);
                                cur_idx = get_next_tok();
                                if (cur_idx.type == DO) {
                                    int cur_tok_idx = tok_idx;
                                    for (;left < right; left++) {
                                        for (auto &variable : variables) {
                                            if (variable.name == name) {
                                                variable.val = left;
                                            }
                                        }
                                        do_block();
                                        tok_idx = cur_tok_idx;
                                    }
                                }
                            } else if (cur_idx.type == PARAMATER) {
                                right = get_tempotary_variable(cur_idx.name);
                                cur_idx = get_next_tok();
                                if (cur_idx.type == DO) {
                                    int cur_tok_idx = tok_idx;
                                    for (;left < right; left++) {
                                        for (auto &variable : variables) {
                                            if (variable.name == name) {
                                                variable.val = left;
                                            }
                                        }
                                        do_block();
                                        tok_idx = cur_tok_idx;
                                    }
                                }
                            } else {
                                cout << "Error: unexpected factor" << endl;
                            }
                        } else {
                            cout << "Error: can't found token 'TO'" << endl;
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int left = get_variable(cur_idx.name);
                        cur_idx = get_next_tok();
                        if (cur_idx.type == TO) {
                            cur_idx = get_next_tok();
                            if (cur_idx.type == INT) {
                                right = cur_idx.value;
                                cur_idx = get_next_tok();
                                if (cur_idx.type == DO) {
                                    int cur_tok_idx = tok_idx;
                                    for (;left < right; left++) {
                                        for (auto &variable : variables) {
                                            if (variable.name == name) {
                                                variable.val = left;
                                            }
                                        }
                                        do_block();
                                        tok_idx = cur_tok_idx;
                                    }
                                }
                            } else if (cur_idx.type == TEMPORARY_MEMORY) {
                                right = get_variable(cur_idx.name);
                                cur_idx = get_next_tok();
                                if (cur_idx.type == DO) {
                                    int cur_tok_idx = tok_idx;
                                    for (;left < right; left++) {
                                        for (auto &variable : variables) {
                                            if (variable.name == name) {
                                                variable.val = left;
                                            }
                                        }
                                        do_block();
                                        tok_idx = cur_tok_idx;
                                    }
                                }
                            } else if (cur_idx.type == PARAMATER) {
                                right = get_tempotary_variable(cur_idx.name);
                                cur_idx = get_next_tok();
                                if (cur_idx.type == DO) {
                                    int cur_tok_idx = tok_idx;
                                    for (;left < right; left++) {
                                        for (auto &variable : variables) {
                                            if (variable.name == name) {
                                                variable.val = left;
                                            }
                                        }
                                        do_block();
                                        tok_idx = cur_tok_idx;
                                    }
                                }
                            } else {
                                cout << "Error: unexpected factor" << endl;
                            }
                        } else {
                            cout << "Error: can't found token 'TO'" << endl;
                        }
                    } else if (cur_idx.type == PARAMATER) {
                        int left = get_tempotary_variable(cur_idx.name);
                        cur_idx = get_next_tok();
                        if (cur_idx.type == TO) {
                            cur_idx = get_next_tok();
                            if (cur_idx.type == INT) {
                                right = cur_idx.value;
                                cur_idx = get_next_tok();
                                if (cur_idx.type == DO) {
                                    int cur_tok_idx = tok_idx;
                                    for (;left < right; left++) {
                                        for (auto &variable : variables) {
                                            if (variable.name == name) {
                                                variable.val = left;
                                            }
                                        }
                                        do_block();
                                        tok_idx = cur_tok_idx;
                                    }
                                }
                            } else if (cur_idx.type == TEMPORARY_MEMORY) {
                                right = get_variable(cur_idx.name);
                                cur_idx = get_next_tok();
                                if (cur_idx.type == DO) {
                                    int cur_tok_idx = tok_idx;
                                    for (;left < right; left++) {
                                        for (auto &variable : variables) {
                                            if (variable.name == name) {
                                                variable.val = left;
                                            }
                                        }
                                        do_block();
                                        tok_idx = cur_tok_idx;
                                    }
                                }
                            } else if (cur_idx.type == PARAMATER) {
                                right = get_tempotary_variable(cur_idx.name);
                                cur_idx = get_next_tok();
                                if (cur_idx.type == DO) {
                                    int cur_tok_idx = tok_idx;
                                    for (;left < right; left++) {
                                        for (auto &variable : variables) {
                                            if (variable.name == name) {
                                                variable.val = left;
                                            }
                                        }
                                        do_block();
                                        tok_idx = cur_tok_idx;
                                    }
                                }
                            } else {
                                cout << "Error: unexpected factor" << endl;
                            }
                        } else {
                            cout << "Error: can't found token 'TO'" << endl;
                        }
                    }
                    else if (cur_idx.type == LIST_NAME) {
                        list_found = true;
                        vector<int> list = get_list(cur_idx.name);
                        int cur_tok_idx = tok_idx;
                        for (int i : list) {
                            for (auto &variable : variables) {
                                if (variable.name == name) {
                                    variable.val = i;
                                }
                            }
                            do_block();
                            tok_idx = cur_tok_idx;
                        }
                    } else {
                        cout << "Error: unexpected factor" << endl;
                    }
                } else {
                    cout << "Error: can't found token 'IN'" << endl;
                }
            } else {
                cout << "Error: name variable failed" << endl;
            }
        } else {
            cout << "Error: can't found token 'FOR'" << endl;
        }
        if (!list_found) variables.push_back({name, right});
    }

    void pop() {
        cur_idx = get_next_tok();
        if (cur_idx.type == POP) {
            cur_idx = get_next_tok();
            if (cur_idx.type == LIST_NAME) {
                string name = cur_idx.name;
                cur_idx = get_next_tok();
                if (cur_idx.type == AT) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int order = cur_idx.value;
                        for (auto &list : lists) {
                            if (list.name == name) {
                                list.list.erase(list.list.begin() + order - 1);
                            }
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int order = get_variable(cur_idx.name);
                        for (auto &list : lists) {
                            if (list.name == name) {
                                list.list.erase(list.list.begin() + order - 1);
                            }
                        }
                    } else if (cur_idx.type == PARAMATER) {
                        int order = get_tempotary_variable(cur_idx.name);
                        for (auto &list : lists) {
                            if (list.name == name) {
                                list.list.erase(list.list.begin() + order - 1);
                            }
                        }
                    }
                } else if (cur_idx.type == ARROW_TOKEN) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int erase_element = cur_idx.value;
                        for (auto &list : lists) {
                            if (list.name == name) {
                                for (int i = 0; i < list.list.size(); i++) {
                                    if (list.list[i] == erase_element) {
                                        list.list.erase(list.list.begin() + i);
                                    }
                                }
                            }
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int erase_element = get_variable(cur_idx.name);
                        for (auto &list : lists) {
                            if (list.name == name) {
                                for (int i = 0; i < list.list.size(); i++) {
                                    if (list.list[i] == erase_element) {
                                        list.list.erase(list.list.begin() + i);
                                    }
                                }
                            }
                        }
                    } else if (cur_idx.type == PARAMATER) {
                        int erase_element = get_tempotary_variable(cur_idx.name);
                        for (auto &list : lists) {
                            if (list.name == name) {
                                for (int i = 0; i < list.list.size(); i++) {
                                    if (list.list[i] == erase_element) {
                                        list.list.erase(list.list.begin() + i);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void push() {
        cur_idx = get_next_tok();
        if (cur_idx.type == PUSH) {
            cur_idx = get_next_tok();
            if (cur_idx.type == LIST_NAME) {
                string name = cur_idx.name;
                cur_idx = get_next_tok();
                if (cur_idx.type == ARROW_TOKEN) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int element = cur_idx.value;
                        for (auto &list : lists) {
                            if (list.name == name) {
                                list.list.push_back(element);
                            }
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int element = get_variable(cur_idx.name);
                        for (auto &list : lists) {
                            if (list.name == name) {
                                list.list.push_back(element);
                            }
                        }
                    } else if (cur_idx.type == PARAMATER) {
                        int element = get_tempotary_variable(cur_idx.name);
                        for (auto &list : lists) {
                            if (list.name == name) {
                                list.list.push_back(element);
                            }
                        }
                    }
                }
            }
        }
    }

    void repair() {
        cur_idx = get_next_tok();
        if (cur_idx.type == REPAIR) {
            cur_idx = get_next_tok();
            if (cur_idx.type == LIST_NAME) {
                string name = cur_idx.name;
                cur_idx = get_next_tok();
                if (cur_idx.type == AT) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int order = cur_idx.value;
                        cur_idx = get_next_tok();
                        if (cur_idx.type == ASSIGN) {
                            cur_idx = get_next_tok();
                            if (cur_idx.type == INT) {
                                int element = cur_idx.value;
                                for (auto &list : lists) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            } else if (cur_idx.type == TEMPORARY_MEMORY) {
                                int element = get_variable(cur_idx.name);
                                for (auto &list : lists) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            } else if (cur_idx.type == PARAMATER) {
                                int element = get_tempotary_variable(cur_idx.name);
                                for (auto &list : lists) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            }
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int order = get_variable(cur_idx.name);
                        cur_idx = get_next_tok();
                        if (cur_idx.type == ASSIGN) {
                            cur_idx = get_next_tok();
                            if (cur_idx.type == INT) {
                                int element = cur_idx.value;
                                for (auto &list : lists) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            } else if (cur_idx.type == TEMPORARY_MEMORY) {
                                int element = get_variable(cur_idx.name);
                                for (auto &list : lists) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            } else if (cur_idx.type == PARAMATER) {
                                int element = get_tempotary_variable(cur_idx.name);
                                for (auto &list : lists) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int while_loop() {
        cur_idx = get_next_tok();
        if (cur_idx.type == WHILE) {
            int condition = comparison();
            if (condition == 1) {
                cur_idx = get_next_tok();
                if (cur_idx.type == DO) {
                    do_block();
                    tok_idx = 0;
                    while_loop();
                } else {
                    cout << "Error: can't not found the token 'DO' in while loop" << endl;
                }
            }
        }
        return 0;
    }

    void make_var() {
        datatype name;
        int val;
        string var_name;
        bool check_string = false;
        auto tok = get_next_tok();
        if (tok.type == LET) {
            name = get_next_tok();
            if (name.type == TEMPORARY_MEMORY) {
                var_name = name.name;
            } else {
                cout << "Error: name variable failed" << endl;
            }
            tok = get_next_tok();
            if (tok.type == ASSIGN) {
                tok = get_next_tok();
                if (tok.type == INT) {
                    tok_idx--;
                    val = expr();
                } else if (tok.type == STRING) {
                    string val = tok.name;
                    check_string = true;
                    variables.push_back({var_name, 0, val, STRING_TYPE_, check_string});
                } else {
                    cout << "Error: type not found" << endl;
                }
            }
        }

        if (!check_string) {
            variables.push_back({var_name, val});
        }
    }

    int comparison() {
        auto left_token = get_next_tok();
        VerType OP = get_next_tok().type;
        auto right_token = get_next_tok();
        int left = 0;
        int right = 0;
        if (left_token.type == TEMPORARY_MEMORY) {
            string name = left_token.name;
            left = get_variable(name);
        } else if (left_token.type == INT) {
            left = left_token.value;
        } else if (left_token.type == PARAMATER) {
            left = get_tempotary_variable(left_token.name);
        } 
        else {
            cout << "Error: error type" << endl;
        }
        if (right_token.type == TEMPORARY_MEMORY) {
            string name = right_token.name;
            right = get_variable(name);
        } else if (right_token.type == INT) {
            right = right_token.value;
        } else if (right_token.type == PARAMATER) {
            right = get_tempotary_variable(right_token.name);
        }
        switch (OP) {
            case BIGGER:
                return left > right ? 1 : 0;
            case SMALLER:
                return left < right ? 1 : 0;
            case EQUAL:
                return left == right ? 1 : 0;
            case BE:
                return left >= right ? 1 : 0;
            case SE:
                return left <= right ? 1 : 0;
            case DIFFERENCES:
                return left != right ? 1 : 0;
        }
        return 0;
    }

    bool found_else = false;
    bool found_elif = false;

    int condition() {
        int pos = tok_idx;
        cur_idx = get_next_tok();
        if (cur_idx.type == IF) {
            int check = comparison();
            if (check == 1 && get_next_tok().type == THEN) {
                do_block();
            } else if (check == 0 && get_next_tok().type == THEN) {
                while (tok_idx < tokenize.size()) {
                    cur_idx = tokenize[tok_idx];
                    if (cur_idx.type == ELSE) {
                        found_else = true;
                        break;
                    } else if (cur_idx.type == ELIF) {
                        found_elif = true;
                        break;
                    }
                    tok_idx++;
                }
                if (found_elif) {
                    tok_idx++;
                    int elif_check = comparison();
                    if (elif_check == 1 && get_next_tok().type == THEN) {
                        do_block();
                    } else {
                        while (tok_idx < tokenize.size() && tokenize[tok_idx].type != ELSE && tokenize[tok_idx].type != ELIF) {
                            tok_idx++;
                        }
                        if (tokenize[tok_idx].type == ELSE) {
                            found_else = true;
                        }
                    }
                }
                if (found_else) {
                    tok_idx++;
                    do_block();
                }
            } else {
                cout << "Error: condition failed" << endl;
            }
        }
        return 0;
    }

    void print_func() {
        auto tok = get_next_tok();
        if (tok.type == PRINT) {
            auto next_tok = get_next_tok();
            if (next_tok.type == STRING) {
                cout << next_tok.name << endl;
            } else {
                tok_idx--;
                cout << expr() << endl;
            }
        }
    }

    void do_block() {
        while (tok_idx < tokenize.size()) {
            cur_idx = tokenize[tok_idx];
            if (cur_idx.type == PRINT) {
                print_func();
                tok_idx++;
            } else if (cur_idx.type == LET) {
                make_var();
                tok_idx++;
            } else if (cur_idx.type == NONE || cur_idx.type == COMMA) {
                tok_idx++;
            } else if (cur_idx.type == IF) {
                condition();
                tok_idx++;
            } else if (cur_idx.type == LIST) {
                make_list();
                tok_idx++;
            } else if (cur_idx.type == FOR_LOOP) {
                for_loop();
                tok_idx++;
            } else if (cur_idx.type == WHILE) {
                while_loop();
                tok_idx++;
            } else if (cur_idx.type == FUNCTION_CALL) {
                call_function();
                tok_idx++;
            } else if (cur_idx.type == FUNCTION) {
                make_function();
                tok_idx++;
            } else if (cur_idx.type == POP) {
                pop();
                tok_idx++;
            } else if (cur_idx.type == PUSH) {
                push();
                tok_idx++;
            } else if (cur_idx.type == REPAIR) {
                repair();
                tok_idx++;
            } else if (cur_idx.type == IMPORT) {
                imprort_library();
                tok_idx++;
            } else {
                expr();
            }
        }
    }

    void run_code() {
        while (tok_idx < tokenize.size()) {
            if (tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == BIGGER 
            || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == SMALLER
            || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == EQUAL
            || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == BE
            || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == SE
            || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == DIFFERENCES) {
                tok_idx = 0;
                cout << comparison() << endl;
                break;
            } else if (tokenize[tok_idx].type == PRINT) {
                print_func();
                break;
            } else if (tokenize[tok_idx].type == IF) {
                condition();
                break;
            } else if (tokenize[tok_idx].type == LET) {
                make_var();
                break;
            } else if (tokenize.empty()) {
                continue;
            } else if (tokenize[tok_idx].type == WHILE) {
                while_loop();
                break;
            } else if (tokenize[tok_idx].type == LIST) {
                make_list();
                break;
            } else if (tokenize[tok_idx].type == FOR_LOOP) {
                for_loop();
                break;
            } else if (tokenize[tok_idx].type == FUNCTION) {
                make_function();
                break;
            } else if (tokenize[tok_idx].type == FUNCTION_CALL) {
                call_function();
                break;
            } else if (tokenize[tok_idx].type == PUSH) {
                push();
                break;
            } else if (tokenize[tok_idx].type == POP) {
                pop();
                break;
            }  else if (cur_idx.type == REPAIR) {
                repair();
                break;
            } else if (cur_idx.type == IMPORT) {
                imprort_library();
                break;
            } else {
                expr();
                break;
            }
        }
    }
};

void info() {
    cout << "copy right (c) dinhsonhai132" << endl;
}

void print_var() {
    for (auto &var: variables) {
        cout << "Name: " << var.name << " Value: " << var.val << endl;
    }
}

void print_list() {
    for (auto &list: lists) {
        cout << "LIST NAME: " << list.name << endl;
    }
}

void print_func() {
    vector<string> para_name;
    for (auto &func : functions) {
        for (auto &para : func.Parameters) {
            para_name.push_back(para.name);
        }
        cout << "func name: " << func.function_name << " ";
        cout << "para: ";
        for (auto name : para_name) {
            cout << name << " ";
        }
        cout << "value: ";
        cout << func.value << endl;
        para_name = {};
        cout << endl;
    }
}

void run() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    auto time = ctime(&current_time);
    cout << "MercuryLang [Version 2.0.1]\n(c) (this is test version) All rights reserved.\n type 'help?' for help, 'info' for info, 'exit' to leave" << endl;
    while (true) {
        string input;
        cout << "> ";
        getline(cin, input);

        lexer lex(input);
        vector<datatype> tokens = lex.token();
        parser par(tokens);

        if (input == "help?") {
            cout << "Visit https://dinhsonhai132.github.io/fslang.github.io/fslang.html for more info" << endl;
        } else if (input == "exit") {
            cout << "Goodbye :)" << endl;
            break; 
        } else if (input == "info") {
            info();
        } else if (input == "var") {
            print_var();
        } else if (input.empty() || input == "") {
            continue;
        } else if (input == "list") {
            print_list();
        } else if (input == "func") {
            print_func();
        } else {
            par.run_code();
        }
    }
}

void debug() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    auto time = ctime(&current_time);
    cout << "MercuryLang [Version 2.0.1] \n(c) (this is test version) All rights reserved.\n type 'help?' for help, 'info' for info, 'exit' to leave" << endl;
    while (true) {
        string input;
        cout << "debug_mode> ";
        getline(cin, input);
        lexer lex(input);
        vector<datatype> tokens = lex.token();
        parser par(tokens);

        if (input == "help?") {
            cout << "Visit https://dinhsonhai132.github.io/fslang.github.io/fslang.html for more info" << endl;
        } else if (input == "exit") {
            cout << "Goodbye :)" << endl;
            break;  
        } else if (input == "info") {
            info();
        } else if (input == "var") {
            print_var();
        } else if (input.empty() || input == "") {
            continue;
        } else if (input == "list") {
            print_list();
        } else if (input == "func") {
            print_func();
        } else {
            par.run_code();
            string token_type;
            for (auto &token : tokens) {
                switch(token.type) {
                    case PLUS: token_type = "PLUS"; break; 
                    case INT: token_type = "INT"; break; 
                    case IF: token_type = "IF"; break; 
                    case THEN: token_type = "THEN"; break; 
                    case ELSE: token_type = "ELSE"; break;
                    case DIV: token_type = "DIV"; break; 
                    case MINUS: token_type = "MINUS"; break; 
                    case TIME: token_type = "TIME"; break; 
                    case PRINT: token_type = "PRINT"; break; 
                    case STRING: token_type = "STRING"; break;
                    case MEMORY: token_type = "MEMORY"; break;
                    case TEMPORARY_MEMORY: token_type = "TEMPORARY_MEMORY"; break;
                    case NONE: token_type = "NONE"; break;
                    case BIGGER: token_type = "BIGGER"; break;
                    case SMALLER: token_type = "SMALLER"; break;
                    case PP: token_type = "PP"; break;
                    case MM: token_type = "MM"; break;
                    case LET: token_type = "LET"; break;
                    case ASSIGN: token_type = "ASSIGN"; break;
                    case COMMA: token_type = "COMMA"; break;
                    case FUNCTION: token_type = "FUNCTION"; break;
                    case PARAMATER: token_type = "PARAMATER"; break;
                    case DOUBLE_COLON: token_type = "DOUBLE_COLON"; break;
                    case FUNCTION_CALL: token_type = "FUNCTION_CALL"; break;
                    case LP: token_type = "LP"; break;
                    case RP: token_type = "RP"; break;
                    case DO: token_type = "DO"; break;
                    case WHILE: token_type = "WHILE"; break;
                    case LIST: token_type = "LIST"; break;
                    case LIST_NAME: token_type = "LIST_NAME"; break;
                    case ARROW_TOKEN: token_type = "ARROW_TOKEN"; break;
                    case SPARE_LP: token_type = "SPARE_LP"; break;
                    case SPARE_RP: token_type = "SPARE_RP"; break;
                    case FOR_LOOP: token_type = "FOR_LOOP"; break;
                    case IN: token_type = "IN"; break;
                    case TO: token_type = "TO"; break;
                    case END: token_type = "END"; break;
                    case RETURN_FUNC: token_type = "RETURN_FUNC"; break;
                    case POP: token_type = "POP"; break;
                    case PUSH: token_type = "PUSH"; break;
                    case AT: token_type = "AT"; break;
                    case REPAIR: token_type = "REPAIR"; break;
                    case PARAMATER_KWARGS: token_type = "PARAMATER_KWARGS"; break;
                    case DIFFERENCES: token_type = "DIFFERENCES"; break;
                    case BE: token_type = "BE"; break;
                    case SE: token_type = "SE"; break;
                    case EQUAL: token_type = "EQUAL"; break;
                    case DOT: token_type = "DOT"; break;
                }
                cout << "Type: " << token_type << " Value: " << token.value << " Name: " << token.name << endl;
            }
        }
    }
}

int interpreter(string file_name) {
    std::ifstream inputFile(file_name);
    if (!inputFile) {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        lexer lex(line);
        vector<datatype> tokens = lex.token();
        parser par(tokens);
        par.run_code();
    }

    inputFile.close();
    return 0;
}

int main() {
    cout << "enter 'debug' to debug, 'run' to run, or file name to run file" << endl;
    cout << "mode> ";
    string mode;
    getline(cin, mode);
    if (mode == "debug") {
        debug();
    } else if (mode == "run") {
        run();
    } else {
        interpreter(mode);
    }
    return 0;
}
