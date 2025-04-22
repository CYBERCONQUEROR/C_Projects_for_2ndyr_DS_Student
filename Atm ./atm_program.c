#include<stdio.h>
#include<stdlib.h>
int main(){
    int choice , pin , enteredpin , accountnum ,ACCOUNTNUM, age , PhoneNo , attempt;
    float balance=5000 , withdraw , deposit  ;
    char name[50],address[50] ;
    printf("please fill given details\n");

    printf("what is your name:--\n");
    scanf("%49s",name);
    printf("what is your address:--\n");
    scanf("%49s",address);
    printf("what is your age:--\n");
    scanf("%d",&age);
    printf("Enter your PhoneNo.\n");
    scanf("%d",&PhoneNo);

    printf("Enter your accountnum.:--\n");
    scanf("%d",&accountnum);
    printf("Enter your pin:--\n");
    scanf("%d",&pin);
    printf("please select one option:--\n1.Login     2.Logout:--\n");
    scanf("%d",&choice);
    switch (choice) {
        case 1:
        printf("Congrulation! You have successfully login:--\n");
        break;
        case 2:
        printf("Sorry, You have no login:--\n");
        break;
    }
    if(choice==1){
    printf("Welcome to ATM Transition:--\n");
    printf("please enter your corret ACCOUNTNUM.:--\n");
    scanf("%d",&ACCOUNTNUM);
    if(ACCOUNTNUM==accountnum){
        printf("please enter your correct pin:--\n");
        scanf("%d",&enteredpin);
        if(enteredpin==pin){
            do{
            printf("ATM Menu\n");
            printf("1. Check Balance\n");
            printf("2. Withdraw\n");
            printf("3. Deposit\n");
            printf("4. Exit\n");
            printf("Enter your choice:--\n");
            scanf("%d",&choice);
            switch (choice){
                case 1:
                printf("Your current balance is:--%f\n",balance);
                break;
                case 2:
                printf("Enter amount to withdraw");
                scanf("%f",&withdraw);
                if(withdraw>balance){
                    printf("Insufficient balance\n");
                }
                else if(withdraw<=0){
                    printf("Invalid amount\n");
                }
                else{
                    balance=balance-withdraw;
                    printf("withdraw successful\n");
                }
                break;
                case 3:
                printf("Enter amount to deposit");
                scanf("%f",&deposit);
                if(deposit<0){
                    printf("Invalid amount\n");
                }
                else{
                    balance=balance+deposit;
                    printf("Deposit successful\n");
                }
                break;
                case 4:
                printf("Thank you for using our ATM\n");
                break;
            }
            }
            while(choice!=4);
        }
        else{
            printf("Incorrect PIN\n");
        }
    }
    else{
        printf("Invalid account number\n");
    }
    }
    else if(choice==2){
        printf("You are logout!!");
    }
    else{
        printf("Invalid choice\n");
    }
}