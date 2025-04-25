/* Josephine Ekenya*/

#include <stdio.h>
#include <math.h>
#define MAX_ARRAY_LENGTH 200 /* the maximum number of assignments is 50, 
thus save space for 200 array items. */
#define INFO_NUM 4 /* there'll be 4 information per assignment */
#define MAX_INT 2147483647 /* initialized to maximum int value for comparison*/

int create_array(int num_of_assignments, int assignment_info[]);
int print_assignment_info(int assignment_info[], int num_of_assignments,
int cur_length);
double compute_mean(int penalty_per_day, int num_of_assignments, int cur_length, 
int assignment_info[]);
double compute_std(double mean, int num_of_assignments, int cur_length,
int penalty_per_day, 
int assignment_info[]);

double compute_grade(int cur_length, int penalty_per_day, int drop_n_lower_assignments, 
int assignment_info[]);
int check_dropped_assignment(int num, int dropped_assignments[], int dropped_count);
void find_lowest_valued(int lowest_score_arr[], int assignment_info[], int cur_length,
int *dropped_arr_length); /*this basically just adds the lowest valued assignment into 
an array*/

/*This code reads input for penalty per day, the number of assignments to drop, 
and whether to compute statistical information (mean and standard deviation). 
It then reads the number of assignments and populates an array with assignment 
details. If the array is successfully created and conditions are met, 
it computes and displays the numeric score based on the given assignments, 
penalties, and the number of assignments to drop. It also prints details 
of the assignments. If the user has indicated ('y' or 'Y'), it computes 
and displays the mean and standard deviation of the scores.*/
int main(){
    int penalty_per_day, drop_n_lower_assignments, num_of_assignments, cur_length, 
    terminate;
    int assignment_info[MAX_ARRAY_LENGTH];
    double score, mean, std_dev; 
    char stats;

    scanf("%d %d %c", &penalty_per_day, &drop_n_lower_assignments, &stats);
    scanf("%d", &num_of_assignments);
    cur_length = num_of_assignments * INFO_NUM; /* this will be the actual used length of 
    the array we are
    working with instead of the max 200 */

    /* Pass all the information to a method that will create the array */
    terminate = create_array(num_of_assignments, assignment_info);
    /* if the array was created and the sum of the weight of assignments is 100, do the next 
    computation*/
    if (terminate != 0){
        /* compute grade */
        score = compute_grade(cur_length, penalty_per_day, drop_n_lower_assignments, 
        assignment_info);
        printf("Numeric Score: %5.4f\n", score);
        printf("Points Penalty Per Day Late: %d\n", penalty_per_day);
        printf("Number of Assignments Dropped: %d\n", drop_n_lower_assignments);

        /* print the assignment information*/
        printf("Values Provided:\n");
        printf("Assignment, Score, Weight, Days Late\n"); 
        print_assignment_info(assignment_info, num_of_assignments, cur_length);
        if (stats == 'y' || stats == 'Y'){
            mean = compute_mean(penalty_per_day, num_of_assignments, cur_length,
            assignment_info);
            std_dev = compute_std(mean, num_of_assignments, cur_length, penalty_per_day, 
            assignment_info);
            printf("Mean:  %5.4f, Standard Deviation: %5.4f\n", mean, std_dev);
        }
    }
    return 0;
}

/* This code creates a 1d array that will be used to store information 
about assignments. It takes in inputs related to assignment infomation such as
number, grade weight..etc. It also computes the total weight of all assignments
ensuring that they add up to 100. If weight do not add up to 100, it terminates
the program, displaying an error message.*/
int create_array(int num_of_assignments, int assignment_info[]){
     int arr_in = 0;
     int n_info = 0;
     int weight_sum = 0;
    /*get assignment information n (num_of_assignments) times and and add to the array*/
    /* assignment information will be read in the following order, assignment number, 
    student's score, weight, and days late*/
    while (n_info < num_of_assignments){
        scanf("%d, %d, %d, %d", &assignment_info[arr_in], &assignment_info[arr_in + 1], 
        &assignment_info[arr_in + 2], &assignment_info[arr_in + 3]); 
        weight_sum += assignment_info[arr_in + 2]; /* add the weight of the assignment_info */

        arr_in += INFO_NUM; /*increment the array initializer to represent the next set of values*/
        n_info += 1; /* get the next assignment information*/
    }

    if (weight_sum != 100){
        printf("ERROR: Invalid values provided");
        return 0;
    }
    return 1; 
}

/*This code iterates through an array containing information for a number of assignments, 
and prints out the details for each assignment in order from least to greatest.
*/
int print_assignment_info(int assignment_info[], int num_of_assignments,
int cur_length){
    int i, j, assignment_num, weight, score, days_late;
    /*Print a line for each assignment information*/
    for (i = 0; i < num_of_assignments; i++) {
        for (j = 0; j < cur_length; j += 4) {
            if (assignment_info[j] % num_of_assignments == 0) { /* check if the 
            assignment is the 
            last assignment */
                assignment_num = assignment_info[j];
                score = assignment_info[j + 1];
                weight = assignment_info[j+2];
                days_late = assignment_info[j + 3];
            }else if (assignment_info[j] % num_of_assignments == i) { /* check if 
            the assignment number 
            is equal to the number format */
                printf("%d, %d, %d, %d\n", assignment_info[j], assignment_info[j + 1], 
                assignment_info[j + 2], 
                assignment_info[j + 3]);
            }
        }
    }
    printf("%d, %d, %d, %d\n", assignment_num, score, weight, days_late);

    return 0;
}

/* This code computes the mean of an assignment making use of the late penalty, and number of assignmenst.*/
double compute_mean(int penalty_per_day, int num_of_assignments, int cur_length, 
int assignment_info[]){
    double mean = 0.0;
    double total_score = 0.0;
    int j;

    /*get the mean of all assignments*/
    for (j = 0; j < cur_length; j += INFO_NUM) {
            int late = assignment_info[j + 3] * penalty_per_day;
            int grade = assignment_info[j + 1] - late;
            total_score += grade;
        }

    mean = total_score / num_of_assignments;

    return mean;
}

/* Similar to the compute mean function, this code computes the standard dewviation of all assignments.*/
double compute_std(double mean, int num_of_assignments, int cur_length, 
int penalty_per_day, 
int assignment_info[]){
    double sum_of_diff = 0.0;
    double variance, std;
    int j;
    /*get the standard deviation of all assignments*/
    for (j = 0; j < cur_length; j += INFO_NUM){
            int late = assignment_info[j + 3] * penalty_per_day;
            int grade = assignment_info[j+1] - late;
            sum_of_diff += pow((grade - mean), 2); 
    }

    variance = sum_of_diff / num_of_assignments;
    std = sqrt(variance); 

    return std;
}

/* This code calculates the overall grade for a set of assignments after applying penalties 
for late submissions and optionally dropping the lowest-valued assignments as specified. 
It iterates through the assignment information, excludes the specified number of lowest-valued 
assignments, and then computes the total score by applying late penalties and weighting each assignment's grade. 
The final grade is the weighted average of the included assignments, ensuring there's no division 
by zero if the total weight is zero.*/
double compute_grade(int cur_length, int penalty_per_day, int drop_n_lower_assignments, 
int assignment_info[]){
    double score = 0.0;
    int j, i, grade, weight, late_penalty, num;
    int dropped_arr_length = 0; /*the length of the dropped assignment
    array drop based on how many assignments should be dropped times the number of 
    information 
    about the assignment*/
    int dropped_assignments[MAX_ARRAY_LENGTH];
    int *p = &dropped_arr_length; /*using a reference so we can update the value*/
    int total_weight = 0;

    i = 0;
    /* Drop the specified number of lowest-valued assignments 
    by adding courses that need to be dropped in the drop array*/
    for(i = 0; i < drop_n_lower_assignments; i++){
        find_lowest_valued(dropped_assignments, assignment_info, cur_length, p);
    }



     for (j = 0; j < cur_length; j += INFO_NUM) {
            num = assignment_info[j];
            /*check if the assignement is a dropped assignment. only compute grade f
            or the assignment if 
            it isnt a droped assignment*/
            if (check_dropped_assignment(num, dropped_assignments, *p) == 0){
                /*do grade calculation based on dropped assignment*/
                grade = assignment_info[j + 1];
                weight = assignment_info[j + 2];
                late_penalty = assignment_info[j + 3] * penalty_per_day;
                grade = grade - late_penalty;
                total_weight += weight; /*updating weight*/
                /* An assignment score will be set to 0 if the assignment’s score 
                becomes less than 0 
                after the late penalty is applied*/
                if (grade < 0){
                    grade = 0;
                }
                /*multiply the grade by its weight and add to total score*/
                score += grade * weight;
            }
        }
        if(total_weight > 0){
        score /= total_weight;
    } else {
        score = 0.0; /* this handles the case where total_weight is 0 to avoid 
        division by zero */
    }

    return score;
}

/*This checks the list of dropped assignment to see if the assignment info
 being passed in 
has already been dropped*/
int check_dropped_assignment(int num, int dropped_assignments[], int arr_length){
    int i; 

    for (i = 0; i < arr_length; i += 1 ){
        if(num == dropped_assignments[i]){
            return 1; /* indicates that assignment was dropped */
        }
    }
    return 0; /* assignment was not dropped */
}

/*this basically just adds the lowest valued assignment into an array*/
void find_lowest_valued(int drop_arr[], int assignment_info[], int cur_length, 
int *dropped_arr_length){
    int i, value, num;
    int min_value = MAX_INT; /* initialized to maximum int value for comparison*/
    int min_value_index = -1; /* used to indicate when a low value has been found*/

    for (i = 0; i < cur_length; i += INFO_NUM){
         num = assignment_info[i];
        /* if they have the same weight, check which assignment number is lower*/
        /* check that the assignment info has not already been added to the drop 
        list before adding to the drop list*/
        if (check_dropped_assignment(num, drop_arr, *dropped_arr_length) == 0){
            value = assignment_info[i + 1] * assignment_info[i + 2];
            if(value < min_value){
                min_value = value;
                min_value_index = i;
            }
        }
    }
   /* Add the lowest-valued assignment to the dropped list if one is found */
    if(min_value_index != -1){
        drop_arr[*dropped_arr_length] = assignment_info[min_value_index];
         /*update the length of the drop list*/
        *dropped_arr_length += 1;
    }
} 
