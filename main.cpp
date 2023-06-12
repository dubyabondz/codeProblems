
#include <iostream>
#include <iomanip>  // used for the setwidth function
#include <cstdlib>
#include <vector>
#include <time.h>
#include <math.h>

// Function prototype for the up-front processing
bool _bPrepareQandA(FILE*, std::vector<int>**);

// TODO: MOVE REPLACE THIS FUNCTIONS
void func1();
void func2();

int main(/*unsigned*/ int argc, char** argv)
{ // why do I get a warning saying that the first arg int 'main' should be an int instead of an unisgned int???
    argc; argv;

    // Prep the log file for use
    FILE* fErrOut = nullptr;
    fErrOut = fopen("_QandA_errors.txt", "w");
    if (!fErrOut)
    {
        std::cout << "Exiting early."  << std::endl << "Failed to create the log file." << std::endl;
        return -1;
    }

    // Vector pointer to be used by the func as a return arg for populating.  NEED TO CHANGE 'int' TO THE CLASS TYPE THAT WILL BE USED
    std::vector<int>* pVectOutQandA = nullptr;

    // Prepare the vector and the class objects for each problem before presentin user information
    if(!_bPrepareQandA(fErrOut, &pVectOutQandA))
    {
        // Failed in the prep, log files should be written
    }

    std::cout << "This is the coding questions program.  The following is a list of of questions." << std::endl
            << "Enter the number of the problem that you wish to see a question and potentially an answer for." << std::endl
            << "All other input exits the program." << std::endl << std::endl;


    func1();

    func2();

    fclose(fErrOut);
    return 0;

}

bool _bPrepareQandA(FILE* fErrOut, std::vector<int>** doesntMatter)
{
    return true;
}

void func1()
{
    // First question: How do you find the missing number in a given integer array of 1 to 100?
    std::cout << "How do you find the missing number in a given integer array of 1 to 100?" << std::endl;

    // Going to use the simple additive of the endspoints.  
    //  For 100 we start at the two ends 1 & 100 or 0 & 100
    //  100+1=101 then 99+2=101, 98+3=101, 97+4=101, and so on...
    //  Using the 100 & 1 boundaries we'll have 101*50, the first 50 will coincide with the last 50
    unsigned int uiFull = 101 * 50;
    std::cout << "The number that the value should have is a total of: " << uiFull << "." << std::endl;
    //  Now we simply take the amount that's missing from this from the user and give them the answer
    std::cout << "This is the absolute number to do.  Simply creating an array with a randomly missing number and then see if it matches"  << std::endl;
    
    //  Create and store the random number
    srand((unsigned int)time(NULL));   
    unsigned int uiRand = rand() % 100; 

    unsigned int uiMissingNum = 0;
    for (unsigned int i=1; i<=100; ++i)
    {
        if (i != uiRand)
        {
            uiMissingNum += i;
        }
    }

    // Now we have a sequence with a missing number
    std::cout << "The missing number is: " << uiRand << std::endl;
    // And we're going to show that they match
    if (uiRand == (uiFull - uiMissingNum))
    {
        std::cout << "The missing number is " << uiRand << " and we found it with our approach." << std::endl;
    }
}    


void func2()
{
    // Second question: How do you find the duplicate number on a given integer array?
    std::cout << std::endl << std::endl << "***************" << std::endl << "How do you find the duplicate number on a given integer array?" << std::endl;

    // First we need to generate an arrary of random size and place unique values in it.  
    // I'm going to just an array of less than 400 & greater than 200 for convenience
    
    // Going to mod 400 to get an array of less than 200 and then double it until it's greater than 100
    unsigned int uiArraySize = (rand() % 200) + 1;  // The +1 is done on the off chance that 0 is returned from the rand mod op
    while (uiArraySize < 100)
    {
        std::cout << uiArraySize << std::endl;
        uiArraySize *=2;
    }

    std::cout << "array size: " << uiArraySize << std::endl;

    unsigned int* uiArrayRand = new unsigned int [uiArraySize];
    if (!uiArrayRand)
    {
        std::cerr << "Failure to alloc mem for integer array.  Exiting." << std::endl;
        return;
    }

    // Now we have to fill the array with values that are not repeating the same save one pair of values
    // TODO: Find an efficient way to randomly populate this array with non-repeating values
    for (unsigned int i=0; i<uiArraySize; ++i)
    {
        //TODO FIX: this needs to change such that the 8 bit values are unique; either 1, 2, 4, 8, 16, 32, 64, 128
        uiArrayRand[i] = i+201;
    }

    // Output the array
    // TODO FIX: Overflow with the +8 op past the Array Size
    for (unsigned int i=0; i<uiArraySize; i+=8)
    {
        std::cout << i+1 << ". " << uiArrayRand[i] << "  " << i+2 << ". " << uiArrayRand[i+1] 
            << "  " << i+3 << ". " << uiArrayRand[i+2] << "  " << i+4 << ". " << uiArrayRand[i+3]
            << "  " << i+5 << ". " << uiArrayRand[i+4] << "  " << i+6 << ". " << uiArrayRand[i+5]
            << "  " << i+7 << ". " << uiArrayRand[i+6] << "  " << i+8 << ". " << uiArrayRand[i+7] << std::endl;
    }

    // Since this is just a simple 'Does the value pre-exist or not' check or map can be a simple binary check and I can use a simple binary array for this
    // Map needs to be big enough to cover the scope of a 32 bit int for now
    unsigned int uiMapSize = (unsigned int)exp(32) / (sizeof(unsigned char)*8);
    unsigned char* ucMap = new unsigned char[uiMapSize];
    std::cout<<"size of ucMap is " << uiMapSize << std::endl;
    if (!ucMap)
    {
        std::cerr << "Failure to alloc memory for map.  Exiting." << std::endl;
        return;
    }

    // Going to grab a random value in the first half of the array and set it equal to a random value in the 2nd half
    unsigned int uiTempVal1, uiTempVal2 = 0;
    uiTempVal1 = rand() % uiArraySize;
    uiTempVal2 = ( (~uiTempVal1) % uiArraySize ); // 2s compliment to guartee it's not the same value as it's sister
    uiArrayRand[uiTempVal1] = uiArrayRand[uiTempVal2];  // set the duplicate

    std::cout << "Index duplicates are at " << uiTempVal2 << " and " << uiTempVal1 << " with value of " << uiArrayRand[uiTempVal1] << std::endl;

    // Now we loop through the array and map the values
    unsigned int uiTempIndex = 0;
    for(unsigned int i=0; i<uiArraySize; i++)
    {
        uiTempIndex = uiArrayRand[i] >> 3; // div by 8 to get the index into the map

        //Taking the value of each entry and flipping the bit in the map
        switch (uiArrayRand[i] % 8)
        {
        case 0:
            if (ucMap[uiTempIndex] & 0x1) goto mapError;
            ucMap[uiTempIndex] |= 0x1;
            break;
        case 1:
            if (ucMap[uiTempIndex] & 0x2) goto mapError;
            ucMap[uiTempIndex] |= 0x2;
            break;
        case 2:
            if (ucMap[uiTempIndex] & 0x4) goto mapError;
            ucMap[uiTempIndex] |= 0x4;
            break;
        case 3:
            if (ucMap[uiTempIndex] & 0x8) goto mapError;
            ucMap[uiTempIndex] |= 0x8;
            break;
        case 4:
            if (ucMap[uiTempIndex] & 0x10) goto mapError;
            ucMap[uiTempIndex] |= 0x10;
            break;
        case 5:
            if (ucMap[uiTempIndex] & 0x20) goto mapError;
            ucMap[uiTempIndex] |= 0x20;
            break;
        case 6:
            if (ucMap[uiTempIndex] & 0x40) goto mapError;
            ucMap[uiTempIndex] |= 0x40;
            break;
        case 7:
            if (ucMap[uiTempIndex] & 0x80) goto mapError;
            ucMap[uiTempIndex] |= 0x80;
            break;
        default:

mapError:
            if (i == uiTempVal1 || i == uiTempVal2)
            {
                std::cout << "Found the appropriate duplicates with indices " << uiTempVal1 << " and " << uiTempVal2 << " and value " << uiArrayRand[i] << std::endl;
            }
            else
            {
                std::cerr << "Failure unknown in assigning bit to map for index " << uiTempIndex
                          << " with value " << uiArrayRand[uiTempIndex] << ", map value is " << ucMap[uiTempIndex]
                          << ", Exiting." << std::endl;
            }
        }
    }

    delete[] uiArrayRand;
    delete[] ucMap;

}