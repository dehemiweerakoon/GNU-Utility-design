#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#define A 18.5  //for  year
#define B 16    //for  year
#define C 28    //for  year
#define limitA 1000000
#define limitB 6000000
#define limitC 2000000
void open();
void display();
void ChangeProfile();
void Deposit_withDrowl();
void  searchAccount();
void loanBranch();
void closeAccount();

typedef struct Account
{
    char account_no[10];
    char name[50];
    float balance;
    char gender[10];
    char account_type;
    float amount;
    float have_to_pay;
    float interest_rate;
} account_holder;



void main()
{
    int choice;
    printf("\n\n---------------------Login------------------\n\n");
    char username[10];
    char password[20],c;
    printf("Enter username:");
    scanf(" %s",username);
    if(strcmp(username,"admin"))
    {
        printf("User name Incorrect");
        exit(0);
    }
    //printf("Enter worker Password:");
    // scanf(" %s",password);


    int index = 0;

    printf("Enter Password : ");
    /* 13 is ASCII value of Enter key */
    while((c = getch()) != 13)
    {
        if(index < 0)
            index = 0;
        /* 8 is ASCII value of BACKSPACE character */
        if(c == 8)
        {
            putch('\b');
            putch(NULL);
            putch('\b');
            index--;
            continue;
        }
        password[index++] = c;
        putch('*');
    }
    password[index] = '\0';
    if(strcmp(password,"2001"))
    {
        printf("\nPassword Incorrect");
        exit(0);
    }
    while(1)
    {



        printf("\n\n---------------------Welcome to CDB bank Management System------------------\n\n");
        printf("01.Open Accounts\n");
        printf("02.Display Accounts\n");
        printf("03.Change Personal Data\n");
        printf("04.Deposit / Withdrawal \n");
        printf("05.Search for special account details\n");
        printf("06.Pay for a Loan / Get A Loan\n");
        printf("07.Close Account\n");// User can close account if he/she dont have any loan to pay
        printf("08.Exit\n");
        printf("\nEnter choice to continue:");
        scanf(" %d",&choice);

        switch(choice)
        {
        case 1:
            open();
            break;
        case 2:
            display();
            break;
        case 3:
            ChangeProfile();
            break;
        case 4:
            Deposit_withDrowl();
            break;
        case 5:
            searchAccount();
            break;
        case 6:
            loanBranch();
            break;
        case 7:
            closeAccount();
            break;
        default:
            printf("Thank You Program Closed");
            exit(0);
        }

    }
    system("cls");
}
void open()
{
    int n_acc;
    FILE *fi;
    printf("\nHow many accounts do you want to open:");
    scanf(" %d",&n_acc);
    account_holder* customers;
    customers=(account_holder*)calloc(n_acc,sizeof(account_holder));
    fi=fopen("Account.txt","a");

    if (fi == NULL)
    {
        printf("Error opening the file: %s\n","Account.txt" );
        return 1;
    }
    for(int i=0; i<n_acc; i++)
    {
        printf("\n-----------------------------------------------------------------------------------------------------");
        printf("\nEnter Account NO:");
        scanf(" %s",customers[i].account_no);
        printf("\nEnter holders name:");
        scanf(" %[^\n]",customers[i].name);
        printf("\nEnter holders gender:");
        scanf(" %s",customers[i].gender);
        printf("\nEnter holders balance:");
        scanf(" %f",&customers[i].balance);
        while(customers[i].balance<500)
        {
            printf("\nYou must enter more than 500 to open account");
            printf("\nEnter holders balance:");
            scanf(" %f",&customers[i].balance);
        }
        printf(" \n");
        printf("\nEnter Account Type:(Saving Account---(S)/Loan Account---(L):");
        scanf(" %c",&customers[i].account_type);
        customers[i].account_type=toupper(customers[i].account_type);
        toupper(customers[i].account_type);
        if(customers[i].account_type=='L')
        {
            char type;
            printf("\nA.IF THE LOAN IS PERSONAL ---> INTEREST IS:18.5%");
            printf("\nB.IF THE LOAN IS HOUSING  ---> INTEREST IS:16%  ");
            printf("\nC.OTHER LOANS IS ------------> INTEREST IS:28%  ");
t:
            printf("\nEnter type of the loan: ");
            scanf(" %c",&type);
            customers[i].interest_rate=(type=='A' || type=='a')?A:(type=='B' || type=='b')?B:C;

            printf("\nAmount of the Loan Do you want:");
            scanf(" %f",&customers[i].amount);
            if((type=='A' || type=='a') && customers[i].amount>limitA)
            {
                printf("\nCan't take this amount of loan in this loan type.");
                goto t;
            }
            if((type=='B' || type=='b')&& customers[i].amount>limitB)
            {
                printf("\nCan't take this amount of loan in this loan type.");
                goto t;
            }
            if((type=='C' || type=='c') && customers[i].amount>limitC)
            {
                printf("\nCan't take this amount of loan in this loan type.");
                goto t;
            }
            int y;
            printf("\n1.1 year");
            printf("\n2.2 year");
            printf("\n3.3 year");
            printf("\n4.4 year");
            printf("\n5.5 year");
            printf("\nPayable years:");
            scanf( "%d",&y);
            customers[i].have_to_pay=(customers[i].amount*(customers[i].interest_rate/100)*y)+customers[i].amount;

        }
        fwrite(&customers[i],sizeof(account_holder),1,fi);

    }
    fclose(fi);
    free(customers);
}
void display()
{
  printf("Account No |       Name            |   Balance      | Gender | Type  | Loan Amount  | Full Payment    | Int Rate ");
    printf("\n-----------------------------------------------------------------------------------------------------");
    account_holder a;
    FILE *pi;
    pi = fopen("Account.txt", "r");
    if (pi == NULL)
    {
        printf("Error opening the file: %s\n","Account.txt" );
        return 1;
    }
    while (fread(&a, sizeof(account_holder), 1, pi))
    {
        printf("\n%-10s | %-20s | %16.3f | %-6s |   %c   |", a.account_no, a.name, a.balance, a.gender, a.account_type);
        if (a.amount != 0)
        {
            printf(" %11.3f | %15.3f | %3.1f", a.amount, a.have_to_pay, a.interest_rate);
        }
    }
    fclose(pi);

}
void ChangeProfile() //changing profile means the update of name and the gender of the account holder
{
    int found=0;
    char acc[10];
    printf("What Account no you want:");
    scanf(" %[^\n]",acc);
    account_holder a1;
    FILE *pi;
    FILE *t;
    pi=fopen("Account.txt","r");
    t=fopen("t.txt","a");
    if (pi == NULL)
    {
        printf("Error opening the file: %s\n", "Account.txt");
        return 1;
    }
    if (pi == NULL)
    {
        printf("Error opening the file: %s\n", "t.txt");
        return 1;
    }
    while(fread(&a1,sizeof(account_holder),1,pi))
    {
        if(!strcmp(acc,a1.account_no))
        {
            printf("\nHolders Name:%s",a1.name);
            printf("\nGender :%s",a1.gender);
            printf("\nCurrent Balance:%f",a1.balance);
            printf("\nAccount type:%c",a1.account_type);
            found=1;
            char name[50];
            char gender[10];
            printf("\nEnter holders new name:");
            scanf(" %[^\n]",name);
            printf("\nEnter holders new gender:");
            scanf(" %s",gender);
            strcpy(a1.name,name);
            strcpy(a1.gender,gender);
        }
        fwrite(&a1, sizeof(account_holder), 1, t);
    }

    if(found==0)
    {
        printf("\nThere is no such Account\n");
    }
    fclose(pi);
    fclose(t);
    remove("Account.txt");
    rename("t.txt","Account.txt");
    return ;
}
void Deposit_withDrowl()
{
    int found=0;
    char acc[10];
    printf("What Account no you want:");
    scanf(" %[^\n]",acc);
    account_holder a1;
    FILE *pi;
    FILE *t;
    pi=fopen("Account.txt","r");
    t=fopen("t.txt","a");
    if (pi == NULL)
    {
        printf("Error opening the file: %s\n","Account.txt");
        return 1;
    }
    if (t == NULL)
    {
        printf("Error opening the file: %s\n", "t.txt");
        return 1;
    }
    while(fread(&a1,sizeof(account_holder),1,pi))
    {
        if(!strcmp(acc,a1.account_no))
        {
            found=1;
            printf("\nAccount Found\n");
            int choice;
            printf("\n1.Deposit");
            printf("\n2.Withdrowl");
            printf("\nenter your choice:");
            scanf(" %d",&choice);
            if(choice==1)
            {
                float deposit;
                printf("\nEnter holders deposit amount :");
                scanf(" %f",&deposit);
                a1.balance+=deposit;
            }
            else
            {
                float withdrow;
                printf("\nEnter holders withdrawl amount :");
                scanf(" %f",&withdrow);
                if(withdrow>a1.balance || a1.balance-withdrow<500)
                {
                    printf("\nDo not have sufficient amount Try again.");
                    continue;
                }
                a1.balance-=withdrow;
            }
            printf("\n---------------------------------------------------------------------");
            printf("\nAccount No:%s",a1.account_no);
            printf("\nHolders Name:%s",a1.name);
            printf("\nGender :%s",a1.gender);
            printf("\nCurrent Balance:%f",a1.balance);
            printf("\nAccount type:%c",a1.account_type);
            if(a1.amount!=0)
            {
                printf("\nLoan Amount:%f",a1.amount);
                printf("\nLoan amount to pay future:%f",a1.have_to_pay);
                printf("\nLoan interest rate:%f\n",a1.interest_rate);
            }

        }
        fwrite(&a1, sizeof(account_holder), 1, t);
    }
    if(found==0)
    {
        printf("\nThere is no such Account\n");
    }
    fclose(pi);
    fclose(t);
    remove("Account.txt");
    rename("t.txt","Account.txt");
    return;
}
void  searchAccount()
{

    char acc[10];
    printf("What Account no you want:");
    scanf(" %[^\n]",acc);
    account_holder a1;
    FILE *pi;
    pi=fopen("Account.txt","r");
    if (pi == NULL)
    {
        printf("Error opening the file: %s\n", "Account.txt");
        return 1;
    }
    while(fread(&a1,sizeof(account_holder),1,pi))
    {
        if(!strcmp(acc,a1.account_no))
        {
            printf("\n---------------------------------------------------------------------");
            printf("\nAccount No:%s",a1.account_no);
            printf("\nHolders Name:%s",a1.name);
            printf("\nGender :%s",a1.gender);
            printf("\nCurrent Balance:%f",a1.balance);
            printf("\nAccount type:%c",a1.account_type);
            if(a1.amount!=0)
            {
                printf("\nLoan Amount:%f",a1.amount);
                printf("\nLoan amount to pay future:%f",a1.have_to_pay);
                printf("\nLoan interest rate:%f\n",a1.interest_rate);
            }
            return ;
        }
    }
    fclose(pi);
    printf("\nThere is no such Account\n");
    return ;
}
void loanBranch()
{
    int found=0;
    char acc[10];
loan:
    printf("What is the Account no you want:");
    scanf(" %[^\n]",acc);
    account_holder a1;
    FILE *pi;
    FILE *t;
    pi=fopen("Account.txt","r");
    t=fopen("t.txt","a");
    if (pi == NULL)
    {
        printf("Error opening the file: %s\n", "Account.txt");
        return 1;
    }
    if (t == NULL)
    {
        printf("Error opening the file: %s\n", "t.txt");
        return 1;
    }
    while(fread(&a1,sizeof(account_holder),1,pi))
    {
        found=1;
        if(!strcmp(acc,a1.account_no))
        {
            printf("\nAccount Found\n");
            int choice;
            printf("\n1.Apply for a Loan");
            printf("\n2.Pay for Loan");
            printf("\nenter your choice:");
            scanf(" %d",&choice);
            if(choice==1)
            {
                if(a1.account_type=='L')
                {
                    printf("\nYou already have a loan in this account please try again opening another account");
                    return;
                }
                a1.account_type='L';
                char type;
                printf("\nA.IF THE LOAN IS PERSONAL ---> INTEREST IS:18.5%");
                printf("\nB.IF THE LOAN IS HOUSING  ---> INTEREST IS:16%  ");
                printf("\nC.OTHER LOANS IS ------------> INTEREST IS:28%  ");

t:
                printf("\nEnter type of the loan: ");
                scanf(" %c",&type);
                a1.interest_rate=(type=='A')?A:(type=='B')?B:(type=='C')?C:0;

                printf("\nAmount of the Loan Do you want:");
                scanf(" %f",&a1.amount);
                if(type=='A' && a1.amount>limitA)
                {
                    printf("\nCan't take this amount of loan in this loan type.");
                    goto t;
                }
                if(type=='B' && a1.amount>limitB)
                {
                    printf("\nCan't take this amount of loan in this loan type.");
                    goto t;
                }
                if(type=='C' && a1.amount>limitC)
                {
                    printf("\nCan't take this amount of loan in this loan type.");
                    goto t;
                }
                int y;
                printf("\n1.1 year");
                printf("\n2.2 year");
                printf("\n3.3 year");
                printf("\n4.4 year");
                printf("\n5.5 year");
                printf("\nPayable years:");
                scanf("%d",&y);
                a1.have_to_pay=(a1.amount*(a1.interest_rate/100)*y)+a1.amount;

            }
            else
            {
                if(a1.account_type=='S')
                {
                    printf("You don't have any Loan to pay ");
                    printf("If you want a loan please enter (Y/N)")  ;
                    char e;
                    scanf(" %c",&e);
                    if(e=='y'|| e=='Y')
                    {
                        continue;
                    }
                    else
                    {
                        return;
                    }
                }

                float pay;
                printf("\nEnter holders pay amount :");
                scanf(" %f",&pay);
                a1.have_to_pay-=pay;
            }
            printf("\n---------------------------------------------------------------------");
            printf("\nAccount No:%s",a1.account_no);
            printf("\nHolders Name:%s",a1.name);
            printf("\nGender :%s",a1.gender);
            printf("\nCurrent Balance:%f",a1.balance);
            printf("\nAccount type:%c",a1.account_type);
            if(a1.amount!=0)
            {
                printf("\nLoan Amount:%f",a1.amount);
                printf("\nLoan amount to pay future:%f",a1.have_to_pay);
                printf("\nLoan interest rate:%f\n",a1.interest_rate);
            }

        }
        fwrite(&a1, sizeof(account_holder), 1, t);
    }
    if(found==0)
    {
        printf("\nThere is no such Account to Apply a loan please create a account.\n");
    }
    fclose(pi);
    fclose(t);
    remove("Account.txt");
    rename("t.txt","Account.txt");
    return;
}
void closeAccount()
{
    while(1)
    {
        int found=0;
        char acc[10];
        printf("What account you want to close:");
        scanf(" %[^\n]",acc);
        account_holder a1;
        FILE *pi;
        FILE *t;
        pi=fopen("Account.txt","r");
        t=fopen("t.txt","a");
        if (pi == NULL)
        {
            printf("Error opening the file: %s\n","Account.txt");
            return 1;
        }
        if (t == NULL)
        {
            printf("Error opening the file: %s\n","t.txt");
            return 1;
        }
        while(fread(&a1,sizeof(account_holder),1,pi))
        {
            if(!strcmp(acc,a1.account_no))
            {
                found=1;
                printf("\n------------------------------------------------------------------------------------------------------------");
                printf("\nAccount No:%s",a1.account_no);
                printf("\nHolders Name:%s",a1.name);
                printf("\nGender :%s",a1.gender);
                printf("\nCurrent Balance:%f",a1.balance);
                printf("\nAccount type:%c",a1.account_type);
                if(a1.have_to_pay!=0)
                {
                    printf("\nLoan Amount:%f",a1.amount);
                    printf("\nLoan amount to pay future:%f",a1.have_to_pay);
                    printf("\nLoan interest rate:%f\n",a1.interest_rate);
                    printf("\nYOU HAVE DEBTS YOU CAN NOT CLOSE THE ACCOUNT\n");
                }
                else
                {
                    printf("Successfully closed Account.\nYour balance is %f \n",a1.balance);
                    printf("\nThank you");
                     printf("\n---------------------------------------------------------------------\n");
                    continue;
                }

            }
            fwrite(&a1, sizeof(account_holder), 1, t);
        }
        if(found==0)
        {
            printf("\nThere is no such Account\n");
        }
        fclose(pi);
        fclose(t);
        remove("Account.txt");
        rename("t.txt","Account.txt");

        char d;
        printf("\n\n\nDo you want to close more accounts(Y/N):");
        scanf(" %c",&d);
        if(d=='y' || d=='Y')
        {
            continue;
        }
        return;
    }
}
