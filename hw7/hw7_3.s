######################################################################
# SPIM source file for homework 7, problem 3                         #
#                                                                    #
# In SPIM, use: load "hw7_3.s"                                       #
# Then use the step command to step through instructions.            #
#                                                                    #
# The actual code in the homework is a portion of the code in this   #
# file.  You can modify this source file and check with SPIM that    #
# behavior is unchanged.  However, you must start SPIM with:         #
#                                                                    #
#     spim -delayed_branches -delayed_loads                          #
#                                                                    #
######################################################################
	.data
args:	.word   0x00000001	# Change to zero to branch
	.word   0x00000000
	.word   0x00000000
	.word   0x00000000
	.text
	.globl main
main:
	la   $a0,args		# Load base address
	lw   $t0,12($a0)
	nop
	
	# Start of code in homework problem
label0:	beq  $t0,$zero,label9
label1:	nop
label2:	lw   $t1,0($a0)
label3:	lw   $t2,4($a0)
label4:	nop
label5:	add  $t0,$t1,$t2
label6:	lw   $t3,8($a0)
label7:	nop
label8:	add  $t0,$t0,$t3
label9:	sw   $t0,8($a0)
	# End of code in homework problem

	jr   $ra
	nop

