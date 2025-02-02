
/************************************************************************
* Programmer:Ruben Ramirez
*
* Course:  CSCI 1320.03
*
* Date: April 28, 2016
*
* Assignment Number | Keyword : 21 | 1040ez
*
* Point Value :  400
*
* Environment: visual studio 2013
*
* Files Included: output.txt
*
* Purpose: to print input file for form 1040ez
*
* Input:data.txt
*
* Preconditions:none
*
* Output: name, address, and tax information
*
* Postconditions:none
*
* Algorithm: while loop to read file and print user tax info
*
*
* Errors:
*
* Example: Show an example in terms of input and output (if appropriate)
*
* History:re-used code from structure program
***********************************************************************/

#include <stdio.h>   // printf
#include <string.h>  // strtok, strcpy
#include <stdlib.h>  // atof, atoi


typedef struct
{
	unsigned long int social;   // Simulated social #
	unsigned long int income;  // users income
	unsigned short int taxInterest;  // users taxable interest
	unsigned long int unemployment;  // users unemployment compensation
	unsigned long int withheld;  // income tax withheld
	unsigned long int account;   // users bank account number
	unsigned long int routing;  // user bank routing number

	double price;    // Price of one of this item
	char lastName[20];  // users last name
	char firstName[30]; // users first name
	char street[40];  // users street address
	char location[100];  //  users city state zip
}  TAX;




// Student writes two function prototypes here


int earnedCredit(int earnings);


int taxTable(int earnings);



// Definition code re-use - for reading the files
#define MAX_LINE 1023



int main(int argc, char * argv[])
{

	FILE * input;
	FILE * output;

	output = fopen("54_1040ez_Ruben_Ramirez.txt", "w");


	int gross;  // adjusted gross income line 4

	int EIC;  // line 8a. earned income credit calculated by earnedCredit function

	int credits;  // line 9. total payments and credits

	int taxable;  // line 10. tax of gross calculated by function taxTable

	int totalTax;  // line 12. tax due

	int taxOwed;  // tax due if line 12 > line 9


	char aLine[MAX_LINE];  // Needed for scanf - BUT NOT USED

	char * curStr; // pointer to the current string


	TAX  aPerson;  // One person




	// student writes required number keyword and name


	printf("54_1040ez_Ruben_Ramirez\n\n");
	fprintf(output, "54_1040ez_Ruben_Ramirez\n\n");


	// check if input file was declared

	if (argc < 2)
	{
		printf("\nOperator ERROR this program expects a file to read\n Exiting ...\n\n");
		return 1;
	}

	input = fopen(argv[1], "r");

	// check if input file can be found

	if (input == NULL)
	{
		printf("\nUnable to open file: %s\n", argv[1]);
		printf("Either the spelling does not match the filename or the file is in a different directory\n\n");
		return 2;
	}

	while (fgets(aLine, sizeof(aLine), input))
	{
		// parse of data for individual tax information


		/*******************************************

		USER IDENTIFICATION INFORMATION

		***********************************************/

		curStr = strtok(aLine, ",");

		strcpy(aPerson.firstName, curStr);  // first name

		curStr = strtok(NULL, ",");

		strcpy(aPerson.lastName, curStr);  // last name

		curStr = strtok(NULL, ",");

		aPerson.social = atoi(curStr);  // social #

		curStr = strtok(NULL, ",");

		strcpy(aPerson.street, curStr);  // users street address

		curStr = strtok(NULL, ",");

		strcpy(aPerson.location, curStr);  // users city state zip

		curStr = strtok(NULL, ",");


		// print statement of output for user identification information


		printf("%s %s \t%i\n%s\n%s\n", aPerson.firstName, aPerson.lastName, aPerson.social, aPerson.street, aPerson.location);

		fprintf(output, "%s %s \t%i\n%s\n%s\n", aPerson.firstName, aPerson.lastName, aPerson.social, aPerson.street, aPerson.location); // to output file


		/******************************************
		INCOME

		*********************************************/

		aPerson.income = atoi(curStr);  //line 1. users income

		curStr = strtok(NULL, ",");

		aPerson.taxInterest = atoi(curStr); //line 2. users taxable interest

		curStr = strtok(NULL, ",");

		// line 3. unemployment

		aPerson.unemployment = atoi(curStr);

		curStr = strtok(NULL, ",");

		// line 4. adjusted gross income = line 1 + line 2 + line 3

		gross = aPerson.income + aPerson.taxInterest + aPerson.unemployment;

		// line 5. dependent = 0

		// line 6. taxable income = gross


		

		// lines 1 - 6
		printf("1. Income \t\t%i\n2. Interest \t\t%i\n3. Unemployment \t%i\n4. Gross income \t%i\n5. Dependents \t\t0\n6. taxable income \t%i\n", aPerson.income, aPerson.taxInterest, aPerson.unemployment, gross, gross);

		fprintf(output, "1. Income \t\t%i\n2. Interest \t\t%i\n3. Unemployment \t%i\n4. Gross income \t%i\n5. Dependents \t\t0\n6. taxable income \t%i\n", aPerson.income, aPerson.taxInterest, aPerson.unemployment, gross, gross);  // to output file



		/********************************************************************

		PAYMENTS, CREDITS, AND TAX


		*******************************************************************/

		// line 7.

		aPerson.withheld = atoi(curStr);

		curStr = strtok(NULL, ",");

		// line 8a.  earned income credit calcuated by function earnedCredit

		EIC = earnedCredit(gross);

		// line 9. total payments and credits = line 7 + line 8a

		credits = aPerson.withheld + EIC;

		// line 10. tax calculated by function taxtable

		taxable = taxTable(gross);

		// line 11. health care = 0

		// line 12. total tax = line 10 + line 11

		totalTax = taxable;

		

	
		// lines 7 - 12
		printf("7. Withholding \t\t%i\n8a. EIC \t\t%i\n9. Credits \t\t%i\n10. Tax \t\t%i\n11. Healthcare \t\t0\n12. Total tax \t\t%i\n", aPerson.withheld, EIC, credits, taxable, totalTax);

		fprintf(output, "7. Withholding \t\t%i\n8a. EIC \t\t%i\n9. Credits \t\t%i\n10. Tax \t\t%i\n11. Healthcare \t\t0\n12. Total tax \t\t%i\n", aPerson.withheld, EIC, credits, taxable, totalTax); // to output file



		// line 13b. routing number

		aPerson.routing = atoi(curStr);

		curStr = strtok(NULL, ",");

		// line 13d. account number

		aPerson.account = atoi(curStr);

		curStr = strtok(NULL, ",");


		

		// line 14. tax owed if line 12 > line 9


		if (totalTax > credits)
		{
			taxOwed = totalTax - credits;
			
			// line 13 bank info
			
			printf("13a. Refund \t\t0\n");
			fprintf(output, "13a. Refund \t\t0\n");
			
			printf("13b. Routing number \t%i\n13d. Account number \t%i\n", aPerson.routing, aPerson.account);

			fprintf(output, "13b. Routing number \t%i\n13d. Account number \t%i\n", aPerson.routing, aPerson.account);
			
			printf("14. Tax due \t\t%i\n",taxOwed);
			fprintf(output,"14. Tax due \t\t%i\n", taxOwed);
		}

		else
		{

			
			
			// line 13 bank info
			
			
			taxOwed = credits - totalTax;
			printf("13a. Refund \t\t%i\n", taxOwed);
			fprintf(output,"13a. Refund \t\t%i\n", taxOwed);
			
			
			
			printf("13b. Routing number \t%i\n13d. Account number \t%i\n", aPerson.routing, aPerson.account);

			fprintf(output, "13b. Routing number \t%i\n13d. Account number \t%i\n", aPerson.routing, aPerson.account);
			
			taxOwed = 0;

			printf("14. Tax due \t\t%i\n", taxOwed);
			fprintf(output, "14. Tax due \t\t%i\n", taxOwed);

			
		}




		// print statement for designee signature

		printf("Designee: Ruben Ramirez\tPhone no.: 123-456-7854\n\n");

		fprintf(output, "Designee: Ruben Ramirez\tPhone no.: 123-456-7854\n\n");

		// print statement for user signature

		printf("Your signature: %s %s\n\n", aPerson.firstName, aPerson.lastName);

		fprintf(output, "Your signature: %s %s\n\n", aPerson.firstName, aPerson.lastName);


	}  // end of while read file


	/*

	int ii;  // Used to simulate incomes
	int ei;
	int tx;

	for (ii = 0; ii < 21000; ii += 50)  // increase by 50 dollars so not too many prints
	{
	ei = earnedCredit(ii);
	tx = taxTable(ii);
	printf("%i,%i,%i\n", ii, ei, tx);
	}

	*/


	fclose(input); // close input file
	fclose(output); // close output file
	return 0;
}  // end of main



/************************************************************************
* Purpose:  To emulate the Earned Income Tax Table from the IRS for 1040EZ
*
* Parameters: The earnings of a person
*
* Action:  Match the earnings to the approximate Earned Income Credit
*          table from the IRS using piecewise linear functions
*
*    The results are within about a single dollar of the actual IRS table
*
* Author: Neil Miserendino 4/21/2016
***********************************************************************/
int earnedCredit(int earnings)
{
	double credit;

	if (earnings < 6550)  // credit increases for each dollar earned
	{
		credit = .0765 * earnings + 1.925; //  earnings < 6550
		if (credit < 0)
		{
			credit = 1;  // arbitrary number that is not zero  (you will get a credit of 1 with 0 earnings)
		}
	}
	else
	{
		if (earnings < 8250)  // Maximum credit range here
		{
			credit = 503;          // X < 8250
		}
		else
		{
			if (earnings < 14850)  // credit declines
			{
				credit = -.0765  * earnings + 1131.8;  //  earnings < 15000
			}
			else   // earn too much no earned income credit 
			{
				credit = 0;  //  X >= 15000
			}   // end else no credit
		}       // end else NOT maximum credit
	}           // end else credit increases for each dollar earned


	return ((int)credit);  // truncate the cents - you may chage to round
}  // end of function earnedCredit


/************************************************************************
* Purpose:  To emulate the Income Tax Due Table from the IRS for 1040EZ
*
* Parameters: The earnings of a person
*
* Action:  Match the earnings to the approximate Income Tax Due
*          table from the IRS using piecewise linear functions
*
*    The results are within about a single dollar of the actual IRS table
*
* Author: Neil Miserendino 4/21/2016
***********************************************************************/
int taxTable(int earnings)
{
	double tax;

	if (earnings < 3000)
	{    // tax will be $1 with 0 earnings
		tax = .1 * earnings + 1.2; //    earnings < 3000
	}
	else
	{

		if (earnings < 9500)
		{
			tax = .1  * earnings + 1.73;     //  earnings < 9500
		}
		else
		{
			tax = .15 * earnings - 457.23; //  earnings .= 9500
		}

	}  // end else > 3000


	return ((int)tax);  // truncate the cents - you may chage to round
}   // end of function taxTable