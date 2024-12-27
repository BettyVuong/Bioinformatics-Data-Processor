#include "givenA1.h"

// task 1
int readFromFile(char fName[30], struct Animal dataZoo[NUM_SAMPLES]){
  int index = 0;
  int i = 0;
  FILE *fptr = fopen(fName, "r");
  //ensures file exists
  if (fptr == NULL){
    printf("\nFile doesn't exist");
    return -1;
  }
  //populating structs
  while(!feof(fptr)){
    fscanf(fptr, "%s", dataZoo[index].animalName);
    for (i = 0; i < NUM_FEATURES; i++){
      fscanf(fptr, "%d", &dataZoo[index].features[i]);
    }
    fscanf(fptr, "%d", &dataZoo[index].classLabel);
    index++;
  }
  fclose(fptr);
  return 1; // function ran successfully
}

// task 2
int generateStatisticsFeatureX(struct Animal dataZoo[NUM_SAMPLES], int whichFeature, float * mean, int * mode){
  float sum = 0;
  float value = 0;
  int i = 0;
  //checking if feature is within the valid parameters
  if (whichFeature < 1 || whichFeature > 16){
    return -1;
  }
  //calculate mean of the feature
  for(i = 0; i < NUM_SAMPLES; i++){
    value = (float)dataZoo[i].features[whichFeature-1];
    sum = sum+value;
  }
  *mean = sum/NUM_SAMPLES;
  //calculating mode
  *mode = -1;
  int maxCount = 0; //count tracker max for mode comparison
  int count = 0; //count tracker
  int traverseInd = 0;//looks at every index for counting
  //looping to find the mode of the feature
  for(i = 0; i < NUM_SAMPLES; i++){
    //looping to find the amount of occurences of a specific index
    for(traverseInd = 0; traverseInd < NUM_SAMPLES; traverseInd++){
      if(dataZoo[i].features[whichFeature-1] == dataZoo[traverseInd].features[whichFeature-1]){
        count++;
      }
    }
    //comparing to see if there's a new mode
    if (maxCount < count){
      *mode = dataZoo[i].features[whichFeature-1];
      maxCount = count;
      }
    count = 0; //set to zero to find the other occurences
  }
  //check if there is a mode
  if (maxCount == 1){
    *mode = -1;
  }
  //testing purposes
  //printf("\nmean %f\nmode %d", *mean, *mode);
  return 1;
}

//task 3
void classDistribution(struct Animal dataZoo[NUM_SAMPLES]){
  int class1 = 0;
  int class2 = 0;
  int class3 = 0;
  int class4 = 0;
  int class5 = 0;
  int class6 = 0;
  int class7 = 0;
  int i = 0;
  //counting the number of occurences of each class
  for(i = 0; i < NUM_SAMPLES; i++){
    if(dataZoo[i].classLabel == 1){
      class1++;
    } else if (dataZoo[i].classLabel == 2){
      class2++;
    } else if (dataZoo[i].classLabel == 3){
      class3++;
    } else if (dataZoo[i].classLabel == 4){
      class4++;
    } else if (dataZoo[i].classLabel == 5){
      class5++;
    } else if (dataZoo[i].classLabel == 6){
      class6++;
    } else if (dataZoo[i].classLabel == 7){
      class7++;
    } else {
      printf("\nClass label doesn't exist");
    }
  }
  //finding the largest class
  int indSet = 0;
  int maxRow = 0;
  for (i = 0; i < NUM_CLASSES; i++){
    if(i == 0){
      indSet = class1;
    } else if(i == 1){
      indSet = class2;
    } else if(i == 2){
      indSet = class3;
    } else if(i == 3){
      indSet = class4;
    } else if (i == 4){
      indSet = class5;
    } else if(i == 5){
      indSet = class6;
    } else if(i == 6){
      indSet = class7;
    }
    //finding the max row count
    if(maxRow < indSet){
      maxRow = indSet;
    }
  }
  //maxRow++; //extra num added for histogram printing purposes
  //declraing an array for the histogram based on the data
  char histogram[maxRow+1][7];
  //loading array with data * count
  //class 1
  for(i = maxRow -1; i >= 0; i--){
    if( i > class1){
      histogram[i][0] = ' ';
    } else {
      histogram[i][0] = '*';
    }
  }
  //class 2
  for(i = maxRow - 1; i >= 0; i--){
    if (i > class2){
      histogram[i][1] = ' ';
    } else {
      histogram[i][1] = '*';
    }
  }
  //class 3
  for(i = maxRow -1;i>= 0; i--){
    if(i > class3){
      histogram[i][2] = ' ';
    } else {
      histogram[i][2] = '*';
    }
  }
  //class 4
  for(i = maxRow-1; i >= 0; i--){
    if(i > class4){
      histogram[i][3] = ' ';
    } else {
      histogram[i][3] = '*';
    }
  }
  //class 5
  for(i = maxRow-1; i >=0; i--){
    if(i > class5){
      histogram[i][4] = ' ';
    } else {
      histogram[i][4] = '*';
    }
  }
  //class 6
  for(i = maxRow -1; i >=0; i--){
    if(i > class6){
      histogram[i][5] = ' ';
    } else {
      histogram[i][5] = '*';
    }
  }
  //class 7
  for(i = maxRow-1; i >=0; i--){
    if(i > class7){
      histogram[i][6] = ' ';
    } else {
      histogram[i][6] = '*';
    }
  }
  //printing the histogram
  int col = 0;
  for(i = maxRow-1; i >= 0; i--){
    for(col = 0; col < NUM_CLASSES; col++){
      //printing the value
      printf("    %c    ", histogram[i][col]);
    }
    printf("\n");
  }
  printf(" Class 1  Class 2  Class 3  Class 4  Class 5  Class 6  Class 7\n");
}

//task 4
float euclideanDistance(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]){
  int sum = 0;
  double sumSqr = 0;
  float euclideanCalc = 0;
  int index = 0;
  for(index = 0; index < NUM_FEATURES; index++){
    sumSqr = (double)(vector1[index]-vector2[index]);
    sum = sum+pow(sumSqr, 2);
  }
  //squareroots the value
  euclideanCalc = (float)(sqrt(sum));
  return euclideanCalc;

}

//task 5
int hammingDistance(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]){
  int i = 0;
  int difference = 0;
  //finding the difference between vector1 and vector2
  for(i = 0; i < NUM_FEATURES; i++){
    if(vector1[i] != vector2[i]){
      difference++;
    }
  }
  return difference;
}

//task 6
float jaccardSimilarity(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]){
  float zMatch = 0;
  float nMatch = 0;
  float jSCalc = 0;
  int i = 0;
  //finding the matches
  for(i = 0; i < NUM_FEATURES; i++){
    //checking if the vectors match
    if(vector1[i] == vector2[i]){
      //checking if it's a 0-0 match
      if(vector1[i] == 0 && vector2[i] == 0){
        zMatch++;
      } else {
        nMatch++;
      }
    }
  }
  //testing purposes
  //printf("\nz = %f n = %f", zMatch, nMatch);
  //calculating jaccard similarity
  zMatch = (float)NUM_FEATURES-zMatch;
  jSCalc = (nMatch/zMatch);
  return jSCalc;
}

//task 7
void findKNearestNeighbors(struct Animal dataZoo[NUM_SAMPLES], int newSample[NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors[NUM_SAMPLES]){
  int i = 0;
  int j = 0;
  int temp = 0;
  float calcData[NUM_SAMPLES]; //dummy array used to sub and sort
  //int indSort[NUM_SAMPLES]; used during sort for indices
  //loading calculated data according to the distance function called
  for (i = 0; i < NUM_SAMPLES; i++){
    //Euclidean distance
    if(whichDistanceFunction == 1){
      calcData[i] = euclideanDistance(newSample, dataZoo[i].features);
    } else if (whichDistanceFunction == 2){ //Hamming Distance
      calcData[i] = (float)hammingDistance(newSample, dataZoo[i].features);
    } else if (whichDistanceFunction == 3){ //Jaccard's similarity
      calcData[i] = (float)jaccardSimilarity(newSample, dataZoo[i].features);
    } else{ //case is out of bounds
      printf("\nNot a valid choice");
    }
  }
  //loading array with index placement
  for(i = 0; i < NUM_SAMPLES; i++){
    kNearestNeighbors[i] = i+1;
  }
  //sorting arrays using bubble sort
  //OpenAI. (2024). ChatGPT (January 2022 version) [Large language model].
  //	https://chat.openai.com/c/6f55cd94-2557-4a45-91c2-5e259915d42b
  for( i = 0; i<NUM_SAMPLES - 1; i++){
    for(j = 0; j < NUM_SAMPLES - 1; j++){
      if(calcData[j] > calcData[j+1]){
        //swaping dummy array
        temp = calcData[j];
        calcData[j] = calcData[j+1];
        calcData[j+1] = temp;
        //swapping for indices
        temp = kNearestNeighbors[j];
        kNearestNeighbors[j] = kNearestNeighbors[j+1];
        kNearestNeighbors[j+1] = temp;
      }
    }
  }
}

//task 8
int predictClass(struct Animal dataZoo[NUM_SAMPLES], int neighborsForNewSample[NUM_SAMPLES], int newSample[NUM_FEATURES], int k){
  
