//������� ���� ȯ�� ���� ����ü ���� �� linked list ���� �ڵ� ������ (ifct_database.h �Լ�Ȱ��
//Ư�� ���ǿ� �´� ȯ���� ���� ��� �ڵ� ����
//ȯ���� �����ڸ� �����ϰ� ���� �����ڸ� �˾Ƴ��� �ڵ� ���� 

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
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
    //���� ������ �����ϱ� ���� �迭  
	int arr[5][8]; 
	int i, j;

 
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1],"r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    //1-2. loading each patient informations
    //fscanf�� ���� ���� �а� �����ϱ�  -> ������ ���� �� ��Ʈ ���� 
    /*
    while(3 == fscanf("3���� �б�",������))
    {
    for() {fscanf(5�� �б�);}
	}
    */
    
    for(i=0; i<5; i++){
    	for(j=0; j<8; j++){
			fscanf(fp,"%d",&arr[i][j]);
    		printf("%d ",arr[i][j]);
    	}
    	printf("\n");
    }
    
   
    
    //1-3. FILE pointer close
    fclose(fp);
    
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
				
				//patient index, patient age, detected time, pathHistory ��� 
                break;
                
            case MENU_PLACE:
            	printf("Place Name: ");
            	//scanf("%s",&??)
                //printf("There are %d patients detected in %s",���, ?? );
            
                break;
                
            case MENU_AGE:
            	/*
            	���� �ּҿ� �ִ� �Է��Ͽ� 
				patient index, age, dectedtime, pathHistory ��� 
            	*/
                
                break;
                
            case MENU_TRACK:
                    
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}

