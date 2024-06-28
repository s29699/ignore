#include"header.h"

int main()
{
	int array[MAX];
	int i,n;	
        int choice;

	printf("\n\nEnter no of numbers you want to enter:");
	scanf("%d",&n);
	printf("\nEnter elements:\n");
	
	for(i=0; i < n; i++)
	{
	   scanf("%d", &array[i]);
	}


	printf("\nElements Before sorting :\n");
	for(i=0;i<n;i++)
	{
	   printf("%4d\n",array[i]);
	}

        printf("\n Please enter your choice of sorting technique:");
        printf("\n 1. Insertion Sort");
        printf("\n 2. Quick Sort");
        printf("\n 3. Merge Sort\n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                     insertion_sort(array, n);
                     break;
            case 2:
                     quick_sort(array, 0, n-1);
                     break;
            case 3:
                     merge_sort(array, 0, n-1);
                     break;
        }


	printf("\n\nelements After sorting :\n");
	for(i=0; i < n; i++)
	{
		printf("%4d\n", array[i]);
	}

	printf("\n");
	return EXIT_SUCCESS;
}

