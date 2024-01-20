
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct rec
{
//to store various data required
int id;
char name[30];
 char branch[30];
 char dose[30];
 char type[30];
 int cert_no;
}rec;
//    FUNCTION TO INSERT RECORDS TO THE FILE
void insert()
{
 FILE *fp;
 fp = fopen("CR", "a");
 printf("\nEnter the ID.:");
 scanf("%d", &rec.id);
 printf("\n---------------");
 fflush(stdin);
 printf("\nEnter the Name.:");
 scanf("%[^\n]s", &rec.name);
 printf("\n-----------------");
 printf("\nEnter the Branch.:");
 scanf("%s", &rec.branch);
 printf("\n------------------");
 fflush(stdin);
 printf("\nEnter vaccination status(DONE[D]/NOT DONE[NT]).:");
 scanf("%s", &rec.dose);
 printf("\n-------------------------------------------------");
 printf("\nEnter the student or faculty (STUD/FACT).:");
 scanf("%s", &rec.type);
 printf("\n--------------------------------------------");
 printf("\nEnter the Certificate Number.:");
 scanf("%d", &rec.cert_no);
 printf("\n-------------------------------");
 printf("\n*************************************************************");
 printf("\n-------------------DATA SAVED SUCCESSFULLY---------------------");
 printf("\n*************************************************************");
 fwrite(&rec, sizeof(rec), 1, fp);
 fclose(fp);
}
//FUNCTION TO DISPLAY RECORDS
void display()
{
 FILE *fp1;
 fp1 = fopen("CR", "r");
 printf("\n*************************************************************************************************************************************************************************");
 printf("\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
 printf(" \n       ID           |          NAME            |            BRANCH            |         VAC_STATUS         |         STUD/FACT           |          CERT_NO        \n\n");
 printf("\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
 printf("\n*************************************************************************************************************************************************************************");
 while (fread(&rec, sizeof(rec), 1, fp1))
 printf(" %d                    %s                       %s                       %s                                %s                               %d\n", rec.id,rec.name,rec.branch,rec.dose,rec.type,rec.cert_no);
 printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
 fclose(fp1);
}
//    FUNCTION TO SEARCH THE GIVEN RECORD
void search()
{
 FILE *fp2;
 int r, s, avl;
 printf("\nEnter the ID to be searched.:");
 scanf("%d", &r);
 printf("\n-------------------------------");
 avl = avlrollno(r);
 if (avl == 0)
  printf("ID %d is not available in the file\n",r);
 else
 {
  fp2 = fopen("CR", "r");
  while (fread(&rec, sizeof(rec), 1, fp2))
  {
   s = rec.id;
   if (s == r)
   {
    printf("\n*****************************************");
    printf("\n-----------------------------------------");
    printf("\nID = %d", rec.id);
    printf("\nNAME = %s", rec.name);
    printf("\nBRANCH = %s", rec.branch);
    printf("\nVACCINE_STATUS = %s", rec.dose);
    printf("\nSTUDENT/FACULTY = %s", rec.type);
    printf("\nCERTIFICATE_NO = %d", rec.cert_no);
    printf("\n-----------------------------------------");
    printf("\n*****************************************");
   }
  }
  fclose(fp2);
 }
}
//    FUNCTION TO DELETE A RECORD
void delete()
{
 FILE *fpo;
 FILE *fpt;
 int r, s;
 printf("Enter the ID to be deleted:");
 scanf("%d", &r);
 printf("\n--------------------------");
 if (avlrollno(r) == 0)
  printf("ID %d is not available in the file\n", r);
 else
 {
  fpo = fopen("CR", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&rec, sizeof(rec), 1, fpo))
  {
   s = rec.id;
   if (s != r)
    fwrite(&rec, sizeof(rec), 1, fpt);
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("CR", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&rec, sizeof(rec), 1, fpt))
   fwrite(&rec, sizeof(rec), 1, fpo);
  printf("\nRECORD DELETED\n");
  fclose(fpo);
  fclose(fpt);
 }
}
//    FUNCTION TO UPDATE THE RECORD
void update()
{
 int avl;
 FILE *fpt;
 FILE *fpo;
 int s, r, ch;
 printf("Enter ID to update:");
 scanf("%d", &r);
 printf("\n-----------------");
 avl = avlrollno(r);
 if (avl == 0)
 {
  printf("ID %d is not Available in the file", r);
 }
 else
 {
  fpo = fopen("CR", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&rec, sizeof(rec), 1, fpo))
  {
   s = rec.id;
   if (s != r)
    fwrite(&rec, sizeof(rec), 1, fpt);
   else
   {
    printf("\n*****************************************");
    printf("\n-----------------------------------------");
    printf("\n\t1. Update Name of ID %d", r);
    printf("\n\t2. Update Branch of ID %d", r);
    printf("\n\t3. Update Vaccination Status of ID %d", r);
    printf("\n\t4. Update Student/Faculty status of ID %d", r);
    printf("\n\t5. Update Certificate Number of ID %d", r);
    printf("\n-----------------------------------------");
    printf("\n******************************************");
    printf("\nEnter your choice:");
    scanf("%d", &ch);
    printf("\n------------------\n");
    switch (ch)
    {
    case 1:
     printf("Enter Name.:");
     scanf("%s", &rec.name);
     printf("\n-----------");
     break;
    case 2:
     printf("Enter Branch.: ");
     scanf("%s", &rec.branch);
     printf("\n-------------");
     break;
    case 3:
     printf("Enter Vaccination Status.: ");
     scanf("%s", &rec.dose);
     printf("\n-------------------------");
     break;
     case 4:
     printf("Enter Student/Faculty status.: ");
     scanf("%s", &rec.type);
     printf("\n-----------------------------");
     break;
     case 5:
     printf("Enter Certificate Number.: ");
     scanf("%d", &rec.cert_no);
     printf("\n--------------------------");
     break;
     default:
     printf("Invalid Selection");
     break;
    }
    fwrite(&rec, sizeof(rec), 1, fpt);
   }
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("CR", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&rec, sizeof(rec), 1, fpt))
  {
   fwrite(&rec, sizeof(rec), 1, fpo);
  }
  fclose(fpo);
  fclose(fpt);
  printf("RECORD UPDATED");
 }
}
//    FUNCTION TO CHECK GIVEN ID IS AVAILABLE //
int avlrollno(int id)
{
 FILE *fp;
 int c = 0;
 fp = fopen("CR", "r");
 while (!feof(fp))
 {
  fread(&rec, sizeof(rec), 1, fp);

  if (id == rec.id)
  {
   fclose(fp);
   return 1;
  }
 }
 fclose(fp);
 return 0;
}
//FUNCTION TO CHECK THE FILE IS EMPTY OR NOT
int empty()
{
 int c = 0;
 FILE *fp;
 fp = fopen("CR", "r");
 while (fread(&rec, sizeof(rec), 1, fp))
  c = 1;
 fclose(fp);
 return c;
}
void certificate(char fna[50],char lna[50], int ag, int Aa, char va[50],char date[10])
{
printf("\n************************************************\n");
printf("------------------------------------------------\n");
printf("          COVID-19 VACCINATION CERTIFICATE          ");
printf("\n------------------------------------------------\n");
printf("************************************************\n");
printf("\n\n");
printf("\n------------------------------------------------\n");
printf("\n              BENEFICIARY DETAILS               \n");
printf("\n------------------------------------------------\n");
printf("Beneficiary First Name : ");
puts(fna);
printf("Beneficiary Last Name : ");
puts(lna);
printf("\nAge : %d\n ",ag);
printf("AADHAR CARD NUMBER : %d\n", Aa);
printf("\n\n");
printf("\n*************************************************\n");
printf("\n*************************************************\n");
printf("\n\n");
printf("\n-------------------------------------------------\n");
printf("                VACCINATION DETAILS                \n");
printf("\n-------------------------------------------------\n");
printf("Vaccination Name : ");
puts(va);
printf("\n");
printf("\nVaccination Date ");
puts(date);
printf("\n************************************************\n");
printf("\n************************************************\n");
printf("\n");
printf("-----------------------------------------------------------------------\n");
printf("CONGRATULATIONS YOU ARE NOW VACCINATED AND ELIGIBLE TO ATTEND COLLEGE\n");
printf("             STAY SAFE AND ALWAYS FOLLOW COVID PROTOCOLS             \n");
printf("-----------------------------------------------------------------------");
}
// MAIN PROGRAM
int main()
{
printf("\n----------------------------------------------------------------------------------------------------------------\n");
    printf("                     WELCOME TO                        ");
printf("\n\n");
    printf("      ***       ****        **          **   **    *****\n");
    printf("     ****     **    **       **        **    **    **   ** \n");
    printf("    **       **      **       **      **     **    **    **\n");
    printf("    **       **      **        **    **      **    **     **\n");
    printf("     ****     **    **          **  **       **    **    **\n");
    printf("      ***      *****              **         **    *******\n");
    printf("\n\n");
    printf("    *       *     *       ****    ****    **    *      *   ****** \n");
    printf("     *     *    *  *     *       *        **    * *    *   *      \n");
    printf("      *   *    ******    *       *        **    *  *   *   ****   \n");
    printf("       * *    *      *   *       *        **    *    * *   *      \n");
    printf("        *    *        *   ****    ****    **    *      *   ****** \n");
    printf("\n\n");
    printf("     *****    *      *     *****  *******   *****    **       **\n");
    printf("    *          *    *     *          *      *        * *     * *\n");
    printf("     ****        ***      ****       *      ****     *  *   *  *\n");
    printf("         *        *           *      *      *        *   * *   *\n");
    printf("     ****         *       ****       *      *****    *    *    *\n");
    printf("\n");
    printf("\n----------------------------------------------------------------------------------------------------------------\n");
 int c,emp;
 {
    int e=0;
	char username[15];
	char password[15];
	char original_username[25]="SDF";
	char original_password[15]="a";
    do
    {
		printf("\n\n\n\n\t\t\tEnter your Username and Password :)");
		printf("\n\t\t---------------------------------------------------");
		printf("\n\n\n\t\t\t\t\tUsername:");
		scanf("%s", &username);
		printf("\n\t\t---------------------------------------------------\n");
		printf("\n\n\t\t\t\t\tPassword:");
		scanf("%s",&password);
		printf("\n\t\t---------------------------------------------------\n");
		if(strcmp(username,original_username)==0 && strcmp(password,original_password)==0)
		{
			printf("\n\n\n\t\t\t\t...Login Successfull...");
			printf("\n\t\t***************************************************\n");
			getch();
			//call MainMenu function
			break;
		}
		else
		{
			printf("\n\t\t\tPassword is incorrect:( Try Again :)");
			e++;
			getch();
		}

	}while(e<=2);
	if(e>2)
	{
		printf("You have cross the limit.You cannot Login. :( :(");
		getch();
		printf("--------------------------------------------------");

	}
do
{
  printf("\n------------------------------------Select your choice------------------------------------\n");
  printf("\n\t1. INSERT\n\t2. DISPLAY\n\t3. SEARCH                          ");
  printf("\n\t4. DELETE\n\t5. UPDATE\n\t6. VACCINATION CERTIFICATE\n\t7. VIEW DATE OF  NEXT VACCINATION");
  printf("\n\t8. EXIT");
  printf("\n\n-----------------------------------------------------------------------------------------\n");
  printf("\nEnter your choice:");
  scanf("%d", &c);
  printf("\n---------------------");
  printf("\n");
  char firstname[50];
  char lastname[50];
  int age, Aadhar;
  char vaccine[50];
  char dt[10];
  int day=0;
  int month=0;
  int year=0;
  int n=0;
  if(c==1)
   insert();
  else if(c==2)
  {
   emp = empty();
   if (emp == 0)
    printf("\nThe file is EMPTY\n");
   else
   display();
  }
   else if(c==3)
   search();
   else if(c==4)
   delete();
   else if(c==5)
   update();
   else if(c==6)
  {
printf("Enter the First name");
scanf("%s",firstname);
printf("\n-----------------------\n");
printf("Enter the Last name");
scanf("%s",lastname);
printf("\n-----------------------\n");
printf("Enter age \n");
scanf("%d",&age);
printf("\n-----------------------\n");
printf("Enter Aadhar Number");
scanf("%d",&Aadhar);
printf("\n-----------------------\n");
printf("Enter VACCINE NAME\n");
scanf("%s",vaccine);
printf("\n-----------------------\n");
printf("Enter Date Of Vaccination in DD-MM-YY format");
scanf("%s",dt);
printf("\n--------------------------------------------\n");
certificate(firstname,lastname,age,Aadhar,vaccine,dt);
printf("\n\n\n\n");
}
else if(c==7)
{
  printf("\n---------------------------------\n");
  printf("ENTER THE DATE OF FIRST DOSE : \n");
  // To print the next date of vaccination
  scanf("%d/%d/%d",&day,&month,&year);
 printf("\n---------------------------------\n");
  if(month>=1&&month<=12)
  {
    if(month==1||month==3||month==5||month==7||month==8||month==10)
    {
        if(day==1)
        {
        printf("THE DATE OF NEXT VACCINATION IS : %d/%d/%d\n",day+30,month,year);}
      else if(day>1&&day<=31)
      {
        printf("THE DATE OF NEXT VACCINATION IS : %d/%d/%d\n",day,month+1,year);
      }else{
        printf("Invalid date");
      }
    }
    else if(month==4||month==6||month==9||month==11)
    {
      if(day>=1&&day<=30)
      {
        printf("THE DATE OF NEXT VACCINATION IS : %d/%d/%d\n",day,month+1,year);
      }else{
        printf("Invalid date");
      }
    }
    else if(month==2)
    {
      if(year%4==0)
      {
        if(year%100==0)
        {
          if(year%400==0)
          {
            if(day>=1&&day<=29)
            {
              printf("THE DATE OF NEXT VACCINATION IS : %d/%d/%d\n",day,month+1,year);
            }else{
              printf("Invalid date.\n");
            }
          }
          else if(day>=1&&day<=28)
          {
            printf("THE DATE OF NEXT VACCINATION IS : %d/%d/%d\n",day,month+1,year);
          }else{
            printf("Invalid date");
          }
        }
        else if(day>=1&&day<=29)
        {
          printf("THE DATE OF NEXT VACCINATION IS : %d/%d/%d\n",day,month+1,year);
        }else{
          printf("Invalid date");
        }
      }
      else if(day>=1&&day<=28)
      {
        printf("THE DATE OF NEXT VACCINATION IS : %d/%d/%d\n",day,month+1,year);
      }else{
        printf("Invalid date");
      }
    }
  }
  else{
    printf("Invalid date");
  }
  if(month==12)
  {
      if(day==1)
      printf("THE DATE OF NEXT VACCINATION IS : %d/%d/%d\n",day+30,month,year);
      else
      printf("THE DATE OF NEXT VACCINATION IS : %d/%d/%d\n",day,month-11,year+1);
  }
  printf("--------------------------------------------------------------------------------");
}
else if(c==8)
{
printf("\n-----------------------------------------------------------------------------------------------\n");
printf("                                 PRECAUTIONS FOR COVID-19                                             ");
printf("\n-----------------------------------------------------------------------------------------------\n");
printf("\n            1)Maintain a safe distance from others (ATLEAST 1 meter)                    ");
printf("\n                           2)  Wear a mask in public                                    ");
printf("\n   3)  Clean your hands often. Use soap and water or an alchol based handrub            ");
printf("\n   4) Choose open, well-ventilated spaces over closed ones to prevent oxygen deficiency ");
printf("\n                               5) Get Vaccinated when it is your turn                   ");
printf("\n               6) Stay home if you feel unwell and avoid unnecessary gatherings         ");
printf("\n------------------------------------------------------------------------------------------\n");
printf("                                EMERGENCY  WARNING SIGNS                                                    ");
printf("\n------------------------------------------------------------------------------------------\n");
printf(" \n                                1)Trouble breathing                                                                 ");
printf(" \n                         2)Persistent chest pain or pressure                                                    ");
printf(" \n                                   3)High Fever                                                                          ");
printf("\n-------------------------------------------------------------------------------------------------------\n");
printf("                                   EMERGENCY TREATMENT                                                              ");
printf("\n-------------------------------------------------------------------------------------------------------\n");
printf("\n 1) If oxygen level goes down make the patient lie on his chest and breathe in and out  ");
printf(" \n                 2) Immediately call the ambulance from a nearby hospital              ");
printf("\n\n");
printf(" \nSTAY SAFE, RESPECT ALL THOSE WHO ARE WORKING FOR OUR SAFETY IN THESE TOUGH TIMES,DO NOT LOOSE HOPE\n");
printf(",THIS SHALL TOO PASS AND WE ARE TOGETHER IN THIS AND ALWAYS REMEMBER THE THREAT IS THE VIRUS, NOT THE PEOPLE");
printf("\n");
printf("\n*************************************************************************************************************\n");
printf("                                      THANK YOU                                                              ");
printf("\n*************************************************************************************************************\n");
printf("!!YOU HAVE BEEN EXITED FROM THE PROGRAM!!\n\n");
exit(1);
}
  else
   printf("\nYour choice is wrong\nPlease try again...\n");
 } while (c!= 8);
 return 0;
}

Output:
 

 

 

  
 
  

  
 
 

  

  
 
