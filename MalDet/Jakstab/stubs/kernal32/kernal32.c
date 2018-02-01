#include <stdio.h>
#include <stdlib.h>

__declspec (dllexport) long __stdcall GetVersion(void)
{
  return 1;
}

