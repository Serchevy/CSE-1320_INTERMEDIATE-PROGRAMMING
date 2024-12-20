#include "iris.h"

int main(int argc, char *argv[]) 
{
    // Make sure the inputs from command line are correct
    if (argc != 2) 
    {
        printf("USSAGE: ./a.out \"FILENAME\"\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    //Verify if file opens correctly
    if (!fp) 
    {
        printf("Erro! Unable to Open File...\n");
        return 1;
    }

    char buffer[BUF_SIZE] = { 0 };
    int num_samples = 0;
    int num = 0;

    iris_t data[MAX_SAMPLES] = { 0 };

    while (fgets(buffer, BUF_SIZE, fp)) 
    {
        trim(buffer);
        data[num_samples++] = parse_line(buffer);
    }
    
    printf("Please Type Number as a Selection\n  1. List dataset\n  2. Compare Averge Statistics\n  3. Quit\n");
    scanf("%d", &num);
    // If statemets for fomatting and logic
    if(num == 1)
    {
        printf("Sepal Length   Sepal Width   Petal Length   Petal Width   Species\n");
        printf("---------------------------------------------------------------------\n");
        for(int i = 0; i < num_samples; i++) 
            {
                printf("%-14.1f %-13.1f %-14.1f %-13.1f %s\n", data[i].sepal_length, data[i].sepal_width, data[i].petal_length, data[i].petal_width, data[i].name);
            }
    }
    else if(num == 2)
    {
        float sum, sum2, sum3, sum4;
        for(int i = 0; i < num_samples; i++)
        {
            sum += data[i].sepal_length;
            sum2 += data[i].sepal_width;
            sum3 += data[i].petal_length; 
            sum4 += data[i].petal_width; 
        }
        printf("Sepal Length   Sepal Width   Petal Length   Petal Width\n");
        printf("-------------------------------------------------------\n");
        printf("%-14.2f %-13.2f %-14.2f %-13.2f\n", sum/num_samples, sum2/num_samples, sum3/num_samples, sum4/num_samples);
        
    }
    else //(num == 3)
    {
        return 1;
    }

    fclose(fp);

    return 0;
}

// Tokinize data
iris_t parse_line(char *csv_line) 
{
    iris_t sample = { 0 };
    int num_feature = 0;

    char *token = strtok(csv_line, ",");

    while (token) 
    {
        switch (num_feature) 
        {
            case 0:
                sample.sepal_length = atof(token);
                break;
            case 1:
                sample.sepal_width = atof(token);
                break;
            case 2:
                sample.petal_length = atof(token);
                break;
            case 3:
                sample.petal_width = atof(token);
                break;
            case 4:
                strcpy(sample.name, token);
                break;
            default:
                printf("no\n");
        }
        num_feature++;
        token = strtok(NULL, ",");
    }

    return sample;
}

//Get rid off new line character in extracted strings
void trim(char *str) 
{
    int l = strlen(str);

    if (str[l-1] == '\n') 
    {
        str[l-1] = 0;
    }
}

