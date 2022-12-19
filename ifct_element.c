#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ifct_element.h"

typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
} place_t;

char countryName[N_PLACE+1][MAX_PLACENAME] =
{   "Seoul","Jeju","Tokyo","LosAngeles","NewYork","Texas","Toronto","Paris",
    "Nice","Rome","Milan","London","Manchester","Basel","Luzern","Munich",
    "Frankfurt","Berlin","Barcelona","Madrid","Amsterdam","Stockholm","Oslo","Hanoi",
    "Bangkok","KualaLumpur","Singapore","Sydney","SaoPaulo","Cairo","Beijing","Nairobi",
	"Cancun","BuenosAires","Reykjavik","Glasgow","Warsow","Istanbul","Dubai","CapeTown",
	"Unrecognized"
};

typedef struct ifs_ele {
	int index; //number
	int age; //age
	int time; //time
	//place_t place[N_HISTORY]; //place[N_HISTORY] 수정하기 전, 밑에가 수정 후  
	char place[N_HISTORY];
} ifs_ele_t;



//아래 함수를 통해 만들어진 구조체 변수가 가르키는 주소가  함수의 반환값이 되어서 나옴
//이를 main.c에서 ifc_element가 받을 예정 
//메인에서 ifc_element를 반환값으로 받고 이를 linked list에 넣는다. adddTail사용하라는데 무슨의미일까
 
void* ifctele_getElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
{
	int i;
	//main.c에서 각 정보를 받아와 ifs_ele_t 구조체에 넣는 함수
	ifs_ele_t* ptr;
	ptr = malloc(sizeof(ifs_ele_t));
	ptr->index=index;	
	ptr->age=age;
	ptr->time=detected_time;
	
	
	for(i = 0; i < N_HISTORY; i++){
		ptr->place[i] = history_place[i];	 //-> 일단 인덱스 잘 출력됨. 
		//ptr->place[i] = countryName[history_place[i]]; // -> 의도는 이러함 돌아가지는 않는다. 
	}

	//printf("%d %d %d",ptr->index,ptr->age,ptr->time);  
	return ptr;	
}


int ifctele_getAge(int obj, int obj2)
{
	int i;	 
	int cnt=0;
	
	//printf("%d %d",obj,obj2); 
	//obj는 최솟값, obj2는 최댓값으로 매개변수로 넘어온 것 
	//입력마다 수행해야 하기 때문에 void 포인터를 쓰지 않아도 된다
	
	for(i=0; i<5; i++){ 

	
		ifs_ele_t* ptr = (ifs_ele_t*)ifctdb_getData(i);
		//최댓값, 최솟값, 환자 나이 잘 나오는지 테스트 
		//printf("%d %d %d \n",obj,obj2,ptr->age);
		
		//긱 환자의 나이를 pAge 변수로 저장	
		int pAge = ptr-> age;
	
		//pAge가 최솟값 obj보다 크거나 같고, 
		//최댓값 obj2보다 작거나 같으면 
		//그 확자의 정보 출력 
		
		if( obj <= pAge && obj2 >= pAge ) {
			printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
			cnt++;
			ifctele_printElement(ifctdb_getData(i));
		}			
	}
	
	//몇명의 확자가 있는지도 추가 출력 , 예제 프로그램과 형식 맞추기 
	printf("Threr are %d patients whose age between %d and %d\n\n",cnt,obj,obj2);
	return 0;
}

//int ifctele_getHistPlaceIndex(void* obj, int index); -> 기존의 baseCode 
int ifctele_getHistPlaceIndex(void* s,int i){
	int cnt=0;
	
//매개변수가 잘 넘어왔는지 확인한 코드 
//	printf("%s",s); 

	ifs_ele_t* ptr = (ifs_ele_t*)ifctdb_getData(i);
	//s== countryName[~] 가 만족하는 경우가 없어서 테스트하기 위해 작성한  코드 
	//printf("%s %s",s,countryName[ptr->place[N_HISTORY-1]]);
		
	int compare = strcmp(s,countryName[ptr->place[N_HISTORY-1]]);
	if(compare==0){
		//두 문자가 같다는 의미이므로 i idnex의 환자 정보 출력
		ifctele_printElement(ifctdb_getData(i));
		cnt++;
	}
	
	//몇명의 확자가 있는지도 추가 출력 , 예제 프로그램과 형식 맞추기 
	//+수정, 반환값을 조건을 만족하는 환자의수로 반환해보자  

	return cnt;	
}


unsigned int ifctele_getinfestedTime(void* obj){
	int i; int j;
	
	int track_1[100];
	int track_2[100];
	
	for(i=0; i<5; i++){
		ifs_ele_t* ptr = (ifs_ele_t*)ifctdb_getData(i); //기준 인덱스의 () 선언 
		int a = ptr->time;
		track_1[ptr->time]  =ptr->place[4];
		track_1[ptr->time-1]=ptr->place[3];
		track_1[ptr->time-2]=ptr->place[2];
		track_1[ptr->time-3]=ptr->place[1];
		track_1[ptr->time-4]=ptr->place[0];
		
		for(j=0; j<5; j++){
			int k;
			if(i==j){
				continue;
			}
			ifs_ele_t* ptr2 = (ifs_ele_t*)ifctdb_getData(j); //비교 인덱스가 될 () 선언
			int b = ptr2->time;
			if(a>b){
				continue; 
				//추적 조건에 만족하지 않으므로 밑에 코드 수행하지 않고 i++  
			}
			
			//밑의 조건들이 중요해보인다 -> 연산 횟수를 감소할 수 있음. 
			//ptr2->time, ptr2->time-1 만 유효한 값이다
			//위의 값들이 a-4~ a까지의 사이에 있냐. 그 공통된 값들만 탐색
			//밑의 코드가 그 구현 
			if(   (ptr2->time) >= a-4 && (ptr2->time) <=a ){
					if(   track_1[ptr->time] == ptr2->place[4] ){
						// index j번째는 i번째를 감염시킨 것이다
						//위의 두 피연산자는 논리적으로 (방문나라)로 매핑되기 때문에 짠 코드
						printf("%d 번째의 환자는 %d번째 환자에게 전염되었습니다\n",i,j); 
					}
			}
			
		
		
		}		 
	}
	
}


void ifctele_printElement(void* obj)
{
	int i;
	ifs_ele_t* ptr = (ifs_ele_t*)obj; 
	printf("Patient index: %i\n", ptr->index);
	printf("Patient age: %i\n", ptr->age);
	printf("Detected time: %i\n", ptr->time);
	
	//인덱스를 밑의 기존의 함수 ifctele_getPlaceName 함수의 매개변수로 전달하여 그대로 출력하면 되었다 
	for(i = 0; i < N_HISTORY; i++){
		printf(ifctele_getPlaceName(ptr->place[i]));
		
		//마지막 인덱스에서는 화살표를 출력하지 않기 위한 코드 (기능적X) 
		if(i==(N_HISTORY-1)){
			break;
		}
		printf("->");
	}
	printf("\n- - - - - - - - - - - - - - - - - - - -\n");
	
	//장소 이름으로 대체만 하면된다
	//성공 
}

char* ifctele_getPlaceName(int placeIndex)
{
	return countryName[placeIndex];
}
