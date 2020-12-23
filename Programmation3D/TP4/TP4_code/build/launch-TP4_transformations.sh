#!/bin/sh
bindir=$(pwd)
cd /home/saffin/Bureau/Modelisation3D/TP4_code/TP4_transformations/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/saffin/Bureau/Modelisation3D/TP4_code/build/TP4_transformations 
	else
		"/home/saffin/Bureau/Modelisation3D/TP4_code/build/TP4_transformations"  
	fi
else
	"/home/saffin/Bureau/Modelisation3D/TP4_code/build/TP4_transformations"  
fi
