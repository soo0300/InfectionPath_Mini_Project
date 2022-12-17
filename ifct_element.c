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


int ifctele_getAge(void* obj, void* obj2)
{
	int i;	 
	
	printf("%d %d",obj,obj2);
	
	for(i=0; i<5; i++){ 
		ifs_ele_t* ptr = (ifs_ele_t*)ifctdb_getData(i);
		if( obj <= (ptr->age) && obj2 >= (ptr->age) ) {
			ifctele_printElement(ifctdb_getData(i));
			
		}
			
	}
	
	return 0;
	//return ptr->age;
}


int ifctele_getHistPlaceIndex(void* obj, int index);
unsigned int ifctele_getinfestedTime(void* obj);


void ifctele_printElement(void* obj)
{
	int i;
	ifs_ele_t* ptr = (ifs_ele_t*)obj; 
	printf("NUM : %i\n", ptr->index);
	printf("Age : %i\n", ptr->age);
	printf("Time: %i\n", ptr->time);
	
	for(i = 0; i < N_HISTORY; i++){
		//인덱스를 밑의 기존의 함수 ifctele_getPlaceName 함수의 매개변수로 전달하여 그대로 출력하면 되었다 
		printf(ifctele_getPlaceName(ptr->place[i]));
		printf(" ");
	}
	//장소 이름으로 대체만 하면된다
	//12.17 성공 
}

char* ifctele_getPlaceName(int placeIndex)
{
	return countryName[placeIndex];
}
