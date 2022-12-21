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
		
		//��  ȯ���� ���̸� pAge ������ ����	
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
int ifctele_getHistPlaceIndex(void* s){
	
	int i;	int cnt=0;
	for(i=0; i<5; i++){ 
		ifs_ele_t* ptr = (ifs_ele_t*)ifctdb_getData(i);
		//s== countryName[~] �� �����ϴ� ��찡 ��� �׽�Ʈ�ϱ� ���� �ۼ���  �ڵ� 
		//printf("%s %s",s,countryName[ptr->place[N_HISTORY-1]]);

		int compare = strcmp(s,countryName[ptr->place[N_HISTORY-1]]);
		if(compare==0){
			ifctele_printElement(ifctdb_getData(i));
			cnt+=1;

		}
	}
	
	printf("%s���� ",s); //��� ���, ���(cnt)�� ��ȯ������ �����Ͽ� �����Լ����� �̾ ����ϵ��� �ڵ� 
	return cnt;
}

//���� ������ ������ ���� �迭 ���� �߰�, ���� ���� �Ǵ��� ���� -1�� �ʱ�ȭ 
static int fst_arr[5] = {-1,-1,-1,-1,-1};

//+unsigned ifctele_getinfestedTime(void* obj); -> ���� �ڵ� ���� , �� ���Ĵ�� �ϴϱ� �Ű������� ����� �ȳѾ�� 
int ifctele_getinfestedTime(int obj){
	int i; 
	int track_1[20];
	//printf("%d",obj); �Ű����� ����� �Ѿ�Դ��� Ȯ��  
	
	//obj = pIndex;
	ifs_ele_t* ptr = (ifs_ele_t*)ifctdb_getData(obj); //���� �ε����� () ���� 

	int a = ptr->time;
	//���ν�Ű�� ���� 
	track_1[ptr->time]  =ptr->place[4];
	track_1[ptr->time-1]=ptr->place[3];
	track_1[ptr->time-2]=ptr->place[2];
	track_1[ptr->time-3]=ptr->place[1];
	track_1[ptr->time-4]=ptr->place[0];
	
	
	for(i=0; i<5; i++){
		if(obj==i){
			//������ ���ϴ� ���̹Ƿ� 
			continue;
		}
		ifs_ele_t* ptr2 = (ifs_ele_t*)ifctdb_getData(i); //�� �ε����� �� () ����
		int b = ptr2->time;
		
		if(a<b){
			continue; 
			//���� ���ǿ� �������� �����Ƿ� �ؿ� �ڵ� �������� �ʰ� i++  
		}
		
		//���� ���ǵ��� �߿��غ��δ� -> ���� Ƚ���� ������ �� ����. 
		//ptr2->time, ptr2->time-1 �� ��ȿ�� ���̴�
		//���� ������ a-4~ a������ ���̿� �ֳ�. �� ����� ���鸸 Ž��
		//���� �ڵ尡 �� ����
		
		 
//		�׽�Ʈ �뵵	-> ptr-> tiem�� ptr2->time ���� ���� ��� �ذ�	
//		printf("%d %d\n",ptr2->place[4], track_1[ptr2->time]);
//		printf("%d %d\n\n\n",ptr2->place[3], track_1[ptr2->time-1]);
	
		if(   (ptr2->time) >= a-4 && (ptr2->time) <=a ){
			if(   track_1[ptr2->time] == ptr2->place[4] ){
				// index j��°�� i��°�� ������Ų ���̴�
				//���� �� �ǿ����ڴ� �������� (�湮����)�� ���εǱ� ������ § �ڵ�
				printf("%d ��°�� ȯ�ڴ� %d��° ȯ�ڿ��� �����Ǿ����ϴ�\n",obj,i);
				printf("�����ð�: %d, �������: %s (%d)\n",ptr2->time,ifctele_getPlaceName(ptr2->place[4]),ptr2->place[4]);
				
				//arr[������] = ������ 
				//arr[obj]�� ���� �̹� �ִٸ�, ���� �����ڴ� ��������� �� 
				if(fst_arr[obj]!=-1){
					fst_arr[obj] = fst_arr[i]; 
					//1���� ������ -> 0������ 
					//0���� ������ -> 2�� ������ ����
					
				} else{
					//�����ڰ� ���� ���Ľ�Ų ȯ�ڰ� ������ 
					//���� ��Ȳ�� �迭�� ����ϰ� �Ѿ�� 
					fst_arr[obj]=i;
					
				}
				printf("%d\n\n",fst_arr[obj]); 
			}
		}
		
		if(   (ptr2->time-1) >= a-4 && (ptr2->time-1) <=a ){
			if(   track_1[ptr2->time-1] == ptr2->place[3] ){
				// index j��°�� i��°�� ������Ų ���̴�
				//���� �� �ǿ����ڴ� �������� (�湮����)�� ���εǱ� ������ § �ڵ�
				printf("%d ��°�� ȯ�ڴ� %d��° ȯ�ڿ��� �����Ǿ����ϴ�\n",obj,i); 
				printf("�����ð�: %d, �������: %s (%d)\n",ptr2->time-1,ifctele_getPlaceName(ptr2->place[3]),ptr2->place[3]);
				

				
				//arr[������] = ������ 
				//arr[obj]�� ���� �̹� �ִٸ�, ���� �����ڴ� ��������� �� 
				if(fst_arr[obj]!=-1){
					fst_arr[obj] = fst_arr[i]; 
					//1���� ������ -> 0������ 
					//0���� ������ -> 2�� ������ ����
					
				} else{
					//�����ڰ� ���� ���Ľ�Ų ȯ�ڰ� ������ 
					//���� ��Ȳ�� �迭�� ����ϰ� �Ѿ�� 
					fst_arr[obj]=i;
					
				}
				printf("%d\n\n",fst_arr[obj]); 

	
			}
		}
		
	}
	
	if(obj==fst_arr[obj]){
		printf("\n���� �����ڴ� %d�� ȯ�� �����Դϴ�",i);
	} else{
		printf("\���� �����ڴ� %d��° ȯ���Դϴ�",fst_arr[obj]); 
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
	
	//�ε����� ���� ������ �Լ� ifctele_getPlaceName �Լ��� �Ű������� �����Ͽ� �״�� ����ϸ� �Ǿ��� 
	for(i = 0; i < N_HISTORY; i++){
		printf(ifctele_getPlaceName(ptr->place[i]));
		printf("(%d)",ptr->place[i]);
		
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
