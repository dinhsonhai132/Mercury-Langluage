this is README for test
# MercuryLang *version 2.0.1 binary* is out! ✨
## What's in this update? 👀

## 1) New Compiler called Mercury Virtual Machine (MVM) 💻
### What's is MVM? 
* MVM is a compiler that compile low level programing language make for execute Mercury codes 
### What MVM can do? 
* MVM can do a basic codes like what a basic low level programing language can do for example:
```MVM
PROGRAM_START
PUSH_FLOAT 1.000000
PUSH_FLOAT 1.000000
BINARY_ADD
PROGRAM_END
```
* That code is the compiled code of:
``` MercuryLang
1+1
```
### Why use MVM? 
* Using MVM to execute code is faster and easier to manage the code 
* By not straight code from AST to value can not cause a lot of error when new version update or small mistake run code 
## 2) How to compile code into MVM code? ♻
* s1: Install the language if you are not install go to the offical page for more info
* s2: Make a ```.mer``` file and write code into it
* s3: Open cmd, go to your file path and type ```./shell.exe main.mer```
* s5: When done the MVM will automaticly compiled your ```.mer``` file into ```.merc``` file, that file will be your bytecode
* s6: If you want to execute code type ```./exec.exe main.merc``` and it will show the output

**And that are all the feature that the 2.0.1 MercuryLang has, have fun coding 😆**
