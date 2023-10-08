#!/bin/bash

NAZWA=""
KATALOG=""
CZASMOD=""
CZASMOD_ZNAK=""
UPRAW=""
ROZMIAR=""
ROZMIAR_ZNAK=""
ZAWAR=""

KOMENDA=""

if [[ "$EUID" != 0 ]] ; then 
zenity --info --title "Uprawnienia roota" --width 300 --text "Uruchom skrypt z uprawnieniami root, by móc wyszukiwać pliki w całym systemie.\n\nKliknij OK, aby przejść dalej"
fi

szukaj() {
	
	unset ${!FIND*} 
	
	if [ ${#KATALOG} != 0 ] ; then
	FIND1="find $KATALOG -type f"
	else
	FIND1="find . -type f"
	fi
	
	if [ ${#NAZWA} != 0 ] ; then
	FIND2="-name \"${NAZWA}*\""
	fi
	
	if [ ${#ROZMIAR} != 0 ] ; then
		if [[ $ROZMIAR_ZNAK == "mniejszy niż" ]] ; then
		FIND3="-size -${ROZMIAR}M" 
		elif [[ $ROZMIAR_ZNAK == "większy niż" ]] ; then
		FIND3="-size +${ROZMIAR}M"
		else
		FIND3="-size ${ROZMIAR}M"
		fi
	fi
	
	if [ ${#CZASMOD} != 0 ] ; then
		if [[ $CZASMOD_ZNAK == "wcześniej niż" ]] ; then
		FIND4="-mtime +$CZASMOD"
		elif [[ $CZASMOD_ZNAK == "póżniej niż" ]] ; then
		FIND4="-mtime -$CZASMOD"
		else
		FIND4="-mtime $CZASMOD"
		fi
	fi
	
	if [ ${#UPRAW} != 0 ] ; then
	FIND5="-perm $UPRAW"
	fi
	
	if [ ${#ZAWAR} != 0 ] ; then
	FIND6="-exec grep -n -H -o --text '$ZAWAR' {} +"
	else
	FIND6="-exec ls -lh {} +"
	fi
	
	echo "Szukanie..."
	
	RESULT=$(eval $FIND1 $FIND2 $FIND3 $FIND4 $FIND4 $FIND5 $FIND6)
	
	echo "Koniec"
	
	
	if [ ${#RESULT} == 0 ] ; then
	zenity --warning --width 300 --text "Nic nie znaleziono\n\nKliknij OK, aby szukać dalej"
	else 
	echo "$RESULT" | zenity --text-info --no-wrap --width 800 --height 300 --title "Wynik szukania:"
	fi
	
	if [[ $? == 1 ]]; then
	exit
	fi
}

while [[ true ]] ; do

KOMENDA=$(zenity --forms --title="Skrypt do szukania plików" \
--text="Wprowadź informacje o pliku:" \
--add-entry="Nazwa pliku:" \
--add-entry="Katalog:" \
--add-combo="Czas ost. modyfikacji:" \
--combo-values="wcześniej niż|później niż" \
--add-entry="w dniach:" \
--add-entry="Uprawnienia:" \
--add-combo="Rozmiar pliku:" \
--combo-values="mniejszy niż|większy niż|równy" \
--add-entry="w MB:" \
--add-entry="Zawartość pliku:" \
--height 300 --width 300)

if [[ $? == 1 ]] ; then
exit
fi

echo $KOMENDA

NAZWA=$(echo "$KOMENDA" | cut -d '|' -f 1)
KATALOG=$(echo "$KOMENDA" | cut -d '|' -f 2)
CZASMOD_ZNAK=$(echo "$KOMENDA" | cut -d '|' -f 3)
CZASMOD=$(echo "$KOMENDA" | cut -d '|' -f 4)
UPRAW=$(echo "$KOMENDA" | cut -d '|' -f 5)
ROZMIAR_ZNAK=$(echo "$KOMENDA" | cut -d '|' -f 6)
ROZMIAR=$(echo "$KOMENDA" | cut -d '|' -f 7)
ZAWAR=$(echo "$KOMENDA" | cut -d '|' -f 8)


szukaj

done

