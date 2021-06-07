#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Circle
{
    double x;
    double y;
    double r;

} circle;

typedef struct Node
{
    circle circleData;
    struct Node *next;
} node;

char menu();
void printNode(node *head);
void print(circle circleData);
void getData(double *a, double *b, double *c);
circle loadCircleData(node *head);
void addNode(node** head, circle circleData);
void readBinaryFile(node** head);
void createBinaryFile(node* head);
void processData(node *head);

int main()
{
   node *head = NULL;
   char c;
   while(1)
    {
        system("cls");
        switch(menu()){
            case '1':
            printf("Enter data from the keyboard(K) or get data from file(F)? \n");
            printf("Select <K/F>: ");
            fflush(stdin);
            c = toupper(getchar());
            if(c == 'K'){
                    int num;
                    printf("Enter number of circles: \n");
                    scanf("%d", &num);
                    int i;
                    for(i=0; i<num; i++)
                    {
                      printf("Circle No. %d: \n", i+1);
                      addNode(&head, loadCircleData(head));
                    }
            }
            if(c == 'F'){
                readBinaryFile(&head);
            }
               break;
            case '2': printf("Print data on the screen(S) or save to file(F)? \n");
            printf("Select <S/F>: ");
            fflush(stdin);
            c = toupper(getchar());
            if(c == 'S'){
                printNode(head);
                system("pause");
            }
            if(c == 'F'){
                createBinaryFile(head);
                system("pause");
            }
                break;
           case '3': processData(head);
           system("pause");
                break;
            case '0':
                exit(0);
                break;

            return 0; }
    }
}

char menu()
{
    char i;
	printf("1. Enter data. \n");
	printf("2. Print data. \n");
	printf("3. Get result. \n");
	printf("0. Exit. \n");
	do
	{   printf("Select option (0-3): ");
		fflush(stdin);
		scanf("%c", &i);
	} while(i < '0' || i > '3');
	return i;
}

void print(circle circleData)
{
	printf("Center with coordinates:   \n X = %1.2f ,  Y = %1.2f \n", circleData.x, circleData.y);
    printf("Radius:   \n R = %1.2f \n", circleData.r);
}

void printNode(node *head)
{
    int i=1;
    if(!(head))
    {
        printf("List is empty!\n");
        return;
    }
    while(head)
    {
        printf("For circle No. %d: \n", i);
        print(head->circleData);
        i++;
        head = head->next;
    }
}
void getData(double *a, double *b, double *c)
{
    printf("Enter X and Y for the center of the circle. \n");
    printf("X = ");
    scanf("%lf", a);
    fflush(stdin);
    printf("Y = ");
    scanf("%lf", b);
    fflush(stdin);
    printf("Enter length of the radius. \n");
    printf("R = ");
    scanf("%lf", c);
    fflush(stdin);
}

circle loadCircleData(node *head)
{
    circle data;
    getData(&data.x, &data.y, &data.r);
    return data;
}

void addNode(node** head, circle circleData)
{
	        node* new_circle;
	        if((new_circle = (node*)malloc(sizeof(node)))==NULL)
                  {   printf("Allocating memory ERROR! \n");
                      exit(1);}
            node* temp = *head;
	        new_circle->circleData = circleData;
	        new_circle->next = NULL;
	        if(!(*head)) //Ако е празен списъка добавя първи елемент
	          {
                *head = new_circle;
		         return;
	          }
	        while(temp->next)
            {
		      temp = temp->next;
	        }
	        temp->next = new_circle;
}

void readBinaryFile(node** head)
{
	FILE* fp;
	circle data;
	if((fp = fopen("circle.bin", "rb"))==NULL){
		printf("Error reading the file! \n");
		return;}
	while(1)
	{
		if((fread(&data, sizeof(circle), 1, fp))!=1){
                printf("Error occurred while reading the file. \n");
                exit(4); }
		addNode(head, data);
	}
	fclose(fp);
}

void createBinaryFile(node* head)
{
	FILE* fp;
	if(!head)
	{
		printf("List is empty!\n");
		return;
	}
	if((fp = fopen("circle.bin", "wb"))==NULL)
	{
		printf("Error opening the file! \n");
		exit(2);
	}
	while(head)
	{
		if(fwrite(&head->circleData, sizeof(circle), 1, fp) != 1){
			printf("Error occurred while writing on file\n");
			exit(3); }
		head = head->next;
	}
	printf("Data saved to file. \n");
	fclose(fp);
}

void processData(node *head)
{
    node * temp = head;
    int i=1;
    char c;
    printf("Print result on the screen(S) or save to file(F)? \n");
    printf("Select <S/F>: ");
    fflush(stdin);
    c = toupper(getchar());
    int len;
    if(c == 'F')
    {
       FILE* fp;
       if((fp = fopen("ResultFile.txt", "w"))==NULL)
        {
		printf("Error opening the file! \n");
		exit(5);
	    }

        while (temp != NULL) {
        if(temp->circleData.x == 0 || temp->circleData.y == 0)
        {
            fprintf(fp, "The center (with coordinates: X = %1.2f, Y = %1.2f) of circle No.%d with radius R = %1.2f \n", temp->circleData.x, temp->circleData.y, i, temp->circleData.r);
            fprintf(fp, "lays on the origin point O of the coordinate system. \n");
		}
		len = sqrt(pow(temp->circleData.x,2)+pow(temp->circleData.y,2));
		if(len == temp->circleData.r)
        {
            fprintf(fp, "Circle No.%d with coordinates of the center: X = %1.2f, Y = %1.2f and radius R = %1.2f \n", i, temp->circleData.x, temp->circleData.y, temp->circleData.r);
            fprintf(fp, "crosses the origin point O of the coordinate system. \n");
        }
		if(temp->circleData.x<0 || temp->circleData.y<0)
        {
            double x = (-1)*temp->circleData.x;
            double y = (-1)*temp->circleData.y;
            if(temp->circleData.r<x || temp->circleData.r<y)
            {
                fprintf(fp, "Circle No.%d with coordinates of the center: X = %1.2f, Y = %1.2f and radius R = %1.2f \n", i, temp->circleData.x, temp->circleData.y, temp->circleData.r);
                fprintf(fp, "lays in quadrant. \n");
            }

        }
		temp = temp->next;
		i++;
     }
     printf("File created. \n");
     fclose(fp);
    }
    if(c == 'S')
    {
        while (temp != NULL) {
		if(temp->circleData.x == 0 || temp->circleData.y == 0)
        {
            printf("The center (with coordinates: X = %1.2f, Y = %1.2f) of circle No.%d with radius R = %1.2f \n", temp->circleData.x, temp->circleData.y, i, temp->circleData.r);
            printf("lays on the origin point O of the coordinate system. \n");
		}
		len = sqrt(pow(temp->circleData.x,2)+pow(temp->circleData.y,2));
		if(len == temp->circleData.r)
        {
            printf("Circle No.%d with coordinates of the center: X = %1.2f, Y = %1.2f and radius R = %1.2f \n", i, temp->circleData.x, temp->circleData.y, temp->circleData.r);
            printf("crosses the origin point O of the coordinate system. \n");
        }
        if(temp->circleData.x<0 || temp->circleData.y<0)
        {
            double x = (-1)*temp->circleData.x;
            double y = (-1)*temp->circleData.y;
            if(temp->circleData.r<x || temp->circleData.r<y)
            {
                printf("Circle No.%d with coordinates of the center: X = %1.2f, Y = %1.2f and radius R = %1.2f \n", i, temp->circleData.x, temp->circleData.y, temp->circleData.r);
                printf("lays in third quadrant. \n");
            }

        }
		temp = temp->next;
		i++;
     }
    }
}


