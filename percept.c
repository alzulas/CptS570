//Leah Zulas
//Perceptron Algorithm and Passive Aggressive Algorithm
//CptS 570 Machine Learning
//Fall 2015

// basic file operations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main () {
  FILE * pFile, *pFile2;
  long lSize;
  char * buffer, *buffer2;
  size_t result;
  char *token;
  char *token2;
  int arrayNum = 0, numMistakes = 0, numExamples = 0;//, j = 0; 
  double sum = 0.0, prediction = 0.0, sumArray = 0.0;//, tau = 1.0;
  double myArray[124];
  char* linePointer;
  char* inLinePointer;
  double weightArray[124];
  double tau[124];
  int mistakeArray[100], mistakeArray2[100];
  double denominator = 0;
  double c[124];

  bzero(c, sizeof(double)*124);
  bzero(weightArray, sizeof(double)*124);
  bzero(myArray, sizeof(double)*124);
  bzero(tau, sizeof(double)*124);
  bzero(mistakeArray, sizeof(int)*100);
  bzero(mistakeArray2, sizeof(int)*100);


  for (int i = 0; i < 124; i++){
    tau[i] = 1;
    c[i] = 1;
  }


  pFile = fopen ( "train.txt" , "rb" );
  if (pFile==NULL) { 
  	printf("File error\n"); 
  	exit (1);
  }

  for (int trials = 0; trials < 101; trials ++)
  {
    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {
    	printf ("Memory error \n"); 
    	exit (2);
    }
    //printf("allocated=%ld\n", lSize); exit(1);
    // copy the file into the buffer:
    
    result = fread (buffer,1,lSize,pFile);
    
    if (result != lSize) {
    	printf("Reading error\n"); 
    	exit (3);
    }
    else
    {
    	//printf("can't token\n");
      linePointer=0;
      inLinePointer=0;
    	token = strtok_r(buffer, " ", &linePointer);
    	//printf("got a token\n");
     	/* walk through other tokens */
     	//int firsten=0;
      while( token != NULL ) 
      {
        //printf("token=|%s|\n",token);
        //printf("%d\n",firsten++);
    		//printf("in while token\n");
    		bzero(myArray, sizeof(double)*124);
    		//printf("bzero didn't fail\n");
        if (strcmp(token, "+1") != 0 || strcmp(token, "-1") != 0)
        {
      		//printf("+1\n");
      		
        		myArray[0] = atoi(token);
        		token = strtok_r(NULL, " ", &linePointer);//get next
            //printf("token=|%s|\n",token);
        }

        //printf( " %s\n", token );

    		while (token!=NULL && strstr(token, "\n") == NULL)
    		{
          //printf("token=|%s|\n",token);
    			token2 = strtok_r(token, ":", &inLinePointer);
    			arrayNum = atoi(token2);
    			if (arrayNum<=0 || arrayNum >123) 
          {
            printf("oops arrayNum=%d",arrayNum);
          }
    			else 
          { 
            myArray[arrayNum] = 1;
          }
    			//printf("arrayNum = %d\n", arrayNum);
    			
    			token = strtok_r(NULL, " ", &linePointer);

    			//inLinePointer = 0;
    		}
        //denominator = 0;
        for (int i = 1; i < 124; i++){ //calculate prediction
           sum += c[i]*weightArray[i]*myArray[i];//*tau[i]; array should be all weights for all 100 trials c
           //denominator += pow(myArray[i], 2.0);
           //printf("%f, %f, %f \n", weightArray[i], myArray[i], sum);
        }
        //sum = sum + sumArray ;
        prediction = sum * myArray[0]; //calculated prediction
        //printf("prediction = %f\n", prediction);
        if (prediction <= 0){ //Mistake happened, change weights
          for (int i = 1; i < 124; i++){
            weightArray[i] = weightArray[i] + (myArray[0]*myArray[i]);//w + tau * yt * xt = new weight
            //tau[i] = 1 - (myArray[0]*(weightArray[i]*myArray[i]))/(denominator);//yt((wt*xt))/||x||2
            if (tau[i] <= 0)
            {
              tau[i] = 0.0;
            }
            //printf("%f \n", tau[i]);
            c[i] += 1;
          }
          numMistakes++;
          //printf("Mistake\n");
        }
        else {
        for (int i = 0; i < 124; i++){
        c[i] = 1;
        }}
        prediction = 0.0;
        sum = 0.0;
    	// printf("Array= ");
    	// for(int i = 0; i < 124; i ++){
    	// 	//if (myArray[i]>0 || myArray[i]==-1) { printf("%d=%d ", i,myArray[i]); }
    	// 	printf("%f ", weightArray[i]);
    	// }
      numExamples++;
    	//printf("\n");
      printf("Mistakes = %d\n", numMistakes);
      printf("Examples = %d\n", numExamples);
      // char f;
      // scanf("%c", &f);



        //token = strtok_r(NULL, " ", &linePointer);
        //if (firsten++ > 10) {break;} //exit out after first ten results
      }
    }
    mistakeArray[trials] = numMistakes;
    numMistakes = 0;
    numExamples = 0;
    denominator = 0;
    //token = strtok_r(buffer, " ", &linePointer);
    //linePointer = 0;
    //inLinePointer = 0;
  }
  printf("Array= ");
  for(int i = 0; i < 100; i ++){
       //if (myArray[i]>0 || myArray[i]==-1) { printf("%d=%d ", i,myArray[i]); }
      printf("%d \n", mistakeArray[i]);
  }
  printf("\n");
  char f;
  scanf("%c", &f);
  fclose (pFile);
  free (buffer);

  pFile2 = fopen ( "test.txt" , "rb" );
  if (pFile2==NULL) { 
    printf("File error\n"); 
    exit (1);
  }
  for (int trials = 0; trials < 101; trials ++)
  {
    // obtain file size:
    fseek (pFile2 , 0 , SEEK_END);
    lSize = ftell (pFile2);
    rewind (pFile2);

    // allocate memory to contain the whole file:
    buffer2 = (char*) malloc (sizeof(char)*lSize);
    if (buffer2 == NULL) {
      printf ("Memory error \n"); 
      exit (2);
    }
    //printf("allocated=%ld\n", lSize); exit(1);
    // copy the file into the buffer:
    
    result = fread (buffer2,1,lSize,pFile2);
    
    if (result != lSize) {
      printf("Reading error\n"); 
      exit (3);
    }
    else
    {
      //printf("can't token\n");
      linePointer=0;
      inLinePointer=0;
      token = strtok_r(buffer2, " ", &linePointer);
      //printf("got a token\n");
      /* walk through other tokens */
      //int firsten=0;
      while( token != NULL ) 
      {
        //printf("token=|%s|\n",token);
        //printf("%d\n",firsten++);
        //printf("in while token\n");
        bzero(myArray, sizeof(double)*124);
        //printf("bzero didn't fail\n");
        if (strcmp(token, "+1") != 0 || strcmp(token, "-1") != 0)
        {
          //printf("+1\n");
          
            myArray[0] = atoi(token);
            token = strtok_r(NULL, " ", &linePointer);//get next
            //printf("token=|%s|\n",token);
        }

        //printf( " %s\n", token );

        while (token!=NULL && strstr(token, "\n") == NULL)
        {
          //printf("token=|%s|\n",token);
          token2 = strtok_r(token, ":", &inLinePointer);
          arrayNum = atoi(token2);
          if (arrayNum<=0 || arrayNum >123) 
          {
            printf("oops arrayNum=%d",arrayNum);
          }
          else 
          { 
            myArray[arrayNum] = 1;
          }
          //printf("arrayNum = %d\n", arrayNum);
          
          token = strtok_r(NULL, " ", &linePointer);

          //inLinePointer = 0;
        }
        //denominator = 0;
        for (int i = 1; i < 124; i++){ //calculate prediction
           sum += c[i]*weightArray[i]*myArray[i];//*tau[i];
           //denominator += pow(myArray[i], 2.0);
           //printf("%f, %f, %f \n", weightArray[i], myArray[i], sum);
        }
        prediction = sum * myArray[0]; //calculated prediction
        //printf("prediction = %f\n", prediction);
        if (prediction <= 0){ //Mistake happened, change weights
          for (int i = 1; i < 124; i++){
            weightArray[i] = weightArray[i] + (myArray[0]*myArray[i]);//w + tau * yt * xt = new weight
            //tau[i] = 1 - (myArray[0]*(weightArray[i]*myArray[i]))/(denominator);//yt((wt*xt))/||x||2

            if (tau[i] <= 0)
            {
              tau[i] = 0.0;
            }
            c[i] = 1;
            //printf("%f \n", tau[i]);
          }
          numMistakes++;
          //printf("Mistake\n");
        }
        else {for (int i = 0; i < 124; i++){
        c[i] = 1;
        }}
        prediction = 0.0;
        sum = 0.0;
      // printf("Array= ");
      // for(int i = 0; i < 124; i ++){
      //  //if (myArray[i]>0 || myArray[i]==-1) { printf("%d=%d ", i,myArray[i]); }
      //  printf("%f ", weightArray[i]);
      // }
      numExamples++;
      printf("\n");
      printf("Mistakes = %d\n", numMistakes);
      printf("Examples = %d\n", numExamples);
      // char f;
      // scanf("%c", &f);



        //token = strtok_r(NULL, " ", &linePointer);
        //if (firsten++ > 10) {break;} //exit out after first ten results
      }
    }
    mistakeArray2[trials] = numMistakes;
    numMistakes = 0;
    numExamples = 0;
    denominator = 0;
    //token = strtok_r(buffer, " ", &linePointer);
    //linePointer = 0;
    //inLinePointer = 0;
  }
  printf("Array= ");
  for(int i = 0; i < 100; i ++){
       //if (myArray[i]>0 || myArray[i]==-1) { printf("%d=%d ", i,myArray[i]); }
      printf("%d \n", mistakeArray2[i]);
  }
  printf("\n");

  /* the whole file is now loaded in the memory buffer. */
  //printf("%s\n", buffer);
  // terminate
  fclose (pFile2);
  free (buffer2);
  return 0;
}
