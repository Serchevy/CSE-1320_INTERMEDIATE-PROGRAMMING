#include "wordle.h"

int main(int argc, char **argv) 
{
    /////////////////////////////////////////////
    if (argc != 2){
        printf("USSAGE: ./a.out \"FILENAME\"\n");
        return 1;
    }
    
    char *str = argv[1];
    
    if(load_words(str).num_words == 0){
        printf("Something went Wrong!\n");
        return 1; 
    }
    
    /*storing struct in a variable*/
    wordlist_t random = load_words(str);
    
    /*storing random word*/
    char *word = select_random_answer(random);
    
    char guess[6];
    char symbol[6] = { 0 }; /*array to store ^ or * according to comparison with guess*/
    int num_tries = 0;
    /*printf("%s\n", word);*/
    ////////////////////////////////////////////////
    
    while(num_tries < MAX_TRIES){
        printf("--------------------------------\n");
        printf("Enter your guess (%d left): ", MAX_TRIES - num_tries);
        fgets(guess, 6, stdin);
        while(getchar() != '\n');
        
        int num_correct = 0;
        
        for(int i = 0; i < 5; i++){
            if(guess[i] == word[i]){
                symbol[i] = '^';
                num_correct++;
            }
            else{
                symbol[i] = ' ';
            }
        }
        
        for(int i = 0; i < 5; i++){
            if(symbol[i] == ' '){
                for(int j = 0; j < 5; j++){
                    if(guess[i] == word[j]){
                        symbol[i] = '*';
                    }
                }
            }
        }
        printf("%s\n", guess);
        printf("%s\n", symbol);

        if(num_correct == 5){
            printf("%s is correct!\n", word);
            break;
        }
        num_tries++;
    }
    
    if(num_tries == 6){
        printf("Correct word was: \"%s\"\n", word);
    }
     
    /////////////////////////////////////////////
    /*Don't really knwo if this is how we had to free memory*/
    for (int i = 0; i < random.num_words; i++){
        free(random.words[i]);
    }
    free(random.words);
    /////////////////////////////////////////////
    
    return 0;
    
}


wordlist_t load_words(char *str)
{
    wordlist_t wordle = { 0 };
    
    FILE *fp = fopen(str, "r");
    
    if (!fp){
        printf("Erro! Unable to Open File...\n");
        return wordle;
    }
    
    char buffer[BUF_SIZE] = { 0 };
    
    while (fgets(buffer, BUF_SIZE, fp)){
        trim(buffer);
        wordle.words = realloc(wordle.words, sizeof(void *) * (wordle.num_words + 1));
        wordle.words[wordle.num_words] = malloc(strlen(buffer) + 1);
        strcpy(wordle.words[wordle.num_words++], buffer);
    }
    fclose(fp);
    
    return wordle;
    
}

void trim(char *buffer){
    int l = strlen(buffer);

    if (buffer[l-1] == '\n'){
        buffer[l-1] = 0;
    }
}

char* select_random_answer(wordlist_t random){
    time_t t = time(NULL);
    srand(t);
    
    int a = 0;
    int b = (random.num_words - 1);
    int index = rand() % (a - b) + a;

    char *rand_word = random.words[index];
    
    return rand_word;

}


