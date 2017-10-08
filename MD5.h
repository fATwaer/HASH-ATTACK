#ifndef _MD5_ 
#define _MD5_

#include <iostream>
#include <string>


class MD5
{
public:
	
	MD5() ;
	MD5(const std::string );
	void Managedata(const char*, size_t );
	void Managedata(const unsigned char*, size_t);
	const std::string final_handle();	
	
private:
	typedef unsigned int byte4 ;
	typedef unsigned char byte1 ;
	typedef const unsigned int sizetype ;
	sizetype blocksize = 8;
	sizetype size = 64;
	sizetype infoblock = 4 ;
	
	std::string hex(unsigned int);
	void transform();
	void init();
	void fill(byte1* , size_t);
	void encode(const byte1*);
	
	static inline byte4 F(byte4 x, byte4 y, byte4 z);
	static inline byte4 G(byte4 x, byte4 y, byte4 z);
	static inline byte4 H(byte4 x, byte4 y, byte4 z);
	static inline byte4 I(byte4 x, byte4 y, byte4 z);
	
	static inline byte4 routate_left(byte4, int); 
	
	static inline byte4 FF(byte4& a, byte4 b, byte4 c, byte4 d, byte4 Mi, byte4 s, byte4 Ti);
	static inline byte4 GG(byte4& a, byte4 b, byte4 c, byte4 d, byte4 Mi, byte4 s, byte4 Ti);
	static inline byte4	HH(byte4& a, byte4 b, byte4 c, byte4 d, byte4 Mi, byte4 s, byte4 Ti);
	static inline byte4 II(byte4& a, byte4 b, byte4 c, byte4 d, byte4 Mi, byte4 s, byte4 Ti);
	
	unsigned int length ;
	byte4 Mi[16] ;
	byte4 Hi[4]  ;
	std::string retext;
	
};


const std::string md5(const std::string&);


#endif
