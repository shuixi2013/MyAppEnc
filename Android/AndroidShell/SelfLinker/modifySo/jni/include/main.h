#include "Mstruct.h"
#include "elf32.h"
#include "utils.h"

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MYSECTION __attribute__((section (".vmp")))

#ifndef NELEM
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

void ShellInit(void) __attribute__ ((constructor)) ;
