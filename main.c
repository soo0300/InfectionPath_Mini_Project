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
	//구조체 변수를 다루기 위한 void 형 포인터변수 선언 
	//element.c에서 생성된 구조체를 linked list에 넣을 예정  
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
	//추가 생성 
	int i,j;
	int age2;

	//ifs_ele_t arr[5]; 이렇게 해야하는거 아니야?  


    //BASE CODE 31줄부터 45줄까지 
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
    

	//ifct_element = ifctele_getElement(index,age,,,);


	for(i = 0; i < 5; i++){
		fscanf(fp,"%d",&pIndex); //파일의 첫번째 요소를 pIndex로 저장
		fscanf(fp,"%d",&age);  //파일의 두번째 요소를 age로 저장
		fscanf(fp,"%d",&time); //파일의 세번째 요소를 time으로 저장
		
		for(j=0; j<N_HISTORY; j++){
			fscanf(fp,"%d",(placeHist+j));
		}  
		
		ifct_element = ifctele_getElement(pIndex,age,time,placeHist);
		ifctdb_addTail(ifct_element); 
		
	}
	 
	printf("\n- - - - - - - - -\n\n");
	 
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
            	
            	printf("환자의 Index를 입력해주세요: ");
            	scanf("%d",&pIndex);
            	printf("%d의 정보는... ",pIndex);
            	ifctele_printElement(ifctdb_getData(pIndex));
            
            	
                break;
                
            case MENU_PLACE:
                
                break;
                
            case MENU_AGE:
            	printf("minimal age: ");
            	scanf("%d",&age);
            	printf("max age: ");
            	scanf("%d",&age2);
            	
            	//ifctele_getAge(*age,*age2);
            
                
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
