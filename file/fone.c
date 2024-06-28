 #include <stdio.h>
 #include <ctype.h>
 #include <stdlib.h>

 int display_file(FILE *);
 int copy_file(FILE *, FILE *);
 int main()
 {
     FILE *input = NULL, *output = NULL;
     int ret_value = 1;
     input = fopen("test", "r");
     if(input == NULL)
     {
         printf("opening 'test' failed\n");
         return EXIT_FAILURE;
     }
     output = fopen("sample", "w");
     if(output == NULL)
     {
         printf("Opening 'sample' failed\n");
         return EXIT_FAILURE;
     }

     ret_value = copy_file(input, output);
     if(ret_value == 0)
     {
         printf("Error in copying a file");
         return EXIT_FAILURE;
     }
     ret_value = fclose(output);
     if(ret_value != 0)
     {
         printf("Error in closing 'sample' file");
         return EXIT_FAILURE;
     }

     ret_value = fclose(input);
     if(ret_value != 0)
     {
         printf("Error in closing 'test' file");
         return EXIT_FAILURE;
     }
     output = fopen("sample", "r");
     if(output == NULL)
     {
         printf("Opening 'sample' failed\n");
         return EXIT_FAILURE;
     }
     ret_value = display_file(output);
     if(ret_value==0)
     {
         printf("Displaying 'output' failed\n");
         return 0;
     }

     ret_value = fclose(output);
     if(ret_value != 0)
     {
         printf("Error in closing 'output' file");
         return EXIT_FAILURE;
     }
     return 0;
 }

 int display_file( FILE *arg_file )

 {
  char file_char = '\0';

  while(1)
  {

   if(feof(arg_file) != 0)
   {
    break;
   }

   file_char = (char)fgetc(arg_file);
   printf("%c", file_char);
  }
  printf("\n");
  return 1;
 }

 int copy_file(FILE *in_file, FILE *out_file )
 {
  int ret = 0;

  char file_char = '\0', out_char = '\0';

  while(1)
  {

   if(feof(in_file) != 0)
   {
    break;
   }
     file_char = (char)fgetc(in_file);
     if(isalpha(file_char))   {
      out_char = toupper(file_char);
      ret = fputc(out_char, out_file);
     if(EOF == ret)    {
            return 0;
    }
   }
   else
   {
    ret = fputc(file_char, out_file);
    if(EOF == ret)
    {
     return 0;
    }
   }
  }

  return 1;
 }
