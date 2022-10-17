#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// The aim of the program is to implement Absolute loader in C

char input[10], label[10], hexstr[2];
int addr, f = 0, start, ptaddr, l, length = 0, end, count = 0, taddr, address, i = 0;
FILE *fp1, *fp2;

int charToHex(char* str)
{
    int num;
    sscanf(str, "%X", &num);
    return num;
}

void check()
{
    count++;
    address++;
    taddr = taddr + 1;
    if (count == 4)
    {
        fprintf(fp2, "  ");
        i++;
        if (i == 4)
        {
            fprintf(fp2, "\n\t%X\t\t\t", taddr);
            i = 0;
        }
        count = 0;
    }
}

void main()
{
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w");
    fscanf(fp1, "%s", input);

    fprintf(fp2, "Memory Address\t\t\t\t\tContent");
    fprintf(fp2, "\n______________\t\t______________________________________");
    while (strcmp(input, "E") != 0)
    {
        if (strcmp(input, "H") == 0)
        {
            fscanf(fp1, "%s %X %X %s", label, &start, &end, input);
            address = start;
        }
        else if (strcmp(input, "T") == 0)
        {
            l = length;
            ptaddr = addr;
            fscanf(fp1, "%X %X %s", &taddr, &length, input);
            addr = taddr;
            if (f == 0)
            {
                ptaddr = address;
                f = 1;
            }
            for (int k = 0; k < (taddr - (ptaddr + l)); k++)
            {
                address++;
                fprintf(fp2, "XX");
                count++;
                if (count == 4) 
                {
                    fprintf(fp2, "  ");
                    i++;
                    if (i == 4)
                    {
                        fprintf(fp2, "\n\t%X\t\t\t", address);
                        i = 0;
                    }
                    count = 0;
                }
            }
            if (taddr == start)
                fprintf(fp2, "\n\t%X\t\t\t", taddr);

            for(int k=0; k<strlen(input); k+=2)
            {
                hexstr[0] = input[k];
                hexstr[1] = input[k+1];
                fprintf(fp2, "%02X", charToHex(hexstr));
                check(); 
            }
            fscanf(fp1, "%s", input);
        }
        else
        {
            for(int k=0; k<strlen(input); k+=2)
            {
                hexstr[0] = input[k];
                hexstr[1] = input[k+1];
                fprintf(fp2, "%02X", charToHex(hexstr));
                check(); 
            }
            fscanf(fp1, "%s", input);
        }
    }

    count--;
    check();
    if(i < 4)
    {
        if(count < 4)
        {
            for(int j=0; j<4-count; j++)
                fprintf(fp2, "XX");
            i++;
        }
        for(int k=0; k<4-i; k++)
            fprintf(fp2, "  XXXXXXXX");
    }
    
    fclose(fp1);
    fclose(fp2);
}

// END
