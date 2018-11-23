#include <stdio.h>
#include <string.h>
#include <string.h> 
const char *str0 = "magicvalue";
const char *str1 = "magic value is missing\n";
const char *str2 = "magicvalue is given\n";
const char program_text[] = {('\xAB'), ('\xAB'), ('\xAB'), ('\xAB'), ('\xAB'), ('\xAB'), ('\xAB'), ('\xAB'), (0x03), (0x02), ('\x04'), ('\x00'), ('\x00'), ('\x00'), ('\xAB'), ('\xAB'), ('\xAB'), ('\xAB'), (0x05), (0x0D), (0x08), ('\xF5'), ('\xFF'), ('\xFF'), ('\xFF'), (0x06), (0x05), (0x10), (0x0C), (0x09), ('\xDE'), ('\xFF'), ('\xFF'), ('\xFF'), (0x02), ('\x01'), ('\x00'), ('\x00'), ('\x00'), (0x11), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), (0x02), ('\x00'), ('\x00'), ('\x00'), ('\x00'), (0x03), (0x01), (0x15), (0x08), ('\xD1'), ('\xFF'), ('\xFF'), ('\xFF'), (0x02), ('\x00'), ('\x00'), ('\x00'), ('\x00'), (0x02), ('\x10'), ('\x00'), ('\x00'), ('\x00'), (0x0F), (0x11), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), (0x03), (0x02), ('\x0A'), ('\x00'), ('\x00'), ('\x00'), (0x0F), (0x11), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), ('\xFF'), (0x00), (0x02), ('\x00'), ('\x00'), ('\x00'), ('\x00')};
char program[sizeof(program_text)];

const char *init_program(int *argcptr,char *argv[])
{
  memcpy(program,program_text,sizeof(program_text));
   *((void **)(&program[0])) = argv;
   *((const char **)(&program[40])) = str0;
   *((const char **)(&program[73])) = str1;
   *((const char **)(&program[89])) = str2;
  return program;
}
