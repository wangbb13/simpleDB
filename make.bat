@echo off
rem compile it
gcc simpleDB.c -o db
g++ -std=c++11 simpleDB.cpp -o db++
echo compile done.
echo.
pause