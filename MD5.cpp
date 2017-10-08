#include "MD5.h"
#include <assert.h>

using std::string;
using std::cout;


/*          constructor                */
MD5::MD5()
{
	init() ;
}

MD5::MD5(const string text)
{
	init() ;	
	Managedata(text.c_str(),text.length());
}




/*         initial  variables                 */
void MD5::init()
{
	for(int i=0; i < 16; ++i)
		Mi[i] = 0 ;
	
	Hi[0] = 0x67452301 ;
	Hi[1] = 0xEFCDAB89 ;
	Hi[2] = 0x98BADCFE ;
	Hi[3] = 0x10325476 ;

}



/*           type convertion               */
void MD5::Managedata(const char* text, size_t n)
{
	Managedata((const unsigned char*)text,n);
}





/*				byte opreation				*/ 
void MD5::Managedata(const unsigned char* text, size_t n)
{
	byte1 block[64] ;
	for(int i = 0; i < n; ++i)
		block[i] = text[i] ;


	fill(block, n);
	
////////////////////////////////
	for(int i = 0, re = 8; i < 64 ; ++i)
	{
		printf("%4x,",block[i]);
		re--;
		if(re == 0) 
		{
			cout << std::endl ;
			re = 8 ;
		}		
	}
///////////////////////////////	

	encode(block);
	transform();
	final_handle();
}




/*         convert the decimal to hex         */
string MD5::hex(unsigned int dec)
{
	char ch[25] = {0x00};
	int bit_sum = dec*8 ;
	
	for(int i = 0; bit_sum != 0 ; ++i)
	{
		ch[i] =  bit_sum & 0xff ;
		bit_sum = bit_sum >> 8 ;
		
	}
	return  string(ch);
}





/*         padding  10000......000000  + length        */
void MD5::fill(byte1* block, size_t n)
{
	unsigned char end[64] = { 0x80 , 0x00 , 0x00 , 0x00 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
	0x00 , 0x00 , 0x00 , 0x00 	};
	
	int block_fill =  size - n - blocksize ;
	length = n ;
	
	for(int i = n; i < n+block_fill; ++i)
		block[i] = end[i-n] ;
	n += block_fill ;
	
	for(int i = n; i < size - blocksize ; ++i)
		block[i] = end[i-n] ;
	n = 56 ;
	
	
	string len = hex(length) ;
	
	for(int i = 0; i < blocksize; ++i)
	{
		block[size-i-1] = len[7-i];
	}



	 
}

void MD5::encode(const byte1* text)
{
	for(int i = 0, j = 0; i < 16; ++i,j+=4 )
	{
		Mi[i] = ((byte4)text[j])|((byte4)text[j+1]<<8)|((byte4)text[j+2]<<16)|((byte4)text[j+3]<<24)  ;
		printf("0x%08x \n",Mi[i]);
	}

	
}


inline MD5::byte4 MD5::F(byte4 x, byte4 y, byte4 z)
{
	return x&y | ~x&z; 
}
inline MD5::byte4 MD5::G(byte4 x, byte4 y, byte4 z)
{
	return x&z | y&~z;
}
inline MD5::byte4 MD5::H(byte4 x, byte4 y, byte4 z)
{
	return x^y^z;
}
inline MD5::byte4 MD5::I(byte4 x, byte4 y, byte4 z)
{
	return y ^ (x | ~z);
}


inline MD5::byte4 MD5::routate_left(byte4 unrtt, int s)
{
	return (unrtt << s) | (unrtt >> ( 32 - s ));
}

inline MD5::byte4 MD5::FF(byte4& a, byte4 b, byte4 c, byte4 d, byte4 Mi, byte4 s, byte4 Ti)
{
	a = routate_left(  (a + F(b, c, d) + Mi + Ti), s ) + b ;
}

inline MD5::byte4 MD5::GG(byte4& a, byte4 b, byte4 c, byte4 d, byte4 Mi, byte4 s, byte4 Ti)
{
	a = routate_left(  (a + G(b, c, d) + Mi + Ti), s ) + b ;
}

inline MD5::byte4 MD5::HH(byte4& a, byte4 b, byte4 c, byte4 d, byte4 Mi, byte4 s, byte4 Ti)
{
	a = routate_left(  (a + H(b, c, d) + Mi + Ti), s ) + b ;
}

inline MD5::byte4 MD5::II(byte4& a, byte4 b, byte4 c, byte4 d, byte4 Mi, byte4 s, byte4 Ti)
{
	a = routate_left( (a + I(b, c, d) + Mi + Ti), s ) + b ;
}











void MD5::transform()
{
	Hi[0] = 0x67452301;
	byte4 a = Hi[0] , b = Hi[1] , c = Hi[2] , d = Hi[3] ;

	/* first */
	FF(a ,b ,c ,d ,Mi[0] , 7 ,0xd76aa478 );  /**/
	FF(d ,a ,b ,c ,Mi[1] ,12 ,0xe8c7b756 );  /**/
	FF(c ,d ,a ,b ,Mi[2] ,17 ,0x242070db );  /**/
	FF(b ,c ,d ,a ,Mi[3] ,22 ,0xc1bdceee );  /**/
	FF(a ,b ,c ,d ,Mi[4] , 7 ,0xf57c0faf );  /**/
	FF(d ,a ,b ,c ,Mi[5] ,12 ,0x4787c62a );  /**/
	FF(c ,d ,a ,b ,Mi[6] ,17 ,0xa8304613 );  /**/
	FF(b ,c ,d ,a ,Mi[7] ,22 ,0xfd469501 );  /**/
	FF(a ,b ,c ,d ,Mi[8] , 7 ,0x698098d8 );  /**/
	FF(d ,a ,b ,c ,Mi[9] ,12 ,0x8b44f7af );  /**/
	FF(c ,d ,a ,b ,Mi[10] ,17 ,0xffff5bb1 );  /**/
	FF(b ,c ,d ,a ,Mi[11] ,22 ,0x895cd7be );  /**/
	FF(a ,b ,c ,d ,Mi[12] , 7 ,0x6b901122 );  /**/
	FF(d ,a ,b ,c ,Mi[13] ,12 ,0xfd987193 );  /**/
	FF(c ,d ,a ,b ,Mi[14] ,17 ,0xa679438e );  /**/
	FF(b ,c ,d ,a ,Mi[15] ,22 ,0x49b40821 );  /**/
	
	/* second */
	GG(a ,b ,c ,d ,Mi[1] ,5 ,0xf61e2562 );  /**/
	GG(d ,a ,b ,c ,Mi[6] ,9 ,0xc040b340 );  /**/
	GG(c ,d ,a ,b ,Mi[11] ,14 ,0x265e5a51 );  /**/
	GG(b ,c ,d ,a ,Mi[0] ,20 ,0xe9b6c7aa );  /**/
	GG(a ,b ,c ,d ,Mi[5] ,5 ,0xd62f105d );  /**/
	GG(d ,a ,b ,c ,Mi[10] ,9 ,0x02441453 );  /**/
	GG(c ,d ,a ,b ,Mi[15] ,14 ,0xd8a1e681 );  /**/
	GG(b ,c ,d ,a ,Mi[4] ,20 ,0xe7d3fbc8 );  /**/
	GG(a ,b ,c ,d ,Mi[9] ,5 ,0x21e1cde6 );  /**/
	GG(d ,a ,b ,c ,Mi[14] ,9 ,0xc33707d6 );  /**/
	GG(c ,d ,a ,b ,Mi[3] ,14 ,0xf4d50d87 );  /**/
	GG(b ,c ,d ,a ,Mi[8] ,20 ,0x455a14ed );  /**/
	GG(a ,b ,c ,d ,Mi[13] ,5 ,0xa9e3e905 );  /**/
	GG(d ,a ,b ,c ,Mi[2] ,9 ,0xfcefa3f8 );  /**/
	GG(c ,d ,a ,b ,Mi[7] ,14 ,0x676f02d9 );  /**/
	GG(b ,c ,d ,a ,Mi[12] ,20 ,0x8d2a4c8a );  /**/
	
	/* third */
	HH(a ,b ,c ,d ,Mi[5] ,4 ,0xfffa3942 );  /**/
	HH(d ,a ,b ,c ,Mi[8] ,11 ,0x8771f681 );  /**/
	HH(c ,d ,a ,b ,Mi[11] ,16 ,0x6d9d6122 );  /**/
	HH(b ,c ,d ,a ,Mi[14] ,23 ,0xfde5380c );  /**/
	HH(a ,b ,c ,d ,Mi[1] ,4 ,0xa4beea44 );  /**/
	HH(d ,a ,b ,c ,Mi[4] ,11 ,0x4bdecfa9 );  /**/
	HH(c ,d ,a ,b ,Mi[7] ,16 ,0xf6bb4b60 );  /**/
	HH(b ,c ,d ,a ,Mi[10] ,23 ,0xbebfbc70 );  /**/
	HH(a ,b ,c ,d ,Mi[13] ,4 ,0x289b7ec6 );  /**/
	HH(d ,a ,b ,c ,Mi[0] ,11 ,0xeaa127fa );  /**/
	HH(c ,d ,a ,b ,Mi[3] ,16 ,0xd4ef3085 );  /**/
	HH(b ,c ,d ,a ,Mi[6] ,23 ,0x04881d05 );  /**/
	HH(a ,b ,c ,d ,Mi[9] ,4 ,0xd9d4d039 );  /**/
	HH(d ,a ,b ,c ,Mi[12] ,11 ,0xe6db99e5 );  /**/
	HH(c ,d ,a ,b ,Mi[15] ,16 ,0x1fa27cf8 );  /**/
	HH(b ,c ,d ,a ,Mi[2] ,23 ,0xc4ac5665 );  /**/
	 
	/* fourth */
	II(a ,b ,c ,d ,Mi[0] ,6 ,0xf4292244 );  /**/
	II(d ,a ,b ,c ,Mi[7] ,10 ,0x432aff97 );  /**/
	II(c ,d ,a ,b ,Mi[14] ,15 ,0xab9423a7 );  /**/
	II(b ,c ,d ,a ,Mi[5] ,21 ,0xfc93a039 );  /**/
	II(a ,b ,c ,d ,Mi[12] ,6 ,0x655b59c3 );  /**/
	II(d ,a ,b ,c ,Mi[3] ,10 ,0x8f0ccc92 );  /**/
	II(c ,d ,a ,b ,Mi[10] ,15 ,0xffeff47d );  /**/
	II(b ,c ,d ,a ,Mi[1] ,21 ,0x85845dd1 );  /**/
	II(a ,b ,c ,d ,Mi[8] ,6 ,0x6fa87e4f );  /**/
	II(d ,a ,b ,c ,Mi[15] ,10 ,0xfe2ce6e0 );  /**/
	II(c ,d ,a ,b ,Mi[6] ,15 ,0xa3014314 );  /**/
	II(b ,c ,d ,a ,Mi[13] ,21 ,0x4e0811a1 );  /**/
	II(a ,b ,c ,d ,Mi[4] ,6 ,0xf7537e82 );  /**/
	II(d ,a ,b ,c ,Mi[11] ,10 ,0xbd3af235 );  /**/
	II(c ,d ,a ,b ,Mi[2] ,15 ,0x2ad7d2bb );  /**/
	II(b ,c ,d ,a ,Mi[9] ,21 ,0xeb86d391 );  /**/
	
	
	Hi[0] += a ;
	Hi[1] += b ;
	Hi[2] += c ;
	Hi[3] += d ;
	
	printf("abcd:%x %x %x %x\n",a,b,c,d);
	printf("final:%x %x %x %x\n",Hi[0],Hi[1],Hi[2],Hi[3]);

	
	
}

const string MD5::final_handle()
{
	char buffer[100] ;
	int pos = 0 ;
	string retext; 
	
	for(int i = 0; i < 4; ++i)
	{	
		sprintf(buffer+0,"%x",(Hi[i]&0x000000ff) >> 0)	;
		sprintf(buffer+2,"%x",(Hi[i]&0x0000ff00) >> 8)	;
		sprintf(buffer+4,"%x",(Hi[i]&0x00ff0000) >> 16)	;
		sprintf(buffer+6,"%x",(Hi[i]&0xff000000 )>> 24)	;
		retext += string(buffer) ;
	} 
	return retext;
}

const string md5(const std::string& text)
{
	MD5 _md5(text) ;
	return _md5.final_handle();
	
}




