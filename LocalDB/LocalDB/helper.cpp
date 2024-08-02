#include"common.hpp"

void UTF8ToUTF16 (WStrPtr pDestination, CAStrPtr pSource, UInt32 pLength)
{
    MultiByteToWideChar (CP_UTF8, 0, (LPCCH)pSource, pLength, pDestination, pLength * sizeof (Char));

    pDestination[pLength] = (WChar)EOS;
}

void UTF16ToUTF8 (AStrPtr pDestination, CWStrPtr pSource, UInt32 pLength)
{
    WideCharToMultiByte (CP_UTF8, WC_ERR_INVALID_CHARS, (LPCWCH)pSource, pLength, pDestination, pLength, NULL, NULL);

    pDestination[pLength] = EOS;
}

void UTF16ToAscii (AStrPtr pDest, CWStrPtr pSrc, Long pSrcLen)
{
    while (pSrcLen--)
        if (*pSrc > MAX_ASCII_CHAR_LIMIT) {

            *pDest++ = C_QUESTION;
            pSrc++;

        }
        else
            *pDest++ = (AChar)*pSrc++;

    *pDest = '\0';
}

void AsciiToUTF16 (WStrPtr pDestination, CAStrPtr pSource, UInt32 pLength)
{
    while (pLength--) {

        // copy to destination as UTF16
        *(pDestination++) = *(pSource++);
    }

    *pDestination = (WChar)EOS;
}