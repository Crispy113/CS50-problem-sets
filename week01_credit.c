#include <cs50.h>
#include <stdio.h>

int countDigit(long n);
int validate(long cardNb);


int main(void)
{

    long cardNb = 0; //Variable to store card number
    int digitCount = 0; //Nb. of digits in card number
    int valid = 0;

    //Ask user for card nb.
    cardNb = get_long("Number: ");

    //Count nb. of digits in card nb.
    digitCount = countDigit(cardNb);

    //Validate checksum
    valid = validate(cardNb);

    //Check card type
    if ((cardNb / 10000000000000 == 34 || cardNb / 10000000000000 == 37) && digitCount == 15) // AMEX
    {
        if (valid == 1)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else if (digitCount == 16 && (cardNb / 100000000000000 > 50) && (cardNb / 100000000000000 < 56))// MASTERCARD
    {
        if (valid == 1)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else if (digitCount == 13  && (cardNb / 1000000000000) == 4) // VISA
    {
        if (valid == 1)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (digitCount == 16  && (cardNb / 1000000000000000) == 4) // VISA
    {
        if (valid == 1)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else //INVALID
    {
        printf("INVALID\n");
    }

} //End of Main



//CUSTOM VARIABLES

//Count number of digits in number
int countDigit(long n)
{
    int count = 0;
    do
    {
        n /= 10;
        ++count;
    }
    while (n != 0);

    return count;
}

//Validate checksum w. Luhn’s algorithm
int validate(long cardNb)
{
    int sum = 0;
    int valid = 0;

    while (cardNb > 0)
    {
        sum = sum + (cardNb % 10);
        cardNb = cardNb / 10;

        sum = sum + (((cardNb % 10) * 2) % 10) + ((((cardNb % 10) * 2) / 10) % 10);
        cardNb = cardNb / 10;
    }

    if ((sum % 10) == 0)
    {
        valid = 1;
    }

    return valid;
}
