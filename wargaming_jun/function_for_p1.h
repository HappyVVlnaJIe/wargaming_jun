#pragma once

bool WargamingIsEven(int value) { return value % 2 == 0; }

/*
*	через % реализация понятнее 
*	операция div часто требует больше тактов чем &
*/

bool MyIsEven(int value) {
	return !(value & 1);
}