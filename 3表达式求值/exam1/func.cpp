

#include <queue>
#include <stack>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


/* 整个代码分为两个部分 lexer parser 对应 词法解析 语法解析 */

/* 原生的逆波兰式 未使用改进算法 未作改进 */

/* 按照优先级排列 最小的在前 */
enum token_t
{
    token_none = 0,

    token_right_brackets,

    token_plus,
    token_sub,
    token_multiply,
    token_divide,

    token_single_begin,

    token_mclr,
    token_mrd,
    token_mstr,
    token_mplus,
    token_msub,

    token_single_end,

    token_left_brackets,
    token_pe,

    token_end,
};
typedef token_t operator_t;

/* return -1 for fail */
int32_t 
_operator_need_number_count(operator_t i)
{
    if (i > token_right_brackets && i < token_single_begin)
    {
        return 2;
    }
    else if (i > token_single_begin && i < token_single_end)
    {
        switch (i)
        {
        case token_mclr: return 0;
        case token_mrd: return 0;
        default: return 1;
        }
    }


    else if (i == token_pe)
    {
        return 2;
    }
    return -1;
}



typedef double number_t;

struct value_t
{
    enum{ value_number, value_operator } type;
    union 
    {
        number_t number;
        operator_t oper;
    };
};
void value_clear(value_t * v);


struct lexer_t
{
    std::queue<value_t> expression;
    double mstore;
};
typedef struct lexer_t lexer_t;

void
lexer_clear(lexer_t * l)
{
    for (;!l->expression.empty();)
    {
        l->expression.pop();
    }

    l->mstore = 0;
}

bool
lexer_is_number(const char * buffer)
{

    if (buffer[0] >= '0' && buffer[0] <= '9')
    {
        return true;
    }


    if (0 == strncmp(buffer,"0x",2)
        || 0 == strncmp(buffer,"0X",2)
        )
    {
        return true;
    }

    return false;
}

/* return 0 for success */
int
lexer_get_number(const char ** buffer, number_t * d)
{
    char * p = 0;
    number_t v;

    v = strtod(*buffer, &p);
    if (p == *buffer)
    {
        return -1;
    }

    *d = v;
    *buffer = p;
    return 0;
}


bool
_is_token(const char ** buffer, operator_t * out_token_id
    , const char * token_s
    , operator_t token_id)
{
    if (0 == memcmp(*buffer,token_s,strlen(token_s)))
    {
        *buffer += strlen(token_s);
        *out_token_id = token_id;
        return true;
    }
    return false;
}

/* return 0 for success */
int  
lexer_is_operator(const char ** buffer, operator_t * token_id)
{

    switch (**buffer)
    {
    case '+': *buffer += 1; *token_id = token_plus; return 0;
    case '-': *buffer += 1; *token_id = token_sub; return 0;
    case '*': *buffer += 1; *token_id = token_multiply; return 0;
    case '/': *buffer += 1; *token_id = token_divide; return 0;
    default:
        break;
    }

    if (**buffer =='M')
    {
        if (_is_token(buffer,token_id,"MCLR",token_mclr))
        {
            return 0;
        }

        if (_is_token(buffer,token_id,"MRD",token_mrd))
        {
            return 0;
        }

        if (_is_token(buffer,token_id,"MSTR",token_mstr))
        {
            return 0;
        }
        if (_is_token(buffer, token_id, "MPLUS", token_mplus))
        {
            return 0;
        }

        if (_is_token(buffer, token_id, "MSUB", token_msub))
        {
            return 0;
        }
    }

    if (_is_token(buffer,token_id,"PE",token_pe))
    {
        return 0;
    }

    if (_is_token(buffer,token_id,"(",token_left_brackets))
    {
        return 0;
    }
    if (_is_token(buffer, token_id, ")", token_right_brackets))
    {
        return 0;
    }

    return -1;
}


int
lexer_lex(lexer_t * l, const char * buffer)
{
    const char * cursor = buffer;
    number_t d;
    int ret;
    operator_t token_id=token_none;
    operator_t token_id2=token_none;
    value_t v;

    /* s1 s2 对应逆波兰表达式中的 s1 s2 */
    std::stack<operator_t> s1;

    /* 这样取出来就已经是反转过的 stack 会是反序 */
    std::queue<value_t> & s2 = l->expression;

    s1.push(token_none);

    for (;*cursor;)
    {
        if (' ' == *cursor)
        {
            cursor += 1;
        }
        else if (lexer_is_number(cursor))
        {
            d = 0;
            ret = lexer_get_number(&cursor, &d);
            if (ret != 0)
            {
                return ret;
            }
            v.type = value_t::value_number;
            v.number = d;
            s2.push(v);
        }
        else if ((ret = lexer_is_operator(&cursor,&token_id))==0)
        {
            
            if (token_id == token_left_brackets)
            {
                s1.push(token_id);
            }
            else if (token_id == token_right_brackets)
            {
                for (;!s1.empty();)
                {
                    token_id2 = s1.top();
                    s1.pop();

                    if (token_id2==token_left_brackets)
                    {
                        break;
                    }
                    v.type = value_t::value_operator;
                    v.oper = token_id2;
                    s2.push(v);
                }
            }
            else if (s1.top() == token_left_brackets 
                || token_id > s1.top()
                )
            {
                s1.push(token_id);
            }
            else 
            {
                for (;!s1.empty() && (!(s1.top()<token_id) || s1.top()==token_left_brackets);)
                {
                    v.type = value_t::value_operator;
                    v.oper = s1.top();
                    s1.pop();
                    s2.push(v);
                }
                s1.push(token_id);
            }
        }

        else
        {
            return -1;
        }
    }


    for (;!s1.empty();)
    {
        if (token_none != s1.top())
        {
            v.type = value_t::value_operator;
            v.oper = s1.top();
            s2.push(v);
        }
        s1.pop();
    }

    return 0;
}

/* return 0 for success, other for fail */
int
parser_binocular_operator(number_t * n1, number_t * n2, operator_t op, number_t * result)
{
    switch (op)
    {
    case token_plus: *result = *n1 + *n2; return 0;
    case token_sub: *result = *n1 - *n2; return 0;
    case token_multiply: *result = *n1 * *n2; return 0;
    case token_divide: if (*n2 == 0) { return -1; } *result = *n1 / *n2; return 0;
    case token_pe: *result = ((*n1)*(*n2) / 100); return 0;
    default: return -1;
    }
}

/* return 0 for success, other for fail */
int
parser_unary_operator(lexer_t * l, number_t * n1, operator_t op, number_t * result)
{
    switch (op)
    {
    case token_mstr: *result = *n1; l->mstore = *n1; return 0;
    case token_mplus: *result = *n1; l->mstore += *n1; return 0;
    case token_msub: *result = *n1; l->mstore -= *n1; return 0;
    default: return -1;
    }
}


int
parser_zero_operator(lexer_t * l, operator_t op, number_t * result)
{
    switch (op)
    {
    case token_mclr:  *result = 0;  l->mstore = 0; return 0;
    case token_mrd: *result = l->mstore; return 0;
    default: return -1;
    }
}


int 
parser_parse(lexer_t * l, number_t * out_result)
{
    std::stack<int8_t> opers_tmp;
    std::stack<number_t> s_result;
    number_t number1;
    number_t number2;
    number_t result;
    int ret;

    value_t * p;
    int32_t count;
    std::queue<value_t> & expr = l->expression;

    for (;!expr.empty();)
    {
        p = &expr.front();

        if (p->type==value_t::value_number)
        {
            s_result.push(p->number);
        }

        else 
        {

            // operator
            count = _operator_need_number_count(p->oper);
            if (count == -1)
            {
                return -1;
            }

            switch (count)
            {
            case 0:
                ret = parser_zero_operator(l, p->oper, &result);
                if (ret != 0)
                {
                    return -2;
                }
                s_result.push(result);
                break;
            case 1:
                if (s_result.empty())
                {
                    return -3;
                }
                number1 = s_result.top(); s_result.pop();
                ret = parser_unary_operator(l, &number1, p->oper, &result);
                if (ret != 0)
                {
                    return -4;
                }
                s_result.push(result);
                break;
            case 2:
                if (s_result.empty())
                {
                    return -5;
                }
                number1 = s_result.top(); s_result.pop();
                if (s_result.empty())
                {
                    return -6;
                }
                number2 = s_result.top(); s_result.pop();
                if (p->oper == token_pe)
                {
                    /* PE 操作符 不取出左操作数 需要放回去 */
                    s_result.push(number2);
                }
                ret = parser_binocular_operator(&number2, &number1, p->oper, &result);
                if (ret != 0)
                {
                    return -7;
                }
                s_result.push(result);

                break;

            default: return -8;
            }


        }

        expr.pop(); // pop_front

    }


    if (s_result.empty())
    {
        return -9;
    }

    result = s_result.top(); s_result.pop();
    if (!s_result.empty())
    {
        return -10;
    }
    *out_result = result;
    return 0;
}



int calc_math_expression(const char * math_expression, double *expression_value)
{
    lexer_t l;
    int ret;

    lexer_clear(&l);

    ret = lexer_lex(&l, math_expression);
    if (ret != 0)
    {
        return -1;
    }

    ret = parser_parse(&l, expression_value);
    if (ret != 0)
    {
        return -2;
    }
    return 0;
}

void 
value_clear(value_t * v)
{
    memset(v, 0, sizeof(*v));
}
