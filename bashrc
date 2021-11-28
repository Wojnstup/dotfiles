#
# ~/.bashrc
#


# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
PS1='[\u@\h \W]\$ '


export PATH="$PATH:$HOME/bin"
export QT_QPA_PLATFORMTHEME="qt5ct"
export LC_ALL="C"

TMP="/tmp"

setxkbmap pl

export EDITOR=vim
export VISUAL=vim

alias dwmconf="cd /home/wojnstup/Github/dwm ; vim CONFIG"
alias qtileconf="vim /home/wojnstup/.config/qtile/config.py"
alias walconf="/home/wojnstup/Github/dwm/conf.sh"
alias storage="sudo mount /dev/sda1 /home/wojnstup/Storage"
#alias vim="emacs -nw"

[ -f ~/.fzf.bash ] && source ~/.fzf.bash

blue='\[\033[1;36m\]'
red='\[\033[1;31m\]'
pink='\[\033[1;35m\]'
#arrow='➤'
arrow=">"
reset='\[\033[m\]'

PS1="$blue\u$red@$pink\h $blue\W $arrow  $reset"

#Raylib export line, without it raylib programs won't compile
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
# Import colorscheme from 'wal' asynchronously
# &   # Run the process in the background.
# ( ) # Hide shell job control messages.
# Not supported in the "fish" shell.
(cat ~/.cache/wal/sequences &)

# Alternative (blocks terminal for 0-3ms)
cat ~/.cache/wal/sequences

