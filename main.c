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
	char ifct_place;
	

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
    

	//ifct_element = ifctele_getElement(index,age,,,); -> 교수님 베이스 코드 예시
	 
	//while문 대신 for문을 써서 파일의 값을 입력받아 저장하는 코드 
	for(i = 0; i < 5; i++){
		fscanf(fp,"%d",&pIndex); //파일의 첫번째 요소를 pIndex 으로 저장
		fscanf(fp,"%d",&age);  //파일의 두번째 요소를 age 으로 저장
		fscanf(fp,"%d",&time); //파일의 세번째 요소를 time 으로 저장
		
		for(j=0; j<N_HISTORY; j++){
			fscanf(fp,"%d",(placeHist+j));
		}  
		ifct_element = ifctele_getElement(pIndex,age,time,placeHist);
		ifctdb_addTail(ifct_element); 
	}
	 
	printf("\n- - - - 파일 입력받았다, 입력 성공- - - - -\n\n");
	 
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
				//구조 짜놓기 
                //0~5 index의 환자들의 ifctele_getPlaceName(ptr->place[4]) == ifct_place
				//위의 조건을 만족한다면 그 환자의 정보 출력하기 
                //ifctele_getHistPlaceIndex(void* obj, int index); //매개변수 obj에는 ifct_palce
				int cnt=0;
				for(i=0; i<N_HISTORY; i++){
					cnt=cnt+ifctele_getHistPlaceIndex(&ifct_place,i);
				}
				printf("%d명의 환자가 %s에서 확인되었습니다\n\n",cnt,ifct_place);
                
                break;
                
            case MENU_AGE:
            	printf("minimal age: ");
            	scanf("%d",&age);
            	printf("max age: ");
            	scanf("%d",&age2);
    
            	//구현 중... 실행 조건을 보니 나이의 최소와 최대를 우선 입력받는다.
				//index 0~5까지 환자의 .age가 이 범위 내에 있다면 cnt를 증가하는 함수로 이어져야 할 것  
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
