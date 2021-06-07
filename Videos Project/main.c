
#include <stdio.h>
#include <stdlib.h>
typedef struct Comment
{
    char text[150];
    char user[50];
    char commentDate[11];
    int likes;
} comment;

typedef struct Video
{
    char link[100];
    char name[50];
    int rating;
    char date[11];
    int likes;
    int dislikes;
    int numOfComments;
    comment comments[100];
} video;

typedef struct Node
{
    video videoData;
    struct Node *next;
} node;

char menu(); //Меню, с което се командва програмата
void print(video videoData, comment commentData); //Изпечатване на въведената информация.
void printNode(node *head); //Изпечатване на списъка.
void addNode(node** head, video videoData, int mode); //Въвеждане на нов елемент в края на свързания списък.
void createBinaryFile(node *head); //Записване на списъка в бинарен файл.
void readBinaryFile(node **head); //Четене на списъка от бинарен файл.
void getName(char *name); //Получаване на име на видеото от клавиатурата.
void getLink(char *link); //Получаване на линк към видеото от клавиатурата.
void getRating(int *rating); //Получаване на рейтинга на видеото от клавиатурата.
void getDate(char* date); //Получаване датата на добавяне на видеото от клавиатурата.
void getLikes(int *likes); //Получаване на брой харесвания от клавиатурата.
void getDislikes(int *dislikes); //Получаване на брой нехаресвания от клавиатурата.
comment getComment(comment data); // Получаване на информация за коментарите.
video loadVideoData(node *head); // Зареждане на информацията за дадено видео.
void addCommentToVideo(node **head); //Добавяне на нов коментар към избрано от потребителя видео.
void deleteDirtyComments(node *head); //Изтриване на всичи коментари, които съдържат нецензурни думи.
void deleteVideo(node **head); //Изттриване на всички видеа с отношение харесвания/нехаресвания по-малко от 0,5.
void deleteNode(node** head, int possition); //Изтриване на даден елемент от определена позиция.

int main()
{   node *head = NULL;
printf("da\n");
    while(1)
    {   system("pause");
        system("cls");
        switch(menu()){
            case '1': readBinaryFile(&head);
                break;
            case '2': createBinaryFile(head);
                break;
            case '3': printNode(head);
                break;
            case '4': addNode(&head, loadVideoData(head), 1);
                break;
            case '5': addCommentToVideo(&head);
                break;
            case '6': deleteDirtyComments(head);
                break;
            case '7': deleteVideo(&head);
                break;
            return 0; }
    }
}
char menu()
{
	char i;
	printf(" MAIN MENU: \n");
	printf("1. Load data from file. \n");
	printf("2. Save data to file. \n");
	printf("3. Print. \n");
	printf("4. Add video. \n");
	printf("5. Add comment. \n");
	printf("6. Delete dirty comments. \n");
	printf("7. Delete videos (with likes/dislikes < 0.5). \n");
	printf("0. Exit. \n");

	do
	{   printf("Select option (0-7): ");
		fflush(stdin);
		scanf("%c", &i);
	} while(i < '0' || i > '7');
	return i;
}
void print(video videoData, comment commentData)
{
    printf("Name:                %s\n", videoData.name);
	printf("Leading link:        %s\n", videoData.link);
	printf("Rating:              %d\n", videoData.rating);
	printf("Date added:          %s\n", videoData.date);
	printf("Likes:               %d\n", videoData.likes);
	printf("Dislikes:            %d\n", videoData.dislikes);
	printf("Number of comments:  %d\n", videoData.numOfComments);
    printf("Username:            %s\n", commentData.user);
    printf("Comment:             %s\n", commentData.text);
    printf("Date added:          %s\n", commentData.commentDate);
    printf("Likes:               %d\n", commentData.likes);
}
void printNode(node *head) //Печата целия свързан списък
{
    int i;
    if(!(head))
    {
        printf("List is empty!\n");
        return;
    }
    while(head)
    {
        for(i = 0; i < head->videoData.numOfComments; i++)
        {
        print(head->videoData, head->videoData.comments[i]);
        head = head->next; }
    }
}
void addNode(node** head, video videoData, int mode)
{
	node* new_video;
	if((new_video = (node*)malloc(sizeof(node)))==NULL)
    {   printf("Allocating memory ERROR! \n");
        exit(1);}
    node* temp = *head;
	new_video->videoData = videoData;
	new_video->next = NULL;
	if(!(*head)) //Ако е празен списъка добавя първи елемент
	{
		*head = new_video;
		if(mode == 1){
		    printf("First Video added successfully!\n");}
		return;
	}
	while(temp->next)
	{
		temp = temp->next;
	}
	temp->next = new_video;
	if(mode == 1){
		printf("New Video added successfully!\n");}
}
void createBinaryFile(node* head)
{
    char fileName[] = "video";
	FILE* fp;
	if(!head)
	{
		printf("List is empty!\n");
		return;
	}
	if((fp = fopen(fileName, "wb"))==NULL)
	{
		printf("Error opening the file! \n");
		exit(2);
	}
	while(head)
	{
		if(fwrite(&head->videoData, sizeof(video), 1, fp) != 1){
			printf("Error occured while writing on file\n");
			exit(3); }
		head = head->next;
	}
	fclose(fp);
}
void readBinaryFile(node** head)
{
	FILE* fp;
	video data;
	if((fp = fopen("video.bin", "rb"))==NULL){
		printf("Error reading the file! \n");
		return;}
	while(1)
	{
		if((fread(&data, sizeof(data), 1, fp))!=1){
                printf("Error occurred while reading the file. \n");
                exit(4); }
		addNode(head, data, 2);
	}
	fclose(fp);
}
void getName(char *name)
{
    printf("Enter name of video: ");
    fflush(stdin);
    gets(name);
}
void getLink(char *link)
{
    printf("Enter link of video: ");
    fflush(stdin);
    gets(link);
}

void getRating(int *rating)
{
    printf("Enter rating 0-10: \n");
    scanf("%d", rating);
    fflush(stdin);
}
void getDate(char* date)
{
	printf("Enter date: \n");
	fflush(stdin);
	gets(date);
}
void getLikes(int *likes)
{
    printf("Enter likes: ");
    scanf("%d", likes);
    fflush(stdin);
}
void getDislikes(int *dislikes)
{
    printf("Enter dislikes: ");
    scanf("%d", dislikes);
    fflush(stdin);
}
comment getComment(comment data)
{
    int i, flag = 0;
    do
    {
        printf("Enter comment: ");
        fflush(stdin);
        gets(data.text);
    } while(!strlen(data.text));
    for(i = 0; i < strlen(data.text); i++)
    {
        data.text[i] = toupper(data.text[i]);
    }
    do
    {
        printf("Enter Username: ");
        fflush(stdin);
        gets(data.user);
    } while(!strlen(data.user));
    getLikes(&data.likes);
    return data;
}
video loadVideoData(node *head)
{
    video data;
    int i;
    char c;
    getLink(data.link);
    getName(data.name);
    getRating(&data.rating);
    getLikes(&data.likes);
    getDislikes(&data.dislikes);
    for(i = 0; i<100; i++)
    {
        printf("Do you want to add a comment<Y/N>: ");

        while(1)
        {
            fflush(stdin);
            c = toupper(getchar());
            if(c == 'N')
                return data;
            if(c == 'Y')
                break;
            printf("Select <Y/N>: ");
        }
        data.comments[i] = getComment(data.comments[i]);
        data.numOfComments = i + 1;
    }
    return data;
}
void addCommentToVideo(node **head)
{
    node *temp = *head;
    char name[50];
    int i;
    if(!(*(head))){
        printf("List is empty!\n");
        return; }
    printf("Enter video to search: ");
    fflush(stdin);
    gets(name);
    while(temp != NULL)
    {
        if((strcmp(temp->videoData.name, name)) == 0){
            temp->videoData.comments[temp->videoData.numOfComments] = getComment(temp->videoData.comments[temp->videoData.numOfComments]);
            temp->videoData.numOfComments++; }
        temp = temp->next;
    }
}
void deleteDirtyComments(node *head)
{
    node *temp = head;
    int i, flag = 0;
    if(!(head)){
        printf("List is empty!\n");
        return; }

    while(temp)
    {
        for(i = 0; i < temp->videoData.numOfComments; i++)
        {
            flag = 1;
            if(strstr(temp->videoData.comments[i].text, "Fuck"))
                strcpy(temp->videoData.comments[i].text, "Comment deleted!");
            if(strstr(temp->videoData.comments[i].text, "Shit"))
                strcpy(temp->videoData.comments[i].text, "Comment deleted!");
            if(strstr(temp->videoData.comments[i].text, "Bitch"))
                strcpy(temp->videoData.comments[i].text, "Comment deleted!");
            if(strstr(temp->videoData.comments[i].text, "Nigga"))
                strcpy(temp->videoData.comments[i].text, "Comment deleted!");
            if(strstr(temp->videoData.comments[i].text, "Ass"))
                strcpy(temp->videoData.comments[i].text, "Comment deleted!");
        }
        temp = temp->next;
    }
    if(!flag){
        printf("No dirty comments found!\n");}
    else printf("All dirty comments have been deleted!\n");

}
void deleteVideo(node **head)
{
    int possition = 1;
    node *temp = *head;
    double result;
    if(!(*head))
    {   printf("Empty list!\n");
        return; }
    while(temp!=NULL)
    {
        result = (double) (temp->videoData.likes) / (temp->videoData.dislikes);
		if(result < 0.5){
			deleteNode(head, possition);
			printf("Video deleted!\n");
			return; }
		else {
			temp = temp->next;
			++possition; }
	}
}
void deleteNode(node** head, int possition)
{
	int i;
	node *temp1 = (*head), *temp2;

	if(possition == 1){
		(*head) = temp1->next;
		free(temp1);
		return;
	}

	for(i = 0; i < possition-2; i++){
		temp1 = temp1->next;
		//temp1 pointst to (n-1)th possition;
	}
	temp2 = temp1->next;//temp2 points to n-th poss Node;
	temp1->next = temp2->next;
	free(temp2);
}
