/*
Project on : Image Steganography 
Group 10 (ISS)
Harshil Shah - 201501097   Het Sheth - 1401051
*/

#include "header_Steganography.h"

int main(int argc,char *argv[])
{
    int i;
    char *argv_2,*argv_3,*argv_4;

    switch(argc)
    {
			//Cases to decode or encode according to the command fired 
	case 8 :	if(!strcmp(argv[1],"-E"))
			{
			    for (i = 2; i < 8; i++)
			    {
				if (!strcmp(argv[i],"-i"))
				    argv_2 = argv[i+1];

				if (!strcmp(argv[i],"-s"))
				    argv_3 = argv[i+1];

				if (!strcmp(argv[i],"-o"))
				    argv_4 = argv[i+1];
			    }			    
			    Encode(argv_2, argv_3, argv_4);
			    break;
			}

	case 6 :	if(!strcmp(argv[1], "-D"))
			{
			    for (i = 2; i < 6; i++)
			    {
				if (!strcmp(argv[i],"-i"))
				    argv_2 = argv[i+1];
				if (!strcmp(argv[i],"-o"))
				    argv_4 = argv[i+1];
			    }			    

			    Decode(argv_2, argv_4);
			    break;
			}

	default : 
                printf("\n\n*** IMAGE STEGANOGRAPHY (with password and magic string protection) ***\n");
		printf("\n\nFor Execution => ");
		printf("\n\nENCODING => \t./a.out -E -i <input.bmp> -s <secret_text.txt> -o <output.bmp>");
		printf("\n\nDECODING => \t./a.out -D -i <output.bmp> -o <output_text.txt>\n\n");

    }	
    return 0;
}

