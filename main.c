//입출력을 통해 환자 정보 구조체 생성 및 linked list 저장 코드 구현현 (ifct_database.h 함수활용
//특정 조건에 맞는 환자의 정보 출력 코드 구현
//환자의 전파자를 추적하고 최초 전파자를 알아내는 코드 구현 

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
    
    //읽은 내용을 저장하기 위한 배열  
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
    //fscanf로 샘플 파일 읽고 저장하기  -> 교수님 수업 중 힌트 예제 
    /*
    while(3 == fscanf("3가지 읽기",변수들))
    {
    for() {fscanf(5개 읽기);}
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
				
				//patient index, patient age, detected time, pathHistory 출력 
                break;
                
            case MENU_PLACE:
            	printf("Place Name: ");
            	//scanf("%s",&??)
                //printf("There are %d patients detected in %s",결과, ?? );
            
                break;
                
            case MENU_AGE:
            	/*
            	나이 최소와 최대 입력하여 
				patient index, age, dectedtime, pathHistory 출력 
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

