#pragma once

class InstrumentationHelper
{
public:
    static HRESULT LoadMachineSpecificId(_Out_ BSTR * pbstrMachineId, BOOL fLoadPathFromReg = FALSE);
    static HRESULT LoadUserSpecificId(_Out_ BSTR * pbstrUserId, BOOL fCreateIfNoExistence = FALSE);

private:
    static HRESULT CreateUserId(_In_z_ BSTR bstrUserIdFilePath);
};