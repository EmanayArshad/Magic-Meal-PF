#include<stdio.h>		
#include<time.h> 			
#include<stdlib.h> 			
#include <ctype.h>			
#include <windows.h>
#include<string.h>			
 
typedef struct{ 			

	char id[20]; 
	char firstname[25];
	char lastname[15];
	char number[15];
	char email[35];
	char address[70];
	char gender;

}customer;

	int i,x,again,total,quantity,loginv=0,b=0,l=0,d=0,sumtotal=0;	 
	char choice,id1;	
    int* lptr=&loginv;

// Consume the rest of the current input line to recover from invalid input
static void discardLine(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}
	
void titlepage(void){		 				

	system("color 6"); 		
	printf("\t\t\t\t ********************************************************\n");
	printf("\t\t\t\t |\t\tWelcome to The Meal-Magic\t\t|\n");
	printf("\t\t\t\t |\tThe Ultimate Restaurant Management System\t|\n");
	printf("\t\t\t\t *********************************************************\n");
	printf("Programming Fundamentals-Project made by:\n\t Ayesha Hassan (22K-4326)\n\t Emanay Arshad (22K-4602)\n\t Muhammad Ali Ansari (22K-4135)\n\t Section: BSCS-1F\n\n"); 
	
	 
    time_t time1; 				
    char* date_time; 			 
    time(&time1); 				 
    date_time = ctime(&time1); 
    printf("Today's Date and Current Time: %s", date_time);
    
	printf("\nIn this program, Pressing the following keys will perform respective actions.\n");
	printf(" 0. To exit the program\n");
	printf(" 1. Register as a new costumer\n");
	printf(" 2. Login as a registered costumer\n");
    printf(" 3. Order Meal \n");
    printf(" 4. View Customer Details \n");}

// Forward declarations
int search(customer cust);
void registration(customer cust);
customer login_customer(customer st);

int search(customer cust){
    FILE* fptr = fopen("textfile.txt","r");
    if (fptr == NULL) {
        return -1;
    }

    int foundLineNumber = -1;
    char line[1024];
    char idBuffer[20];
    int currentLine = 0;

    while (fgets(line, sizeof(line), fptr) != NULL) {
        currentLine++;
        if (sscanf(line, "%19s", idBuffer) == 1) {
            if (strcmp(cust.id, idBuffer) == 0) {
                foundLineNumber = currentLine;
                break;
            }
        }
    }

    fclose(fptr);
    return foundLineNumber;
}

void registration(customer cust) {
	system("CLS");
	printf("\t\t\tWelcome to the Registration process of The Magic Meal Restaurant.\n ");
	printf("\t\t\t***************************************************************\n");

	printf("\nEnter the following details for registration\n");

	FILE* fptr;
	fptr = fopen("textfile.txt", "a+");
	if (fptr == NULL) {
		printf("Error in opening file!\n");
		exit(1);
	}

	// --- ID input and duplicate check ---
	while (1) {
		printf("Enter ID (Preference: 13 Characters): ");
		scanf("%19s", cust.id);
		if (strlen(cust.id) != 13) {
			printf("Invalid CNIC length. Must be exactly 13 characters.\n");
			continue;
		}
		int found = 0;
		rewind(fptr);
		char temp_line[1024];
		char temp_id[20];
		while (fgets(temp_line, sizeof(temp_line), fptr) != NULL) {
			if (sscanf(temp_line, "%19s", temp_id) == 1) {
				if (strcmp(cust.id, temp_id) == 0) { found = 1; break; }
			}
		}
		if (found) {
			printf("You are already registered, please login and press y to continue.\n");
			fclose(fptr);
			return;
		} else {
			printf("This ID has %d characters and is successfully stored into the database\n", (int)strlen(cust.id));
			break;
		}
	}

	// --- First name ---
	printf("\nFirst name: ");
	getchar();
	scanf("%24[^\n]", cust.firstname);

	// --- Last name ---
	printf("\nLast name: ");
	getchar();
	scanf("%14[^\n]", cust.lastname);

	// --- Gender ---
	do {
		printf("\nGender (m/f): ");
		scanf(" %c", &cust.gender);
		cust.gender = tolower(cust.gender);
		if (cust.gender != 'm' && cust.gender != 'f') {
			printf("Invalid gender. Please enter 'm' or 'f'.\n");
		}
	} while (cust.gender != 'm' && cust.gender != 'f');

	// --- Address ---
	printf("\nPermanent Address: ");
	getchar();
	scanf("%69[^\n]", cust.address);

	// --- Email ---
	while (1) {
		printf("\nActive email: ");
		getchar();
		scanf("%34[^\n]", cust.email);
		if (strchr(cust.email, '@') == NULL || strchr(cust.email, '.') == NULL) {
			printf("\nEmail invalid\n");
		} else {
			break;
		}
	}

	// --- Phone ---
	while (1) {
		printf("\nPhone number: ");
		getchar();
		scanf("%14[^\n]", cust.number);
		if (strlen(cust.number) == 11) break; else printf("Incorrect Phone Number\nIt should be of 11 digits\n");
	}

	// --- Save to file ---
	fprintf(fptr, "%s %s %s %c %s %s %s\n",
		cust.id,
		cust.firstname,
		cust.lastname,
		cust.gender,
		cust.address,
		cust.email,
		cust.number
	);

	fclose(fptr);
}

customer login_customer(customer st){
	system("cls");
	system("color 6");
	printf("\t\t\t\tWelcome to the login Portal of The Magic Meal Restaurant.\n ");
	printf("\t\t\t\t*********************************************************\n");
	if(*lptr!=0){
		printf("You are already logged in!");
		return st;
	}

	printf("\n\nKindly enter your ID: ");
	scanf("%19s",st.id);
	int index=search(st);
	if (index != -1){
		*lptr=1;
		FILE* fptr = fopen("textfile.txt","r");
		if (fptr != NULL){
			char line[1024];
			int current=0;
			while (fgets(line,sizeof(line),fptr) != NULL){
				current++;
				if (current==index) {
					char* token;
					char buffer[1024];
					strcpy(buffer,line);
					// id
					token = strtok(buffer, " \n"); if(token) strcpy(st.id, token);
					// firstname
					token = strtok(NULL, " \n"); if(token) strcpy(st.firstname, token);
					// lastname
					token = strtok(NULL, " \n"); if(token) strcpy(st.lastname, token);
					// gender
					token = strtok(NULL, " \n"); if(token) st.gender = token[0];
					// address
					char address_acc[256] = "";
					while ((token = strtok(NULL, " \n")) != NULL) {
						if (strchr(token,'@') != NULL) break;
						if (address_acc[0] != '\0') strcat(address_acc, " ");
						strcat(address_acc, token);
					}
					strcpy(st.address, address_acc);
					// email
					if (token) strcpy(st.email, token);
					// number
					token = strtok(NULL, " \n"); if(token) strcpy(st.number, token);
					break;
				}
			}
			fclose(fptr);
		}
		char title[5];
		if(st.gender=='f'){
			strcpy(title,"Miss");
		}
		else{
			strcpy(title,"Mr.");
		}
		printf("\nLogin Successfull\nWelcome %s %s to our Restaurant.",title,(st.firstname));
		return st;
	} else {
		int attempts;
		printf("\nID is incorrect or ID is not registered in the database.\n");
		for(attempts=3;attempts>0;attempts--){
			printf("\nEnter ID again: ");
			getchar();
			scanf("%19s",st.id);
			int idx=search(st);
			if (idx != -1){
				*lptr=1;
				FILE* fptr = fopen("textfile.txt","r");
				if (fptr != NULL){
					char line[1024];
					int current=0;
					while (fgets(line,sizeof(line),fptr) != NULL){
						current++;
						if (current==idx) {
							char* token;
							char buffer[1024];
							strcpy(buffer,line);
							token = strtok(buffer, " \n"); if(token) strcpy(st.id, token);
							token = strtok(NULL, " \n"); if(token) strcpy(st.firstname, token);
							token = strtok(NULL, " \n"); if(token) strcpy(st.lastname, token);
							token = strtok(NULL, " \n"); if(token) st.gender = token[0];
							char address_acc[256] = "";
							while ((token = strtok(NULL, " \n")) != NULL) {
								if (strchr(token,'@') != NULL) break;
								if (address_acc[0] != '\0') strcat(address_acc, " ");
								strcat(address_acc, token);
							}
							strcpy(st.address, address_acc);
							if (token) strcpy(st.email, token);
							token = strtok(NULL, " \n"); if(token) strcpy(st.number, token);
							break;
						}
					}
					fclose(fptr);
				}
				char title[5];
				if(st.gender=='f') strcpy(title,"Miss"); else strcpy(title,"Mr.");
				printf("\nLogin Successfull\nWelcome %s %s to our Restaurant.",title,(st.firstname));
				break;
			} else {
				printf("\nID is incorrect or ID is not registered in the database.\n");
			}
		}
		return st;
	}
}

// Ordering phase starts here

typedef struct{
	char name[35];
	int price;
	int quantity;
}order;

	order *bp;
	order *lp;
	order *dp;
	void bfast();		
	void lunch();
	void dinner(); 
	void eexit();
	void ending();
	void m_m();
	void m_m(void){ 								
  	printf("\t\t\t\tWelcome to the Ordering Phase of The Magic Meal Restaurant.\n ");
  	printf("\t\t\t\t*****************************************************************\n");
  	printf("\n\nKindly enter the type of Meal you want:\n");
  	printf("\t\t\t[A] Breakfast\n");
  	printf("\t\t\t[B] Lunch\n");
  	printf("\t\t\t[C] Dinner\n");
  	printf("\t\t\t[D] Exit\n\n");
    printf("Your Choice: ");
    scanf(" %c", &choice);						
  	system("cls");{
		if (toupper(choice) == 'A' ) 			 
		  	bfast();
		else if (toupper(choice) == 'B')
			lunch();
		else if (toupper(choice) == 'C')
			dinner();
		else if (toupper(choice) == 'D'){
			printf("\nThank you for exiting from Meal-Magic-Ordering Phase.\nWe Expect to see you again.");
			system("CLS");}	
        else { 
            m_m();}}}
						
void bfast(void){ 							 
  int choice = 0,quantity=0,again=0;	
  // fflush(stdin); // removed unsafe fflush
  	printf("\t\t\t\tWelcome to Ordering Phase of The Magic Meal Restaurant.\n ");
  	printf("\t\t\t\t******************************************************\n\n");
  	printf("\t\t\t\t\t*Breakfast Menu*\n");
  	printf("\nKindly enter the Meal Number of Breakfast:\n");
  	printf("\t\t\t[1] Egg & Cheese McMuffin Meal - Rs 250\n");
  	printf("\t\t\t[2] Hashbrowns Wrap with Smoothie - Rs 400\n");
  	printf("\t\t\t[3] Big Breakfast Meal - Rs 1000\n\t\t    Meal 3 includes: Three fluffy scrambled eggs, savoury chicken sausage and a crispy golden hash brown\n");
  	printf("\n\t\t\t *Special 30 %% discount on Meal 3*\n\t\t\t *Discount valid only for today*\n");
	printf("Your Choice: ");
	b++;
	if(b==1){
        bp=(order*)malloc(b*sizeof(order));
        if (bp == NULL) { printf("Memory allocation failed\n"); exit(1); }
	}
	else{
        order* tmp = (order*)realloc(bp,b*sizeof(order));
        if (tmp == NULL) { printf("Memory allocation failed\n"); exit(1); }
        bp = tmp;
	}
  	scanf("%d", &choice);{
  		if (choice == 1) {
			printf("Enter quantity: ");
	  		scanf("%d", &quantity);
	  		total = 250 * quantity ;
	   		printf("Your total amount is Rs %d\n ", total); 
	   		strcpy((bp+(b-1))->name,"Egg & Cheese McMuffin Meal");
	   		(bp+(b-1))->price=total;
	   		(bp+(b-1))->quantity=quantity;
	   		sumtotal+=total;
	   		buy:
        printf("\nWould you like to buy anything else?\n[1] Yes , [2] No : "); 
        if (scanf("%d", &again) != 1) { discardLine(); printf("\n\nSorry Invalid Decision Entered\n\n\n\n"); goto buy; }
			system("cls");
		if (again == 1 )
			bfast();
		else if (again == 2 )
              	eexit();
        else {
            printf("\n\nSorry Invalid Decision Entered\n\n\n\n");
            goto buy;
            }}
		else if ( choice == 2){
		  	printf("Enter quantity: ");
		  	scanf("%d", &quantity);
		  	total = 400 * quantity ;
		  	printf("Your total amount is Rs %d\n\n ", total);
		  	strcpy((bp+(b-1))->name,"Hashbrowns Wrap with Smoothie");
	   		(bp+(b-1))->price=total;
	   		(bp+(b-1))->quantity=quantity;
	   		sumtotal+=total;
            printf("\nWould you like to buy anything else?\n[1] Yes , [2] No : "); 
            if (scanf("%d", &again) != 1) { discardLine(); printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n"); goto buy; }
			system("cls");
		if (again == 1 )
			bfast();
		else if (again == 2 )	
			eexit();
        else {
            printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n");
            goto buy;
            }}
		else if ( choice == 3 ){
			printf("Enter quantity: ");
			scanf("%d", &quantity);
			total = 700 * quantity ;
			printf("Your total amount is Rs %d\n\n ", total); 
			strcpy((bp+(b-1))->name,"Big Breakfast Meal");
	   		(bp+(b-1))->price=total;
	   		(bp+(b-1))->quantity=quantity;
	   		sumtotal+=total;
            printf("\nWould you like to buy anything else?\n[1] Yes , [2] No : "); 
            if (scanf("%d", &again) != 1) { discardLine(); printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n"); goto buy; }
			system("cls");
		if (again == 1 ){
			bfast();}
		else if (again == 2 ){	
			eexit();
			}
        else {
            printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n");
            goto buy;
            }}
        else if (choice != 1 && choice != 2 && choice != 3 ){
			system("CLS");
			bfast();}}}

void lunch(){ 								
    int choice = 0,quantity=0,again=0;	 					
	printf("\t\t\t\tWelcome to Ordering Phase of The Magic Meal Restaurant.\n ");
  	printf("\t\t\t\t******************************************************\n\n");
  	printf("\t\t\t\t*Lunch Menu*\n");
  	printf("\nKindly enter the Meal Number of Lunch:\n");
  	printf("\t\t\t[1] Fried Rice with Fish - Rs 400\n");
  	printf("\t\t\t[2] Crispy Chicken Bucket - Rs 1600\n");
  	printf("\t\t\t[3] Happy Meal - Rs 1000\n");
  	printf("\n\t\t\t *Special 50 %% discount on Meal 2*\n\t\t\t *Discount valid only for today*\n");
	printf("Your Choice: ");
	l++;
	if(l==1){
        lp=(order*)malloc(l*sizeof(order));
        if (lp == NULL) { printf("Memory allocation failed\n"); exit(1); }
	}
	else{
        order* tmp = (order*)realloc(lp,l*sizeof(order));
        if (tmp == NULL) { printf("Memory allocation failed\n"); exit(1); }
        lp = tmp;
	}
  	scanf("%d", &choice);{
  		if (choice == 1) {
	  		printf("Enter quantity: ");
	  		scanf("%d", &quantity);
	  		total = 400 * quantity ;
	  		printf("Your total amount is Rs %d \n ", total);
			strcpy((lp+(l-1))->name,"Fried Rice with Fish");
	   		(lp+(l-1))->price=total;
	   		(lp+(l-1))->quantity=quantity;
			sumtotal+=total;{
	  	    buyy:
            printf("\nWould you like to buy anything else?\n[1] Yes , [2] No : ");
            if (scanf("%d", &again) != 1) { discardLine(); printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n"); goto buyy; }
			system("cls");
		if (again == 1 )
			lunch();
		else if (again == 2 )
			eexit();
        else { 	
            printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n");
            goto buyy;
            }}}
		else if ( choice == 2){
		  	printf("Enter quantity: ");
		  	scanf("%d", &quantity);
		  	total = 800 * quantity ;
		  	printf("Your total amount is Rs %d\n ", total);
			strcpy((lp+(l-1))->name,"Crispy Chicken Bucket");
	   		(lp+(l-1))->price=total;
	   		(lp+(l-1))->quantity=quantity;
			sumtotal+=total;{
            printf("\nWould you like to buy anything else?\n[1] Yes , [2] No : ");
            if (scanf("%d", &again) != 1) { discardLine(); printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n"); goto buyy; }
			system("cls");
		if (again == 1 )
			lunch();
		else if (again == 2 )
				eexit();
        else { 	
                 printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n");
                 goto buyy;}}}
		else if ( choice == 3 ){
			printf("Enter quantity: ");
			scanf("%d", &quantity);
			total = 1000 * quantity ;
			printf("Your total amount is Rs %d \n\n ", total);
			strcpy((lp+(l-1))->name,"Happy Meal");
	   		(lp+(l-1))->price=total;
	   		(lp+(l-1))->quantity=quantity;
			sumtotal+=total;{
            printf("\nWould you like to buy anything else?\n[1] Yes , [2] No : ");
            if (scanf("%d", &again) != 1) { discardLine(); printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n"); goto buyy; }
			system("cls");
		if (again == 1 )
			lunch();
		else if (again == 2 )
			eexit();
        else { 	
            printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n");
            goto buyy;
            }}} 
        else if (choice != 1 && choice != 2 && choice != 3){
			system("cls");
			printf("\n\n\t\t Invalid Choice Entered\n\n");
			lunch();}}}
			
void dinner() {								
    int choice = 0,quantity=0,again=0;	 						
    printf("\t\t\t\tWelcome to Ordering Phase of The Magic Meal Restaurant.\n ");
  	printf("\t\t\t\t******************************************************\n\n");
  	printf("\t\t\t\t*Dinner Menu*\n");
  	printf("\nKindly enter the Meal type of Dinner:\n");
  	printf("\t\t\t[1] Beef Steak - Rs 1000\n");
  	printf("\t\t\t[2] Krunch Chicken Combo - Rs 550\n");
  	printf("\t\t\t[3] Rice N Spice - Rs 300\n");
  	printf("\n\t\t\t *Special 35 %% discount on Meal 1*\n\t\t\t *Discount valid only for today*\n");
  	printf("Your Choice: ");
d++;
  	if(d==1){
        dp=(order*)malloc(d*sizeof(order));
      if (dp == NULL) { printf("Memory allocation failed\n"); exit(1); }
	  }
	else{
        order* tmp = (order*)realloc(dp,d*sizeof(order));
        if (tmp == NULL) { printf("Memory allocation failed\n"); exit(1); }
        dp = tmp;
	}
    scanf("%d", &choice);
    
  		if (choice == 1) {
	  		printf("Enter quantity: ");
	  		scanf("%d", &quantity);
        total = 650 * quantity;
	  		printf("Your total amount is Rs %d\n ", total);
			strcpy((dp+(d-1))->name,"Beef Steak");
	   		(dp+(d-1))->price=total;
	   		(dp+(d-1))->quantity=quantity;
        sumtotal+=total;
        
            buyyy:
            printf("\nWould you like to buy anything else?\n[1] Yes , [2] No : ");
        if (scanf("%d", &again) != 1) { 
            discardLine(); 
            printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n"); 
            goto buyyy; 
        }
			system("cls");
        if (again == 1)
			dinner();
        else if (again == 2)
			eexit();
        else { 	
            printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n");
            goto buyyy;
        }
    }
    else if (choice == 2) {
		  	printf("Enter quantity: ");
		  	scanf("%d", &quantity);
        total = 550 * quantity;
        printf("Your total amount is Rs %d\n ", total);
			strcpy((dp+(d-1))->name,"Crunch Chicken Combo");
	   		(dp+(d-1))->price=total;
	   		(dp+(d-1))->quantity=quantity;
        sumtotal+=total;
        
            printf("\nWould you like to buy anything else?\n[1] Yes , [2] No : ");
        if (scanf("%d", &again) != 1) { 
            discardLine(); 
            printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n"); 
            goto buyyy; 
        }
			system("cls");
        if (again == 1)
			dinner();
        else if (again == 2)
			eexit();
        else { 	
            printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n");
            goto buyyy;
        }
    }
    else if (choice == 3) {
			printf("Enter quantity: ");
			scanf("%d", &quantity);
        total = 300 * quantity;
			printf("Your total amount is Rs %d\n ", total);
			strcpy((dp+(d-1))->name,"Rice N Spice");
	   		(dp+(d-1))->price=total;
	   		(dp+(d-1))->quantity=quantity;
        sumtotal+=total;
        
            printf("\nWould you like to buy anything else?\n[1] Yes , [2] No : ");
        if (scanf("%d", &again) != 1) { 
            discardLine(); 
            printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n"); 
            goto buyyy; 
        }
			system("cls");
        if (again == 1)
			dinner();
        else if (again == 2)
			eexit();
        else { 	
            printf("\n\n\t\tSorry Invalid Decision Entered\n\n\n\n");
            goto buyyy;
        }
    }
    else if (choice != 1 && choice != 2 && choice != 3) {
            system("cls");
            printf("\n\n\t\tInvalid Choice Entered\n\n");
        dinner();
		}
}

void rating(void){
	system("CLS");
	printf("\t\t\t\tWelcome to Rating and Suggestion phase of The Magic Meal Restaurant\n ");
  	printf("\t\t\t\t*******************************************************************\n\n");
 	FILE *rates;
 	rates=fopen("ratings.txt","r");
  	
  	// Initialize frequency counts
  	int freqcount[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  	
  	// Only read from file if it exists and can be opened
  	if (rates != NULL) {
	fscanf(rates,"%d %d %d %d %d %d %d %d %d %d\n",&freqcount[0],&freqcount[1],&freqcount[2],&freqcount[3],&freqcount[4],&freqcount[5],&freqcount[6],&freqcount[7],&freqcount[8],&freqcount[9]);
	fclose(rates);
  	}
  	
	int rate=0;
	char choice=0,suggestion[100];
	
	printf("\nKindly rate our program-service from 1 to 10: ");
	scanf("%d",&rate);
	while(rate<0 || rate>10){
		printf("\nInvalid rating");
		printf("\nKindly rate our program-service from 1 to 10: ");
		scanf("%d",&rate);
	}
	
	// Update frequency count based on rating
	if(rate >= 1 && rate <= 10) {
		freqcount[rate-1]++;
	}
	
	// Save updated ratings to file
	rates=fopen("ratings.txt","w");
	if (rates != NULL) {
	fprintf(rates,"%d %d %d %d %d %d %d %d %d %d\n",freqcount[0],freqcount[1],freqcount[2],freqcount[3],freqcount[4],freqcount[5],freqcount[6],freqcount[7],freqcount[8],freqcount[9]);
	fclose(rates);
		printf("\nThank you for your rating of %d!\n", rate);
	} else {
		printf("\nThank you for your rating of %d!\n", rate);
	}
	
suggest:
    printf("\nAny suggestions(Y/N): ");
    scanf(" %c",&choice);
	if(choice=='Y'|| choice=='y'){
		printf("\nKindly enter your suggestion here: ");
		FILE* suggest;
		suggest=fopen("Suggestions.txt","a");
		if (suggest != NULL) {
			getchar(); // clear leftover newline
			fgets(suggestion, sizeof(suggestion), stdin);
			suggestion[strcspn(suggestion, "\n")] = 0; // remove newline
		fputs(suggestion,suggest);
		fputs("\n",suggest);
		fclose(suggest);
		printf("\nYour valuable suggestion has been successfully recorded");
		} else {
			printf("\nThank you for your suggestion!");
		}
		Sleep(2000);
		ending(); // Go to ending which returns to main menu
	}
	else if(choice=='N'|| choice=='n'){
		ending(); // Go to ending which returns to main menu
	} 
	else {
	printf("\nInvalid Choice\n");
		goto suggest; 
	}
	}
	
 void hyperlink(void)
{
    char* internet = "START https://www.hbl.com/personal/digital-banking/hbl-internetbanking?gclid=CjwKCAiAjs2bBhACEiwALTBWZWO6ETOzYIHMkJcGeYa5FyAIxtkzLpvoWwRCmvRiUiuvtEaTmMlrCxoCvQ8QAvD_BwE"; //CharPointer or Char
    system (internet);
}
void billing_method(void){ 
	free(bp);
	free(lp);
	free(dp);
	int method;
	printf("\nSelect the billing method\n1.Online Payment\n2.Cash On Delivery\nYour Choice: ");
  	scanf("%d",&method);
  	switch(method){
  		case 1 :{
  			system("CLS");
  			printf("Redirecting you to the Online payment link...");
  			Sleep(2000);
  			hyperlink();
			break;
		  }
		  case 2:{
		   printf("\nThank you for choosing Cash on Delivery Method of payment\nOur Rider will be at your doorstep shortly...");
		  break;
		  }
		  default:{
		  	printf("\nInvalid Option Entered. Please select 1 or 2.\n");
		  	// Don't call billing_method() recursively to prevent infinite loop
		  	printf("Defaulting to Cash on Delivery...\n");
		  	printf("Thank you for choosing Cash on Delivery Method of payment\nOur Rider will be at your doorstep shortly...");
			break;
			}
	  }
}

void eexit()
{
    char billing_choice;
    char choice; // Declare choice variable locally
	system("CLS"); 
  printf("\t\t\t\tThank You for using ordering phase of The Meal Magic Restaurant\n ");
  printf("\t\t\t\t****************************************************************\n\n");
  printf("----------------------Order Summary----------------------\nName\t\t\t\tQuantity\tTotal Price\n");
  if(b>0){
  	for(int i=0;i<b;i++){
  	printf("%25s\t%d\t\t%d\n",(bp+i)->name,(bp+i)->quantity,(bp+i)->price);
  }
  }

  if(l>0){
  	for(int i=0;i<l;i++){
  	printf("%25s\t%d\t\t%d\n",(lp+i)->name,(lp+i)->quantity,(lp+i)->price);
  }
  }

  if(d>0){
  	for(int i=0;i<d;i++){
  	printf("%25s\t%d\t\t%d\n",(dp+i)->name,(dp+i)->quantity,(dp+i)->price);
  }
  }

  printf("----------------------------------------------------------\n%s\t\t\t\t\t\t%d\n----------------------------------------------------------\n\n","Total",sumtotal);
  
  // Always proceed to billing after showing order summary
  printf("\nProceeding to Billing...\n");
  Sleep(1000);
  	billing_method();
  
  // Ask for rating and suggestions with strict input validation
  for(;;){
  	printf("\nWhile the meal is on its way, do you wish to rate and suggest something for our restaurant?\nChoose from (Y/N): ");
  	if (scanf(" %c", &choice) != 1) { discardLine(); continue; }
  	choice = (char)tolower((unsigned char)choice);
  	if (choice == 'y'){
  		system("CLS");
  		printf("Proceeding to Rating and Suggestion Phase...\n");
  		Sleep(2000);
  		rating();
  		break;
  	} else if (choice == 'n'){
  		system("CLS");
  		printf("Thank you for your order!\n");
  		Sleep(2000);
  		ending();
  		break;
  	} else {
  		printf("\nInvalid choice. Please enter Y or N.\n");
  	}
  }
}

		
void viewall(customer st){
	system("cls");	
	printf("\t\t\t ********************************************************\n");
	printf("\t\t\t |\t\tWelcome to The Meal-Magic\t\t|\n");
	printf("\t\t\t |\tThe Ultimate Restaurant Management System\t|\n");
	printf("\t\t\t *********************************************************\n");
	int i=0;
	char title[5];
    if(st.gender=='f'){
		strcpy(title,"Miss");
	}
	else{
		strcpy(title,"Mr.");
	}
		    	printf("\n\t\tDetails Of %s %s\n",title,st.firstname);
				printf("\n\t\t**********************");
   				// fflush(stdin); // removed unsafe fflush
   				printf("\n\nID: %s",st.id);
   				printf("\nFirst Name: %s",st.firstname);
   				printf("\nLast Name: %s",st.lastname);
   				printf("\nContact Number: %s",st.number);
   				printf("\nEmail ID: %s",st.email);
	   			printf("\nAddress: %s",st.address);
   				printf("\nGender: %c",st.gender);
				printf("\n");}   

void hy_socialmedia(void){    
	char ch_social;
	printf("\nFor further updates visit our social media page ");
	againsocialmedia:
    printf("\nDo you want to visit our social media page(Y/N) ");
    scanf(" %c",&ch_social);
	if(ch_social=='Y' || ch_social=='y'){
		char*internet;
	internet="START https://www.facebook.com/profile.php?id=100087781915508";
	system (internet);
		printf("\nThank you for visiting our social media page!\n");
	}
	else if(ch_social=='N' || ch_social=='n'){
		printf("\nThank you for using our service!\n");
	}
	else {
		printf("\nEnter Valid Option: ");
		goto againsocialmedia;
	} 
	// Function returns to calling function (ending) which then returns to main menu
}

void ending(){
			system("CLS");
	 	 	printf("\n\t\t\tThank You for using the ordering phase of Meal-Magic \n ");
  			printf("\t\t\t******************************************************\n");
	printf("\n\t\t\t******************************************************\n");
  			hy_socialmedia();
	printf("\nReturning to main menu...\n");
			Sleep(2000);
	system("CLS");
	// Reset order counters for fresh start
	b = 0;
	l = 0;
	d = 0;
	sumtotal = 0;
	// Show title page when returning to main menu
	titlepage();
}


int main(){
	customer st;
	customer cust = {0}; // Initialize cust with zeros to prevent crashes
	titlepage();
	int yourchoice;
	char confirm;
	do{
		printf("Enter your choice(0-4): ");
		scanf("%d",&yourchoice);
		if (yourchoice==0) {
 	 		printf("\n\t\t\tThank You for using this program\n ");
  			printf("\t\t\t*********************************\n");
  			printf("\t\t\tTeam Meal-Magic expects to see you again in the near future.\n");
			printf("\t\t\t*************************************************************\n");
			break;}
		
switch(yourchoice){
			case 1:
				registration(st);
				break;
			case 2: 
				cust = login_customer(st);
				break;
			case 3:
				m_m();
				break;
			case 4:
				if(loginv == 0) {
					printf("\nPlease login first to view customer details!\n");
				} else {
					viewall(cust);
				}
				break;
	default:
	printf("\nInvalid Input\n");    
}
		
		// Only show confirmation prompt if not exiting
		if(yourchoice != 0) {
again99:
printf("\nPress y or Y to continue: ");
scanf(" %c",&confirm);
if(confirm=='y'||confirm=='Y'){
system("CLS");
				titlepage(); // Show full title page when returning to main menu
			} else if(confirm != 'n' && confirm != 'N') {
				goto again99;
			}
		}
	} while(confirm=='y'||confirm=='Y');
return EXIT_SUCCESS;
}