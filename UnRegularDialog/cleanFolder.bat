for /f %%i in ('dir /a:d /b') do ( rd %%i\Debug /s /q
rd %%i\Release /s /q )