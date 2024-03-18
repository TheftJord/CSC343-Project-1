/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: student
 *
 * Created on February 26, 2023, 1:04 PM
 */

#include "processManagement.h"
#include "processTestCode.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    if (0 != processTestOne()) {
        fprintf(stderr,"Failure in process test one");
        exit (EXIT_FAILURE);
    }
    if (0 != processTestTwo()) {
        fprintf(stderr,"Failure in process test two");
        exit (EXIT_FAILURE);
    }
    if (0 != processTestThree()) {
        fprintf(stderr,"Failure in process test three");
        exit (EXIT_FAILURE);
    }
    printf("Tests Succeeded");
    return (EXIT_SUCCESS);
}



