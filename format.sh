#!/bin/sh

if ! [ "$(which astyle)" ]; then
    echo "Install astyle first!"
    exit
fi

astyle \
--mode=c \
--style=google \
--indent=force-tab \
--attach-namespaces \
--attach-classes \
--attach-inlines \
--indent-col1-comments \
--pad-header \
--unpad-paren \
--align-pointer=type \
--fill-empty-lines \
--recursive \
--suffix=none *.c *.cpp *.h *.hpp
