/****************************************************************************
 * *
 * FILE NAME:     header.h
 * 
 * DESCRIPTION:   all declarations of the function for various sorting tech
 *
 * DATE           NAME            REFERENCE       REASON
 * -----------------------------------------------------------
 *Copyrights 2015 Aricent Technolegies (Holdings) ltd
 *
 ***************************************************************************/

/***************************************************************************
 *			Header Files					   *
 ***************************************************************************/

#include<stdio.h>
#include<stdlib.h>
 
#define MAX 30
#define SUCCESS 1
#define FAILURE 0


int insertion_sort(int *,int);
void quick_sort(int *,int, int);
void merge_sort(int *,int, int);

