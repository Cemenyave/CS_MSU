@echo off

for %%i in (10, 20, 50, 100) do (
  for %%j in (1, 2, 3, 4, 5) do (
    sorting.exe %1 < ./data/test_%%i_%%j
  )
)
