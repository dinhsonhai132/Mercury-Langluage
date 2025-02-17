#include "lexer.h"

using namespace std;

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
            tokens.push_back(token(dot_count == 0 ? INT : FLOAT,
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
