//Include libraries
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//Inclead Headers
#include "StandardConstants.h"
#include "Console_IO_Utility.h"
#include "File_Input_Utility.h"
#include "File_Output_Utility.h"

// global constants
const int MIN_RAND_COUNT = 1;
const int MAX_RAND_COUNT = 10;
const int MIN_RAND_LIMIT = 1;
const int MAX_RAND_LIMIT = 100000;
const int VALUES_IN_ONE_LINE = 5;

//Include prototypes
int calculateTotal(int incomeArray[], int sourceCount);
void displayResults(int sourceCount, int totalIncome);
void downloadRandomValues(char *fileName, int minValue, int maxValue);
int getRandBetween(int minLimit, int maxLimit);
void printTitle();
int uploadData(char *fileName, int incomeArray[]);

//main function
int main()
{
	//Inititalzie Variables
	char fileName[ STD_STR_LEN ];
	int incomeArray[ STD_STR_LEN ];
	int currentInteger, incomeCount, sourceCount;

	//initilization of srand
		//function: srand
	srand(time(NULL));

	//Show title
		//Function: printTitle
	printTitle();

	//Get fine name
		//Function: promptForString
	promptForString("Enter the file name for random data generation: ", fileName);

	//check if data file exists
		//function: openInputFile()
	if (openInputFile(fileName))
		{
			//close the file
			closeInputFile();
		}

	//File does not exist, create a new file and random data genertion
	else
		{
			//put random values in a file
				//Function: downloadRandomValues()
			downloadRandomValues(fileName, MIN_RAND_COUNT, MAX_RAND_COUNT);
		}

	//upload data and assign array size
		//function: uploadData()
	sourceCount = uploadData(fileName, incomeArray);

	//calculate income total sum
		//Function: calculateTotal()
	incomeCount = calculateTotal(incomeArray, sourceCount);

	//Display results
		//Function: Display Results
	displayResults(sourceCount, incomeCount);

	return 0;
}
/*
Name: calculateTotal
process: accepts the one dimensional array and total count, sums up all the
				 numbers, and returns the sum
Function input/parameters: int incomeArray[], int sourceCount
Function output/parameters: none
Function output/returned: totalIncome
Device input/file: none
Device output/monitor: none
Dependencies: None
*/
int calculateTotal(int incomeArray[], int sourceCount)
{
	int totalIncome = 0;
	int index;

	//Loop to the end array
	for ( index = 0; index < sourceCount; index++)
		{
			//Add to total count
			totalIncome += incomeArray[index];
		}

	return totalIncome;
}

/*
Name: displayResults
process: 	accepts the appropriate data and displays all the results as provided
					below ONLY if values are found in the file; if no values are found in
					the file, this function displays the error message provided below
Function input/parameters: int sourceCount, int totalIncome
Function output/parameters: none
Function output/returned: none
Device input/file: none
Device output/monitor: sourceCount, totalIncome
Dependencies: Console IO Utilities tools
*/
void displayResults(int sourceCount, int totalIncome)
{
	//Check if there are any numbers in the file
	if (totalIncome != 0)
		{
			//print source count, income count
				//function: printString(), printInteger(), printEndline()
			printEndline();
			printString("Total Sources of Income : ");
			printInteger(sourceCount);
			printEndline();
			printEndline();
			printString("Total income            : ");
			printInteger(totalIncome);
			printEndline();
			printEndline();
			printString("End Program");
			printEndline();
		}
	else
		{
			printString("\nERROR: Data file not found. Program aborted.\n");
		}

}

/*
Name: getRandBetween
process: accepts the file name and a minimum and maximum number of output values
					It then finds a random number between the two (inclusive)
					The function then opens the file, downloads that number of random
					numbers as comma-delimited (or comma-separated) values, and then
					closes the file. Note that the last value must not have a comma after
					it
Function input/parameters: char fileName, int minValue, int maxValue
Function output/parameters: Writes to file
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: File output IO Utilities tools
*/
void downloadRandomValues(char *fileName, int minValue, int maxValue)
{

	//inititalize Variables
	int randomNumberLoop, randomIncomeNumber, index;
	int numberCount = 0;

	//Create new file
		//function: fopen()
	openOutputFile( fileName );

	//Get random number n between 1 and 10
		//function: getRandBetween()
	randomNumberLoop = getRandBetween(minValue, maxValue);

	//Loop n-times getting a random value for an income
	for (index = 0; index < randomNumberLoop - 1; index++)
	{
		//get the income value
		randomIncomeNumber = getRandBetween( MIN_RAND_LIMIT, MAX_RAND_LIMIT );

		//Upload the random value PLUS THE DELIMITER
			//function: writeIntegerToFile( int outVal )
			//function: writeStringToFile(", ")
		writeIntegerToFile(randomIncomeNumber);
		writeStringToFile(", ");

		//Increase count
		numberCount++;

		if (numberCount % 5 == 0) //if there are 5 items move to next line
			{
				//function: writeEndlineToFile()
				writeEndlineToFile();
			}
	}

	//upload the last value WITHOUT THE DELIMITER
		//function: writeIntegerToFile( int outVal )
	randomIncomeNumber = getRandBetween( MIN_RAND_LIMIT, MAX_RAND_LIMIT );
	writeIntegerToFile(randomIncomeNumber);

	//Close the file
		//function: closeOutputFile()
	closeOutputFile();
}

/*
Name: getRandBetween
process: accepts a low limit and high limit value and generates a value between
			 	 them (inclusive), then returns it
Function input/parameters: int minLimit, int maxLimit
Function output/parameters: none
Function output/returned: Random number
Device input/file: none
Device output/monitor: none
Dependencies: rand
*/
int getRandBetween(int minLimit, int maxLimit)
{

	// initialize variables
	int range;

	// set range
	range = maxLimit - minLimit + 1;

	// return value
	return rand()% range + minLimit;
}

/*
Name: printTitle
process: prints the title of the program with a thick underline
Function input/parameters: none
Function output/parameters: none
Function output/returned: none
Device input/file: none
Device output/monitor: Title and underline
Dependencies: Console IO Utilities tools
*/
void printTitle()
{
	// prints the title and underline
		//functions: printEndline(), printString()
	printString("\nTotal Income From File Calculator\n");
	printString("=================================\n\n");

}

/*
Name: uploadData
process: accepts the file name, opens the file, loads the one dimensional
			 	 array with the data, closes the file, and returns the number of values.
				 Otherwise the function returns zero
Function input/parameters: fileName (char array), incomeArray (int array)
Function output/parameters: loads array
Function output/returned: sourceCount (int)
Device input/file: none
Device output/monitor: none
Dependencies: File input IO utilities
*/
int uploadData(char *fileName, int incomeArray[])
{

	int sourceCount = 0;
	int currentInteger;

	//open the file
	openInputFile(fileName);

	//prime the loop
	currentInteger = readIntegerFromFile();

	//Loop to the end of the file
		//function: checkForEndOfInputFile()
	while ( !checkForEndOfInputFile() )
		{
			//Add the integer into the array
			incomeArray[sourceCount] = currentInteger;

			//Increase array count
			sourceCount++;

			//read the delimiter
			readCharacterFromFile();

			//read the current integer
			currentInteger = readIntegerFromFile();
		}

	//close the file
	closeOutputFile();

	return sourceCount;
}
