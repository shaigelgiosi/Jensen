#include<stdio.h>
#include<string.h>
int main(void)
{
    char str[100];
    if(fgets(str,sizeof(str),stdin)!=NULL)
    {
        for(int i=0;str[i]!='\0';i++)
        {
            if(str[i]>='a'&&str[i]<='y')
            {
                str[i]=str[i]+1;
            }
            else if(str[i]=='z')
            {
                str[i]='a';
            }
            else if(str[i]>='A'&&str[i]<='Y')
            {
                str[i]=str[i]+1;
            }
            else if(str[i]=='Z')
            {
                str[i]='A';
            }
        }
        printf("%s",str);
    }
    return 0;
}

