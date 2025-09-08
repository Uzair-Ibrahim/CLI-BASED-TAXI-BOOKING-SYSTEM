#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max_drivers 100
#define points 16
#define booking_file "booking_records.txt"
#define user_file "users.txt"

typedef struct 
{
    char name[20];
} Driver;

 char phoneNumber[20];

const char *pickupPoints[points] =
{
    "North Karachi", "Tower", "Kemari", "DHA", "Gulshan-e-Iqbal", "Johar",
    "PECHS", "Karsaz", "Clifton", "Sea View", "Numaish", "Drigh Road",
    "Malir", "Quaidabad", "Shah Latif Town", "Gulshan-e-Hadeed"
};

void signup() 
{
    char name[50], phone[15], password[20], fileName[50], filePhone[15],filePassword[20];
    FILE *file;
    file = fopen(user_file, "r");
    if (!file) {
        printf("Error: Unable to open file.\n");
        return;
    }

    system("color 9C");
    printf("             Enter your name: ");
    scanf("%s", name);
    fflush(stdin);
	while (1) 
	{
        printf("             Enter phone (11 digits): ");
        scanf("%s", phone);

        if (strlen(phone) != 11) 
		{
            printf("             Error: Phone number must be exactly 11 characters long.\n");
        } 
		else 
		{
            int i,valid = 1;
            for (i = 0; i < 11; i++) 
			{
                if (phone[i] < '0' || phone[i] > '9') 
				{
                    valid = 0;
                    break;
                }
            }

            if (valid) 
			{
                break; 
            } 
			else 
			{
                printf("             Error: Phone number must contain only digits.\n");
            }
        }
    }
    printf("             Create a password: ");
    scanf("%s", password);

    while (fscanf(file, "%s %s %s", fileName, filePhone, filePassword) != EOF) 
	{
        if (strcmp(phone, filePhone) == 0) 
		{
            printf("             Error: Phone number already exists. Please use a different phone number.\n");
            printf("             enter any key to continue...");
            getchar();
			getchar();
            system("cls");
            fclose(file);
            return;
        }
    }
    fclose(file);
    
    file = fopen(user_file, "a");
    if (!file) 
	{
        printf("Error: Unable to open file for writing.\n");
        return;
    }
    fprintf(file, "%s %s %s\n", name, phone, password);
    fclose(file);

    printf("             Signup successful! You can now login.\n");
    printf("             enter any key to continue...");
    getchar();
	getchar();
	system("cls");
}

int login() 
{
    char phone[15], password[20], filePhone[15], filePassword[20], fileName[50];
    FILE *file = fopen(user_file, "r");
    if (!file) 
	{
        printf("Error: Unable to open file.\n");
        return 0;
    }
    
	system("color 8A");
    while (1) 
	{
        printf("             Enter phone (11 digits): ");
        scanf("%s", phone);

        if (strlen(phone) != 11) 
		{
            printf("             Error: Phone number must be exactly 11 characters long.\n");
        } 
		else 
		{
            int i,valid = 1;
            for (i = 0; i < 11; i++) 
			{
                if (phone[i] < '0' || phone[i] > '9') 
				{
                    valid = 0;
                    break;
                }
            }

            if (valid) 
			{
                break;
            } 
			else 
			{
                printf("             Error: Phone number must contain only digits.\n");
            }
        }
    }
    printf("             Enter your password: ");
    scanf("%s", password);
    while (fscanf(file, "%s %s %s", fileName, filePhone, filePassword) != EOF) 
	{
        if (strcmp(phone, filePhone) == 0 && strcmp(password, filePassword) == 0) 
		{
        	strcpy(phoneNumber, phone);
            fclose(file);
            printf("             Login successful!\n");
            printf("             enter any key to continue...");
            getchar();
			getchar();
			system("cls"); 
            return 1;
        }
    }
    fclose(file);
    printf("             Invalid phone number or password.\n");
    printf("             enter any key to continue...");
    getchar();
    getchar();
    system("cls");
    return 0;
}

int getFareRate(int vehicleType) 
{
    switch (vehicleType) 
	{
        case 1: 
			return 5;
        case 2: 
			return 10;
        case 3: 
			return 15;
        case 4: 
			return 20;
        default: 
			return 0;
    }
}

int loadDrivers(Driver drivers[max_drivers]) 
{
    FILE *file = fopen("drivers.txt", "r");
    if (!file) 
	{
        printf("Error: Could not open file drivers.txt\n");
        return 0;
    }
    int count = 0;
    while (fscanf(file, "%19s", drivers[count].name) == 1) 
	{
        count++;
    }
    fclose(file);
    return count;
}

int calculateDistance(int pickup, int dropoff) 
{
    int distances[points][points] = 
	{
        {0, 10, 20, 25, 15, 18, 12, 16, 22, 30, 8, 12, 35, 40, 45, 50},
        {10, 0, 12, 18, 10, 15, 8, 10, 15, 20, 6, 9, 30, 35, 40, 45},
        {20, 12, 0, 10, 25, 30, 18, 20, 12, 15, 20, 25, 40, 45, 50, 55},
        {25, 18, 10, 0, 12, 20, 15, 10, 8, 12, 15, 18, 30, 35, 40, 45},
        {15, 10, 25, 12, 0, 10, 12, 15, 20, 25, 5, 10, 22, 28, 35, 40},
        {18, 15, 30, 20, 10, 0, 8, 10, 15, 18, 12, 10, 20, 25, 30, 35},
        {12, 8, 18, 15, 12, 8, 0, 10, 18, 20, 5, 10, 25, 30, 35, 40},
        {16, 10, 20, 10, 15, 10, 10, 0, 8, 12, 10, 15, 18, 25, 30, 35},
        {22, 15, 12, 8, 20, 15, 18, 8, 0, 10, 15, 20, 28, 35, 40, 45},
        {30, 20, 15, 12, 25, 18, 20, 12, 10, 0, 22, 25, 35, 40, 45, 50},
        {8, 6, 20, 15, 5, 12, 5, 10, 15, 22, 0, 6, 25, 30, 35, 40},
        {12, 9, 25, 18, 10, 10, 10, 15, 20, 25, 6, 0, 20, 25, 30, 35},
        {35, 30, 40, 30, 22, 20, 25, 18, 28, 35, 25, 20, 0, 15, 20, 25},
        {40, 35, 45, 35, 28, 25, 30, 25, 35, 40, 30, 25, 15, 0, 10, 15},
        {45, 40, 50, 40, 35, 30, 35, 30, 40, 45, 35, 30, 20, 10, 0, 12},
        {50, 45, 55, 45, 40, 35, 40, 35, 45, 50, 40, 35, 25, 15, 12, 0}
    };
    
	return distances[pickup][dropoff];
}

void saveRecord(const char *name, const char *phone, const char *vehicleName,const char *pickupPoint, const char *dropoffPoint,int distance, int fare, const char *driver) 
{
    FILE *file = fopen(booking_file, "a");
    if (!file) 
	{
        printf("Error: Could not open file.\n");
        return;
    }
    
    fprintf(file, "Phone: %s\n", phone);
    fprintf(file, "Vehicle: %s\n", vehicleName);
    fprintf(file, "Pick-Up: %s\n", pickupPoint);
    fprintf(file, "Drop-Off: %s\n", dropoffPoint);
    fprintf(file, "Distance: %d KM\n", distance);
    fprintf(file, "Fare: %d\n", fare);
    fprintf(file, "Driver: %s\n\n", driver);
    fclose(file);
}

void viewBookings() 
{
    printf("\nBOOKING DETAILS\n");

    FILE *file = fopen("booking_records.txt", "r");
    if (!file) 
	{
        printf("No bookings found.\n");
        return;
    }
    char data[200];
    int found = 0;
    char name[50] = "", phone[20] = "", vehicle[50] = "", pickup[20] = "";
    char dropoff[20] = "", distance[20] = "", fare[20] = "", driver[50] = "";
    while (fgets(data, sizeof(data), file)) 
	{
        if (strstr(data, phoneNumber)) 
		{
            found = 1;
            strcpy(phone, phoneNumber);

            fflush(stdin);
            while (fgets(data, sizeof(data), file)) 
			{
			    if (strstr(data, "Vehicle:")) 
				{
                    sscanf(data, "Vehicle: %49[^\n]", vehicle);
                } 
				else if (strstr(data, "Pick-Up:")) 
				{
                    sscanf(data, "Pick-Up: %19[^\n]", pickup);
                } 
				else if (strstr(data, "Drop-Off:")) 
				{
                    sscanf(data, "Drop-Off: %19[^\n]", dropoff);
                } 
				else if (strstr(data, "Distance:")) 
				{
                    sscanf(data, "Distance: %19[^\n]", distance);
                } 
				else if (strstr(data, "Fare:")) 
				{
                    sscanf(data, "Fare: %19[^\n]", fare);
                }
				else if (strstr(data, "Driver:")) 
				{
                    sscanf(data, "Driver: %49[^\n]", driver);
                }
            }

            printf("Vehicle: %s\n", vehicle);
            printf("Pickup: %s\n", pickup);
            printf("Dropoff: %s\n", dropoff);
            printf("Distance: %s\n", distance);
            printf("Fare: %s\n", fare);
            printf("Driver: %s\n", driver);
            break; 
        }
    }

    if (!found) 
	{
        printf("No bookings found for this phone number.\n");
    }

    fclose(file);
}

void updateBookingRecords(char *oldPhone, char *newPhone) 
{
    FILE *file = fopen(booking_file, "r");
    FILE *tempFile = fopen("temp_bookings.txt", "w");
    if (!file || !tempFile) 
	{
        printf("Error: Could not open booking files.\n");
        
		if (file) fclose(file);
        
		if (tempFile) fclose(tempFile);
        
		return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) 
	{
        if (strstr(line, oldPhone)) 
		{
            fprintf(tempFile, "Phone: %s\n", newPhone);
        } 
		else 
		{
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(booking_file);
    rename("temp_bookings.txt", booking_file);

}

void updatePhoneNumber() 
{
    char oldPhone[20], newPhone[20], fileName[50], filePhone[20], filePassword[20];
    int found = 0;

    FILE *file = fopen(user_file, "r");
    FILE *tempFile = fopen("temp_users.txt", "w");
    if (!file || !tempFile) 
	{
        printf("Error: Could not open files.\n");
    
	    if (file) fclose(file);
    
	    if (tempFile) fclose(tempFile);
    
	    return;
    }
    
    while (1) 
	{
        printf("             Enter old phone (11 digits): ");
        scanf("%s", oldPhone);

        if (strlen(oldPhone) != 11) 
		{
            printf("             Error: Phone number must be exactly 11 characters long.\n");
        } 
		else 
		{
            int i,valid = 1;
            for (i = 0; i < 11; i++) 
			{
                if (oldPhone[i] < '0' || oldPhone[i] > '9') 
				{
                    valid = 0;
                    break;
                }
            }
            if (valid) 
			{
                break; 
            } 
			else 
			{
                printf("                Error: Phone number must contain only digits.\n");
            }
        }
    }
    
    while (1) 
	{
        printf("                Enter New phone (11 digits): ");
        scanf("%s", newPhone);

        if (strlen(newPhone) != 11) 
		{
            printf("                Error: Phone number must be exactly 11 characters long.\n");
        } 
		else 
		{
            int i,valid = 1;
            for (i = 0; i < 11; i++) 
			{
                if (newPhone[i] < '0' || newPhone[i] > '9') 
				{
                    valid = 0;
                    break;
                }
            }

            if (valid) 
			{
                break;
            } 
			else 
			{
                printf("                Error: Phone number must contain only digits.\n");
            }
        }
    }

    while (fscanf(file, "%s %s %s", fileName, filePhone, filePassword) != EOF) 
	{
        if (strcmp(filePhone, oldPhone) == 0) 
		{
            fprintf(tempFile, "%s %s %s\n", fileName, newPhone, filePassword);
            found = 1;
        }
		else 
		{
            fprintf(tempFile, "%s %s %s\n", fileName, filePhone, filePassword);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) 
	{
        remove(user_file);
        rename("temp_users.txt", user_file);
        updateBookingRecords(oldPhone, newPhone);
        printf("Phone number updated successfully.\n");
    } 
	else 
	{
        remove("temp_users.txt");
        printf("Current phone number not found.\n");
    }
}

int main() 
{
    
	Driver drivers[max_drivers];
    int driverCount = loadDrivers(drivers);
    
	if (driverCount == 0) 
	{
        printf("No drivers available.\n");
        return 1;
    }
    
	int loggedIn = 0;
    
	while (1) 
	{
        int choice;
        system("color 0D");
        printf("                ====================================================\n");
        printf("                |      WELCOME TO CLI-BASED TAXI BOOKING SYSTEM    |\n");
        printf("                ====================================================\n");
        printf("                PRESS ANY KEY TO CONTINUE....");
		getchar();
        system("cls");
        
		system("color 5A");
		printf("                ====================================================\n");
        printf("                |1. Signup                                         |\n");
        printf("                |2. Login                                          |\n");
        printf("                |3. Exit                                           |\n");
        printf("                ====================================================\n");
		printf("                Enter choice: ");
		scanf("%d", &choice);
        system("cls");
        
		switch (choice) 
		{
            case 1: 
			    signup(); 
			    break;
            case 2:
			    loggedIn = login(); 
			    if (loggedIn) system("cls"); 
				break;
            case 3: 
				return 0;
            default: 
				printf("                Invalid choice.\n");
			    continue;
            }
            if (loggedIn) break;
    }
    while (loggedIn) 
	{
        int userChoice;
       
	    system("color 7D");
        printf("                                =========================================\n");
        printf("                                |1. Book a Ride                         |\n");
        printf("                                |2. View Booking                        |\n");
        printf("                                |3. Update Phone Number                 |\n");
        printf("                                |4. Logout                              |\n");
        printf("                                =========================================\n");
		printf("                                Enter choice: ");
		scanf("%d", &userChoice);
        system("cls");
        
		switch (userChoice) {
            case 1: {
		
				    char name[50], phone[15], vehicleName[20];
				    int vehicleType, pickup, dropoff, distance, fare;
				    char driverName[20];
				
				    system("color 0A");
				    printf("            Enter name: ");
				    scanf("%s", name);
				    fflush(stdin);
		
				    while (1) 
					{
				        printf("         Enter phone (11 digits): ");
				        scanf("%s", phone);
				
				        if (strlen(phone) != 11) 
						{
				            printf("             Error: Phone number must be exactly 11 characters long.\n");
				        } 
						else 
						{
				            int i,valid = 1;
				            for ( i = 0; i < 11; i++) 
							{
				                if (phone[i] < '0' || phone[i] > '9') 
								{
				                    valid = 0;
				                    break;
				                }
				            }
				            if (valid) 
							{
				                break;
				            } 
							else 
							{
				                printf("            Error: Phone number must contain only digits.\n");
				            }
				        }
				    }
				    
					system("cls");
				
				    printf("                ====================================================\n");
				    printf("                |1. Motorcycle                                     |\n");
				    printf("                |2. Rickshaw                                       |\n");
				    printf("                |3. Mini Car                                       |\n");
				    printf("                |4. AC Car                                         |\n");
				    printf("                ====================================================\n");
				    printf("                |Enter vehicle type: ");
				    scanf("%d", &vehicleType);
				    printf("                ====================================================\n");
				    system("cls");
				
				    switch (vehicleType) 
					{
				        case 1: 
							strcpy(vehicleName, "Motorcycle"); 
							break;
				        case 2: 
							strcpy(vehicleName, "Rickshaw"); 
							break;
				        case 3: 
							strcpy(vehicleName, "Mini Car"); 
							break;
				        case 4: 
							strcpy(vehicleName, "AC Car"); 
							break;
				        default:
				            printf("Invalid vehicle type.\n");
				            continue;
				    }
				    
					system("color 2E");
					int i;
					printf("             ===================================================\n");
				    for (i = 0; i < points; i++) 
					{
				        printf("             |%d. %s\n", i + 1, pickupPoints[i]);
				    }
				    printf("             ===================================================\n");
				    printf("             |Select pickup point: ");
				    scanf("%d", &pickup);
				
				    if (pickup < 1 || pickup > points) 
					{
				        printf("              Invalid pickup point.\n");
				        continue;
				    }
				    pickup--;
				    system("cls");
				    
				    printf("             ===================================================\n");
				    for (i = 0; i < points; i++) 
					{
				        printf("             |%d. %s\n", i + 1, pickupPoints[i]);
				    }
				    printf("             ===================================================\n");
				    printf("             |Select drop-off point: ");
				    scanf("%d", &dropoff);
				
				    if (dropoff < 1 || dropoff > points) 
					{
				        printf("              Invalid drop-off point.\n");
				        continue;
				    }
				    dropoff--;
				    
					distance = calculateDistance(pickup, dropoff);
				    fare = distance * getFareRate(vehicleType);
				    
				    strcpy(driverName, drivers[rand() % driverCount].name);
				    
					saveRecord(name, phone, vehicleName, pickupPoints[pickup],
				               pickupPoints[dropoff], distance, fare, driverName);
				
				    printf("Booking Confirmed!\n");
				    printf("Enter any key to continue...");
				    getchar();
				    getchar();
				    system("cls");
				}
				break;
            case 2: 
			    viewBookings(); 
			    printf("enter any key to continue...");
			    getchar();
			    getchar();
                system("cls");
				break;
			case 3:
				updatePhoneNumber();
				printf("enter any key to continue...");
			    getchar();
			    getchar();
                system("cls");
				break;
            case 4: 
				loggedIn = 0; 
				printf("Logged out.\n"); 
				break;
            default: 
				printf("Invalid choice.\n");
				continue;
            }
    }
    return 0;
}
