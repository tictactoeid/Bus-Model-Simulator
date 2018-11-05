/*
	BUS MODEL SIMULATOR
    INCHEON JINSAN SCIENCE HIGH SCHOOL
	MATHEMATICS R&E
    보드게임 도블 (Dobble)에 적용된 유한 사영평면을 활용한 버스 노선의 효율적 개선에 대한 연구
	MADE BY JUNG JIMIN (TEAM LEADER)
	2018. 10. 31. (WED) VER 1.0
*/

/*
주의사항: 프로그램이 있는 경로에 result라는 이름의 폴더를 생성하여야 함.
*/
#include <stdio.h>
#include <math.h>

int main(){
    // 프로그램에서 사용할 변수 선언 및 값 저장
    double time = 0.0; // time: 버스가 운행을 시작하고 경과한 시간 
	int busno = 1; // busno: 운행 중인 버스의 번호 
    int stop[3] = {0}; // stop[0], stop[1], stop[2]: 운행 중인 버스가 지나는 세 정류장 
    double t[8][8] = {}; // t[a][b] : a번 정류장에서 b번 정류장까지 가는 데 소요되는 시간

	int i, cnt = 0;
	int hour, min = 0;
	double sec, tmp = 0;

    double a = 37.5; //정삼각형 한 변의 절반
	double b = 45.3; //원 코스 3분의 1
	double c = 43.3; //정삼각형 높이 두 선분 중 긴 쪽
	double d = 21.7; //높이의 짧은 쪽
	
	double val = 0.0;
	
	int now = 0; // 버스가 현재 위치한 정류장 
	int next = 0; // 버스가 다음 번에 도착할 정류장 

	// 소요 시간값 배열 t에 값을 저장한다. 
	t[1][2] = a;
	t[2][5] = a;
	t[5][6] = a;
	t[6][7] = a;
	t[7][3] = a;
	t[3][1] = a;
	
	t[2][6] = b;
	t[6][3] = b;
	t[3][2] = b;
	
	t[5][4] = c;
	t[7][4] = c;
	t[1][4] = c;
	
	t[2][4] = d;
	t[6][4] = d;
	t[3][4] = d;

    //결과를 저장한 파일을 연다.
    FILE *ft[8];
    FILE *fa[8];

    ft[1] = fopen(".\\result\\time1.txt", "a"); //time(n).txt: n번 버스가 도착하는 정류장 번호와 그 때의 시간
    ft[2] = fopen(".\\result\\time2.txt", "a");
    ft[3] = fopen(".\\result\\time3.txt", "a");
    ft[4] = fopen(".\\result\\time4.txt", "a");
    ft[5] = fopen(".\\result\\time5.txt", "a");
    ft[6] = fopen(".\\result\\time6.txt", "a");
    ft[7] = fopen(".\\result\\time7.txt", "a");
    
    fa[1] = fopen(".\\result\\arrive1.txt", "a"); //arrive(n).txt: n번 정류장에 도착하는 버스 번호와 시간 
    fa[2] = fopen(".\\result\\arrive2.txt", "a");
    fa[3] = fopen(".\\result\\arrive3.txt", "a");
    fa[4] = fopen(".\\result\\arrive4.txt", "a");
    fa[5] = fopen(".\\result\\arrive5.txt", "a");
    fa[6] = fopen(".\\result\\arrive6.txt", "a");
    fa[7] = fopen(".\\result\\arrive7.txt", "a");

   for (busno=1; busno<8; busno++){ //1번부터 7번 버스까지 반복 
		cnt = 0;
		// cnt: 현재 반복 실행된 횟수를 나타냄 (코드의 구현 상 필요, 연구에서는 중요하지 않음) 
		 
			if (busno == 1){ // 버스 번호에 따라 운행하는 정류장 값을 넣음 
				stop[0] = 1;
				stop[1] = 2;
				stop[2] = 5;
			}
			else if (busno == 2){			
				stop[0] = 1;
				stop[1] = 4;
				stop[2] = 6;
			}
			else if (busno == 3){			
				stop[0] = 1;
				stop[1] = 3;
				stop[2] = 7;
			}
			else if (busno == 4){
				stop[0] = 5;
				stop[1] = 6;
				stop[2] = 7;
			}
			else if (busno == 5){
				stop[0] = 5;
				stop[1] = 4;
				stop[2] = 3;
			}	
			else if (busno == 6){
				stop[0] = 7;
				stop[1] = 4;
				stop[2] = 2;
			}	
			else if (busno == 7){
				stop[0] = 2;
				stop[1] = 6;
				stop[2] = 3;
			}
		
		now = stop[0];
		next = stop[1];
		fprintf(ft[busno], "%d번 버스, %d-%d-%d\n", busno, stop[0], stop[1], stop[2]);
    	fprintf(ft[busno], "정류장 / 시간\n");
    	
		while (time <= 3600){ //1시간 (3600초) 동안 실행 
			// 처음 1회의 경우 now, next 지정 
			if (cnt == 0){
				now = stop[0];
				next = stop[1];
			}
			else if (busno != 7){ // 7번 제외 나머지 버스(직선 코스), a- b-c-b-a - b-c-b-a 형태로 운행 (처음 1회제외 4번 간격으로 반복) 
				if (cnt%4 == 1){
					now = stop[1];
					next = stop[2];
				}
				else if (cnt%4 == 2){
					now = stop[2];
					next = stop[1];
				}
				else if (cnt%4 == 3){
					now = stop[1];
					next = stop[0];
				}
				else{
					now = stop[0];
					next = stop[1];
				}
			} 
			else{ // 7번 버스(원형 코스), a-b-c - a-b-c 형태로 정류장을 운행 (3번 간격으로 반복) 
				if (cnt%3 == 1){
					now = stop[1];
					next = stop[2];
				}
				else if (cnt%3 == 2){
					now = stop[2];
					next = stop[0];
				}
				else{
					now = stop[0];
					next = stop[1];
				}				
			}
			
    		hour = (int) time/3600; // 시간 단위 표시 
    		min = (((int) time)/60 )% 60; // 분 단위 표시 
			sec = time - hour*3600 - min*60; // 초 단위 표시
			 
    		fprintf(ft[busno], "%d %02d:%02d:%.2lf\n", now, hour, min, sec);
    		fprintf(fa[now], "%d %02d:%02d:%.2lf\n", busno, hour, min, sec);
    		printf("write! cnt == %d, time == %f, hour == %d, min == %d, sec == %f\n", cnt, time, hour, min, sec); //테스트용
    		
    		/*a번 정류장에서 b번 정류장으로 가는 경우, 
			코드가 너무 길어지는 것을 막기 위해 t[a][b]와 t[b][a]중 하나에만 값이 들어있고 나머지는 0임.
			따라서 두 값을 검사해 0이 아닌 값을 val에 넣음
			*/ 

    		if ((int) t[now][next] != 0){     		
    			val = t[now][next];
			}
			else if ((int)t[next][now] != 0){
				val = t[next][now];
			}
			else { // 코딩 과정 중 디버깅용 (실제 동작과 무관) 
				printf("ERR");
				return 1;
			}
			
			time += val; //소요 시간을 time에 더함 
	   		cnt++;
    		
		}		
			for (i=0; i<3; i++){
				fprintf(fa[stop[i]], "\n\n\n\n"); //가독성을 위한 4줄 띄어쓰기 
			}
			
		fprintf(ft[busno], "\n\n\n\n");
		fclose(ft[busno]);
		printf("Done: %d\n\n", busno); // 버스 1개에 대해 파일 작성 종료
	}
	
	for (i=1; i<8; i++){ //arrive 파일 8개 닫음
		fclose(fa[i]); 
	}
	
	printf("All Done!");
	return 0; // 프로그램 실행 종료
}