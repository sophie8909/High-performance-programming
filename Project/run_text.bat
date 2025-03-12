@echo off
echo Running Sudoku Solver for all input files...

REM Loop over all .dat files inside input folder
for %%f in (input\*.dat) do (
    echo Processing %%f ...
    sudoku.exe %%f
    echo.
)

echo All files processed.
pause
