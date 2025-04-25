# C-grade-Calculator
This C program processes assignment scores to compute a student's final numeric grade and generate statistical information, based on specified criteria. It handles late penalties, weighted grading, assignment drops, and optional calculation of mean and standard deviation.

**Features**

Reads assignment data from input
Applies late penalties
Drops the lowest scoring assignments
Calculates a weighted numeric grade
Optionally computes statistical data (mean and standard deviation)
Validates assignment weights (must total 100)
Prints results in a clean, ordered format

**Input Format**
Input must follow this structure:

Points_Penalty_Per_Day_Late Drop_N_Lower_Value_Assignments Stats_Y/N
Number_of_Assignments
Assignment_Number, Score, Weight, Days_Late

**Example Input**
10 2 Y
4
2, 82, 40, 1
1, 91, 40, 0
4, 84, 10, 3
3, 73, 10, 3

**Processing Logic**
Drop Assignments: Based on score × weight (not affected by lateness).

Late Penalty: Applied after drop phase; subtract days_late × penalty from score.

Final Grade: Weighted average using adjusted scores and weights.

Stats Mode (Y/y): Computes mean and standard deviation using all assignments with penalties, but without drops or weights.

**Sample Output**

Numeric Score: 81.5000
Points Penalty Per Day Late: 10
Number of Assignments Dropped: 2
Values Provided:
Assignment, Score, Weight, Days Late
1, 91, 40, 0
2, 82, 40, 1
3, 73, 10, 3
4, 84, 10, 3
Mean: 65.0000, Standard Deviation: 18.2346

**Compilation & Execution**
To compile and run the program:
gcc grades.c -lm -o grades
./grades < input.txt

**Requirements & Restrictions**
No use of:
Structs
Global variables
2D arrays
Dynamic memory allocation
qsort function



