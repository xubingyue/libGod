#!/bin/bash

PROG_DIR=`dirname ${BASH_SOURCE[0]}`

ASM_DIR="$PROG_DIR/asm"

echo $PROG_DIR
echo $ASM_DIR

sed -i "s/jump_fcontext/god_swap_context/g" `grep "jump_fcontext" -rl $ASM_DIR`
sed -i "s/make_fcontext/god_make_context/g" `grep "make_fcontext" -rl $ASM_DIR`
