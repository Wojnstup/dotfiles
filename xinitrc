#!/bin/bash
wal -i $(cat /home/wojnstup/Github/dwm/prevWallpaper) &
#cd /home/wojnstup/Github/dwm
#sudo make install
setxkbmap pl &
picom -b &
dunst &

#Status bar
{
	ram_icon="💾"
	net_icon="🌐"
	vol_icon=""
	cpu_icon="🖥️"

	UPDATES=$( pacman -Qu | wc -l)

	if (( $UPDATES == 0 )); then
	        UPDATES=""
	else
	        UPDATES="[Updates: $UPDATES] "
	fi

	while : ; do
		CPU=$( echo $cpu_icon:$( grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage }' | awk -F. '{print $1"."substr($2,1,2)"%"}' ) )
		MEM=$( echo $ram_icon:$(free -m | grep Mem | awk '{ print $3"M/"$2"M" }' ))
		NET=$( echo $net_icon:$( ifstat | grep eno1 | awk '{ print $6" ⇵ "$8 }' ) )
		VOL=$( echo $vol_icon:$( amixer -c 0 get Master | grep "Mono: Playback" | awk -F[ '{ print $2 }' | sed 's/]//g'))
		xsetroot -name " $UPDATES[$VOL] [$MEM] [$NET] [$CPU] $(date +"%H:%M %A")"
		sleep 2
	done 
} &

#exec dwm
while : ; do
	dwm
done

