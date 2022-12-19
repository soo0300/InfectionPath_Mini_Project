#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2

int trackInfester(int patient_no, int *detected_time, int *place);
int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element; 
	//����ü ������ �ٷ�� ���� void �� �����ͺ��� ���� 
	//element.c���� ������ ����ü�� linked list�� ���� ����  
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
	//�߰� ���� 
	int i,j;
	int age2;
	char ifct_place;
	

    //BASE CODE 31�ٺ��� 45�ٱ��� 
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    

	//ifct_element = ifctele_getElement(index,age,,,); -> ������ ���̽� �ڵ� ����
	 
	//while�� ��� for���� �Ἥ ������ ���� �Է¹޾� �����ϴ� �ڵ� 
	for(i = 0; i < 5; i++){
		fscanf(fp,"%d",&pIndex); //������ ù��° ��Ҹ� pIndex ���� ����
		fscanf(fp,"%d",&age);  //������ �ι�° ��Ҹ� age ���� ����
		fscanf(fp,"%d",&time); //������ ����° ��Ҹ� time ���� ����
		
		for(j=0; j<N_HISTORY; j++){
			fscanf(fp,"%d",(placeHist+j));
		}  
		ifct_element = ifctele_getElement(pIndex,age,time,placeHist);
		ifctdb_addTail(ifct_element); 
	}
	 
	printf("\n- - - - ���� �Է¹޾Ҵ�, �Է� ����- - - - -\n\n");
	 
    //1-3. FILE pointer close
    fclose(fp);
    
    {
    	int place1, place2;
    	
		place1 = 3;
    	place2 = 15;
    	
    	printf("The first place is %s\n", ifctele_getPlaceName(place1)) ;
    	printf("The second place is %s\n", ifctele_getPlaceName(place2)) ;
	}
    
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                     //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        switch(menu_selection)
        {
            case MENU_EXIT:
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:
            	
            	printf("Patient index: ");
            	scanf("%d",&pIndex);
            	printf("- - - - - - - - - - - - - - - - - - - -\n");
            	ifctele_printElement(ifctdb_getData(pIndex));
                
				break;
                
            case MENU_PLACE:
            	printf("Place Name: ");
				scanf("%s",&ifct_place);
				printf("- - - - - - - - - - - - - - - - - - - -\n");
				//���� ¥���� 
                //0~5 index�� ȯ�ڵ��� ifctele_getPlaceName(ptr->place[4]) == ifct_place
				//���� ������ �����Ѵٸ� �� ȯ���� ���� ����ϱ� 
                //ifctele_getHistPlaceIndex(void* obj, int index); //�Ű����� obj���� ifct_palce
				int cnt=0;
				for(i=0; i<N_HISTORY; i++){
					cnt=cnt+ifctele_getHistPlaceIndex(&ifct_place,i);
				}
				printf("%d���� ȯ�ڰ� %s���� Ȯ�εǾ����ϴ�\n\n",cnt,ifct_place);
                
                break;
                
            case MENU_AGE:
            	printf("minimal age: ");
            	scanf("%d",&age);
            	printf("max age: ");
            	scanf("%d",&age2);
    
            	//���� ��... ���� ������ ���� ������ �ּҿ� �ִ븦 �켱 �Է¹޴´�.
				//index 0~5���� ȯ���� .age�� �� ���� ���� �ִٸ� cnt�� �����ϴ� �Լ��� �̾����� �� ��  
            	ifctele_getAge(age,age2);
            	
                break;
                
            case MENU_TRACK:
        
            	printf("Patient index: ");
            	scanf("%d",&pIndex);
        		ifctele_getinfestedTime(pIndex);
        		
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
