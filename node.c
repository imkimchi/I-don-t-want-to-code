#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void printBlank(int size);
void printWithBlank(int size, char *error);

int main(int argc, char **argv){
  char cwd[1024];
  char str[300]={0,};

  if(argc>1){
    puts("module.js:442\n");
    printWithBlank(4, "throw err;");
    printWithBlank(4, "^");
    if(getcwd(cwd, sizeof(cwd)) != NULL)
      fprintf(stdout, "Error: Cannot find module '%s/%s'\n", cwd, argv[1]);
    else
      exit(1);

    printWithBlank(4, "at Function.Module._resolveFilename (module.js:440:15)");
    printWithBlank(4, "at Function.Module._load (module.js:388:25)");
    printWithBlank(4, "at Function.Module.runMain (module.js:575:10)");
    printWithBlank(4, "at startup (node.js:160:18)");
    printWithBlank(4, "at node.js:449:3");
  } else {
    while(1){
      printf("> ");
      scanf("%s", str);
      printf("ReferenceError: %s is not defined\n", str);
      printWithBlank(4, "at repl:1:1");
      printWithBlank(4, "at REPLServer.defaultEval (repl.js:272:27)at bound (domain.js:280:14)");
      printWithBlank(4, "at REPLServer.runBound [as eval] (domain.js:293:12)");
      printWithBlank(4, "at REPLServer.<anonymous> (repl.js:441:10)");
      printWithBlank(4, "at emitOne (events.js:101:20)");
      printWithBlank(4, "at REPLServer.emit (events.js:188:7)");
      printWithBlank(4, "at REPLServer.Interface._onLine (readline.js:224:10)");
      printWithBlank(4, "at REPLServer.Interface._line (readline.js:566:8)");
      printWithBlank(4, "at REPLServer.Interface._ttyWrite (readline.js:843:14)");
      memset(str, 0, sizeof(str));
    }
  }
  return 0;
}

void printBlank(int size){
    for(int i=0; i<size; i++){
        printf(" ");
    }
}

void printWithBlank(int size, char *error){
  printBlank(size);
  printf("%s\n", error);
}
