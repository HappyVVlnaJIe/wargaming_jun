#pragma once

bool WargamingIsEven(int value) { return value % 2 == 0; }

/*
*	����� % ���������� �������� 
*	�������� div ����� ������� ������ ������ ��� &
*/

bool MyIsEven(int value) {
	return !(value & 1);
}