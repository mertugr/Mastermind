#include <iostream>
#include <ctime>    //for rand function

using namespace std;

void generateRandomNumber( char secretNumber[],int N) {
    int NorC; //randomly choosing number or char digit
    bool usedDigits[N] = {false}; // Array to keep track of used digits

    // Generate the first character to be a digit or a lowercase letter
    //its seperate for prevent it from being 0
    NorC = rand() % 2 + 1; // Choose between digit and letter
    if (NorC == 1)//if digit
        secretNumber[0] = rand() % 9 + 49; // ASCII for digits '1' to '9'
    else if (NorC == 2)//if letter
        secretNumber[0] = rand() % 5 + 97; // ASCII for lowercase letters 'a' to 'e'

    if (secretNumber[0] >= '0' && secretNumber[0] <= '9')//if its digit
        usedDigits[secretNumber[0] - '0'] = true; //add it to the usedDigits array
    else //if its lowercase letter
        usedDigits[secretNumber[0] - 'a'] = true; //add it to the usedDigits array

    for (int i = 1; i < N; ++i) //other digits
        {
        NorC = rand() % 2 + 1; // Choose between digit and letter

        if (NorC == 1)//if digit
            {
            int digit;
            do {
                digit = rand() % 10; //choosing random number
            } while (usedDigits[digit]); //if used generating random again
            secretNumber[i] = digit + '0'; //adding it to the secret number
            usedDigits[digit] = true; //for track if its used
        }
        else if (NorC == 2)//if its letter
         {
            char letter;
            do {
                letter = rand() % 5 + 'a';// 'a' to 'e'
            } while (usedDigits[letter - 'a']);
            secretNumber[i] = letter; //adding it to the secret number
            usedDigits[letter - 'a'] = true; //for track if its used
        }
    }
  secretNumber[N] = '\0'; //making last element \0 to finish the array
}

void play(char secret[], int N){
        char input[N+1];
        int exactCounter=0;
        int misplacedCounter=0;
        int tries=1;

        //cout << "Random number with " << N << " digits: " << secret << endl;
        cout<<"Make your guess"<<endl;
        while(1){
             cin>>input;
              int size = 0;
        while(input[size] != '\0') //getting input size to check if its equal or not to secretNumber size
            {
                size++;
            }
            if(size != N)
            {
                cout << "E1" << endl;
                exit(1);
            }
             for(int i = 0; i < N; ++i){
                if(input[i] < '0' || (input[i] > '9' && input[i] < 'a') || input[i] > 'e')
                {
                cerr << "E0" << endl;
                exit(1);
                }
            }
                for(int i=0;i<N;i++){
                    if(input[i]==secret[i])
                        exactCounter++;
                    for(int k=0;k<N;k++){
                        if((input[k]==secret[i])&&(input[i]!=secret[i]))
                            misplacedCounter++;
                    }
                }
                if(exactCounter==N){
                    cout<<"FOUND "<<tries<<endl;
                    break;
               }
                cout<<exactCounter<<"  "<<misplacedCounter<<endl;

                //Reseting counters for new try
                exactCounter=0;
                misplacedCounter=0;
                tries++;
                if(tries==101)
                    {
                    cout<<"FAILED"<<endl;
                    exit(-1);
                    }
        }
}

int main(int argc, char* argv[]){
srand(time(nullptr)); //For generate random number for every run
 if(argc != 3 || (argv[1][1] != 'r' && argv[1][1] != 'u'))
    {
        cerr << "E0" << endl;
        exit(1);
    }
     char option = argv[1][1]; //to determine option r or u

       if (option == 'r') {
        int N = atoi(argv[2]); //getting N info

         if (N == 0 && argv[2][0] != '0')  //checking if its not integer
            {
            cerr <<"E2"<<endl;
            exit(1);
            }

        else if(N>15 || N<1)
            {
            cerr<<"E0"<<endl;
            exit(1);
            }

        char secret[N];
        generateRandomNumber(secret,N);
        play(secret,N);
       }
         else if (option == 'u') {
        // Using the provided secret number

        int N = 0;
        while(argv[2][N] != '\0') //getting secretNumber size
            {
                N++;
            }
            if(argv[2][0]=='0')
                    {
                    cerr << "E0"<< endl;
                    exit(1);
                    }
            for(int i=1;i<N;i++) //checking digits of the number followed by -u are unique or not.
            {
                for(int j=0;j<i;j++)
                    if(argv[2][j]==argv[2][i])
                    {
                    cerr << "E0"<< endl;
                    exit(1);
                    }
                if (!((argv[2][i] >= '0' && argv[2][i] <= '9') || (argv[2][i] >= 'a' && argv[2][i] <= 'e')))
                    {
                    cerr << "E0"<< endl;
                    exit(1);
                    }


            }
            char secret[N+1];
            for(int i=0;i<N;i++){
             secret[i] = argv[2][i];
            }
            secret[N] = '\0'; //making last element \0 to finish the array
        play(secret,N);
    }
     else
        {
        cerr << "E0"<< endl;
        exit(1);
        }

    return 0;
}
