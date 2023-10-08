#!/bin/bash

gnome-terminal -- bash -c "cat /dev/null > ~/.bash_history && history -c && echo 'History cleared [Enter]' && read"
