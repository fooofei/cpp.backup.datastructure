
#include <stdio.h>
#include <stdint.h>
#include <string.h>





extern int calc_math_expression(const char * math_expression, double *expression_value);


void
_test_framework(const char* expr, const char* result)
{
    double expression_value;
    bool pass = false;
    char value_string[128] = {0};

    if (calc_math_expression(expr, &expression_value) == 0)
    {
        snprintf(value_string, sizeof(value_string), "%.6f", expression_value);
        pass = (strcmp(result, value_string) == 0);
    }
    printf("%s % s= %s, expect=%s\n", (pass ? "pass" : "fail"), expr, value_string, result);
}



int main()
{
    
    _test_framework("(1 + 2) * 4", "12.000000");

    _test_framework("1  +   2 * (3 + 4)  + MSTR(5) * MSUB 5 + MRD() / 10 - PE 5", "40.000000");
    
    _test_framework("40 + 0 - PE 5", "40.000000");
    _test_framework("0x1 + 0x3", "4.000000");
    _test_framework("6 + PE 5", "6.300000");


    return 0;
}
