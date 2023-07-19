#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define A 18.5  //for 10 year
#define B 16    //for 5 year
#define C 28    //for 15 year
void open();
void display();
char ChangeProfile();
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
    while(1)
    {
        printf("\n\n---------------------Welcome to CDB bank Management System------------------\n\n");
        printf("01.Open Accounts\n");
        printf("02.Display Accounts\n");
        printf("03.Change Personal Data\n");
        printf("04.Deposit / Withdrawal \n");
        printf("05.Search for special account details\n");
        printf("06.Pay for a Loan / Get A Loan\n");
        printf("07.Close Account");// User can close account if he/she dont have any loan to pay
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
            exit(0);
        }

    }
}
void open()
{
    int n_acc;
    FILE *fi;
    printf("\nHow many accounts do you want to open:");
    scanf("%d",&n_acc);
    account_holder* customers;
    customers=(account_holder*)calloc(n_acc,sizeof(account_holder));
    fi=fopen("Account.txt","a");

    for(int i=0; i<n_acc; i++)
    {
        printf("\nEnter Account NO:");
        scanf(" %s",customers[i].account_no);
        printf("\nEnter holders name:");
        scanf(" %[^\n]",customers[i].name);
        printf("\nEnter holders gender:");
        scanf(" %s",customers[i].gender);
        printf("\nEnter holders balance:");
        scanf(" %f",&customers[i].balance);
        printf("\nEnter Account Type:(Saving Account---(S)/Loan Account---(L):");
        scanf(" %c",&customers[i].account_type);
        toupper(customers[i].account_type);
        if(customers[i].account_type=='L')
        {
            char type;
            printf("\nAmount of the Loan Do you want:");
            scanf(" %f",&customers[i].amount);
            printf("\nAmount to pay:");
            scanf(" %f",&customers[i].have_to_pay);

            printf("\nA.IF THE LOAN IS PERSONAL ---> INTEREST IS:18.5%");
            printf("\nB.IF THE LOAN IS HOUSING  ---> INTEREST IS:16%  ");
            printf("\nC.OTHER LOANS IS ------------> INTEREST IS:28%  ");
            printf("\nEnter type of the loan: ");
            scanf(" %c",&type);
            customers[i].have_to_pay=customers[i].amount*type*10+customers[i].amount;

            customers[i].interest_rate=(type=='A')?A:(type=='B')?B:(type=='C')?C:0;


        }
        fwrite(&customers[i],sizeof(account_holder),1,fi);
        fclose(fi);
        free(customers);
    }
}
void display()
{
    printf("hello");
    account_holder a;
    FILE *pi;
    pi=fopen("Account.txt","r");
    while(fread(&a,sizeof(account_holder),1,pi))
    {
        printf("\n%-10s| %-20s | %-15.2f | %-10s | %-10c  |",a.account_no,a.name,a.balance,a.gender,a.account_type);
        if(a.amount!=0)
        {
            printf("  %10.4f  |  %15.4f | %6.2f  |",a.amount,a.have_to_pay,a.interest_rate);
        }
    }
    fclose(pi);

}
char ChangeProfile() //changing profile means the update of name and the gender of the account holder
{
    char found;
    char acc[10];
    printf("What Account no you want:");
    scanf(" %[^\n]",acc);
    account_holder a1;
    FILE *pi;
    pi=fopen("Account.txt","r");
    while(fread(&a1,sizeof(account_holder),1,pi))
    {
        if(!strcmp(acc,a1.account_no))
        {
            printf("\nEnter holders name:");
            scanf(" %[^\n]",a1.name);
            printf("\nEnter holders gender:");
            scanf(" %s",a1.gender);
            found='y';
            return found ;
        }
    }
    found='n';
    printf("\nThere is no such Account\n");
    fclose(pi);
    return found;
}
void Deposit_withDrowl()
{
    char acc[10];
    printf("What Account no you want:");
    scanf(" %[^\n]",acc);
    account_holder a1;
    FILE *pi;
    pi=fopen("Account.txt","r");
    while(fread(&a1,sizeof(account_holder),1,pi))
    {
        if(!strcmp(acc,a1.account_no))
        {
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
                a1.balance+=withdrow;
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
            return 0;
        }
    }
    printf("\nThere is no such Account\n");
    fclose(pi);
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
    printf("\nThere is no such Account\n");
    return ;
}
void loanBranch()
{
    char acc[10];
  loan: printf("What Account no you want:");
    scanf(" %[^\n]",acc);
    account_holder a1;
    FILE *pi;
    pi=fopen("Account.txt","r");
    while(fread(&a1,sizeof(account_holder),1,pi))
    {
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
              if(a1.account_type=='S'){
                   printf("You don't have any Loan to pay ");
                   printf("If you want a loan please enter (Y/N)")  ;
                   char e;
                   scanf(" %c",&e);
                   if(e=='y'|| e=='Y'){
                       continue;
                   }
              }
                a1.account_type='L';
                char type;
                printf("\nAmount of the Loan Do you want:");
                scanf(" %f",&a1.amount);
                printf("\nAmount to pay:");
                scanf(" %f",&a1.have_to_pay);
                printf("\nA.IF THE LOAN IS PERSONAL ---> INTEREST IS:18.5%");
                printf("\nB.IF THE LOAN IS HOUSING  ---> INTEREST IS:16%  ");
                printf("\nC.OTHER LOANS IS ------------> INTEREST IS:28%  ");
                printf("\nEnter type of the loan: ");
                scanf(" %c",&type);
                a1.interest_rate=type;
            }
            else
            {
                float pay;
                printf("\nEnter holders payl amount :");
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
            return 0;
        }
    }
    printf("\nThere is no such Account to Apply a loan please create a account.\n");
    fclose(pi);
    return;
}
void closeAccount(){

     char acc[10];
    printf("What account you want to close:");
    scanf(" %[^\n]",acc);
    account_holder a1;
    FILE *pi;
    pi=fopen("Account.txt","r");
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
                printf("\nYOU HAVE DEBTS YOU CAN NOT CLOSE THE ACCOUNT\n");
            }else{
             printf("Successfully closed Account.\n%f is your balance\n",a1.balance);
             printf("Thank you");
            }
            return ;
        }
    }
    printf("\nThere is no such Account\n");
    return ;
}
