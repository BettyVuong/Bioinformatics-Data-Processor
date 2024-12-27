#include "givenA1.h"

int main(){
  int choice = 0;
  int feature = 0;
  char fName[30] = "a1Data.txt";
  struct Animal dataZoo[NUM_SAMPLES];
  int vector1[NUM_FEATURES] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1};
  int vector2[NUM_FEATURES] = {1,0,0,1,0,0,1,1,1,1,0,0,4,0,0,1};
  float ans = 0;
  int sol = 0;
  int k = 0;
  int funcChoice = 1;
  int kNearestNeighbors[NUM_SAMPLES];
  struct Animal testData[NUM_TEST_DATA];
  int i = 0;
  int index = 0;
  char fileLine[70];
  char *p;
  do {
    printf("\nPredict Me menu - enter a number between 1-9:\n\n");
    printf("1. Read info from data\n2. Calculate mean and mode from data");
    printf("\n3. Generate a histogram from data\n4. Euclidean distance\n");
    printf("5. Hamming distance of vectors\n6. Jaccard similarity");
    printf("\n7. Nearest neighbors\n8. Predicting class\n9. Accuracy calculation\n");
    //user input choice
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    //performing choice
    switch(choice){
      case 1:
        strcpy(fName, "a1Data.txt");
        readFromFile(fName, dataZoo);
        break;
      case 2:
        float mean;
        int mode;
        printf("Enter feature from 1-16: ");
        scanf("%d", &feature);
        //ensure that file is loaded first
        strcpy(fName, "a1Data.txt");
        readFromFile(fName, dataZoo);
        //call task 2
        generateStatisticsFeatureX(dataZoo, feature, &mean, &mode);
        printf("\nThe mean is %.2f and mode is %d", mean, mode);
        break;
      case 3:
        //ensure that file is loaded first
        strcpy(fName, "a1Data.txt");
        readFromFile(fName, dataZoo);
        //call task 3
        classDistribution(dataZoo);
        break;
      case 4:
        //ensures that file is loaded
        strcpy(fName, "a1Data.txt");
        readFromFile(fName, dataZoo);
        //call task 4
        ans = euclideanDistance(vector1, vector2);
        printf("\nThe Euclidean distance between two vectors is %.2f", ans);
        break;
      case 5:
        //ensures thar file is loaded
        strcpy(fName, "a1Data.txt");
        readFromFile(fName, dataZoo);
        //call task 5
        sol = hammingDistance(vector1, vector2);
        printf("\nThe hamming distance is %d", sol);
        break;
      case 6:
        //ensures that file is loaded
        strcpy(fName, "a1Data.txt");
        readFromFile(fName, dataZoo);
        //call task 6
        ans = jaccardSimilarity(vector1, vector2);
        printf("\nThe jaccard similarity is %.2f", ans);
        break;
      case 7:
        //ensures that file is loaded
        strcpy(fName, "a1Data.txt");
        readFromFile(fName, dataZoo);
        k = 8;
        //call task 7
        findKNearestNeighbors(dataZoo, vector1, k, funcChoice, kNearestNeighbors);
        printf("Here are the %d nearest neighbors: ", k);
        for(sol = 0; sol < k; sol++){
          printf("%d ", kNearestNeighbors[sol]);
        }
        break;
      case 8:
        //ensures that file is loaded
        strcpy(fName, "a1Data.txt");
        readFromFile(fName, dataZoo);
        //call task 7 in order to run task 8
        k = 8;
        findKNearestNeighbors(dataZoo, vector1, k, funcChoice, kNearestNeighbors);
        //testing purposes
        /*printf("kNeighbors from main: ");
        for(sol = 0; sol <k; sol++){
          printf("%d ", kNearestNeighbors[sol]);
        }*/
        //call task 8
        sol = predictClass(dataZoo, kNearestNeighbors, vector1, k);
        printf("\nPredicted class label: %d", sol);
        break;
      case 9:
        //ensures that file is loaded
        strcpy(fName, "a1Data.txt");
        readFromFile(fName, dataZoo);
        //loading the testData file into structs
        index = 0;
        strcpy(fName, "testData.csv");
        FILE *fptr = fopen(fName, "r");
        //ensures that file exists
        if(fptr == NULL){
          printf("\nFile doesn't exist");
          exit(1);
        }
        //populating array of structs
        while(fgets(fileLine, 70, fptr)){
          p = strtok(fileLine, ",");
          strcpy(testData[index].animalName, p);//copying name
          for(i = 0; i <NUM_FEATURES; i++){ //copying all features in the struct
            p = strtok(NULL, ",");
            testData[index].features[i] = atoi(p); //copying by parsing the string to an int
          }
          p = strtok(NULL, ",");
          testData[index].classLabel = atoi(p);
          //printf("\n%s %d %d %d", testData[index].animalName, testData[index].features[0], testData[index].features[1], testData[index].classLabel);
          index++;
        }
        fclose(fptr);
        //call task 9
        k = 4;
        ans = findAccuracy(dataZoo, testData, k);
        printf("\nAccuracy of the ML algorithm is: %.2f%%", ans);
        break;
      //continue for other tasks as you go
      default:
        printf("\nNumber entered is out of range");
        break;
    }
  } while (choice >= 1 && choice <= 9);
  return 0;
}
