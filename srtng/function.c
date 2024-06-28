#include "header.h"

static void merge(int *, int, int, int, int);
static int partition(int *, int, int);

int insertion_sort(int *array, int n)
{
	int i,temp,j;

	for(i=1;i<n;i++)		//loop for n-1 passes
	{
		temp = array[i];
		j = i-1;
	
		//inserting i th element into sorted port of the array

		while((temp<array[j])&&(j>=0))	// Find place to insert
		{
		    array[j+1]=array[j];
	   	    j = j-1;
		}
		
		array[j+1]=temp;
	}

	return SUCCESS;
}


void quick_sort(int *array, int BEG, int END)
{
	int p;

	if(BEG < END) /* check at least two elements in list */
	{
	    p = partition(array, BEG, END); //return the position of pivot
	    quick_sort(array, BEG, p-1);
	    quick_sort(array, p+1, END);
	}	
}

static int partition(int *array,  int BEG,  int END)    
{
	int LEFT, RIGHT, LOC, temp;

	LEFT = BEG;
	RIGHT = END;
	LOC = BEG;

	while(LEFT<=RIGHT)
	{
		while((array[RIGHT] >= array[LOC]) &&  (LOC != RIGHT))			
		{
		   RIGHT = RIGHT - 1;
		}
		
		if(LOC == RIGHT)
		{
		   return LOC;
		}
		else
		{
		   temp = array[LOC];
		   array[LOC]=array[RIGHT];
		   array[RIGHT]=temp;
		   LOC = RIGHT;
		}
	
		while((array[LEFT] <= array[LOC]) &&(LOC != LEFT))
		{
		   LEFT = LEFT + 1;
		}
		
		if(LOC == LEFT)
		{
		   return LOC;
		}
		else
		{
		   temp = array[LOC];
		   array[LOC]=array[LEFT];
		   array[LEFT]=temp;
		   LOC = LEFT;
		}
	}

	return LOC;
}


void merge_sort(int *array, int BEG, int END)
{
	int MID;

	if(BEG < END) 
	{
		MID = (BEG + END)/2;
		merge_sort(array, BEG, MID);
		merge_sort(array, MID+1, END);
		merge(array, BEG, MID, MID+1, END);
	}
}


static void merge(int *array, int LB1,  int UB1,  int LB2,  int UB2)   {
	int c[MAX]; 
	int i;
	int j, k;

	i = LB1;
	j = LB2;

	k=0;

	while((i <= UB1) &&   (j <= UB2))
	{
	   if(array[i] < array[j])
	   {
		c[k] = array[i];
		i++;
		k++;
 	   }
	   else
	   {
		c[k] = array[j];
		j++;
		k++;
	   }
	}
	
	while(i <= UB1)
	{
	   c[k] = array[i];
	   k++;
	   i++;
	}
	
	while(j <= UB2)
	{
	   c[k] = array[j];
	   k++;
	   j++;
	}

	i = LB1;
	k = 0;

	while(i <= UB2)
	{
	   array[i] = c[k];
	   i++;
	   k++;
	}
}

