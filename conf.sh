#! /bin/bash

if [[ -z $1 ]]; then
	picture="/home/wojnstup/Pictures/Wallpapers/$(ls -1 /home/wojnstup/Pictures/Wallpapers | fzf)"
	echo $picture > /home/wojnstup/Github/dwm/prevWallpaper
else
	if [[ $1 = /*  ]] || [[$1 = ~/* ]]; then
		echo $1 > /home/wojnstup/Github/dwm/prevWallpaper
	else
		echo "$(pwd)/$1" > /home/wojnstup/Github/dwm/prevWallpaper
	fi
	picture=$1
fi
echo $picture
wal -i $picture
cd /home/wojnstup/Github/dwm
lead='^\/\/COLOR-CONFIG-START$'
tail='^\/\/COLOR-CONFIG-END$'
sed -e "/$lead/,/$tail/{ /$lead/{p; r /home/wojnstup/.cache/wal/colors-wal-dwm.h
        }; /$tail/p; d }"  CONFIG > config.h

sudo make install

sel_bg=$(cat /home/wojnstup/.cache/wal/colors-wal-dwm.h | grep "sel_bg\[" | awk -F\" '{print $2}')
norm_bg=$(cat /home/wojnstup/.cache/wal/colors-wal-dwm.h | grep "norm_bg\[" | awk -F\" '{print $2}')

cat /home/wojnstup/.config/pipecat_turbo.template | sed "s/sel_bg/$sel_bg/g" | sed "s/norm_bg/$norm_bg/g" > /home/wojnstup/.config/pipecat_turbo.conf

pkill dwm
