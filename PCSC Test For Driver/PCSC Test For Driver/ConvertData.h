#pragma once

#define CONV_OK					0
#define CONV_INVALID_CHAR_FOUND 1
#define CONV_BUFFER_TOO_SHORT	2
// CConvertData

class CConvertData : public CWnd
{
	DECLARE_DYNAMIC(CConvertData)

public:
	CConvertData();
	virtual ~CConvertData();

protected:
	DECLARE_MESSAGE_MAP()

public:
	//functions
	afx_msg int ChartoByte(unsigned char *bArray,unsigned char *ch, int chLen);
	afx_msg int ByteToChar(unsigned char *ch, unsigned char *bArray, int datalen);
	afx_msg int CStringToChar(CString str, unsigned char *ch, int dataLen);
	afx_msg int HexStringToByteArray(CString str, unsigned char* byteArr, int* dataLen);
	afx_msg int HexStringToByteArray(CString str, unsigned char* byteArr, unsigned long* dataLen);

	//returns the string meaning of the
	//afx_msg CString Translate_CK_OBJECT_CLASS(CK_OBJECT_CLASS objcla);
	//afx_msg CString Translate_CK_MECHANISM_TYPE(CK_MECHANISM_TYPE mechtype);
	//afx_msg CString Translate_CK_KEY_TYPE(CK_MECHANISM_TYPE keytype);
	//afx_msg CString Translate_CK_ATTRIBUTE_TYPE(CK_ATTRIBUTE_TYPE attType);

private:
	afx_msg unsigned char ChartoByte(unsigned char *ch);
	afx_msg int ByteToChar(unsigned char b, unsigned char *ch);
};


