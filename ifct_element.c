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
	//place_t place[N_HISTORY]; //place[N_HISTORY] �����ϱ� ��, �ؿ��� ���� ��  
	char place[N_HISTORY];
} ifs_ele_t;



//�Ʒ� �Լ��� ���� ������� ����ü ������ ����Ű�� �ּҰ�  �Լ��� ��ȯ���� �Ǿ ����
//�̸� main.c���� ifc_element�� ���� ���� 
//���ο��� ifc_element�� ��ȯ������ �ް� �̸� linked list�� �ִ´�. adddTail����϶�µ� �����ǹ��ϱ�
 
void* ifctele_getElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
{
	int i;
	//main.c���� �� ������ �޾ƿ� ifs_ele_t ����ü�� �ִ� �Լ�
	ifs_ele_t* ptr;
	ptr = malloc(sizeof(ifs_ele_t));
	ptr->index=index;	
	ptr->age=age;
	ptr->time=detected_time;
	
	
	for(i = 0; i < N_HISTORY; i++){
		ptr->place[i] = history_place[i];	 //-> �ϴ� �ε��� �� ��µ�. 
		//ptr->place[i] = countryName[history_place[i]]; // -> �ǵ��� �̷��� ���ư����� �ʴ´�. 
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
		//�ε����� ���� ������ �Լ� ifctele_getPlaceName �Լ��� �Ű������� �����Ͽ� �״�� ����ϸ� �Ǿ��� 
		printf(ifctele_getPlaceName(ptr->place[i]));
		printf(" ");
	}
	//��� �̸����� ��ü�� �ϸ�ȴ�
	//12.17 ���� 
}

char* ifctele_getPlaceName(int placeIndex)
{
	return countryName[placeIndex];
}
