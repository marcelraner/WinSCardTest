#include <iostream>
#include <string>
#include <winscard.h>

int main()
{
	SCARDCONTEXT    hScardContext;
	LONG            lReturn;
	LPTSTR			pmszReaders = NULL;
	LPTSTR			pReader;
	DWORD           cch = SCARD_AUTOALLOCATE;

	lReturn = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, 
									&hScardContext);
	if (SCARD_S_SUCCESS != lReturn) {
		std::cout << "Failed to establish a scard-context" << std::endl;
	}
	else {
		lReturn = SCardListReaders(hScardContext, NULL, (LPTSTR)&pmszReaders, 
								   &cch);
		switch (lReturn) {
		case SCARD_E_NO_READERS_AVAILABLE:
			std::cout << "No readers available" << std::endl;
			break;

		case SCARD_S_SUCCESS:
			LONG lReturn2;

			pReader = pmszReaders;
			while ('\0' != *pReader) {
				std::wcout << "Reader: " << pReader << std::endl;
				pReader = pReader + wcslen(pReader) + 1;
			}

			lReturn2 = SCardFreeMemory(hScardContext, pmszReaders);
			if (SCARD_S_SUCCESS != lReturn2) {
				std::cout << "Failed SCardFreeMemory" << std::endl;
			}

			break;

		default:
			std::cout << "Unhandled return code of SCardListReaders()" <<
				std::endl;
			break;
		}
	}

	std::cout << "Press enter to end application..." << std::endl;
	std::cin.get();

	return 0;
}
