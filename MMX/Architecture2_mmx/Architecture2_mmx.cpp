#include "stdafx.h"
#include <iostream>
#include <cassert>
#undef NDEBUG

void Add(signed int *fir, signed int *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 1
		jz lenLes8

        mov esi, [sec]
		mov edi, [fir]
   cyc: movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		paddd mm0, mm1
		movq qword ptr[edi], mm0
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 1
		jz ext
  cyc2: lodsd
		add eax, [edi]
		stosd
		loop cyc2

   ext: emms
	}
}
void Add(signed short *fir, signed short *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 2
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
   cyc: movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		paddw mm0, mm1
		movq qword ptr[edi], mm0
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 3
		jz ext
  cyc2: lodsw
		add ax, word ptr[edi]
		stosw
		loop cyc2

   ext: emms
	}
}
void Add(signed char *fir, signed char *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 3
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
  cyc:  movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		paddb mm0, mm1
		movq qword ptr[edi], mm0
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 7
		jz ext				
  cyc2: lodsb
		add al, byte ptr[edi]
		stosb
		loop cyc2

   ext: emms
	}
}
void AddSatr(unsigned short *fir, unsigned short *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 2
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
		cyc:  movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		paddusw mm0, mm1
		movq qword ptr[edi], mm0
		add esi, 8
		add edi, 8
		loop cyc

		lenles8 : mov ecx, len
		and ecx, 3
		jz ext			
  cyc2: lodsw
		add ax, word ptr[edi]
		jnc corr
		mov ax, 0ffffh
  corr: stosw
		loop cyc2

   ext: emms
	}
}
void AddSatr(unsigned char *fir, unsigned char *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 3
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
  cyc:  movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		paddusb mm0, mm1
		movq qword ptr[edi], mm0
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 7
		jz ext				
  cyc2: lodsb
		add al, byte ptr[edi]
		jnc corr
		mov al, 0ffh
  corr: stosb
		loop cyc2
		
   ext: emms
	}
}
void AddSatr(signed short *fir, signed short *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 2
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
	cyc:movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		paddsw mm0, mm1
		movq qword ptr[edi], mm0
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 3
		jz ext
  cyc2: lodsw
		add ax, word ptr[edi]
		jno corr
		mov ax, 7fffh
  corr: stosw
		loop cyc2

   ext: emms
	}
}
void AddSatr(signed char *fir, signed char *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 3
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
	cyc:movq mm0, qword ptr [esi]
		movq mm1, qword ptr [edi]
		paddsb mm0, mm1
		movq qword ptr [edi], mm0
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 7
		jz ext
  cyc2: lodsb
		add al, byte ptr[edi]
		jno corr
		mov al, 7fh
  corr: stosb
		loop cyc2

	ext:emms
	}
}

void Sub(signed int *fir, signed int *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 1
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
		cyc:  movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		psubd mm1, mm0
		movq qword ptr[edi], mm1
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 1
		jz ext		
   cyc2:lodsd
		sub [edi], eax
		mov eax, [edi]
		stosd
		loop cyc2

   ext: emms
	}
}
void Sub(signed short *fir, signed short *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 2
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
   cyc: movq mm0, qword ptr[esi]
	    movq mm1, qword ptr[edi]
		psubw mm1, mm0
		movq qword ptr[edi], mm1
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 3
		jz ext				
   cyc2:lodsw
		sub word ptr[edi], ax
		mov ax, [edi]
		stosw
		loop cyc2

   ext: emms
	}
}
void Sub(signed char *fir, signed char *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 3
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
   cyc: movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		psubb mm1, mm0
		movq qword ptr[edi], mm1
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 7
		jz ext
						
  cyc2: lodsb
		sub byte ptr[edi], al
		mov al, byte ptr[edi]
		stosb
		loop cyc2

	ext: emms
	}
}
void SubSatr(unsigned short *fir, unsigned short *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 2
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
   cyc: movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		psubusw mm1, mm0
		movq qword ptr[edi], mm1
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 3
		jz ext					
  cyc2: lodsw
		sub word ptr[edi], ax
		mov ax, [edi]
		jnc corr
		mov ax, 0h
  corr: stosw
		loop cyc2

   ext: emms
	}
}
void SubSatr(unsigned char *fir, unsigned char *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 3
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
   cyc: movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		psubusb mm1, mm0
		movq qword ptr[edi], mm1
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 7
		jz ext		
  cyc2: lodsb
	    sub byte ptr[edi], al
		mov al, [edi]
		jnc corr
		mov al, 0h
  corr: stosb
		loop cyc2

	ext: emms
	}
}
void SubSatr(signed short *fir, signed short *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 2
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
   cyc: movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		psubsw mm1, mm0
		movq qword ptr[edi], mm1
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 3
		jz ext			
  cyc2: lodsw
	    sub word ptr[edi], ax
		mov ax, [edi]
		jno corr
		mov ax, 8000h
  corr: stosw
		loop cyc2

   ext: emms
	}
}
void SubSatr(signed char *fir, signed char *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 3
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
   cyc: movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		psubsb mm1, mm0
		movq qword ptr[edi], mm1
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 7
		jz ext		
  cyc2: lodsb
		sub byte ptr[edi], al
		mov al, [edi]
		jno corr
		mov al, 80h
  corr: stosb
		loop cyc2

   ext: emms
	}
}

void Mul(unsigned short *fir, size_t len, int n)
{
	_asm
	{
		mov ecx, len
		mov edx, ecx
		shr ecx, 2
		jz lenLes8

		mov edi, [fir]
		movd mm0, n
   cyc: movq mm1, qword ptr[edi]
		psllw mm1, mm0
		movq qword ptr[edi], mm1
		add edi, 8
		loop cyc

lenles8:mov esi, edi
		mov ecx, n
		and edx, 3
		jz ext
  cyc2: lodsw
		shl ax, cl
		stosw
		dec edx
		jnz cyc2

   ext: emms
	}

}
void Mul(unsigned int *fir, size_t len, int n)
{
	_asm
	{
		mov ecx, len
		mov edx, ecx
		shr ecx, 1
		jz lenLes8

		mov edi, [fir]
		movd mm0, n
  cyc:  movq mm1, qword ptr[edi]
		pslld mm1, mm0
		movq qword ptr[edi], mm1
		add edi, 8
		loop cyc

lenles8:mov ecx, n
		and edx, 1
		mov esi, edi
		jz ext
  cyc2: lodsd
		shl eax, cl
		stosd
		dec edx
		jnz cyc2

  ext : emms
	}
}
void Div(unsigned short *fir, size_t len, int n)
{
	_asm
	{
		mov ecx, len
		mov edx, ecx
		shr ecx, 2
		jz lenLes8

		mov edi, [fir]
		movd mm0, n
   cyc: movq mm1, qword ptr[edi]
		psrlw mm1, mm0
		movq qword ptr[edi], mm1
		add edi, 8
		loop cyc

lenles8:mov ecx, n
		and edx, 3
		mov esi, edi
		jz ext
   cyc2:lodsw
		shr ax, cl
		stosw
		dec edx
		jnz cyc2

	ext: emms
	}

}
void Div(unsigned int *fir, size_t len, int n)
{
	_asm
	{
		mov ecx, len
		mov edx, ecx
		shr ecx, 1
		jz lenLes8

		mov edi, [fir]
		movd mm0, n
   cyc: movq mm1, qword ptr[edi]
		psrld mm1, mm0
		movq qword ptr[edi], mm1
		add edi, 8
		loop cyc

lenles8:mov ecx, n
		and edx, 1
		mov esi, edi
		jz ext
  cyc2: lodsd
		shr eax, cl
		stosd
		dec edx
		jnz cyc2

   ext: emms
	}
}
void Div(signed short *fir, size_t len, int n)
{
	_asm
	{
		mov ecx, len
		mov edx, ecx
		shr ecx, 2
		jz lenLes8

		mov edi, [fir]
		movd mm0, n
   cyc: movq mm1, qword ptr[edi]
		psraw mm1, mm0
		movq qword ptr[edi], mm1
		add edi, 8
		loop cyc

lenles8:mov ecx, n
		and edx, 3
		mov esi, edi
		jz ext
   cyc2:lodsw
		sar ax, cl
		stosw
		dec edx
		jnz cyc2

   ext: emms
	}

}
void Div(signed int *fir, size_t len, int n)
{
	_asm
	{
		mov ecx, len
		mov edx, ecx
		shr ecx, 1
		jz lenLes8

		mov edi, [fir]
		movd mm0, n
   cyc: movq mm1, qword ptr[edi]
		psrad mm1, mm0
		movq qword ptr[edi], mm1
		add edi, 8
		loop cyc

lenles8:mov ecx, n
		and edx, 1
		mov esi, edi
		jz ext
  cyc2 :lodsd
		sar eax, cl
		stosd
		dec edx
		jnz cyc2

	ext:emms
	}
}

bool IsEqu(signed char *fir, signed char *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 3
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
    cyc:movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		pcmpeqb mm0, mm1
		packsswb mm0, mm0
		movd eax, mm0
		cmp eax, 0ffffffffh
		jnz nt
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 7
		jz ext
   cyc2:lodsb
		cmp al, byte ptr [edi]
		jnz nt
	    stosb
		loop cyc2

  ext : emms
	}
	return true;
nt:return false;
}
bool IsEqu(signed short *fir, signed short *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 2
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
    cyc:movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		pcmpeqw mm0, mm1
		packsswb mm0, mm0
		movd eax, mm0
		cmp eax, 0ffffffffh
		jnz nt
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 3
		jz ext
   cyc2:lodsw
		cmp ax, word ptr [edi]
		jnz nt
	    stosw
		loop cyc2

  ext : emms
	}
	return true;
nt:return false;
}
bool IsEqu(signed int *fir, signed int *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 1
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
    cyc:movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		pcmpeqd mm0, mm1
		packssdw mm0, mm0
		movd eax, mm0
		cmp eax, 0ffffffffh
		jnz nt
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 1
		jz ext
   cyc2:lodsd
		cmp eax, [edi]
		jnz nt
	    stosd
		loop cyc2

  ext : emms
	}
	return true;
nt:return false;
}

bool Greater(signed char *fir, signed char *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 3
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
    cyc:movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		pcmpgtb mm1, mm0
		packsswb mm1, mm1
		movd eax, mm1
		cmp eax, 0ffffffffh
		jnz nt
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 7
		jz ext
   cyc2:lodsb
		cmp al, byte ptr [edi]
		jge nt
	    stosb
		loop cyc2

  ext : emms
	}
	return true;
nt:return false;
}
bool Greater(signed short *fir, signed short *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 2
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
    cyc:movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		pcmpgtw mm1, mm0
		packsswb mm1, mm1
		movd eax, mm1
		cmp eax, 0ffffffffh
		jnz nt
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 3
		jz ext
   cyc2:lodsw
		cmp ax, word ptr [edi]
		jge nt
	    stosw
		loop cyc2

  ext : emms
	}
	return true;
nt:return false;
}
bool Greater(signed int *fir, signed int *sec, size_t len)
{
	_asm
	{
		mov ecx, len
		shr ecx, 1
		jz lenLes8

		mov esi, [sec]
		mov edi, [fir]
    cyc:movq mm0, qword ptr[esi]
		movq mm1, qword ptr[edi]
		pcmpgtd mm1, mm0
		packssdw mm1, mm1
		movd eax, mm1
		cmp eax, 0ffffffffh
		jnz nt
		add esi, 8
		add edi, 8
		loop cyc

lenles8:mov ecx, len
		and ecx, 1
		jz ext
   cyc2:lodsd
		cmp eax, [edi]
		jge nt
	    stosd
		loop cyc2

  ext : emms
	}
	return true;
nt:return false;
}

void SIGNED_BYTE_TESTS()
{
	signed char *fir, *sec, *exp;

	// add signed byte 

	fir = new signed char[11]{ -1,2,3,4,5,6,7,8,9,10 };
	sec = new signed char[11]{ 1,2,3,4,5,6,7,8,9,10 };
	exp = new signed char[11]{ 0,4,6,8,10,12,14,16,18,20};
	Add(fir, sec, 10);
	assert(!memcmp(fir, exp, 10));
	delete[] fir, sec, exp;

	fir = new signed char[11]{ 1,2,3,4,5,6,7,8,9,_I8_MAX };
	sec = new signed char[11]{ 1,2,3,4,5,6,7,8,9,_I8_MAX };
	exp = new signed char[11]{ 2,4,6,8,10,12,14,16,18,-2 };
	Add(fir, sec, 10);
	assert(!memcmp(fir, exp, 10));
	delete[] fir, sec, exp;

	fir = new signed char[11]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9 };
	sec = new signed char[11]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9 };
	exp = new signed char[11]{ 2,-2,6,8,10,12,14,16,-2,18 };
	Add(fir, sec, 10);
	assert(!memcmp(fir, exp, 10));
	delete[] fir, sec, exp;

	fir = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,127 };
	sec = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,1 };
	exp = new signed char[20]{ 2,-2,6,8,10,12,14,16,-2,18,20,22,24,26,28,30,32,34,36,-128 };
	Add(fir, sec, 20);
	assert(!memcmp(fir, exp, 20));
	delete[] fir, sec, exp;

	// add signed byte saturation

	fir = new signed char[11]{ -1,2,3,4,5,6,7,8,9,10 };
	sec = new signed char[11]{ 1,2,3,4,5,6,7,8,9,10 };
	exp = new signed char[11]{ 0,4,6,8,10,12,14,16,18,20 };
	AddSatr(fir, sec, 10);
	assert(!memcmp(fir, exp, 10));
	delete[] fir, sec, exp;

	fir = new signed char[11]{ 1,2,3,4,5,6,7,8,9,_I8_MAX };
	sec = new signed char[11]{ 1,2,3,4,5,6,7,8,9,_I8_MAX };
	exp = new signed char[11]{ 2,4,6,8,10,12,14,16,18,_I8_MAX };
	AddSatr(fir, sec, 10);
	assert(!memcmp(fir, exp, 10));
	delete[] fir, sec, exp;

	fir = new signed char[11]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9 };
	sec = new signed char[11]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9 };
	exp = new signed char[11]{ 2,_I8_MAX,6,8,10,12,14,16,_I8_MAX,18 };
	AddSatr(fir, sec, 10);
	assert(!memcmp(fir, exp, 10));
	delete[] fir, sec, exp;

	fir = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,127 };
	sec = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,1 };
	exp = new signed char[20]{ 2,_I8_MAX,6,8,10,12,14,16,_I8_MAX,18,20,22,24,26,28,30,32,34,36,127 };
	AddSatr(fir, sec, 20);
	assert(!memcmp(fir, exp, 20));
	delete[] fir, sec, exp;

	// sub signed byte 

	fir = new signed char[11]{ -1,2,3,4,5,6,7,8,9,10 };
	sec = new signed char[11]{  1,2,3,4,5,6,7,8,9,10 };
	exp = new signed char[11]{ -2,0,0,0,0,0,0,0,0,0,0 };
	Sub(fir, sec, 10);
	assert(!memcmp(fir, exp, 10));
	delete[] fir, sec, exp;

	fir = new signed char[11]{ 1,2,3,4,5,6,7,8,9,_I8_MAX };
	sec = new signed char[11]{ 1,2,3,4,5,6,7,8,9,_I8_MAX };
	exp = new signed char[11]{ 0,0,0,0,0,0,0,0,0,0,0 };
	Sub(fir, sec, 10);
	assert(!memcmp(fir, exp, 10));
	delete[] fir, sec, exp;

	fir = new signed char[11]{ 10,_I8_MAX,3,4,5,6,7,8,_I8_MAX,90,0 };
	sec = new signed char[11]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,0 };
	exp = new signed char[11]{ 9,0,0,0,0,0,0,0,0,81,0 };
	Sub(fir, sec, 10);
	assert(!memcmp(fir, exp, 10));
	delete[] fir, sec, exp;

	fir = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,127 };
	sec = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,1 };
	exp = new signed char[20]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,126};
	Sub(fir, sec, 20);
	assert(!memcmp(fir, exp, 20));
	delete[] fir, sec, exp;

	//sub signed byte saturation

	fir = new signed char[11]{ -1,2,3,4,5,6,7,8,9,10 };
	sec = new signed char[11]{ 1,2,3,4,5,6,7,8,9,10 };
	exp = new signed char[11]{ -2,0,0,0,0,0,0,0,0,0,0 };
	SubSatr(fir, sec, 10);
	assert(!memcmp(fir, exp, 10));
	delete[] fir, sec, exp;

	fir = new signed char[11]{ 1,2,3,4,5,6,7,8,9,_I8_MIN };
	sec = new signed char[11]{ 1,2,3,4,5,6,7,8,9,_I8_MIN };
	exp = new signed char[11]{ 0,0,0,0,0,0,0,0,0,0,_I8_MIN };
	SubSatr(fir, sec, 10);
	assert(!memcmp(fir, exp, 10));
	delete[] fir, sec, exp;

	fir = new signed char[11]{ 10,_I8_MIN,3,4,5,6,7,8,_I8_MIN,90,0 };
	sec = new signed char[11]{ 1,_I8_MIN,3,4,5,6,7,8,_I8_MIN,9,0 };
	exp = new signed char[11]{ 9,0,0,0,0,0,0,0,0,81,0 };
	SubSatr(fir, sec, 10);
	assert(!memcmp(fir, exp, 10));
	delete[] fir, sec, exp;

	fir = new signed char[20]{ 1,_I8_MIN,3,4,5,6,7,8,_I8_MIN,9,10,11,12,13,14,15,16,17,18,-128 };
	sec = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,1 };
	exp = new signed char[20]{ 0,_I8_MIN,0,0,0,0,0,0,_I8_MIN,0,0,0,0,0,0,0,0,0,0,-128 };
	SubSatr(fir, sec, 20);
	assert(!memcmp(fir, exp, 20));
	delete[] fir, sec, exp;

	// isEdu signed byte

	fir = new signed char[11]{ 1,2,3,4,5,6,7,8,9,10 };
	sec = new signed char[11]{ 1,2,3,4,5,6,7,8,9,10 };
	assert(IsEqu(fir, sec, 10) == true);
	delete[] fir, sec;

	fir = new signed char[11]{ 1,2,3,4,5,6,7,8,9,_I8_MIN };
	sec = new signed char[11]{ 1,2,3,4,5,6,7,8,9,_I8_MIN };
	assert(IsEqu(fir, sec, 10) == true);
	delete[] fir, sec;

	fir = new signed char[11]{ 10,_I8_MIN,3,4,5,6,7,8,_I8_MIN,90,0 };
	sec = new signed char[11]{ 1,_I8_MIN,3,4,5,6,7,8,_I8_MIN,9,0 };
	assert(IsEqu(fir, sec, 10) == false);
	delete[] fir, sec;

	fir = new signed char[20]{ 1,_I8_MIN,3,4,5,6,7,8,_I8_MIN,9,10,11,12,13,14,15,16,17,18,-128 };
	sec = new signed char[20]{ 1,_I8_MIN,3,4,5,6,7,8,_I8_MIN,9,10,11,12,13,14,15,16,17,18,-128 };
	assert(IsEqu(fir, sec, 20) == true);
	delete[] fir, sec;

	fir = new signed char[20]{ 1,_I8_MIN,3,4,5,6,7,8,_I8_MIN,9,10,11,12,13,14,15,16,17,18,-128 };
	sec = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,-128 };
	assert(IsEqu(fir, sec, 20) == false);
	delete[] fir, sec;

	fir = new signed char[20]{ 0,_I8_MIN,3,4,5,6,7,8,_I8_MIN,9,10,11,12,13,14,15,16,17,18,-128 };
	sec = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,-128 };
	assert(IsEqu(fir, sec, 20) == false);

	fir = new signed char[20]{ 0,0,3,4,5,6,7,8,0,9,10,11,12,13,14,15,16,17,18,-128 };
	sec = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,-128 };
	assert(IsEqu(fir, sec, 20) == false);
	delete[] fir, sec;

	// greater signed byte 

	fir = new signed char[11]{ 1,2,3,4,5,6,7,8,9,10 };
	sec = new signed char[11]{ 1,2,3,4,5,6,7,8,9,10 };
	assert(Greater(fir, sec, 10) == false);
	delete[] fir, sec;

	fir = new signed char[11]{ 2,3,4,5,6,7,8,9,10,0 };
	sec = new signed char[11]{ 1,2,3,4,5,6,7,8,9,_I8_MIN };
	assert(Greater(fir, sec, 10) == true);
	delete[] fir, sec;

	fir = new signed char[11]{ 1,3,4,5,6,7,8,9,10,0 };
	sec = new signed char[11]{ 1,2,3,4,5,6,7,8,9,_I8_MIN };
	assert(Greater(fir, sec, 10) == false);
	delete[] fir, sec;

	fir = new signed char[11]{ _I8_MAX,_I8_MAX,_I8_MAX,_I8_MAX,_I8_MAX,_I8_MAX,_I8_MAX,_I8_MAX,_I8_MAX,_I8_MAX,_I8_MAX };
	sec = new signed char[11]{ 1,_I8_MIN,3,4,5,6,7,8,_I8_MIN,9,0 };
	assert(Greater(fir, sec, 10) == true);
	delete[] fir, sec;

	fir = new signed char[20]{ 1,_I8_MIN,3,4,5,6,7,8,_I8_MIN,9,10,11,12,13,14,15,16,17,18,-128 };
	sec = new signed char[20]{ 1,_I8_MIN,3,4,5,6,7,8,_I8_MIN,9,10,11,12,13,14,15,16,17,18,-128 };
	assert(Greater(fir, sec, 20) == false);
	delete[] fir, sec;

	fir = new signed char[20]{ 1,_I8_MIN,3,4,5,6,7,8,_I8_MIN,9,10,11,12,13,14,15,16,17,18,-128 };
	sec = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,-128 };
	assert(Greater(fir, sec, 20) == false);
	delete[] fir, sec;

	fir = new signed char[20]{ 0,_I8_MIN,3,4,5,6,7,8,_I8_MIN,9,10,11,12,13,14,15,16,17,18,-128 };
	sec = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,-128 };
	assert(Greater(fir, sec, 20) == false);

	fir = new signed char[20]{ 0,0,3,4,5,6,7,8,0,9,10,11,12,13,14,15,16,17,18,-128 };
	sec = new signed char[20]{ 1,_I8_MAX,3,4,5,6,7,8,_I8_MAX,9,10,11,12,13,14,15,16,17,18,-128 };
	assert(Greater(fir, sec, 20) == false);
	delete[] fir, sec;
}
void UNSIGNED_WORD_TESTS()
{
	unsigned short *fir, *res;
	int mult;

	// mul unsigned word

	fir = new unsigned short[11]{ 1,2,3,4,5,6,7,8,9,10,11 };
	res = new unsigned short[11]{ 2,4,6,8,10,12,14,16,18,20,22 };
	mult = 1;
	Mul(fir, 11, mult);
	assert(!memcmp(fir,res,11));
	delete[] fir, res;

	fir = new unsigned short[11]{ 1,2,3,4,5,6,7,8,9,UINT16_MAX };
	res = new unsigned short[11]{ 1,2,3,4,5,6,7,8,9,UINT16_MAX };
	mult = 0;
	Mul(fir, 11, mult);
	assert(!memcmp(fir, res, 11));
	delete[] fir, res;

	fir = new unsigned short[11]{ 10,UINT16_MAX,3,4,5,6,7,8,UINT16_MAX,45,0 };
	res = new unsigned short[11]{ 20,65534,6,8,10,12,14,16,65534,90,0 };
	mult = 1;
	Mul(fir, 11, mult);
	assert(!memcmp(fir, res, 11));
	delete[] fir, res;

	// div unsigned word

	fir = new unsigned short[11]{ 2,4,6,8,10,12,14,16,18,20,22 };
	res = new unsigned short[11]{ 1,2,3,4,5,6,7,8,9,10,11 };
	mult = 1;
	Div(fir, 11, mult);
	assert(!memcmp(fir, res, 11));
	delete[] fir, res;

}

void PrintArray(signed short *arr, size_t len);
void SIMPLE_CONSOLE_INPUT()
{
	signed short *fir = new signed short[100]
				,*sec = new signed short[100],
				 *firCopy = new signed short[100];
	size_t len;
	int multiplier;
	std::cout << "Task: MMX (current type: signed short)" << '\n';
	std::cout << "Enter the length of the array: ";
	std::cin >> len;
	std::cout << "Enter the first string of integer (sep. by space): ";
	for (size_t i = 0; i < len; i++)
		std::cin >> fir[i];
	std::cout << "Enter the second array of integer (sep. by space): ";
	for (size_t i = 0; i < len; i++)
		std::cin >> sec[i];
	std::cout << "Enter the degree: ";
	std::cin >> multiplier;

	memcpy(firCopy, fir, len*2);
	Add(firCopy, sec, len);
	std::cout << "Add: " << '\n';
	PrintArray(firCopy, len);

	memcpy(firCopy, fir, len * 2);
	AddSatr(firCopy, sec, len);
	std::cout << "Add with saturation: " << '\n';
	PrintArray(firCopy, len);

	memcpy(firCopy, fir, len * 2);
	Sub(firCopy, sec, len);
	std::cout << "Sub: " << '\n';
	PrintArray(firCopy, len);

	memcpy(firCopy, fir, len * 2);
	SubSatr(firCopy, sec, len);
	std::cout << "Sub with saturation: " << '\n';
	PrintArray(firCopy, len);

	memcpy(firCopy, fir, len * 2);
	Mul((unsigned short*)firCopy, len, 2);
	std::cout << "Mul first: " << '\n';
	PrintArray(firCopy, len);

	memcpy(firCopy, fir, len * 2);
	Div(firCopy, len, multiplier);
	std::cout << "Div first: " << '\n';
	PrintArray(firCopy, len);

	memcpy(firCopy, fir, len * 2);
	std::cout << "Is equivalet?: " << '\n';
	std::cout << IsEqu(firCopy, sec, len) << '\n';

	memcpy(firCopy, fir, len * 2);
	std::cout << "Is greater?: " << '\n';
	std::cout << Greater(firCopy, sec, len) << '\n';

	delete[] fir, sec, firCopy;
}

void PrintArray(signed short *arr, size_t len)
{
	for (size_t i = 0; i < len; i++)
		std::cout << arr[i] << ' ';
	std::cout << '\n';
}
int main()
{
	SIGNED_BYTE_TESTS();
	UNSIGNED_WORD_TESTS();

	SIMPLE_CONSOLE_INPUT();
	return 0;
}



