#define _CRT_SECURE_NO_WARNINGS //이전 버전에서 사용되던 메모리 관련 명령어들 및 이를 이용한 출력문이 갖고 있는 잠재적인 문제점들(보안, 메모리 등)에 대한 경고에러를 해결하기 위해 정의.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//대출 가능 여부
#define POSSIBLE 1
#define IMPOSSIBLE 0
#ifndef time_H //time을 구조체로 선언하면 재정의하라는 오류가 발생. 오류에 대한 해결방법으로 #ifndef #define #endif를 기재하면 해결된다.
#define time_H

int RentalSize = 0;

struct time { //현재날짜를 구하기 위해 구조체 정의
	int sec;   /* Seconds */
	int min;   /* Minutes */
	int hour;  /* Hour (0--23) */
	int mday;  /* Day of month (1--31) */
	int mon;   /* Month (0--11) */
	int year;  /* Year (calendar year minus 1900) */
	int wday;  /* Weekday (0--6; Sunday = 0) */
	int yday;  /* Day of year (0--365) */
	int isdst; /* 0 if daylight savings time is not in effect) */
};

#endif

typedef struct customer { //고객명단 구조체
	char nm[10];
	int pn;
	int birth;
	struct customer *link;
} customer;

typedef struct {
	customer *head;
} linkedList;
/////////////////////////////////////////////////
typedef struct dvd { //DVD 구조체
	char title[20]; //제목
	char genre[10]; //장르
	int release; //출시연도
	int rented; //대여여부(가능하면 1 불가능하면 0)
	struct dvd *link;
} dvd;

typedef struct {
	dvd *head;
} dvdLinkedList;
/////////////////////////////////////////////////
typedef struct rent {
	char topic[20]; //DVD제목
	char people[10]; //대여한 고객
	int rentDate; //대여날짜
	int returnDate; //반납날짜
	char overdue[10]; //연체여부(O,X로 표시)
	struct rent *link;
} rent;

typedef struct {
	rent *head;
} rentLinkedList;

rent *firstRentalInfoNode = NULL;
rent *lastRentalInfoNode = NULL;
/*대여된 DVD정보를 표시(제목, 대여한 고객, 대여날짜, 반납날짜, 연체여부), 표시가 된 DVD는 DVD검색 함수에서 대여여부가 0으로 바뀌어야한다*/
//DVD대여는 입력, DVD대여여부는 탐색, DVD반납은 대여여부에서 삭제함수로 만들면 된다.
///////////////////////////////////////////////
typedef struct od {
	char overDvName[20];
	char overCuName[10];
	int overdueNumber;
	struct od *link;
} od;

typedef struct {
	od *head;
} odLinkedList;

od *firstPersonNode = NULL;
od *lastPersonNode = NULL;
/////////////////////////////////////////

linkedList *createLinkedList(void) { //고객 명단 연결리스트 생성
	linkedList* L;
	L = (linkedList *)malloc(sizeof(linkedList));
	L->head = NULL;
	return L;
}
////////////////////////////////////////
dvdLinkedList *createDvdLinkedList(void) { //DVD 연결리스트 생성
	dvdLinkedList* D;
	D = (dvdLinkedList *)malloc(sizeof(dvdLinkedList));
	D->head = NULL;
	return D;
}
/////////////////////////////////////////
rentLinkedList *createRentLinkedList(void) { //대여한 DVD 연결리스트 생성
	rentLinkedList* R;
	R = (rentLinkedList *)malloc(sizeof(rentLinkedList));
	R->head = NULL;
	return R;
}

odLinkedList *createOdLinkedList(void) {
	odLinkedList* O;
	O = (odLinkedList *)malloc(sizeof(odLinkedList));
	O->head = NULL;
	return O;
}

void newMemberInput(linkedList* L, char* name, int phoneNumber, int private) { //신규고객 입력
	customer* newNode;
	customer* temp;
	newNode = (customer*)malloc(sizeof(customer));
	strcpy(newNode->nm, name);
	newNode->pn = phoneNumber;
	newNode->birth = private;
	newNode->link = NULL;
	if (L->head == NULL) {
		L->head = newNode;
		return;
	}
	temp = L->head;
	while (temp->link != NULL) temp = temp->link;
	temp->link = newNode;
}

void rentInformationInput(rentLinkedList* R, char* title, char* name, int give, int receive, char* ox) { //대여하는 DVD 정보 입력
	rent* newNode;
	rent* temp;
	newNode = (rent*)malloc(sizeof(rent));
	strcpy(newNode->topic, title);
	strcpy(newNode->people, name);
	newNode->rentDate = give;
	newNode->returnDate = receive;
	strcpy(newNode->overdue, ox);
	newNode->link = NULL;
	if (R->head == NULL) {
		R->head = newNode;
		return;
	}
	temp = R->head;
	while (temp->link != NULL) temp = temp->link;
	temp->link = newNode;
}

void newDvdInput(dvdLinkedList* D, char* ti, char* ge, int rel, int ren) { //새로운 DVD 입력
	dvd* newNode;
	dvd* temp;
	newNode = (dvd*)malloc(sizeof(dvd));
	strcpy(newNode->title, ti);
	strcpy(newNode->genre, ge);
	newNode->release = rel;
	newNode->rented = ren;
	newNode->link = NULL;
	if (D->head == NULL) {
		D->head = newNode;
		return;
	}
	temp = D->head;
	while (temp->link != NULL) temp = temp->link;
	temp->link = newNode;
}

void originalDvdInput(dvdLinkedList *D, char* ti, char* ge, int rel, int ren) { //기존에 존재하는 DVD 입력
	dvd* newNode;
	newNode = (dvd*)malloc(sizeof(dvd));
	strcpy(newNode->title, ti);
	strcpy(newNode->genre, ge);
	newNode->release = rel;
	newNode->rented = ren;
	newNode->link = D->head;
	D->head = newNode;
}

void odInput(odLinkedList* O, char* dn, char* cn, int overdueNum) { //연체 정보 입력
	od* newNode;
	od* temp;
	newNode = (od*)malloc(sizeof(od));
	strcpy(newNode->overDvName, dn);
	strcpy(newNode->overCuName, cn);
	newNode->overdueNumber = overdueNum;
	newNode->link = NULL;
	if (O->head == NULL) {
		O->head = newNode;
		return;
	}
	temp = O->head;
	while (temp->link != NULL) temp = temp->link;
	temp->link = newNode;
}

void deleteMember(linkedList* L, customer* p) { //고객명단 삭제
	customer* pre;
	if(L->head == NULL) return;
	if (L->head->link == NULL) {
		free(L->head);
		L->head = NULL;
		return;
	}
	else if (p == NULL) return;
	else {
		pre = L->head;
		while (pre->link != p) {
			pre = pre->link;
		}
		pre->link = p->link;
		free(p);
	}
}

void deleteRent(rentLinkedList* R, rent* u) { //대여한 DVD 반납
	rent* pre;
	if (R->head == NULL) return;
	if (R->head->link == NULL) {
		free(R->head);
		R->head = NULL;
		return;
	}
	else if (u == NULL) return;
	else {
		pre = R->head;
		while (pre->link != u) {
			pre = pre->link;
		}
		pre->link = u->link;
		free(u);
	}
}

void deleteDvd(dvdLinkedList* D, dvd* o) { //DVD 삭제
	dvd* pre;
	if (D->head == NULL) return;
	if (D->head->link == NULL) {
		free(D->head);
		D->head = NULL;
		return;
	}
	else if (o == NULL) return;
	else {
		pre = D->head;
		while (pre->link != o) {
			pre = pre->link;
		}
		pre->link = o->link;
		free(o);
	}
}

customer* searchMember(linkedList *L, char* x) { //고객삭제를 위한 검색
	customer *temp;
	temp = L->head;
	while (temp != NULL) {
		if (strcmp(temp->nm, x) == 0) return temp;
		else temp = temp->link;
	}
	return temp;
}

rent* searchRent(rentLinkedList *R, char* x) { //반납하는 DVD삭제를 위한 검색
	rent *temp;
	temp = R->head;
	while (temp != NULL) {
		if (strcmp(temp->topic, x) == 0) return temp;
		else temp = temp->link;
	}
	return temp;
}

dvd* searchDvd(dvdLinkedList *D, char* x) { //DVD삭제를 위한 검색
	dvd *temp;
	temp = D->head;
	while (temp != NULL) {
		if (strcmp(temp->title, x) == 0) return temp;
		else temp = temp->link;
	}
	return temp;
}
/*
dvd* rented(dvdLinkedList *D, char *x) {
	dvd *temp;
	temp = D->head;
	while (temp != NULL) {
		if (strcmp(temp->title, x) == 0) temp->rented == 0;
		else temp = temp->link;
	}
}


int member() { //고객관리
return 0;
}
*/

void memberSearch(linkedList *L) { //고객검색
	customer *p;
	printf("---------------------------------------------------------------\n");
	printf("                        고객님 명단                             \n\n");
	p = L->head;
	if (p == NULL) printf("\n\n                   데이터가 존재하지 않습니다.              \n\n\n\n");
	while (p != NULL) {
			printf("                ***************************\n");
			printf("                *      성함: %s       *\n", p->nm);
			printf("                *  전화번호: %d   *\n", p->pn);
			printf("                *  생년월일: %d       *\n", p->birth);
			printf("                ***************************\n");
			p = p->link;
	}
	printf("---------------------------------------------------------------\n");
}

void rentSearch(rentLinkedList *R) { //대여현황
	rent *u;
	printf("---------------------------------------------------------------\n");
	printf("                          대여 현황                             \n\n");
	u = R->head;
	if (u == NULL) printf("\n\n                   데이터가 존재하지 않습니다.              \n\n\n\n");
	while (u != NULL) {
		printf("                ***************************\n");
		printf("                       제목: %s        \n", u->topic);
		printf("                 대여하신분: %s    \n", u->people);
		printf("                   대여날짜: %d        \n", u->rentDate);
		printf("                   반납날짜: %d        \n", u->returnDate);
		printf("                   연체여부: %s        \n", u->overdue);
		printf("                ***************************\n");
		u = u->link;
	}
}

void dvdSearch(dvdLinkedList *D) { //DVD 검색
	dvd *o;
	printf("---------------------------------------------------------------\n");
	printf("                            DVD                              \n\n");
	o = D->head;
	if (o == NULL) printf("\n\n                   데이터가 존재하지 않습니다.              \n\n\n\n");
	while (o != NULL) {
		printf("                ***************************\n");
		printf("                       제목: %s        \n", o->title);
		printf("                       장르: %s    \n", o->genre);
		printf("                   개봉연도: %d        \n", o->release);
		printf("                   대여여부: %d        \n", o->rented);
		printf("                ***************************\n");
		o = o->link;
	}
	printf("---------------------------------------------------------------\n");
}

void overdue(odLinkedList *O) { //연체된 DVD 정보
	od *y;
	printf("---------------------------------------------------------------\n\n");
	printf("                         연체정보                              \n\n");
	y = O->head;
	if (y == NULL) printf("\n\n                   데이터가 존재하지 않습니다.              \n\n\n\n");
	while (y != NULL) {
	printf("                ***************************\n");
	printf("                 연체된 DVD: %s        \n", y->overDvName);
	printf("                 연체고객님: %s    \n", y->overCuName);
	printf("                ***************************\n");
	y = y->link;
	}
	printf("\n---------------------------------------------------------------\n");
}

/*
overdueCustomer overdueName(char* overDvName, char* overCuName) { //연체 고객 이름, DVD제목을 리턴하는 함수
	overdueCustomer g;
	g.overDvName[20] = overDvName;
	g.overCuName[10] = overCuName;
	return g;
}
*/

void overdueMember(odLinkedList *O) { //연체 고객 리스트
	od *y;
	od e;
	printf("---------------------------------------------------------------\n\n");
	printf("                      연체 고객리스트                              \n\n");
	y = O->head;
	if (y == NULL) printf("\n\n                   데이터가 존재하지 않습니다.              \n\n\n\n");
	while (y != NULL) {
		printf("                ***************************\n");
		printf("                 연체고객님: %s    \n", y->overCuName);
		printf("                   연체횟수: %d    \n", y->overdueNumber);
		printf("                ***************************\n");
		//if (strcmp(y->overCuName, y) == 0) return temp;
		y = y->link;
	}
	printf("\n---------------------------------------------------------------\n");
}

void returnDelay() {
	char* rentalPersonName = malloc(sizeof(char) * 30); // 검색하고 싶은 이름이 저장되는 문자열 변수
	int i = 0; // 가입된 손님 정보 갯수 만큰 for문 돌리기 위해 선언!
	int j = 0; // 대여 횟수 만큼 for을 돌리기 위해 선언!
	int returnDelay = 0;
	rent *temp = firstRentalInfoNode;//
	od *tempPerson = firstPersonNode; // 첫번째 가입정보를 입력!!
		printf("\n고객의 대여 정보의 연체 처리를 위해 이름을 입력해주세요\n");
	scanf_s("%s", rentalPersonName, sizeof(rentalPersonName));
	fflush(stdin);
	if (firstRentalInfoNode == NULL) {// 하는거 아니야?? (내가 바꿔줘어써1
			printf("\n<현재 매장에서 대여해준 dvd가 없습니다.> \n");
		return;
	}
	/*
	for (j; j < RentalSize; j++) {
		if (!strcmp(temp->RpersonName, rentalPersonName)) {// 첫번째 노드의 이름과 입력한 이름이 같을 경우
				temp->overDue = "ReturnDelay";
			////////////// 이름 찾기위한 for문////////////////////////////////////
				for (i; i < size; i++) { // i = 0 이니까 대여정보 구조체가 만들어진 횟수보다 1 적은 수를 비교해야한다.
						if (!strcmp(tempPerson->name, rentalPersonName)) {//첫번째 노드의 이름과 입력한 이름이 같을 경우
								tempPerson->delayNumberOfTime += 1;
							printf("\n검색하신 손님의 대여정보를 연체 처리하고 회원 정보에연체 횟수를 '1' 증가 시켰습니다.\n");
								returnDelay += 1;
						}
					tempPerson = tempPerson->nextNode;// 다음에 손님정보에서 검색하기위해 변수들의 값을 바꾸는 것이다.
				}
		}
		temp = temp->nextNode;
	}
	if ((temp == NULL) && (returnDelay == 0)) { // 다음에 손님정보에 대해 내가 입력한 값이라
			printf("\n현재 연체 중인 dvd는 없습니다.\n");// 비교하고 싶어도 더 이상
	}
	return;
	*/
}
void blacklist() { //연체가 쌓인 고객 블랙리스트

}


int main() {
	int select;
	char a[10]; //고객님 이름
	int b; //고객님 전화번호 
	int c; //고객님 주민번호 앞자리
	char yesNo[10]; //탈퇴 여부
	char d[10]; //탈퇴할 고객님 이름
	char e[10]; //DVD이름
	char f[10]; //DVD장르
	int g; //출시연도
	int h; //대여여부(가능하면 1 불가능하면 0)
	char i[10]; //삭제할 DVD 제목
	char j[20]; //대여할 DVD이름
	char k[10]; //대여하는 고객님
	int l; //대여날짜
	char m[10]; //연체여부
	int overdueNum = 1; //연체횟수
	char overExist[10]; //연체된 DVD존재 유무
	char overDvd[20]; //연체된 DVD 제목
	char overName[10]; //연체한 고객님
	char regi[10]; //가입여부

	linkedList* L = createLinkedList();
	customer *p;
	dvdLinkedList* D = createDvdLinkedList();
	dvd *o;
	rentLinkedList* R = createRentLinkedList();
	rent *u;
	odLinkedList* O = createOdLinkedList();
	od *y;
	time_t timer;
	struct time *t;
	timer = time(NULL); //현재시각을 초 단위로 얻기(유닉스 시간 얻기) *꼭 선언해줘야 한다*
	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

	originalDvdInput(D, "신세계", "범죄", 20130221, 1);
	originalDvdInput(D, "타이타닉", "멜로/로맨스", 19980220, 1);
	originalDvdInput(D, "보헤미안랩소디", "드라마", 20181031, 1);
	originalDvdInput(D, "겨울왕국", "애니메이션", 20140116, 1);
	originalDvdInput(D, "완벽한타인", "코미디", 20181031, 1);
	//첫번째 노드로 삽입되는 originalDvdInput함수. 다른 노드 삽입함수는 마지막 노드로 삽입되게 구현 했다.
	printf("\n안녕하세요!                         현재날짜: %d년 %d월 %d일   %d시 %d분\n\n", t->year + 1900, t->mon + 1, t->mday, t->hour, t->min);
	do {
		printf("1_ 신규고객 가입\n");
		printf("2_ 고객 탈퇴\n"); //레코드가 2개일경우 최근에 입력된 레코드만 삭제할 수 있다는 문제가 있음
		printf("3_ 고객 검색\n");
		printf("4_ DVD 현황\n");
		printf("5_ DVD 정보입력\n");
		printf("6_ DVD 삭제\n"); //레코드가 2개일경우 최근에 입력된 레코드만 삭제할 수 있다는 문제가 있음
		printf("7_ DVD 대여\n");
		printf("8_ DVD 대여 현황\n");
		printf("9_ DVD 반납\n"); //레코드가 2개일경우 최근에 입력된 레코드만 삭제할 수 있다는 문제가 있음
		printf("10_ 연체된 DVD\n");
		printf("11_ 연체고객리스트\n");
		printf("12_ 블랙리스트\n");
		printf("13_ 그만보기\n");
		printf("\n항목을 선택하여 주세요: ");
		scanf("%d", &select);
		printf("\n\n");

		if (select == 1) {
			//scanf의 %s에는 앰퍼샌드(&)가 필요없고, sizeof(변수)를 기재해야한다.
			printf("---------------------------------------------------------------\n");
			printf("신규고객님 정보를 입력하여 주세요. (전화 번호는 -제외하고 입력)\n\n");
			printf("이름 입력: ");
			scanf_s("%s", a, sizeof(a));
			printf("전화번호 입력(첫 0제외하고 입력): ");
			scanf_s("%d", &b, sizeof(b));
			printf("생년월일 입력(6자리): ");
			scanf_s("%d", &c, sizeof(c));			
			printf("\n - \n\n환영합니다! [%s]고객님!\n", a);
			printf("연락처 [%d]와 \n생년월일[%d]이 저장되었습니다!\n\n", b, c);
			printf("---------------------------------------------------------------\n");

			newMemberInput(L, a, b, c);			
		}
		else if (select == 2) {
			printf("---------------------------------------------------------------\n\n");
			printf("정말 탈퇴하시겠습니까? (Y/N) : ");
			scanf_s("%s", yesNo, sizeof(yesNo));
			if (strcmp(yesNo, "Y") == 0) {
				printf("고객님의 성함을 입력하여 주세요: ");
				scanf_s("%s", d, sizeof(d));
				p = searchMember(L, d);
				deleteMember(L, p);
				printf("\n-\n\n이용해 주셔서 감사합니다!\n");
			}
			else if (strcmp(yesNo, "N") == 0) {
				printf("");
			}
			printf("\n---------------------------------------------------------------\n");
		}
		else if (select == 3) {
			memberSearch(L);
		}
		else if (select == 4) {
			dvdSearch(D);
		}
		else if (select == 5) {
			printf("---------------------------------------------------------------\n\n");
			printf("DVD 정보를 입력하여주세요.\n");
			printf("DVD 제목: ");
			scanf_s("%s", e, sizeof(e));
			printf("    장르: ");
			scanf_s("%s", f, sizeof(f));
			printf("    개봉연도(8자리): ");
			scanf_s("%d", &g, sizeof(g));
			printf("    대여여부(가능: 1, 불가능:0): ");
			scanf_s("%d", &h, sizeof(h));
			printf("\n-\n\n입력되었습니다!\n\n");
			printf("---------------------------------------------------------------\n");

			newDvdInput(D, e, f, g, h);
		}
		else if (select == 6) {
			printf("---------------------------------------------------------------\n\n");
			printf("삭제할 DVD제목을 입력하여주세요: ");
			scanf_s("%s", i, sizeof(i));
			o = searchDvd(D, i);
			deleteDvd(D, o);
			printf("\n-\n\n삭제되었습니다!\n");
			printf("\n---------------------------------------------------------------\n");
		}
		else if (select == 7) {
			printf("---------------------------------------------------------------\n\n");
			printf("회원이십니까?(Y/N) ");
			scanf("%s", regi, sizeof(regi));
			if (strcmp(regi, "Y") == 0) {
				printf("대여할 DVD 정보를 입력하여주세요.\n\n");
				printf("DVD 제목: ");
				scanf_s("%s", j, sizeof(j));
				printf("대여고객님 성함: ");
				scanf_s("%s", k, sizeof(k));
				printf("대여날짜(8자리): ");
				scanf_s("%d", &l, sizeof(l));
				printf("반납날짜(8자리): %d\n", l + 3); //대여날짜가 정해지면 반납날짜가 +3으로 정해진다. 하지만 반납날짜가 다음 달로 넘어갈경우 문제가 생김
				printf("연체여부(O/X): ");
				scanf_s("%s", m, sizeof(m));
				printf("\n-\n\n대여되었습니다!\n\n");
				printf("---------------------------------------------------------------\n");
			}
			else if (strcmp(regi, "N") == 0) {
				printf("\n---------------------------------------------------------------\n");
				printf("신규고객님 정보를 입력하여 주세요. (전화 번호는 -제외하고 입력)\n\n");
				printf("이름 입력: ");
				scanf_s("%s", a, sizeof(a));
				printf("전화번호 입력(첫 0제외하고 입력): ");
				scanf_s("%d", &b, sizeof(b));
				printf("생년월일 입력(6자리): ");
				scanf_s("%d", &c, sizeof(c));
				printf("\n - \n\n환영합니다! [%s]고객님!\n", a);
				printf("연락처 [%d]와 \n생년월일[%d]이 저장되었습니다!\n\n", b, c);
				printf("---------------------------------------------------------------\n");

				newMemberInput(L, a, b, c);

				printf("대여할 DVD 정보를 입력하여주세요.\n\n");
				printf("DVD 제목: ");
				scanf_s("%s", j, sizeof(j));
				printf("대여고객님 성함: ");
				scanf_s("%s", k, sizeof(k));
				printf("대여날짜(8자리): ");
				scanf_s("%d", &l, sizeof(l));
				printf("반납날짜(8자리): %d\n", l + 3); //대여날짜가 정해지면 반납날짜가 +3으로 정해진다. 하지만 반납날짜가 다음 달로 넘어갈경우 문제가 생김
				printf("연체여부(O/X): ");
				scanf_s("%s", m, sizeof(m));
				printf("\n-\n\n대여되었습니다!\n\n");
				printf("---------------------------------------------------------------\n");
			}

			rentInformationInput(R, j, k, l, l+3, m);
			//if (strcmp(b1->topic, a1->title) == 0) a1->rented == 0;
		}
		else if (select == 8) {
			rentSearch(R);
				printf("\n연체된 DVD가 있습니까(Y/N)? ");
				scanf_s("%s", overExist, sizeof(overExist));
				if (strcmp(overExist, "Y") == 0) {
					printf("\n연체된 DVD제목을 입력하여주세요: ");
					scanf_s("%s", overDvd, sizeof(overDvd));
					printf("연체하신 고객님 성함을 입력하여주세요: ");
					scanf_s("%s", overName, sizeof(overName));
					printf("\n-\n\n연체 목록에 저장되었습니다.\n\n");
					printf("---------------------------------------------------------------\n");
					odInput(O, overDvd, overName, overdueNum);
					//over = overdueName(overDvd[20], overName[10]);
				}
				else if (strcmp(overExist, "N") == 0) {
					printf("");
					printf("---------------------------------------------------------------\n\n");
				}
		}
		else if (select == 9) {
			printf("---------------------------------------------------------------\n\n");
			printf("반납하는 DVD제목을 입력하여주세요: ");
			scanf_s("%s", j, sizeof(j));
			u = searchRent(R, j);
			deleteRent(R, u);
			printf("\n-\n\n반납되었습니다!\n");
			printf("\n---------------------------------------------------------------\n");
		}
		else if (select == 10) { 
			overdue(O);
		}
		else if (select == 11) {
			overdueMember(O);
			//++overdueNum;
		}
	} while (select != 13);
	getchar();
}

//문제
//1. DVD를 대여하면 DVD현황에서 대여가능여부의 숫자가 0으로 바뀌어야함.
//   (대여된 DVD의 제목을 DVD정보 연결리스트의 노드들의 제목과 비교하여 일치한다면 대여가능여부를 0으로 바꾸어야함)
//2. 11번 연체고객리스트에 A라는 이름이 추가되고 그 후에 또 A라는 이름이 추가되면 데이터추가가 되는 대신에 연체횟수가 증가해야한다.
//   (연결리스트의 노드들을 비교해 같은 이름의 데이터를 가지고있다면 삭제하고 연체횟수를 1증가시켜야 함)
//   (연체 횟수를 전역변수로 선언하여 누적시킬지 구조체 안에 선언하여 누적시킬지 생각)
//3. 연체고객리스트의 연체횟수가 3번 누적된 고객은 블랙리스트로 넘어가게된다.
//   (2번이 해결되면 if(연체횟수 >= 3) 블랙리스트()함수로 해결할 수 있다)
