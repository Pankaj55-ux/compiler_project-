# Multi-File Mini Compiler using Flex & Bison

A custom mini compiler for a subset of the C language built using Flex, Bison, React, and Node.js.

---

# Features

- Lexical Analysis using Flex
- Syntax Analysis using Bison
- AST Generation
- Symbol Table Management
- Semantic Analysis
- Scope Handling
- Multi-file Linking
- Three Address Code (TAC) Generation
- Constant Folding Optimization
- Dead Code Elimination
- React + Monaco Editor UI
- Node.js Backend Integration

---

# Technologies Used

- C
- Flex
- Bison
- GCC
- Node.js
- Express.js
- React.js
- Monaco Editor

---

# Project Structure

```txt
compiler-project/
│
├── lexer/
├── parser/
├── ast/
├── tac/
├── symboltable/
├── input/
├── backend/
├── frontend/
│
├── compiler.exe
├── AST.txt
├── TAC.txt
├── SymbolTable.txt






How To Run The Project
STEP 1 — Open Project

Open the complete compiler-project folder in VS Code.

STEP 2 — Compile Lexer and Parser

Open VS Code terminal and run these commands one by one:

cd parser
bison -d parser.y
cd ../lexer
flex lexer.l
cd ..
STEP 3 — Build Compiler

Run:

gcc lexer/lex.yy.c parser/parser.tab.c ast/ast.c symboltable/symboltable.c tac/tac.c main.c -o compiler.exe

This creates:

compiler.exe
STEP 4 — Run Compiler

Run:

.\compiler.exe input/file1.c

Compiler generates:

AST.txt
TAC.txt
SymbolTable.txt
Run Backend

Open NEW terminal.

Run:

cd backend

Install packages (first time only):

npm install

Start backend:

node server.js

Expected output:

SERVER RUNNING ON PORT 5000
Run Frontend

Open another NEW terminal.

Run:

cd frontend

Install packages (first time only):

npm install

Start frontend:

npm start

Browser opens automatically:

http://localhost:3000
How To Test

Edit:

input/file1.c

Example:

int a;
int b;
int c;

a = b + c;

Save file.

Then:

refresh webpage
click COMPILE button

Compiler outputs will appear:

AST
Symbol Table
TAC


# EXAMPLES

Arithmetic Example
int a;
int b;
int c;

a = b + c;


If Statement Example
int a;
int b;

if(a<b)
{
a=b;
}


While Loop Example
int a;
int b;

while(a<b)
{
a=b;
}


For Loop Example
int i;
int a;
int b;

for(i=0;i<10;i=i+1)
{
a=b;
}



