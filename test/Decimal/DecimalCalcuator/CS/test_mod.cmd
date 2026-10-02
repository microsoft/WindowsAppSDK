@ECHO OFF
SETLOCAL

SET C=DecimalCalculator_CS.exe


%C% mod  1       2       1
%C% mod  123     4567    123
%C% mod  1       -2      1
%C% mod  -1      -2      -1
%C% mod  -1      2       -1
%C% mod  1.2     3.45    1.2
%C% mod  -1.2    3.45    -1.2
%C% mod  1.2     -3.45   1.2
%C% mod  -1.2    -3.45   -1.2
%C% mod  .2      .45     0.2
%C% mod  -.2     .45     -0.2
%C% mod  .2      -.45    0.2
%C% mod  -.2     -.45    -0.2
%C% mod  2       1       0
%C% mod  4567    123     16
%C% mod  3.45    1.2     1.05
%C% mod  2       -1      0
%C% mod  -2      1       0
%C% mod  -2      -1      0
%C% mod  3.45    -1.2    1.05
%C% mod  -3.45   1.2     -1.05
%C% mod  -3.45   -1.2    -1.05
%C% mod  .45     .2      0.05
%C% mod  .45     -.2     0.05
%C% mod  -.45    .2      -0.05
%C% mod  -.45    -.2     -0.05

:TheEnd
ENDLOCAL
