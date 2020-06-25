#include "pch.h"
#include "Http.h"

wchar_t * __stdcall sendPOST(bool cot, wchar_t* _List, int _ListLen, bool FIRST_AND_LAST) {
	std::wstring urlList = L"http://invizzz.com:3333/nodejs/listenMQL.js";
	std::string answer_List = "";

	std::string head = "Cache-Control:no-cache, no-store";
	http.setHeader(head);

	if (FIRST_AND_LAST) { // ����������� ������ ��� ������������� � ��������������� �������. (List)
		std::wstring tempList = L"";
		for (long i = 0; i < _ListLen; ++i) {
			tempList += _List[i];
		} std::string List(tempList.begin(), tempList.end());

		answer_List = http.POST(urlList, List);

		std::wstring temp(answer_List.begin(), answer_List.end());
		return const_cast<wchar_t*>(temp.c_str());
	}
	
	if (cot) { // ����������� �� ������� ������� ����������� � ��������� ��������� �� ����...
		std::wstring tempBody = L"";
		for (long i = 0; i < _ListLen; ++i) {
			tempBody += _List[i];
		} std::string shortList(tempBody.begin(), tempBody.end());

		http.POST(urlList, shortList);

		// ������� ��������� ��� �������, ���������� ����� ������ ������, ��� �������� ����� ��������:
		// ������ �������� ������ ����� �������, ����� ��������� ������ ID:
		std::wstring tempID = L"";
		for (long i = 0; i < _ListLen; ++i) {
			if (_List[i] != L';') {
				tempID += _List[i];
			}
			else {
				tempID += L';';
				break;
			}
		} std::string ID(tempID.begin(), tempID.end());

		std::wstring temp(answer_List.begin(), answer_List.end());
		return const_cast<wchar_t*>(temp.c_str());
	}
	
	// � ����� ������ �������� �� ������ ������ ID, ����� �������� � ������� ������ � ��������:
	std::wstring tempID = L"";
	for (long i = 0; i < _ListLen; ++i) {
		tempID += _List[i];
	} std::string ID(tempID.begin(), tempID.end());

	answer_List = http.POST(urlList, ID);

	std::wstring temp(answer_List.begin(), answer_List.end());
	return const_cast<wchar_t*>(temp.c_str());
}