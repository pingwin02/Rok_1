#!/bin/bash

# Author : Damian Jankowski ( s188597@student.pg.edu.pl )
# Created On : 02.05.2022
# Last Modified By : Damian Jankowski ( s188597@student.pg.edu.pl )
# Last Modified On : 03.05.2022
# Version : 1.0
#
# Description : Temporary files cleaner and manager
#
#
# Licensed under GPL (see /usr/share/common-licenses/GPL for more details
# or contact # the Free Software Foundation for a copy)

. paths.rc
if [[ ${#TMP_DIRS} == 0 ]]; then
	echo "Błędny plik paths.rc. Wczytano domyślne ustawienie"
	TMP_DIRS="/tmp /var/tmp $HOME/.cache /var/log /var/cache"
fi
CHOSEN_PATH=$HOME

pomoc() {
echo "Pomoc - skrypt Czyszczenie plików tymczasowych/Menadżer pamięci v1.0"
echo
echo "Autor: Damian Jankowski s188597"
echo
echo "Skrypt ten ma za zadanie czyścić system z niepotrzebnych plików tymczasowych," 
echo "które często zajmują dużo miejsca. Pokazuje procent zajętego miejsca na dysku " 
echo "wraz z podziałem na typy plików. Z poziomu okna można usunąć wybrane pliki. " 
echo "Do pełnego działania skrypt potrzebuje uprawnień root. "
echo "Uruchomić go trzeba za pomocą sudo ./duzyskrypt.sh"
echo
echo "Podstawowe funkcjonalności skyptu:"
echo
echo "Informacje o użytkowniku - podaje informacje o zalogowanym użytkowniku, "
echo "wybór tej opcji pokaże więcej szczegółów"
echo
echo "Czas - pokazuje aktualną datę i godzinę, wybór opcji odświeży czas"
echo
echo "Zmień folder roboczy - wybranie tej opcji umożliwi zmianę aktualnego folderu roboczego, "
echo "kolejne opcje są od niego uzależnione"
echo
echo "Informacje o dysku - podaje informacje nt. procenta zajętości dysku oraz jego pojemności"
echo
echo "Szczegóły folderu roboczego - podaje rozmiar folderu roboczego, po wybraniu tej opcji "
echo "skrypt podaje listę wszystkich plików w tym folderze posortowanych rozmiarem oraz"
echo "w następnym oknie szczegóły nt. łącznego rozmiaru poszczególnych typów plików"
echo
echo "Usuń wybrane pliki z <folder roboczy> - umożliwa wybór, a potem usunięcie wybranych "
echo "plików z systemu. UWAGA! Proces jest nieodwracalny"
echo 
echo "Pliki tymczasowe - umożliwa wykasowanie plików tymczasowych z folderów wskazanych "
echo "w paths.rc. Zalecane jest zrestartowanie systemu po operacji."
echo 
}

wersja() {
echo "Wersja v1.0"
echo
echo "Damian Jankowski s188597"
echo
echo "Dat. ost. modyfikacji 03-05-2022"
}

while getopts hv OPT; do 
	case $OPT in
	h) pomoc;;
	v) wersja;;
	*) echo "Użycie [-h|-v] [pomoc|wersja]";;
	esac
	exit
done

menu() {
	menu=(\
	"Użytkownik"\
	"Czas"\
	"Zmień folder roboczy"\
	"Informacje o dysku"\
	"Szczegóły folderu roboczego" \
	"Usuń wybrane pliki z folderu $(echo; echo $CHOSEN_PATH)"\
	"Pliki tymczasowe"\
	"Pomoc"\
	)
	
	wartosc=(\
	"$USER"\
	"$(date)"\
	"Ustawiono $CHOSEN_PATH" \
	"$(df -H | tail -n +2 | grep -vE '^Filesystem|tmpfs|cdrom|loop|udev'|\
	 awk '{ print "Zajęte " $5 " " $3"/"$2 "   " $1 }')" \
	 "$(du -sh $CHOSEN_PATH 2> /dev/null) "\
	"<wybierz pliki>" \
	"Wykryto $(find $TMP_DIRS -type f 2> /dev/null | wc -l) plików tymczasowych w folderach: $(echo; du -sh $TMP_DIRS 2> /dev/null | sort -rh)"\
	 "<pomoc>"\
	)
	
	wiersz=()
	
	for (( i=0; i<${#menu[*]}; ++i )); do 
		wiersz+=( "${menu[$i]}" "${wartosc[$i]}" )
	done

	odp=$(zenity --list --title "Menedżer plików w systemie Linux" --text "Wybierz element z listy, by zobaczyć szczegóły" \
	--column Menu --column Wartość "${wiersz[@]}" --height 500 --width 650)

}

while [[ true ]] ; do

	menu

	if [[ $? == 1 ]] ; then
		exit
	fi
	
	if [[ $odp == ${menu[0]} ]] ; then
		who -u | zenity --text-info --width 350 --height 100 --title "Informacje o użytkowniku"
	fi
	
	if [[ $odp == ${menu[2]} ]] ; then
		odp=$(zenity --entry --title "Wybierz folder roboczy" --width 300 --text "w formacie /<sciezka>")
		if [[ -d "$odp" ]] && [[ $EUID == 0 || $odp != "/" ]]; then
			CHOSEN_PATH=$odp
		elif [[ ${#odp} != 0 ]]; then
			zenity --warning --width 300 --text "Podana ścieżka nie istnieje lub nie masz do niej dostępu!"
		fi
	fi
	
	if [[ $odp == ${menu[4]} ]] ; then
		zenity --list --title "Informacje o rozszerzeniach" --text "w folderze roboczym $CHOSEN_PATH" \
		--column "Łączny rozmiar" --column Rozszerzenie\
		$(find $CHOSEN_PATH -type f -print0 2> /dev/null | xargs -0 du -k | grep "\.[a-zA-Z]*$" | rev |\
		sed -e "s#\..*\t#\t#g" | rev | awk '{SUM[$2]+=$1} END{for (x in SUM) print SUM[x]/1024"MB",x}' |\
		sort -rh ) --width 300 --height 300
		find $CHOSEN_PATH -type f -exec du -Sh {} + 2> /dev/null | sort -rh | zenity --text-info --no-wrap --width 800 --height 300 --title "Lista plików w $CHOSEN_PATH"
	fi
	
	if [[ $odp == ${menu[5]} ]] ; then
		odp=$(zenity --file-selection --separator " " --title "Wybierz pliki do usunięcia" --multiple --filename $CHOSEN_PATH/*)
		if [[ $? == 0 ]]; then 
			zenity --question --width 300 --title "Jesteś pewny?" --text "Czy jesteś pewny, że chcesz usunąć: \n $odp ?\n\nProces jest nieodwracalny!"
			if [[ $? == 0 ]]; then 
				rm -v $odp
			fi
		fi
	fi
	
	if [[ $odp == ${menu[6]} ]] ; then
		zenity --question --width 300 --title "Jesteś pewny?" --text "Czy jesteś pewny, że chcesz usunąć pliki tymczasowe z folderów: \n $TMP_DIRS ?\n\nProces jest nieodwracalny!"
		odp6=$?
		if [[ $odp6 == 0 && $EUID == 0 ]]; then 
			find $TMP_DIRS -type f -delete
			zenity --question --width 300 --text "Zaleca się zrestartowanie systemu. Zrestartować teraz?"
			if [[ $? == 0 ]]; then
				shutdown --reboot now
			fi
		elif [[ $odp6 == 0 && $EUID != 0 ]]; then
			zenity --warning --width 300 --text "Brak uprawnień, uruchom skrypt z uprawnieniami root"
		fi
	fi
	
	if [[ $odp == ${menu[7]} ]] ; then
		pomoc | zenity --text-info --no-wrap --width 650 --height 450 --title "Pomoc"
	fi
	
	
	
done
