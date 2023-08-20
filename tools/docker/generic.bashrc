
################################################################################
# File:     generic.bashrc
# Created:  8/17/2023
# By:       Kaleb C
################################################################################

########################################
# History Control
########################################

HISTCONTROL=ignoredups:ignorespace
HISTSIZE=1000
HISTFILESIZE=2000

########################################
# Prompt Setup
########################################

if [ -z "$debian_chroot" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '

########################################
# Alias
########################################

alias ls='ls --color=auto'
alias ll='ls -a -l -F'
alias la='ls -A'
alias lc='ls -C -F'

########################################