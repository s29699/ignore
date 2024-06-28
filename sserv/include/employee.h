// employee.h
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include "utils.h"

extern char employeeIDs[MAXEMPLOYEES][20];
extern int empSize;

void loadEmployeeIDs();

int validateEmployeeID(char *employeeID);

#endif /* EMPLOYEE_H */

