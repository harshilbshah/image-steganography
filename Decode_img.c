// decryption of sizes
 void size_decryption(FILE *pf1, int *size_txt)
{
	int file_buff = 0, i;
	int ch, bit_msg;
	for (i = 0; i < 8; i++)
	{
		ch = fgetc(pf1);
		bit_msg = (ch & 1);
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}
	}
	*size_txt = file_buff;
}

// decryption of strings
void string_decryption(FILE *pf1,char *strng,int size)
{
	int file_buff=0, i, j=0, k=0;
	int ch, bit_msg;
	for (i = 0; i < (size * 8); i++)
	{
		j++;
		ch = fgetc(pf1);
		bit_msg = (ch & 1);
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}

		if ( j == 8)
		{
			strng[k] =(char)file_buff; 
			j=0;
			k++;
			file_buff = 0;
		}
	}
	strng[k] = '\0';
}
// decryption of secret message
void secret_decryption(int size_txt, FILE *pf1, FILE *pf2)
{
	int file_buff=0, i, j = 0, k = 0;
	int ch,bit_msg;
	char output[250] = {0};
	for (i = 0; i < (size_txt * 8); i++)
	{
		j++;
		ch = fgetc(pf1);
		bit_msg = (ch & 1);
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}

		if ( j == 8)
		{
			putc(file_buff, pf2);
			output[k++] = file_buff;
			j=0;
			file_buff = 0;
		}
	}
	printf("\nDecoded Secret Text is =>  %s\n\n", output);
}

//Decode function
int Decode(char *argv_2, char *argv_4)
{
	FILE *pf1, *pf2;
	
	int size, size1, size_txt;

	//opening Image File
	if((pf1 = fopen(argv_2, "r")) == NULL) 
	{
		printf("\nFile %s does not exist.\nAborting the execution\n", argv_2);
		return 1;
	}

	fseek(pf1,54 ,SEEK_SET);
	
        //opening the file in which the decrypted text will be stored
	if((pf2 = fopen(argv_4, "w+")) == NULL) 
	{
		printf("\nFile %s does not exist.\nAborting the execution\n", argv_4);
		return 1;
	}

	//magic str
	char magic_strn[20], magic_strn1[20], strng[20];
	int j;

	size_decryption(pf1,&size);
	string_decryption(pf1,magic_strn,size);
        
        int a,b;
        int temp;

        do
        {
	printf("\nEnter the  Magic String : ");
	for(j = 0;(magic_strn1[j] = getchar()) != '\n'; j++);
	magic_strn1[j]= '\0';

	
	temp = strcmp(magic_strn1, magic_strn);

	if(temp)
	{
		printf("\nERROR !!!\n*** Entered Wrong Magic String ***\n\n");
		printf("\nRe-enter the Magic String\n");
                a=1;
	}
	else
        {
		printf("\n*** Magic String Accepted ***\n\n");
                a=0;
        }

        }while(a);


	//password
	char passwd[20], passwd_str[20];

	size_decryption(pf1,&size1);
	string_decryption(pf1,passwd_str,size1);

        do{
	printf("\nEnter The Password : ");
	scanf("%s", passwd);

	temp = strcmp(passwd,passwd_str);

	if(temp)
	{
		printf("\nERROR !!!\n*** Entered Wrong Password ***\n\n");
		printf("\nRe-enter the Passowrd\n");
                b=1;
	}
	else
        {
		printf("\n*** Password Accepted ***\n\n");
                b=0;
        }
        }while(b);

	//Secret Text 
	size_decryption(pf1, &size_txt);
	secret_decryption(size_txt, pf1, pf2);

	printf("\nThe Secret Text Is Copied To => %s\n\n", argv_4);

	// closeing files
	fclose(pf1);

}
