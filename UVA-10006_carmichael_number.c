#include<stdio.h>
#include<math.h>

int check_prime(int primes[],int len,int NUM){
    for(int i=0;i<=len;i++){
        if(NUM == primes[i]){
            return 1;
        }
    }
    return 0;
}

int FermatTest(int NUM){
    int i=2;
    for(i;i<NUM;i++){
        int expo = 1;
        int total_expo_count = 0;
        int len = 0;
        int record[1000] = {0};
        long long int multi = i%NUM;
        int check_exceed = 0;
        while(expo < NUM){
            record[len] = multi;
            len++;
            multi = (multi*multi)%NUM;
            expo*=2;
        }
        expo/=2;
        multi = 1;
        len--;
        while(len >= 0){
            while(total_expo_count+expo<=NUM){
                total_expo_count += expo;
                multi = (multi*record[len])%NUM;
            }
            len--;
            expo/=2;
        }
        if(multi != i){
            return 0;
        }
    }
    return 1;
}

void CarMichael_NUM(int NUM){
    static int primes_count[32500] = {2};
    static int count = 0;
    if(primes_count[count] < NUM){
        for(int i=primes_count[count];i<=NUM;i++){
            for(int j=0;j<=count;j++){
                if(i%primes_count[j] == 0){
                    break;
                }else if(j == count){
                    count++;
                    primes_count[count] = i;
                }
            }
        }
    }
    if(check_prime(primes_count,count,NUM)){
        printf("%d is normal.\n",NUM);
    }else{
        if(FermatTest(NUM)){
            printf("The number %d is a Carmichael number.\n",NUM);
        }else{
            printf("%d is normal.\n",NUM);
        }
    }

}



int main(void)
{
    int NUM;
    while(scanf("%d",&NUM)){
        if(!NUM){
            break;
        }
        CarMichael_NUM(NUM);
    }
    return 0;
}
