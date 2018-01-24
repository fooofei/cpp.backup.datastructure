

#include <queue>
#include <stack>
#include <list>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include "testlib.h"


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

typedef std::stack<operator_t> operators_stack_t;
typedef std::stack<number_t> numbers_stack_t;

struct lexer_t
{
    double mstore;
    operators_stack_t s_operators;
    numbers_stack_t s_numbers;
};
typedef struct lexer_t lexer_t;

void
lexer_clear(lexer_t * l)
{
    l->mstore = 0;

    for (;!l->s_operators.empty();)
    {
        l->s_operators.pop();
    }

    for (;!l->s_numbers.empty();)
    {
        l->s_numbers.pop();
    }
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

/* 退避缓存算法 */

int
lexer_lex(lexer_t * l, const char * buffer)
{
    const char * cursor = buffer;
    number_t d;
    int ret;
    operator_t token_id=token_none;
    operator_t token_id2=token_none;

    operators_stack_t & s1 = l->s_operators;
    numbers_stack_t & s2 = l->s_numbers;

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

            s2.push(d);
        }
        else if ((ret = lexer_is_operator(&cursor,&token_id))==0)
        {
            s1.push(token_id);
        }

        else
        {
            return -1;
        }
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

// 退避缓存算法 
/*
构建操作符栈s1和操作数栈s2，并准备一个临时缓存用的操作符ts1和操作数ts2。
1、首先解析字符串成s1和s2。
1.1 遍历表达式字符串，将表达式中的数据和操作符按顺序分别依次压入s1和s2
1.2 然后向s1压入一个箱底，即最低优先级的操作符，假定为NONE（说明: ‘)’操作符的优先级仅高于NONE操作符）
1.3  此时的s1和s2与原始表达式相比，正好是反转表达式，需要反正成正向表达式
2、开始计算，从s1中取出操作符x，如果x是
2.1 ‘(’，则直接压入ts1

2.2   ‘)’，则判断ts1栈顶操作符，如果是‘(’，则直接弹出，丢弃‘(’和‘)’，返回第2步，继续取下一个操作符x；
如果不是‘(’，则将‘)’重新压回s1，以等待ts1栈顶出现‘(’
2.2.1  如果ts1栈顶操作符不是‘(’ ，则判断ts1栈顶操作符的优先级与s1栈顶操作符的优先级关系(即下一个待计算的操作符)，
如果ts1缓存的栈顶操作符优先级大于或者等于s1栈顶的操作符，说明需要优先计算之前缓存的操作符，
因此，将ts1栈顶操作符及其对应的左操作数(如果有左操作数)分别弹出，并依次压入s1和s2等待下一步计算。
然后返回第2步，继续取下一个操作符x 。——退避弹出过程

2.3  其他操作符，如果x的优先级小于（不包含等于）s1栈顶操作符的优先级（即下一个操作符的优先级），说明x操作符还不能进行计算，
则将x及其对应的左操作数(如果存在的话，单目操作无左操作数)，分别压入ts1和ts2缓存起来。
然后返回第2步，继续取下一个操作符x ；否则，按x操作符计算，将计算结果放入s2。——退避缓存过程

3  重复2，直到取出压箱底NONE操作符，完成计算过程
4  s2中存在的唯一操作数即为计算结果
异常处理：生成s1/s2或者计算过程中，均可能发现表达式错误，一旦发现错误则停止计算，返回失败。

注: s1 的数据结构不应该是栈，不然到 2.2 会出现死循环

太乱了  我失败了
*/

int 
parser_parse(lexer_t * l, number_t * out_result)
{
    number_t number1;
    number_t number2;
    number_t result;
    int ret;

    int32_t count;
    std::list<operator_t> s1;
    numbers_stack_t & s2 = l->s_numbers; 

    operators_stack_t ts1;
    numbers_stack_t ts2;
    operator_t oper_x;


    for (;!l->s_operators.empty();)
    {
        s1.push_front(l->s_operators.top());
        l->s_operators.pop();
    }


    for (;!s1.empty();)
    {
        oper_x = s1.front();
        s1.pop_front();

        if (oper_x == token_left_brackets)
        {
            ts1.push(oper_x);
        }
        else if(oper_x == token_right_brackets)
        {
            if (ts1.top() == token_left_brackets)
            {
                ts1.pop();
            }
            else
            {
                // TODO
                if (ts1.top() >= s1.front())
                {
                }
                s1.push_back(oper_x);
            }
        }
        // 运算符优先级低 不能立即计算
        else if (!s1.empty() && oper_x < s1.front())
        {
            ts1.push(oper_x);
        }

       

    }


   
    *out_result = result;
    return 0;
}



UINT32 calc_math_expression(const char * math_expression, double *expression_value)
{
    lexer_t l;
    int ret;

    lexer_clear(&l);

    ret = lexer_lex(&l, math_expression);
    if (ret != 0)
    {
        return RET_FAILURE;
    }

    ret = parser_parse(&l, expression_value);
    if (ret != 0)
    {
        return RET_FAILURE;
    }
    return RET_SUCCESS;
}

