@echo off

for %%i in (10, 20, 50, 100) do (
  for %%j in (1, 2, 3, 4, 5) do (
    generator.exe %%i %%j > ./data/test_%%i_%%j
  )
)
