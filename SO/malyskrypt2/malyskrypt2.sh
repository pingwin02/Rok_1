#!/bin/bash

NAZWA=""
KATALOG=""
CZASMOD=""
CZASMOD_MIN_MAX=""
UPRAW=""
ROZMIAR=""
ROZMIAR_MIN_MAX=""
ZAWAR=""
KOMENDA=""

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
		if [[ $ROZMIAR_MIN_MAX == ">" ]] ; then
		FIND3="-size +${ROZMIAR}M"
		elif [[ $ROZMIAR_MIN_MAX == "<" ]] ; then
		FIND3="-size -${ROZMIAR}M"
		else
		FIND3="-size ${ROZMIAR}M"
		fi
	fi
	
	if [ ${#CZASMOD} != 0 ] ; then
		if [[ $CZASMOD_MIN_MAX == ">" ]] ; then
		FIND4="-mtime +$CZASMOD"
		elif [[ $CZASMOD_MIN_MAX == "<" ]] ; then
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
	FIND6="-exec ls --color=auto -lh {} +"
	fi
	
	echo ""
	
	RESULT=$(eval $FIND1 $FIND2 $FIND3 $FIND4 $FIND4 $FIND5 $FIND6)
	
	if [ ${#RESULT} == 0 ] ; then
	echo "Nic nie znaleziono!"
	else 
	echo "$RESULT"
	fi
	
	echo ""
	
	read -p "Kliknij dowolny przycisk..."
}

while [[ $KOMENDA != 8 ]] ; do

echo ""
echo "Skrypt do szukania plików"
echo ""
echo "1. Nazwa pliku: $NAZWA"
echo "2. Katalog: $KATALOG"
echo "3. Czas ost. modyfik. (w dniach): $CZASMOD_MIN_MAX$CZASMOD"
echo "4. Uprawnienia: $UPRAW"
echo "5. Rozmiar pliku (w MB): $ROZMIAR_MIN_MAX$ROZMIAR"
echo "6. Zawartość pliku: $ZAWAR"
echo "7. Szukaj"
echo "8. Koniec"
echo ""
echo "Wpisz numer (1-8):"

read KOMENDA

if [ ${#KOMENDA} == 0 ] ; then
continue
fi

if [ $KOMENDA == 1 ] ; then
echo "Podaj nazwę pliku:"
read NAZWA
fi

if [ $KOMENDA == 2 ] ; then
echo "Podaj katalog:"
read KATALOG
fi

if [ $KOMENDA == 3 ] ; then
CZASMOD_MIN_MAX=""
echo "Podaj czas modyfikacji w dniach:"
read CZASMOD
	if [ ${#CZASMOD} != 0 ] ; then
	echo "> Wcześniej niż"
	echo "< Później niż"
	echo "= Dokładnie tyle"
	read CZASMOD_MIN_MAX
	fi
fi

if [ $KOMENDA == 4 ] ; then
echo "Podaj uprawnienia pliku:"
read UPRAW
fi

if [ $KOMENDA == 5 ] ; then
ROZMIAR_MIN_MAX=""
echo "Podaj rozmiar pliku w MB"
read ROZMIAR
	if [ ${#ROZMIAR} != 0 ] ; then
	echo "> Większy niż"
	echo "< Mniejszy niż"
	echo "= Równy"
	read ROZMIAR_MIN_MAX
	fi
fi

if [ $KOMENDA == 6 ] ; then
echo "Podaj zawartość pliku:"
read ZAWAR
fi

if [ $KOMENDA == 7 ] ; then
szukaj
fi

done
