@ECHO OFF

IF "%1" == "" (
  GOTO ABORT
)

SET time="%1"

:RUN
  CALL python3 ./src/main.py %time%
  GOTO END

:ABORT
  ECHO ������ �ð��� �Է����ּ���~!
  ECHO ����, ���� 8�� ������ �����ϰ� ������ �Ʒ��� ���� �Է����ּ���.
  ECHO main.bat 20

:END
  EXIT /b 0