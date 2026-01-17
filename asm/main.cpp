#include <stdio.h>

void intro() {
	// dodawanie 2 liczb
	unsigned char a, b;
	unsigned short y;

	a = 255;
	b = 200;

	_asm {
		XOR AH, AH // clearing registry
		MOV AL, a
		MOV BL, b
		ADD AL, BL
		ADC AH, 0 // AH = AH + 0 + Carry

		LEA ESI, y // ESI holds ptr to y
		MOV [ESI], AL
		MOV [ESI+1], AH
	}

	printf("%d", y);
}
	
void zad1() {
// mnozenie z wzorem sprocenego mnozenia
	unsigned char a, b;
	unsigned int y;

	a = 255;
	b = 200;

	// (a+b)^2  =  a^2 + 2ab + b^2
	_asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX
		MOV	AL, a
		MOV BL, b
		MOV CL, AL

		MUL BL // AX = BL * AL wynik zawsze w AX
		SHL EAX, 1 // *2 - bit shift
		MOV ESI, EAX // 2ab

		MOV EAX, EBX // przeniesienie zmiennej b do rejestru
		MUL AL // pomnozenie go przez siebie
		ADD ESI, EAX // dodanie wyniku do rejestru z 2ab

		MOV EAX, ECX
		MUL AL
		ADD ESI, EAX

		MOV y, ESI //a^2 + 2ab + b^2
	}

	printf("%d", y);
}

void zad2() {
	// mnozenie zwykle
	unsigned char a, b;
	unsigned int y;

	a = 255;
	b = 200;

	// (a+b)^2
	_asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX
		MOV	AL, a
		MOV BL, b
		ADD AX, BX

		MUL AX // DX:AX = (a+b)^2
		// bity ktore sie nie zmiescily po mnozeniu zostaly wywalone do EDX
		SHL EDX, 16
		MOV DX, AX
		MOV y, EDX
	}
	printf("%d", y);
	}

void mul() {
	// mnozenie ze znakiem
	unsigned char a, b;
	short z;

	a = 255;
	b = 200;

	// z=3b
	_asm {
		XOR EAX, EAX
		MOV AL, b
		IMUL SI, AL, 3
		MOV z, SI
	}
	printf("%d", z);
	}

void suma() {
	// ile wynosi suma naturalnych nieparzystych liczb mniejszych od 100
	// 1 + 3 + 5 ... + 97 + 99
	int k = 0;
	for (int i = 1; i < 100; i+= 2) {
		k += i;
	}
	printf("%d", k);
}

void sum_odd() {
		// suma liczb nieparzystych
		int sum = 0;
		_asm {
			XOR EAX, EAX
			MOV EAX, 1
			MOV sum, 0

			petla:
				ADD sum, EAX
				ADD EAX, 2
				CMP EAX, 100
			JB petla
		}
		printf("%d", sum);
		_asm {
			XOR EAX, EAX
			MOV EAX, 99
			MOV sum, 0

			petlaa:
				ADD sum, EAX
				SUB EAX, 2
				JNS petlaa
		}
		printf("%d", sum);
}


	void zad3(){
	// plusik +  ^_^
	unsigned char a;
	bool y;
	// if(a==0x32) y=false else y=true
	// A
	a = 0x32;
	_asm {
		XOR AX, AX
		MOV al, a
		SUB al, 0x32
		XOR bl, bl
		SHL ax, 1

		OR bl, ah
		XOR ah, ah
		SHL ax, 1

		OR bl, ah
		XOR ah, ah
		SHL ax, 1

		OR bl, ah
		XOR ah, ah
		SHL ax, 1

		OR bl, ah
		XOR ah, ah
		SHL ax, 1

		OR bl, ah
		XOR ah, ah
		SHL ax, 1

		OR bl, ah
		XOR ah, ah
		SHL ax, 1

		OR bl, ah
		XOR ah, ah
		SHL ax, 1

		OR bl, ah
		XOR ah, ah
		SHL ax, 1

		MOV y, bl
	}
	printf("%d", y);

}



void zad4_A(){
	// for(int i=0; i!=5; i++) { y+=i }
	
	int i = 0, y = 0;
	_asm {
		XOR eax, eax 
		XOR ebx, ebx
		XOR ecx, ecx
		MOV eax , i

		petla:
			MOV ecx, eax
			SUB ecx, 5
			JZ koniec
			ADD ebx, eax
			ADD eax, 1
		JMP petla

		koniec:
		MOV y, ebx
	}
	printf("%d", y);
}

void zad4_B(){
	int i = 0, y = 0;
	
	// ver B
	_asm {
		MOV eax, y
		MOV ebx, 0
		petla :
			MOV ecx, eax
			ADD eax, ebx
			ADD ebx, 1
			CMP ebx, 5
			JNZ petla 
		MOV y, eax
	}
	printf("%d", y);
	
}

void zad4_C(){
	int i = 0, y = 0;
	
	_asm {
		// for( int i=5; i!=0; i--) y-=i
		MOV eax, 5
		mov edx, 0
		petla :
			cmp eax, 0
			jz koniec
			add edx, eax
			add eax, -1
			jmp petla

		koniec :
			xor edx, -1
			add edx, 1
			mov y, edx
	}
	printf("%d", y);
	
}

void zad5(){
	int y = 0;
	_asm {
		// while(y != 5) y+=1

		MOV eax, y
		petla :
		cmp eax, 5
		jz koniec
			add eax, 1
			jmp petla
			koniec:
		MOV y, eax
	}
}

void zad5_B(){
	int y = 0;
	_asm {
		// while(y != 5) y+=1
		MOV eax, y
		petla :
			MOV ebx, eax
			sub ebx, 5
			jz koniec
			add eax, 1
			jmp petla
			koniec :
		MOV y, eax
	}
}


void zad5_C(){
	int y = 0;
	
	_asm {
		// while(y != 5) y+=1

		MOV eax, y
		petla :
			add eax, 1
			cmp eax, 5
			jz koniec
		jmp petla
			koniec :
		MOV y, eax
	}
	

	printf("%d", y);
}


void zad7(){

	unsigned char a = 131; 
	unsigned char r = 0;
	//for (int i = 0; i < 8; i++) {
	//	r = r + ((a >> i) & 1);
	//	if (i != 7) {
	//		r = r << 1;
	//	}
	//}
	/*
	for (int i = 0; i < 7; i++) {
		r = r + ((a >> i) & 1);
		r = r << 1;
	}
	r = r + ((a >> 7) & 1);
	*/

	_asm {
		xor eax, eax;
		xor ebx, ebx;
		xor ecx, ecx;
		mov ah, a;
		mov bl, r;
		mov cl, 255;

		zamiana:
		shr ax, 1;
		mov bl, al;
		shl bx, 1;
		shr cl, 1;
		test cl, cl;
		jz wyjdz 
		jmp zamiana
		wyjdz:
		
		mov r, bh;
	}
}

void zad9a() {
	// zad 9: y = a * b
	unsigned char a = 255;
	unsigned char b = 255;
	unsigned short sum = 0;
	/*
	for (int i = a; i != 0; i--) {
		sum += b;
	}
	*/
	_asm {
		mov bx, 0
		mov ax, 0
		mov cx, 0 // sum
		mov al, a
		mov bl, b

		petla :
		add cx, bx
			add al, -1

			mov dl, al
			and dl, 255
			jz koniec

			mov dl, al
			and dl, 255
			jnz petla
			koniec :
		mov sum, cx
	}

	printf("%d, %d", sum, (a * b));
}

void zad9bc() {
	// zad 9: y = a * b
	unsigned char a = 120;
	unsigned char b = 200;
	unsigned short sum = 0;

	_asm {
		mov bx, 0
		mov ax, 0
		mov cx, 0 // sum
		mov al, a
		mov bl, b

		petla :
		add cx, bx
			add al, -1

			test al, 255
			jnz petla
			mov sum, cx
	}

	printf("%d, %d", sum, (a * b));
}

void zad9d() {
	unsigned char a = 10;
	unsigned char b = 30;
	unsigned short sum = 0;

	_asm {
		mov ax, 0
		mov bx, 0
		mov dx, 0
		mov al, a
		mov bl, b

		// 8x{
		mov ch, 0
		mov cl, al

		add cl, 1
		AND cl, 1
		add cx, -1

		and cx, bx
		add dx, cx

		shl bl, 1
		shr al, 1
		// }
		mov ch, 0
		mov cl, al
		add cl, 1
		AND cl, 1
		add cx, -1
		and cx, bx
		add dx, cx
		shl bl, 1
		shr al, 1

		mov ch, 0
		mov cl, al
		add cl, 1
		AND cl, 1
		add cx, -1
		and cx, bx
		add dx, cx
		shl bl, 1
		shr al, 1

		mov ch, 0
		mov cl, al
		add cl, 1
		AND cl, 1
		add cx, -1
		and cx, bx
		add dx, cx
		shl bl, 1
		shr al, 1

		mov ch, 0
		mov cl, al
		add cl, 1
		AND cl, 1
		add cx, -1
		and cx, bx
		add dx, cx
		shl bl, 1
		shr al, 1

		mov ch, 0
		mov cl, al
		add cl, 1
		AND cl, 1
		add cx, -1
		and cx, bx
		add dx, cx
		shl bl, 1
		shr al, 1

		mov ch, 0
		mov cl, al
		add cl, 1
		AND cl, 1
		add cx, -1
		and cx, bx
		add dx, cx
		shl bl, 1
		shr al, 1

		mov ch, 0
		mov cl, al
		add cl, 1
		AND cl, 1
		add cx, -1
		and cx, bx
		add dx, cx
		shl bl, 1
		shr al, 1

		mov sum, dx
	}
	printf("%d, %d", sum, (a * b));

}


void zad10_C() {
	//  mnozenie a * 1.125
	unsigned short a;
	unsigned int y;
	a = 1000;
	// y = a * 9/8 = a * (8+1)/8 = 8a+a/8
	y = a << 3;
	y = y + a;
	y = y >> 3;
	// y = a + (a >> 3)
	printf("%d", y);
}

void zad10() {
	//  mnozenie a * 1.125
	unsigned short a = 1000;
	unsigned int y;
	_asm {
		MOV EAX, 0
		mov ax, a
		MOV EBX, 0
		mov BX, AX
		shr BX, 3
		add EAX, EBX
		mov y, EAX
	}
	printf("%d", y);
}

void zad11ab() {
	unsigned char y, a;
	a = 2;
	_asm {
		mov AL, a
		mov BL, 1
		sub a, 0x05
		jnc koniec
		mov BL, 0
		koniec:
		mov y, BL
	}
	printf("%d", y);
}

void zad11c() {
	unsigned char y, a;
	a = 3;
	_asm {
		mov AL, a
		mov BL, 0
		mov CL, 0x05
		cmp CL, AL
		jnc koniec
		mov BL, 1
		koniec:
		mov y, BL
	}
	printf("%d", y);
}

void zad11d() {
	unsigned char y, a;
	a = 6;
	
	_asm {
		mov AL, a
		mov BL, 1
		mov CL, 250
		add AL, CL
		jc koniec
		mov BL, 0
		koniec:
		mov y, BL
	}
	printf("%d", y);
}

void zad12a() {
	int i=0, y=0;
	// for (int i = 0; i < 5; i++) y += i;  //y=10
	_asm {
		mov eax, 0 // y
		mov ebx, 0 // i
		mov ecx, 0 // temp
		start:
			mov ecx, ebx
			sub ecx, 5	 // i<5
			jnc koniec
			add eax, ebx // y += i
			add ebx, 1   // i++
			jmp start;
		koniec:
		mov y, eax
	}
	printf("%d", y);
}

void zad12c() {
	int i = 5, y = 0, b = 111;
	//for (int i = 5; i >= 1; i--) y -= i;  //y=-15

	_asm {
		mov eax, 0 // y
		mov ebx, 5 // i
		mov ecx, 0 // temp
		mov edx, 0 // temp 2
		start:
		mov ecx, ebx
			cmp ecx, 1	 // i<1
			jc koniec
			mov edx, ebx
			xor edx, -1
			add edx, 1
			add eax, edx
			add ebx, -1   // i--
			jmp start;
			koniec:
		mov y, eax
	}
	printf("%d", y);
}

void zad13() {
	char a = 5;
	char b = 4;
	char c = 1;

	_asm {
		mov al, a
		mov bl, b
		mov cl, c

		sub cl, 1
		jz prawda
		sub cl, cl
		jz skip

		prawda:
			and bl, 3
			mov al, bl

		skip:
		mov a, al
	}
	printf("%d", a);
}

void zad14() {
	char a = 13;
	char b = 22;
	char c = 0;

	_asm {
		mov al, a
		mov bl, b
		mov cl, 0

		and al, 1
		and bl, 7

		sub al, 1
		jz mnozenie
		sub al, al
		jz skip

		mnozenie:
		mov cl, bl

		skip:
		mov c, cl
	}
	printf("%d", c);
}


void zad15() {
	unsigned char tab[5];
	/*
	for (int i = 0; i != 5; i++) {
		*(tab + i) = i;
	}*/

	_asm {
		LEA ebx, tab
		mov eAX, 0

		petla:
		cmp eAX, 5
		jz koniec
			mov [ebx + EAX], AL

		add eAx, 1
		jmp petla

		koniec:
		//mov tab, EBX
	}


	for (int i = 0; i < 5; i++) {
		printf("%d ", tab[i]);
	}
}


void wyznaczniki() {
	double a[2][2] = { {2,4}, {3,5} };
	double b[2] = { 10, 11 };
	double x[2] = { 0, 0 };

	_asm {
		// praca z koprocesorem
		// wczytanie wskaxnikow
		LEA ESI, a
		LEA EBX, b
		LEA EDI, x

		// wrzut na stos
		FLD  qword ptr[ESI]			// a11
		FMUL qword ptr[ESI + 3*8]	// a22 // stack(0) = a11 * a22
		
		FLD  qword ptr[ESI + 2*8]	// a21
		FMUL qword ptr[ESI + 8]		// a12
		// stack(1) = a11 * a22 ^
		// stack(0) = a21 * a12
		FSUBP ST(1), ST(0) // float SUB pop
		// ST(0) = a11*a22 - a21*a12

		FLD  qword ptr[EBX]			// b11
		FMUL qword ptr[ESI + 3*8]	// a22 // stack(0) = b11 * a22
		FLD  qword ptr[EBX + 8]		// b12
		FMUL qword ptr[ESI + 8]		// a12 // st(0) = b12 * a12
		FSUBP ST(1), ST(0)
		

		FLD  qword ptr[ESI]			
		FMUL qword ptr[EBX + 8]	
		FLD  qword ptr[ESI + 2*8]		
		FMUL qword ptr[EBX]		
		FSUBP ST(1), ST(0)
		// ST(0) = Wx2
		// ST(1) = Wx1
		// ST(2) = W

		FDIV ST(0), ST(2)	// ST0 = st0/st2 = Wx2/W
		FSTP qword ptr[EDI + 8]		// float store pop
		// ST(0) = Wx1
		// ST(1) = W
		
		FDIV ST(0), ST(1)	// ST0 = st0/st1 = Wx1/W
		FSTP qword ptr[EDI]

	}
	printf("x1: %f, x2: %f", x[0], x[1]);
}


int main() {
	
	wyznaczniki();
	return 0;
}