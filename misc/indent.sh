#!/bin/sh
#

# OpenBSD style - https://man.openbsd.org/style
INDENT_ARGS="-bap -br -ce -ci4 -cli0 -d0 -di0 -i8 -ip -l79 -nbc -ncdb -ndj -ei -nfc1 -nlp -npcs -psl -sc -sob -nv"

find . -name "*.h" -exec indent $INDENT_ARGS {} \;
find . -name "*.c" -exec indent $INDENT_ARGS {} \;

