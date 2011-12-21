/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test the posix regexp api 
 *
 *        Version:  1.0
 *        Created:  2011年12月21日 10时54分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Regan (), lcqhigh@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <sys/types.h>
#include <regex.h>
#include <assert.h>

#include	<stdio.h>
#include	<stdlib.h>

static int match(const char *str, const char *regexp)
{
    if ((!str) || (!regexp))
        return 0;
    
    int ret = 0;
    regex_t reg;
    static const int flag = REG_EXTENDED | REG_ICASE;
    static char  errbuf[128];
    int res = regcomp(&reg, regexp, flag);
    if (res) {
        regerror(res, &reg, errbuf, sizeof(errbuf));
        printf("compile the [%s] failed for %s\n", regexp, errbuf);
        goto out;
    }
    
    regmatch_t matches[4];
    res = regexec(&reg, str, 4, matches, 0);
    if (!res) {
        int k, j;
        for (j = 0; j < 4; ++j)
        {
            if (matches[j].rm_so == -1)
                break;
            for (k = matches[j].rm_so; k < matches[j].rm_eo; ++k)
                putchar(str[k]);
            printf ( "\n" );
        }
        /* 
        regmatch_t *mp = &matches[0];
        while (mp->rm_so != -1)
        {
            int k = 0;
            for (k = mp->rm_so; k < mp->rm_eo; ++k)
            {
                putchar(str[k]);
            }
            printf ( "\n" );
            ++mp;
        }
        */
        ret = 1;
        printf ( "match\n" );
    }
    else
        printf ( "doesn't match\n" );

out:
    regfree(&reg);
    return ret;
}


int main()
{
    const char *regex = "\r\nat\\^SISR: [0-9]+,[0-9]{1}\r\n[^\\^]*\\^SISR:";
    const char *exp2 = "\\<\\d+\\>";
    const char *test_str2 = "34,43, 43, 4326";
    const char *test_str1 = "ewrwerwe\r\nat^SISR: 1,2\r\n^SISR:hew";

    char exp[128];
    char str[256];

    match(test_str1, regex);

    while (scanf("%s%s", exp, str) != EOF)
    {
        match(str, exp);
    }

    return 0;
}
