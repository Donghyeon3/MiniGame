#include <bangtal.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
SoundID sound1,sound2,sound3,sound4;
SceneID scene1;
ObjectID startButton, endButton,nextButton;
TimerID timer5;
int r_num,endscenenum=2;
int gameNum=0;

/////////////////////////////////////////////////////////// Pong HAU K'I 
ObjectID CirR1, CirR2, CirB1, CirB2, CirB, CirR, Turn;
int P1W = 0, P2W = 0;
bool PongOn = false;
bool Bturn = true;
int PongXY[2][3] = { {1,0,1},{1,1} };
int B1X = 120, B2X = 1050, B1Y = 460, B2Y = 460;
int R1X = 120, R2X = 1050, R1Y = 20, R2Y = 20;
void BPong() {
	setSceneImage(scene1, "images/BPong.png");
	hideObject(startButton);
	showObject(nextButton);
}
void endPong() {
	hideObject(CirB1);
	hideObject(CirB2);
	hideObject(CirR1);
	hideObject(CirR2);
	hideObject(Turn);
	hideObject(CirB);
	hideObject(CirR);
	showObject(nextButton);
	gameNum++;
}
void Pongwin() {
	endPong();
	if (r_num == 0) {
		if (Bturn) {
			showMessage("Player 2 Win\nClick Nextbutton To Check Score");
			P2W++;
		}
		else if (not Bturn) {
			showMessage("Player 1 Win\nClick Nextbutton To Check Score");
			P1W++;
		}
	}
	else {
		if (Bturn) {
			showMessage("Player 1 Win\nClick Nextbutton To Check Score");
			P1W++;
		}
		else if (not Bturn) {
			showMessage("Player 2 Win\nClick Nextbutton To Check Score");
			P2W++;
		}
	}
	PongOn = false;
}
void startPong() {
	r_num = rand() % 2;
	PongOn = true;
	setSceneImage(scene1, "images/Pong.png");
	Turn = createObject("images/BTurn.png");
	CirR1 = createObject("images/circleR.png");
	CirR2 = createObject("images/circleR.png");
	CirB1 = createObject("images/circleB.png");
	CirB2 = createObject("images/circleB.png");
	CirB = createObject("images/circleB.png");
	CirR = createObject("images/circleR.png");
	if (r_num == 0) {
		locateObject(CirB, scene1, 140, 650);
		locateObject(CirR, scene1, 140, 600);
	}
	else {
		locateObject(CirB, scene1, 140, 600);
		locateObject(CirR, scene1, 140, 650);
	}
	scaleObject(CirB, 0.05f);
	scaleObject(CirR, 0.05f);
	scaleObject(CirB1, 0.2f);
	scaleObject(CirB2, 0.2f);
	scaleObject(CirR1, 0.2f);
	scaleObject(CirR2, 0.2f);

	locateObject(Turn, scene1, 1000, 580);
	locateObject(CirB1, scene1, B1X, B1Y);
	locateObject(CirB2, scene1, B2X, B2Y);
	locateObject(CirR1, scene1, R1X, R1Y);
	locateObject(CirR2, scene1, R2X, R2Y);

	showObject(Turn);
	showObject(CirB2);
	showObject(CirB1);
	showObject(CirR1);
	showObject(CirR2);
	showObject(CirR);
	showObject(CirB);
	hideObject(nextButton);
}
void movePong(ObjectID object, int X, int Y) {
	if (X == 120 && Y == 460) { //왼쪽위
		PongXY[0][0] = 0;
		if (PongXY[0][1] == 0) {
			X += 465;
			Y -= 220;
			PongXY[0][1] = 1;
		}
		else if (PongXY[1][0] == 0) {
			Y -= 440;
			PongXY[1][0] = 1;
		}
		else Pongwin();
	}
	else if (X == 120 && Y == 20) { //왼쪽아래
		PongXY[1][0] = 0;
		if (PongXY[0][0] == 0) {
			Y += 440;
			PongXY[0][0] = 1;
		}
		else if (PongXY[1][1] == 0) {
			X += 930;
			PongXY[1][1] = 1;
		}
		else if (PongXY[0][1] == 0) {
			X += 465;
			Y += 220;
			PongXY[0][1] = 1;
		}
		else Pongwin();
	}

	else if (X == 1050 && Y == 460) { //오른쪽위
		PongXY[0][2] = 0;
		if (PongXY[0][1] == 0) {
			X -= 465;
			Y -= 220;
			PongXY[0][1] = 1;
		}
		else if (PongXY[1][1] == 0) {
			Y -= 440;
			PongXY[1][1] = 1;
		}
		else Pongwin();
	}

	else if (X == 1050 && Y == 20) { // 오른쪽 아래
		PongXY[1][1] = 0;
		if (PongXY[0][2] == 0) {
			Y += 440;
			PongXY[0][2] = 1;
		}
		else if (PongXY[1][0] == 0) {
			X -= 930;
			PongXY[1][0] = 1;
		}
		else if (PongXY[0][1] == 0) {
			X -= 465;
			Y += 220;
			PongXY[0][1] = 1;
		}
		else Pongwin();
	}

	else if (X == 585 && Y == 240) { // 가운데
		PongXY[0][1] = 0;
		if (PongXY[0][0] == 0) {
			X -= 465;
			Y += 220;
			PongXY[0][0] = 1;
		}
		else if (PongXY[0][2] == 0) {
			X += 465;
			Y += 220;
			PongXY[0][2] = 1;
		}
		else if (PongXY[1][0] == 0) {
			X -= 465;
			Y -= 220;
			PongXY[1][0] = 1;
		}
		else if (PongXY[1][1] == 0) {
			X += 465;
			Y -= 220;
			PongXY[1][1] = 1;
		}
		else Pongwin();
	}
	if (object == CirB1) {
		B1X = X;
		B1Y = Y;
	}
	else if (object == CirB2) {
		B2X = X;
		B2Y = Y;
	}
	else if (object == CirR1) {
		R1X = X;
		R1Y = Y;
	}
	else if (object == CirR2) {
		R2X = X;
		R2Y = Y;
	}
	locateObject(object, scene1, X, Y);
}
////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////// Racing 
ObjectID car1, car2,trafficlight,red,green,yellow,p1,p2;
TimerID timer1, timer2, timer3;
int car1X = 15, car1Y = 60;
int car2X = 10, car2Y = 0;
float speed = 3, car1dx = 0, car2dx = 0;
bool raceOn = false;
int typeSignal;
float signalTime;
void BRace() {
	setSceneImage(scene1, "images/BRace.png");
	hideObject(startButton);
	showObject(nextButton);
}
void startRace() {
	raceOn = true;
	signalTime = (rand() % 3) + 1;
	typeSignal = rand() % 2;
	timer1 = createTimer(0.01f);
	timer2 = createTimer(0.01f);
	timer3 = createTimer(signalTime);
	startTimer(timer1);
	startTimer(timer2);
	startTimer(timer3);
	car1 = createObject("images/car1.png");
	car2 = createObject("images/car2.png");
	p1 = createObject("images/car1.png");
	p2 = createObject("images/car2.png");
	red = createObject("images/red.png");
	green = createObject("images/green.png");
	yellow = createObject("images/yellow.png");

	trafficlight = createObject("images/trafficlight.png");
	scaleObject(p1, 0.1f);
	scaleObject(p2, 0.1f);
	scaleObject(red, 0.5f);
	scaleObject(yellow, 0.5f);
	scaleObject(green, 0.5f);
	scaleObject(trafficlight, 0.5f);
	scaleObject(car1, 0.3f);
	scaleObject(car2, 0.3f);

	locateObject(p1, scene1, 110, 635);
	locateObject(p2, scene1, 110, 595);
	locateObject(red, scene1, 1150, 345);
	locateObject(green, scene1, 1150, 280);
	locateObject(yellow, scene1, 1150, 215);
	locateObject(trafficlight, scene1, 1050, 170);
	locateObject(car1, scene1, car1X, car1Y);
	locateObject(car2, scene1, car2X, car2Y);

	if (typeSignal == 0) {
		showObject(red);
		typeSignal++;
	}
	else if (typeSignal == 1) {
		showObject(green);
		typeSignal++;
	}
	showObject(p1);
	showObject(p2);
	showObject(car1);
	showObject(car2);
	showObject(trafficlight);
	setSceneImage(scene1, "images/Racing.png");
	hideObject(nextButton);
}
void keyboardCallback(KeyCode code, KeyState state)
{
	if (code == KeyCode::KEY_D) {			
		car1dx += (state == KeyState::KEY_PRESSED ? speed : -speed);
	}
	else if (code == KeyCode::KEY_RIGHT_ARROW) {		
		car2dx += (state == KeyState::KEY_PRESSED ? speed : -speed);
	}
}
void endRace() {
	raceOn = false;
	stopTimer(timer1);
	stopTimer(timer2);
	stopTimer(timer3);
	hideObject(red);
	hideObject(green);
	hideObject(yellow);
	hideObject(car1);
	hideObject(car2);
	hideObject(p1);
	hideObject(p2);
	hideObject(trafficlight);
	showObject(startButton);
	gameNum++;
}
/////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////// Click Number
ObjectID one, two, three, four, five, six, seven, eight, nine;
TimerID timer4;
int num1 = 1;
bool NumberOn = false;
bool P1turn = true;
float scale1, t,p1t,p2t;
int nx, ny;
void BCNIO() {
	setSceneImage(scene1, "images/BCNIO.png");
	hideObject(startButton);
	locateObject(endButton, scene1, 1170, 680);
	showObject(nextButton);
} //// scale1 이 0되는지 점검 ****
void setNum(ObjectID object) {
	scale1 = (float)((rand() % 10) + 1) / 10;
	nx = rand() % (int)(1280 - 512 * scale1);
	ny = rand() % (int)(720 - 512 * scale1);
	scaleObject(object,scale1);
	locateObject(object, scene1, nx, ny);
	showObject(object);
}
void setall() {
	setNum(nine); setNum(eight); setNum(seven); setNum(six); setNum(five); setNum(four); setNum(three); setNum(two); setNum(one);
}
void clickrightNum(ObjectID object1,ObjectID object2,int i) {
	if (object1 == object2) {
		playSound(sound2);
		if (num1 == i) {
			num1++;
			hideObject(object2);
		}
		else {
			num1 = 1;
			setall();
		}
	}
}
void startNumber() {
	t = 0;
	timer4 = createTimer(0.1f);
	startTimer(timer4); 
	NumberOn = true;
	hideObject(nextButton);
	setSceneImage(scene1, "images/CNIO.png");
	one = createObject("images/1.png");
	two = createObject("images/2.png");
	three = createObject("images/3.png");
	four = createObject("images/4.png");
	five = createObject("images/5.png");
	six = createObject("images/6.png");
	seven = createObject("images/7.png");
	eight = createObject("images/8.png");
	nine = createObject("images/9.png");
	setall();
}
void endNumber() {
	gameNum++;
	showObject(startButton);
}
////////////////////////////////////////////////////////////////////////////

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == startButton) { 
		stopSound(sound1);
		playSound(sound2);
		if (gameNum == 0) {
			playSound(sound3,1);
			BCNIO();
		}
		if (gameNum == 1) {
			BRace();
		}
		if (gameNum == 2) {
			BPong();
		}
	}
	if (object == nextButton) {
		playSound(sound2);
		if (gameNum == 0) {
			startNumber();
		}
		if (gameNum == 1) {
			startRace();
		}
		if (gameNum == 2) {
			startPong();
		}
		if (gameNum == 3) {
			stopSound(sound3);
			playSound(sound4, 1);
			timer5 = createTimer(0.1f);
			hideObject(nextButton);
			startTimer(timer5);
			if(P1W == 2 && P2W == 1) setSceneImage(scene1, "images/p211.jpg");
			else if (P1W == 1 && P2W == 2) setSceneImage(scene1, "images/p121.jpg");
			else if (P1W == 3 && P2W == 0) setSceneImage(scene1, "images/p301.jpg");
			else if (P1W == 0 && P2W == 3) setSceneImage(scene1, "images/p031.jpg");
			else if (P1W == 1 && P2W == 1) setSceneImage(scene1, "images/p11.jpg");
		}
	}
	if (object == endButton) {
		playSound(sound2);
		endGame();
	}
	if (PongOn) {
		if (Bturn) {
			if (object == CirB1) {
				playSound(sound2);
				movePong(CirB1, B1X, B1Y);
				Bturn = false;
				setObjectImage(Turn, "images/RTurn.png");
			}
			else if (object == CirB2) {
				playSound(sound2);
				movePong(CirB2, B2X, B2Y);
				Bturn = false;
				setObjectImage(Turn, "images/RTurn.png");
			}
		}
		else {
			if (object == CirR1) {
				playSound(sound2);
				movePong(CirR1, R1X, R1Y);
				Bturn = true;
				setObjectImage(Turn, "images/BTurn.png");
			}
			else if (object == CirR2) {
				playSound(sound2);
				movePong(CirR2, R2X, R2Y);
				Bturn = true;
				setObjectImage(Turn, "images/BTurn.png");
			}
		}
	}
	if (NumberOn) {
		clickrightNum(object, one, 1); clickrightNum(object, two, 2); clickrightNum(object, three, 3); clickrightNum(object, four, 4); clickrightNum(object, five, 5); clickrightNum(object, six, 6); clickrightNum(object, seven, 7); clickrightNum(object, eight, 8); clickrightNum(object, nine, 9);
		if (num1 == 10) {
			if (P1turn) {
				p1t = t;
				stopTimer(timer4);
				char t1[100];
				sprintf_s(t1, 100, "Player 1 Time : %.1fs\nClick Nextbutton To Play Player 2's Game", p1t);
				showMessage(t1);
				showObject(nextButton);
				P1turn = false;
			}
			else {
				stopTimer(timer4);
				char t2[100];
				p2t = t;
				if (p1t > p2t) {
					sprintf_s(t2, 100, "Player 1 Time : %.1fs   Player 2 Time : %.1fs\nPlayer 2 Win!\nClick Startbutton To Play Next Game", p1t,p2t);
					showMessage(t2);
					P2W++;
				}
				else if (p1t < p2t) {
					sprintf_s(t2, 100, "Player 1 Time : %.1fs   Player 2 Time : %.1fs\nPlayer 1 Win!\nClick Startbutton To Play Next Game",p1t,p2t);
					showMessage(t2);
					P1W++;
				}
				else {
					sprintf_s(t2, 100, "Player 1 Time : %.1fs   Player 2 Time : %.1fs\nDraw!\nClick Startbutton To Play Next Game", p1t,p2t);
					showMessage(t2);
				}
				P1turn = true;
				endNumber();
			}
			num1 = 1;
		}
	}
}
void timerCallback(TimerID timer)
{
	if (raceOn) {
		if (timer == timer1) {
			car1X += car1dx;
			locateObject(car1, scene1, car1X, car1Y);
			setTimer(timer1, 0.01f);
			startTimer(timer1);
			if (car1dx > 0 && typeSignal == 1) {
				showMessage("Player 1 moved on the red light!\nPlayer 2 Win\nClick Startbutton To Play Next Game");
				P2W++;
				endRace();
			}
			if (car1X > 15 + 1070) {
				showMessage("Player 1 Win\nClick Startbutton To Play Next Game");
				P1W++;
				endRace();
			}
		}
		else if (timer == timer2) {
			car2X += car2dx;
			locateObject(car2, scene1, car2X, car2Y);
			setTimer(timer2, 0.01f);
			startTimer(timer2);
			if (car2dx > 0 && typeSignal == 1) {
				showMessage("Player 2 moved on the red light!\nPlayer 1 Win\nClick Startbutton To Play Next Game");
				P1W++;
				endRace();
			}
			if (car2X > 10 + 1070) {
				showMessage("Player 2 Win\nClick Startbutton To Play Next Game");
				P2W++;
				endRace();
			}
		}
		else if (timer == timer3) {
			signalTime = (rand() % 4) + 1;
			if (typeSignal == 0) {
				showObject(red);
				hideObject(green);
				hideObject(yellow);
				typeSignal++;


			}
			else if (typeSignal == 1) {
				showObject(green);
				hideObject(red);
				hideObject(yellow);
				typeSignal++;
			}
			else if (typeSignal == 2) {
				showObject(yellow);
				hideObject(red);
				hideObject(green);
				signalTime = 0.5;
				typeSignal = 0;
			}
			setTimer(timer3, signalTime);
			startTimer(timer3);
		}
	}
	if (NumberOn) {
		if(timer == timer4){
			t+=0.1;
			setTimer(timer4, 0.1f);
			startTimer(timer4);
		}
	}
	if (timer == timer5) {
		char end[20];
		if (P1W == 2 && P2W == 1) sprintf_s(end, 20, "images/p21%d.jpg", endscenenum);
		else if (P1W == 1 && P2W == 2) sprintf_s(end, 20, "images/p12%d.jpg", endscenenum);
		else if (P1W == 3 && P2W == 0) sprintf_s(end, 20, "images/p30%d.jpg", endscenenum);
		else if (P1W == 0 && P2W == 3) sprintf_s(end, 20, "images/p03%d.jpg", endscenenum);
		else if (P1W == 1 && P2W == 1) sprintf_s(end, 20, "images/p11.jpg");
		endscenenum++;
		setSceneImage(scene1, end);
		setTimer(timer5, 0.1f);
		startTimer(timer5);
		if (endscenenum == 7) {
			stopTimer(timer5);
		}

	}
}


int main() {
	sound1 = createSound("sounds/main.mp3");
	sound2 = createSound("sounds/button.mp3");
	sound3 = createSound("sounds/play.mp3");
	sound4 = createSound("sounds/end.mp3");
	playSound(sound1,1);
	setTimerCallback(timerCallback);
	srand(time(NULL));
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	scene1 = createScene("2인용 미니 게임", "Images/StartBack.jpg");
	startButton = createObject("Images/start.png");
	endButton = createObject("Images/end.png");
	nextButton = createObject("Images/next.png");
	scaleObject(nextButton, 0.15f);
	locateObject(nextButton, scene1, 1170, 20);
	locateObject(startButton, scene1, 590, 160);
	locateObject(endButton, scene1, 590, 120);
	showObject(startButton);
	showObject(endButton);
	setMouseCallback(mouseCallback);
	setKeyboardCallback(keyboardCallback);
	startGame(scene1);
}