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


int ifctele_getAge(int obj, int obj2)
{
	int i;	 
	int cnt=0;
	
	//printf("%d %d",obj,obj2); 
	//obj�� �ּڰ�, obj2�� �ִ����� �Ű������� �Ѿ�� �� 
	//�Է¸��� �����ؾ� �ϱ� ������ void �����͸� ���� �ʾƵ� �ȴ�
	
	for(i=0; i<5; i++){ 

	
		ifs_ele_t* ptr = (ifs_ele_t*)ifctdb_getData(i);
		//�ִ�, �ּڰ�, ȯ�� ���� �� �������� �׽�Ʈ 
		//printf("%d %d %d \n",obj,obj2,ptr->age);
		
		//�� ȯ���� ���̸� pAge ������ ����	
		int pAge = ptr-> age;
	
		//pAge�� �ּڰ� obj���� ũ�ų� ����, 
		//�ִ� obj2���� �۰ų� ������ 
		//�� Ȯ���� ���� ��� 
		
		if( obj <= pAge && obj2 >= pAge ) {
			printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
			cnt++;
			ifctele_printElement(ifctdb_getData(i));
		}			
	}
	
	//����� Ȯ�ڰ� �ִ����� �߰� ��� , ���� ���α׷��� ���� ���߱� 
	printf("Threr are %d patients whose age between %d and %d\n\n",cnt,obj,obj2);
	return 0;
}

//int ifctele_getHistPlaceIndex(void* obj, int index); -> ������ baseCode 
int ifctele_getHistPlaceIndex(void* s,int i){
	int cnt=0;
	
//�Ű������� �� �Ѿ�Դ��� Ȯ���� �ڵ� 
//	printf("%s",s); 

	ifs_ele_t* ptr = (ifs_ele_t*)ifctdb_getData(i);
	//s== countryName[~] �� �����ϴ� ��찡 ��� �׽�Ʈ�ϱ� ���� �ۼ���  �ڵ� 
	//printf("%s %s",s,countryName[ptr->place[N_HISTORY-1]]);
		
	int compare = strcmp(s,countryName[ptr->place[N_HISTORY-1]]);
	if(compare==0){
		//�� ���ڰ� ���ٴ� �ǹ��̹Ƿ� i idnex�� ȯ�� ���� ���
		ifctele_printElement(ifctdb_getData(i));
		cnt++;
	}
	
	//����� Ȯ�ڰ� �ִ����� �߰� ��� , ���� ���α׷��� ���� ���߱� 
	//+����, ��ȯ���� ������ �����ϴ� ȯ���Ǽ��� ��ȯ�غ���  

	return cnt;	
}


unsigned int ifctele_getinfestedTime(void* obj){
	int i; int j;
	
	int track_1[100];
	int track_2[100];
	
	for(i=0; i<5; i++){
		ifs_ele_t* ptr = (ifs_ele_t*)ifctdb_getData(i); //���� �ε����� () ���� 
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
			ifs_ele_t* ptr2 = (ifs_ele_t*)ifctdb_getData(j); //�� �ε����� �� () ����
			int b = ptr2->time;
			if(a>b){
				continue; 
				//���� ���ǿ� �������� �����Ƿ� �ؿ� �ڵ� �������� �ʰ� i++  
			}
			
			//���� ���ǵ��� �߿��غ��δ� -> ���� Ƚ���� ������ �� ����. 
			//ptr2->time, ptr2->time-1 �� ��ȿ�� ���̴�
			//���� ������ a-4~ a������ ���̿� �ֳ�. �� ����� ���鸸 Ž��
			//���� �ڵ尡 �� ���� 
			if(   (ptr2->time) >= a-4 && (ptr2->time) <=a ){
					if(   track_1[ptr->time] == ptr2->place[4] ){
						// index j��°�� i��°�� ������Ų ���̴�
						//���� �� �ǿ����ڴ� �������� (�湮����)�� ���εǱ� ������ § �ڵ�
						printf("%d ��°�� ȯ�ڴ� %d��° ȯ�ڿ��� �����Ǿ����ϴ�\n",i,j); 
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
	
	//�ε����� ���� ������ �Լ� ifctele_getPlaceName �Լ��� �Ű������� �����Ͽ� �״�� ����ϸ� �Ǿ��� 
	for(i = 0; i < N_HISTORY; i++){
		printf(ifctele_getPlaceName(ptr->place[i]));
		
		//������ �ε��������� ȭ��ǥ�� ������� �ʱ� ���� �ڵ� (�����X) 
		if(i==(N_HISTORY-1)){
			break;
		}
		printf("->");
	}
	printf("\n- - - - - - - - - - - - - - - - - - - -\n");
	
	//��� �̸����� ��ü�� �ϸ�ȴ�
	//���� 
}

char* ifctele_getPlaceName(int placeIndex)
{
	return countryName[placeIndex];
}
