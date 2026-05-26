const express = require("express");

const cors = require("cors");

const fs = require("fs");

const { exec } = require("child_process");

const app = express();

app.use(cors());

app.use(express.json());

app.get("/compile", (req, res) =>
{
    exec(
        "..\\compiler.exe ..\\input\\file1.c",

        (error, stdout, stderr) =>
        {
            if(error)
            {
                return res.json({
                    error: stderr
                });
            }

            const ast =
            fs.readFileSync("../AST.txt", "utf8");

            const symbolTable =
            fs.readFileSync("../SymbolTable.txt", "utf8");

            const tac =
            fs.readFileSync("../TAC.txt", "utf8");

            res.json({
                compilerOutput: stdout,
                ast: ast,
                symbolTable: symbolTable,
                tac: tac
            });
        }
    );
});

app.listen(5000, () =>
{
    console.log("SERVER RUNNING ON PORT 5000");
});