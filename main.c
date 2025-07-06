#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>


bool check_prime(int n) //function to check if a number is prime or not
{
    int count=0;
    //count is used to know how many times the number is divisible by any number from 1 to n-1
    for(int i=1;i<=n;i++)
    //this for loop is used to iterate from 1 to n
    {
        if(n%i==0) //condition to check is a number is divisible by i or not
        {
            count++;
        }
    } 
    //if count is 2 then it returns true otherwise false
    if(count==2)
    {
        return true; 
    }
    else
    {
        return false;
    }
}

//this function is created to find the greatest common divisor of a and b

int gcd(int a ,int b)
{
    if(b==0)
    return a;
    else
    return gcd(b,a%b);
}

//when the user don't know which e values are valid between 1 to n.

//this function is used to find the valid e values between 1 to n.

void e_values(int pi)
{
    for(int i=2;i<pi;i++)
    {

        // this conditon is used to check if gcd(i,pi) is equal to 1 or not

        if(gcd(i,pi)==1)
        {
            //this will print numbers with a tab space.

            printf("%d\t",i);

        }
    }
    //this \n is used to jump to next line
    printf("\n");
}

// this function is used to store n and e into a text file so that the sender can access.
void sender_store(int n,int e)
{
    FILE* a=fopen("sender_file.txt","w");

    //if the file is not exit then this will print this message.
    if(a==NULL)
    {
        printf("file not found");
        exit(1);
    }

    // it is in written mode so the if the file is not created it will create and store n and e.

    fprintf(a, "public key(n,e): (%d , %d)\n",n,e);
    fclose(a);

}


int generate_keys()
{
    int p,q,e,n,pi,temp;
    bool checkp,checkq;

    // reciever will eneter the first prime numebr.
    printf("\nenter your first prime number:\n");

    //it will store in p.
    scanf("%d",&p);

    checkp=check_prime(p);
    //the result of function check_prime first prime number will be stored in p.

    //reciver will enter his second prime number.
    printf("\nenter your second prime number:\n");
    //it will store in q.
    scanf("%d",&q);

    //the result of function check_prime on second prime number will be stored in q.
    checkq=check_prime(q);

    //this condition will check if the result of function of p and q is true then it will proceed.
    if(checkp==true && checkq==true)
    {
        //it will store multiplication value of p and q in n.
        n=p*q;
        pi=(p-1)*(q-1); 

        printf("enter your e value for public key among the give numbers:\n");
        // we will pass pi value to e_valeus functions
        e_values(pi);

        //after reciever enter a value it will store in e.
        scanf("%d",&e);

        //we will use d to iterate from 1 to pi
        for(int d=1;d<pi;d++)
        {
            //we will check if (d*e-1) is divisible by pi. and d is not equal to e. then only it will proceed
            if((d*e)%pi==1 && d!=e)
            {
                // d value will store into temp
                temp=d;
                break;
            }
        }
        // printf("\nplease enter a number between 1 and %d\n",pi);
        
        // if e value satisfy this condition then it will proceed.
        if(1<e && e<pi && gcd(e,pi)==1)
        {
            // this will print the public key to the reciever.

            printf("\npublic key is %d %d\n",n,e);

            //this print the private key to the reciever.
            printf("\nprivate key is %d %d\n",n,temp);

            //this will open a file and write the public key and private key in the file.
            FILE* fp=fopen("keys.txt","w");
            if(fp==NULL)
            {
                printf("file not found");
                exit(1);
            }
            //this will print p,q,n,public key and private key in the file.
            fprintf(fp, "p: %d\n", p);
            fprintf(fp, "q: %d\n", q);
            fprintf(fp, "n: %d\n", n);
            fprintf(fp, "phi(n): %d\n", pi);
            fprintf(fp, "public key(n,e): (%d , %d)\n",n,e);
            fprintf(fp, "private key(n,d): (%d , %d)\n",n,temp);

            //this will store the public into the sender file.
            sender_store(n,e);
            
            //this will close the file name fp.
            fclose(fp);
            //if everything run execute correctly.it will show keys are saved successfully.
            printf("keys are saved successfully");
        }
    else
        {
            //if the if condition if false then it will again recall the generate_keys function.
            generate_keys();
        }

    }
    else
    {
        //if the check primes condition function false then it will say to enter prime numbers.
        printf("\nplease enter prime numbers\n");
        //it will again recall the generate_keys function.
        generate_keys();

        return 0;
    }
}


void view_keys()
{
    char ch;
    //this will open a file and read and print everything from the file.

    FILE* fp=fopen("keys.txt","r");

    //this condition will check if the file is present or not.

    if(fp==NULL)
    {
        //if the file is not foud it will print this message.
        printf("file not found");
    }
    else
    {
        //this will read the elements till the end of the file.

        while((ch=fgetc(fp))!=EOF)
        {

            //it read the elements from the file and print them on the screen.
            putchar(ch);

        }
    }
    //this will close the file.

    fclose(fp);
}

//this function is used to decrypt the cipher message into original message.
void decrypt()
{
    // this open a file with an pointer fg and read the elements from the file.
    FILE* fg=fopen("sender_file.txt","r");

    // this open a file with an pointer fp and read the elements from the file.
    FILE* fp=fopen("keys.txt","r");
    if (fp==NULL)
    {
        printf("file not found");
    }
    if (fg==NULL)
    {
        printf("file not found");
    }
    int n,d,c;

    // this will read n and from the file.
    fscanf(fp, "%d %d", &n, &d);

    //this will read cipher number from the file.
    fscanf(fg,"%d",&c);

    int M;
    for(int i=0;i<d;i++)
    {
        //this will calculate the M value.

        M=(M*c)%n;

    }
    //this will close the file with pointer named fg.
    fclose(fg);
    //this will close the file with pointer named fp.
    fclose(fp);

    //this will print original message on the screen.
    printf("your decrpted message is : %d",M);
}


int main()
{
    int ch,choice;

    // we created a while never ends until the user choose to exit or there is a break statement.
    while(1)
    {
        // this will print the menu on the screen.
        printf("\n1.sender\n2.reciever\n3.exit\n");

        //the user need to enter his one choice.
        printf("\nenter you choice:\n");
        //user choice will be stored in ch.
        scanf("%d",&ch);

        //we use switch case statement here.
        switch(ch)
        {
            // this case belongs to sender.
            case 1:
            {
                break;
            }
            // this case belongs to reciever.
            case 2:
            printf("---reciever options----");
           printf("\n1.generate keys\n2.view keys\n3.exit\n");
            scanf("%d",&choice);
            switch(choice)
            {
                //this case used to create the public and private keys for the reciver.
                case 1:generate_keys();
                //this statement is used to break out of the while loop.
                break;

                // this case is used to show all the keys which stored in reciver text file.
                case 2:view_keys();
                //this statement is used to break out of the while loop.
                break;

                //this case is used to decrypt the cipher message.
                case 3:decrypt();
                //this statement is used to break out of the while loop.
                break;

                //this case will get us out of the loop.
                case 4:exit(0);

                default:printf("invalid choice. please try again");
                //this statement is used to break out of the while loop.
                break;
            }
            
            //this break statement we make us out of this while loop.
            break;

            // this case belongs to exit.
            case 3:exit(0);

            // this is default case if the user enter any other number.it will print this message.

            default:printf("\ninvalid choice. try again\n");
            break;
        }

    }
    //this will retun 0
    return 0;
}