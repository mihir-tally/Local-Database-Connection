#ifndef HELPER_HPP
#define HELPER_HPP

#define C_TAB                   '\t'
#define EOS                     '\0'
#define C_QUESTION              '?'
#define C_BACKSLASH             '\\'

void UTF8ToUTF16      (WStrPtr pDestination, CAStrPtr pSource, UInt32 pLength);
void UTF16ToUTF8      (AStrPtr pDestination, CWStrPtr pSource, UInt32 pLength);
void UTF16ToAscii     (AStrPtr pDest, CWStrPtr pSrc, Long pSrcLen);
void AsciiToUTF16     (WStrPtr pDestination, CAStrPtr pSource, UInt32 pLength);
void HandleBadReponse (CAStrPtr pBadResponse, StrPtr& pBadRespStr);

#endif //HELPER_HPP