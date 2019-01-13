#define _CRT_SECURE_NO_WARNINGS //���� �������� ���Ǵ� �޸� ���� ��ɾ�� �� �̸� �̿��� ��¹��� ���� �ִ� �������� ��������(����, �޸� ��)�� ���� ������� �ذ��ϱ� ���� ����.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//���� ���� ����
#define POSSIBLE 1
#define IMPOSSIBLE 0
#ifndef time_H //time�� ����ü�� �����ϸ� �������϶�� ������ �߻�. ������ ���� �ذ������� #ifndef #define #endif�� �����ϸ� �ذ�ȴ�.
#define time_H

int RentalSize = 0;

struct time { //���糯¥�� ���ϱ� ���� ����ü ����
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

typedef struct customer { //����� ����ü
	char nm[10];
	int pn;
	int birth;
	struct customer *link;
} customer;

typedef struct {
	customer *head;
} linkedList;
/////////////////////////////////////////////////
typedef struct dvd { //DVD ����ü
	char title[20]; //����
	char genre[10]; //�帣
	int release; //��ÿ���
	int rented; //�뿩����(�����ϸ� 1 �Ұ����ϸ� 0)
	struct dvd *link;
} dvd;

typedef struct {
	dvd *head;
} dvdLinkedList;
/////////////////////////////////////////////////
typedef struct rent {
	char topic[20]; //DVD����
	char people[10]; //�뿩�� ��
	int rentDate; //�뿩��¥
	int returnDate; //�ݳ���¥
	char overdue[10]; //��ü����(O,X�� ǥ��)
	struct rent *link;
} rent;

typedef struct {
	rent *head;
} rentLinkedList;

rent *firstRentalInfoNode = NULL;
rent *lastRentalInfoNode = NULL;
/*�뿩�� DVD������ ǥ��(����, �뿩�� ��, �뿩��¥, �ݳ���¥, ��ü����), ǥ�ð� �� DVD�� DVD�˻� �Լ����� �뿩���ΰ� 0���� �ٲ����Ѵ�*/
//DVD�뿩�� �Է�, DVD�뿩���δ� Ž��, DVD�ݳ��� �뿩���ο��� �����Լ��� ����� �ȴ�.
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

linkedList *createLinkedList(void) { //�� ��� ���Ḯ��Ʈ ����
	linkedList* L;
	L = (linkedList *)malloc(sizeof(linkedList));
	L->head = NULL;
	return L;
}
////////////////////////////////////////
dvdLinkedList *createDvdLinkedList(void) { //DVD ���Ḯ��Ʈ ����
	dvdLinkedList* D;
	D = (dvdLinkedList *)malloc(sizeof(dvdLinkedList));
	D->head = NULL;
	return D;
}
/////////////////////////////////////////
rentLinkedList *createRentLinkedList(void) { //�뿩�� DVD ���Ḯ��Ʈ ����
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

void newMemberInput(linkedList* L, char* name, int phoneNumber, int private) { //�ű԰� �Է�
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

void rentInformationInput(rentLinkedList* R, char* title, char* name, int give, int receive, char* ox) { //�뿩�ϴ� DVD ���� �Է�
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

void newDvdInput(dvdLinkedList* D, char* ti, char* ge, int rel, int ren) { //���ο� DVD �Է�
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

void originalDvdInput(dvdLinkedList *D, char* ti, char* ge, int rel, int ren) { //������ �����ϴ� DVD �Է�
	dvd* newNode;
	newNode = (dvd*)malloc(sizeof(dvd));
	strcpy(newNode->title, ti);
	strcpy(newNode->genre, ge);
	newNode->release = rel;
	newNode->rented = ren;
	newNode->link = D->head;
	D->head = newNode;
}

void odInput(odLinkedList* O, char* dn, char* cn, int overdueNum) { //��ü ���� �Է�
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

void deleteMember(linkedList* L, customer* p) { //����� ����
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

void deleteRent(rentLinkedList* R, rent* u) { //�뿩�� DVD �ݳ�
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

void deleteDvd(dvdLinkedList* D, dvd* o) { //DVD ����
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

customer* searchMember(linkedList *L, char* x) { //�������� ���� �˻�
	customer *temp;
	temp = L->head;
	while (temp != NULL) {
		if (strcmp(temp->nm, x) == 0) return temp;
		else temp = temp->link;
	}
	return temp;
}

rent* searchRent(rentLinkedList *R, char* x) { //�ݳ��ϴ� DVD������ ���� �˻�
	rent *temp;
	temp = R->head;
	while (temp != NULL) {
		if (strcmp(temp->topic, x) == 0) return temp;
		else temp = temp->link;
	}
	return temp;
}

dvd* searchDvd(dvdLinkedList *D, char* x) { //DVD������ ���� �˻�
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


int member() { //������
return 0;
}
*/

void memberSearch(linkedList *L) { //���˻�
	customer *p;
	printf("---------------------------------------------------------------\n");
	printf("                        ���� ���                             \n\n");
	p = L->head;
	if (p == NULL) printf("\n\n                   �����Ͱ� �������� �ʽ��ϴ�.              \n\n\n\n");
	while (p != NULL) {
			printf("                ***************************\n");
			printf("                *      ����: %s       *\n", p->nm);
			printf("                *  ��ȭ��ȣ: %d   *\n", p->pn);
			printf("                *  �������: %d       *\n", p->birth);
			printf("                ***************************\n");
			p = p->link;
	}
	printf("---------------------------------------------------------------\n");
}

void rentSearch(rentLinkedList *R) { //�뿩��Ȳ
	rent *u;
	printf("---------------------------------------------------------------\n");
	printf("                          �뿩 ��Ȳ                             \n\n");
	u = R->head;
	if (u == NULL) printf("\n\n                   �����Ͱ� �������� �ʽ��ϴ�.              \n\n\n\n");
	while (u != NULL) {
		printf("                ***************************\n");
		printf("                       ����: %s        \n", u->topic);
		printf("                 �뿩�Ͻź�: %s    \n", u->people);
		printf("                   �뿩��¥: %d        \n", u->rentDate);
		printf("                   �ݳ���¥: %d        \n", u->returnDate);
		printf("                   ��ü����: %s        \n", u->overdue);
		printf("                ***************************\n");
		u = u->link;
	}
}

void dvdSearch(dvdLinkedList *D) { //DVD �˻�
	dvd *o;
	printf("---------------------------------------------------------------\n");
	printf("                            DVD                              \n\n");
	o = D->head;
	if (o == NULL) printf("\n\n                   �����Ͱ� �������� �ʽ��ϴ�.              \n\n\n\n");
	while (o != NULL) {
		printf("                ***************************\n");
		printf("                       ����: %s        \n", o->title);
		printf("                       �帣: %s    \n", o->genre);
		printf("                   ��������: %d        \n", o->release);
		printf("                   �뿩����: %d        \n", o->rented);
		printf("                ***************************\n");
		o = o->link;
	}
	printf("---------------------------------------------------------------\n");
}

void overdue(odLinkedList *O) { //��ü�� DVD ����
	od *y;
	printf("---------------------------------------------------------------\n\n");
	printf("                         ��ü����                              \n\n");
	y = O->head;
	if (y == NULL) printf("\n\n                   �����Ͱ� �������� �ʽ��ϴ�.              \n\n\n\n");
	while (y != NULL) {
	printf("                ***************************\n");
	printf("                 ��ü�� DVD: %s        \n", y->overDvName);
	printf("                 ��ü����: %s    \n", y->overCuName);
	printf("                ***************************\n");
	y = y->link;
	}
	printf("\n---------------------------------------------------------------\n");
}

/*
overdueCustomer overdueName(char* overDvName, char* overCuName) { //��ü �� �̸�, DVD������ �����ϴ� �Լ�
	overdueCustomer g;
	g.overDvName[20] = overDvName;
	g.overCuName[10] = overCuName;
	return g;
}
*/

void overdueMember(odLinkedList *O) { //��ü �� ����Ʈ
	od *y;
	od e;
	printf("---------------------------------------------------------------\n\n");
	printf("                      ��ü ������Ʈ                              \n\n");
	y = O->head;
	if (y == NULL) printf("\n\n                   �����Ͱ� �������� �ʽ��ϴ�.              \n\n\n\n");
	while (y != NULL) {
		printf("                ***************************\n");
		printf("                 ��ü����: %s    \n", y->overCuName);
		printf("                   ��üȽ��: %d    \n", y->overdueNumber);
		printf("                ***************************\n");
		//if (strcmp(y->overCuName, y) == 0) return temp;
		y = y->link;
	}
	printf("\n---------------------------------------------------------------\n");
}

void returnDelay() {
	char* rentalPersonName = malloc(sizeof(char) * 30); // �˻��ϰ� ���� �̸��� ����Ǵ� ���ڿ� ����
	int i = 0; // ���Ե� �մ� ���� ���� ��ū for�� ������ ���� ����!
	int j = 0; // �뿩 Ƚ�� ��ŭ for�� ������ ���� ����!
	int returnDelay = 0;
	rent *temp = firstRentalInfoNode;//
	od *tempPerson = firstPersonNode; // ù��° ���������� �Է�!!
		printf("\n���� �뿩 ������ ��ü ó���� ���� �̸��� �Է����ּ���\n");
	scanf_s("%s", rentalPersonName, sizeof(rentalPersonName));
	fflush(stdin);
	if (firstRentalInfoNode == NULL) {// �ϴ°� �ƴϾ�?? (���� �ٲ�����1
			printf("\n<���� ���忡�� �뿩���� dvd�� �����ϴ�.> \n");
		return;
	}
	/*
	for (j; j < RentalSize; j++) {
		if (!strcmp(temp->RpersonName, rentalPersonName)) {// ù��° ����� �̸��� �Է��� �̸��� ���� ���
				temp->overDue = "ReturnDelay";
			////////////// �̸� ã������ for��////////////////////////////////////
				for (i; i < size; i++) { // i = 0 �̴ϱ� �뿩���� ����ü�� ������� Ƚ������ 1 ���� ���� ���ؾ��Ѵ�.
						if (!strcmp(tempPerson->name, rentalPersonName)) {//ù��° ����� �̸��� �Է��� �̸��� ���� ���
								tempPerson->delayNumberOfTime += 1;
							printf("\n�˻��Ͻ� �մ��� �뿩������ ��ü ó���ϰ� ȸ�� ��������ü Ƚ���� '1' ���� ���׽��ϴ�.\n");
								returnDelay += 1;
						}
					tempPerson = tempPerson->nextNode;// ������ �մ��������� �˻��ϱ����� �������� ���� �ٲٴ� ���̴�.
				}
		}
		temp = temp->nextNode;
	}
	if ((temp == NULL) && (returnDelay == 0)) { // ������ �մ������� ���� ���� �Է��� ���̶�
			printf("\n���� ��ü ���� dvd�� �����ϴ�.\n");// ���ϰ� �; �� �̻�
	}
	return;
	*/
}
void blacklist() { //��ü�� ���� �� ������Ʈ

}


int main() {
	int select;
	char a[10]; //���� �̸�
	int b; //���� ��ȭ��ȣ 
	int c; //���� �ֹι�ȣ ���ڸ�
	char yesNo[10]; //Ż�� ����
	char d[10]; //Ż���� ���� �̸�
	char e[10]; //DVD�̸�
	char f[10]; //DVD�帣
	int g; //��ÿ���
	int h; //�뿩����(�����ϸ� 1 �Ұ����ϸ� 0)
	char i[10]; //������ DVD ����
	char j[20]; //�뿩�� DVD�̸�
	char k[10]; //�뿩�ϴ� ����
	int l; //�뿩��¥
	char m[10]; //��ü����
	int overdueNum = 1; //��üȽ��
	char overExist[10]; //��ü�� DVD���� ����
	char overDvd[20]; //��ü�� DVD ����
	char overName[10]; //��ü�� ����
	char regi[10]; //���Կ���

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
	timer = time(NULL); //����ð��� �� ������ ���(���н� �ð� ���) *�� ��������� �Ѵ�*
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	originalDvdInput(D, "�ż���", "����", 20130221, 1);
	originalDvdInput(D, "Ÿ��Ÿ��", "���/�θǽ�", 19980220, 1);
	originalDvdInput(D, "����̾ȷ��ҵ�", "���", 20181031, 1);
	originalDvdInput(D, "�ܿ�ձ�", "�ִϸ��̼�", 20140116, 1);
	originalDvdInput(D, "�Ϻ���Ÿ��", "�ڹ̵�", 20181031, 1);
	//ù��° ���� ���ԵǴ� originalDvdInput�Լ�. �ٸ� ��� �����Լ��� ������ ���� ���Եǰ� ���� �ߴ�.
	printf("\n�ȳ��ϼ���!                         ���糯¥: %d�� %d�� %d��   %d�� %d��\n\n", t->year + 1900, t->mon + 1, t->mday, t->hour, t->min);
	do {
		printf("1_ �ű԰� ����\n");
		printf("2_ �� Ż��\n"); //���ڵ尡 2���ϰ�� �ֱٿ� �Էµ� ���ڵ常 ������ �� �ִٴ� ������ ����
		printf("3_ �� �˻�\n");
		printf("4_ DVD ��Ȳ\n");
		printf("5_ DVD �����Է�\n");
		printf("6_ DVD ����\n"); //���ڵ尡 2���ϰ�� �ֱٿ� �Էµ� ���ڵ常 ������ �� �ִٴ� ������ ����
		printf("7_ DVD �뿩\n");
		printf("8_ DVD �뿩 ��Ȳ\n");
		printf("9_ DVD �ݳ�\n"); //���ڵ尡 2���ϰ�� �ֱٿ� �Էµ� ���ڵ常 ������ �� �ִٴ� ������ ����
		printf("10_ ��ü�� DVD\n");
		printf("11_ ��ü������Ʈ\n");
		printf("12_ ������Ʈ\n");
		printf("13_ �׸�����\n");
		printf("\n�׸��� �����Ͽ� �ּ���: ");
		scanf("%d", &select);
		printf("\n\n");

		if (select == 1) {
			//scanf�� %s���� ���ۻ���(&)�� �ʿ����, sizeof(����)�� �����ؾ��Ѵ�.
			printf("---------------------------------------------------------------\n");
			printf("�ű԰��� ������ �Է��Ͽ� �ּ���. (��ȭ ��ȣ�� -�����ϰ� �Է�)\n\n");
			printf("�̸� �Է�: ");
			scanf_s("%s", a, sizeof(a));
			printf("��ȭ��ȣ �Է�(ù 0�����ϰ� �Է�): ");
			scanf_s("%d", &b, sizeof(b));
			printf("������� �Է�(6�ڸ�): ");
			scanf_s("%d", &c, sizeof(c));			
			printf("\n - \n\nȯ���մϴ�! [%s]����!\n", a);
			printf("����ó [%d]�� \n�������[%d]�� ����Ǿ����ϴ�!\n\n", b, c);
			printf("---------------------------------------------------------------\n");

			newMemberInput(L, a, b, c);			
		}
		else if (select == 2) {
			printf("---------------------------------------------------------------\n\n");
			printf("���� Ż���Ͻðڽ��ϱ�? (Y/N) : ");
			scanf_s("%s", yesNo, sizeof(yesNo));
			if (strcmp(yesNo, "Y") == 0) {
				printf("������ ������ �Է��Ͽ� �ּ���: ");
				scanf_s("%s", d, sizeof(d));
				p = searchMember(L, d);
				deleteMember(L, p);
				printf("\n-\n\n�̿��� �ּż� �����մϴ�!\n");
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
			printf("DVD ������ �Է��Ͽ��ּ���.\n");
			printf("DVD ����: ");
			scanf_s("%s", e, sizeof(e));
			printf("    �帣: ");
			scanf_s("%s", f, sizeof(f));
			printf("    ��������(8�ڸ�): ");
			scanf_s("%d", &g, sizeof(g));
			printf("    �뿩����(����: 1, �Ұ���:0): ");
			scanf_s("%d", &h, sizeof(h));
			printf("\n-\n\n�ԷµǾ����ϴ�!\n\n");
			printf("---------------------------------------------------------------\n");

			newDvdInput(D, e, f, g, h);
		}
		else if (select == 6) {
			printf("---------------------------------------------------------------\n\n");
			printf("������ DVD������ �Է��Ͽ��ּ���: ");
			scanf_s("%s", i, sizeof(i));
			o = searchDvd(D, i);
			deleteDvd(D, o);
			printf("\n-\n\n�����Ǿ����ϴ�!\n");
			printf("\n---------------------------------------------------------------\n");
		}
		else if (select == 7) {
			printf("---------------------------------------------------------------\n\n");
			printf("ȸ���̽ʴϱ�?(Y/N) ");
			scanf("%s", regi, sizeof(regi));
			if (strcmp(regi, "Y") == 0) {
				printf("�뿩�� DVD ������ �Է��Ͽ��ּ���.\n\n");
				printf("DVD ����: ");
				scanf_s("%s", j, sizeof(j));
				printf("�뿩���� ����: ");
				scanf_s("%s", k, sizeof(k));
				printf("�뿩��¥(8�ڸ�): ");
				scanf_s("%d", &l, sizeof(l));
				printf("�ݳ���¥(8�ڸ�): %d\n", l + 3); //�뿩��¥�� �������� �ݳ���¥�� +3���� ��������. ������ �ݳ���¥�� ���� �޷� �Ѿ��� ������ ����
				printf("��ü����(O/X): ");
				scanf_s("%s", m, sizeof(m));
				printf("\n-\n\n�뿩�Ǿ����ϴ�!\n\n");
				printf("---------------------------------------------------------------\n");
			}
			else if (strcmp(regi, "N") == 0) {
				printf("\n---------------------------------------------------------------\n");
				printf("�ű԰��� ������ �Է��Ͽ� �ּ���. (��ȭ ��ȣ�� -�����ϰ� �Է�)\n\n");
				printf("�̸� �Է�: ");
				scanf_s("%s", a, sizeof(a));
				printf("��ȭ��ȣ �Է�(ù 0�����ϰ� �Է�): ");
				scanf_s("%d", &b, sizeof(b));
				printf("������� �Է�(6�ڸ�): ");
				scanf_s("%d", &c, sizeof(c));
				printf("\n - \n\nȯ���մϴ�! [%s]����!\n", a);
				printf("����ó [%d]�� \n�������[%d]�� ����Ǿ����ϴ�!\n\n", b, c);
				printf("---------------------------------------------------------------\n");

				newMemberInput(L, a, b, c);

				printf("�뿩�� DVD ������ �Է��Ͽ��ּ���.\n\n");
				printf("DVD ����: ");
				scanf_s("%s", j, sizeof(j));
				printf("�뿩���� ����: ");
				scanf_s("%s", k, sizeof(k));
				printf("�뿩��¥(8�ڸ�): ");
				scanf_s("%d", &l, sizeof(l));
				printf("�ݳ���¥(8�ڸ�): %d\n", l + 3); //�뿩��¥�� �������� �ݳ���¥�� +3���� ��������. ������ �ݳ���¥�� ���� �޷� �Ѿ��� ������ ����
				printf("��ü����(O/X): ");
				scanf_s("%s", m, sizeof(m));
				printf("\n-\n\n�뿩�Ǿ����ϴ�!\n\n");
				printf("---------------------------------------------------------------\n");
			}

			rentInformationInput(R, j, k, l, l+3, m);
			//if (strcmp(b1->topic, a1->title) == 0) a1->rented == 0;
		}
		else if (select == 8) {
			rentSearch(R);
				printf("\n��ü�� DVD�� �ֽ��ϱ�(Y/N)? ");
				scanf_s("%s", overExist, sizeof(overExist));
				if (strcmp(overExist, "Y") == 0) {
					printf("\n��ü�� DVD������ �Է��Ͽ��ּ���: ");
					scanf_s("%s", overDvd, sizeof(overDvd));
					printf("��ü�Ͻ� ���� ������ �Է��Ͽ��ּ���: ");
					scanf_s("%s", overName, sizeof(overName));
					printf("\n-\n\n��ü ��Ͽ� ����Ǿ����ϴ�.\n\n");
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
			printf("�ݳ��ϴ� DVD������ �Է��Ͽ��ּ���: ");
			scanf_s("%s", j, sizeof(j));
			u = searchRent(R, j);
			deleteRent(R, u);
			printf("\n-\n\n�ݳ��Ǿ����ϴ�!\n");
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

//����
//1. DVD�� �뿩�ϸ� DVD��Ȳ���� �뿩���ɿ����� ���ڰ� 0���� �ٲ�����.
//   (�뿩�� DVD�� ������ DVD���� ���Ḯ��Ʈ�� ������ ����� ���Ͽ� ��ġ�Ѵٸ� �뿩���ɿ��θ� 0���� �ٲپ����)
//2. 11�� ��ü������Ʈ�� A��� �̸��� �߰��ǰ� �� �Ŀ� �� A��� �̸��� �߰��Ǹ� �������߰��� �Ǵ� ��ſ� ��üȽ���� �����ؾ��Ѵ�.
//   (���Ḯ��Ʈ�� ������ ���� ���� �̸��� �����͸� �������ִٸ� �����ϰ� ��üȽ���� 1�������Ѿ� ��)
//   (��ü Ƚ���� ���������� �����Ͽ� ������ų�� ����ü �ȿ� �����Ͽ� ������ų�� ����)
//3. ��ü������Ʈ�� ��üȽ���� 3�� ������ ���� ������Ʈ�� �Ѿ�Եȴ�.
//   (2���� �ذ�Ǹ� if(��üȽ�� >= 3) ������Ʈ()�Լ��� �ذ��� �� �ִ�)
