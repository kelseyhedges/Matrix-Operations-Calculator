# Matrix-Operations-Calculator
This program functions as a calculator for matrix addition and multiplication.

Dimensions for Matrix A and B are supplied by the user and adjusted automatically by the program to ensure that the selected operation
(addition or multiplication) can be done with the given dimensions. For example, when addition is selected, any changes to the 
dimensions of Matrix A will be applied to Matrix B as well and vice versa. When multiplication is selected, changes to the column value of Matrix A will be applied to the row value of Matrix B; changes to the row value of Matrix B will apply to the column value of Matrix A as well.

The calculator can operate on double type values and will print an error message to the GUI if an inputted element connot be converted
to a double. 

(GUI build using Qt Creator; written in C++)
