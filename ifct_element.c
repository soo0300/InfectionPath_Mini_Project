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
{   "Seoul","Jeju","Tokyo","LosAngeles","NewYork","Texas","Toronto","Paris","Nice",
	"Rome","Milan","London","Manchester","Basel","Luzern","Munich","Frankfurt","Berlin",
	"Barcelona","Madrid","Amsterdam","Stockholm","Oslo","Hanoi","Bangkok","KualaLumpur",
	"Singapore","Sydney","SaoPaulo","Cairo","Beijing","Nairobi","Cancun","BuenosAires",
	"Reykjavik","Glasgow","Warsow","Istanbul","Dubai","CapeTown","Unrecognized"
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
		
		//각  환자의 나이를 pAge 변수로 저장	
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
int ifctele_getHistPlaceIndex(void* s){
	
	int i;	int cnt=0;
	for(i=0; i<5; i++){ 
		ifs_ele_t* ptr = (ifs_ele_t*)ifctdb_getData(i);
		//s== countryName[~] 가 만족하는 경우가 없어서 테스트하기 위해 작성한  코드 
		//printf("%s %s",s,countryName[ptr->place[N_HISTORY-1]]);

		int compare = strcmp(s,countryName[ptr->place[N_HISTORY-1]]);
		if(compare==0){
			ifctele_printElement(ifctdb_getData(i));
			cnt+=1;

		}
	}
	
	printf("%s에서 ",s); //장소 출력, 명수(cnt)는 반환값으로 전달하여 메인함수에서 이어서 출력하도록 코딩 
	return cnt;
}

//최초 전파자 연산을 위한 배열 변수 추가, 연산 유무 판단을 위해 -1로 초기화 
static int fst_arr[5] = {-1,-1,-1,-1,-1};

//+unsigned ifctele_getinfestedTime(void* obj); -> 기존 코드 한줄 , 이 형식대로 하니까 매개변수가 제대로 안넘어옴 
int ifctele_getinfestedTime(int obj){
	int i; 
	int track_1[20];
	//printf("%d",obj); 매개변수 제대로 넘어왔는지 확인  
	
	//obj = pIndex;
	ifs_ele_t* ptr = (ifs_ele_t*)ifctdb_getData(obj); //기준 인덱스의 () 선언 

	int a = ptr->time;
	//매핑시키는 과정 
	track_1[ptr->time]  =ptr->place[4];
	track_1[ptr->time-1]=ptr->place[3];
	track_1[ptr->time-2]=ptr->place[2];
	track_1[ptr->time-3]=ptr->place[1];
	track_1[ptr->time-4]=ptr->place[0];
	
	
	for(i=0; i<5; i++){
		if(obj==i){
			//본인을 비교하는 것이므로 
			continue;
		}
		ifs_ele_t* ptr2 = (ifs_ele_t*)ifctdb_getData(i); //비교 인덱스가 될 () 선언
		int b = ptr2->time;
		
		if(a<b){
			continue; 
			//추적 조건에 만족하지 않으므로 밑에 코드 수행하지 않고 i++  
		}
		
		//밑의 조건들이 중요해보인다 -> 연산 횟수를 감소할 수 있음. 
		//ptr2->time, ptr2->time-1 만 유효한 값이다
		//위의 값들이 a-4~ a까지의 사이에 있냐. 그 공통된 값들만 탐색
		//밑의 코드가 그 구현
		
		 
//		테스트 용도	-> ptr-> tiem을 ptr2->time 으로 추적 기능 해결	
//		printf("%d %d\n",ptr2->place[4], track_1[ptr2->time]);
//		printf("%d %d\n\n\n",ptr2->place[3], track_1[ptr2->time-1]);
	
		if(   (ptr2->time) >= a-4 && (ptr2->time) <=a ){
			if(   track_1[ptr2->time] == ptr2->place[4] ){
				// index j번째는 i번째를 감염시킨 것이다
				//위의 두 피연산자는 논리적으로 (방문나라)로 매핑되기 때문에 짠 코드
				printf("%d 번째의 환자는 %d번째 환자에게 전염되었습니다\n",obj,i);
				printf("전염시간: %d, 전염장소: %s (%d)\n",ptr2->time,ifctele_getPlaceName(ptr2->place[4]),ptr2->place[4]);
				
				//arr[감염자] = 전파자 
				//arr[obj]의 값이 이미 있다면, 최초 전파자는 연결해줘야 함 
				if(fst_arr[obj]!=-1){
					fst_arr[obj] = fst_arr[i]; 
					//1번의 전파자 -> 0번에서 
					//0번의 전파자 -> 2번 값으로 연결
					
				} else{
					//전파자가 전에 전파시킨 환자가 없으면 
					//현재 상황을 배열에 기록하고 넘어간다 
					fst_arr[obj]=i;
					
				}
				printf("%d\n\n",fst_arr[obj]); 
			}
		}
		
		if(   (ptr2->time-1) >= a-4 && (ptr2->time-1) <=a ){
			if(   track_1[ptr2->time-1] == ptr2->place[3] ){
				// index j번째는 i번째를 감염시킨 것이다
				//위의 두 피연산자는 논리적으로 (방문나라)로 매핑되기 때문에 짠 코드
				printf("%d 번째의 환자는 %d번째 환자에게 전염되었습니다\n",obj,i); 
				printf("전염시간: %d, 전염장소: %s (%d)\n",ptr2->time-1,ifctele_getPlaceName(ptr2->place[3]),ptr2->place[3]);
				

				
				//arr[감염자] = 전파자 
				//arr[obj]의 값이 이미 있다면, 최초 전파자는 연결해줘야 함 
				if(fst_arr[obj]!=-1){
					fst_arr[obj] = fst_arr[i]; 
					//1번의 전파자 -> 0번에서 
					//0번의 전파자 -> 2번 값으로 연결
					
				} else{
					//전파자가 전에 전파시킨 환자가 없으면 
					//현재 상황을 배열에 기록하고 넘어간다 
					fst_arr[obj]=i;
					
				}
				printf("%d\n\n",fst_arr[obj]); 

	
			}
		}
		
	}
	
	if(obj==fst_arr[obj]){
		printf("\n최초 전파자는 %d번 환자 본인입니다",i);
	} else{
		printf("\최초 전파자는 %d번째 환자입니다",fst_arr[obj]); 
	}
	return 0;
	

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
		printf("(%d)",ptr->place[i]);
		
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
