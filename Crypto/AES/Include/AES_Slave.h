#ifndef __AES_Slave_H__
#define __AES_Slave_H__

extern void ProcessECBmode(const DWORD* Testkey, const DWORD* InData, DWORD* OutData,UINT8 EnDecrp);
extern void ProcessCBCmode(const DWORD* Testkey, const DWORD* InData, const DWORD* Iv, DWORD* OutData, UINT8 EnDecrp);
extern void ProcessCFBmode(const DWORD* Testkey, const DWORD* InData, const DWORD* Iv, DWORD* OutData, UINT8 EnDecrp);
extern void ProcessCTRmode(const DWORD* Testkey, const DWORD* InData, const DWORD* Iv, DWORD* OutData, UINT8 EnDecrp);
extern void ProcessOFBmode(const DWORD* Testkey, const DWORD* InData, const DWORD* Iv, DWORD* OutData, UINT8 EnDecrp);
#endif
