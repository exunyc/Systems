#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int numchild;
char *sortname;
char *sortpath;
char *outputname;
char *fullname;
char *category;
char *output_dir;
int hasoutput;
int hasinput;

void sort(FILE *fp, char *sortParam, char *fileName, char *outPutDir){
	
	int i, j, numRecords, cols, ct;
	char *entry = NULL;
	size_t len = 0;
	ssize_t len1; 
	numRecords = 0;
	dataEntry *arr = malloc(sizeof(dataEntry));
	while ((len1 = getline(&entry, &len, stdin) != -1)) {
		if (strstr(entry, ",") == NULL) {
			break;
		}
		arr = realloc(arr, (numRecords + 1) * sizeof(dataEntry));
		if (numRecords == 1) {
      cols = ct; 
			arr[0].cols = cols;
      for (i = 0; i < cols; i++) {
	     	for (j = i + 1; j < cols; j++) {
			    if (strcmp(arr[i].entry, arrr[j].entry) == 0) {
			    	printf("Error: Multiple columns with the same name found!\n");
			     	return -1;
		    	}
	    	} 
	  `}
			
			int paramFound = 0;
			i = 0;
			while (i < cols) {
				if (strcmp(arr[0].entry[i], argv[2]) == 0) {
					paramFound = 1;
				}
				i++;
			}
			if (paramFound == 0) {
				printf("Error! \n");
				return -1;
			}
		}
		char *t, *end = entry;	
		ct = 0;
		arr[numRecords].entry = malloc(sizeof(char **));
		while (end != NULL) {
			if (end[0] != '\"') {
				t = strsep(&end, ",");	
			} else {
				end++;
				t = strsep(&end, "\"");
				end++;
			}
			if (ct > 0) {
				arr[numRecords].entry = realloc(arr[numRecords].entry, (ct + 1) * sizeof(char **));
			}
			
			int front = 0;
			int end = strlen(t) - 1;
			while (isspace((unsigned char) t[front])) {
				front++;
			}
			while ((end >= front) && isspace((unsigned char) t[end])) {
				end--;
			}
			i = front;
			while(i <= end) {
				t[i - front] = t[i];
				i++;
			}
			t[i - front] = '\0';
			
			arr[numRecords].entry[ct] = malloc(strlen(t) * sizeof(char) + 1);
			strcpy(arr[numRecords].entry[ct], t);
			ct++;
		}
		arr[numRecords].cols = cols;
		numRecords++;
	}
	
	int cI = -1;
	
	i = 0;
	while (i < cols) {
		if (strcmp(arr[0].entry[i], argv[2]) == 0) {
			cI = i;
			break;
		}
		i++;
	}
	
	
	if (cI < 0) {
		return -1;
	} else {
		mergeSort(arr, cI, numRecords - 1);
	}
	if (opendir(outputDir) == NULL) {
		mkdir(outputDir, S_IRWXU);
	}
	
	FILE *sortedFile;
	char *base, *extension;
	extension = strrchr(fileName, '.');
	const char *substring = strstr(fileName, extension);
	size_t baseLength = substring - fileName;
	// Get the base of the filename
	base = malloc(len + 1);
	memcpy(base, fileName, baseLength);
	base[baseLength] = '\0';
	if (strcmp(outputDir, "") != 0) {	
		base = strrchr(base, '/');	
	}
	int totalLength = strlen(outputDir) + strlen(base) + strlen("-sorted-") + strlen(sortParam) + strlen(extension) + 1;
	char sortedFileName[totalLength];
  
	// Creates sorted CSV file
	snprintf(sortedFileName, totalLength + 1, "%s/%s-sorted-%s%s", outputDir, base, sortParam, extension);
	sortedFile = fopen(sortedFileName, "w");
  i = 0;
	while(i < numRecords) { 
		for (j = 0; j < numColumns; j++) {
			if (j != (numColumns - 1)) {
				fprintf(sortedFile, "%s,", arr[i].line[j]);
			}else{
				fprintf(sortedFile, "%s", arr[i].line[j]);
			}
      i++;
		}
		fprintf(sortedFile, "\n");
	}
	
}

void removeQuotes(char *str){
	int i;
	if(input[0] == '\"' || input[0] == '"'){
		for(i = 0; i < strlen(input); i++){
			input[i] = input[i+1];
		}
		
	}
	if(input[strlen(input)-1] == '"' || input[strlen(input)-1] == '\"'){
		input[strlen(input)-1] = '\0';
	}
}

int main(int argc, char **argv){
	char *input_dir=malloc(100000); 
	output_dir = malloc(100000);
	outputname = malloc(100000);
	DIR *dir;
	char path[4096];
	//num_processes = 0;
	hasoutput=0;
	hasinput=0;
	int parentID = getpid();
	
	if(argv[2] == '0' || argv[2] == NULL){
		printf("Error. One or more arguments are null");
		return -1;
	}
	
	
	if(argc == 3){
		
		if(strmcmp(argv[1], "-c") != 0){
			printf("Error. '-c' is expected as first argument. \n");
			return -1;
		
		}
	}
	
	switch(argc){
		case '3':
			if(strcmp(argv[1], "-c") != 0){
				printf("Error: '-c' is expected as first argument. \n");
				return -1;
			}
			if(getcwd(path, sizeof(path)) == NULL){
				printf("Error: Cannot get current working directory. \n");
				return -1;
			}
			
			sortpath = path;
			if((dir = opendir(path)) == NULL){
				printf("Error: Input directory is invalid. \n");
				return -1;
			}
			break;
		case '5':
			if(strcmp(argv[1], "-c") != 0){
				printf("Error: '-c' is expected as first argument. \n");
				return -1;
			}
			if(strcmp(argv[3], "-d") == 0){
				hasinput = 1;
			}else if(strmp(argv[3], "-o") == 0){
				hasoutput = 1;
			}else{
				printf("Error: '-d' or '-o' is expected as third argument. \n");
				return -1;
			}
			
			if(hasinput){
				strcpy(input_dir, argv[4]);
				removeQuotes(input_dir);
				sortpath = input_dir;
				int i;
				while(i < strlen(input_dir)){
					path[i] = input_dir[i];
				}
				if((dir = opendir(path)) == NULL){
					printf("Error: Input directory is invalid. \n");
					return -1;
				}
				
			}
			
			if(hasoutput){
				strcpy(output_dir, argv[4]);
				removeQuotes(output_dir);
				if(getcwd(path, sizeof(path)) == NULL){
					printf("Error: Error with getting directory. \n");
					return -1;
				}
				sortpath = path;
				dir = opendir(path);
			}
			break;
		case '7':
			if(strcmp(argv[3], "-d") == 0){
				strcpy(input_dir, argv[4];
				removeQuotes(input_dir);
				hasinput = 1;
			}
			if(strcmp(argv[5], "-o") == 0){
				hasoutput = 1;
				strcpy(output_dir, argv[6]);
				removeQuotes(output_dir);
			}else{
				printf("Error: Incorrect argument entered. \n");
				return -1;
			}
			
			sortpath = input_dir;
			int i;
			while(i < strlen(input_dir)){
				path[i] = input_dir[i];
			}
			if((dir = opendir(path)) == NULL){
				printf("Error: Input directory is invalid. \n");
				return -1;
			}
			break;
		default:
			printf("Error: Error in given arguments. \n");
			return -1;
			
		printf("Original PID: %d\n", getpid());
		printf("PID of child processes: ");
		fflush(stdout);
		
		numchild = 0;
		
		struct dirent *str;
		
		if ( dir != NULL){
		str = readdir(dir); // reads the first thing in the directory
		while(str != NULL){
			if((strcmp(str->d_name,"..") != 0) && (strcmp(str->d_name,".") != 0)){
				if(str->d_type == DT_DIR){	
					int pid = fork();
					if(pid == 0){
						
						printf("%d, ", getpid());
						fflush(stdout);
						closedir(dir); //close the original directory
						strcat(path,"/"); //append the folder to the path
						strcat(path, str->d_name);
						//printf("%s\n",nextdir);
						dir = opendir(path);	//open the new directory
						numchild = 0;	//reset number of children			
					}
					else
					{
						numchild++; //increment number of children in parent
					}
					
				}
				else
				{
					char* extension = strrchr(str->d_name,'.'); // gets the extension of the file
					char* sorted = strstr(str->d_name,"-sorted-");
					if (sorted != NULL)
					{
							//printf("\n %s is already sorted, skipping. \n",str->d_name);
					}
					
					
					if(extension!=NULL && sorted==NULL){
						if(strcmp(extension,".csv")==0)	{
							if(checkvalid(path,str->d_name)){

								int pid = fork(); // fork on here
								if(pid == 0){
								
									printf("%d, ", getpid());
									fflush(stdout);
									numchild = 0; //reset number of children
									sortname = str->d_name; //set the name of the file
									sortpath = path; //set the path of the file
									break; //exit look
								}
								else
								{		
									numchild++; //increment number of children in parent
								}
							
							}
							else
							{
									//printf("\nImproperly formatted file, skipping: %s\n", str->d_name);
							}
										
						}
					}
					
				}		
			}	
       str = readdir(dir);
		}	
	}
	closedir(dir); 
	int exitnum;
	if(sortpath != NULL && sortname == NULL){
		i = numchild;	
    while(i > 0){
				int status;
				wait(&status);
      i--;
			}
		if(originalPID == getpid()){
				printf("\nTotal number of processes: %i\n",exitnum+numchild+1);
		}
		
		return numchild+exitnum;

	}	

	fullname = malloc(4096); 
		outputname = strcpy(outputname,sortname);											
		fullname = strcpy(fullname, sortpath);
		fullname = strcat(fullname, "/");
		fullname = strcat(fullname, sortname); 
	
	sort(argv);
	
	free(outputname);
	free(input_dir);
	free(output_dir);
	
	return 0;
	
}
		
					
				
