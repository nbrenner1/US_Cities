// **************************************************************************************
// Title: U.S. Cities
// Author: Nick Brenner
// Functionality: This program reads in from a file containing information
// about major U.S. cities. This information includes city name, state in which
// the city resides, latitude, longitude, and population. The user can then
// enter a state to view all cities from that state included in the file
// as well as their coordinates and population. The program also returns the
// total population of all the cities from that state. Finally, this
// program outputs all cities with a population between 1 million and 2 million
// **************************************************************************************

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCAR 500

struct metro   // Define metro stucture
{
    char city[50];
    char state[3];
    double latitude;
    double longitude;
    int population;
};

void atometro(char *buf, struct metro *met);

int totalStatePopulation(struct metro[], char[], int);

void citiesWithPopulations1Mto2M(struct metro[],int);

int main()
{
    FILE *fp;
    char row[MAXCAR];
    char title[MAXCAR];
    struct metro x[MAXCAR];
    char userState[2];
    int size=0;
    int totalPop=0;

    fp = fopen("uscities.csv", "r");  // Open file for reading
    fgets(title, MAXCAR, fp);  // Get the first line in order to skip it before starting the loop
    int i=0;
    while (fgets(row, MAXCAR, fp) != NULL)  // Read in a row until none remain
    {
        atometro(row, &x[i]);  // Take the information in that row and make it a metro in our array
        i++;
    }
    size = i+1;  // Size of our array of metros is the number of times through the loop (i=0 to start)

    printf("Enter a state to view cities and total population (ex. WI): ");
    scanf("%s", userState); // Read in user's chosen state
    printf("** In %s\n", userState);
    for (int j=0; j<size; j++)
    {
        int result = strcmp(x[j].state, userState);  // Check if the state matches for each metro in the array
        if (result==0)
        {
            printf("%-20s %-4s %-10f %-11f %d\n", x[j].city, x[j].state, x[j].latitude, x[j].longitude, x[j].population);
        }
    }
    printf("Population %45d\n", totalStatePopulation(x,userState,size));  // Compute and print population
    printf("\n");

    citiesWithPopulations1Mto2M(x,size);  // Function called to print cities with populations between 1M and 2M
}


void atometro(char *buf, struct metro *met)  // Function to save info from the file to a metro
{
    strcpy(met->city, strtok(buf, ","));
    strcpy(met->state, strtok(NULL, ","));
    met->latitude = atof(strtok(NULL, ","));
    met->longitude = atof(strtok(NULL, ","));
    met->population = atof(strtok(NULL, ","));
}

int totalStatePopulation(struct metro met[], char *userState, int size)
{
    int totalPop=0;
    for (int j=0; j<size; j++)
    {
        int result = strcmp(met[j].state, userState);  // Find cities in desired state
        if (result==0)
        {
            totalPop += met[j].population;  // Increment total population by that city's population
        }
    }

    return totalPop;
}

void citiesWithPopulations1Mto2M(struct metro met[], int size)
{
    printf("** Cities Popultion (1M to 2M)\n");
    for (int i=0; i<size; i++)
    {
        if ((met[i].population > 1000000) && (met[i].population < 2000000))    // Check that population falls in range 1M to 2M
        {
            printf("%-20s %-4s %-10f %-11f %d\n", met[i].city, met[i].state, met[i].latitude, met[i].longitude, met[i].population);
        }
    }
}
