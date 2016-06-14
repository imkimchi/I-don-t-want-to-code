#include <stdio.h>
#include <string.h>

void printError(char *argv, int line, char *error, char *file);
void printBlank(unsigned long size);
char pyFileCheck(int argc, char **argv, char **pyFile);

int main(int argc, char **argv)
{
    char source[255];
    char *pyFile;
    int i = 1;
    char str[300]={0,};

    if(argc > 1){
      pyFileCheck(argc, argv, &pyFile);
      FILE *pFile = fopen(pyFile, "r");
      //파일 불러오기 실패했을시 에러출력
      for(int i=0; i<argc-1; i++){
          if(pFile == NULL){
              printf("/usr/local/Cellar/python/2.7.10_2/Frameworks/Python.framework/Versions/2.7/Resources/Python.app/Contents/MacOS/Python: can't open file");
              printf("%s: [Errno 2] No such file or directory", argv[1]);
          };
      };

      //파일 불러오기 성공할 시 실행
      if(pFile != NULL) {
          char *pStr;
          while(!feof(pFile)) {
              pStr = fgets(source, sizeof(source), pFile);
              unsigned long length = strlen(source)+1;
              char lastChar = source[strlen(source)-2];
              switch(lastChar){
                  case '"': //마지막 문자가 " 일 경우
                      printError(pyFile, i,"Quotes", NULL);
                      printf("   %s", source);
                      printBlank(length);
                      printf("^\n");
                      printf("SyntaxError: EOL while scanning string literal\n");
                      break;
              }
              i++;
          }
          fclose(pFile);
      }
    } else {
      puts("Python 2.7.10 (default, Nov 21 2015, 12:59:54)");
      puts("[GCC 4.2.1 Compatible Apple LLVM 7.0.0 (clang-700.1.76)] on darwin");
      puts("Type \"help\", \"copyright\", \"credits\" or \"license\" for more information.");
      while(1){
        printf("> ");
        scanf("%s", str);
        puts("Traceback (most recent call last):");
        puts("  File \"<stdin>\", line 1, in <module>");
        printf("NameError: name '%s' is not defined\n", str);
        memset(str, 0, sizeof(str));
      }
    }

    return 0;
}

//라인 수와 함께 에러 출력
void printError(char *argv, int line ,char * error,char *file){
    if(!strcmp(error, "Quotes")){
        printf(" File \"%s\", line %d\n",argv,line);
    }
}

void printBlank(unsigned long size){
    for(int i=0; i<size; i++){
        printf(" ");
    }
}

//argv 인자중에서 py파일을 pyFile에 저장함
char pyFileCheck(int argc, char **argv, char **pyFile){
    char *checkC;

    for(int i=1; i<argc; i++){
        checkC = strchr(argv[i], '.');
        if(!(checkC == NULL)){
            if(!strcmp(checkC, ".py")){
                *pyFile = argv[i];
                return 0;
            }
        }
    }
    return 1;
}
