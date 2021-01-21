#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>
#include <string.h>

#define A 220
#define A2 233.08
#define B 246.942
#define C 261.6256
#define C2 277.18
#define D 293.6648
#define D2 311.13
#define E 329.6275
#define F 349.2282
#define F2 369.99
#define G 391.9954
#define G2 415.30

#define INPUT_MAX 100
#define datasize 1000

double ratios[17] = {1.0, 1.067, 1.125, 1.2, 1.125, 1.2, 1.25, 1.333, 1.406, 1.5, 1.6, 1.6875, 1.8, 1.6875, 1.8, 1.875, 2.0};



//Use Beep function to play a sound at a frequency

/*ragas*/
double srutis[12] = {A, A2, B, C, C2, D, D2, E, F, F2, G, G2};

/* swaras */
const char *swaras[17] = {"S0", "R1", "R2", "R3", "G1", "G2", "G3", "M1", "M2", "P", "D1", "D2", "D3", "N1", "N2", "N3", "S1"};

void playsruti(double sruti);

struct raga * upload_data(struct raga * data, FILE * x);

void printRagas(struct raga * data);

void addraga();

int indexof(double x);

int indexofchar(char *x);

void playragam(char * sruti, int index);

int search(char (*input)[1000]);

void clearKeyBoardBuffer(void);

typedef struct raga {
    char name[INPUT_MAX];
    double scale[30];
    char (*swarascale[2])[30];
    int length;
} raga;

struct raga data[datasize];

int main(void) {

    FILE * fp = fopen("C:\\Users\\srira\\Desktop\\all-ragas.txt","r");
    //FILE * fp = fopen("ragas.txt","r");
    printf("WELCOME\n\n");
    if (!fp) {
        fprintf(stderr, "File could not be opened!\n");
        exit(1);
    }
    printf("UPLOADING DATA\n\n");
    upload_data(data,fp);
    fclose(fp);
    printf("DONE UPLOADING DATA\n\n");
    //printf("printing ragas\n");
    //printRagas();
    ///printf("done printing ragas\n");
    char input[1000] = "";
    char sruti[2];
    search(&input);
    return 0;
}

void printRagas(struct raga * data) {
    int i=0;
    while(i<datasize) {
        printf("%s  length=%d ", data[i].name,data[i].length);
        for (int j=0; j<data[i].length; j++) {
            printf("%s   ", data[i].swarascale[j]);
        }
        printf("\n");
        i++;
    }
}

int indexof(double x) {
    for (int i = 0; i<17; i++) {
        if (x==ratios[i]){
            return i;
        }
    }
    return -1;
}

int indexofchar(char * x) {
    for (int i = 0; swaras[i]!=NULL; i++) {
        if (strcmp(swaras[i],x)==0){
            return i;
        }
    }
    return -1;
}

struct raga * upload_data(struct raga * data, FILE * x) {
    char strread[200];  //stores each line of raga database
    int num=0;
    while(fgets(strread, sizeof(strread), x) != NULL) {
        //printf("strread ====== %s  size=%d\n",strread,sizeof(strread));
        struct raga *melakarta = malloc(sizeof(melakarta));
        int namechar = 0;
        //printf("IN UPLOAD  ");
        char * info = strtok(strread, "\t");
        strcpy(melakarta->name, info);
        //printf("name: %s\n", melakarta->name);

        int swaracount=0;  //counter for swara in both arohana and avarohana
        info = strtok(NULL, "\t");
        while (info!=NULL && strlen(info)<=2) {
            //	melakarta->scale[swaracount]=info;
            //	printf("Next swara is %s %d\n", info, swaracount);
            melakarta->scale[swaracount] = ratios[indexofchar(info)];
            melakarta->swarascale[swaracount] = info;
            //	printf("info is %s\n", info);
            ++swaracount;
            info = strtok(NULL, "\t");
        }
        //printf("Stop reading into scale, swaracount=%d\n",swaracount);
        melakarta->length = swaracount-1;

        swaracount=0; //reset swara counter to 0
        //strcpy(strread,"");
        data[num] = *melakarta;
        printf("End: Raga %d added: %s, %d\n\n", num, data[num].name, data[num].length);
        ++num;
        free(info);
    }
    return data;
    printf("EXITING UPLOAD\n\n");
}

/*void playsruti(double sruti) {
    while(1) {
        Beep(sruti,500);
    }
}*/

/*void playragam(char * sruti, int index) {
    double freq;
    if (strcmp(sruti,"A")==0){
        freq = A;
    }else if (strcmp(sruti,"A#")==0){
        freq = A2;
    }else if (strcmp(sruti,"B")==0){
        freq = B;
    }else if (strcmp(sruti,"C")==0){
        freq = C;
    }else if (strcmp(sruti,"C#")==0){
        freq = C2;
    }else if (strcmp(sruti,"D")==0){
        freq = D;
    }else if (strcmp(sruti,"D#")==0){
        freq = D2;
    }else if (strcmp(sruti,"E")==0){
        freq = E;
    }else if (strcmp(sruti,"F")==0){
        freq = F;
    }else if (strcmp(sruti,"F#")==0){
        freq = F2;
    }else if (strcmp(sruti,"G")==0){
        freq = G;
    }else if (strcmp(sruti,"G#")==0){
        freq = G2;
    }
    for (int i=0; i<data[index].length; i++) {
        printf("%s ", swaras[indexof(data[index].scale[i])]);
        Beep( freq*data[index].scale[i], 500);
        Sleep(10);
    }
    printf("\nFinished playing ragam\n\n");
}*/

int search(char (*input)[1000]) {
    char newinput[1000];
    printf("Enter your ragam:\n");
    scanf("%s", newinput);
    strcpy(input,newinput);
    //printf("got search info\n");
    int index=0;
    while (index<datasize && strcmp(data[index].name, &input)!=0) {
        //printf("in search index = %d\n", index);
        index++;
    }
    if (index==datasize) {
        printf("Ragam not in database.  Please try again.\n");
        clearKeyBoardBuffer();
        return 0;
    } else {
        printf("found ragam %d\n", index);
        clearKeyBoardBuffer();
        return 1;
    }
}

/*void addraga() {
	struct raga * new = (struct raga *)malloc(sizeof(struct raga));

	char *scale = malloc(30*sizeof(char[2])+29*sizeof(' '));
    double notescale[30];
    const char name[INPUT_MAX];
	int i=0;

	printf("What is the name of your new ragam?");
	scanf("%[^\n]s", name);
	int namelen = (int)strlen(name);
	strcpy(new->name, name);
	memset(new->name, '\0', sizeof(new->name));
	printf("name: %s\n", new->name);
	clearKeyBoardBuffer();

	printf("Enter arohana and avarohana (up and down scales):\n");
	scanf("%[^\n]s", scale);
	char * swara = strtok(scale, " ");
	while (scale!=NULL) {
        new->scale[i] = swara;
		printf("%s\n", new->scale[i]);
		i++;
		swara = strtok(NULL," ");
	}
	printf("Added swaraas\n");
	new->length = i;
	printf("length: %d\n", new->length);
	clearKeyBoardBuffer();

	if (search(new->name)==1) {
		printf("Ragam is already in database.\n");
	} else	{
        data[sizeof(data)/sizeof(struct raga) - 1] = new;
		if (i < 10) {
			printf("Error entering new raga.\n");
		}	else	{
			printf("You've successfully entered a new raga!\n");
		}
	}
	clearKeyBoardBuffer();
}
*/
void clearKeyBoardBuffer(void) {
    char ch;
    scanf("%c", &ch);
    while (ch != '\n' && ch != '\0') {
        scanf("%c", &ch);
    }
}



