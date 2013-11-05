// ConvertData.cpp : implementation file
//

#include "stdafx.h"
#include "ConvertData.h"
#include <ctype.h>

// CConvertData

IMPLEMENT_DYNAMIC(CConvertData, CWnd)

CConvertData::CConvertData()
{

}

CConvertData::~CConvertData()
{
}


BEGIN_MESSAGE_MAP(CConvertData, CWnd)
END_MESSAGE_MAP()



// CConvertData message handlers
unsigned char CConvertData::ChartoByte(unsigned char *ch)
{
	char temp[3];
	unsigned char bAns;
	memset(temp,0,3);
	memcpy_s(temp,3,ch,2);
	
	sscanf_s(temp,"%X",&bAns);
	
	return bAns;
}

int CConvertData::ChartoByte(unsigned char *bArray, unsigned char *ch,int chLen)
{
	
	for(int i = 0; i < chLen /2 ; i++)
	{
		bArray[i] = ChartoByte(ch + i*2);
	}
	return 0;
}

int CConvertData::ByteToChar(unsigned char *ch, unsigned char *bArray, int datalen)
{
	for(int i = 0; i < datalen; i++)
	{
		ByteToChar(bArray[i],ch+i*2);
	}
	return 0;
}

int CConvertData::ByteToChar(unsigned char b, unsigned char *ch)
{
	char temp[3];
	memset(temp,0,3);
	sprintf_s(temp,3,"%02X",b);
	memcpy_s(ch,2,temp,2);

	return 0;
}

int CConvertData::HexStringToByteArray(CString str, unsigned char* byteArr, unsigned long* dataLen)
{
	
	int numchars = str.GetLength();
	char* temp = new char[numchars];//with spaces
	char* cleaned = new char[numchars]; //without spaces
	int ret = CONV_OK;//ok
	int Len = 0;  // reset data length
	int i;
	memcpy_s(temp,numchars,str,numchars);
	//check characters and remove spaces
	for(i=0;i< numchars;i++)
	{
		if(isxdigit(*(temp + i)))
		{
			*(cleaned +Len) = *(temp +i );
			Len++;
		}
		else if(isspace(*(temp + i)))
		{
			//do nothing
		}
		else
		{
			//not a valid character was entered
			ret = CONV_INVALID_CHAR_FOUND;
		}
	}

	if(ret == CONV_OK)
	{
		if(byteArr != NULL)
		{
			//check buffer length
			if(Len / 2 > *dataLen) //pair of characters to number of bytes
			{
				*dataLen = Len/2;
				ret= CONV_BUFFER_TOO_SHORT;
			}
			else
			{
				//convert to Byte Array
				for(i = 0; i < Len/2; i ++ )
				{
					*(byteArr +i ) = ChartoByte((unsigned char*)cleaned + i*2);
				}
			}
		}
		else
		{
			*dataLen = Len/2;//pair of char = number of bytes
		}
	}
	//else do nothing

	delete[] temp;
	delete[] cleaned;
	return ret;
}

int CConvertData::HexStringToByteArray(CString str, unsigned char* byteArr, int* dataLen)
{
	
	int numchars = str.GetLength();
	char* temp = new char[numchars];//with spaces
	char* cleaned = new char[numchars]; //without spaces
	int ret = CONV_OK;//ok
	int Len = 0;  // reset data length
	int i;
	memcpy_s(temp,numchars,str,numchars);
	//check characters and remove spaces
	for(i=0;i< numchars;i++)
	{
		if(isxdigit(*(temp + i)))
		{
			*(cleaned +Len) = *(temp +i );
			Len++;
		}
		else if(isspace(*(temp + i)))
		{
			//do nothing
		}
		else
		{
			//not a valid character was entered
			ret = CONV_INVALID_CHAR_FOUND;
		}
	}

	if(ret == CONV_OK)
	{
		if(byteArr != NULL)
		{
			//check buffer length
			if(Len / 2 > *dataLen) //pair of characters to number of bytes
			{
				*dataLen = Len/2;
				ret= CONV_BUFFER_TOO_SHORT;
			}
			else
			{
				//convert to Byte Array
				for(i = 0; i < Len/2; i ++ )
				{
					*(byteArr +i ) = ChartoByte((unsigned char*)cleaned + i*2);
				}
			}
		}
		else
		{
			*dataLen = Len/2;//pair of char = number of bytes
		}
	}
	//else do nothing

	delete[] temp;
	delete[] cleaned;
	return ret;
}

int CConvertData::CStringToChar(CString str, unsigned char *ch,int dataLen)
{

	memset(ch,0,dataLen);
	unsigned char *wData = new unsigned char[dataLen + 1];
	memset(wData, 0, dataLen + 1);

	memcpy(wData,str,dataLen*2);

	for(int i = 0; i < dataLen; i++)
	{
		memcpy(ch + i, wData + i , 1); /* Copy 1 byte at a time */
	}

	delete [] wData;
	return 0;
}
/*
CString CConvertData::Translate_CK_OBJECT_CLASS(CK_OBJECT_CLASS objcla)
{
	switch(objcla)
	{
	case CKO_DATA:
		return "CKO_DATA";
	case CKO_CERTIFICATE:
		return "CKO_CERTIFICATE";
	case CKO_HW_FEATURE:
		return "CKO_HW_FEATURE";
	case CKO_PRIVATE_KEY:
		return "CKO_PRIVATE_KEY";
	case CKO_PUBLIC_KEY:
		return "CKO_PUBLIC_KEY";
	case CKO_SECRET_KEY:
		return "CKO_SECRET_KEY";
	case CKO_VENDOR_DEFINED:
		return "CKO_VENDOR_DEFINED";
	default:
		return "UNDEFINED OBJECT CLASS";	
	}
}

CString CConvertData::Translate_CK_KEY_TYPE(CK_MECHANISM_TYPE keytype)
{
	switch(keytype)
	{
	case CKK_RSA:				return "CKK_RSA";
	case CKK_DSA:				return "CKK_DSA";
	case CKK_DH:				return "CKK_DH";
	//case CKK_ECDSA:				return "CKK_ECDSA";
	case CKK_EC:  return "CKK_EC | CKK_ECDSA";
	case CKK_X9_42_DH:  return "CKK_X9_42_DH";
	case CKK_KEA:  return "CKK_KEA";
	case CKK_GENERIC_SECRET:  return "CKK_GENERIC_SECRET";
	case CKK_RC2:  return "CKK_RC2";
	case CKK_RC4:  return "CKK_RC4";
	case CKK_DES:  return "CKK_DES";
	case CKK_DES2:  return "CKK_DES2";
	case CKK_DES3:  return "CKK_DES3";
	case CKK_CAST:  return "CKK_CAST";
	case CKK_CAST3:  return "CKK_CAST3";
	//case CKK_CAST5:  return "CKK_CAST5";
	case CKK_CAST128:  return "CKK_CAST128 | CKK_CAST5";
	case CKK_RC5:  return "CKK_RC5";
	case CKK_IDEA:  return "CKK_IDEA";
	case CKK_SKIPJACK:  return "CKK_SKIPJACK";
	case CKK_BATON:  return "CKK_BATON";
	case CKK_JUNIPER:  return "CKK_JUNIPER";
	case CKK_CDMF:  return "CKK_CDMF";
	case CKK_AES:  return "CKK_AES";
	case CKK_BLOWFISH:  return "CKK_BLOWFISH";
	case CKK_TWOFISH:  return "CKK_TWOFISH";
	case CKK_SECURID:  return "CKK_SECURID";
	case CKK_HOTP:  return "CKK_HOTP";
	case CKK_ACTI:  return "CKK_ACTI";
	case CKK_CAMELLIA:  return "CKK_CAMELLIA";
	case CKK_ARIA:  return "CKK_ARIA";
	case CKK_VENDOR_DEFINED:  return "CKK_VENDOR_DEFINED";
	default: return "UNDEFINED KEY TYPE";
	}
}

CString CConvertData::Translate_CK_MECHANISM_TYPE(CK_MECHANISM_TYPE mechtype)
{
	switch(mechtype)
	{
	case CKM_RSA_PKCS_KEY_PAIR_GEN: return "CKM_RSA_PKCS_KEY_PAIR_GEN";
	case CKM_RSA_PKCS: return "CKM_RSA_PKCS";
	case CKM_RSA_X_509: return "CKM_RSA_X_509";
	case CKM_SHA_1: return "CKM_SHA_1";
	case CKM_MD5: return "CKM_MD5";
	case CKM_SHA256: return "CKM_SHA256";
	case CKM_SHA512: return "CKM_SHA512";
	case CKM_AES_ECB: return "CKM_AES_ECB";
	case CKM_AES_CBC: return "CKM_AES_CBC";
	case CKM_AES_CBC_PAD: return "CKM_AES_CBC_PAD";
	case CKM_DES_ECB: return "CKM_DES_ECB";
	case CKM_DES_CBC: return "CKM_DES_CBC";
	case CKM_DES_CBC_PAD: return "CKM_DES_CBC_PAD";
	case CKM_DES3_ECB: return "CKM_DES3_ECB";
	case CKM_DES3_CBC: return "CKM_DES3_CBC";
	case CKM_DES3_CBC_PAD: return "CKM_DES3_CBC_PAD";
	case CKM_AES_KEY_GEN: return "CKM_AES_KEY_GEN";
	case CKM_DES_KEY_GEN: return "CKM_DES_KEY_GEN";			
	case CKM_DES2_KEY_GEN: return "CKM_DES2_KEY_GEN";			
	case CKM_DES3_KEY_GEN: return "CKM_DES3_KEY_GEN";
	case CKM_DES_CBC_ENCRYPT_DATA: return "CKM_DES_CBC_ENCRYPT_DATA";
	case CKM_DES_ECB_ENCRYPT_DATA: return "CKM_DES_ECB_ENCRYPT_DATA";
	case CKM_DES3_ECB_ENCRYPT_DATA: return "CKM_DES3_ECB_ENCRYPT_DATA";
	case CKM_DES3_CBC_ENCRYPT_DATA: return "CKM_DES3_CBC_ENCRYPT_DATA";
	case CKM_AES_ECB_ENCRYPT_DATA: return "CKM_AES_ECB_ENCRYPT_DATA";
	case CKM_AES_CBC_ENCRYPT_DATA: return "CKM_AES_CBC_ENCRYPT_DATA";
	case CKM_SHA256_RSA_PKCS: return "CKM_SHA256_RSA_PKCS";
	default: return "UNDEFINED MECHANISM TYPE";
	}
}

CString CConvertData::Translate_CK_ATTRIBUTE_TYPE(CK_ATTRIBUTE_TYPE attType)
{
	switch(attType)
	{
	case  CKA_CLASS: return "CKA_CLASS";
	case  CKA_TOKEN: return "CKA_TOKEN";
	case  CKA_PRIVATE: return "CKA_PRIVATE" ;
	case  CKA_LABEL:		return "CKA_LABEL";            
	case  CKA_APPLICATION        :		return "CKA_APPLICATION";
	case  CKA_VALUE:		return "CKA_VALUE";
	case  CKA_OBJECT_ID:		return "CKA_OBJECT_ID";          
	case  CKA_CERTIFICATE_TYPE:		return "CKA_CERTIFICATE_TYPE";   
	case  CKA_ISSUER:		return "CKA_ISSUER";             
	case  CKA_SERIAL_NUMBER:		return "CKA_SERIAL_NUMBER";      
	case  CKA_AC_ISSUER:		return "CKA_AC_ISSUER";          
	case  CKA_OWNER:		return "CKA_OWNER";              
	case  CKA_ATTR_TYPES:		return "CKA_ATTR_TYPES";         
	case  CKA_TRUSTED:		return "CKA_TRUSTED";
	//case :return "";
	case CKA_CERTIFICATE_CATEGORY:	return "CKA_CERTIFICATE_CATEGORY";
	case CKA_JAVA_MIDP_SECURITY_DOMAIN:		return "CKA_JAVA_MIDP_SECURITY_DOMAIN";
	case CKA_URL:	return "CKA_URL";
	case CKA_HASH_OF_SUBJECT_PUBLIC_KEY:	return "CKA_HASH_OF_SUBJECT_PUBLIC_KEY";
	case CKA_HASH_OF_ISSUER_PUBLIC_KEY:	return "CKA_HASH_OF_ISSUER_PUBLIC_KEY";
	case CKA_CHECK_VALUE:	return "CKA_CHECK_VALUE";
	case  CKA_KEY_TYPE:		return "CKA_KEY_TYPE";           
	case  CKA_SUBJECT:		return "CKA_SUBJECT";            
	case  CKA_ID:		return "CKA_ID";                 
	case  CKA_SENSITIVE:		return "CKA_SENSITIVE";          
	case  CKA_ENCRYPT:		return "CKA_ENCRYPT";            
	case  CKA_DECRYPT:		return "CKA_DECRYPT";            
	case  CKA_WRAP:		return "CKA_WRAP";               
	case  CKA_UNWRAP:		return "CKA_UNWRAP";             
	case  CKA_SIGN:		return "CKA_SIGN";               
	case  CKA_SIGN_RECOVER:		return "CKA_SIGN_RECOVER";       
	case  CKA_VERIFY:		return "CKA_VERIFY";             
	case  CKA_VERIFY_RECOVER:		return "CKA_VERIFY_RECOVER";     
	case  CKA_DERIVE:		return "CKA_DERIVE";             
	case  CKA_START_DATE:		return "CKA_START_DATE";         
	case  CKA_END_DATE :		return "CKA_END_DATE";          
	case  CKA_MODULUS :		return "CKA_MODULUS";           
	case  CKA_MODULUS_BITS:		return "CKA_MODULUS_BITS";       
	case  CKA_PUBLIC_EXPONENT:		return "CKA_PUBLIC_EXPONENT";    
	case  CKA_PRIVATE_EXPONENT:		return "CKA_PRIVATE_EXPONENT";   
	case  CKA_PRIME_1:		return "CKA_PRIME_1";            
	case  CKA_PRIME_2:		return "CKA_PRIME_2";            
	case  CKA_EXPONENT_1:		return "CKA_EXPONENT_1";         
	case  CKA_EXPONENT_2:		return "CKA_EXPONENT_2";         
	case  CKA_COEFFICIENT:		return "CKA_COEFFICIENT";        
	case  CKA_PRIME:		return "CKA_PRIME";              
	case  CKA_SUBPRIME:		return "CKA_SUBPRIME";           
	case  CKA_BASE:		return "CKA_BASE"; 
	case CKA_PRIME_BITS:return "CKA_PRIME_BITS";
	case CKA_SUBPRIME_BITS:return "CKA_SUBPRIME_BITS";
	//case CKA_SUB_PRIME_BITS:return "CKA_SUB_PRIME_BITS";
	case  CKA_VALUE_BITS:		return "CKA_VALUE_BITS";         
	case  CKA_VALUE_LEN:		return "CKA_VALUE_LEN";          
	case  CKA_EXTRACTABLE:		return "CKA_EXTRACTABLE";        
	case  CKA_LOCAL:		return "CKA_LOCAL";               
	case  CKA_NEVER_EXTRACTABLE:		return "CKA_NEVER_EXTRACTABLE";   
	case  CKA_ALWAYS_SENSITIVE:		return "CKA_ALWAYS_SENSITIVE";    
	case  CKA_KEY_GEN_MECHANISM:		return "CKA_KEY_GEN_MECHANISM";   
	case  CKA_MODIFIABLE:		return "CKA_MODIFIABLE";          
	//case  CKA_ECDSA_PARAMS:		return "CKA_ECDSA_PARAMS";
	case CKA_EC_PARAMS:return "CKA_EC_PARAMS";
	case  CKA_EC_POINT:		return "CKA_EC_POINT";            
	case  CKA_SECONDARY_AUTH:		return "CKA_SECONDARY_AUTH";
	case  CKA_AUTH_PIN_FLAGS:		return "CKA_AUTH_PIN_FLAGS";
	case CKA_ALWAYS_AUTHENTICATE:return "CKA_ALWAYS_AUTHENTICATE";
	case CKA_WRAP_WITH_TRUSTED:return "CKA_WRAP_WITH_TRUSTED";
	case CKA_WRAP_TEMPLATE:return "CKA_WRAP_TEMPLATE";
	case CKA_UNWRAP_TEMPLATE:return "CKA_UNWRAP_TEMPLATE";
	case CKA_OTP_FORMAT:return "CKA_OTP_FORMAT";
	case CKA_OTP_LENGTH:return "CKA_OTP_LENGTH";
	case CKA_OTP_TIME_INTERVAL:return "CKA_OTP_TIME_INTERVAL";
	case CKA_OTP_USER_FRIENDLY_MODE:return "CKA_OTP_USER_FRIENDLY_MODE";
	case CKA_OTP_CHALLENGE_REQUIREMENT:return "CKA_OTP_CHALLENGE_REQUIREMENT";
	case CKA_OTP_TIME_REQUIREMENT:return "CKA_OTP_TIME_REQUIREMENT";
	case CKA_OTP_COUNTER_REQUIREMENT:return "CKA_OTP_COUNTER_REQUIREMENT";
	case CKA_OTP_PIN_REQUIREMENT:return "CKA_OTP_PIN_REQUIREMENT";
	case CKA_OTP_COUNTER:return "CKA_OTP_COUNTER";
	case CKA_OTP_TIME:return "CKA_OTP_TIME";
	case CKA_OTP_USER_IDENTIFIER:return "CKA_OTP_USER_IDENTIFIER";
	case CKA_OTP_SERVICE_IDENTIFIER:return "CKA_OTP_SERVICE_IDENTIFIER";
	case CKA_OTP_SERVICE_LOGO:return "CKA_OTP_SERVICE_LOGO";
	case CKA_OTP_SERVICE_LOGO_TYPE:return "CKA_OTP_SERVICE_LOGO_TYPE";
	case  CKA_HW_FEATURE_TYPE:		return "CKA_HW_FEATURE_TYPE";
	case  CKA_RESET_ON_INIT:		return "CKA_RESET_ON_INIT";       
	case  CKA_HAS_RESET:		return "CKA_HAS_RESET";              
	case CKA_PIXEL_X:return "CKA_PIXEL_X";
	case CKA_PIXEL_Y:return "CKA_PIXEL_Y";
	case CKA_RESOLUTION:return "CKA_RESOLUTION";
	case CKA_CHAR_ROWS:return "CKA_CHAR_ROWS";
	case CKA_CHAR_COLUMNS:return "CKA_CHAR_COLUMNS";
	case CKA_COLOR:return "CKA_COLOR";
	case CKA_BITS_PER_PIXEL:return "CKA_BITS_PER_PIXEL";
	case CKA_CHAR_SETS:return "CKA_CHAR_SETS";
	case CKA_ENCODING_METHODS:return "CKA_ENCODING_METHODS";
	case CKA_MIME_TYPES:return "CKA_MIME_TYPES";
	case CKA_MECHANISM_TYPE:return "CKA_MECHANISM_TYPE";
	case CKA_REQUIRED_CMS_ATTRIBUTES:return "CKA_REQUIRED_CMS_ATTRIBUTES";
	case CKA_DEFAULT_CMS_ATTRIBUTES:return "CKA_DEFAULT_CMS_ATTRIBUTES";
	case CKA_SUPPORTED_CMS_ATTRIBUTES:return "CKA_SUPPORTED_CMS_ATTRIBUTES";
	case CKA_ALLOWED_MECHANISMS: return "CKA_ALLOWED_MECHANISMS";
	case  CKA_KEY_ID :		return "CKA_KEY_ID";             
	case  CKA_DEFAULT_CERT:		return "CKA_DEFAULT_CERT"; 	   
	case  CKA_VENDOR_DEFINED:		return "CKA_VENDOR_DEFINED";   
	default:		return "UNKNOWN ATTRIBUTE TYPE";
	}
}*/