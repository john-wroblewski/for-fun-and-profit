/* detab */
    /* write a program 'detab' that replaces tabs in the input with
    the proper number of blanks to space to the next tab stop.
    Assume a fixed set of tab stops, say every n columns. Should
    n be a variable or a symbolic parameter? 
    */
#include <stdio.h>

int stringtointeger(char * str);  /* converts the argument to integer if capable */

int main(int argc,char *argv[]){
    if(argc != 2)
        printf("Usage: %s n [tabstop every n columns]\n",argv[0]);
    else{
        int tabstop,k,c;
        if((tabstop = stringtointeger(argv[1]))){
            if(tabstop > 10)
                printf("Tab stop must be less than 10\n");
            else{
                k = tabstop;
                while((c = getchar()) != EOF){
                    if(c != '\t'){
                        putchar( c );
                        if( c == '\n' )
                            k = tabstop;
                        else{
                            if(!(--k))
                                k = tabstop;
                        }
                    }else{
                        for(;k>0;k--)
                            putchar( ' ' );
                        k = tabstop;
                    }
                }
            }
        }
        else
            printf("Input Error. Make sure you are using an integer for argument\n");
    }
    return 0;
}
int stringtointeger(char *str){ /* returns int if argument is int, else returns 0 */
    int i = 0 , c , t = 0;

    if((c = str[i]) < '0' || c > '9')
        return 0;
    else{
        for( i = 0;((c = str[i]) != '\0' && c >= '0' && c <= '9'); ++i )
            t = ( t * 10 ) + ( c - '0' );
        if( c != '\0' )
            return 0;
        return t;
    }
}
