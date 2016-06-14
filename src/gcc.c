#include <stdio.h>
#include <string.h>

void printError(char *argv, int line, unsigned long widthLine, char *error, char *file);
void printBlank(unsigned long size);
int checkCnt(int count);
void printTotalError(int errorCnt, int warnCnt);
char cFileCheck(int argc, char **argv, char **cFile);

int main(int argc, char **argv)
{
    char source[255];
    char *cFile;

    int i = 1;
    int errorCnt = 0;
    int warnCnt = 0;
    char *pch;
    unsigned long quoteLocation;

    cFileCheck(argc, argv, &cFile);
    FILE *pFile = fopen(cFile, "r");
    //파일 불러오기 실패했을시 에러출력
    if(pFile == NULL){
            printf("clang: error: no such file or directory: %s \n", cFile);
            puts("clang: error: no input file");
    };

    //파일 불러오기 성공할 시 실행
    if(pFile != NULL) {
        char *pStr;
        while(!feof(pFile)) {
            pStr = fgets(source, sizeof(source), pFile);
            unsigned long length = strlen(source)+3;
            char lastChar = source[strlen(source)-2];
            switch(lastChar){
                case ';': // 마지막 문자가 ;일경우 세미콜론 오류 출력
                    printError(cFile, i, strlen(source)-1, "semicolon", NULL);
                    printf("%s", source);
                    printBlank(length+1);
                    printf("\033[92m%c\033[0m\n",'^');
                    printBlank(length+1);
                    printf("\033[92m%c\033[0m\n",';');
                    errorCnt++;
                    break;

                case '>': // 마지막 문자가 >일경우 include 오류 출력
                    pch = strchr(source, '<');quoteLocation = pch-source+1;
                    source[strlen(source)-1] = '\0';
                    printError(cFile, i, quoteLocation, "include", pch);
                    printf("%s\n", source);
                    printBlank(quoteLocation-1);
                    printf("\033[92m%c\033[0m\n\n",'^');
                    errorCnt++;
                    break;
            }
            i++;
        }
        printTotalError(errorCnt, warnCnt);
        fclose(pFile);
    }
    return 0;
}

//라인 수와 함께 에러 출력
void printError(char *argv, int line, unsigned long widthLine, char *error, char *file){
    if(!strcmp(error, "semicolon")){
        printf("\033[1m%s:%d:%lu:\033[0m \033[31m%s\033[0m \033[1m%s\033[0m\n", argv, line, widthLine,"error:","expected ';' after expression");
    }
    if(!strcmp(error, "include")){
        printf("\033[1m%s:%d:%lu:\033[0m \033[31m%s\033[0m \033[1m%s %s\033[0m\n", argv, line, widthLine,"fatal error:",file,"file not found");
    }
}

void printBlank(unsigned long size){
    for(int i=0; i<size; i++){
        printf(" ");
    }
}

//에러가 2개 이상인지 확인
int checkCnt(int count){
    if(count>1) return 1;
    else return 0;
}

//에러가 몇갠지 출력
void printTotalError(int errorCnt, int warnCnt){
    char warnMessage[13] = "warning and";
    char errorMessage[17] = "error generated";

    if(checkCnt(errorCnt)){
        strcpy(errorMessage, "errors generated");
    } else if(checkCnt(warnCnt)){
        strcpy(warnMessage, "warnings and");
    }

    if(!warnCnt)
        printf("%d %s.\n", errorCnt, errorMessage);

    if(warnCnt)
        printf("%d %s %d %s.\n", warnCnt, warnMessage, errorCnt, errorMessage);
}

//argv 인자중에서 c파일이나 cpp파일을 cFile에 저장함
char cFileCheck(int argc, char **argv, char **cFile){
    char *checkC;

    for(int i=1; i<argc; i++){
        checkC = strchr(argv[i], '.');
        if(!(checkC == NULL)){
            if(!strcmp(checkC, ".c") || !strcmp(checkC, ".cpp")){
                *cFile = argv[i];
                return 0;
            }
        }
    }
    return 1;
}
